#pragma once

#include "OgreMaterial.h"
#include "OgreVector2.h"
#include "OgreVector3.h"

namespace Ogre 
{ 
	class SceneManager; 
	class SceneNode; 
	class Frustum; 
	class TextureUnitState; 
	class Pass;
	class WorldSpaceServer;
}

/**
* \ingroup : Xavier
*
* \os&IDE  : Microsoft Windows XP (SP3)  &  Microsoft Visual C++ .NET 2008 & ogre1.8
*
* \VERSION : 1.0
*
* \@date   : 2012-05-30
*
* \Author  : lp
*
* \Desc    : Ìù»¨Êó±ê
*
* \bug     : 
*
*/
class XavierDecalCursor
{
public:
	/**
	 *
	 * \param pWorldServer 
	 * \param name 
	 * \param vSize 
	 * \return 
	 */
	XavierDecalCursor(Ogre::WorldSpaceServer* pWorldServer, const Ogre::String& name, const Ogre::Vector2& vSize);

	/**
	 *
	 * \param void 
	 * \return 
	 */
	virtual ~XavierDecalCursor(void);

	/**
	 *
	 * \param vSize 
	 * \param name 
	 */
	virtual	void				createDecalCursor(const Ogre::Vector2& vSize);

	/**
	 *
	 * \param vSize 
	 */
	virtual	void				setDecalSize(const Ogre::Vector2& vSize);
protected:
	Ogre::WorldSpaceServer*		m_pWorldServer;
	Ogre::Vector2				m_vSize;
	Ogre::Vector3				m_vPos;
	Ogre::SceneNode*			m_pProjectionNode;
	Ogre::Frustum*				m_pFrustum;
	Ogre::TextureUnitState*		m_pTextureUnitState;
	Ogre::Pass*					m_pPass;
	Ogre::MaterialPtr			m_pMaterial;
	Ogre::String				m_name;
	bool						m_bVaisible;
};
