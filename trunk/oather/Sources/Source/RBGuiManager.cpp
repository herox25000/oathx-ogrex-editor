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

#include "RBGuiManager.h"

namespace HydraxEditor
{
	RBGuiManager::RBGuiManager(Ogre::Viewport* v, Ogre::SceneManager* sm)
		: mViewport(v)
		, mSceneMgr(sm)
		, isSetup(false)
	{
	}

	RBGuiManager::~RBGuiManager()
	{
        // Delete all windows
		deleteWindows();

		mGuiManager = 0;
	    mGuiCore = 0;
		mEditorCursorManager = 0;
	}

	bool RBGuiManager::setup()
	{
		try
		{
			// Initialize the Gui. This adds all of the default widget factories
			RBGui::Initialize( );

			// Choose the platform and cursor manager to use
			Mocha::RefPointer<RBGui::PlatformManager> platformManager;

#if defined( WIN32 )
			platformManager = new RBGui::Win32PlatformManager();
#elif defined( POSIX )
			manager = new RBGui::PosixPlatformManager( );
#elif defined( MACOSX )
			manager = new RBGui::MacOSPlatformManager( );
#endif
			mEditorCursorManager = new EditorCursorManager();

			// The following code can be used to setup a custom cursor
			/*
			Mocha::RefPointer<RBGui::BrushCursorManager> bcursorManager = new RBGui::BrushCursorManager( );
			bcursorManager->setCursorType( RBGui::CURSOR_TEXT, "cursor_text.png", Mocha::Vector2( 3.0f, 8.0f ), RBGui::BRUSHBLEND_INVERT );
			bcursorManager->setCursorType( RBGui::CURSOR_RESIZE, "cursor_resize.png", Mocha::Vector2( 8.0f, 8.0f ) );
			bcursorManager->setCursorType( RBGui::CURSOR_DEFAULT, "cursor.png" ); 

			mGuiManager->setCursorManager( bcursorManager );
			*/

			// Create the gui manager and set the default theme
			mGuiCore = new RBGui::Core(new RBGui::OgreTextureManager(), platformManager, new RBGui::OgreResourceManager());
			mGuiCore->getThemeManager().setDefaultTheme( "monochrome_grape.theme" );

			// Create a gui
			mGuiManager = mGuiCore->createGui("My Gui", new RBGui::OgreBrush(mSceneMgr, mViewport));
			
			// Set the default window animator and fader for all created windows
			mGuiManager->setDefaultWindowAnimator("Wobble");
			mGuiManager->setDefaultWindowFader("Simple");

			// Set the cursor manager to use
			mGuiManager->setCursorManager(static_cast<RBGui::CursorManager*>(mEditorCursorManager));

			// Add a render queue listener to draw the GUI
			mSceneMgr->addRenderQueueListener(new RBGui::OgreRenderQueueListener(*mGuiManager));
		}
		catch(RBGui::Exception &e)
		{
			LOG(e.getMessage());
			return false;
		}

		isSetup = true;

		return true;
	}

	void RBGuiManager::addWindow(RBGuiWindowBase *Window, const Ogre::String &Name)
	{
		Window->setName(Name);
		mWindows.push_back(Window);

		LOG(Name + " window added.");
	}

	RBGuiWindowBase* RBGuiManager::getWindow(const Ogre::String &Window)
	{
		std::vector<RBGuiWindowBase*>::iterator Ite;

		for(Ite=mWindows.begin(); Ite != mWindows.end(); Ite++)
		{
			if((*Ite)->getName() == Window)
			{
				return (*Ite);
			}
		}

		return static_cast<RBGuiWindowBase*>(NULL);
	}

	void RBGuiManager::deleteWindow(RBGuiWindowBase* Window)
	{
		std::vector<RBGuiWindowBase*>::iterator Ite;

		for(Ite=mWindows.begin(); Ite != mWindows.end(); Ite++)
		{
			if((*Ite) == Window)
			{
				Ogre::String Name = (*Ite)->getName();

				delete (*Ite);
				(*Ite) = 0;
				mWindows.erase(Ite);

                LOG(Name + " window deleted.");
				return;
			}
		}
	}

	void RBGuiManager::deleteWindow(const Ogre::String &Name)
	{
		std::vector<RBGuiWindowBase*>::iterator Ite;

		for(Ite=mWindows.begin(); Ite != mWindows.end(); Ite++)
		{
			if((*Ite)->getName() == Name)
			{
				delete (*Ite);
				(*Ite) = 0;
				mWindows.erase(Ite);

				LOG(Name + " window deleted.");
				return;
			}
		}
	}

	void RBGuiManager::deleteWindows()
	{
        Ogre::String Name;

		for (unsigned int k = 0; k < mWindows.size(); k++)
		{
			Name = mWindows.at(k)->getName();
			delete mWindows.at(k);
			LOG(Name + " window deleted.");
		}

		mWindows.clear();
	}

	void RBGuiManager::createWindows()
	{
		std::vector<RBGuiWindowBase*>::iterator Ite;

		for(Ite=mWindows.begin(); Ite != mWindows.end(); Ite++)
		{
			if(!(*Ite)->isCreated())
			{
				(*Ite)->create();

				LOG((*Ite)->getName() + " window created.");
			}
		}
	}

	bool RBGuiManager::setDefaultTheme(const Mocha::String &Theme)
	{
		if (isSetup)
		{
		    mGuiCore->getThemeManager().setDefaultTheme(Theme);
			return true;
		}

		return false;
	}

	void RBGuiManager::EditorCursorManager::onMouseMoved(const Mocha::Vector2& vPosition)
	{
	}

	void RBGuiManager::EditorCursorManager::onMousePressed(RBGui::MouseButtonID vButton)
	{
	}

	void RBGuiManager::EditorCursorManager::onMouseReleased(RBGui::MouseButtonID vButton)
	{
	}
}