#ifndef _____OgreRenderWindowEditor_H
#define _____OgreRenderWindowEditor_H

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
	* \Desc    : 渲染窗口编辑
	*
	* \bug     : 
	*
	*/
	class Ogre_EditSystem_Export_API RenderWindowEditor : public BaseEditor
	{
	public:
		/**
		 *
		 * \param void 
		 * \return 
		 */
		RenderWindowEditor(HWND hWnd, int w, int h, bool bFullScreen);

		/**
		 *
		 * \param void 
		 * \return 
		 */
		virtual ~RenderWindowEditor(void);
		
	protected:
		RenderWindow*				m_pWindow;	//* ogre render window pointer */
	};

	// 渲染窗口创建过程终必须的参数
	struct SRenderWindowCreateParams : public SBaseCreateParam
	{
		bool						bFullScreen;		// 是否全屏
		HWND						hWnd;				// 窗口句柄
		int							nWidth;				// 窗口宽
		int							nHeight;			// 窗口搞
		
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
	* \Desc    : 渲染编辑工厂
	*
	* \bug     : 
	*
	*/
	class Ogre_EditSystem_Export_API RenderWindowEditorFactory : public BaseEditorFactory
	{
	public:
		/**
		 *
		 * \return 
		 */
		RenderWindowEditorFactory();

		/**
		 *
		 * \return 
		 */
		virtual ~RenderWindowEditorFactory();

		/**
		 *
		 * \param pm 
		 * \return 
		 */
		virtual BaseEditor*				create(const SBaseCreateParam* pm);
	};
}

#endif
