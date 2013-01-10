#ifndef _____Og2dExampleApp_H
#define _____Og2dExampleApp_H

#include "Og2d.h"

namespace Og2d
{
	/**
	* \ingroup : AppDemo
	*
	* \os&IDE  : Microsoft Windows XP (SP2)  &  Microsoft Visual C++ .NET 2008
	*
	* \VERSION : 1.0
	*
	* \date    : 2012-07-23
	*
	* \Author  : lp
	*
	* \Desc    : 
	*
	* \bug     : 
	*
	* \Copyright (c) 2012 lp All rights reserved.
	*/
	class ExampleApp
	{
	public:
		/**
		 *
		 * \param hIst 
		 * \param w 
		 * \param h 
		 * \param bFullScreen 
		 * \param name 
		 * \return 
		 */
		ExampleApp(const String& name, int w, int h, bool bFullScreen);

		/**
		 *
		 * \param void 
		 * \return 
		 */
		virtual ~ExampleApp(void);

		/**
		 *
		 */
		virtual	bool		createApplicationResource();

		/**
		 *
		 */
		virtual	void		go();

		/**
		 *
		 */
		virtual	void		clearUp();

	protected:
		HWND				m_hWnd;
		System*				m_pSystem;
		String				m_szAppName;
	};
}

#endif
