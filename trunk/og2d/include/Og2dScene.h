#ifndef _____Og2dScene_H
#define _____Og2dScene_H

#include "Og2dSceneNode.h"
#include "Og2dViewport.h"

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
		Scene(const String& szName, const Vector2D& vOrigin, const Size& cSize, 
			const Rect& rcView);

		/** ��������
		 *
		 * \return 
		 */
		virtual ~Scene();
		
		/** ���ó�������
		 *
		 * \param szName 
		 */
		virtual	void		setName(const String& szName);

		/** ��ȡ��������
		 *
		 * \return 
		 */
		virtual	String		getName() const;
		
		/** ��ȡ����ԭ��
		 *
		 * \return 
		 */
		virtual	Vector2D	getOrigin() const;

		/** ���ó���ԭ��
		 *
		 * \param vOrigin 
		 */
		virtual	void		setOrigin(const Vector2D& vOrigin);

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

		/**
		 *
		 * \return 
		 */
		virtual	Vector2D	getCenter() const;

		/** ��ȡ������Χ��
		 *
		 * \return 
		 */
		virtual	Rect		getBoundingBox() const;

		/** ���������ڵ�
		 *
		 * \param szName		�����ڵ�����
		 * \param rcBoundingBox �ڵ��Χ��
		 * \return 
		 */
		virtual	SceneNode*	createSceneNode(const String& szName, const Rect& rcBoundingBox);

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

		/** �����Գ�������
		 *
		 * \param fElapsed 
		 */
		virtual	void		update(float fElapsed);
		
	protected:
		String				m_szName;
		// �����ڵ�ӳ���
		MapSceneNodeTab		m_MapSceneNodeTab;
		// ������Χ��
		Rect				m_rcBouingBox;
		// ����ԭ��λ��
		Vector2D			m_vOrigin;
	};
}

#endif