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

#ifndef _EditorApp_H_
#define _EditorApp_H_

#include "Prerequisites.h"
#include "EditorListener.h"
#include "RBGuiManager.h"
#include "Singleton.h"
#include "HydraxManager.h"

using namespace Ogre;

namespace HydraxEditor
{

#if OGRE_PLATFORM == OGRE_PLATFORM_APPLE
	// This function will locate the path to our application on OS X,
	// unlike windows you can not rely on the curent working directory
	// for locating your configuration files and resources.
	std::string macBundlePath()
	{
		char path[1024];
		CFBundleRef mainBundle = CFBundleGetMainBundle();
		assert(mainBundle);

		CFURLRef mainBundleURL = CFBundleCopyBundleURL(mainBundle);
		assert(mainBundleURL);

		CFStringRef cfStringRef = CFURLCopyFileSystemPath( mainBundleURL, kCFURLPOSIXPathStyle);
		assert(cfStringRef);

		CFStringGetCString(cfStringRef, path, 1024, kCFStringEncodingASCII);

		CFRelease(mainBundleURL);
		CFRelease(cfStringRef);

		return std::string(path);
	}
#endif

	using namespace Ogre;

	/** Base hydrax editor application class
	 */
	class EditorApp : public HydraxEditor::Singleton<EditorApp>
	{
	public:
		/** Constructor
		*/
		EditorApp();

		/** Destructor
		*/
		~EditorApp();

		/** Start
		*/
		void go();

		/** End
		 */
		void end();

		/** Get Ogre::Root
		    @return Ogre::Root pointer
		 */
		inline Ogre::Root* getRoot()
		{
			return mRoot;
		}

		/** Get Ogre::Camera
		    @return Ogre::Camera
		 */
		inline Ogre::Camera* getCamera()
		{
			return mCamera;
		}

		/** Get our viewport
		    @return Ogre::Viewport pointer
		 */
		inline Ogre::Viewport* getViewport()
		{
			return mViewport;
		}

		/** Get our Scene Manager
		    @return Ogre::SceneManager pointer
		 */
		inline Ogre::SceneManager* getSceneManager()
		{
			return mSceneMgr;
		}

		/** Get our Ogre::RenderWindow pointer
		    @return Ogre::RenderWindow pointer
		 */
		inline Ogre::RenderWindow* getRenderWindow()
		{
			return mWindow;
		}

		/** Get our RBGuiManager
		    @return HydraxEditor::RBGuiManager
		 */
		inline RBGuiManager* getRBGuiManager()
		{
			return mRBGuiManager;
		}

		/** Get our HydraxEditor::HydraxManager pointer
		    @return HydraxEditor::HydraxManager pointer
		 */
		inline HydraxManager* getHydraxManager()
		{
			return mHydraxManager;
		}

	private:
		/// Ogre::Root pointer
		Root *mRoot;
		/// Ogre::Camera pointer
		Camera* mCamera;
        /// Ogre::Viewport pointer
		Viewport* mViewport;
		/// Ogre::SceneManager pointer
		SceneManager* mSceneMgr;
		/// Ogre::RenderWindow pointer
		RenderWindow* mWindow;
		/// EditorListener pointer 
		EditorListener* mEditorListener;
		/// HydraxEditor RBGuiManager pointer
		RBGuiManager* mRBGuiManager;
		/// HydraxEditor HydraxManager pointer
		HydraxManager* mHydraxManager;
		/// Resource path string
		Ogre::String mResourcePath;

		/** Sets up the application - returns false if the user chooses to abandon configuration. 
		*/
		bool setup();

		/** Configures the application - returns false if the user chooses to abandon configuration. 
		*/
		bool configure();

		/** Set our scene manager
		*/
		void chooseSceneManager();

		/** Create camera
		 */
		void createCamera();

		/** Create editor listener
		 */
		void createEditorListener();

		/** Create scene(Setting up hydrax, etc)
		 */
		void createScene();  

		/** Destroy scene
		 */
		void destroyScene();

		/** Create viewports 
		 */
		void createViewports();

		/** Set up ogre resources
		 */
		void setupResources();

		/** Load resources
		 */
		void loadResources();
	};
};

#endif