#include "Og2dNode.h"

namespace Og2d
{
	/**
	 *
	 * \param szName 
	 * \param vPos 
	 * \return 
	 */
	Node::Node(const String& szName, const Vector2D& vPos)
		: m_szName(szName), m_vPos(vPos), m_pParent(NULL)
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
	 * \param vPos 
	 */
	void		Node::setPosition(const Vector2D& vPos)
	{
		m_vPos = vPos;
	}

	/**
	 *
	 * \return 
	 */
	Vector2D	Node::getPosition() const
	{
		return m_vPos;
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
	 * \param pNode 
	 */
	bool		Node::addChildNode(Node* pNode)
	{
		MapChildNode::iterator it = m_MapChildren.find(pNode->getName());
		if ( it == m_MapChildren.end() )
		{
			// if the node no parent
			Node* pParent = pNode->getParent();
			if (pParent != NULL)
			{
				// remove this node, but no destroy
				pParent->removeChildNode(pNode, 0);
			}			
		
			// set parent
			pNode->setParent(this);

			// update this node position
			Vector2D vPos = m_vPos + pNode->getPosition(); 
			pNode->setPosition(vPos);

			m_MapChildren.insert(MapChildNode::value_type(pNode->getName(),
				pNode));

			return true;
		}

		return 0;
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
	void		Node::removeChildNode(Node* pNode, 
		bool bDestroy/* =true */)
	{
		removeChildNode(pNode->getName(), bDestroy);
	}

	/**
	 *
	 * \param szName 
	 */
	void		Node::removeChildNode(const String& name, 
		bool bDestroy/* =true */)
	{
		MapChildNode::iterator it = m_MapChildren.find(name);
		if ( it != m_MapChildren.end() )
		{
			if (bDestroy)
			{
				SAFE_DELETE(it->second);
			}

			m_MapChildren.erase(it);
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