#ifndef _____OgreTerrainGroupEditor_H
#define _____OgreTerrainGroupEditor_H

#include "OgreBaseEditor.h"
#include "OgreTerrain.h"
#include "OgreTerrainGroup.h"
#include "OgreTerrainQuadTreeNode.h"
#include "OgreTerrainMaterialGeneratorA.h"
#include "OgreTerrainPaging.h"

namespace Ogre
{
	/**
	* \ingroup : OgreTerrainEditor
	*
	* \os&IDE  : Microsoft Windows XP (SP3)  &  Microsoft Visual C++ .NET 2008 & ogre1.8
	*
	* \VERSION : 1.0
	*
	* \@date   : 2012-03-31
	*
	* \Author  : lp
	*
	* \Desc    : 
	*
	* \bug     : 
	*
	*/
	class TerrainGroupEditor : public BaseEditor
	{
	public:
		TerrainGroupEditor(void);
		virtual ~TerrainGroupEditor(void);
	};
}

#endif
