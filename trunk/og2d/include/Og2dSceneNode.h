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
	* \Desc    : �����ڵ�
	*
	* \bug     : 
	*
	* \Copyright (c) 2012 lp All rights reserved.
	*/
	class Og2d_Export_API SceneNode : public Node
	{
	public:
		/**
		 *
		 * \return 
		 */
		SceneNode();

		/** ���캯��
		 *
		 * \param szName �����ڵ�����
		 * \return 
		 */
		SceneNode(const String& szName, const Rect& rcBoundingBox, Node* pParent);

		/** ��������
		 *
		 * \return 
		 */
		virtual ~SceneNode();

		/** ����ȾĿ�굽�ڵ�
		 *
		 * \param pRenderTarget 
		 * \return 
		 */
		virtual	bool		attachRenderTarget(RenderTarget* pRenderTarget);

		/** ȡ���󶨵���ȾĿ��
		 *
		 * \param pRenderTarget 
		 */
		virtual	void		detachRenderTarget(RenderTarget* pRenderTarget);

		/** ���³����ڵ�
		 *
		 * \param fElapsed 
		 */
		virtual	void		update(float fElapsed);
	protected:
		String				m_szName;
		MapRenderTarget		m_vRenderTarget;

	};
}

#endif