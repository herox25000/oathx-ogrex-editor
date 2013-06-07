#ifndef _____OgreSandBoxUnity_H
#define _____OgreSandBoxUnity_H

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
	class Ogre_SandBox_Export_API Unity
	{
	public:
		/**
		 *
		 * \param szName 
		 * \return 
		 */
		static bool			createDirectory(const String& szName);

		/**
		 *
		 * \param szPath 
		 * \return 
		 */
		static String		getPath(const String& szPath);
		/**
		 *
		 * \param szPath 
		 * \return 
		 */
		static String		getName(const String& szPath);
	};
}

#endif