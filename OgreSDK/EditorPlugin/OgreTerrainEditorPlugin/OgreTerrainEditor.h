#ifndef _____OgreTerrainEditor_H
#define _____OgreTerrainEditor_H

#include "OgreEditorPlugin.h"

namespace Ogre
{
	/**
	* \ingroup : OgreTerrainEditorPlugin
	*
	* \os&IDE  : Microsoft Windows XP (SP2)  &  Microsoft Visual C++ .NET 2008
	*
	* \VERSION : 1.0
	*
	* \date    : 2013-02-15
	*
	* \Author  : lp
	*
	* \Desc    : 
	*
	* \bug     : 
	*
	* \Copyright (c) 2012 lp All rights reserved.
	*/
	class TerrainEditor : public EditorPlugin
	{
	public:
		/**
		 *
		 * \param void 
		 * \return 
		 */
		TerrainEditor(const String& pluginName);

		/**
		 *
		 * \param void 
		 * \return 
		 */
		virtual ~TerrainEditor(void);
	};
}

#endif
