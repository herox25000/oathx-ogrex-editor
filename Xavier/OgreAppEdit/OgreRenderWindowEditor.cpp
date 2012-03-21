#include "OgreAppEditPrerequisites.h"
#include "OgreRenderWindowEditor.h"
#include "OgreAppEdit.h"

namespace Ogre
{
	/**
	 *
	 * \return 
	 */
	RenderWindowEditor::RenderWindowEditor(RenderWindow* pRenderWindow)
		: m_pWindow(pRenderWindow)
	{
		setTypeName(EDIT_RENDERWINDOW);
	}

	/**
	 *
	 * \param void 
	 * \return 
	 */
	RenderWindowEditor::~RenderWindowEditor(void)
	{
	}

	/**
	 *
	 * \return 
	 */
	RenderWindow*	RenderWindowEditor::getRenderWindow() const
	{
		return m_pWindow;
	}

	//////////////////////////////////////////////////////////////////////////
	//
	//////////////////////////////////////////////////////////////////////////
	RenderWindowEditorFactory::RenderWindowEditorFactory()
	{
		setTypeName(FACTORY_RENDERWINDOW);
	}

	/**
	 *
	 * \return 
	 */
	RenderWindowEditorFactory::~RenderWindowEditorFactory()
	{

	}

	/**
	 *
	 * \param pm 
	 * \return 
	 */
	BaseEditor*		RenderWindowEditorFactory::create(const SBaseCreateParam* pm)
	{
		if (pm != NULL)
		{
			/*
				获取渲染参数
			*/
			SRenderWindowCreateParams* rwcm = (SRenderWindowCreateParams*)(pm);
			
			/*
				创建渲染窗口编辑器
			*/
			BaseEditor* editor = new RenderWindowEditor(
				AppEdit::getSingletonPtr()->getRenderWindow()
				);

			return editor;
		}

		return NULL;
	}
}

