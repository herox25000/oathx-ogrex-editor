#ifndef _____Og2dWorld_H
#define _____Og2dWorld_H

#include "Og2dSingleton.h"
#include "Og2dScene.h"

namespace Og2d
{
	enum WorldMask{
		SWF_DEFAULT,
	};
	
	// 场景映射表
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
	* \Desc    : 世界对象
	*
	* \bug     : 
	*
	* \Copyright (c) 2012 lp All rights reserved.
	*/
	class Og2d_Export_API World : public Singleton<World>
	{
	public:
		/** 实现获取单件引用
		 *
		 * \return 
		 */
		static	World&				getSingleton();

		/** 使用获取单件指针
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


		/** 创建创建
		 *
		 * \param szCreateFactoryName 
		 * \param szName 
		 * \return 
		 */
		virtual	Scene*			createScene(const String& szName, const Rect& rcBound, int nFactoryType=SWF_DEFAULT);
		
		/** 获取场景
		 *
		 * \param szName 
		 * \return 
		 */
		virtual	Scene*			getScene(const String& szName);
		
		/** 销毁指定场景
		 *
		 * \param pScene 
		 */
		virtual	void			destroyScene(Scene* pScene);

		/** 销毁指定场景
		 *
		 * \param szName 
		 */
		virtual	void			destroyScene(const String& szName);

		/** 销毁所有场景对象
		 *
		 */
		virtual	void			destroyAllScene();

		/** 周期性更新，只更新需要更新的场景对象
		 *
		 * \param fElapsed 
		 */
		virtual	void			update(float fElapsed);
		
	protected:
		// 世界名
		String					m_szName;
		// 场景映射表
		SceneMapTab				m_MapSceneTab;
	};
}

#endif