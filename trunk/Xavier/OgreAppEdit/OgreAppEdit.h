#ifndef _____OgreAppEdit_H
#define _____OgreAppEdit_H

#include "OgreSingleton.h"

namespace Ogre
{
	class BaseEditor;
	class BaseEditorFactory;
	class EditorPlugin;

	/**
	* \ingroup : OgreEditSystem
	*
	* \os&IDE  : Microsoft Windows XP (SP3)  &  Microsoft Visual C++ .NET 2008 & ogre1.8
	*
	* \VERSION : 1.0
	*
	* \@date   : 2012-03-11
	*
	* \Author  : lp
	*
	* \Desc    : 
	*
	* \bug     : 
	*
	*/
	class OgreAppEdit_Export_API AppEdit : public Singleton<AppEdit>
	{
		// 编辑工厂容器
		typedef std::map<String, BaseEditorFactory*>	StringEditorFactory;
		
		// 编辑器容器
		typedef std::deque<BaseEditor*>					VEditor;
		
		// 编辑器插件
		typedef std::vector<EditorPlugin*>				VEditorPlugin;
		typedef std::vector<DynLib*>					VDynLib;
	public:
		/** 获取编辑系统
		 *
		 * \return 
		 */
		static	AppEdit&			getSingleton();

		/** 获取编辑系统
		 *
		 * \return 
		 */
		static	AppEdit*			getSingletonPtr();

	public:
		/** 构造函数
		 *
		 * \param void 
		 * \return 
		 */
		AppEdit(void);

		/** 析构函数
		 *
		 * \param void 
		 * \return 
		 */
		virtual ~AppEdit(void);

	public:
		/** 创建编辑系统
		 *
		 * \param pluginFileName	
		 * \param resourceFileName  
		 * \return 
		 */
		virtual	bool				createSystem(const String& pluginFileName, const String& resourceFileName);
		
		/** 创建渲染窗口
		 *
		 * \param hWnd 
		 * \param w 
		 * \param h 
		 * \param bFullScree 
		 */
		virtual void				createRenderWindow(HWND hWnd, int w, int h, bool bFullScreen);
		
		/** 获取渲染窗口
		 *
		 * \return 
		 */
		virtual RenderWindow*		getRenderWindow() const;

		/** 系统更新
		 *
		 */
		virtual void				update();

		/** 注册编辑器
		 *
		 * \param pFactory 
		 * \return 
		 */
		virtual bool				registerEditorFactory(BaseEditorFactory* pFactory);

		/**
		 *
		 * \param pFactory 
		 */
		virtual void				unregisterEditorFactory(BaseEditorFactory* pFactory);

		/** 获取编辑器
		 *
		 * \param typeName 
		 * \return 
		 */
		virtual BaseEditorFactory*	getEditorFactory(const String& typeName);

		/** 注册编辑对象
		 *
		 * \param pEditor 
		 * \return 
		 */
		virtual bool				addEditor(BaseEditor* pEditor);

		/** 获取编辑对象
		 *
		 * \param typeName 
		 * \return 
		 */
		virtual BaseEditor*			getEditor(const String& typeName);

		/** 注销编辑对象
		 *
		 * \param pEditor 
		 */
		virtual void				delEditor(BaseEditor* pEditor);

		/** 注销编辑对象
		 *
		 * \param typeName 
		 */
		virtual void				delEditor(const String& typeName);

		/** 获取编辑工具
		 *
		 * \return 
		 */
		virtual int					getEditorCount();

		/** 获取编辑器
		 *
		 * \param index 
		 * \return 
		 */
		virtual BaseEditor*			getEditor(int index);

		/** 清空编辑器
		 *
		 */
		virtual void				clearEditor();

		/** 加载编辑插件
		 *
		 * \param name 
		 */
		virtual void				loadPlugin(const String& name);

		/** 卸载编辑插件
		 *
		 * \param name 
		 */
		virtual void				unloadPlugin(const String& name);

		/** 安装编辑插件
		 *
		 * \param pPlugin 
		 */
		virtual void				installPlugin(EditorPlugin* pPlugin);

		/** 删除编辑插件
		 *
		 * \param pPlugin 
		 */
		virtual void				uninstallPlugin(EditorPlugin* pPlugin);

		/**
		 *
		 */
		virtual void				clearPlugin();

		/** 销毁编辑系统
		 *
		 */
		virtual void				destroySystem();
		
	protected:
		Root*						m_pRoot;			// ogre root object
		StringEditorFactory			m_Factory;			// 编辑工厂
		VEditor						m_vEditor;
		RenderWindow*				m_pRenderWindow;
		VEditorPlugin				m_vPlugin;
		VDynLib						m_vDynlib;
	};
}

#endif
