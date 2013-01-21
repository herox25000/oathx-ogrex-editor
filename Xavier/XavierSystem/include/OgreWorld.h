#ifndef _____OgreWorld_H
#define _____OgreWorld_H

namespace Ogre
{
	/**
	* \ingroup : XavierSystem
	*
	* \os&IDE  : Microsoft Windows XP (SP3)  &  Microsoft Visual C++ .NET 2008
	*
	* \VERSION : 1.0
	*
	* \date    : 2013-01-21
	*
	* \Author  : lp
	*
	* \Desc    :
	*
	* \bug     : 
	*
	* \Copyright (c) 2012 lp All rights reserved.
	*/
	class Ogre_System_Export_API World : public Singleton<World>
	{
	public:
		static const String		DEFAULT_MAIN_CAMERA;
	public:
		/**
		 *
		 * \return 
		 */
		static	World&			getSingleton();

		/**
		 *
		 * \return 
		 */
		static	World*			getSingletonPtr();

	public:
		/**
		 *
		 * \param name 
		 * \param typeMask 
		 * \param clrAmbientLight 
		 * \param vPos 
		 * \param vLookAt 
		 * \param fYaw 
		 * \param fPitch 
		 * \param fNearClipDistance 
		 * \param fFarClipDistance 
		 * \return 
		 */
		World(const String& name, const SceneTypeMask& typeMask, const ColourValue& clrAmbientLight,
			const Vector3& vPos, const Vector3& vLookAt, Real fYaw, Real fPitch, Real fNearClipDistance, Real fFarClipDistance, const ColourValue& background);

		/**
		 *
		 * \return 
		 */
		virtual ~World();

		/**
		 *
		 * \return 
		 */
		virtual	SceneManager*	getSceneManager() const;
		
		/**
		 *
		 * \return 
		 */
		virtual	Camera*			getCamera() const;

		/**
		 *
		 * \return 
		 */
		virtual	Viewport*		getViewport() const;
	protected:
		/**
		 *
		 * \param vPos 
		 * \param vLookAt 
		 * \param fYaw 
		 * \param fPitch 
		 * \param fNearClipDistance 
		 * \param fFarClipDistance 
		 * \return 
		 */
		virtual	bool			configureDefault(const Vector3& vPos, const Vector3& vLookAt,
			Real fYaw, Real fPitch, Real fNearClipDistance, Real fFarClipDistance, const ColourValue& background);
	protected:
		SceneManager*			m_pSceneManager;
		Camera*					m_pCamera;
		Viewport*				m_pViewport;
	};
}

#endif