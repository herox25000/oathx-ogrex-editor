#ifndef _____OgreAxisGizmo_H
#define _____OgreAxisGizmo_H

#include "OgreSceneManager.h"

namespace Ogre
{	
	class AxisGizmo : public Singleton<AxisGizmo>
	{
	public:
		AxisGizmo(SceneManager* pSceneManager);
		virtual ~AxisGizmo();
		
		static AxisGizmo&	getSingleton(void);
	public:
		virtual	void		showAxisGizmoMeshFormMesh(const Ogre::String& sName);
	protected:
		Ogre::SceneManager* m_pSceneManager;
		Ogre::SceneNode*	m_pAxisGizmo;
		
	};
}

#endif