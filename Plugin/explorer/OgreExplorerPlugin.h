#ifndef EXPLORER_PLUGIN_H
#define EXPLORER_PLUGIN_H

#include "OgrePlugin.h"
#include "OgreExplorerManager.h"

namespace Ogre
{
	/**
	* \ingroup : explorer
	*
	* \os&IDE  : Microsoft Windows XP (SP2)  &  Microsoft Visual C++ .NET 2008 & ogre1.8
	*
	* \VERSION : 1.0
	*
	* \date    : 2011-12-15
	*
	* \Author  : lp
	*
	* \Desc    : 
	*
	* \bug     : 
	*
	*/
	class _OgreExplorerExport ExplorerPlugin : public Plugin
	{
	public:
		/**
		 *
		 * \param void 
		 * \return 
		 */
		ExplorerPlugin(void);

		/**
		 *
		 * \param void 
		 * \return 
		 */
		virtual ~ExplorerPlugin(void);

		/**
		 *
		 * \return 
		 */
		const String&		getName() const;

		/**
		 *
		 */
		void				install();

		/**
		 *
		 */
		void				initialise();

		/**
		 *
		 */
		void				shutdown();

		/**
		 *
		 */
		void				uninstall();
	private:
		ExplorerManager*	m_pExplorerManager;
	};
}

#endif
