#ifndef _____OgreEditorPlugin_H
#define _____OgreEditorPlugin_H

#include "OgreEditorInput.h"

namespace Ogre
{
	// 插件创建适配参数
	struct SEditorPluginAdp
	{
		// 插件名称
		String		pluginName;
	};

	//////////////////////////////////////////////////////////////////////////
	// 插件映射表
	typedef HashMap<String, EditorPlugin*>		HashMapEditorPlugin;
	// 插件迭代器
	typedef MapIterator<HashMapEditorPlugin>	HashMapEditorPluginIter;

	enum{
		PRIORITY_LOWEST,
		PRIORITY_LOW,
		PRIORITY_NORMAL,
		PRIORITY_HEIGHT,
	};

	/**
	* \ingroup : OgreEditor
	*
	* \os&IDE  : Microsoft Windows XP (SP2)  &  Microsoft Visual C++ .NET 2008
	*
	* \VERSION : 1.0
	*
	* \date    : 2013-02-14
	*
	* \Author  : lp
	*
	* \Desc    : 编辑插件基类
	*
	* \bug     : 
	*
	* \Copyright (c) 2012 lp All rights reserved.
	*/
	class Ogre_EditorCore_Export_API EditorPlugin : public EditorInput
	{
	public:
		/**
		 *
		 * \param name 
		 * \return 
		 */
		EditorPlugin(const String& pluginName);

		/**
		 *
		 * \return 
		 */
		virtual ~EditorPlugin();

		/** 设置编辑插件名
		 *
		 * \param name 
		 */
		virtual	void					setName(const String& pluginName);

		/** 获取编辑插件名
		 *
		 * \return 
		 */
		virtual	String					getName() const;

		/** 注册编辑插件
		 *
		 * \param pPlugin 
		 * \return 
		 */
		virtual	bool					registerPlugin(EditorPlugin* pPlugin);

		/** 获取编辑插件
		 *
		 * \param name 
		 * \return 
		 */
		virtual	EditorPlugin*			getPlugin(const String& pluginName);

		/**
		 *
		 * \param pluginName 
		 * \return 
		 */
		virtual	EditorPlugin*			findPlugin(const String& pluginName);

		/** 注销编辑插件
		 *
		 * \param pPlugin 
		 */
		virtual	void					unregisterPlugin(EditorPlugin* pPlugin, bool bDestroy=true);

		/** 设置父编辑器
		 *
		 * \param pParent 
		 */
		virtual	void					setParent(EditorPlugin* pParent);

		/** 获取当前编辑器的父亲
		 *
		 * \return 
		 */
		virtual	EditorPlugin*			getParent() const;
		
		/** 销毁所有编辑器
		 *
		 */
		virtual	void					destroyAllPlugin();

		/** 获取子插件迭代器
		 *
		 * \return 
		 */
		virtual	HashMapEditorPluginIter	getPluginIter();
		

		/** 设置优先级，该优先级将决定编辑插件的删除顺序
		 *
		 * \param nPriority 
		 */
		virtual void					setPriority(int nPriority);

		/** 获取优先级
		 *
		 * \return 
		 */
		virtual	int						getPriority() const;

	public:
		/** 当编辑器主窗口大小发生改变时调用
		 *
		 * \param cx 
		 * \param cy 
		 * \return 
		 */
		virtual	bool					OnSize(int cx, int cy);

		/** 鼠标滚轮改变时调用
		 *
		 * \param fzDelta 
		 * \param vPos 
		 * \return 
		 */
		virtual	bool					OnMouseWheel(float fzDelta, const Vector2& vPos);

		/** 鼠标左键按下
		 *
		 * \param vPos 
		 * \return 
		 */
		virtual	bool					OnLButtonDown(const Vector2& vPos);

		/** 鼠标左键弹起
		 *
		 * \param vPos 
		 * \return 
		 */
		virtual	bool					OnLButtonUp(const Vector2& vPos);

		/** 鼠标右键按下
		 *
		 * \param vPos 
		 * \return 
		 */
		virtual	bool					OnRButtonDown(const Vector2& vPos);

		/** 鼠标左键弹起
		 *
		 * \param vPos 
		 * \return 
		 */
		virtual	bool					OnRButtonUp(const Vector2& vPos);

		/** 鼠标移动
		 *
		 * \param vPos 
		 * \return 
		 */
		virtual	bool					OnMouseMove(const Vector2& vPos);

		/** 键盘按键按下
		 *
		 * \param nChar 
		 * \param nRepCnt 
		 * \param nFlags 
		 * \return 
		 */
		virtual	bool					OnKeyDown(uint32 nChar, uint32 nRepCnt, uint32 nFlags);

		/** 键盘按键弹起
		 *
		 * \param nChar 
		 * \param nRepCnt 
		 * \param nFlags 
		 * \return 
		 */
		virtual	bool					OnKeyUp(uint32 nChar, uint32 nRepCnt, uint32 nFlags);

		/** 编辑属性改变
		 *
		 * \param parentName 
		 * \param name 
		 * \param anyValue 
		 * \param nType 
		 * \return 
		 */
		virtual	bool					OnPropertyChanged(const String& parentName, const String& name, 
			const Any& anyValue, int nType);

	protected:
		HashMapEditorPlugin				m_HashMapEditorPlugin;
		String							m_Name;
		EditorPlugin*					m_pParent;
		int								m_nPriority;
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
	* \Desc    : 插件创建工厂
	*
	* \bug     : 
	*
	* \Copyright (c) 2012 lp All rights reserved.
	*/
	class Ogre_EditorCore_Export_API EditorPluginFactory
	{
	public:
		/**
		 *
		 * \param typeName 
		 * \return 
		 */
		EditorPluginFactory(const String& factoryName)
			: m_factoryName(factoryName)
		{

		}

		/**
		 *
		 * \return 
		 */
		virtual ~EditorPluginFactory()
		{

		}

		/**
		 *
		 * \return 
		 */
		virtual	String			getName() const
		{
			return m_factoryName;
		}
		
		/**
		 *
		 * \param ssadp 
		 * \param pParent 
		 * \return 
		 */
		virtual	EditorPlugin*	createPlugin(const SEditorPluginAdp& ssadp, EditorPlugin* pParent) = 0;

	protected:
		String					m_factoryName;
	};
}

#endif