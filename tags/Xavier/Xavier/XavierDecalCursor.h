#pragma once

#include "OgreMaterial.h"
#include "OgreVector2.h"
#include "OgreVector3.h"

namespace Ogre 
{ 
	class ManualObject;
	class TerrainGroupServer;
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
* \Desc    : 贴花鼠标
*
* \bug     : 
*
*/
class XavierDecalCursor
{
public:
	/**
	 *
	 * \return 
	 */
	static XavierDecalCursor&	getSingleton();


	// 单件指针
	static XavierDecalCursor*	mInstance;
public:
	/**
	 *
	 * \param pWorldServer 
	 * \param name 
	 * \param vSize 
	 * \return 
	 */
	XavierDecalCursor(Ogre::WorldSpaceServer* pWorldServer, Ogre::TerrainGroupServer* pTerrainServer);

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

	/**
	 *
	 * \param pCamera 
	 * \param nScreenX 
	 * \param nScreenY 
	 */
	virtual	void				invalid(Ogre::Camera* pCamera, float fScreenX, float fScreenY);

	/**
	 *
	 * \return 
	 */
	virtual	Ogre::Vector3&		getPosition();

	/**
	 *
	 * \param fRadius 
	 */
	virtual	void				setRadius(float fRadius);

	/**
	 *
	 * \return 
	 */
	virtual	float				getRadius() const;
protected:
	Ogre::WorldSpaceServer*		m_pWorldServer;
	Ogre::TerrainGroupServer*	m_pTerrainServer;
	Ogre::ManualObject*			m_pDecalMesh;
	Ogre::Vector3				m_vPos;
	float						m_fRadius;
};
