#ifndef _____OgreEditorViewport_H
#define _____OgreEditorViewport_H

#include "OgreEditorPlugin.h"

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
	* \Desc    : 视口编辑器
	*
	* \bug     : 
	*
	* \Copyright (c) 2012 lp All rights reserved.
	*/
	class Ogre_EditorCore_Export_API EditorViewport : public EditorPlugin
	{
	public:
		/** 构造视口编辑插件
		 *
		 * \param pluginName	插件名
		 * \param background	视口默认颜色
		 * \param adp			视口默认摄像机适配参数
		 * \return 
		 */
		EditorViewport(const String& pluginName, const ColourValue& background, const SEditorCamearAdp& adp);

		/** 析构函数
		 *
		 * \return 
		 */
		virtual ~EditorViewport();

		/** 获取包装的视口对象
		 *
		 * \return 
		 */
		virtual	Viewport*		getViewport() const;
		
		/** 窗口尺寸改变
		 *
		 */
		virtual	void			windowMovedOrResized();
		
		/** 获取当前激活的摄像机
		 *
		 * \return 
		 */
		virtual	EditorCamera*	getActiveCamera() const;

		/** 获取鼠标射线
		 *
		 * \param vPos	当前鼠标屏幕位置
		 * \param ray 
		 * \return 
		 */
		virtual bool			getMouseRay(const Vector2& vPos, Ray& ray);
	public:
		/**	当框架窗口尺寸改变时触发
		 *
		 * \param cx 
		 * \param cy 
		 * \return 
		 */
		virtual	bool			OnSize(int cx, int cy);

		/** 当编辑插件属性改变时触发
		 *
		 * \param parentName	父属性
		 * \param name			属性名
		 * \param anyValue		属性值
		 * \param nType			属性值类型
		 * \return 
		 */
		virtual bool			OnPropertyChanged(const String& parentName, const String& name, 
			const Any& anyValue, int nType);

	protected:
		/** 构造配置
		 *
		 * \param pluginName 
		 * \param background 
		 * \param adp 
		 * \return 
		 */
		virtual	bool			configure(const String& pluginName, const ColourValue& background,
			const SEditorCamearAdp& adp);
	protected:
		Viewport*				m_pViewport;
		EditorCamera*			m_pCamera;
	};

	// 场景插件适配器
	struct SEditorPluginViewportAdp : public SEditorPluginAdp
	{
		ColourValue				background;
		SEditorCamearAdp		cameraAdp;
	};

	/**
	* \ingroup : XavierEditor
	*
	* \os&IDE  : Microsoft Windows XP (SP2)  &  Microsoft Visual C++ .NET 2008
	*
	* \VERSION : 1.0
	*
	* \date    : 2013-01-24
	*
	* \Author  : lp
	*
	* \Desc    : 插件工厂
	*
	* \bug     : 
	*
	* \Copyright (c) 2012 lp All rights reserved.
	*/
	class Ogre_EditorCore_Export_API EditorViewportFactory : public EditorPluginFactory
	{
	public:
		/**
		 *
		 * \param factoryName 
		 * \return 
		 */
		EditorViewportFactory(const String& factoryName);

		/**
		 *
		 * \return 
		 */
		virtual ~EditorViewportFactory();

		/**	创建编辑插件
		 *
		 * \param ssadp			插件适配参数
		 * \param pParent		父插件
		 * \return 
		 */
		virtual	EditorPlugin*			createPlugin(const SEditorPluginAdp& ssadp, EditorPlugin* pParent);
	};
}

#endif