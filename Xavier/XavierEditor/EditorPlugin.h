#ifndef _____EditorPlugin_H
#define _____EditorPlugin_H

namespace Ogre
{
	// 插件创建适配参数
	struct SEditorPluginAdp
	{
		// 插件名称
		String		pluginName;
	};

	// 插件映射表
	typedef HashMap<String, EditorPlugin*>		HashMapEditorPlugin;
	// 插件迭代器
	typedef MapIterator<HashMapEditorPlugin>	HashMapEditorPluginIter;

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
	* \Desc    : 编辑插件
	*
	* \bug     : 
	*
	* \Copyright (c) 2012 lp All rights reserved.
	*/
	class EditorPlugin : public PropertySet
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

		/**
		 *
		 * \param pParent 
		 */
		virtual	void					setParent(EditorPlugin* pParent);

		/**
		 *
		 * \return 
		 */
		virtual	EditorPlugin*			getParent() const;

		/**
		 *
		 * \return 
		 */
		virtual	HashMapEditorPluginIter	getPluginIter();
		
		/**
		 *
		 * \param bInheritPick 
		 */
		virtual	void					setInheritPick(bool bInheritPick);

		/**
		 *
		 * \return 
		 */
		virtual	bool					getInheritPick() const;
	public:
		/**
		 *
		 * \param cx 
		 * \param cy 
		 * \return 
		 */
		virtual	bool					OnSize(int cx, int cy);

		/**
		 *
		 * \param fzDelta 
		 * \param vPos 
		 * \return 
		 */
		virtual	bool					OnMouseWheel(float fzDelta, const Vector2& vPos);

		/**
		 *
		 * \param vPos 
		 * \return 
		 */
		virtual	bool					OnLButtonDown(const Vector2& vPos);

		/**
		 *
		 * \param vPos 
		 * \return 
		 */
		virtual	bool					OnLButtonUp(const Vector2& vPos);

		/**
		 *
		 * \param vPos 
		 * \return 
		 */
		virtual	bool					OnRButtonDown(const Vector2& vPos);

		/**
		 *
		 * \param vPos 
		 * \return 
		 */
		virtual	bool					OnRButtonUp(const Vector2& vPos);

		/**
		 *
		 * \param vPos 
		 * \return 
		 */
		virtual	bool					OnMouseMove(const Vector2& vPos);

		/**
		 *
		 * \param nChar 
		 * \param nRepCnt 
		 * \param nFlags 
		 * \return 
		 */
		virtual	bool					OnKeyDown(uint32 nChar, uint32 nRepCnt, uint32 nFlags);

		/**
		 *
		 * \param nChar 
		 * \param nRepCnt 
		 * \param nFlags 
		 * \return 
		 */
		virtual	bool					OnKeyUp(uint32 nChar, uint32 nRepCnt, uint32 nFlags);

		/**
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
		bool							m_bInheritPick;
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
	class EditorPluginFactory
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