#include "AppDemo.h"
#include "Og2dDebug.h"

namespace Og2d
{
	/**
	 *
	 * \param name 
	 * \param w 
	 * \param h 
	 * \param bFullScreen 
	 * \return 
	 */
	AppDemo::AppDemo(const String& name, int w, int h, bool bFullScreen)
		: ExampleApp(name, w, h, bFullScreen)
	{
	}

	/**
	 *
	 * \param void 
	 * \return 
	 */
	AppDemo::~AppDemo(void)
	{
	}

	/**
	 *
	 */
	bool	AppDemo::createApplicationResource()
	{
		InputManager::getSingleton().addInputListener( new AppDemoInuptListener(this) );

		// 创建世界对象
		World* pWorld = System::getSingleton().createWorld("AppDemo", 
			Vector2D(0, 0), WORLD_PAGE_SECNE);
		if (pWorld)
		{
			
		}
		
		return true;
	}
	
	/**
	 *
	 */
	void	AppDemo::clearUp()
	{
		ExampleApp::clearUp();	
	}

	//////////////////////////////////////////////////////////////////////////
	/**
	 *
	 * \param pApp 
	 * \return 
	 */
	AppDemoInuptListener::AppDemoInuptListener(AppDemo* pApp)
		: m_pTheApp(pApp)
	{

	}

	/**
	 *
	 * \return 
	 */
	AppDemoInuptListener::~AppDemoInuptListener()
	{

	}

	/**
	 *
	 * \param iEvt 
	 * \return 
	 */
	bool	AppDemoInuptListener::OnEvent(const SInputEvent& iEvt)
	{
		switch (iEvt.iType)
		{
		case EIPT_KEY:
			{
				if (iEvt.keyboard.evt == KEYEVT_DOWN)
				{

				}
					
			}
			break;
		}

		return 0;
	}
}

//////////////////////////////////////////////////////////////////////////
/**
 *
 * \return 
 */
int main()
{
#ifdef _WIN32
	_CrtSetDbgFlag(_CRTDBG_LEAK_CHECK_DF | _CRTDBG_ALLOC_MEM_DF);
#endif
	// construct app
	Og2d::AppDemo app("AppDemo", 800, 600, 0);

	try{
		/*
		* create app all resource
		*/
		app.createApplicationResource();
		// start app;
		app.go();
		// clear app resource
		app.clearUp();
	}
	catch (Og2d::Exception& e)
	{
#if OG2D_PLATFORM == OG2D_PLATFORM_WIN32
		::MessageBox(NULL, e.getFullDescription().c_str(), NULL, MB_OKCANCEL);
#else
		printf(e.getFullDescription().c_str());
#endif
		app.clearUp();
	}

	return 0;
}