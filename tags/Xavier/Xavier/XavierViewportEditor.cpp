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
			
			// º”‘ÿ Ù–‘
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