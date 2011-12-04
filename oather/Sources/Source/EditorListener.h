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

#ifndef _EditorListener_H_
#define _EditorListener_H_

#include "Prerequisites.h"

#include "RBGuiManager.h"
#include "HydraxManager.h"

using namespace Ogre;

namespace HydraxEditor
{

	class EditorListener: 
		public FrameListener, 
		public WindowEventListener, 
		public RenderSystem::Listener,
		public OIS::MouseListener,
		public OIS::KeyListener
	{
	public:

		/** Constructor
		@param win Our Ogre::RenderWindow pointer
		@param cam Our Ogre::Camera pointer
		@param rbguiman HydraxEditor::RBGuiManager pointer
		@param hm HydraxEditor::HydraxManager pointer
		*/
		EditorListener(RenderWindow* win, 
			Camera* cam, 
			RBGuiManager* rbguiman,
			HydraxManager* hm);

		/** Destructor
		*/
		~EditorListener();

		/** Make sure mouse region is up to date
		 */
		void updateMouseWindowMetrics();

		/** From Ogre::FrameListener, process changes after 
		window resize
		@param rw Ogre::RenderWindow resized pointer
		*/
		void windowResized(RenderWindow* rw);

		/** From Ogre::FrameListener, process changes after 
		window close
		@param rw Ogre::RenderWindow closed pointer
		*/
		void windowClosed(RenderWindow* rw);

		/** Move camera 
		@param evt Ogre::FrameEvent
		*/
		void moveCamera(const FrameEvent& evt);

		/** Frame rendering queued
		@param evt Ogre::FrameEvent
		*/
		bool frameRenderingQueued(const FrameEvent& evt);

		/** Frame started
		@param evt Ogre::FrameEvent
		*/
		bool frameStarted(const FrameEvent& evt);

		/** Frame ended
		@param evt Ogre::FrameEvent
		*/
		bool frameEnded(const FrameEvent& evt);

		/** Mouse moved
		    @param vEvent OIS::MouseEvent&
		 */
		bool mouseMoved(const OIS::MouseEvent& vEvent);

		/** Mouse pressed
		    @param vEvent OIS::MouseEvent&
			@param id OIS::MouseButtonID
		 */
		bool mousePressed(const OIS::MouseEvent& vEvent, OIS::MouseButtonID id);

		/** Mouse released
		    @param vEvent OIS::MouseEvent&
			@param id OIS::MouseButtonID
		 */
        bool mouseReleased(const OIS::MouseEvent& vEvent, OIS::MouseButtonID id);

		/** Key released
		    @param vEvent OIS::KeyEvent&
		 */
        bool keyPressed(const OIS::KeyEvent& vEvent);

		/** Key released
		    @param vEvent OIS::KeyEvent&
		 */
		bool keyReleased(const OIS::KeyEvent& vEvent);

		/** For RBGui device lost
		@param eventName Event name
		@param parameters Ogre::NameValuePairList
		*/
		void eventOccurred(const Ogre::String& eventName, const Ogre::NameValuePairList *parameters);

	protected:
		/// Ogre::Camera pointer
		Camera* mCamera;
		/// Ogre::RenderWindow pointer
		RenderWindow* mWindow;
		/// HydraxEditor::RBGuiManager pointer
		RBGuiManager* mRBGuiManager;
		/// HydraxEditor::HydraxManager pointer
        HydraxManager* mHydraxManager;

		/// Our translate vector(for camera)
		Vector3 mTranslateVector;
		/// Mode scale constant
		float mMoveScale;
		/// Root scale constant
		Degree mRotScale;
		/// Our temporal rot axis
		Radian mRotX, mRotY;

		// For RBGui
		Mocha::Vector2 mPrevPos;
        bool mFirst;
		bool mLeftPressed;
		bool mInScroll;

		/// OIS Imput manager
		OIS::InputManager* mInputManager;
		/// OIS Mouse
		OIS::Mouse* mMouse;
		/// OIS Keyboard
		OIS::Keyboard* mKeyboard;
	};
};

#endif
