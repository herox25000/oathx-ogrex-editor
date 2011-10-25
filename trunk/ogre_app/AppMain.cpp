#include "AppMain.h"

namespace Ogre
{
	//////////////////////////////////////////////////////////////////////////
	//
	//////////////////////////////////////////////////////////////////////////
	AppMain::AppMain(void)
		:m_pRoot(NULL),m_pWnd(NULL),m_pSceneMgr(NULL),m_pCamera(NULL)
	{
		m_pRoot = new Root();
	}

	//////////////////////////////////////////////////////////////////////////
	AppMain::~AppMain(void)
	{
		if (m_pRoot != NULL)
		{
			delete m_pRoot;
			m_pRoot = NULL;
		}
	}

	//////////////////////////////////////////////////////////////////////////
	bool			AppMain::createAppMainResource(HWND hWnd/* =NULL */, int w/* =0 */, int h/* =0 */)
	{
		ConfigFile cf;
		cf.load("resources.cfg");

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
				ResourceGroupManager::getSingleton().addResourceLocation(
					archName, typeName, secName);
			}
		}

		if (hWnd != NULL)
		{
			if (m_pRoot->showConfigDialog())
			{
				m_pRoot->initialise(true);
			}
		}
		else
		{
			/*
			 *	创建渲染系统
			 */
			Ogre::RenderSystemList::iterator pRend = m_pRoot->getAvailableRenderers()->begin();
			while(pRend != m_pRoot->getAvailableRenderers()->end())
			{
				Ogre::String rName = (*pRend)->getName();
				if (rName == "OpenGL Rendering Subsystem")
					break;

				pRend++;
			}
			Ogre::RenderSystem *rsys = *pRend;

			rsys->setConfigOption("Colour Depth", "32" );
			rsys->setConfigOption( "Full Screen", "No" );
			rsys->setConfigOption( "VSync", "No" );
			rsys->setConfigOption( "Video Mode", "800 x 600" );
			rsys->setConfigOption( "Display Frequency", "60" );

			m_pRoot->setRenderSystem( rsys );
			
			/*
			 *	创建渲染窗口
			 */
			m_pRoot->initialise(false);

			NameValuePairList miscParams;
			miscParams["externalWindowHandle"] = StringConverter::toString((long)hWnd);
			m_pWnd = m_pRoot->createRenderWindow("OgreRenderWindow", 
				w,
				h,
				false,
				&miscParams
				);
			assert(m_pWnd != NULL);
		}

		/*
		*	创建场景管理器
		*/
		m_pSceneMgr = m_pRoot->createSceneManager(
				ST_GENERIC, 
				"AppSceneInstance"
				);
		if (m_pSceneMgr != NULL)
		{
			/*
			 *	创建摄像机
			 */
			m_pCamera = m_pSceneMgr->createCamera("AppMain");
			
			// 设置初始位置
			m_pCamera->setPosition(
					Vector3(0,0,500)
					);
			m_pCamera->lookAt(
				Vector3(0,0,-300)
				);
			m_pCamera->setNearClipDistance(5);
			
			// 设置视口
			Viewport* vp = m_pWnd->addViewport(m_pCamera);
			vp->setBackgroundColour(ColourValue(0,0,0));
			
			m_pCamera->setAspectRatio(
				Real(vp->getActualWidth()) / Real(vp->getActualHeight())
				);

			TextureManager::getSingleton().setDefaultNumMipmaps(5);

			// 安装资源组
			ResourceGroupManager::getSingleton().initialiseAllResourceGroups();
		}

		return true;
	}

	//////////////////////////////////////////////////////////////////////////
	void			AppMain::update()
	{
		m_pRoot->_fireFrameStarted();
		m_pWnd->update();
		m_pRoot->_fireFrameEnded();
	}

	//////////////////////////////////////////////////////////////////////////
	void			AppMain::clearUp()
	{

	}
}
