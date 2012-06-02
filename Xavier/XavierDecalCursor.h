#pragma once

#include "OgreMaterial.h"
#include "OgreVector2.h"
#include "OgreVector3.h"

namespace Ogre 
{ 
	class ManualObject;
	class WorldSpaceServer;
	class ETMTerrainServer;
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
	XavierDecalCursor(Ogre::WorldSpaceServer* pWorldServer, Ogre::ETMTerrainServer* pTerrainServer);

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
	virtual	void				createDecalCursor(float fRaidus);

	/**
	 *
	 * \param vSize 
	 */
	virtual	void				setDecalCursor(float x, float z, float fRaidus);

	/**
	 *
	 * \param x 
	 * \param z 
	 * \return 
	 */
	virtual	float				getTerrainHeight(float x, float z);
protected:
	Ogre::WorldSpaceServer*		m_pWorldServer;
	Ogre::ETMTerrainServer*		m_pTerrainServer;
	Ogre::ManualObject*			m_pDecalMesh;
};
