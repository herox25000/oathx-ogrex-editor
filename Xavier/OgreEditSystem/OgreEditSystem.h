#ifndef _____OgreEditSystem_H
#define _____OgreEditSystem_H

#include "OgreSingleton.h"

namespace Ogre
{
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
	class Ogre_EditSystem_Export_API EditSystem : public Singleton<EditSystem>
	{
		// 编辑工厂容器
		typedef HashMap<String, BaseEditorFactory*> StrEditorFactory;
		
		// 编辑器容器
		typedef HashMap<String, BaseEditor*>		StrEditor;
	public:
		/** 获取编辑系统
		 *
		 * \return 
		 */
		static	EditSystem&			getSingleton();

		/** 获取编辑系统
		 *
		 * \return 
		 */
		static	EditSystem*			getSingletonPtr();

	public:
		/** 构造函数
		 *
		 * \param void 
		 * \return 
		 */
		EditSystem(void);

		/** 析构函数
		 *
		 * \param void 
		 * \return 
		 */
		virtual ~EditSystem(void);

	public:
		/** 创建编辑系统
		 *
		 * \param pluginFileName	
		 * \param resourceFileName  
		 * \return 
		 */
		virtual	bool				createSystem(const String& pluginFileName, const String& resourceFileName);

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

		/** 销毁编辑系统
		 *
		 */
		virtual void				destroySystem();
		
	protected:
		Root*						m_pRoot;	// ogre root object
		StrEditorFactory			m_Factory;	// 编辑工厂
		StrEditor					m_Editor;
	};
}

#endif
