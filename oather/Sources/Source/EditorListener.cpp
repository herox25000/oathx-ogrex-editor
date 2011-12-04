/*
--------------------------------------------------------------------------------
This source file is part of Hydrax editor.
Visit ---

Copyright (C) 2007 Xavier Verguín González <xavierverguin@hotmail.com>
                                           <xavyiy@gmail.com>

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software Foundation, Inc.,
59 Temple Place - Suite 330, Boston, MA  02111-1307, USA, or go to
http://www.gnu.org/copyleft/gpl.html.
--------------------------------------------------------------------------------
*/

#include "EditorListener.h"
#include "EditorApp.h"

namespace HydraxEditor
{

	EditorListener::EditorListener(RenderWindow* win, 
			Camera* cam, 
			RBGuiManager *rbguiman,
			HydraxManager *hm)
        : mCamera(cam)
		, mWindow(win)
		, mRBGuiManager(rbguiman)
		, mHydraxManager(hm)
		, mTranslateVector(Vector3::ZERO)
		, mMoveScale(325.0f)
		, mRotScale(45)
		, mFirst(true)
		, mLeftPressed(false)
		, mInScroll(false)
		, mInputManager(0)
		, mMouse(0)
		, mKeyboard(0)
	{
		using namespace OIS;

		LOG("*** Initializing OIS ***");
		
		// Setup param list
		size_t data;
		mWindow->getCustomAttribute( "WINDOW", &data );

		std::ostringstream windowString;
		windowString << data;

		OIS::ParamList paramList;
		paramList.insert( std::make_pair( std::string( "WINDOW" ), windowString.str( ) ) );
		paramList.insert( std::make_pair( std::string( "w32_mouse" ), std::string( "DISCL_FOREGROUND" ) ) );
		paramList.insert( std::make_pair( std::string( "w32_mouse" ), std::string( "DISCL_NONEXCLUSIVE" ) ) );
		paramList.insert( std::make_pair( std::string( "w32_keyboard" ), std::string( "DISCL_FOREGROUND" ) ) );
		paramList.insert( std::make_pair( std::string( "w32_keyboard" ), std::string( "DISCL_NONEXCLUSIVE" ) ) );

		// Create input object using parameter list
		mInputManager = OIS::InputManager::createInputSystem( paramList );

		// Create all devices
		mKeyboard = static_cast<Keyboard*>(mInputManager->createInputObject( OISKeyboard, true ));
		mMouse = static_cast<Mouse*>(mInputManager->createInputObject( OISMouse, true ));

		// Set initial mouse clipping size
		windowResized(mWindow);

		// Register as a Window listener
		WindowEventUtilities::addWindowEventListener(mWindow, this);

		// Register as a RenderSystem listener
		Ogre::Root::getSingleton().getRenderSystem()->addListener(this);

		// Registret OIS listeners
		mMouse->setEventCallback(this);
		mKeyboard->setEventCallback(this);
	}

	EditorListener::~EditorListener()
	{
		// Remove ourself as a Window listener
		WindowEventUtilities::removeWindowEventListener(mWindow, this);

		// Remove as a RenderSystem listener
		Ogre::Root::getSingleton().getRenderSystem()->removeListener(this);

		windowClosed(mWindow);
	}

	void EditorListener::updateMouseWindowMetrics()
	{
		int x;
		int y;
		size_t w;
		size_t h;
		size_t depth;
		mWindow->getMetrics(w, h, depth,
			                x, y);

		const OIS::MouseState& state = mMouse->getMouseState();
		state.width = (int)w;
		state.height = (int)h;
	}

	void EditorListener::windowResized(RenderWindow* rw)
	{
        int x;
		int y;
		size_t w;
		size_t h;
		size_t depth;
		mWindow->getMetrics(w, h, depth, 
			                x, y);

		const OIS::MouseState& state = mMouse->getMouseState();
		state.width = (int)w;
		state.height = (int)h;
	}

	void EditorListener::windowClosed(RenderWindow* rw)
	{
		if (rw == mWindow)
		{
			if (mInputManager)
			{
				mInputManager->destroyInputObject(mMouse);
				mInputManager->destroyInputObject(mKeyboard);

				OIS::InputManager::destroyInputSystem(mInputManager);
				mInputManager = 0;
			}
		}
	}

	void EditorListener::moveCamera(const Ogre::FrameEvent& evt)
	{
		// Make all the changes to the camera
		// Note that YAW direction is around a fixed axis (freelook style) rather than a natural YAW
		// (e.g. airplane)
		mCamera->yaw(mRotX*evt.timeSinceLastFrame);
		mCamera->pitch(mRotY*evt.timeSinceLastFrame);
		mCamera->moveRelative(mTranslateVector*evt.timeSinceLastFrame);
		
		mRotX = 0; mRotY = 0;

		if (mInScroll)
		{
			mTranslateVector.z = 0;

			mInScroll = false;
		}
	}

	bool EditorListener::frameRenderingQueued(const FrameEvent& evt)
	{
		mMouse->capture();
	    mKeyboard->capture();

		if (mWindow->isClosed())	
		{
			return false;
		}

		return true;
	}

	bool EditorListener::frameStarted(const FrameEvent& evt)
	{
		moveCamera(evt);

		updateMouseWindowMetrics();

		// Check camera height
		Ogre::RaySceneQuery * raySceneQuery = 
			EditorApp::getSingleton()->getSceneManager()->
			     createRayQuery(Ogre::Ray(mCamera->getPosition() + Ogre::Vector3(0,1000000,0), 
				                Vector3::NEGATIVE_UNIT_Y));
		Ogre::RaySceneQueryResult& qryResult = raySceneQuery->execute();
        Ogre::RaySceneQueryResult::iterator i = qryResult.begin();
        if (i != qryResult.end() && i->worldFragment)
        {
			if (mCamera->getPosition().y < i->worldFragment->singleIntersection.y + 30)
			{
                mCamera->
				     setPosition(mCamera->getPosition().x, 
                                 i->worldFragment->singleIntersection.y + 30, 
                                 mCamera->getPosition().z);
			}
        }

		delete raySceneQuery;

		// Update RBGui
		mRBGuiManager->getGuiManager()->tick(evt.timeSinceLastFrame);
		static_cast<DebugWindow*>(EditorApp::getSingleton()->getRBGuiManager()->getWindow("DebugWindow"))->update();

		// Update hydrax
		mHydraxManager->getHydrax()->update(evt.timeSinceLastFrame);

		return true;
	}

	bool EditorListener::frameEnded(const FrameEvent& evt)
	{
		return true;
	}

	void EditorListener::eventOccurred( const Ogre::String& eventName, const Ogre::NameValuePairList *parameters )
	{
		// Redraw the Gui if the device has been restored
		if (eventName == "DeviceRestored")
		{
			RBGui::Core::Get().invalidate();
		}
	}

    bool EditorListener::mouseMoved(const OIS::MouseEvent& vEvent)
	{
		// For RBGui
		// Get absolute position
		Mocha::Vector2 abspos = Mocha::Vector2(static_cast<float>(vEvent.state.X.abs),
			                                   static_cast<float>(vEvent.state.Y.abs));
		if (mFirst)
		{
			mPrevPos = abspos;
			mFirst = false;
		}

		// Inject mouse scroll event
		if (vEvent.state.Z.rel != 0)
		{   
			mRBGuiManager->getGuiManager()->injectMouseScrolled(static_cast<float>(vEvent.state.Z.rel / 120.0f), abspos);

			mTranslateVector.z = -7.5f*mMoveScale*(Ogre::Math::Abs(vEvent.state.Z.rel)/vEvent.state.Z.rel);
			mInScroll = true;
		}

		// Calculate relative position in pixels
		Mocha::Vector2 relpos = abspos - mPrevPos;
		mPrevPos = abspos;

		// Send event to gui
		mRBGuiManager->getGuiManager()->injectMouseMotion(relpos, abspos);

		// Rotate camera
		if (mLeftPressed)
		{
			mRotX = -relpos.x/5;
			mRotY = -relpos.y/5;

			mRBGuiManager->getCursorManager()->setCursor(RBGui::CURSOR_CROSS);
		}

		return true;
	}
	
	bool EditorListener::mousePressed(const OIS::MouseEvent& vEvent, OIS::MouseButtonID id)
	{
		// Send event to gui
		mRBGuiManager->getGuiManager()->injectMousePressed(
			// Button id
			static_cast<RBGui::MouseButtonID>(id), 
			// Mouse position
			Mocha::Vector2(static_cast<float>(vEvent.state.X.abs),
			               static_cast<float>(vEvent.state.Y.abs)));

		// Determinate if there is a window under the mouse
		if ((id == OIS::MB_Left || id == OIS::MB_Middle) && mRBGuiManager->getGuiManager()->findWindowAtPoint(mPrevPos) == NULL)
		{
			mLeftPressed = true;

			mRBGuiManager->getCursorManager()->setCursor(RBGui::CURSOR_CROSS);
		}

		return true;
	}

    bool EditorListener::mouseReleased(const OIS::MouseEvent& vEvent, OIS::MouseButtonID id)
	{
		// Send event to gui
		mRBGuiManager->getGuiManager()->injectMouseReleased(
			// Button id
			static_cast<RBGui::MouseButtonID>(id), 
			// Mouse position
			Mocha::Vector2(static_cast<float>(vEvent.state.X.abs),
			               static_cast<float>(vEvent.state.Y.abs)));
		
		// Update our TopMenu(For info see TopMenu.h update() comments)
		static_cast<TopMenu*>(EditorApp::getSingleton()->getRBGuiManager()->getWindow("TopMenu"))->update();

		// Release left button
		if (id == OIS::MB_Left || id == OIS::MB_Middle)
		{
			mLeftPressed = false;

			mRBGuiManager->getCursorManager()->setCursor(RBGui::CURSOR_DEFAULT);
		}
		
		return true;
	}

	bool EditorListener::keyPressed(const OIS::KeyEvent& vEvent)
	{
		// We don't need to translate key IDs because the Key IDs in the Gui are the same as OIS
		mRBGuiManager->getGuiManager()->injectKeyPressed(static_cast<RBGui::KeyID>(vEvent.key));

		// Exit if escape key is pressed
		if (vEvent.key == OIS::KC_ESCAPE)
        {
			EditorApp::getSingleton()->end();
		}

		if (vEvent.key == OIS::KC_N)
		{
			mHydraxManager->getHydrax()->saveCfg("Saved.hdx");
		}

		// Move camera left
		if (vEvent.key == OIS::KC_A || vEvent.key == OIS::KC_LEFT)
		{
			mTranslateVector.x = -mMoveScale;
		}
		// Move camera right
		if (vEvent.key == OIS::KC_D || vEvent.key == OIS::KC_RIGHT)
		{
			mTranslateVector.x = mMoveScale;
		}
		// Move camera forward
		if (vEvent.key == OIS::KC_W || vEvent.key == OIS::KC_UP)
		{
			mTranslateVector.z = -mMoveScale;
		}
		// Move camera backward
		if (vEvent.key == OIS::KC_S || vEvent.key == OIS::KC_DOWN)
		{
			mTranslateVector.z = mMoveScale;
		}

		return true;
	}
	
	bool EditorListener::keyReleased(const OIS::KeyEvent& vEvent)
	{
		// We don't need to translate key IDs because the Key IDs in the Gui are the same as OIS
		mRBGuiManager->getGuiManager()->injectKeyReleased((RBGui::KeyID)vEvent.key);
		
		// Restore camera left/right to 0
		if (vEvent.key == OIS::KC_A || vEvent.key == OIS::KC_D || vEvent.key == OIS::KC_LEFT || vEvent.key == OIS::KC_RIGHT)
		{
			mTranslateVector.x = 0;
		}
		// Restore camera forward/backward to 0
		if (vEvent.key == OIS::KC_W || vEvent.key == OIS::KC_S || vEvent.key == OIS::KC_UP || vEvent.key == OIS::KC_DOWN)
		{
			mTranslateVector.z = 0;
		}

		return true;
	}
}