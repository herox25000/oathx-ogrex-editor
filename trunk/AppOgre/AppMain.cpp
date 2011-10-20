#include "stdafx.h"
#include "AppMain.h"

namespace Ogre
{
	template<> AppMain*	Singleton<AppMain>::ms_Singleton = NULL;
	AppMain&	AppMain::getSingleton()
	{
		assert(ms_Singleton != NULL); return (*ms_Singleton);
	}

	//////////////////////////////////////////////////////////////////////////
	//
	//////////////////////////////////////////////////////////////////////////
	AppMain::AppMain(void)
		:m_pRoot(NULL),m_pWnd(NULL)
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
	bool			AppMain::createMainAppResource(bool bAutoWnd/* =true */, HWND hWnd/* =NULL */, int w/* =0 */, int h/* =0 */)
	{
		if (bAutoWnd)
		{

		}
		else
		{
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

			m_pRoot->initialise(false);

			NameValuePairList miscParams;
			miscParams["externalWindowHandle"] = StringConverter::toString((long)hWnd);
			m_pWnd = m_pRoot->createRenderWindow("OgreRenderWindow", 
				w,
				h,
				false,
				&miscParams
				);

			update();

			return true;
		}

		return 0;
	}

	//////////////////////////////////////////////////////////////////////////
	void			AppMain::update()
	{
		m_pRoot->renderOneFrame();
	}
}
