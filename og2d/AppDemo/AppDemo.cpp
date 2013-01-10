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

	std::vector<Quad*> vQuad;
	/**
	 *
	 */
	void	AppDemo::createApplicationResource()
	{
		InputManager::getSingleton().addInputListener( new AppDemoInuptListener(this) );

		// 创建世界对象
		World* pWorld = System::getSingleton().createWorld("AppDemoWorld", Vector2D(0, 0), WORLD_PAGE_SECNE);
		if (pWorld)
		{
			// 创建演示场景
			Scene* pScene = pWorld->createScene("PageSceneFactory",
				"AppDemo", Vector2D(0, 0), Size(640*10, 480*10), Rect(Vector2D(0,0),Size(1024,768)));
			if (pScene)
			{
				m_pTexture = System::getSingleton().getRenderSystem()->createTextureFromFile("2.bmp");
			
				int nIndex = 0;

				for (int i=0; i<32; i++)
				{
					for (int j=0; j<32; j++)
					{
						char szTmp[128];
						sprintf(szTmp, "x=%d,y=%d", i, j);
						SceneNode* pNode = pScene->createSceneNode(szTmp, 
							Rect(Vector2D(i*640, j*480), Size(640, 480))
							);
						if (pNode)
						{
							Quad* pQuad = new Quad(pNode->getName(), Rect(Vector2D(0, 0), Size(640, 480)));

							pQuad->setTexture(m_pTexture);
							nIndex ++;
							if (nIndex > 4)
								nIndex = 0;
							pNode->attachRenderTarget(pQuad);
							vQuad.push_back(pQuad);
						}
					}
				}

			}
		}
	}
	
	/**
	 *
	 */
	void	AppDemo::clearUp()
	{
		std::vector<Quad*>::iterator it = vQuad.begin();
		while( it != vQuad.end() )
		{
			SAFE_DELETE((*it)); it = vQuad.erase(it);
		}
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