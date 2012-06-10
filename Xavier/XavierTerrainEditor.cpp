#include "stdafx.h"
#include "XavierAppEditor.h"
#include "XavierTerrainEditor.h"


namespace Ogre
{
	/**
	 *
	 * \param typeName 
	 * \return 
	 */
	XavierTerrainEditor::XavierTerrainEditor(const String& typeName, const STerrainGroupServerAdp& adp, const String& propertySetFile) 
		: XavierEditor(typeName, propertySetFile), m_pTerrain(0)
	{
		ServerFactory* pTerrainGroupFactory = System::getSingleton().getServerFactory(
			"Terrain/TerrainGroupServerFactory"
			);
		if (pTerrainGroupFactory)
		{
			m_pServer = pTerrainGroupFactory->createServer(adp);
			ASSERT(m_pServer);

			loadProperty();

			System::getSingleton().addServer(m_pServer);
		}
	}

	/**
	 *
	 * \return 
	 */
	XavierTerrainEditor::~XavierTerrainEditor()
	{
		System::getSingleton().delServer(m_pServer);
	}


	/**
	 *
	 * \param nID 
	 * \param texture 
	 * \param normal 
	 * \param fWorldSize 
	 * \return 
	 */
	int			XavierTerrainEditor::addLayer(const String& texture, const String& normal,
		float fWorldSize)
	{
		TerrainGroupServer* pTerrainServer = static_cast<TerrainGroupServer*>(
			System::getSingleton().getServer(SERVER_TERRAIN_GROUP)
			);
		if (pTerrainServer)
		{
			m_pTerrain = pTerrainServer->getTerrainGroup()->getTerrain(0, 0);
			if (m_pTerrain)
			{
				StringVector vTexture;
				vTexture.push_back(texture);
				vTexture.push_back(normal);
				
				int nCount = m_pTerrain->getLayerCount();
				m_pTerrain->addLayer(nCount, fWorldSize, &vTexture);
				return nCount;
			}
		}

		return 5;
	}

	//////////////////////////////////////////////////////////////////////////
	const String	XavierTerrainEditorFactory::FACTORY_NAME	= "Xavier/XavierTerrainEditorFactory";

	/**
	 *
	 * \param typeName 
	 * \return 
	 */
	XavierTerrainEditorFactory::XavierTerrainEditorFactory()
	{
		// 加载地形插件
#ifdef _DEBUG
		System::getSingleton().loadPlugin("Plugin_Terrain_d.dll");
#else
		System::getSingleton().loadPlugin("Plugin_Terrain.dll");
#endif
	}

	/**
	 *
	 * \return 
	 */
	XavierTerrainEditorFactory::~XavierTerrainEditorFactory()
	{
		// 卸载地形插件
#ifdef _DEBUG
		System::getSingleton().unloadPlugin("Plugin_Terrain_d.dll");
#else
		System::getSingleton().unloadPlugin("Plugin_Terrain.dll");
#endif
	}

	/**
	 *
	 * \return 
	 */
	const String&	XavierTerrainEditorFactory::getTypeName() const
	{
		return XavierTerrainEditorFactory::FACTORY_NAME;
	}

	/**
	 *
	 * \param pNode 
	 * \return 
	 */
	XavierEditor*	XavierTerrainEditorFactory::create(const SSAdp& ssadp)
	{
		const STerrainGroupServerAdp& adp = static_cast<const STerrainGroupServerAdp&>(ssadp);
		return new XavierTerrainEditor(ssadp.typeName, adp, 
			m_PropertySetFile);
	}
}