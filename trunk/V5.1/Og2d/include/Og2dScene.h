#ifndef _____Og2dScene_H
#define _____Og2dScene_H

#include "Og2dSceneNode.h"
#include "Og2dSceneNodeFactoryManager.h"

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
		Scene(const String& szName, const Rect& rcBound);

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

		/**
		 *
		 * \return 
		 */
		virtual void		setActive(bool bActive);


		/**
		 *
		 * \return 
		 */
		virtual bool		getActive() const;
		
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
		virtual	SceneNode*	createSceneNode(const String& szNodeFactoryName, const String& szName, const Rect& rcBound);

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
		String				m_szName;
		MapSceneNodeTab		m_MapSceneNodeTab;
		Rect				m_rcBound;
		bool				m_bActive;
		
	};
}

#endif