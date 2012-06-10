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
	XavierTerrainEditor::XavierTerrainEditor(const String& typeName, const String& propertySetFile) 
		: XavierEditor(typeName, propertySetFile), m_pTerrain(0)
	{

	}

	/**
	 *
	 * \return 
	 */
	XavierTerrainEditor::~XavierTerrainEditor()
	{

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
}