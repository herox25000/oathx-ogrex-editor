#ifndef _____EditorSystem_H
#define _____EditorSystem_H

#include "EditorPluginFactoryManager.h"
#include "EditorPluginManager.h"
#include "EditorActionManager.h"

namespace Ogre
{
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
	class EditorSystem : public Singleton<EditorSystem>
	{
	public:
		/**
		 *
		 * \return 
		 */
		static	EditorSystem&				getSingleton();

		/**
		 *
		 * \return 
		 */
		static	EditorSystem*				getSingletonPtr();
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
		virtual void				update();

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

		/**
		 *
		 * \return 
		 */
		virtual	String				getModulePath();
	protected:
		Root*						m_pRoot;
		RenderWindow*				m_pRenderWindow;
	};
}

#endif