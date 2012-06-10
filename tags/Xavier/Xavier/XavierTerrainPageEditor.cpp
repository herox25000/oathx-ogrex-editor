#include "stdafx.h"
#include "XavierAppEditor.h"
#include "XavierTerrainPageEditor.h"

namespace Ogre
{
	/**
	 *
	 * \param typeName 
	 * \param adp 
	 * \param propertySetFile 
	 * \return 
	 */
	XavierTerrainPageEditor::XavierTerrainPageEditor(const String& typeName, const STerrainPageServerAdp& adp, const String& propertySetFile)
		: XavierEditor(typeName, propertySetFile)
	{
		ServerFactory* pTerrainPageFactory = System::getSingleton().getServerFactory(
			"Terrain/TerrainPageServerFactory"
			);
		if (pTerrainPageFactory)
		{
			m_pServer = pTerrainPageFactory->createServer(adp);
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
	XavierTerrainPageEditor::~XavierTerrainPageEditor()
	{
		System::getSingleton().delServer(m_pServer);
	}

	//////////////////////////////////////////////////////////////////////////
	const String	XavierTerrainPageEditorFactory::FACTORY_NAME	= "Xavier/XavierTerrainPageEditorFactory";

	/**
	 *
	 * \param typeName 
	 * \return 
	 */
	XavierTerrainPageEditorFactory::XavierTerrainPageEditorFactory()
	{

	}

	/**
	 *
	 * \return 
	 */
	XavierTerrainPageEditorFactory::~XavierTerrainPageEditorFactory()
	{

	}

	/**
	 *
	 * \return 
	 */
	const String&	XavierTerrainPageEditorFactory::getTypeName() const
	{
		return XavierTerrainPageEditorFactory::FACTORY_NAME;
	}

	/**
	 *
	 * \param pNode 
	 * \return 
	 */
	XavierEditor*	XavierTerrainPageEditorFactory::create(const SSAdp& ssadp)
	{
		const STerrainPageServerAdp& adp = static_cast<const STerrainPageServerAdp&>(ssadp);
		return new XavierTerrainPageEditor(ssadp.typeName, adp, 
			m_PropertySetFile);
	}
}