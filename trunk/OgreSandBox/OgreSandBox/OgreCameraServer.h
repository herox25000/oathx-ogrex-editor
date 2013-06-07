#ifndef _____OgreCameraServer_H
#define _____OgreCameraServer_H

namespace Ogre
{
	// camera server adapter param
	struct SCameraAdp : public SSAdp
	{
		Vector3			vPos;					// the camera positon
		Quaternion		q;				
		float			fNearClipDistance;
		float			fFarClipDistance;
		float			fFov;
		bool			bAutoAspectRatio;
		uint32			nQueryFlags;
	};

	/**
	* \ingroup : OgreSandBox
	*
	* \os&IDE  : Microsoft Windows XP (SP3)  &  Microsoft Visual C++ .NET 2008
	*
	* \VERSION : 1.0
	*
	* \date    : 2013-06-07
	*
	* \Author  : lp
	*
	* \Desc    : camera server
	*
	* \bug     : 
	*
	* \Copyright (c) 2012 lp All rights reserved.
	*/
	class Ogre_SandBox_Export_API CameraServer : public Server
	{
	public:
		/**
		 *
		 * \param nID 
		 * \param szName 
		 * \return 
		 */
		CameraServer(uint32 nID, const String& szName);

		/**
		 *
		 * \return 
		 */
		virtual ~CameraServer();

	public:
		/**
		 *
		 * \param ssadp 
		 * \return 
		 */
		virtual bool			configure(const SSAdp& ssadp);

	protected:
		Camera*					m_pCamera;
	};
}

#endif