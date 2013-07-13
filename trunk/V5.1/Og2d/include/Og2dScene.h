#ifndef _____Og2dScene_H
#define _____Og2dScene_H

#include "Og2dSceneNode.h"

namespace Og2d
{
	typedef map<String, SceneNode*>::type MapSceneNodeTab;
	
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
	* \Desc    : �������
	*
	* \bug     : 
	*
	* \Copyright (c) 2012 lp All rights reserved.
	*/
	class Og2d_Export_API Scene
	{
	public:
		/** ���캯��
		 *
		 * \param szName	������
		 * \param vOrigin	����ԭ��
		 * \param cSize		�����ߴ�
		 * \param rcView	�����ӿ�
		 * \return 
		 */
		Scene(const String& szName, const Vector2D& vPos, const Size& cSize);

		/** ��������
		 *
		 * \return 
		 */
		virtual ~Scene();

		/**
		 *
		 * \param name 
		 */
		virtual	void		setName(const String& name);

		/**
		 *
		 * \return 
		 */
		virtual String		getName() const;
		
		/** ��ȡ�����ߴ�
		 *
		 * \return 
		 */
		virtual Size		getSize() const;

		/** ���ó����ߴ�
		 *
		 * \param cSize 
		 */
		virtual	void		setSize(const Size& cSize);

		/** ��ȡ������Χ��
		 *
		 * \return 
		 */
		virtual	Rect		getArea() const;

		/** ���������ڵ�
		 *
		 * \param szName		�����ڵ�����
		 * \param rcBoundingBox �ڵ��Χ��
		 * \return 
		 */
		virtual	SceneNode*	createSceneNode(const String& szName, const Vector2D& vPos) = 0;

		/** ��ȡ�����ڵ�
		 *
		 * \param szName 
		 * \return 
		 */
		virtual	SceneNode*	getSceneNode(const String& szName) = 0;

		/** ���ٳ����ڵ�
		 *
		 * \param szName 
		 */
		virtual	void		destroySceneNode(const String& szName) = 0;

		/** ���ٳ����ڵ�
		 *
		 * \param pSceneNode 
		 */
		virtual	void		destroySceneNode(SceneNode* pSceneNode) = 0;
		
		/** �������еĳ����ڵ�
		 *
		 */
		virtual	void		destroyAllSceneNode() = 0;

		/**
		 *
		 * \param fElapsed 
		 */
		virtual	void		update(float fElapsed) = 0;
	protected:
		Size				m_cSize;
		Vector2D			m_vPos;
		String				m_szName;
	};
}

#endif