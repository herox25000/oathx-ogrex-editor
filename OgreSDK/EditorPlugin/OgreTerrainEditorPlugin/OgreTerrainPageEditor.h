#ifndef _____OgreTerrainPageEditor_H
#define _____OgreTerrainPageEditor_H

#include "OgreEditorPlugin.h"

namespace Ogre
{
#ifndef MAX_LAYERS_ALLOWED
#define MAX_LAYERS_ALLOWED	6
#endif

#ifndef INVALID_LAYER
#define INVALID_LAYER		-1
#endif

	struct STerrainPageLayer
	{
		float	fLayerWorldSize[MAX_LAYERS_ALLOWED];
		String	layerDiffuseTexture[MAX_LAYERS_ALLOWED];
		String	layerNormalTexture[MAX_LAYERS_ALLOWED];
	};

	/**
	* \ingroup : OgreTerrainEditorPlugin
	*
	* \os&IDE  : Microsoft Windows XP (SP2)  &  Microsoft Visual C++ .NET 2008
	*
	* \VERSION : 1.0
	*
	* \date    : 2013-02-16
	*
	* \Author  : lp
	*
	* \Desc    : 
	*
	* \bug     : 
	*
	* \Copyright (c) 2012 lp All rights reserved.
	*/
	class TerrainPageEditor : public EditorPlugin
	{
	public:
		/**
		 *
		 * \param pluginName 
		 * \param nPageX 
		 * \param nPageY 
		 * \param vPos 
		 * \param nMinBatchSize 
		 * \param nMaxBatchSize 
		 * \param nLayerCount 
		 * \param tpl 
		 * \param bAtOnceLoad 
		 * \return 
		 */
		TerrainPageEditor(const String& pluginName, int nPageX, int nPageY, const Vector3& vPos, uint16 nMinBatchSize, uint16 nMaxBatchSize,
			uint16 nLayerCount, const STerrainPageLayer& tpl, bool bAtOnceLoad);

		/**
		 *
		 * \return 
		 */
		virtual ~TerrainPageEditor();

		/**
		 *
		 * \return 
		 */
		virtual	Terrain*		getTerrain() const;

		/**
		 *
		 * \param texture 
		 * \return 
		 */
		virtual	int				getLayerID(const String& texture);

		/**
		 *
		 * \param texture 
		 * \param normal 
		 * \param fWorldSize 
		 * \return 
		 */
		virtual	int				addLayer(const String& texture, const String& normal, 
			float fWorldSize);

		/**
		 *
		 * \param area 
		 * \param pData 
		 */
		virtual void			swapHeight(Rect area, float* pData);

		/**
		 *
		 * \param nValue 
		 */
		virtual	void			alterStart(int nValue, const Rect& area);

		/**
		 *
		 * \param nValue 
		 */
		virtual	void			alterEnd(int nValue);
	protected:
		/**
		 *
		 * \param nPageX 
		 * \param nPageY 
		 * \param vPos 
		 * \param nMinBatchSize 
		 * \param nMaxBatchSize 
		 * \param nLayerCount 
		 * \param tpl 
		 * \param bAtOnceLoad 
		 * \return 
		 */
		virtual	bool			configure(int nPageX, int nPageY, const Vector3& vPos, uint16 nMinBatchSize, uint16 nMaxBatchSize, 
			uint16 nLayerCount, const STerrainPageLayer& tpl, bool bAtOnceLoad);

	protected:
		Terrain*				m_pTerrain;
		STerrainPageLayer		m_PageLayer;
		float*					m_pSaveHeight;
		Rect					m_AlterRect;
	};


	// ≥°æ∞≤Âº˛  ≈‰∆˜
	struct STerrainPageEditorAdp : public SEditorPluginAdp
	{
		int						nPageX; 
		int						nPageY; 
		Vector3					vPos;
		uint16					nMinBatchSize; 
		uint16					nMaxBatchSize; 
		uint16					nLayerCount;
		STerrainPageLayer		tpl;
		bool					bAtOnceLoad;
	};

	/**
	* \ingroup : OgreTerrainEditorPlugin
	*
	* \os&IDE  : Microsoft Windows XP (SP2)  &  Microsoft Visual C++ .NET 2008
	*
	* \VERSION : 1.0
	*
	* \date    : 2013-02-16
	*
	* \Author  : lp
	*
	* \Desc    : 
	*
	* \bug     : 
	*
	* \Copyright (c) 2012 lp All rights reserved.
	*/
	class TerrainPageEditorFactory : public EditorPluginFactory
	{
	public:
		/**
		 *
		 * \param factoryName 
		 * \return 
		 */
		TerrainPageEditorFactory(const String& factoryName);

		/**
		 *
		 * \return 
		 */
		virtual ~TerrainPageEditorFactory();

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