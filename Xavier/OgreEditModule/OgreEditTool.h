#pragma once

#include "OgreEditToolPrerequisites.h"
#include "OgreEditPluginFactroy.h"

namespace Ogre
{
	/**
	* \ingroup : OgreEditModule
	*
	* \os&IDE  : Microsoft Windows XP (SP3)  &  Microsoft Visual C++ .NET 2008 & ogre1.8
	*
	* \VERSION : 1.0
	*
	* \@date   : 2012-03-10
	*
	* \Author  : lp
	*
	* \Desc    : Ogre EditTool Manager
	*
	* \bug     : 
	*
	*/
	class OgreEditTool_Export_API EditTool : public Singleton<EditTool>
	{
		// 编辑表
		typedef std::map<String, EditPluginFactroy*>	StrPluginFactroy;
	public:
		/**
		 *
		 * \return 
		 */
		static	EditTool&				getSingleton();

		/**
		 *
		 * \return 
		 */
		static	EditTool*				getSingletonPtr();

	public:
		/**
		 *
		 * \param void 
		 * \return 
		 */
		EditTool(void);

		/**
		 *
		 * \param void 
		 * \return 
		 */
		virtual ~EditTool(void);

		 /** 注册编辑工程
		  *
		  * \param pDescribe			插件描述
		  * \param pPluginFactroy		插件工厂
		  */
		virtual void					registerEditorFactory(void* pDescribe, EditPluginFactroy* pPluginFactroy);

		/**
		 *
		 * \param pPluginFactroy 
		 */
		virtual void					registerEditorFactory(EditPluginFactroy* pPluginFactroy);

		/**
		 *
		 * \param sName 
		 * \return 
		 */
		virtual EditPluginFactroy*		getEditorFactory(const String& sName);

	protected:
		StrPluginFactroy				m_StrPluginFactroy;
	};
}


