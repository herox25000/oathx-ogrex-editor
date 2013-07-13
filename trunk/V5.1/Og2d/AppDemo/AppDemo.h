#pragma once

#include "Og2dExampleApp.h"

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
	* \Desc    : ³ÌÐòÈë¿Ú
	*
	* \bug     : 
	*
	* \Copyright (c) 2012 lp All rights reserved.
	*/
	class AppDemo : public ExampleApp
	{
	public:
		/**
		 *
		 * \param name 
		 * \param w 
		 * \param h 
		 * \param bFullScreen 
		 * \return 
		 */
		AppDemo(const String& name, int w, int h, bool bFullScreen);

		/**
		 *
		 * \param void 
		 * \return 
		 */
		virtual ~AppDemo(void);

		/**
		 *
		 */
		virtual	bool	createApplicationResource();

		/**
		 *
		 */
		virtual	void	clearUp();
	private:
		Texture*		m_pTexture;
	};

	/**
	* \ingroup : AppDemo
	*
	* \os&IDE  : Microsoft Windows XP (SP2)  &  Microsoft Visual C++ .NET 2008
	*
	* \VERSION : 1.0
	*
	* \date    : 2012-08-11
	*
	* \Author  : lp
	*
	* \Desc    : 
	*
	* \bug     : 
	*
	* \Copyright (c) 2012 lp All rights reserved.
	*/
	class AppDemoInuptListener : public InputListener
	{
	public:
		/**
		 *
		 * \param pApp 
		 * \return 
		 */
		AppDemoInuptListener(AppDemo* pApp);

		/**
		 *
		 * \return 
		 */
		virtual ~AppDemoInuptListener();

		/**
		 *
		 * \param iEvt 
		 * \return 
		 */
		virtual	bool	OnEvent(const SInputEvent& iEvt);

	protected:
		AppDemo*		m_pTheApp;
	};
}
