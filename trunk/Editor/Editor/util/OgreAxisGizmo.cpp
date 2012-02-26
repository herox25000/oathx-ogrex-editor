#include "stdafx.h"
#include "OgreAxisGizmo.h"
#include "Ogre.h"

namespace Ogre
{
	template<> AxisGizmo* Singleton<AxisGizmo>::msSingleton = 0;
	AxisGizmo&	AxisGizmo::getSingleton(void)
	{
		assert( msSingleton );  return ( *msSingleton );
	}

	//////////////////////////////////////////////////////////////////////////
	//
	//////////////////////////////////////////////////////////////////////////
	AxisGizmo::AxisGizmo(SceneManager* pSceneManager)
		:m_pSceneManager(pSceneManager), m_pAxisGizmo(NULL)
	{

	}
	
	//////////////////////////////////////////////////////////////////////////
	AxisGizmo::~AxisGizmo()
	{

	}

	//////////////////////////////////////////////////////////////////////////
	void	AxisGizmo::showAxisGizmoMeshFormMesh(const Ogre::String& sName)
	{
		Ogre::Entity* pEntity = m_pSceneManager->createEntity("AxisEntity", sName);

		m_pAxisGizmo = m_pSceneManager->getRootSceneNode()->createChildSceneNode();
		m_pAxisGizmo->attachObject(pEntity);
		m_pAxisGizmo->scale(1,1,1);

		pEntity->setRenderQueueGroup( Ogre::RENDER_QUEUE_SKIES_LATE );
	}
}