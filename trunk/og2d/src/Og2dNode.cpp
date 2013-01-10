#include "Og2dNode.h"

namespace Og2d
{
	/**
	 *
	 * \return 
	 */
	Node::Node() : m_pParent(NULL)
	{

	}

	/**
	 *
	 * \param szName 
	 * \param rcBoundingBox 
	 * \return 
	 */
	Node::Node(const String& szName, const Rect& rcBoundingBox, Node* pParent)
		: m_szName(szName), m_rcBoundingBox(rcBoundingBox), m_pParent(pParent)
	{

	}

	/**
	 *
	 * \return 
	 */
	Node::~Node()
	{
		removeAllChildeNode();
	}

	/**
	 *
	 * \param rcBoundingBox 
	 */
	void		Node::setBoundingBox(const Rect& rcBoundingBox)
	{
		m_rcBoundingBox = rcBoundingBox;
	}

	/**
	 *
	 * \return 
	 */
	Rect		Node::getBoundingBox() const
	{
		return m_rcBoundingBox;
	}

	/**
	 *
	 * \return 
	 */
	Vector2D	Node::getCenter() const
	{
		return m_rcBoundingBox.getCenter();
	}
	
	/**
	 *
	 * \param szName 
	 */
	void		Node::setName(const String& szName)
	{
		m_szName = szName;
	}

	/**
	 *
	 * \return 
	 */
	String		Node::getName() const
	{
		return m_szName;
	}

	/**
	 *
	 * \param vScale 
	 */
	void		Node::setScale(const Vector2D& vScale)
	{
		m_vScale = vScale;
	}

	/**
	 *
	 * \return 
	 */
	Vector2D	Node::getScale() const
	{
		return m_vScale;
	}

	/**
	 *
	 * \param vPos 
	 */
	void		Node::setPosition(const Vector2D& vPos)
	{
		m_rcBoundingBox += vPos;
	}

	/**
	 *
	 * \return 
	 */
	Vector2D	Node::getPosition() const
	{
		return m_rcBoundingBox.getUpper() + m_vRelativelyPosition;
	}

	/**
	 *
	 * \param vPos 
	 */
	void		Node::setRelativelyPosition(const Vector2D& vPos)
	{
		m_vRelativelyPosition = vPos;	
	}

	/**
	 *
	 * \return 
	 */
	Vector2D	Node::getRelativelyPosition() const
	{
		return m_vRelativelyPosition;
	}

	/**
	 *
	 * \param pParent 
	 */
	void		Node::setParent(Node* pParent)
	{
		m_pParent = pParent;
	}

	/**
	 *
	 * \return 
	 */
	Node*		Node::getParent() const
	{
		return m_pParent;
	}

	/**
	 *
	 * \param szName 
	 * \param rcBoundingBox 
	 * \return 
	 */
	Node*		Node::createChildNode(const String& szName, const Rect& rcBoundingBox)
	{
		MapChildNode::iterator it = m_MapChildren.find(szName);
		if ( it == m_MapChildren.end() )
		{
			Node* pNode = new Node(szName, rcBoundingBox, this);
			if (pNode)
			{
				m_MapChildren.insert(MapChildNode::value_type(szName, pNode));
				return pNode;
			}
		}

		return NULL;
	}

	/**
	 *
	 * \param pNode 
	 */
	void		Node::addChildNode(Node* pNode)
	{
		MapChildNode::iterator it = m_MapChildren.find(pNode->getName());
		if ( it == m_MapChildren.end() )
		{
			m_MapChildren.insert(MapChildNode::value_type(pNode->getName(),
				pNode));
		}
	}

	/**
	 *
	 * \param szName 
	 * \return 
	 */
	Node*		Node::getChildNode(const String& szName)
	{
		MapChildNode::iterator it = m_MapChildren.find(szName);
		if ( it != m_MapChildren.end() )
			return it->second;

		return NULL;
	}

	/**
	 *
	 * \param pNode 
	 */
	void		Node::removeChildNode(Node* pNode)
	{
		MapChildNode::iterator it = m_MapChildren.find(pNode->getName());
		if ( it != m_MapChildren.end() )
		{
			SAFE_DELETE(it->second); m_MapChildren.erase(it);
		}
	}

	/**
	 *
	 * \param szName 
	 */
	void		Node::removeChildNode(const String& szName)
	{
		MapChildNode::iterator it = m_MapChildren.find(szName);
		if ( it != m_MapChildren.end() )
		{
			SAFE_DELETE(it->second); m_MapChildren.erase(it);
		}
	}
	
	/**
	 *
	 */
	void		Node::removeAllChildeNode()
	{
		MapChildNode::iterator it = m_MapChildren.begin();
		while( it != m_MapChildren.end() )
		{
			SAFE_DELETE(it->second); it = m_MapChildren.erase(it);
		}
	}

	/**
	 *
	 * \param fElapsed 
	 */
	void		Node::update(float fElapsed)
	{
		for (MapChildNode::iterator it=m_MapChildren.begin();
			it!=m_MapChildren.end(); it++)
		{
			it->second->update(fElapsed);
		}
	}
}