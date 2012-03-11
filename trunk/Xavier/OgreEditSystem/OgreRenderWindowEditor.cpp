#include "OgreEditSystemPrerequisites.h"
#include "OgreRenderWindowEditor.h"

namespace Ogre
{
	/**
	 *
	 * \return 
	 */
	RenderWindowEditor::RenderWindowEditor(HWND hWnd, int w, int h, bool bFullScreen)
		: m_pWindow(NULL)
	{
		NameValuePairList pm;
		pm[KER_HANDLE_WINDOW] = StringConverter::toString((size_t)(hWnd));
		m_pWindow	= Root::getSingletonPtr()->createRenderWindow(XAVIER_WINDOW_NAME, w,
			h, bFullScreen, &pm);
		assert(m_pWindow != NULL);

		TextureManager::getSingleton().setDefaultNumMipmaps(5);
		ResourceGroupManager::getSingleton().initialiseAllResourceGroups();

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
				��ȡ��Ⱦ����
			*/
			SRenderWindowCreateParams* rwcm = (SRenderWindowCreateParams*)(pm);

			/*
				������Ⱦ���ڱ༭��
			*/
			BaseEditor* editor = new RenderWindowEditor(rwcm->hWnd,
				rwcm->nWidth, 
				rwcm->nHeight, 
				rwcm->bFullScreen);

			return editor;
		}

		return NULL;
	}
}

