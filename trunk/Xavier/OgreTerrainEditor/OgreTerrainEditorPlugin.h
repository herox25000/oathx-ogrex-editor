#ifndef _____OgreTerrainEditor_H
#define _____OgreTerrainEditor_H

#include "OgreEditorPlugin.h"

namespace Ogre
{
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
	* \Desc    : 地形编辑插件
	*
	* \bug     : 
	*
	*/
	class TerrainEditorPlugin : public EditorPlugin
	{
	public:
		static const String	PluginTerrainEditorName;

	public:
		/**
		 *
		 * \param void 
		 * \return 
		 */
		TerrainEditorPlugin(void);

		/**
		 *
		 * \param void 
		 * \return 
		 */
		virtual ~TerrainEditorPlugin(void);

	public:
		/**
		 *
		 * \return 
		 */
		virtual const String&	getName() const;

		/** 安装插件
		 *
		 * \return 
		 */
		virtual bool			install();

		/** 卸载插件
		 *
		 */
		virtual void			uninstall();

		/**
		 *
		 */
		virtual void			initialise();

		/**
		 *
		 */
		virtual void			shutdown();
	};
}

#endif
