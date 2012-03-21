#include "OgreAppEditPrerequisites.h"
#include "OgreViewPortEditor.h"
#include "OgreRenderWindowEditor.h"
#include "OgreAppEdit.h"

namespace Ogre
{
	/** ���캯��
	 *
	 * \param pWindow 
	 * \param pCamera 
	 * \param background 
	 * \return 
	 */
	ViewPortEditor::ViewPortEditor(Camera* pCamera, const ColourValue& background)
		:m_pViewPort(NULL), m_pCamera(pCamera)
	{
		/*
		* ����ӿ�
		*/
		m_pViewPort = AppEdit::getSingletonPtr()->getRenderWindow()->addViewport(pCamera);
		if (m_pViewPort != NULL)
		{
			/*
			* ���ñ�����ɫ
			*/
			m_pViewPort->setBackgroundColour(background);

			AppEdit::getSingletonPtr()->getRenderWindow()->windowMovedOrResized();
			pCamera->setAspectRatio(
				Ogre::Real(m_pViewPort->getActualWidth()) / Ogre::Real(m_pViewPort->getActualHeight())
				);	
		}

		setTypeName(EDIT_VIEWPORT);
		
		// add property
		addProperty("background", Any(background),
			"�ӿڱ�����ɫ");
		addProperty("Width", Any(AppEdit::getSingletonPtr()->getRenderWindow()->getWidth()),
			"�ӿڿ��");
		addProperty("Height",Any(AppEdit::getSingletonPtr()->getRenderWindow()->getHeight()),
			"�ӿڸ߶�");
	}

	/** ��������
	 *
	 * \param void 
	 * \return 
	 */
	ViewPortEditor::~ViewPortEditor(void)
	{
		AppEdit::getSingletonPtr()->getRenderWindow()->removeViewport(m_pViewPort->getZOrder());
	}

	/**
	 *
	 * \return 
	 */
	Viewport*		ViewPortEditor::getViewPort() const
	{
		return m_pViewPort;
	}

	/**
	 *
	 */
	void			ViewPortEditor::windowMovedOrResized()
	{
		RenderWindow* pRenderWindow = AppEdit::getSingletonPtr()->getRenderWindow();
		if (m_pCamera != NULL && pRenderWindow != NULL)
		{
			pRenderWindow->windowMovedOrResized();
			
			//fireEvent("");

			m_pCamera->setAspectRatio(
				Ogre::Real(m_pViewPort->getActualWidth()) / Ogre::Real(m_pViewPort->getActualHeight())
				);	
		}
	}

	//////////////////////////////////////////////////////////////////////////
	//
	//////////////////////////////////////////////////////////////////////////
	ViewPortEditorFactory::ViewPortEditorFactory()
	{
		setTypeName(FACTORY_VIEWPORT);
	}

	ViewPortEditorFactory::~ViewPortEditorFactory()
	{

	}

	BaseEditor*		ViewPortEditorFactory::create(const SBaseCreateParam* pm)
	{
		if (pm != NULL)
		{
			SViewPortCreateParam* cm = (SViewPortCreateParam*)(pm);
			
			// ��ȡ��Ⱦ����
			RenderWindow* pRenderWindow = AppEdit::getSingletonPtr()->getRenderWindow();

			/*
			* ��ȡ����������
			*/
			SceneManager* pMgr = Root::getSingletonPtr()->getSceneManager(NAME_SCENEMANAGER);
			assert(pMgr != NULL);
			
			BaseEditor* editor = new ViewPortEditor(pMgr->getCamera(NAME_CAMERA), 
				cm->background);

			return editor;
		}

		return NULL;
	}

}
