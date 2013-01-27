#ifndef _____EditorPluginManager_H
#define _____EditorPluginManager_H

namespace Ogre
{
	/**
	* \ingroup : XavierEditor
	*
	* \os&IDE  : Microsoft Windows XP (SP3)  &  Microsoft Visual C++ .NET 2008
	*
	* \VERSION : 1.0
	*
	* \date    : 2013-01-24
	*
	* \Author  : lp
	*
	* \Desc    : 编辑插件管理器
	*
	* \bug     : 
	*
	* \Copyright (c) 2012 lp All rights reserved.
	*/
	class EditorPluginManager : public Singleton<EditorPluginManager>
	{
	public:
		/**
		 *
		 * \return 
		 */
		static	EditorPluginManager&	getSingleton();

		/**
		 *
		 * \return 
		 */
		static	EditorPluginManager*	getSingletonPtr();

	public:
		/**
		 *
		 * \param rootName 
		 * \return 
		 */
		EditorPluginManager(const String& rootName);

		/**
		 *
		 * \return 
		 */
		virtual ~EditorPluginManager();

		/**
		 *
		 * \return 
		 */
		virtual	EditorPlugin*			getRootPlugin() const;

		/**
		 *
		 * \param name 
		 * \return 
		 */
		virtual	EditorPlugin*			findPlugin(const String& name);
		
		/** 设置当前选择插件
		 *
		 * \param pPlugin 
		 */
		virtual	void					setSelectPlugin(EditorPlugin* pPlugin);

		/** 获取当前选择插件
		 *
		 * \return 
		 */
		virtual	EditorPlugin*			getSelectPlugin() const;
	protected:
		// 根插件
		EditorPlugin*					m_pRootPlugin;
		// 当前选择插件
		EditorPlugin*					m_pSelectPlugin;
	};
}

#endif