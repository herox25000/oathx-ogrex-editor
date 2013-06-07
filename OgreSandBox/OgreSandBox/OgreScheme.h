#ifndef _____OgreSchemeServer_H
#define _____OgreSchemeServer_H

namespace Ogre
{
	struct SSchemeAdp : public SSAdp
	{
		String				szPathName;
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
	* \Desc    : 
	*
	* \bug     : 
	*
	* \Copyright (c) 2012 lp All rights reserved.
	*/
	class Ogre_SandBox_Export_API Scheme : public Server
	{
	public:
		static const String		EventNamespace;
		static const String		ServerTypeName;
	public:
		/**
		 *
		 * \param nID 
		 * \param szName 
		 * \return 
		 */
		Scheme(const uint32 nID, const String& szName);

		/**
		 *
		 * \return 
		 */
		virtual ~Scheme();

		/**
		 *
		 * \param ssadp 
		 */
		virtual	bool			configure(const SSAdp& ssadp);
	};
}

#endif