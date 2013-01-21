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
		 * \return 
		 */
		World();

		/**
		 *
		 * \return 
		 */
		virtual ~World();
	};
}

#endif