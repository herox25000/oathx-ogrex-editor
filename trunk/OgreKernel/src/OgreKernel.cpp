#include "OgreKernel.h"
#include "OgreWorldSpace.h"

namespace Ogre
{
	template<> OgreKernel*	Singleton<OgreKernel>::msSingleton = NULL;
	OgreKernel&		OgreKernel::getSingleton()
	{
		assert(msSingleton != NULL);  return (*msSingleton);
	}

	OgreKernel*		OgreKernel::getSingletonPtr()
	{
		return msSingleton;
	}

	//////////////////////////////////////////////////////////////////////////
	//
	//////////////////////////////////////////////////////////////////////////
	OgreKernel::OgreKernel(void)
		:m_pRoot(NULL), m_pRenderWindow(NULL), m_pWorldSpace(NULL)
	{
		m_pWorldSpace = new WorldSpace();
	}
	
	//////////////////////////////////////////////////////////////////////////
	OgreKernel::~OgreKernel(void)
	{

	}
	
	//////////////////////////////////////////////////////////////////////////
	bool	OgreKernel::createKernel(const String& sPluginPath, const String& sResourceConfigFilePath)
	{
		m_pRoot = new Root(sPluginPath);
		assert(m_pRoot != NULL);

		Ogre::ConfigFile cf;
		cf.load(sResourceConfigFilePath);

		Ogre::ConfigFile::SectionIterator seci = cf.getSectionIterator();

		Ogre::String secName, typeName, archName;
		while (seci.hasMoreElements())
		{
			secName = seci.peekNextKey();
			Ogre::ConfigFile::SettingsMultiMap *settings = seci.getNext();
			Ogre::ConfigFile::SettingsMultiMap::iterator i;

			for (i = settings->begin(); i != settings->end(); ++i)
			{
				typeName = i->first;
				archName = i->second;
				Ogre::ResourceGroupManager::getSingleton().addResourceLocation(
					archName, typeName, secName);
			}
		}

		/*
		 *	创建渲染系统
		 */
		Ogre::RenderSystemList::const_iterator pRend = m_pRoot->getAvailableRenderers().begin();
		while(pRend != m_pRoot->getAvailableRenderers().end())
		{
			Ogre::String rName = (*pRend)->getName();
			if (rName == "OpenGL Rendering Subsystem")
				break;

			pRend++;
		}
		Ogre::RenderSystem *rsys = *pRend;

		rsys->setConfigOption( "Colour Depth", "32" );
		rsys->setConfigOption( "Full Screen", "No" );
		rsys->setConfigOption( "VSync", "No" );
		rsys->setConfigOption( "Video Mode", "800 x 600" );
		rsys->setConfigOption( "Display Frequency", "60" );
		
		m_pRoot->setRenderSystem( rsys );
		
		return true;
	}

	//////////////////////////////////////////////////////////////////////////
	void		OgreKernel::renderOneFrame()
	{
		m_pRoot->renderOneFrame();
	}

	//////////////////////////////////////////////////////////////////////////
	void		OgreKernel::destroyKernel()
	{
		// 销毁世界
		m_pWorldSpace->destroyWorldSpace();
		delete m_pWorldSpace;

		// 删除OGRE根本对象
		if (m_pRoot != NULL)
			delete m_pRoot;

		m_pRoot = NULL;
	}

	//////////////////////////////////////////////////////////////////////////
	bool		OgreKernel::createRenderWindow(HWND hWnd, int w, int h,
		bool bFullScreen, const String& sName)
	{
		if (hWnd != NULL)
		{
			m_pRenderWindow	= m_pRoot->initialise(false, sName);

			/*
				设置外部窗口创建参数
			*/
			Ogre::NameValuePairList miscPm;
			miscPm["externalWindowHandle"] = Ogre::StringConverter::toString((long)hWnd);
			
			/*
				创建外部渲染窗口
			*/
			m_pRenderWindow = m_pRoot->createRenderWindow(sName, 
				w,h,bFullScreen,&miscPm);
	
		}

		// 若都创建失败，则默认创建
		if (m_pRenderWindow == NULL)
		{
			m_pRenderWindow	= m_pRoot->initialise(true, sName);
		}
		
		// 创建世界空间
		m_pWorldSpace->createWorldSpace(Vector3(0,50,500), Vector3(0,100, -300), 1, 10);

		return true;
	}
	
	//////////////////////////////////////////////////////////////////////////
	RenderWindow*	OgreKernel::getRenderWindow() const
	{
		return m_pRenderWindow;
	}

	//////////////////////////////////////////////////////////////////////////
	void			OgreKernel::windowMovedOrResized()
	{
		// 窗口移动或者改变大小
		m_pRenderWindow->windowMovedOrResized();
		
		/*
			重设
		*/
		Viewport* pView = m_pWorldSpace->getViewport();
		if (pView != NULL)
		{
			m_pWorldSpace->getCamera()->setAspectRatio(
				Real(pView->getActualWidth()) / Real(pView->getActualHeight())
				);
		}
	}

	//////////////////////////////////////////////////////////////////////////
	Root*			OgreKernel::getRoot() const
	{
		return m_pRoot;
	}
}
