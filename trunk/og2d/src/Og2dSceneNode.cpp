#include "Og2dSceneNode.h"

namespace Og2d
{
	/**
	 *
	 * \param szName 
	 * \param rcBoundingBox 
	 * \return 
	 */
	SceneNode::SceneNode(const String& szName, const Vector2D& vPos)
		: Node(szName, vPos)
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
			// 重设渲染目标位置
			Vector2D vPos = m_vPos + pRenderTarget->getPosition();
			pRenderTarget->setPosition(
				vPos);

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