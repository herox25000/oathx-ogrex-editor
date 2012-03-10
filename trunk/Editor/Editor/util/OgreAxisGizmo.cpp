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
	
	AxisGizmo*	AxisGizmo::getSingletonPtr()
	{
		return msSingleton;
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
	void	AxisGizmo::showAxisGizmo(bool bVisible)
	{
		Ogre::Entity* pEntity = m_pSceneManager->createEntity("AxisAxisgizmo", 
			"ogrehead.mesh");
		if (pEntity != NULL)
		{
			m_pAxisGizmo = m_pSceneManager->createSceneNode();
			m_pAxisGizmo->attachObject(pEntity);
			m_pAxisGizmo->scale(5,5,5);
			m_pAxisGizmo->setPosition(0,0,0);

			pEntity->setRenderQueueGroup( Ogre::RENDER_QUEUE_SKIES_LATE );	
		}
	}
}