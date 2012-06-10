#include "stdafx.h"
#include "XavierAppEditor.h"
#include "XavierBaseGridEditor.h"

namespace Ogre
{
	/**
	 *
	 * \param typeName 
	 * \param adp 
	 * \param propertySetFile 
	 * \return 
	 */
	XavierBaseGridEditor::XavierBaseGridEditor(const String& typeName, const SBaseGridServerAdp& adp, const String& propertySetFile)
		: XavierEditor(typeName, propertySetFile)
	{
		ServerFactory* pBaseGridFactory = System::getSingleton().getServerFactory(
			BaseGridServerFactory::FactoryTypeName
			);
		if (pBaseGridFactory)
		{
			m_pServer = pBaseGridFactory->createServer(adp);
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
	XavierBaseGridEditor::~XavierBaseGridEditor()
	{
		System::getSingleton().delServer(m_pServer);
	}

//////////////////////////////////////////////////////////////////////////
	const String	XavierBaseGridEditorFactory::FACTORY_NAME	= "Xavier/XavierBaseGridEditorFactory";

	/**
	 *
	 * \param typeName 
	 * \return 
	 */
	XavierBaseGridEditorFactory::XavierBaseGridEditorFactory()
	{
	}

	/**
	 *
	 * \return 
	 */
	XavierBaseGridEditorFactory::~XavierBaseGridEditorFactory()
	{
	}

	/**
	 *
	 * \return 
	 */
	const String&	XavierBaseGridEditorFactory::getTypeName() const
	{
		return XavierBaseGridEditorFactory::FACTORY_NAME;
	}

	/**
	 *
	 * \param pNode 
	 * \return 
	 */
	XavierEditor*	XavierBaseGridEditorFactory::create(const SSAdp& ssadp)
	{
		const SBaseGridServerAdp& adp = static_cast<const SBaseGridServerAdp&>(ssadp);
		return new XavierBaseGridEditor(ssadp.typeName, adp, 
			m_PropertySetFile);
	}
}