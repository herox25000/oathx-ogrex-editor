#ifndef _____EditorTerrain_H
#define _____EditorTerrain_H

#include "EditorTerrainPage.h"

namespace Ogre
{
	class MeshBrush;

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
	class EditorTerrain : public EditorPlugin, public FrameListener
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
		
		/**
		 *
		 * \return 
		 */
		virtual	MeshBrush*		getMeshBrush() const;

		/**
		 *
		 * \param texture 
		 * \param normal 
		 */
		virtual	void			setBlendTexture(const String& texture, const String& normal);

		/**
		 *
		 * \param nActionValue 
		 */
		virtual	void			setActionValue(int nActionValue);
	public:
        /** Called when a frame is about to begin rendering.
		@remarks
			This event happens before any render targets have begun updating. 
            @return
                True to go ahead, false to abort rendering and drop
                out of the rendering loop.
        */
		virtual bool			frameStarted(const FrameEvent& evt);
       
		/** Called after all render targets have had their rendering commands 
			issued, but before render windows have been asked to flip their 
			buffers over.
		@remarks
			The usefulness of this event comes from the fact that rendering 
			commands are queued for the GPU to process. These can take a little
			while to finish, and so while that is happening the CPU can be doing
			useful things. Once the request to 'flip buffers' happens, the thread
			requesting it will block until the GPU is ready, which can waste CPU
			cycles. Therefore, it is often a good idea to use this callback to 
			perform per-frame processing. Of course because the frame's rendering
			commands have already been issued, any changes you make will only
			take effect from the next frame, but in most cases that's not noticeable.
		@return
			True to continue rendering, false to drop out of the rendering loop.
		*/
		virtual bool			frameRenderingQueued(const FrameEvent& evt);
                

        /** Called just after a frame has been rendered.
		@remarks
			This event happens after all render targets have been fully updated
			and the buffers switched.
            @return
                True to continue with the next frame, false to drop
                out of the rendering loop.
        */
        virtual bool			frameEnded(const FrameEvent& evt);

	public:
		/**
		 *
		 * \param vPos 
		 * \return 
		 */
		virtual	bool			OnMouseMove(const Vector2& vPos);
		
		/**
		 *
		 * \param vPos 
		 * \return 
		 */
		virtual	bool			OnLButtonDown(const Vector2& vPos);

		/**
		 *
		 * \param vPos 
		 * \return 
		 */
		virtual bool			OnLButtonUp(const Vector2& vPos);

		/**
		 *
		 * \param nChar 
		 * \param nRepCnt 
		 * \param nFlags 
		 * \return 
		 */
		virtual	bool			OnKeyDown(uint32 nChar, uint32 nRepCnt, uint32 nFlags);

		/**
		 *
		 * \param nChar 
		 * \param nRepCnt 
		 * \param nFlags 
		 * \return 
		 */
		virtual	bool			OnKeyUp(uint32 nChar, uint32 nRepCnt, uint32 nFlags);
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
		 * \param pPage 
		 * \param vPos 
		 * \param timePassed 
		 */
		virtual bool			optPaint(EditorTerrainPage* pPage, Vector3& vPos,
			float timePassed);

		/**
		 *
		 * \param pPage 
		 * \param vPos 
		 * \param timePassed 
		 * \return 
		 */
		virtual	bool			optSplat(EditorTerrainPage* pPage, Vector3& vPos,
			float timePassed);

		/**
		 *
		 * \param pPage 
		 * \param vPos 
		 * \param timePassed 
		 * \return 
		 */
		virtual	bool			optDeform(EditorTerrainPage* pPage, Vector3& vPos,
			float timePassed);
		
		/**
		 *
		 * \param pPage 
		 * \param vPos 
		 * \param timePassed 
		 * \return 
		 */
		virtual	bool			optSmooth(EditorTerrainPage* pPage, Vector3& vPos, float fAvg, float timePassed);

		/**
		 *
		 * \param vPos 
		 * \param brushRect 
		 * \param mapRect 
		 * \param nSize 
		 * \return 
		 */
		virtual	bool			optRect(const Vector3& vPos, Rect& brushRect, 
			Rect& mapRect, int nSize, float fRaidus);
		
		/**
		 *
		 */
		virtual	void			optStart();

		/**
		 *
		 */
		virtual	void			optEnd();

		/**
		 *
		 * \param pPahe 
		 * \param Vector3&vPos 
		 * \param fAvg 
		 * \param nSampleCount 
		 */
		virtual	void			calcSmoothingFactor(EditorTerrainPage* pPahe, Vector3&vPos,
			float& fAvg, int& nSampleCount);
	protected:
		EditorViewport*			m_pViewporPlugin;
		TerrainGroup*			m_pTerrainGroup;
		TerrainGlobalOptions*	m_pGlobalOptions;
		Rect					m_Region;
		MeshBrush*				m_pBrush;
		int						m_nActionValue;
		int						m_nCurAction;
		String					m_BlendTexture;
		String					m_BlendNormal;
		bool					m_bShift;
		bool					m_bActive;
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

	//////////////////////////////////////////////////////////////////////////
	/**
	* \ingroup : XavierEditor
	*
	* \os&IDE  : Microsoft Windows XP (SP3)  &  Microsoft Visual C++ .NET 2008
	*
	* \VERSION : 1.0
	*
	* \date    : 2013-01-28
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
		 * \param materialName 
		 * \param fRaidus 
		 * \param fIntensity 
		 * \param texture 
		 * \return 
		 */
		MeshBrush(SceneManager* pSceneManager, const String& materialName, float fRaidus,
			float fIntensity, const String& texture);

		/**
		 *
		 * \return 
		 */
		virtual ~MeshBrush();

		/**
		 *
		 * \param pTerrain 
		 * \param vPos 
		 */
		virtual	void			setPosition(Terrain* pTerrain, const Vector3& vPos);
		
		/**
		 *
		 * \return 
		 */
		virtual	Vector3			getPosition() const;

		/**
		 *
		 * \param fRadius 
		 */
		virtual	void			setRadius(float fRadius);

		/**
		 *
		 * \return 
		 */
		virtual	float			getRadius() const;

		/**
		 *
		 * \param name 
		 */
		virtual	void			setBrushTexture(const String& texture);

		/**
		 *
		 * \param fIntensity 
		 */
		virtual	void			setIntensity(float fIntensity);

		/**
		 *
		 * \return 
		 */
		virtual	float			getIntensity() const;

		/**
		 *
		 * \return 
		 */
		virtual	float*			getBrushData() const;
		
	protected:
		SceneManager*			m_pSceneManager;
		SceneNode*				m_pBrushNode;
		ManualObject*			m_pBrushMesh;
		Vector3					m_vBrushPos;
		float					m_fRaidus;
		float*					m_pBrushData;
		TexturePtr				m_pBrushTexture;
		float					m_fIntensity;
	};
}

#endif