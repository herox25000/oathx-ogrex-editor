#ifndef _____OgreTerrainEditorPlugin_H
#define _____OgreTerrainEditorPlugin_H

#include "OgreTerrainEditor.h"

namespace Ogre
{
	/**
	* \ingroup : OgreTerrainEditorPlugin
	*
	* \os&IDE  : Microsoft Windows XP (SP3)  &  Microsoft Visual C++ .NET 2008
	*
	* \VERSION : 1.0
	*
	* \date    : 2013-02-16
	*
	* \Author  : lp
	*
	* \Desc    :
	*
	* \bug     : 
	*
	* \Copyright (c) 2012 lp All rights reserved.
	*/
	class TerrainEditorPlugin : public Plugin
	{
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
	protected:
		String					m_Name;
	};
}

#endif