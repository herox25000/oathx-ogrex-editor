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

		/** ��������Ŀ
		 *
		 * \param sName				��Ŀ����
		 * \param sPath				��Ŀ����·��
		 * \return 
		 */
		virtual bool				create(const String& sName, const String& sPath);

		/**	������Ŀ
		 *
		 * \param sName				��Ŀ����
		 * \return 
		 */
		virtual bool				load(const String& sName);

		/**	ж����Ŀ
		 *
		 */
		virtual void				unload(const String& sName);

	protected:
		String						m_sName;
	};
}

#endif
