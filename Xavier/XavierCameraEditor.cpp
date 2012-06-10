#include "stdafx.h"
#include "XavierAppEditor.h"
#include "XavierCameraEditor.h"

namespace Ogre
{
	/**
	 *
	 * \param typeName 
	 * \param adp 
	 * \param propertySetFile 
	 * \return 
	 */
	XavierCameraEditor::XavierCameraEditor(const String& typeName, const SSdkCameraServerAdp& adp, const String& propertySetFile)
		: XavierEditor(typeName, propertySetFile)
	{
		ServerFactory* pCameraFactory = System::getSingleton().getServerFactory(
			CameraServerFactory::FactoryTypeName
			);
		if (pCameraFactory)
		{
			m_pServer = pCameraFactory->createServer(adp);
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
	XavierCameraEditor::~XavierCameraEditor()
	{
		System::getSingleton().delServer(m_pServer);
	}

	/**
	 *
	 * \param vPos 
	 * \return 
	 */
	bool			XavierCameraEditor::OnMouseMove(const Vector2& vPos)
	{
		CameraServer* pCamerServer = static_cast<CameraServer*>(m_pServer);
		if (pCamerServer)
		{
			pCamerServer->injectMouseMove(vPos.x, vPos.y);
			return true;
		}

		return 0;
	}

	/**
	 *
	 * \param zDelta 
	 * \return 
	 */
	bool			XavierCameraEditor::OnMouseWheel(float zDelta, const Vector2& vPos)
	{
		CameraServer* pCamerServer = static_cast<CameraServer*>(m_pServer);
		if (pCamerServer)
		{
			pCamerServer->injectMouseWheel(zDelta);
			return true;
		}
		
		return 0;
	}

	//////////////////////////////////////////////////////////////////////////
	const String	XavierCameraEditorFactory::FACTORY_NAME	= "Xavier/XavierCameraEditorFactory";

	/**
	 *
	 * \param typeName 
	 * \return 
	 */
	XavierCameraEditorFactory::XavierCameraEditorFactory()
	{
	}

	/**
	 *
	 * \return 
	 */
	XavierCameraEditorFactory::~XavierCameraEditorFactory()
	{
	}

	/**
	 *
	 * \return 
	 */
	const String&	XavierCameraEditorFactory::getTypeName() const
	{
		return XavierCameraEditorFactory::FACTORY_NAME;
	}

	/**
	 *
	 * \param pNode 
	 * \return 
	 */
	XavierEditor*	XavierCameraEditorFactory::create(const SSAdp& ssadp)
	{
		const SSdkCameraServerAdp& adp = static_cast<const SSdkCameraServerAdp&>(ssadp);
		return new XavierCameraEditor(ssadp.typeName, adp, 
			m_PropertySetFile);
	}
}