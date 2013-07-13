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
	* \Desc    : 场景借口
	*
	* \bug     : 
	*
	* \Copyright (c) 2012 lp All rights reserved.
	*/
	class Og2d_Export_API Scene
	{
	public:
		/** 构造函数
		 *
		 * \param szName	场景名
		 * \param vOrigin	场景原点
		 * \param cSize		场景尺寸
		 * \param rcView	场景视口
		 * \return 
		 */
		Scene(const String& szName, const Vector2D& vPos, const Size& cSize);

		/** 析构函数
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
		
		/** 获取场景尺寸
		 *
		 * \return 
		 */
		virtual Size		getSize() const;

		/** 设置场景尺寸
		 *
		 * \param cSize 
		 */
		virtual	void		setSize(const Size& cSize);

		/** 获取场景包围盒
		 *
		 * \return 
		 */
		virtual	Rect		getArea() const;

		/** 创建场景节点
		 *
		 * \param szName		场景节点名称
		 * \param rcBoundingBox 节点包围盒
		 * \return 
		 */
		virtual	SceneNode*	createSceneNode(const String& szName, const Vector2D& vPos) = 0;

		/** 获取场景节点
		 *
		 * \param szName 
		 * \return 
		 */
		virtual	SceneNode*	getSceneNode(const String& szName) = 0;

		/** 销毁场景节点
		 *
		 * \param szName 
		 */
		virtual	void		destroySceneNode(const String& szName) = 0;

		/** 销毁场景节点
		 *
		 * \param pSceneNode 
		 */
		virtual	void		destroySceneNode(SceneNode* pSceneNode) = 0;
		
		/** 销毁所有的场景节点
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