#ifndef _____OgreTerrainFactory_H
#define _____OgreTerrainFactory_H

#include "OgreBaseEditor.h"

namespace Ogre
{
	// 地形创建参数
	struct STerrainCreateParam : public SBaseCreateParam
	{

	};

	/**
	* \ingroup : OgreTerrainEditor
	*
	* \os&IDE  : Microsoft Windows XP (SP3)  &  Microsoft Visual C++ .NET 2008 & ogre1.8
	*
	* \VERSION : 1.0
	*
	* \@date   : 2012-03-27
	*
	* \Author  : lp
	*
	* \Desc    : 
	*
	* \bug     : 
	*
	*/
	class TerrainEditorFactory : public BaseEditorFactory
	{
	public:
		/**
		 *
		 * \param void 
		 * \return 
		 */
		TerrainEditorFactory(void);

		/**
		 *
		 * \param void 
		 * \return 
		 */
		virtual ~TerrainEditorFactory(void);

	public:
		/**
		 *
		 * \param pm 
		 * \return 
		 */
		virtual BaseEditor*				create(const SBaseCreateParam* pm);
	};
}

#endif