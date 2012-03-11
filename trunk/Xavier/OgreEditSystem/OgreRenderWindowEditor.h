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
	* \Desc    : ��Ⱦ���ڱ༭
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

		/** ��ȡ��Ⱦ����
		 *
		 * \return 
		 */
		virtual RenderWindow*		getRenderWindow() const;
		
	protected:
		RenderWindow*				m_pWindow;	//* ogre render window pointer */
	};

	// ��Ⱦ���ڴ��������ձ���Ĳ���
	struct SRenderWindowCreateParams : public SBaseCreateParam
	{
		bool						bFullScreen;		// �Ƿ�ȫ��
		HWND						hWnd;				// ���ھ��
		int							nWidth;				// ���ڿ�
		int							nHeight;			// ���ڸ�
		
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
	* \Desc    : ��Ⱦ�༭����
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
