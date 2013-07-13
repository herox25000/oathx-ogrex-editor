#ifndef _____Og2dPageScene_H
#define _____Og2dPageScene_H

#include "Og2dScene.h"

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
	* \Desc    : 页场景管理器
	*
	* \bug     : 
	*
	* \Copyright (c) 2012 lp All rights reserved.
	*/
	class Og2d_PSM_Export_API PageScene : public Scene
	{
	public:
		/**
		 *
		 * \return 
		 */
		PageScene(const String& szName, const Vector2D& vPos, const Size& cSize);

		/**
		 *
		 * \return 
		 */
		virtual ~PageScene();

		/** 创建场景节点
		 *
		 * \param szName		场景节点名称
		 * \param rcBoundingBox 节点包围盒
		 * \return 
		 */
		virtual	SceneNode*	createSceneNode(const String& szName, const Vector2D& vPos);

		/** 获取场景节点
		 *
		 * \param szName 
		 * \return 
		 */
		virtual	SceneNode*	getSceneNode(const String& szName);

		/** 销毁场景节点
		 *
		 * \param szName 
		 */
		virtual	void		destroySceneNode(const String& szName);

		/** 销毁场景节点
		 *
		 * \param pSceneNode 
		 */
		virtual	void		destroySceneNode(SceneNode* pSceneNode);
		
		/** 销毁所有的场景节点
		 *
		 */
		virtual	void		destroyAllSceneNode();

		/**
		 *
		 * \param fElapsed 
		 */
		virtual	void		update(float fElapsed);
	protected:
		MapSceneNodeTab		m_MapSceneNode;
	};
}

#endif