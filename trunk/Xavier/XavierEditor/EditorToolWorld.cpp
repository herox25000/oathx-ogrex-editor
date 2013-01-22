#include "stdafx.h"
#include "EditorTool.h"
#include "EditorToolWorld.h"

namespace Ogre
{
	/**
	 *
	 * \param name 
	 * \return 
	 */
	EditorToolWorld::EditorToolWorld(const String& name, const String& worldName, const SceneTypeMask& typeMask, const ColourValue& clrAmbientLight,
		const Vector3& vPos, const Vector3& vLookAt, Real fYaw, Real fPitch, Real fNearClipDistance, Real fFarClipDistance, const ColourValue& background)
		: EditorTool(name), m_pWorld(NULL)
	{
		m_pWorld = new World(worldName, typeMask, clrAmbientLight, 
			vPos, vLookAt, fYaw, fPitch, fNearClipDistance, fFarClipDistance,
			background);
		if (m_pWorld)
		{
			addProperty("WorldName", Any(worldName), PVT_STRING, true, "修改世界节点名");
			addProperty("Background", Any(background), PVT_COLOUR, true, "修改视口背景颜色");
		}
	}

	/**
	 *
	 * \return 
	 */
	EditorToolWorld::~EditorToolWorld()
	{
		if (m_pWorld)
		{
			delete m_pWorld;
			m_pWorld = NULL;
		}
	}

	/**
	 *
	 * \param cx 
	 * \param cy 
	 * \return 
	 */
	bool	EditorToolWorld::OnSize(int cx, int cy)
	{
		if (m_pWorld)
			m_pWorld->windowMovedOrResized();

		return true;
	}

	//////////////////////////////////////////////////////////////////////////
	/**
	 *
	 * \param name 
	 * \return 
	 */
	EditorToolWorldFactory::EditorToolWorldFactory(const String& name)
		: EditorToolFactory(name)
	{

	}

	/**
	 *
	 * \return 
	 */
	EditorToolWorldFactory::~EditorToolWorldFactory()
	{
		
	}

	/**
	 *
	 * \param seadp 
	 * \return 
	 */
	EditorTool*	EditorToolWorldFactory::createEditorTool(const SEditorAdp& seadp)
	{
		const SEditorWorldAdp& adp = static_cast<const SEditorWorldAdp&>(seadp);

		return new EditorToolWorld(adp.name, adp.worldName, adp.typeMask, adp.clrAmbientLight,
			adp.vPos, adp.vLookAt, adp.fYaw, adp.fPitch, adp.fNearClipDistance, adp.fFarClipDistance,
			adp.background);
	}
}