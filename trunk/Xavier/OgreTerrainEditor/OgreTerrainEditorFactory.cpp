#include "OgreAppEditPrerequisites.h"
#include "OgreTerrainEditorFactory.h"
#include "OgreTerrainEditor.h"

namespace Ogre
{
	/**
	 *
	 * \param void 
	 * \return 
	 */
	TerrainEditorFactory::TerrainEditorFactory(void)
	{
		setTypeName(FACTORY_TERRAIN);
	}

	/**
	 *
	 * \param void 
	 * \return 
	 */
	TerrainEditorFactory::~TerrainEditorFactory(void)
	{
	}

	/**
	 *
	 * \param pm 
	 * \return 
	 */
	BaseEditor*	TerrainEditorFactory::create(const SBaseCreateParam* pm)
	{
		return NULL;
	}
}
