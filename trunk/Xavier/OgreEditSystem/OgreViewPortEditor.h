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
	class Ogre_EditSystem_Export_API ViewPortEditor : public BaseEditor
	{
	public:
		/**	���캯��
		 *
		 * \param pWindow		��Ⱦ����
		 * \param pCamera		�����
		 * \param background	������ɫ
		 * \return 
		 */
		ViewPortEditor(RenderWindow* pWindow, Camera* pCamera, const ColourValue& background);

		/** ��������
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

		/** �����ƶ����߸ı��С
		 *
		 */
		virtual void					windowMovedOrResized();
	protected:
		// �ӿ�
		Viewport*						m_pViewPort;
		RenderWindow*					m_pWindow;
		Camera*							m_pCamera;
	};

	//* �ӿڴ�������
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
	class Ogre_EditSystem_Export_API ViewPortEditorFactory : public BaseEditorFactory
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
