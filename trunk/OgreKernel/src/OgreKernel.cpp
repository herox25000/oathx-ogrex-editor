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
		 *	������Ⱦϵͳ
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
		// ��������
		m_pWorldSpace->destroyWorldSpace();
		delete m_pWorldSpace;

		// ɾ��OGRE��������
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
				�����ⲿ���ڴ�������
			*/
			Ogre::NameValuePairList miscPm;
			miscPm["externalWindowHandle"] = Ogre::StringConverter::toString((long)hWnd);
			
			/*
				�����ⲿ��Ⱦ����
			*/
			m_pRenderWindow = m_pRoot->createRenderWindow(sName, 
				w,h,bFullScreen,&miscPm);
	
		}

		// ��������ʧ�ܣ���Ĭ�ϴ���
		if (m_pRenderWindow == NULL)
		{
			m_pRenderWindow	= m_pRoot->initialise(true, sName);
		}
		
		// ��������ռ�
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
		// �����ƶ����߸ı��С
		m_pRenderWindow->windowMovedOrResized();
		
		/*
			����
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
