#ifndef _____AppMain_H
#define _____AppMain_H

#include "Ogre.h"
#include "AppExport.h"

namespace Ogre
{
	class App_Export_API AppMain : public Singleton<AppMain>
	{
	public:
		static	AppMain&			getSingleton();

	public:
		AppMain(void);
		virtual ~AppMain(void);
		
		virtual	void				createMainApp(bool bAutoWnd=true, HWND hWnd=NULL, int w=0, int h=0);
		virtual	void				update();
		
	protected:
		virtual	void				setupResource();
		virtual	void				setupRenderSystem(const String& sName);
		virtual void				setupRenderWindow(HWND hWnd, int w, int h);
		virtual	void				setupSceneManager();
		virtual	void				setupCamera();
		virtual	void				setupViewport();
		virtual	void				setupAllResourceGroups();
	protected:
		Root*						m_pRoot;
		RenderWindow*				m_pWnd;
		HWND						m_hWnd;
		SceneManager*				m_pSceneMgr;
		Camera*						m_pCamera;
	};
}

#endif

