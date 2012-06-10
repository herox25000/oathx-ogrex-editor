#include "stdafx.h"
#include "XavierAppEditor.h"
#include "XavierViewportEditor.h"

namespace Ogre
{
	/**
	 *
	 * \param typeName 
	 * \return 
	 */
	XavierViewportEditor::XavierViewportEditor(const String& typeName, const SViewportServerAdp& adp, const String& propertySetFile)
		: XavierEditor(typeName, propertySetFile)
	{
		ServerFactory* pViewportFactory = System::getSingleton().getServerFactory(
			ViewportServerFactory::FactoryTypeName
			);
		if (pViewportFactory)
		{
			m_pServer = pViewportFactory->createServer(adp);
			ASSERT(m_pServer);
			
			// 订阅属性改变事件
			m_pServer->subscribeEvent(PropertySet::EventValueChanged, 
				Event::Subscriber(&XavierViewportEditor::onPropertyChanaged, this)
				);

			// 加载属性
			loadProperty();

			System::getSingleton().addServer(m_pServer);
		}
	}

	/**
	 *
	 * \return 
	 */
	XavierViewportEditor::~XavierViewportEditor()
	{
		System::getSingleton().delServer(m_pServer);
	}

	/**
	 *
	 */
	void			XavierViewportEditor::windowMovedOrResized()
	{
		ViewportServer* pViewServer = static_cast<ViewportServer*>(m_pServer);
		if (pViewServer)
			pViewServer->windowMovedOrResized();
	}

	/**
	 *
	 * \param args 
	 * \return 
	 */
	bool			XavierViewportEditor::onPropertyChanaged(const EventArgs& args)
	{
		const PropertyEventArgs& evt = static_cast<const PropertyEventArgs&>(args);
		if (evt.pProperty != NULL)
		{
			ViewportServer* pViewServer = static_cast<ViewportServer*>(m_pServer);
			if (pViewServer)
			{
				String name = evt.pProperty->getName();
				if (name == "BackgroundColour")
				{
					ColourValue clrValue = any_cast<ColourValue>(evt.pProperty->getValue());
					pViewServer->setBackgroundColour(clrValue);
				}
			}
		}

		return 0;
	}
	
	//////////////////////////////////////////////////////////////////////////
	const String	XavierViewportEditorFactory::FACTORY_NAME	= "Xavier/XavierViewportEditorFactory";

	/**
	 *
	 * \param typeName 
	 * \return 
	 */
	XavierViewportEditorFactory::XavierViewportEditorFactory()
	{
	}

	/**
	 *
	 * \return 
	 */
	XavierViewportEditorFactory::~XavierViewportEditorFactory()
	{
	}

	/**
	 *
	 * \return 
	 */
	const String&	XavierViewportEditorFactory::getTypeName() const
	{
		return XavierViewportEditorFactory::FACTORY_NAME;
	}

	/**
	 *
	 * \param pNode 
	 * \return 
	 */
	XavierEditor*	XavierViewportEditorFactory::create(const SSAdp& ssadp)
	{
		const SViewportServerAdp& adp = static_cast<const SViewportServerAdp&>(ssadp);
		return new XavierViewportEditor(ssadp.typeName, adp, 
			m_PropertySetFile);
	}
}