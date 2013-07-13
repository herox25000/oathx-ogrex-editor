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
	* \Desc    : ҳ����������
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

		/** ���������ڵ�
		 *
		 * \param szName		�����ڵ�����
		 * \param rcBoundingBox �ڵ��Χ��
		 * \return 
		 */
		virtual	SceneNode*	createSceneNode(const String& szName, const Vector2D& vPos);

		/** ��ȡ�����ڵ�
		 *
		 * \param szName 
		 * \return 
		 */
		virtual	SceneNode*	getSceneNode(const String& szName);

		/** ���ٳ����ڵ�
		 *
		 * \param szName 
		 */
		virtual	void		destroySceneNode(const String& szName);

		/** ���ٳ����ڵ�
		 *
		 * \param pSceneNode 
		 */
		virtual	void		destroySceneNode(SceneNode* pSceneNode);
		
		/** �������еĳ����ڵ�
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