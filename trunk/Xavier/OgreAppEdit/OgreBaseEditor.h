#ifndef _____OgreBaseEditor_H
#define _____OgreBaseEditor_H

#include "OgreProperty.h"

namespace Ogre
{
	class BaseEditor;
	class BaseEditorFactory;

	// 子编辑器
	typedef std::deque<BaseEditor*>			VEditor;
	typedef std::deque<BaseEditorFactory*>	VEditorFactory;

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
	* \Desc    : 编辑工具基类
	*
	* \bug     : 
	*
	*/
	class OgreAppEdit_Export_API BaseEditor : public PropertySet
	{
	public:
		/** 构造函数
		 *
		 * \param void 
		 * \return 
		 */
		BaseEditor();

		/** 析构函数
		 *
		 * \param void 
		 * \return 
		 */
		virtual ~BaseEditor(void);

		/** 获取编辑类型名
		 *
		 * \return 
		 */
		virtual	String				getTypeName() const;

		/** 设置编辑类型名
		 *
		 * \param typeName 
		 */
		virtual void				setTypeName(const String& typeName);

		/** 加载编辑器
		 *
		 * \param sPath 
		 * \return 
		 */
		virtual bool				load(const String& sPath);

		/** 卸载编辑器
		 *
		 */
		virtual void				unload();

		/** 添加子编辑器
		 *
		 * \param pEditor 
		 */
		virtual void				addEditor(BaseEditor* pEditor);

		/**
		 *
		 * \param name 
		 * \return 
		 */
		virtual BaseEditor*			getEditor(const String& name);	

		/**
		 *
		 * \param pEditor 
		 */
		virtual void				delEditor(BaseEditor* pEditor);

		/**
		 *
		 */
		virtual void				clearEditor();

		/**
		 *
		 * \return 
		 */
		virtual BaseEditor*			getEditor(int index);

		/**
		 *
		 * \return 
		 */
		virtual size_t				getEditorCount() const;

		/** 注册编辑器
		 *
		 * \param pFactory 
		 * \return 
		 */
		virtual void				registerEditorFactory(BaseEditorFactory* pFactory);

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

		/** 清空编辑器
		 *
		 */
		virtual void				clearEditorFactory();

		/** 设置父编辑器
		 *
		 * \param pEditor 
		 */
		virtual void				setParent(BaseEditor* pEditor);

		/** 获取父编辑器
		 *
		 * \return 
		 */
		virtual BaseEditor*			getParent() const;
	protected:
		String						m_typeName;
		VEditor						m_vEditor;
		VEditorFactory				m_vFactory;
		BaseEditor*					m_pParent;
	};

	// 基本创建参数
	struct SBaseCreateParam
	{
		String		typeName;		
	};

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
	class OgreAppEdit_Export_API BaseEditorFactory
	{
	public:
		/** 构造函数
		 *
		 * \param void 
		 * \return 
		 */
		BaseEditorFactory(void);

		/** 析构函数
		 *
		 * \param void 
		 * \return 
		 */
		virtual ~BaseEditorFactory(void);

		/** 获取编辑类型名
		 *
		 * \return 
		 */
		virtual String					getTypeName() const;

		/** 设置编辑类型名
		 *
		 * \param typeName 
		 */
		virtual void					setTypeName(const String& typeName);

		/** 创建
		 *
		 * \param pm 
		 * \return 
		 */
		virtual BaseEditor*				create(const SBaseCreateParam* pm) = 0;

	protected:
		String							m_typeName;
	};
}

#endif
