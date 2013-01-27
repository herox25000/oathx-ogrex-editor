#ifndef _____EditorTerrainPage_H
#define _____EditorTerrainPage_H

namespace Ogre
{
#ifndef MAX_LAYERS_ALLOWED
#define MAX_LAYERS_ALLOWED 6
#endif

	struct STerrainPageLayer
	{
		float	fLayerWorldSize[MAX_LAYERS_ALLOWED];
		String	layerDiffuseTexture[MAX_LAYERS_ALLOWED];
		String	layerNormalTexture[MAX_LAYERS_ALLOWED];
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
	class EditorTerrainPage : public EditorPlugin
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
		EditorTerrainPage(const String& pluginName, int nPageX, int nPageY, const Vector3& vPos, uint16 nMinBatchSize, uint16 nMaxBatchSize,
			uint16 nLayerCount, const STerrainPageLayer& tpl, bool bAtOnceLoad);

		/**
		 *
		 * \return 
		 */
		virtual ~EditorTerrainPage();

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
	};


	// 场景插件适配器
	struct SEditorPluginTerrainPageAdp : public SEditorPluginAdp
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
	* \ingroup : XavierEditor
	*
	* \os&IDE  : Microsoft Windows XP (SP2)  &  Microsoft Visual C++ .NET 2008
	*
	* \VERSION : 1.0
	*
	* \date    : 2013-01-24
	*
	* \Author  : lp
	*
	* \Desc    : 场景插件工厂
	*
	* \bug     : 
	*
	* \Copyright (c) 2012 lp All rights reserved.
	*/
	class EditorTerrainPageFactory : public EditorPluginFactory
	{
	public:
		/**
		 *
		 * \param factoryName 
		 * \return 
		 */
		EditorTerrainPageFactory(const String& factoryName);

		/**
		 *
		 * \return 
		 */
		virtual ~EditorTerrainPageFactory();

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