#ifndef _____Og2dPlugin_H
#define _____Og2dPlugin_H

#include "Og2dTypes.h"

namespace Og2d
{
	/**
	* \ingroup : Og2d
	*
	* \os&IDE  : Microsoft Windows XP (SP2)  &  Microsoft Visual C++ .NET 2008
	*
	* \VERSION : 1.0
	*
	* \date    : 2012-07-22
	*
	* \Author  : lp
	*
	* \Desc    : 插件支持基类
	*
	* \bug     : 
	*
	*/
	class Og2d_Export_API Plugin
	{
	public:
		/** 构造函数
		 *
		 * \return 
		 */
		Plugin();

		/** 析构函数
		 *
		 * \return 
		 */
		virtual ~Plugin();

		/** 获取插件名
		 *
		 * \return 
		 */
		virtual const String&	getTypeName() const = 0;

		/** 安装插件
		 *
		 */
		virtual void			install() = 0;

		/** 卸载插件
		 *
		 */
		virtual void			uninstall() = 0;
	};
}

#endif