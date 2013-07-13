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
		 * \param szName		节点名
		 * \param rcBoundingBox 
		 * \return 
		 */
		Node(const String& szName, const Rect& rcBound);
	
		/**
		 *
		 * \return 
		 */
		virtual ~Node();

		/**
		 *
		 * \param szName 
		 */
		virtual	void		setName(const String& szName);

		/**
		 *
		 * \return 
		 */
		virtual String		getName() const;

		/**
		 *
		 * \param vPos 
		 */
		virtual	void		setPosition(const Vector2D& vPos);

		/**
		 *
		 * \return 
		 */
		virtual Vector2D	getPosition() const;

		/**
		 *
		 * \return 
		 */
		virtual Rect		getBoundingBox() const;

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
		 * \param fElapsed 
		 */
		virtual	void		update(float fElapsed);

		/**
		 *
		 * \param pNode 
		 * \return 
		 */
		virtual	bool		addChildNode(Node* pNode);

		/**
		 *
		 * \param szName 
		 * \return 
		 */
		virtual Node*		getChildNode(const String& szName);

		/**
		 *
		 * \param pNode 
		 */
		virtual	void		removeChildNode(Node* pNode, bool bDestroy=true);

		/**
		 *
		 * \param name 
		 */
		virtual	void		removeChildNode(const String& name, bool bDestroy=true);

		/**
		 *
		 */
		virtual	void		removeAllChildeNode();
	protected:
		String				m_szName;
		MapChildNode		m_MapChildren;
		Rect				m_rcBound;
		Node*				m_pParent;
	};
}

#endif