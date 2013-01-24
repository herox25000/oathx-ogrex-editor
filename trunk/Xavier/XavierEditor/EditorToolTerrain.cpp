#include "stdafx.h"
#include "EditorTool.h"
#include "EditorToolTerrain.h"

namespace Ogre
{
	//////////////////////////////////////////////////////////////////////////
	/**
	 *
	 * \param name 
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
	EditorToolTerrain::EditorToolTerrain(const String& name, float fMaxPixelError, 
		float fCompositeMapDistance, const ColourValue& clrCompositeMapDiffuse, int nTerrainSize, float fWorldSize, int nMinBatchSize, int nMaxBatchSize,
		float fInputScale, const String& texture, const Vector3& vOrigin)
		: EditorTool(name)
	{		

	}

	/**
	 *
	 * \return 
	 */
	EditorToolTerrain::~EditorToolTerrain()
	{

	}


	/**
	 *
	 * \param vPos 
	 * \return 
	 */
	bool	EditorToolTerrain::OnMouseMove(const Vector2& vPos)
	{
		return true;
	}

	/**
	 *
	 * \param evt 
	 * \return 
	 */
	bool	EditorToolTerrain::frameStarted(const FrameEvent& evt)
	{
		return true;
	}

	/**
	 *
	 * \param evt 
	 * \return 
	 */
	bool	EditorToolTerrain::frameRenderingQueued(const FrameEvent& evt)
	{
		return true;
	}

	/**
	 *
	 * \param evt 
	 * \return 
	 */
	bool	EditorToolTerrain::frameEnded(const FrameEvent& evt)
	{
		return true;
	}

	//////////////////////////////////////////////////////////////////////////
	/**
	 *
	 * \param name 
	 * \return 
	 */
	EditorToolTerrainFactory::EditorToolTerrainFactory(const String& name)
		: EditorToolFactory(name)
	{

	}

	/**
	 *
	 * \return 
	 */
	EditorToolTerrainFactory::~EditorToolTerrainFactory()
	{
		
	}

	/**
	 *
	 * \param seadp 
	 * \return 
	 */
	EditorTool*	EditorToolTerrainFactory::createEditorTool(const SEditorAdp& seadp, EditorTool* pParent)
	{
		return NULL;
	}
}