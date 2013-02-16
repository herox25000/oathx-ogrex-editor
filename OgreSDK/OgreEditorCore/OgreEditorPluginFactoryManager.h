#ifndef _____OgreEditorPluginFactoryManager_H
#define _____OgreEditorPluginFactoryManager_H

#include "OgreEditorSceneManager.h"
#include "OgreEditorCamera.h"
#include "OgreEditorViewport.h"

namespace Ogre
{
	enum {
		EPF_SCENEMANAGER,
		EPF_CAMERA,
		EPF_VIEWPORT,
		EPF_TERRAINGROUP,
	};

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
	* \Desc    : 编辑插件工厂管理器
	*
	* \bug     : 
	*
	* \Copyright (c) 2012 lp All rights reserved.
	*/
	class Ogre_EditorCore_Export_API EditorPluginFactoryManager : public Singleton<EditorPluginFactoryManager>
	{
		typedef HashMap<String, EditorPluginFactory*>	HashMapEditorPluginFactory;
	public:
		/** 获取编辑工厂
		 *
		 * \return 
		 */
		static	EditorPluginFactoryManager&	getSingleton();

		/**
		 *
		 * \return 
		 */
		static	EditorPluginFactoryManager*	getSingletonPtr();
	public:
		/** 构造函数
		 *
		 * \return 
		 */
		EditorPluginFactoryManager();

		/** 析构函数
		 *
		 * \return 
		 */
		virtual ~EditorPluginFactoryManager();

		/** 注册编辑工厂
		 *
		 * \param pFactory 
		 * \return 
		 */
		virtual	bool						registerEditorPluginFactory(EditorPluginFactory* pFactory);

		/** 获取编辑工厂
		 *
		 * \param factoryName 
		 * \return 
		 */
		virtual	EditorPluginFactory*		getEditorPluginFactory(const String& factoryName);

		/** 获取编辑工厂
		 *
		 * \param nType 
		 * \return 
		 */
		virtual	EditorPluginFactory*		getEditorPluginFactory(const int nType);

		/** 注销编辑工厂
		 *
		 * \param factoryName 
		 */
		virtual	void						unregisterEditorPluginFactory(const String& factoryName);
	private:
		HashMapEditorPluginFactory			m_HashMapEditorPluginFactory;
	};
}

#endif