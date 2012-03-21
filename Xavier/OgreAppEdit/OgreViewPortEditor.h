#ifndef _____OgreViewPortEditor_H
#define _____OgreViewPortEditor_H

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
	* \Desc    : 
	*
	* \bug     : 
	*
	*/
	class OgreAppEdit_Export_API ViewPortEditor : public BaseEditor
	{
	public:
		/**	构造函数
		 *
		 * \param pWindow		渲染窗口
		 * \param pCamera		摄像机
		 * \param background	背景颜色
		 * \return 
		 */
		ViewPortEditor(Camera* pCamera, const ColourValue& background);

		/** 析构函数
		 *
		 * \param void 
		 * \return 
		 */
		virtual ~ViewPortEditor(void);
		
		/**
		 *
		 * \return 
		 */
		virtual Viewport*				getViewPort() const;

		/** 窗口移动或者改变大小
		 *
		 */
		virtual void					windowMovedOrResized();
	protected:
		// 视口
		Viewport*						m_pViewPort;
		Camera*							m_pCamera;
	};

	//* 视口创建参数
	struct SViewPortCreateParam : public SBaseCreateParam
	{
		ColourValue						background;
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
	class OgreAppEdit_Export_API ViewPortEditorFactory : public BaseEditorFactory
	{
	public:
		/**
		 *
		 * \return 
		 */
		ViewPortEditorFactory();

		/**
		 *
		 * \return 
		 */
		virtual ~ViewPortEditorFactory();

		/**
		 *
		 * \param pm 
		 * \return 
		 */
		virtual BaseEditor*				create(const SBaseCreateParam* pm);
	};
}

#endif
