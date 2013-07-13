#ifndef _____Og2dD3D9Plugin_H
#define _____Og2dD3D9Plugin_H

#include "Og2dPlugin.h"
#include "Og2dD3D9RenderSystem.h"

namespace Og2d
{
	/**
	* \ingroup : RenderSystem_Direct3D9
	*
	* \os&IDE  : Microsoft Windows XP (SP2)  &  Microsoft Visual C++ .NET 2008
	*
	* \VERSION : 1.0
	*
	* \date    : 2012-07-22
	*
	* \Author  : lp
	*
	* \Desc    : D3D9 插件
	*
	* \bug     : 
	*
	* \Copyright (c) 2012 lp All rights reserved.
	*/
	class Og2d_D3D9_Export_API D3D9Plugin : public Plugin
	{
	public:
		/**
		 *
		 * \return 
		 */
		D3D9Plugin();

		/**
		 *
		 * \return 
		 */
		virtual ~D3D9Plugin();
		
		/** 获取插件名
		 *
		 * \return 
		 */
		virtual const String&	getTypeName() const;

		/** 安装插件
		 *
		 */
		virtual void			install();

		/** 卸载插件
		 *
		 */
		virtual void			uninstall();
	protected:
		D3D9RenderSystem*		m_pRenderSystem;
	};	
}

#endif