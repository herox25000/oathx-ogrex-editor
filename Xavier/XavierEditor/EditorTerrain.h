#ifndef _____EditorTerrain_H
#define _____EditorTerrain_H

#include "OgreTerrain.h"
#include "OgreTerrainGroup.h"
#include "OgreTerrainQuadTreeNode.h"
#include "OgreTerrainMaterialGeneratorA.h"
#include "OgreTerrainPaging.h"

namespace Ogre
{
	/**
	* \ingroup : XavierEditor
	*
	* \os&IDE  : Microsoft Windows XP (SP3)  &  Microsoft Visual C++ .NET 2008
	*
	* \VERSION : 1.0
	*
	* \date    : 2013-01-25
	*
	* \Author  : lp
	*
	* \Desc    :
	*
	* \bug     : 
	*
	* \Copyright (c) 2012 lp All rights reserved.
	*/
	class EditorTerrain : public EditorPlugin
	{
	public:
		/**
		 *
		 * \param pluginName 
		 * \param fMaxPixelError 
		 * \param nCompositeMapSize 
		 * \param fCompositeMapDistance 
		 * \param nLightMapSize 
		 * \param nLayerBlendMapSize 
		 * \param fSkirtSize 
		 * \param clrCompositeMapDiffuse 
		 * \param nTerrainSize 
		 * \param fWorldSize 
		 * \return 
		 */
		EditorTerrain(const String& pluginName, float fMaxPixelError, uint16 nCompositeMapSize, float fCompositeMapDistance,
			uint16 nLightMapSize, uint16 nLayerBlendMapSize, float fSkirtSize,
			const ColourValue& clrCompositeMapDiffuse, uint16 nTerrainSize, float fWorldSize);

		/**
		 *
		 * \return 
		 */
		virtual ~EditorTerrain();

	public:
		/**
		 *
		 * \return 
		 */
		virtual	TerrainGroup*	getTerrainGroup() const;

	protected:
		/**
		 *
		 * \param fMaxPixelError 
		 * \param nCompositeMapSize 
		 * \param fCompositeMapDistance 
		 * \param nLightMapSize 
		 * \param nLayerBlendMapSize 
		 * \param fSkirtSize 
		 * \param clrCompositeMapDiffuse 
		 * \param nTerrainSize 
		 * \param fWorldSize 
		 * \return 
		 */
		virtual	bool			configure(float fMaxPixelError, uint16 nCompositeMapSize, float fCompositeMapDistance, uint16 nLightMapSize,
			uint16 nLayerBlendMapSize, float fSkirtSize, const ColourValue& clrCompositeMapDiffuse, uint16 nTerrainSize, float fWorldSize);

	protected:
		TerrainGroup*			m_pTerrainGroup;
		TerrainGlobalOptions*	m_pGlobalOptions;
	};

	// 地形创建适配参数
	struct SEditorPluginTerrainAdp : public SEditorPluginAdp
	{
		float					fMaxPixelError; 
		uint16					nCompositeMapSize; 
		float					fCompositeMapDistance;
		uint16					nLightMapSize;
		uint16					nLayerBlendMapSize; 
		float					fSkirtSize;
		ColourValue				clrCompositeMapDiffuse; 
		uint16					nTerrainSize; 
		float					fWorldSize;
	};

	/**
	* \ingroup : XavierEditor
	*
	* \os&IDE  : Microsoft Windows XP (SP3)  &  Microsoft Visual C++ .NET 2008
	*
	* \VERSION : 1.0
	*
	* \date    : 2013-01-25
	*
	* \Author  : lp
	*
	* \Desc    :
	*
	* \bug     : 
	*
	* \Copyright (c) 2012 lp All rights reserved.
	*/
	class EditorTerrrainFactory : public EditorPluginFactory
	{
	public:
		/**
		 *
		 * \param factoryName 
		 * \return 
		 */
		EditorTerrrainFactory(const String& factoryName);

		/**
		 *
		 * \return 
		 */
		virtual ~EditorTerrrainFactory();

		/**
		 *
		 * \param ssadp 
		 * \param pParent 
		 * \return 
		 */
		virtual	EditorPlugin*			createPlugin(const SEditorPluginAdp& ssadp, EditorPlugin* pParent);
	};
}

#endif