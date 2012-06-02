#ifndef _____OgreSerialzePlugin_H
#define _____OgreSerialzePlugin_H

#include "OgrePlugin.h"

namespace Ogre
{
	/**
	* \ingroup : Plugin_Serialize
	*
	* \os&IDE  : Microsoft Windows XP (SP3)  &  Microsoft Visual C++ .NET 2008 & ogre1.8
	*
	* \VERSION : 1.0
	*
	* \@date   : 2012-05-20
	*
	* \Author  : lp
	*
	* \Desc    : 
	*
	* \bug     : 
	*
	*/
	class SerializePlugin : public Plugin
	{
	public:
		// ²å¼þÃû³Æ
		static const String		SerializePluginName;

	public:
		/**
		 *
		 * \param void 
		 * \return 
		 */
		SerializePlugin(void);

		/**
		 *
		 * \param void 
		 * \return 
		 */
		virtual ~SerializePlugin(void);

		/**
		 *
		 * \return 
		 */
		virtual const String&	getName() const;

		/**
		 *
		 */
		virtual void			install();


		/**
		 *
		 */
		virtual void			initialise();


		/**
		 *
		 */
		virtual void			shutdown();


		/**
		 *
		 */
		virtual void			uninstall();
	};
}

#endif
