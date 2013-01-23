#pragma once

namespace Ogre
{
	/**
	* \ingroup : XavierEditor
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
	class EditorToolTerrain : public EditorTool, public Ogre::FrameListener
	{
	public:
		/**
		 *
		 * \param fMaxPixelError 
		 * \param fCompositeMapDistance 
		 * \param clrCompositeMapDiffuse 
		 * \param nTerrainSize 
		 * \param fWorldSize 
		 * \param nMinBatchSize 
		 * \param nMaxBatchSize 
		 * \param fInputScale 
		 * \param texture 
		 * \param vOrigin 
		 * \return 
		 */
		EditorToolTerrain(const String& name, float fMaxPixelError, 
			float fCompositeMapDistance, const ColourValue& clrCompositeMapDiffuse, int nTerrainSize, float fWorldSize, int nMinBatchSize, int nMaxBatchSize, 
			float fInputScale, const String& texture, const Vector3& vOrigin);

		/**
		 *
		 * \return 
		 */
		virtual ~EditorToolTerrain();

		/**
		 *
		 * \param vPos 
		 * \return 
		 */
		virtual	bool				OnMouseMove(const Vector2& vPos);
	protected:
		/**
		 *
		 * \param evt 
		 * \return 
		 */
		virtual bool				frameStarted(const Ogre::FrameEvent& evt);
			
		/**
		 *
		 * \param evt 
		 * \return 
		 */
		virtual bool				frameRenderingQueued(const Ogre::FrameEvent& evt);

		/**
		 *
		 * \param evt 
		 * \return 
		 */
		virtual bool				frameEnded(const Ogre::FrameEvent& evt);
	protected:
		/**
		 *
		 * \param terrain 
		 * \param vCntre 
		 * \param timeElapsed 
		 */
		virtual	void				upheave(Terrain* pTerrain, const Vector3& vCntre, bool bUpheave, Real timeElapsed);
	protected:
		TerrainSystem*				m_pTerrainSystem;
		DecalMesh*					m_pDecalMesh;
	};

	struct SEditorTerrainAdp : public SEditorAdp
	{
		float						fMaxPixelError;
		float						fCompositeMapDistance;
		ColourValue					clrCompositeMapDiffuse;
		float						fInputScale;
		int							nMinBatchSize;
		int							nMaxBatchSize;
		String						texture;
		float						fWorldSize;
		int							nTerrainSize;
		Vector3						vOrigin;
	};

	/**
	* \ingroup : XavierEditor
	*
	* \os&IDE  : Microsoft Windows XP (SP3)  &  Microsoft Visual C++ .NET 2008
	*
	* \VERSION : 1.0
	*
	* \date    : 2013-01-22
	*
	* \Author  : lp
	*
	* \Desc    :
	*
	* \bug     : 
	*
	* \Copyright (c) 2012 lp All rights reserved.
	*/
	class EditorToolTerrainFactory : public EditorToolFactory
	{
	public:
		/**
		 *
		 * \param name 
		 * \return 
		 */
		EditorToolTerrainFactory(const String& name);

		/**
		 *
		 * \return 
		 */
		virtual ~EditorToolTerrainFactory();

		/**
		 *
		 * \param seadp 
		 * \return 
		 */
		virtual	EditorTool*		createEditorTool(const SEditorAdp& seadp);
	};
}