#include "AppDemo.h"

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
		World* pWorld = System::getSingleton().createWorld("AppDemoWorld", 
			Vector2D(0, 0), WORLD_PAGE_SECNE);
		if (pWorld == NULL)
			return 0;
		
		// 创建演示场景
		Scene* pScene = pWorld->createScene("PageSceneFactory", "AppDemo",
			Vector2D(0, 0), Size(32, 32));
		if (pScene)
		{
			m_pTexture = System::getSingleton().getRenderSystem()->createTextureFromFile("../media/2.bmp");
			assert(m_pTexture != NULL);

			int row = 32;
			int col = 32;
			int w	= m_pTexture->getSize().w;
			int h	= m_pTexture->getSize().h;

			for (int i=0; i<col; i++)
			{
				for (int j=0; j<row; j++)
				{
					char szName[32];
					sprintf(szName, "%d", i * col + j);
					SceneNode* pNode = pScene->createSceneNode(szName, Vector2D(j * w, i * h));
					if (pNode)
					{
						Quad* pQuad = new Quad(szName, Rect(0, 0, w, h));
						if (pQuad)
						{
							pQuad->setTexture(m_pTexture);
							pNode->attachRenderTarget(pQuad);
						}
					}
				}
			}
		}

		return true;
	}
	
	/**
	 *
	 */
	void	AppDemo::clearUp()
	{
		dropAndNULL(m_pTexture);
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
					Viewport* pViewport = World::getSingletonPtr()->getViewport();
					if (pViewport == NULL)
						return 0;

					Vector2D vPos = pViewport->getPosition();

					switch( iEvt.keyboard.code )
					{
					case EKEY_KEY_W:
						{
							vPos.y -= 3;
						}
						break;
					case EKEY_KEY_S:
						{
							vPos.y += 3;
						}
						break;
					case EKEY_KEY_A:
						{
							vPos.x -= 3;
						}
						break;
					case EKEY_KEY_D:
						{
							vPos.x += 3;
						}
						break;
					}

					pViewport->setPosition(vPos);
				}
				else
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
	Og2d::AppDemo app("AppDemo", 1024, 768, 0);

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