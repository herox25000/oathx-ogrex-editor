#ifndef _____Og2dWorld_H
#define _____Og2dWorld_H

#include "Og2dSingleton.h"
#include "Og2dScene.h"

namespace Og2d
{
	enum WorldMask{
		SWF_DEFAULT,
	};
	
	// ����ӳ���
	typedef HashMap<String, Scene*>		SceneMapTab;

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
	class Og2d_Export_API World : public Singleton<World>
	{
	public:
		/** ʵ�ֻ�ȡ��������
		 *
		 * \return 
		 */
		static	World&				getSingleton();

		/** ʹ�û�ȡ����ָ��
		 *
		 * \return 
		 */
		static	World*				getSingletonPtr();
	public:
		/**
		 *
		 * \param vOrigin 
		 * \param cSize 
		 * \return 
		 */
		World(const String& szName);

		/**
		 *
		 * \return 
		 */
		~World();

		/**
		 *
		 * \param szName 
		 */
		virtual	void			setName(const String& szName);

		/**
		 *
		 * \return 
		 */
		virtual	String			getName() const;


		/** ��������
		 *
		 * \param szCreateFactoryName 
		 * \param szName 
		 * \return 
		 */
		virtual	Scene*			createScene(const String& szName, const Rect& rcBound, int nFactoryType=SWF_DEFAULT);
		
		/** ��ȡ����
		 *
		 * \param szName 
		 * \return 
		 */
		virtual	Scene*			getScene(const String& szName);
		
		/** ����ָ������
		 *
		 * \param pScene 
		 */
		virtual	void			destroyScene(Scene* pScene);

		/** ����ָ������
		 *
		 * \param szName 
		 */
		virtual	void			destroyScene(const String& szName);

		/** �������г�������
		 *
		 */
		virtual	void			destroyAllScene();

		/** �����Ը��£�ֻ������Ҫ���µĳ�������
		 *
		 * \param fElapsed 
		 */
		virtual	void			update(float fElapsed);
		
	protected:
		// ������
		String					m_szName;
		// ����ӳ���
		SceneMapTab				m_MapSceneTab;
	};
}

#endif