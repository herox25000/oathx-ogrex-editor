#ifndef EXPLORER_H
#define EXPLORER_H

#include "OgreString.h"
#include "OgreExplorerPrerequisites.h"

namespace Ogre
{
	/**
	* \ingroup : explorer
	*
	* \os&IDE  : Microsoft Windows XP (SP3)  &  Microsoft Visual C++ .NET 2008 & ogre1.8
	*
	* \VERSION : 1.0
	*
	* \@date   : 2011-12-15
	*
	* \Author  : lp
	*
	* \Desc    : 导航类
	*
	* \bug     : 
	*
	*/
	class _OgreExplorerExport Explorer
	{
	public:
		/** 构造函数
		 *
		 * \param sName		项目名称
		 * \param sPath		项目路径
		 * \return 
		 */
		Explorer(const String& sName, const String& sPath);

		/** 析构函数
		 *
		 * \param void 
		 * \return 
		 */
		virtual ~Explorer(void);

	public:
		/** 设置项目路径
		 *
		 * \param sPath			绝对路径
		 */
		virtual void			setPath(const String& sPath);

		/** 获取项目绝对路径
		 *
		 * \return 
		 */
		virtual String			getPath() const;

		/** 设置项目名
		 *
		 * \param sName			项目名
		 */
		virtual void			setName(const String& sName);

		/**	获取项目名
		 *
		 * \return 
		 */
		virtual String			getName() const;

	protected:
		String					m_sName;
		String					m_sPath;
	}; 
}

#endif
