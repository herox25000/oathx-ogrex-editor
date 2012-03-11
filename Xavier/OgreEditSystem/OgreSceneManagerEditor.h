#ifndef _____OgreSceneManagerEditor_H
#define _____OgreSceneManagerEditor_H

#include "OgreBaseEditor.h"

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
	* \Desc    : 场景管理器编辑工具
	*
	* \bug     : 
	*
	*/
	class Ogre_EditSystem_Export_API SceneManagerEditor : public BaseEditor
	{
	public:
		/** 构造函数
		 *
		 * \param void 
		 * \return 
		 */
		SceneManagerEditor(SceneTypeMask typeMask, const String& sName);

		/** 析构函数
		 *
		 * \param void 
		 * \return 
		 */
		virtual ~SceneManagerEditor(void);

	protected:
		// OGRE 场景管理器
		SceneManager*				m_pSceneManager;
	};

	// 场景管理器创建参数
	struct SSceneManagerCreateParam : public SBaseCreateParam
	{
		String						sName;
		SceneTypeMask				typeMask;
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
	class Ogre_EditSystem_Export_API SceneManagerEditorFactory : public BaseEditorFactory
	{
	public:
		/**
		 *
		 * \return 
		 */
		SceneManagerEditorFactory();

		/**
		 *
		 * \return 
		 */
		virtual ~SceneManagerEditorFactory();

		/**
		 *
		 * \param pm 
		 * \return 
		 */
		virtual BaseEditor*			create(const SBaseCreateParam* pm);
	};
}

#endif
