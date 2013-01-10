#include "Og2dExampleApp.h"
#include "Og2dDebug.h"

namespace Og2d
{
	/**
	 *
	 * \param hWnd 
	 * \param msg 
	 * \param wParam 
	 * \param lParam 
	 * \return 
	 */
	LRESULT CALLBACK MsgProc(HWND hWnd ,UINT msg, WPARAM wParam, LPARAM lParam)
	{
		static int s_nClickCount = 0;
		if (GetCapture() != hWnd && s_nClickCount > 0)
			s_nClickCount = 0;

		SInputEvent curEvt;
		curEvt.iType = EIPT_INVALD;

		switch (msg)
		{
		case WM_DESTROY:
			{
				PostQuitMessage( 0 );
			}
			return FALSE;

		case WM_MOUSEMOVE:
			{
				curEvt.iType			= EIPT_MOUSE;
				curEvt.mouse.x			= (float)(LOWORDINT(lParam));
				curEvt.mouse.y			= (float)(HIWORDINT(lParam));
				curEvt.mouse.evt		= MS_MOVE;
				
				InputManager::getSingleton().injectEvent(curEvt);
			}
			return FALSE;

		case WM_LBUTTONDOWN:
			{
				s_nClickCount++;
				SetCapture(hWnd);

				curEvt.iType			= EIPT_MOUSE;
				curEvt.mouse.x			= (float)(LOWORDINT(lParam));
				curEvt.mouse.y			= (float)(HIWORDINT(lParam));
				curEvt.mouse.evt		= MS_LBTNDOWN;
				
				InputManager::getSingleton().injectEvent(curEvt);
			}
			return FALSE;

		case WM_LBUTTONUP:
			{
				s_nClickCount --;
				if (s_nClickCount < 1)
				{
					s_nClickCount = 0;
					ReleaseCapture();
				}

				curEvt.iType			= EIPT_MOUSE;
				curEvt.mouse.x			= (float)(LOWORDINT(lParam));
				curEvt.mouse.y			= (float)(HIWORDINT(lParam));
				curEvt.mouse.evt		= MS_LBTNUP;
				
				InputManager::getSingleton().injectEvent(curEvt);
			}
			return FALSE;

		case WM_MBUTTONDOWN:
			{
				s_nClickCount++;
				SetCapture(hWnd);

				curEvt.iType			= EIPT_MOUSE;
				curEvt.mouse.x			= (float)(LOWORDINT(lParam));
				curEvt.mouse.y			= (float)(HIWORDINT(lParam));
				curEvt.mouse.evt		= MS_MBTNDOWN;
				
				InputManager::getSingleton().injectEvent(curEvt);
			}
			return FALSE;

		case WM_MBUTTONUP:
			{
				s_nClickCount --;
				if (s_nClickCount < 1)
				{
					s_nClickCount = 0;
					ReleaseCapture();
				}

				curEvt.iType			= EIPT_MOUSE;
				curEvt.mouse.x			= (float)(LOWORDINT(lParam));
				curEvt.mouse.y			= (float)(HIWORDINT(lParam));
				curEvt.mouse.evt		= MS_MBTNUP;

				InputManager::getSingleton().injectEvent(curEvt);
			}
			return FALSE;

		case WM_RBUTTONDOWN:
			{
				s_nClickCount++;
				SetCapture(hWnd);

				curEvt.iType			= EIPT_MOUSE;
				curEvt.mouse.x			= (float)(LOWORDINT(lParam));
				curEvt.mouse.y			= (float)(HIWORDINT(lParam));
				curEvt.mouse.evt		= MS_RBTNDOWN;
				
				InputManager::getSingleton().injectEvent(curEvt);
			}
			return FALSE;

		case WM_RBUTTONUP:
			{
				s_nClickCount --;
				if (s_nClickCount < 1)
				{
					s_nClickCount = 0;
					ReleaseCapture();
				}

				curEvt.iType			= EIPT_MOUSE;
				curEvt.mouse.x			= (float)(LOWORDINT(lParam));
				curEvt.mouse.y			= (float)(HIWORDINT(lParam));
				curEvt.mouse.evt		= MS_RBTNUP;
				
				InputManager::getSingleton().injectEvent(curEvt);
			}
			return FALSE;
		case WM_KEYDOWN:
			{
				BYTE allKey[256];
				memset(allKey, 0, 256);

				curEvt.iType			= EIPT_KEY;
				curEvt.keyboard.code	= (EKEY_CODE)wParam;
				curEvt.keyboard.evt		= KEYEVT_DOWN;

				WORD KeyAsc = 0;
				GetKeyboardState(allKey);
				ToAscii((UINT)wParam,(UINT)lParam,allKey,&KeyAsc,0);

				curEvt.keyboard.shift	= ((allKey[VK_SHIFT] & 0x80)!=0);
				curEvt.keyboard.control	= ((allKey[VK_CONTROL] & 0x80)!=0);
				curEvt.keyboard.wchar	= (KeyAsc & 0x00ff);
				
				InputManager::getSingleton().injectEvent(curEvt);
			}
			return FALSE;
		case WM_KEYUP:
			{
				BYTE allKey[256];
				memset(allKey, 0, 256);

				curEvt.iType			= EIPT_KEY;
				curEvt.keyboard.code	= (EKEY_CODE)wParam;
				curEvt.keyboard.evt		= KEYEVT_UP;

				WORD KeyAsc = 0;
				GetKeyboardState(allKey);
				ToAscii((UINT)wParam,(UINT)lParam,allKey,&KeyAsc,0);

				curEvt.keyboard.shift	= ((allKey[VK_SHIFT] & 0x80)!=0);
				curEvt.keyboard.control	= ((allKey[VK_CONTROL] & 0x80)!=0);
				curEvt.keyboard.wchar	= (KeyAsc & 0x00ff);
			
				InputManager::getSingleton().injectEvent(curEvt);
			}
			return FALSE;
		case WM_MOUSEWHEEL:
			{
				curEvt.iType			= EIPT_MOUSE;
				curEvt.mouse.z			= (float)(short(HIWORD(wParam))/120);
				curEvt.mouse.evt		= MS_WHEEL;
				curEvt.mouse.x			= (float)LOWORDINT(lParam);
				curEvt.mouse.y			= (float)HIWORDINT(lParam);
				
				InputManager::getSingleton().injectEvent(curEvt);
			}
			return FALSE;
		}

		return ::DefWindowProc(hWnd,msg,wParam,lParam);
	}
	
	//////////////////////////////////////////////////////////////////////////
	static CHAR	szClassName[] = "Og2d Win32";

	/**
	 *
	 * \param void 
	 * \return 
	 */
	ExampleApp::ExampleApp( const String& name, int w, int h, bool bFullScreen) : m_hWnd(NULL),m_pSystem(NULL)
	{
		WNDCLASSEX wc;
		wc.cbClsExtra		= 0;
		wc.cbWndExtra		= 0;
		wc.cbSize			= sizeof(WNDCLASSEX);
		wc.hbrBackground	= NULL;
		wc.hCursor			= NULL;
		wc.hIcon			= NULL;
		wc.hIconSm			= NULL;
		wc.hInstance		= GetModuleHandle(NULL);
		wc.lpfnWndProc		= MsgProc;
		wc.lpszClassName	= szClassName;
		wc.lpszMenuName		= NULL;
		wc.style			= CS_HREDRAW | CS_VREDRAW;

		if (::RegisterClassEx(&wc))
		{
			RECT rcSize = {
				0, 
				0,
				w,
				h
			};

			DWORD style = WS_SYSMENU | WS_BORDER | WS_CAPTION | WS_CLIPCHILDREN | WS_CLIPSIBLINGS;
			if (bFullScreen)
			{
				style = WS_POPUP;
			}
	
			AdjustWindowRect(&rcSize, style, FALSE);

			int nWidth	= rcSize.right - rcSize.left;
			int nHeight = rcSize.bottom - rcSize.top;

			int nLeft	= (GetSystemMetrics(SM_CXSCREEN) - nWidth) / 2;
			int nTop	= (GetSystemMetrics(SM_CYSCREEN) - nHeight) / 2;

			m_hWnd = ::CreateWindow(szClassName, 
									name.c_str(), 
									style,
									nLeft,
									nTop,
									nWidth,
									nHeight,
									NULL,
									NULL, 
									GetModuleHandle(NULL),
									NULL);
		
			if (m_hWnd)
			{
				::MoveWindow(m_hWnd, nLeft, nTop, nWidth, nHeight, TRUE);
				::ShowWindow(m_hWnd,
					SW_SHOW);
				::UpdateWindow(m_hWnd);

				// create og2d system
				m_pSystem = new System();
				if (m_pSystem)
				{
					StringValue Value;
					Value["HWND"]		= StringUtil::ToSTRING((size_t)(m_hWnd));
					Value["FULLSCREEN"]	= StringUtil::ToSTRING(bFullScreen);
					Value["W"]			= StringUtil::ToSTRING(w);
					Value["H"]			= StringUtil::ToSTRING(h);
					Value["VSVY"]		= StringUtil::ToSTRING(true);
#ifdef _DEBUG
					m_pSystem->startup("Plugin_d.win32", "Og2dLog.html", Value);
#else
					m_pSystem->startup("Plugin.win32",
						"Og2dLog.html", Value);
#endif
				}
			}
		}
	}

	/**
	 *
	 * \param void 
	 * \return 
	 */
	ExampleApp::~ExampleApp(void)
	{
		if (m_pSystem)
			m_pSystem->shutdown();

		SAFE_DELETE(m_pSystem);
	}

	/**
	 *
	 */
	void	ExampleApp::createApplicationResource()
	{
		
	}
	
	/**
	 *
	 */
	void	ExampleApp::go()
	{
		static DWORD dwLastTime = ::timeGetTime();
		static float fFPSTime	= 0;
		static DWORD dwFPS		= 0;

		MSG msg;
		ZeroMemory(&msg, sizeof(MSG));
		
		while (WM_QUIT != msg.message)
		{
			if (::PeekMessage(&msg, NULL, 0L, 0L, PM_REMOVE))
			{
				TranslateMessage( &msg );
				DispatchMessage( &msg );
			}
			else
			{
				DWORD dwCurrentTime	= ::timeGetTime();
				float fElapsed		= (float)(dwCurrentTime - dwLastTime) * 0.001f;

				if (m_pSystem)
					m_pSystem->run(fElapsed);
				
				dwFPS ++;

				fFPSTime += fElapsed;
				if (fFPSTime >= 1.0f)
				{
					char szFPS[64];
					sprintf(szFPS, "System Updat: FPS=%d", dwFPS);
					LogManager::getSingleton().logMessage(INFO_NORMAL,
						szFPS);

					fFPSTime = 0;
					dwFPS	 = 0;
				}
	
				dwLastTime = dwCurrentTime;
			}

			if ((GetAsyncKeyState(VK_ESCAPE) & 0x8000 ? 1 : 0))
			{
				PostQuitMessage(0);
			}
		}
	}

	/**
	 *
	 */
	void	ExampleApp::clearUp()
	{

	}
}
