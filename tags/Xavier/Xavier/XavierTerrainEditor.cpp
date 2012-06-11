#include "stdafx.h"
#include "XavierAppEditor.h"
#include "XavierTerrainEditor.h"


namespace Ogre
{
	/**
	 *
	 * \param typeName 
	 * \return 
	 */
	XavierTerrainEditor::XavierTerrainEditor(const String& typeName, const STerrainGroupServerAdp& adp, const String& propertySetFile) 
		: XavierEditor(typeName, propertySetFile), m_pTerrain(0),m_nBlend(1)
	{
		ServerFactory* pTerrainGroupFactory = System::getSingleton().getServerFactory(
			"Terrain/TerrainGroupServerFactory"
			);
		if (pTerrainGroupFactory)
		{
			m_pServer = pTerrainGroupFactory->createServer(adp);
			ASSERT(m_pServer);

			loadProperty();

			System::getSingleton().addServer(m_pServer);
		}
	}

	/**
	 *
	 * \return 
	 */
	XavierTerrainEditor::~XavierTerrainEditor()
	{
		System::getSingleton().delServer(m_pServer);
	}

	/**
	 *
	 * \return 
	 */
	TerrainGroupServer*	XavierTerrainEditor::getTerrainGroupServer()
	{
		return  static_cast<TerrainGroupServer*>(m_pServer);
	}
	/**
	 *
	 * \param index 
	 * \param texture 
	 * \return 
	 */
	bool		XavierTerrainEditor::createTerrainBlend(const int index, const String& texture)
	{
		return 0;
	}

	/**
	 *
	 * \param vPos 
	 * \return 
	 */
	bool			XavierTerrainEditor::OnLButtonDown(const Vector2& vPos)
	{
		return 0;
	}

	/**
	 *
	 * \param vPos 
	 * \return 
	 */
	bool			XavierTerrainEditor::OnMouseMove(const Vector2& vPos)
	{
		return 0;
	}

	/**
	 *
	 * \param vPos 
	 * \return 
	 */
	bool			XavierTerrainEditor::OnLButtonUp(const Vector2& vPos)
	{
		return 0;
	}
	
	//////////////////////////////////////////////////////////////////////////
	const String	XavierTerrainEditorFactory::FACTORY_NAME	= "Xavier/XavierTerrainEditorFactory";

	/**
	 *
	 * \param typeName 
	 * \return 
	 */
	XavierTerrainEditorFactory::XavierTerrainEditorFactory()
	{
		// 加载地形插件
#ifdef _DEBUG
		System::getSingleton().loadPlugin("Plugin_Terrain_d.dll");
#else
		System::getSingleton().loadPlugin("Plugin_Terrain.dll");
#endif
	}

	/**
	 *
	 * \return 
	 */
	XavierTerrainEditorFactory::~XavierTerrainEditorFactory()
	{
		// 卸载地形插件
#ifdef _DEBUG
		System::getSingleton().unloadPlugin("Plugin_Terrain_d.dll");
#else
		System::getSingleton().unloadPlugin("Plugin_Terrain.dll");
#endif
	}

	/**
	 *
	 * \return 
	 */
	const String&	XavierTerrainEditorFactory::getTypeName() const
	{
		return XavierTerrainEditorFactory::FACTORY_NAME;
	}

	/**
	 *
	 * \param pNode 
	 * \return 
	 */
	XavierEditor*	XavierTerrainEditorFactory::create(const SSAdp& ssadp)
	{
		const STerrainGroupServerAdp& adp = static_cast<const STerrainGroupServerAdp&>(ssadp);
		return new XavierTerrainEditor(ssadp.typeName, adp, 
			m_PropertySetFile);
	}
}