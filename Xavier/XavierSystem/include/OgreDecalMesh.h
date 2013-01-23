#ifndef _____OgreDecalMesh_H
#define _____OgreDecalMesh_H

namespace Ogre
{
	/**
	* \ingroup : XavierSystem
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
	class Ogre_System_Export_API DecalMesh
	{
	public:
		/**
		 *
		 * \param pSceneManager 
		 * \param fRaidus 
		 * \return 
		 */
		DecalMesh(SceneManager* pSceneManager, TerrainSystem* pTerrainSystem, const String& name, 
			float fRaidus, const String& materialName);

		/**
		 *
		 * \return 
		 */
		virtual ~DecalMesh();
		
		/**
		 *
		 * \param fRaidus 
		 */
		virtual	void				setRaidus(float fRaidus);

		/**
		 *
		 * \return 
		 */
		virtual	float				getRaidus() const;

		/**
		 *
		 * \param vSize 
		 */
		virtual	void				setPosition(const Vector3& vPos);
		
		/**
		 *
		 * \return 
		 */
		virtual	Vector3				getPosition();

		/**
		 *
		 * \param x 
		 * \param z 
		 * \return 
		 */
		virtual	float				getTerrainHeight(const Vector3& vPos);
	protected:
		/**
		 *
		 * \param vSize 
		 * \param name 
		 */
		virtual	void				createDecalMesh(const String& name, float fRaidus,
			const String& materialName);
	protected:
		TerrainSystem*				m_pTerrainSystem;
		SceneManager*				m_pSceneManager;
		ManualObject*				m_pDecalMesh;
		float						m_fRaidus;
		Vector3						m_vPos;
	};
}

#endif