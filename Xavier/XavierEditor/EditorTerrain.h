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
	* \ingroup : XavierSystem
	*
	* \os&IDE  : Microsoft Windows XP (SP3)  &  Microsoft Visual C++ .NET 2008
	*
	* \VERSION : 1.0
	*
	* \date    : 2013-01-23
	*
	* \Author  : lp
	*
	* \Desc    :
	*
	* \bug     : 
	*
	* \Copyright (c) 2012 lp All rights reserved.
	*/
	class MeshBrush
	{
	public:
		/**
		 *
		 * \param pSceneManager 
		 * \param pTerrainGroup 
		 * \param fBrushSize 
		 * \param materialName 
		 * \return 
		 */
		MeshBrush(SceneManager* pSceneManager, TerrainGroup* pTerrainGroup, float fBrushSize, const String& materialName);

		/**
		 *
		 * \return 
		 */
		virtual ~MeshBrush();
		
		/**
		 *
		 * \param fRaidus 
		 */
		virtual	void				setBrushSize(float fBrushSize);

		/**
		 *
		 * \return 
		 */
		virtual	float				getBrushSize() const;

		/**
		 *
		 * \param vSize 
		 */
		virtual	void				setPosition(const Vector3& vPos);
		
		/**
		 *
		 * \param x 
		 * \param z 
		 * \return 
		 */
		virtual	float				getTerrainHeight(const Vector3& vPos);
	protected:
		/**
		 *
		 * \param fBrushSize 
		 * \param materialName 
		 */
		virtual	void				createDecalMesh(const String& materialName);
	protected:
		TerrainGroup*				m_pTerrainGroup;
		SceneManager*				m_pSceneManager;
		ManualObject*				m_pDecalMesh;
		float						m_fBrushSize;
	};

	// 地形编辑模式
	enum{
		ETM_NONE,   
		ETM_DEFORM,     
		ETM_SPLAT,      
		ETM_PAINT,      
		ETM_STAMP,     
		ETM_SMOOTH,  
		ETM_SPLATGRASS
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
	
	public:
		/**
		 *
		 * \param vPos 
		 * \return 
		 */
		virtual	bool			OnMouseMove(const Vector2& vPos);

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
		
		/**
		 *
		 * \return 
		 */
		virtual	bool			configureBrush(SceneManager* pSceneManager);
	protected:
		EditorViewport*			m_pViewporPlugin;
		TerrainGroup*			m_pTerrainGroup;
		TerrainGlobalOptions*	m_pGlobalOptions;

		MeshBrush*				m_pBrush;
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