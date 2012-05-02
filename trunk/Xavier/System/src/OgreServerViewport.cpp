#include "OgreSystemPrerequisites.h"
#include "OgreServerViewport.h"
#include "OgreServerCamera.h"
#include "OgreSystem.h"

namespace Ogre
{
		/** 构造函数
	 *
	 * \param pWindow 
	 * \param pCamera 
	 * \param background 
	 * \return 
	 */
	ViewportServer::ViewportServer(const String& typeName, Camera* pCamera, const ColourValue& background)
		: Server(typeName), m_pViewPort(NULL), m_pCamera(pCamera)
	{
		/*
		* 添加视口
		*/
		m_pViewPort = System::getSingleton().getApplicationWindow()->addViewport(pCamera);
		if (m_pViewPort != NULL)
		{
			/*
			* 设置背景颜色
			*/
			m_pViewPort->setBackgroundColour(background);

			System::getSingleton().getApplicationWindow()->windowMovedOrResized();
			pCamera->setAspectRatio(
				Ogre::Real(m_pViewPort->getActualWidth()) / Ogre::Real(m_pViewPort->getActualHeight())
				);	
		}
		
		ARGB argb = background.getAsARGB();
		addProperty("Background", Any(argb),
			"viewport background colour", PROPERTY_COLOUR);

		subscribeEvent(PropertySet::EventValueChanged, Event::Subscriber(&ViewportServer::onPropertyChanaged, this));
	}

	/** 析构函数
	 *
	 * \param void 
	 * \return 
	 */
	ViewportServer::~ViewportServer(void)
	{
		System::getSingleton().getApplicationWindow()->removeViewport(m_pViewPort->getZOrder());
	}

	/**
	 *
	 * \return 
	 */
	Viewport*		ViewportServer::getViewPort() const
	{
		return m_pViewPort;
	}

	/**
	 *
	 */
	void			ViewportServer::windowMovedOrResized()
	{
		RenderWindow* pRenderWindow = System::getSingleton().getApplicationWindow();
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
	bool			ViewportServer::onPropertyChanaged(const EventArgs& args)
	{
		const PropertyEventArgs& evt = static_cast<const PropertyEventArgs&>(args);
		if (evt.pProperty != NULL)
		{
			String name = evt.pProperty->getName();
			if (name == "Background")
			{
				ARGB nValue = any_cast<ARGB>(evt.pProperty->getValue());
				ColourValue backgroud;
				backgroud.setAsARGB(SetAlpha(nValue, 255));
				m_pViewPort->setBackgroundColour(backgroud);
			}
		}

		return true;
	}

	//////////////////////////////////////////////////////////////////////////
	//
	//////////////////////////////////////////////////////////////////////////

	const String	ViewportServerFactory::FactoryTypeName = "System/ViewportServerFactory";

	/**
	 *
	 * \return 
	 */
	ViewportServerFactory::ViewportServerFactory()
	{
		
	}

	/**
	 *
	 * \return 
	 */
	ViewportServerFactory::~ViewportServerFactory()
	{

	}

	/**
	 *
	 * \return 
	 */
	String		ViewportServerFactory::getTypeName() const
	{
		return ViewportServerFactory::FactoryTypeName;
	}

	/**
	 *
	 * \param pm 
	 * \return 
	 */
	Server*		ViewportServerFactory::createServer(const SSAdp& ssadp)
	{
		const SViewportServerAdp& adp = static_cast<const SViewportServerAdp&>(ssadp);

		CameraServer* pSdkCamera = static_cast<CameraServer*>(
			System::getSingleton().getServer(adp.depServerName)
			);
		if (pSdkCamera != NULL)
		{
#ifdef _OUTPUT_LOG
			TKLogEvent("create server " + adp.typeName + " dependencie server " + (adp.depServerName.empty() ? "NULL" : adp.depServerName));
#endif

			return new ViewportServer(adp.typeName, 
				pSdkCamera->getCamera(), adp.background);
		}

		return NULL;
	}
}