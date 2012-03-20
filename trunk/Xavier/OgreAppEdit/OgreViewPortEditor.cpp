#include "OgreAppEditPrerequisites.h"
#include "OgreViewPortEditor.h"
#include "OgreRenderWindowEditor.h"
#include "OgreAppEdit.h"

namespace Ogre
{
	/** 构造函数
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
		* 添加视口
		*/
		m_pViewPort = pWindow->addViewport(pCamera);
		if (m_pViewPort != NULL)
		{
			/*
			* 设置背景颜色
			*/
			m_pViewPort->setBackgroundColour(background);

			pWindow->windowMovedOrResized();
			pCamera->setAspectRatio(
				Ogre::Real(m_pViewPort->getActualWidth()) / Ogre::Real(m_pViewPort->getActualHeight())
				);	
		}

		setTypeName(EDIT_VIEWPORT);
		
		// add property
		addProperty("background", Any(ColourValue(0,0,0,0)), "视口背景颜色");
	}

	/** 析构函数
	 *
	 * \param void 
	 * \return 
	 */
	ViewPortEditor::~ViewPortEditor(void)
	{
		m_pWindow->removeViewport(m_pViewPort->getZOrder());
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
			* 获取渲染工厂
			*/
			RenderWindowEditor* pRWEditor = dynamic_cast<RenderWindowEditor*>(
				AppEdit::getSingletonPtr()->getEditor(EDIT_RENDERWINDOW)
				);
			if (pRWEditor != NULL)
			{
				/*
				* 获取场景管理器
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
