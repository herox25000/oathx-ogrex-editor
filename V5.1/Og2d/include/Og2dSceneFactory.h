#ifndef _____Og2dSceneFactory_H
#define _____Og2dSceneFactory_H

#include "Og2dScene.h"

namespace Og2d
{
	/**
	* \ingroup : Og2d
	*
	* \os&IDE  : Microsoft Windows XP (SP2)  &  Microsoft Visual C++ .NET 2008
	*
	* \VERSION : 1.0
	*
	* \date    : 2012-08-03
	*
	* \Author  : lp
	*
	* \Desc    : 场景工厂
	*
	* \bug     : 
	*
	* \Copyright (c) 2012 lp All rights reserved.
	*/
	class Og2d_Export_API SceneFactory
	{
	public:
		/** 构造函数
		 *
		 * \return 
		 */
		SceneFactory(int nType);

		/** 析构函数
		 *
		 * \return 
		 */
		virtual ~SceneFactory();

		/** 获取工厂类型名
		 *
		 * \return 
		 */
		virtual	int				getType() const;

		/** 创建场景管理器
		 *
		 * \param szName	场景名
		 * \param vOrigin	场景原点
		 * \param cSize		场景尺寸
		 * \param rcView	视口尺寸
		 * \return 
		 */
		virtual	Scene*			createScene(const String& szName, const Rect& rcBound);
	protected:
		int						m_nType;
	};
}

#endif