#ifndef _____OgreTerrainEditorBrush_H
#define _____OgreTerrainEditorBrush_H

namespace Ogre
{
#ifndef BRUSH_DATA_SIZE
#	define BRUSH_DATA_SIZE	128
#endif

	class Terrain;

	/**
	* \ingroup : OgreTerrainEditorPlugin
	*
	* \os&IDE  : Microsoft Windows XP (SP2)  &  Microsoft Visual C++ .NET 2008
	*
	* \VERSION : 1.0
	*
	* \date    : 2013-02-16
	*
	* \Author  : lp
	*
	* \Desc    : 
	*
	* \bug     : 
	*
	* \Copyright (c) 2012 lp All rights reserved.
	*/
	class Brush
	{
	public:
		/**
		 *
		 * \param pSceneManager 
		 * \param materialName 
		 * \param fRaidus 
		 * \param fIntensity 
		 * \param texture 
		 * \return 
		 */
		Brush(SceneManager* pSceneManager, const String& materialName, float fRaidus,
			float fIntensity, const String& texture);

		/**
		 *
		 * \return 
		 */
		virtual ~Brush();

		/**
		 *
		 * \param pTerrain 
		 * \param vPos 
		 */
		virtual	void			setPosition(Terrain* pTerrain, const Vector3& vPos);
		
		/**
		 *
		 * \return 
		 */
		virtual	Vector3			getPosition() const;

		/**
		 *
		 * \param fRadius 
		 */
		virtual	void			setRadius(float fRadius);

		/**
		 *
		 * \return 
		 */
		virtual	float			getRadius() const;

		/**
		 *
		 * \param name 
		 */
		virtual	void			setBrushTexture(const String& texture);

		/**
		 *
		 * \param fIntensity 
		 */
		virtual	void			setIntensity(float fIntensity);

		/**
		 *
		 * \return 
		 */
		virtual	float			getIntensity() const;

		/**
		 *
		 * \return 
		 */
		virtual	float*			getBrushData() const;
		
	protected:
		SceneManager*			m_pSceneManager;
		SceneNode*				m_pBrushNode;
		ManualObject*			m_pBrushMesh;
		Vector3					m_vBrushPos;
		float					m_fRaidus;
		float*					m_pBrushData;
		TexturePtr				m_pBrushTexture;
		float					m_fIntensity;
	};
}

#endif