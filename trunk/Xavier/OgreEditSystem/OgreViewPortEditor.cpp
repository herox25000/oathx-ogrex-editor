#include "OgreEditSystemPrerequisites.h"
#include "OgreViewPortEditor.h"
#include "OgreRenderWindowEditor.h"
#include "OgreEditSystem.h"

namespace Ogre
{
	/** ���캯��
	 *
	 * \param pWindow 
	 * \param pCamera 
	 * \param background 
	 * \return 
	 */
	ViewPortEditor::ViewPortEditor(RenderWindow* pWindow, Camera* pCamera, const ColourValue& background)
		:m_pViewPort(NULL), m_pWindow(pWindow), m_pCamera(pCamera)
	{
		/*
		* ����ӿ�
		*/
		m_pViewPort = pWindow->addViewport(pCamera);
		if (m_pViewPort != NULL)
		{
			/*
			* ���ñ�����ɫ
			*/
			m_pViewPort->setBackgroundColour(background);

			pWindow->windowMovedOrResized();
			pCamera->setAspectRatio(
				Ogre::Real(m_pViewPort->getActualWidth()) / Ogre::Real(m_pViewPort->getActualHeight())
				);	
		}

		setTypeName(EDIT_VIEWPORT);
	}

	/** ��������
	 *
	 * \param void 
	 * \return 
	 */
	ViewPortEditor::~ViewPortEditor(void)
	{
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
		if (m_pWindow != NULL && m_pCamera != NULL)
		{
			m_pWindow->windowMovedOrResized();

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

			/*
			* ��ȡ��Ⱦ����
			*/
			RenderWindowEditor* pRWEditor = dynamic_cast<RenderWindowEditor*>(
				EditSystem::getSingletonPtr()->getEditor(EDIT_RENDERWINDOW)
				);
			if (pRWEditor != NULL)
			{
				/*
				* ��ȡ����������
				*/
				SceneManager* pMgr = Root::getSingletonPtr()->getSceneManager(NAME_SCENEMANAGER);
				assert(pMgr != NULL);
				
				BaseEditor* editor = new ViewPortEditor(pRWEditor->getRenderWindow(),
					pMgr->getCamera(NAME_CAMERA), cm->background);

				return editor;
			}
		}

		return NULL;
	}

}
