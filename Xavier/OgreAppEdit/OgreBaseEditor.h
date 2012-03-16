#ifndef _____OgreBaseEditor_H
#define _____OgreBaseEditor_H

#include "OgreProperty.h"

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

	protected:
		String						m_typeName;
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
