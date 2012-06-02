#ifndef _____OgreTerrainPrerequisites_H
#define _____OgreTerrainPrerequisites_H

#include "OgrePrerequisites.h"

#if _WIN32
#   if defined( __MINGW32__ )
#      define Ogre_Terrain_Export_API
#   else
#      ifdef OGRETERRAIN_EXPORT
#         define Ogre_Terrain_Export_API __declspec (dllexport)
#      else
#         define Ogre_Terrain_Export_API __declspec (dllimport)
#      endif
#   endif
#else
#   define Ogre_System_Export_API
#endif

#ifndef _MSC_VER
#define sprintf_s snprintf
#endif

#include "OgreSSSDK.h"
#include "OgreTerrain.h"
#include "OgreTerrainGroup.h"
#include "OgreTerrainQuadTreeNode.h"
#include "OgreTerrainMaterialGeneratorA.h"
#include "OgreTerrainPaging.h"



#endif