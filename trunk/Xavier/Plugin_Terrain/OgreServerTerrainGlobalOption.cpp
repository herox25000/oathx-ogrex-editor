#include "OgreTerrainPluginPrerequisites.h"
#include "OgreServerTerrainGlobalOption.h"

namespace Ogre
{
	/**
	 *
	 * \param typeName 
	 * \param fMaxPixelError 
	 * \param CompositeMapDistance 
	 * \param vLightMapDirection 
	 * \param clrCompositeMapDiffuse 
	 * \return 
	 */
	TerrainGlobalOptionServer::TerrainGlobalOptionServer(const String& typeName, float fMaxPixelError,
		float CompositeMapDistance, const Vector3& vLightMapDirection, const ColourValue& clrCompositeMapDiffuse) : Server(typeName), m_pGlobalOption(0)
	{
		addProperty(PV_MAXPIXELERROR,		Any(fMaxPixelError),		PVT_REAL);
		addProperty(PV_COMPOSITEMAPDISCANE, Any(CompositeMapDistance),	PVT_REAL);
		addProperty(PV_LIGHTMAPDIRECTION,	Any(vLightMapDirection),	PVT_VECTOR3);
		addProperty(PV_COMPOSITEMAPDIFFUSE, Any(clrCompositeMapDiffuse),PVT_COLOUR);

		// ����
		m_pGlobalOption = new TerrainGlobalOptions();
		if (m_pGlobalOption)
		{
			m_pGlobalOption->setCompositeMapDiffuse(clrCompositeMapDiffuse);
			m_pGlobalOption->setMaxPixelError(fMaxPixelError);
			m_pGlobalOption->setCompositeMapDistance(CompositeMapDistance);
			m_pGlobalOption->setLightMapDirection(vLightMapDirection);
		}
	}

	/**
	 *
	 * \return 
	 */
	TerrainGlobalOptionServer::~TerrainGlobalOptionServer()
	{
		if (m_pGlobalOption != NULL)
			delete m_pGlobalOption;
	}

	//////////////////////////////////////////////////////////////////////////
	const String TerrainGlobalOptionServerFactory::FactoryTypeName	= "Terrain/TerrainGlobalOptionServerFactory";
	//////////////////////////////////////////////////////////////////////////

	/**
	 *
	 * \return 
	 */
	TerrainGlobalOptionServerFactory::TerrainGlobalOptionServerFactory()
	{

	}

	/**
	 *
	 * \return 
	 */
	TerrainGlobalOptionServerFactory::~TerrainGlobalOptionServerFactory()
	{

	}

	/**
	 *
	 * \return 
	 */
	String	TerrainGlobalOptionServerFactory::getTypeName() const
	{
		return TerrainGlobalOptionServerFactory::FactoryTypeName;
	}

	/**
	 *
	 * \param ssadp 
	 * \return 
	 */
	Server*	TerrainGlobalOptionServerFactory::createServer(const SSAdp& ssadp)
	{
		// ת������
		const STerrainGlobalOptionServerAdp& adp = static_cast<const STerrainGlobalOptionServerAdp&>(ssadp);
		
		// �����������÷���
		return new TerrainGlobalOptionServer(adp.typeName, adp.fMaxPixelError,
			adp.fCompositeMapDistance, adp.vLightMapDirection, adp.clrCompositeMapDiffuse);
	}
}