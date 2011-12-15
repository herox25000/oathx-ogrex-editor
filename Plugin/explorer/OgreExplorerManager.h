#ifndef EXPLORER_MANAGER_H
#define EXPLORER_MANAGER_H

#include "OgreSingleton.h"

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
	class ExplorerManager : public Singleton<ExplorerManager>
	{
	public:
		/**
		 *
		 * \return 
		 */
		static	ExplorerManager&	getSingleton();

		/**
		 *
		 * \return 
		 */
		static	ExplorerManager*	getSingletonPtr();

	public:
		/**
		 *
		 * \param void 
		 * \return 
		 */
		ExplorerManager(void);

		/**
		 *
		 * \param void 
		 * \return 
		 */
		virtual ~ExplorerManager(void);

		/** 创建新项目
		 *
		 * \param sName				项目名称
		 * \param sPath				项目所在路径
		 * \return 
		 */
		virtual bool				create(const String& sName, const String& sPath);

		/**	加载项目
		 *
		 * \param sName				项目名称
		 * \return 
		 */
		virtual bool				load(const String& sName);

		/**	卸载项目
		 *
		 */
		virtual void				unload(const String& sName);

	protected:
		String						m_sName;
	};
}

#endif
