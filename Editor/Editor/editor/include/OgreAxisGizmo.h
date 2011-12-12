#ifndef _____OgreAxisGizmo_H
#define _____OgreAxisGizmo_H

#include "OgreSceneManager.h"

namespace Ogre
{	
	class AxisGizmo
	{
	public:
		AxisGizmo();
		virtual ~AxisGizmo();

	public:
		static	void	createAxisGizmoMesh(Ogre::SceneManager* pSceneManager, const Ogre::String& sName);
		static	void	createAxisPlaneMesh(Ogre::SceneManager* pSceneManager, const Ogre::String& sName);
	};
}

#endif