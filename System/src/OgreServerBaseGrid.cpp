#include "OgreSystemPrerequisites.h"
#include "OgreServerBaseGrid.h"
#include "OgreServerWorldSpace.h"
#include "OgreSystem.h"

namespace Ogre
{
	/**
	 *
	 * \param fWidth 
	 * \param fSize 
	 * \param fDepth 
	 * \return 
	 */
	BaseGridServer::BaseGridServer(const String& typeName, WorldSpaceServer* pWorldSpace, Real fWidth, Real fSize, Real fDepth)
		: Server(typeName), m_pWorldSpace(pWorldSpace), m_fDepth(fDepth), m_fSize(fSize), m_fWidth(fWidth), m_pGrid(NULL), m_pLine(NULL), m_bDisplay(true)
	{
		createGird();
	}

	/**
	 *
	 * \param void 
	 * \return 
	 */
	BaseGridServer::~BaseGridServer(void)
	{
		destroy();
	}

	/**
	 *
	 * \param fSize 
	 */
	void	BaseGridServer::setSize(float fSize)
	{
		m_fSize = fSize;
	}

	/**
	 *
	 * \return 
	 */
	float	BaseGridServer::getSize() const
	{
		return m_fSize;
	}

	/**
	 *
	 * \param fDepth 
	 */
	void	BaseGridServer::setDepth(float fDepth)
	{
		m_fDepth = fDepth;
	}

	/**
	 *
	 * \return 
	 */
	float	BaseGridServer::getDepth() const
	{
		return m_fDepth;
	}

	/**
	 *
	 * \param fWidth 
	 */
	void	BaseGridServer::setWidth(float fWidth)
	{
		m_fWidth = fWidth;
	}

	/**
	 *
	 * \return 
	 */
	float	BaseGridServer::getWidth() const
	{
		return m_fWidth;
	}
	
	void	BaseGridServer::invalidate()
	{
		if (m_bDisplay)
		{
			destroy(); createGird();
		}
	}

	/**
	 *
	 */
	void	BaseGridServer::show()
	{
		m_bDisplay = true; createGird();
	}

	/**
	 *
	 * \return 
	 */
	bool	BaseGridServer::isVisible() const
	{
		return m_bDisplay;
	}

	/**
	 *
	 */
	void	BaseGridServer::hide()
	{
		m_bDisplay = false; destroy();
	}
	
	/**
	 *
	 */
	void	BaseGridServer::createGird()
	{
		if (m_pGrid == NULL && m_pLine == NULL)
		{
			m_pGrid = m_pWorldSpace->getSceneManager()->createManualObject("GridEditor/Line3D");
			m_pGrid->begin("Editor/GridLine3D",RenderOperation::OT_LINE_LIST);

			Vector3	vStart(m_fWidth / 2, 0, m_fDepth / 2);
			Real	fStartZ = vStart.z;

			while(fStartZ >= -vStart.z)
			{
				m_pGrid->position(-vStart.x,	0, fStartZ);
				m_pGrid->colour(0,1,0,1);
				m_pGrid->position(vStart.x,		0, fStartZ);

				fStartZ -= m_fSize;
			}

			Real	fStartX = -vStart.x;
			while(fStartX <= vStart.x)
			{
				m_pGrid->position(fStartX,		0, vStart.z);
				m_pGrid->colour(0,1,0,1);
				m_pGrid->position(fStartX,		0, -vStart.z);

				fStartX += m_fSize;
			}

			m_pGrid->end();

			m_pLine = m_pWorldSpace->getSceneManager()->getRootSceneNode()->createChildSceneNode("GridEditor/Line3DNode");
			m_pLine->attachObject(m_pGrid);
		}
	}

	/**
	 *
	 */
	void	BaseGridServer::destroy()
	{
		if (m_pGrid)
		{
			m_pWorldSpace->getSceneManager()->destroyManualObject(m_pGrid);
			m_pGrid = NULL;
		}

		if (m_pLine)
		{
			m_pWorldSpace->getSceneManager()->destroySceneNode(m_pLine->getName());
			m_pLine = NULL;
		}
	}

	/**
	 *
	 * \param args 
	 * \return 
	 */
	bool	BaseGridServer::onPropertyChanaged(const EventArgs& args)
	{
		const PropertyEventArgs& evt = static_cast<const PropertyEventArgs&>(args);
		if (evt.pProperty != NULL)
		{
			String name = evt.pProperty->getName();
			if (name == "display")
			{
				bool bDisplay = any_cast<bool>(evt.pProperty->getValue());
				if (bDisplay)
					createGird();
				else
					destroy();
			}
		}

		return true;
	}

	// define base grid factory name
	const String	BaseGridServerFactory::FactoryTypeName = "System/BaseGridFactory";

	/**
	 *
	 * \return 
	 */
	BaseGridServerFactory::BaseGridServerFactory()
	{
		
	}

	/**
	 *
	 * \return 
	 */
	String		BaseGridServerFactory::getTypeName() const
	{
		return BaseGridServerFactory::FactoryTypeName;
	}

	/**
	 *
	 * \param pm 
	 * \return 
	 */
	Server*		BaseGridServerFactory::createServer(const SSAdp& ssadp)
	{
		const SBaseGridServerAdp& adp = static_cast<const SBaseGridServerAdp&>(ssadp);

		// 获取世界服务
		WorldSpaceServer* pWorldSpace	= static_cast<WorldSpaceServer*>(
			System::getSingleton().getServer(adp.depServerName));

#ifdef _OUTPUT_LOG
		TKLogEvent("create server " + adp.typeName + " dependencie server " + (adp.depServerName.empty() ? "NULL" : adp.depServerName));
#endif
		return new BaseGridServer(adp.typeName, pWorldSpace, 
			adp.fWidth, adp.fSize, adp.fDepth);
	}
}