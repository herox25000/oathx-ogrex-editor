#include "stdafx.h"
#include "EditorCamera.h"
#include "EditorViewport.h"
#include "EditorPluginFactoryManager.h"
#include "EditorSystem.h"

namespace Ogre
{
	//////////////////////////////////////////////////////////////////////////
	enum {
		VIEWPORT_PLUGIN_NAME,
		VIEWPORT_BACKGROUND,

		VIEWPORT_COUNT,
	};

	static const String viewportName[] =
	{
		"Name",
		"Background",
	};

	static const String viewportDesc[] = 
	{
		"Name",
		"Background",
	};

	/**
	 *
	 * \param name 
	 * \return 
	 */
	static int	convertViewportPropertyType(const String& name)
	{
		for (int i=0; i<VIEWPORT_COUNT; i++)
		{
			if (viewportName[i] == name)
				return i;
		}

		return 0;
	}
	
	//////////////////////////////////////////////////////////////////////////
	/**
	 *
	 * \param pluginName 
	 * \param background 
	 * \param adp 
	 * \return 
	 */
	EditorViewport::EditorViewport(const String& pluginName, const ColourValue& background, const SEditorCamearAdp& adp)
		: EditorPlugin(pluginName), m_pViewport(NULL), m_pCamera(NULL)
	{
		if (configure(pluginName, background, adp))
		{
			addProperty(viewportName[VIEWPORT_PLUGIN_NAME], Any(pluginName), PVT_STRING, 0, viewportDesc[VIEWPORT_PLUGIN_NAME]);
			addProperty(viewportName[VIEWPORT_BACKGROUND], Any(background), PVT_COLOUR, true, viewportDesc[VIEWPORT_BACKGROUND]);
		}
	}

	/**
	 *
	 * \return 
	 */
	EditorViewport::~EditorViewport()
	{

	}

	/**
	 *
	 * \return 
	 */
	bool	EditorViewport::configure(const String& pluginName, const ColourValue& background, const SEditorCamearAdp& adp)
	{
		EditorPluginFactory* pCameraFactory = EditorPluginFactoryManager::getSingletonPtr()->getEditorPluginFactory(EPF_CAMERA);
		if (pCameraFactory)
		{
			m_pCamera = static_cast<EditorCamera*>(pCameraFactory->createPlugin(adp, this));
			if (m_pCamera == NULL)
			{
				LogManager::getSingleton().logMessage(LML_CRITICAL, 
					"Can't create editor plugin : " + adp.pluginName);
				return 0;
			}
			
			Camera* p = m_pCamera->getCamera();
			if (p)
			{
				m_pViewport = EditorSystem::getSingletonPtr()->getRenderWindow()->addViewport(p);
				if (m_pViewport)
				{

					EditorSystem::getSingletonPtr()->getRenderWindow()->windowMovedOrResized();
					p->setAspectRatio(
						Real(m_pViewport->getActualWidth()) / Real(m_pViewport->getActualHeight())
						);

					/*
					* 设置背景颜色
					*/
					m_pViewport->setBackgroundColour(background);

					return true;
				}
			}	
		}

		return 0;
	}

	/**
	 *
	 * \return 
	 */
	Viewport*		EditorViewport::getViewport() const
	{
		return m_pViewport;
	}
	
	/**
	 *
	 */
	void			EditorViewport::windowMovedOrResized()
	{
		RenderWindow* pRenderWindow = EditorSystem::getSingleton().getRenderWindow();
		if (m_pCamera != NULL && pRenderWindow != NULL)
		{
			pRenderWindow->windowMovedOrResized();

			m_pCamera->getCamera()->setAspectRatio(
				Real(m_pViewport->getActualWidth()) / Real(m_pViewport->getActualHeight())
				);
		}
	}

	/**
	 *
	 * \return 
	 */
	EditorCamera*	EditorViewport::getActiveCamera() const
	{
		return m_pCamera;
	}

	/**
	 *
	 * \param vPos 
	 * \param ray 
	 * \return 
	 */
	bool			EditorViewport::getMouseRay(const Vector2& vPos, Ray& ray)
	{
		if (m_pCamera == NULL || m_pViewport == NULL)
			return 0;
		
		Camera* pActive = m_pCamera->getCamera();
		if (pActive)
		{
			ray = pActive->getCameraToViewportRay(vPos.x / m_pViewport->getActualWidth(), 
				vPos.y / m_pViewport->getActualHeight());

			return true;
		}
	
		return 0;
	}

	/**
	 *
	 * \param cx 
	 * \param cy 
	 * \return 
	 */
	bool			EditorViewport::OnSize(int cx, int cy)
	{
		if (m_pCamera != NULL && m_pViewport != NULL)
		{
			windowMovedOrResized();
		}
		
		return EditorPlugin::OnSize(cx, cy);
	}

	/**
	 *
	 * \param parentName 
	 * \param name 
	 * \param anyValue 
	 * \param nType 
	 * \return 
	 */
	bool			EditorViewport::OnPropertyChanged(const String& parentName, const String& name, 
		const Any& anyValue, int nType)
	{
		int nPropertyType = convertViewportPropertyType(parentName.empty() ? name : parentName);
		if ( nPropertyType < 0)
		{
			LogManager::getSingleton().logMessage(LML_CRITICAL, "Can't find property " + name);
			return 0;
		}

		switch( nPropertyType )
		{
		case VIEWPORT_BACKGROUND:
			{
				ColourValue background = m_pViewport->getBackgroundColour();

				int nNormal = convertNormalPropertyType(name);
				switch( nNormal )
				{
				case NORMAL_RGB:
					{
						uint32 rgb = any_cast<uint32>(anyValue);
						int a = GetR(rgb);
						int b = GetG(rgb);
						int c = GetB(rgb);

						background.r = NormalValue(GetR(rgb));
						background.g = NormalValue(GetG(rgb));
						background.b = NormalValue(GetB(rgb));
					}
					break;
				case NORMAL_ALHPA:
					{
						background.a = any_cast<float>(anyValue);
					}
					break;
				}

				m_pViewport->setBackgroundColour(background);
				
			}
			break;
		}

		return true;
	}

	//////////////////////////////////////////////////////////////////////////
	
	/**
	 *
	 * \param factoryName 
	 * \return 
	 */
	EditorViewportFactory::EditorViewportFactory(const String& factoryName)
		: EditorPluginFactory(factoryName)
	{

	}

	/**
	 *
	 * \return 
	 */
	EditorViewportFactory::~EditorViewportFactory()
	{

	}

	/**
	 *
	 * \param ssadp 
	 * \param pParent 
	 * \return 
	 */
	EditorPlugin*		EditorViewportFactory::createPlugin(const SEditorPluginAdp& ssadp, 
		EditorPlugin* pParent)
	{
		const SEditorPluginViewportAdp& adp = static_cast<const SEditorPluginViewportAdp&>(ssadp);

		EditorViewport* pEditorViewport = new EditorViewport(adp.pluginName, adp.background, adp.cameraAdp);
		if (pEditorViewport)
		{
			// 设置删除优先级
			pEditorViewport->setPriority(PRIORITY_LOW);

			LogManager::getSingleton().logMessage(LML_NORMAL,
				"Create editor plugin : " + adp.pluginName);

			if (pParent)
				pParent->registerPlugin(pEditorViewport);

			return pEditorViewport;
		}

		return NULL;
	}
}