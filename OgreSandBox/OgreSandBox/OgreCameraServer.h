#ifndef _____OgreCameraServer_H
#define _____OgreCameraServer_H

namespace Ogre
{
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
	* \Desc    : 
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
	};
}

#endif