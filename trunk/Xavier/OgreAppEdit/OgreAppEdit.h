#ifndef _____OgreAppEdit_H
#define _____OgreAppEdit_H

#include "OgreSingleton.h"
#include "OgreBaseEditor.h"

namespace Ogre
{
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
	class OgreAppEdit_Export_API AppEdit : public BaseEditor, public Singleton<AppEdit>
	{
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
		RenderWindow*				m_pRenderWindow;
		VEditorPlugin				m_vPlugin;
		VDynLib						m_vDynlib;
	};
}

#endif
