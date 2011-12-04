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

#include "EditorApp.h"

namespace HydraxEditor
{
	EditorApp::EditorApp()
		: mRoot(0)
		, mCamera(0)
		, mViewport(0)
		, mWindow(0)
		, mSceneMgr(0)
		, mEditorListener(0)
		, mRBGuiManager(0)
		, mHydraxManager(0)
	{
		// Provide a nice cross platform solution for locating the configuration files
		// On windows files are searched for in the current working directory, on OS X however
		// you must provide the full path, the helper function macBundlePath does this for us.
#if OGRE_PLATFORM == OGRE_PLATFORM_APPLE
		mResourcePath = macBundlePath() + "/Contents/Resources/";
#else
		mResourcePath = "";
#endif
	}

	EditorApp::~EditorApp()
	{
		if (mEditorListener)
		{
            delete mEditorListener;
		}
        if (mRoot)
		{
            delete mRoot;
		}
	}

	void EditorApp::go()
	{
		if (!setup())
		{
            return;
		}

        mRoot->startRendering();

        // Clean up
        destroyScene();
	}

	void EditorApp::end()
	{
		mRoot->queueEndRendering();
	}

	bool EditorApp::setup()
    {
        mRoot = new Root(mResourcePath + "ogreplugins.cfg");

        setupResources();

        bool carryOn = configure();
        if (!carryOn) 
		{
			return false;
		}

		// Load resources
		loadResources();

        chooseSceneManager();
        createCamera();
        createViewports();

        // Set default mipmap level
        TextureManager::getSingleton().setDefaultNumMipmaps(5);

		// Setup RBGui system
		mRBGuiManager = new RBGuiManager(mViewport, mSceneMgr);
		mRBGuiManager->setup();

		// Initialize Hydrax's manager
		mHydraxManager = new HydraxManager(mSceneMgr, mCamera, mViewport);

		// Create the scene
        createScene();

		// Create our editor listener
        createEditorListener();

        return true;
    }

	bool EditorApp::configure()
    {
        // Show the configuration dialog and initialise the system
        // You can skip this and use root.restoreConfig() to load configuration
        // settings if you were sure there are valid ones saved in ogre.cfg
        if(mRoot->showConfigDialog())
		{
            // If returned true, user clicked OK so initialise
            // Here we choose to let the system create a default rendering window by passing 'true'
            mWindow = mRoot->initialise(true, "Hydrax editor v"+Ogre::StringConverter::toString(static_cast<float>(HYDRAX_EDITOR_VERSION)));
            return true;
        }
        else
		{
            return false;
        }
    }

	void EditorApp::chooseSceneManager()
    {
        // Create the SceneManager, in this case a generic one
        mSceneMgr = mRoot->createSceneManager("TerrainSceneManager");
    }

	void EditorApp::createCamera()
    {
        // Create the camera
        mCamera = mSceneMgr->createCamera("HydraxEditorCam");
        mCamera->setNearClipDistance(1.0f);
    }

	void EditorApp::createEditorListener()
    {
        mEditorListener = new EditorListener(mWindow, mCamera, mRBGuiManager, mHydraxManager);
        mRoot->addFrameListener(mEditorListener);	
    }
	
    void EditorApp::createScene()
	{  
        // Hydrax
		mHydraxManager->create();

		// RBGui
		mRBGuiManager->addWindow(static_cast<RBGuiWindowBase*>(new TopMenu(mRBGuiManager->getGuiManager(), mWindow)), "TopMenu");
		mRBGuiManager->addWindow(static_cast<RBGuiWindowBase*>(new WOptionsWindow(mRBGuiManager->getGuiManager())), "WOptionsWindow");
		mRBGuiManager->addWindow(static_cast<RBGuiWindowBase*>(new WParametersWindow(mRBGuiManager->getGuiManager())), "WParametersWindow");
		mRBGuiManager->addWindow(static_cast<RBGuiWindowBase*>(new EnvironementWindow(mRBGuiManager->getGuiManager())), "EnvironementWindow");
		mRBGuiManager->addWindow(static_cast<RBGuiWindowBase*>(new DebugWindow(mRBGuiManager->getGuiManager(), mWindow)), "DebugWindow");

		mRBGuiManager->createWindows();
	}

    void EditorApp::destroyScene()
	{
		delete mRBGuiManager;
	}

    void EditorApp::createViewports()
    {
        // Create one viewport, entire window
        mViewport = mWindow->addViewport(mCamera);
        mViewport->setBackgroundColour(ColourValue(0,0,0));

        // Alter the camera aspect ratio to match the viewport
        mCamera->setAspectRatio(Real(mViewport->getActualWidth()) / Real(mViewport->getActualHeight()));
    }

    void EditorApp::setupResources()
    {
        // Load resource paths from config file
        ConfigFile cf;
        cf.load(mResourcePath + "resources.cfg");

        // Go through all sections & settings in the file
        ConfigFile::SectionIterator seci = cf.getSectionIterator();

        String secName, typeName, archName;
        while (seci.hasMoreElements())
        {
            secName = seci.peekNextKey();
            ConfigFile::SettingsMultiMap *settings = seci.getNext();
            ConfigFile::SettingsMultiMap::iterator i;
            for (i = settings->begin(); i != settings->end(); ++i)
            {
                typeName = i->first;
                archName = i->second;
#if OGRE_PLATFORM == OGRE_PLATFORM_APPLE
                // OS X does not set the working directory relative to the app,
                // In order to make things portable on OS X we need to provide
                // the loading with it's own bundle path location
                ResourceGroupManager::getSingleton().addResourceLocation(
                    String(macBundlePath() + "/" + archName), typeName, secName);
#else
                ResourceGroupManager::getSingleton().addResourceLocation(
                    archName, typeName, secName);
#endif
            }
        }
    }

	void EditorApp::loadResources(void)
	{
		// Initialise, parse scripts etc
		ResourceGroupManager::getSingleton().initialiseAllResourceGroups();
	}

}