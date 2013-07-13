#ifndef _____Og2dPageScenePlugin_H
#define _____Og2dPageScenePlugin_H

#include "Og2dPlugin.h"
#include "Og2dPagSceneFactory.h"

namespace Og2d
{
	/**
	* \ingroup : PageSceneManager
	*
	* \os&IDE  : Microsoft Windows XP (SP2)  &  Microsoft Visual C++ .NET 2008
	*
	* \VERSION : 1.0
	*
	* \date    : 2012-08-03
	*
	* \Author  : lp
	*
	* \Desc    : 页场景管理器插件
	*
	* \bug     : 
	*
	* \Copyright (c) 2012 lp All rights reserved.
	*/
	class Og2d_PSM_Export_API PageScenePlugin : public Plugin
	{
	public:
		/**
		 *
		 * \return 
		 */
		PageScenePlugin();

		/**
		 *
		 * \return 
		 */
		virtual ~PageScenePlugin();
		
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
	};	
}

#endif