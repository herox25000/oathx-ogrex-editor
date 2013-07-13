#ifndef _____Og2dSceneNode_H
#define _____Og2dSceneNode_H

#include "Og2dRenderTarget.h"
#include "Og2dNode.h"

namespace Og2d
{
	typedef map<String, RenderTarget*>::type MapRenderTarget;

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
	* \Desc    : 场景节点
	*
	* \bug     : 
	*
	* \Copyright (c) 2012 lp All rights reserved.
	*/
	class Og2d_Export_API SceneNode : public Node
	{
	public:
		/** 构造函数
		 *
		 * \param szName 场景节点名称
		 * \return 
		 */
		SceneNode(const String& szName, const Rect& rcBound);

		/** 析构函数
		 *
		 * \return 
		 */
		virtual ~SceneNode();

		/** 绑定渲染目标到节点
		 *
		 * \param pRenderTarget 
		 * \return 
		 */
		virtual	bool			attachRenderTarget(RenderTarget* pRenderTarget);

		/**
		 *
		 * \param name 
		 * \return 
		 */
		virtual RenderTarget*	getRenderTarget(const String& name);

		/** 取消绑定的渲染目标
		 *
		 * \param pRenderTarget 
		 */
		virtual	void			detachRenderTarget(RenderTarget* pRenderTarget);

		/** 更新场景节点
		 *
		 * \param fElapsed 
		 */
		virtual	void			update(float fElapsed);
	protected:
		String					m_szName;
		MapRenderTarget			m_vRenderTarget;
		Size					m_cSize;
	};
}

#endif