#include "Og2dSceneNode.h"

namespace Og2d
{
	/**
	 *
	 * \param szName 
	 * \return 
	 */
	SceneNode::SceneNode()
	{

	}

	/**
	 *
	 * \param szName 
	 * \param rcBoundingBox 
	 * \return 
	 */
	SceneNode::SceneNode(const String& szName, const Rect& rcBoundingBox, Node* pParent)
		: Node(szName, rcBoundingBox, pParent)
	{

	}

	/**
	 *
	 * \return 
	 */
	SceneNode::~SceneNode()
	{

	}

	/**
	 *
	 * \param pRenderTarget 
	 * \return 
	 */
	bool		SceneNode::attachRenderTarget(RenderTarget* pRenderTarget)
	{
		MapRenderTarget::iterator it = m_vRenderTarget.find(pRenderTarget->getName());
		if ( it == m_vRenderTarget.end() )
		{
			// �������λ��
			m_rcBoundingBox += pRenderTarget->getPosition();
			
			// ������ȾĿ��λ��
			pRenderTarget->setPosition(
				m_rcBoundingBox.getUpper()
				);

			m_vRenderTarget.insert(MapRenderTarget::value_type(pRenderTarget->getName(),
				pRenderTarget));

			return true;
		}

		return 0;
	}

	/**
	 *
	 * \param pRenderTarget 
	 */
	void		SceneNode::detachRenderTarget(RenderTarget* pRenderTarget)
	{
		MapRenderTarget::iterator it = m_vRenderTarget.find(pRenderTarget->getName());
		if ( it != m_vRenderTarget.end() )
		{
			m_vRenderTarget.erase(it);
		}	
	}

	/**
	 *
	 * \param fElapsed 
	 */
	void		SceneNode::update(float fElapsed)
	{
		// draw all render target
		for (MapRenderTarget::iterator it=m_vRenderTarget.begin();
			it!=m_vRenderTarget.end(); it++)
		{
			it->second->draw(fElapsed);
		}
		
		// update all child node
		Node::update(fElapsed);
	}
}