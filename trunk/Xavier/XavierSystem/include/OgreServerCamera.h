#ifndef _____OgreServerCamera_H
#define _____OgreServerCamera_H

namespace Ogre
{
	/**
	* \ingroup : XavierSystem
	*
	* \os&IDE  : Microsoft Windows XP (SP2)  &  Microsoft Visual C++ .NET 2008
	*
	* \VERSION : 1.0
	*
	* \date    : 2013-01-31
	*
	* \Author  : lp
	*
	* \Desc    : 
	*
	* \bug     : 
	*
	* \Copyright (c) 2012 lp All rights reserved.
	*/
	class Ogre_System_Export_API ServerCamera : public Server
	{
	public:
		/**
		 *
		 * \param pluginName 
		 * \param vPos 
		 * \param q 
		 * \param fNearClipDistance 
		 * \param fFarClipDistance 
		 * \param fFov 
		 * \param bAutoAspectRatio 
		 * \param nQueryFlags 
		 * \return 
		 */
		ServerCamera(const String& name, const Vector3& vPos, const Quaternion& q,  
			float fNearClipDistance, float fFarClipDistance, float fFov, bool bAutoAspectRatio, 
			uint32 nQueryFlags);

		/**
		 *
		 * \return 
		 */
		virtual ~ServerCamera();
		
		/**
		 *
		 * \return 
		 */
		virtual	Camera*			getCamera() const;
	protected:
		/**
		 *
		 * \param vPos 
		 * \param q 
		 * \param fNearClipDistance 
		 * \param fFarClipDistance 
		 * \param fFov 
		 * \param bAutoAspectRatio 
		 * \param nQueryFlags 
		 */
		virtual bool			configure(const String& name, const Vector3& vPos, const Quaternion& q,  
			float fNearClipDistance, float fFarClipDistance, float fFov, bool bAutoAspectRatio, 
			uint32 nQueryFlags);
	protected:
		ServerSceneManager*		m_pSceneManagerServer;
		Camera*					m_pCamera;
	};


	// …„œÒª˙±‡º≠  ≈‰≤Œ ˝
	struct SServerCameraAdp : public SServerAdp
	{
		Vector3					vPos;
		Quaternion				q;  
		float					fNearClipDistance; 
		float					fFarClipDistance; 
		float					fFov; 
		bool					bAutoAspectRatio; 
		uint32					nQueryFlags;
	};

	/**
	* \ingroup : XavierEditor
	*
	* \os&IDE  : Microsoft Windows XP (SP2)  &  Microsoft Visual C++ .NET 2008
	*
	* \VERSION : 1.0
	*
	* \date    : 2013-01-24
	*
	* \Author  : lp
	*
	* \Desc    : 
	*
	* \bug     : 
	*
	* \Copyright (c) 2012 lp All rights reserved.
	*/
	class ServerCameraFactory : public ServerFactory
	{
	public:
		/**
		 *
		 * \param factoryName 
		 * \return 
		 */
		ServerCameraFactory(const String& factoryName);

		/**
		 *
		 * \return 
		 */
		virtual ~ServerCameraFactory();

		/**
		 *
		 * \param ssadp 
		 * \param pParent 
		 * \return 
		 */
		virtual	Server*			createServer(const SServerAdp& ssadp, Server* pParent);
	};
}

#endif