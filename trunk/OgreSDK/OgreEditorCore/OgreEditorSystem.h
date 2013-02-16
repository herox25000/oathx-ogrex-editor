#ifndef _____OgreEditorSystem_H
#define _____OgreEditorSystem_H

#include "OgreEditorPluginFactoryManager.h"
#include "OgreEditorPluginManager.h"

namespace Ogre
{
	typedef std::vector<Plugin*>	PluginRegister;
	typedef std::vector<DynLib*>	DynlibRegister;

	/**
	* \ingroup : OgreSystem
	*
	* \os&IDE  : Microsoft Windows XP (SP3)  &  Microsoft Visual C++ .NET 2008
	*
	* \VERSION : 1.0
	*
	* \date    : 2013-01-15
	*
	* \Author  : lp
	*
	* \Desc    :
	*
	* \bug     : 
	*
	* \Copyright (c) 2012 lp All rights reserved.
	*/
	class Ogre_EditorCore_Export_API EditorSystem : public Singleton<EditorSystem>
	{
	public:
		/**
		 *
		 * \return 
		 */
		static	EditorSystem&		getSingleton();

		/**
		 *
		 * \return 
		 */
		static	EditorSystem*		getSingletonPtr();
	public:
		/**
		 *
		 * \return 
		 */
		EditorSystem();

		/**
		 *
		 * \return 
		 */
		virtual ~EditorSystem();

		/** 创建系统
		 *
		 * \param pluginFileName	系统插件配置文件
		 * \param resourceFileName	系统资源配置文件
		 * \param bAutoCreateWindow 
		 * \return 
		 */
		virtual bool				createEditorSystem(const String& pluginFileName, const String& resourceFileName, bool bAutoCreateWindow);
		
		/**
		 *
		 */
		virtual void				drawFrame();

		/** 销毁系统
		 *
		 */
		virtual void				clearUp();

	public:
		/** 创建渲染窗口
		 *
		 * \param hWnd 
		 * \param w 
		 * \param h 
		 * \param bFullScree 
		 */
		virtual bool				createRenderWindow(const String& name, HWND hWnd, 
			int w, int h, bool bFullScreen);
		
		/** 获取渲染窗口
		 *
		 * \return 
		 */
		virtual RenderWindow*		getRenderWindow() const;

		/** 加载插件
		 *
		 * \param name 
		 */
		virtual	void				loadPlugin(const String& name);

		/** 卸载插件
		 *
		 * \param name 
		 */
		virtual void				unloadPlugin(const String& name);

		/** 安装插件
		 *
		 * \param pPlugin 
		 */
		virtual void				installPlugin(Plugin* pPlugin);

		/** 卸载插件
		 *
		 * \param pPlugin 
		 */
		virtual void				uninstallPlugin(Plugin* pPlugin);

		/** 清空插件
		 *
		 */
		virtual void				clearPlugin();
	protected:
		Root*						m_pRoot;
		RenderWindow*				m_pRenderWindow;
		PluginRegister				m_vPluginRegister;
		DynlibRegister				m_vDynlibRegister;
	};
}

#endif