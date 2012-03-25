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
	ViewPortEditor::ViewPortEditor(Camera* pCamera, const ColourValue& background)
		:m_pViewPort(NULL), m_pCamera(pCamera)
	{
		/*
		* 添加视口
		*/
		m_pViewPort = AppEdit::getSingletonPtr()->getRenderWindow()->addViewport(pCamera);
		if (m_pViewPort != NULL)
		{
			/*
			* 设置背景颜色
			*/
			m_pViewPort->setBackgroundColour(background);

			AppEdit::getSingletonPtr()->getRenderWindow()->windowMovedOrResized();
			pCamera->setAspectRatio(
				Ogre::Real(m_pViewPort->getActualWidth()) / Ogre::Real(m_pViewPort->getActualHeight())
				);	
		}

		setTypeName(EDIT_VIEWPORT);
		
		// add property
		addProperty("Background", Any(background),
			"视口背景颜色", PROPERTY_COLOUR);

		subscribeEvent(PropertySet::EventValueChanged, Event::Subscriber(&ViewPortEditor::onPropertyChanaged, this));
	}

	/** 析构函数
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
			
			m_pCamera->setAspectRatio(
				Ogre::Real(m_pViewPort->getActualWidth()) / Ogre::Real(m_pViewPort->getActualHeight())
				);	
		}
	}

	/**
	 *
	 * \param args 
	 */
	bool			ViewPortEditor::onPropertyChanaged(const EventArgs& args)
	{
		const PropertyEventArgs& evt = static_cast<const PropertyEventArgs&>(args);
		if (evt.pProperty != NULL)
		{
			String name = evt.pProperty->getName();
			if (name == "Background")
				m_pViewPort->setBackgroundColour(any_cast<ColourValue>(evt.pProperty->getValue()));
		}

		return true;
	}

	//////////////////////////////////////////////////////////////////////////
	//
	//////////////////////////////////////////////////////////////////////////
	/**
	 *
	 * \return 
	 */
	ViewPortEditorFactory::ViewPortEditorFactory()
	{
		setTypeName(FACTORY_VIEWPORT);
	}

	/**
	 *
	 * \return 
	 */
	ViewPortEditorFactory::~ViewPortEditorFactory()
	{

	}

	/**
	 *
	 * \param pm 
	 * \return 
	 */
	BaseEditor*		ViewPortEditorFactory::create(const SBaseCreateParam* pm)
	{
		if (pm != NULL)
		{
			SViewPortCreateParam* cm = (SViewPortCreateParam*)(pm);
			
			// 获取渲染窗口
			RenderWindow* pRenderWindow = AppEdit::getSingletonPtr()->getRenderWindow();

			/*
			* 获取场景管理器
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
