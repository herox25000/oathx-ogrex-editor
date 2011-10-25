#ifndef _____AppMain_H
#define _____AppMain_H

#include "Ogre.h"
#include "AppExport.h"

namespace Ogre
{
	class App_Export_API AppMain
	{
	public:
		AppMain(void);
		virtual ~AppMain(void);
		
		virtual	bool				createAppMainResource(HWND hWnd=NULL, int w=0, int h=0);
		virtual	void				update();
		virtual void				clearUp();
	protected:
		Root*						m_pRoot;
		RenderWindow*				m_pWnd;
		HWND						m_hWnd;
		SceneManager*				m_pSceneMgr;
		Camera*						m_pCamera;
	};
}

#endif

