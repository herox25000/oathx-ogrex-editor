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
		float CompositeMapDistance, const Vector3& vLightMapDirection, const ColourValue& clrCompositeMapDiffuse) : Server(typeName), m_pGlobalOption(NULL)
	{
		addProperty(PY_NAME_MAXPIXELERROR, Any(fMaxPixelError),
			PY_NAME_MAXPIXELERROR_DESC, PROPERTY_REAL);
		addProperty(PY_NAME_COMPOSITEMAPDISCANE, Any(CompositeMapDistance),
			PY_NAME_COMPOSITEMAPDISCANE_DESC, PROPERTY_REAL);
		addProperty(PY_NAME_LIGHTMAPDIRECTION, Any(vLightMapDirection),
			PY_NAME_LIGHTMAPDIRECTION_DESC, PROPERTY_VECTOR3);
		addProperty(PY_NAME_COMPOSITEMAPDIFFUSE, Any(clrCompositeMapDiffuse),
			PY_NAME_COMPOSITEMAPDIFFUSE_DESC, PROPERTY_COLOUR);

		// 构造
		m_pGlobalOption = new TerrainGlobalOptions();
		// 配置
		configureTerrainDefault();
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

	/**
	 *
	 */
	void	TerrainGlobalOptionServer::configureTerrainDefault()
	{
		float fValue;
		getPropertyValue(PY_NAME_MAXPIXELERROR, fValue);
		m_pGlobalOption->setMaxPixelError(fValue);

		getPropertyValue(PY_NAME_COMPOSITEMAPDISCANE, fValue);
		m_pGlobalOption->setCompositeMapDistance(fValue);

		Vector3 vLightMapDirection;
		getPropertyValue(PY_NAME_LIGHTMAPDIRECTION, vLightMapDirection);
		m_pGlobalOption->setLightMapDirection(vLightMapDirection);

		ColourValue clrCompositeMapDiffuse;
		getPropertyValue(PY_NAME_COMPOSITEMAPDIFFUSE, clrCompositeMapDiffuse);
		m_pGlobalOption->setCompositeMapDiffuse(clrCompositeMapDiffuse);
	}

	/**
	 *
	 */
	bool	TerrainGlobalOptionServer::load()
	{
		return 0;
	}

	/**
	 *
	 */
	void	TerrainGlobalOptionServer::unload()
	{

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
		// 转换参数
		const STerrainGlobalOptionServerAdp& adp = static_cast<const STerrainGlobalOptionServerAdp&>(ssadp);
		
		// 创建地形配置服务
		return new TerrainGlobalOptionServer(adp.typeName, adp.fMaxPixelError,
			adp.fCompositeMapDistance, adp.vLightMapDirection, adp.clrCompositeMapDiffuse);
	}
}