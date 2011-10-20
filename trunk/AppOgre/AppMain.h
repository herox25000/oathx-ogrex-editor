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
		
		virtual	bool				createMainAppResource(bool bAutoWnd=true, HWND hWnd=NULL, int w=0, int h=0);
		virtual	void				update();
		
	protected:
		Root*						m_pRoot;
		RenderWindow*				m_pWnd;
		HWND						m_hWnd;
	};
}

#endif

