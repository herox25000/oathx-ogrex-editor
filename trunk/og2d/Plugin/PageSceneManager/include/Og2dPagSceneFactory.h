#ifndef _____Og2dPageSceneFactory_H
#define _____Og2dPageSceneFactory_H

#include "Og2dSceneFactory.h"

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
	* \Desc    : 
	*
	* \bug     : 
	*
	* \Copyright (c) 2012 lp All rights reserved.
	*/
	class Og2d_PSM_Export_API PageSceneFactory : public SceneFactory
	{
	public:
		/** 构造函数
		 *
		 * \param typeName 
		 * \return 
		 */
		PageSceneFactory(const String& typeName);

		/** 析构函数
		 *
		 * \return 
		 */
		virtual ~PageSceneFactory();

		/** 创建场景管理器
		 *
		 * \param szName	场景名
		 * \param vOrigin	场景原点
		 * \param cSize		场景尺寸
		 * \param rcView	视口尺寸
		 * \return 
		 */
		virtual	Scene*			createScene(const String& szName, const Vector2D& vOrigin, const Size& cSize, 
			const Rect& rcView);
	};
}

#endif