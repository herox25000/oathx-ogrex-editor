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
	class TerrainPlugin : public Plugin
	{
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
	};
}

#endif
