#include "stdafx.h"
#include "XavierAppEditor.h"
#include "XavierWorldSpaceEditor.h"

namespace Ogre
{
	/**
	 *
	 * \param typeName 
	 * \return 
	 */
	XavierWorldSpaceEditor::XavierWorldSpaceEditor(const String& typeName, const SWorldSpaceServerAdp& adp, const String& propertySetFile)
		: XavierEditor(typeName, propertySetFile)
	{
		ServerFactory* pWorldSpaceFactory = System::getSingleton().getServerFactory(
			WorldSpaceServerFactory::FactoryTypeName
			);
		if (pWorldSpaceFactory)
		{
			m_pServer = pWorldSpaceFactory->createServer(adp);
			ASSERT(m_pServer);
						
			// 订阅属性改变事件
			m_pServer->subscribeEvent(PropertySet::EventValueChanged, 
				Event::Subscriber(&XavierWorldSpaceEditor::onPropertyChanaged, this)
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
	XavierWorldSpaceEditor::~XavierWorldSpaceEditor()
	{
		System::getSingleton().delServer(m_pServer);
	}

	/**
	 *
	 * \param args 
	 * \return 
	 */
	bool			XavierWorldSpaceEditor::onPropertyChanaged(const EventArgs& args)
	{
		return 0;
	}
	
	//////////////////////////////////////////////////////////////////////////
	const String	XavierWorldSpaceEditorFactory::FACTORY_NAME	= "Xavier/XavierWorldSpaceEditorFactory";

	/**
	 *
	 * \param typeName 
	 * \return 
	 */
	XavierWorldSpaceEditorFactory::XavierWorldSpaceEditorFactory()
	{
	}

	/**
	 *
	 * \return 
	 */
	XavierWorldSpaceEditorFactory::~XavierWorldSpaceEditorFactory()
	{
	}

	/**
	 *
	 * \return 
	 */
	const String&	XavierWorldSpaceEditorFactory::getTypeName() const
	{
		return XavierWorldSpaceEditorFactory::FACTORY_NAME;
	}

	/**
	 *
	 * \param pNode 
	 * \return 
	 */
	XavierEditor*	XavierWorldSpaceEditorFactory::create(const SSAdp& ssadp)
	{
		const SWorldSpaceServerAdp& adp = static_cast<const SWorldSpaceServerAdp&>(ssadp);
		return new XavierWorldSpaceEditor(ssadp.typeName, adp, 
			m_PropertySetFile);
	}
}