#ifndef _____Og2dNode_H
#define _____Og2dNode_H

#include "Og2dMath.h"

namespace Og2d
{
	// 子节点映射表
	typedef HashMap<String, Node*>	MapChildNode;

	/**
	* \ingroup : Og2d
	*
	* \os&IDE  : Microsoft Windows XP (SP2)  &  Microsoft Visual C++ .NET 2008
	*
	* \VERSION : 1.0
	*
	* \date    : 2012-08-04
	*
	* \Author  : lp
	*
	* \Desc    : 基本节点
	*
	* \bug     : 
	*
	* \Copyright (c) 2012 lp All rights reserved.
	*/
	class Og2d_Export_API Node
	{
	public:
		/** 构造函数
		 *
		 * \return 
		 */
		Node();

		/** 构造函数
		 *	
		 * \param szName		节点名
		 * \param rcBoundingBox 
		 * \return 
		 */
		Node(const String& szName, const Rect& rcBoundingBox, Node* pParent);
	
		/**
		 *
		 * \return 
		 */
		virtual ~Node();

		/**
		 *
		 * \param rcBoundingBox 
		 */
		virtual	void		setBoundingBox(const Rect& rcBoundingBox);

		/**
		 *
		 * \return 
		 */
		virtual	Rect		getBoundingBox() const;

		/**
		 *
		 * \return 
		 */
		virtual	Vector2D	getCenter() const;

		/**
		 *
		 * \param szName 
		 */
		virtual	void		setName(const String& szName);

		/**
		 *
		 * \return 
		 */
		virtual	String		getName() const;

		/**
		 *
		 * \param vScale 
		 */
		virtual	void		setScale(const Vector2D& vScale);

		/**
		 *
		 * \return 
		 */
		virtual	Vector2D	getScale() const;

		/**
		 *
		 * \param vPos 
		 */
		virtual	void		setPosition(const Vector2D& vPos);

		/**
		 *
		 * \return 
		 */
		virtual	Vector2D	getPosition() const;
		
		/**
		 *
		 * \param vPos 
		 */
		virtual	void		setRelativelyPosition(const Vector2D& vPos);

		/**
		 *
		 * \return 
		 */
		virtual	Vector2D	getRelativelyPosition() const;

		/**
		 *
		 * \param pParent 
		 */
		virtual	void		setParent(Node* pParent);

		/**
		 *
		 * \return 
		 */
		virtual	Node*		getParent() const;

		/**
		 *
		 * \param szName 
		 * \param rcBoundingBox 
		 * \return 
		 */
		virtual	Node*		createChildNode(const String& szName, const Rect& rcBoundingBox);

		/**
		 *
		 * \param pNode 
		 */
		virtual	void		addChildNode(Node* pNode);

		/**
		 *
		 * \param szName 
		 * \return 
		 */
		virtual	Node*		getChildNode(const String& szName);

		/**
		 *
		 * \param pNode 
		 */
		virtual	void		removeChildNode(Node* pNode);

		/**
		 *
		 * \param szName 
		 */
		virtual	void		removeChildNode(const String& szName);
		
		/**
		 *
		 */
		virtual	void		removeAllChildeNode();

		/**
		 *
		 * \param fElapsed 
		 */
		virtual	void		update(float fElapsed);
	protected:
		String				m_szName;
		Rect				m_rcBoundingBox;
		Vector2D			m_vRelativelyPosition;
		MapChildNode		m_MapChildren;
		Node*				m_pParent;
		Vector2D			m_vScale;
	};
}

#endif