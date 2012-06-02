#ifndef _____OgreTerrainPlugin_H
#define _____OgreTerrainPlugin_H

#include "OgrePlugin.h"

namespace Ogre
{
	/**
	* \ingroup : Plugin_Terrain
	*
	* \os&IDE  : Microsoft Windows XP (SP3)  &  Microsoft Visual C++ .NET 2008 & ogre1.8
	*
	* \VERSION : 1.0
	*
	* \@date   : 2012-05-06
	*
	* \Author  : lp
	*
	* \Desc    : 
	*
	* \bug     : 
	*
	*/
	class Ogre_Terrain_Export_API TerrainPlugin : public Plugin
	{
	public:
		// ²å¼þÃû³Æ
		static const String		TerrainPluginName;

	public:
		/**
		 *
		 * \param void 
		 * \return 
		 */
		TerrainPlugin(void);

		/**
		 *
		 * \param void 
		 * \return 
		 */
		virtual ~TerrainPlugin(void);

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
