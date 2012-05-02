#include "OgreSystemPrerequisites.h"
#include "OgreServerCamera.h"
#include "OgreServerWorldSpace.h"
#include "OgreSystem.h"

namespace Ogre
{
	/**
	 *
	 * \param vPos 
	 * \param vLookAt 
	 * \param fYaw 
	 * \param fPitch 
	 * \param fNearClipDistance 
	 * \param fFarClipDistance 
	 * \return 
	 */
	CameraServer::CameraServer(const String& typeName, const String& name, int nMode, WorldSpaceServer* pWorldSpace, const Vector3& vPos, const Vector3& vLookAt, Real fYaw,
		Real fPitch, Real fNearClipDistance, Real fFarClipDistance) : Server(typeName), m_pCamera(NULL), m_pTarget(NULL), m_nMode(nMode)
	{
		SceneManager* pSceneManager = pWorldSpace->getSceneManager();
		
		/*
		* 创建摄像机
		*/
		m_pCamera = pSceneManager->createCamera(name);
		
		// 设置位置
		m_pCamera->setPosition(vPos);
		// 设置观察点
		m_pCamera->lookAt(vLookAt);

		// 设置近截面和远截面
		m_pCamera->setNearClipDistance(fNearClipDistance);
		m_pCamera->setFarClipDistance(fFarClipDistance);
	
		m_pCamera->yaw(Degree(fYaw));
		m_pCamera->pitch(Degree(fPitch));

		// 添加模式属性
		addProperty("PolygonMode", Any(PM_SOLID),
			"set polygon mode", PROPERTY_POLYGONMODE);
		
		// 订阅内部事件
		subscribeEvent(PropertySet::EventValueChanged, Event::Subscriber(&CameraServer::onPropertyChanaged, this));
		setMode(nMode);
	}

	/**
	 *
	 * \param void 
	 * \return 
	 */
	CameraServer::~CameraServer(void)
	{
		SceneManager* pSceneManager = m_pCamera->getSceneManager();
		if (pSceneManager)
			pSceneManager->destroyCamera(m_pCamera);
	}
	
	/**
	 *
	 * \param args 
	 * \return 
	 */
	bool		CameraServer::onPropertyChanaged(const EventArgs& args)
	{
		const PropertyEventArgs& evt = static_cast<const PropertyEventArgs&>(args);
		if (evt.pProperty != NULL)
		{
			String name = evt.pProperty->getName();
			if (name == "PolygonMode")
				m_pCamera->setPolygonMode(any_cast<PolygonMode>(evt.pProperty->getValue()));
		}

		return true;
	}

	/**
	 *
	 * \return 
	 */
	Camera*		CameraServer::getCamera() const
	{
		return m_pCamera;
	}

	/**
	 *
	 * \param pCamera 
	 */
	void		CameraServer::setCamera(Camera* pCamera)
	{
		m_pCamera = pCamera;
	}

	/**
	 *
	 * \param pTarget 
	 */
	void		CameraServer::setTarget(SceneNode* pTarget)
	{
		if (pTarget != m_pTarget)
		{
			m_pTarget = pTarget;
			setYawPitchDist(Ogre::Degree(0), Ogre::Degree(15), 150);
			m_pCamera->setAutoTracking(true, m_pTarget);
		}
		else
		{
			m_pTarget->setAutoTracking(false);
		}
	}

	/**
	 *
	 * \return 
	 */
	SceneNode*	CameraServer::getTarget() const
	{
		return m_pTarget;
	}

	/**
	 *
	 * \param nMode 
	 */
	void		CameraServer::setMode(int nMode)
	{
		if (m_nMode != CS_ORBIT && nMode == CS_ORBIT)
		{
			setTarget(m_pTarget ? m_pTarget : m_pCamera->getSceneManager()->getRootSceneNode());
			m_pCamera->setFixedYawAxis(true);
			setYawPitchDist(Degree(0), Degree(15), 150);
		}
		else if (m_nMode != CS_FREELOOK && nMode == CS_FREELOOK)
		{
			m_pCamera->setAutoTracking(false);
			m_pCamera->setFixedYawAxis(true);
		}
		else if (m_nMode != CS_MANUAL && nMode == CS_MANUAL)
		{
			m_pCamera->setAutoTracking(false);	
		}
		
		m_nMode = nMode;
	}

	/**
	 *
	 * \return 
	 */
	int			CameraServer::getMode() const
	{
		return m_nMode;
	}

	/**
	 *
	 * \param x 
	 * \param y 
	 * \param z 
	 */
	void		CameraServer::injectMouseMove(float x, float y)
	{
		switch (m_nMode)
		{
		case CS_ORBIT:
			{
				Real dist = (m_pCamera->getPosition() - m_pTarget->_getDerivedPosition()).length();
				// to do
			}
			break;
		case CS_FREELOOK:
			{
				m_pCamera->yaw(Ogre::Degree(x * 0.15f));
				m_pCamera->pitch(Ogre::Degree(y * 0.15f));	
			}
			break;
		}
	}

	/**
	 *
	 * \param z 
	 */
	void		CameraServer::injectMouseWheel(float z)
	{
		m_pCamera->moveRelative(Ogre::Vector3(0, 0, z * 0.02f));

		TKLogEvent("camera position " + StringConverter::toString(m_pCamera->getPosition()));
	}

	/**
	 *
	 * \param key 
	 */
	void		CameraServer::injectKeyDown(int key)
	{
		switch(key)
		{
		case VK_SPACE:
			{
				
			}
			break;
		}
	}

	/**
	 *
	 * \param yaw 
	 * \param pitch 
	 * \param dist 
	 */
	void		CameraServer::setYawPitchDist(Radian yaw, Radian pitch, Real dist)
	{
		m_pCamera->setPosition(m_pTarget->_getDerivedPosition());
		m_pCamera->setOrientation(m_pTarget->_getDerivedOrientation());
		m_pCamera->yaw(yaw);
		m_pCamera->pitch(-pitch);
		m_pCamera->moveRelative(Ogre::Vector3(0, 0, dist));
	}
	
	// factory name
	const String	CameraServerFactory::FactoryTypeName = "System/CameraServerFactory";

	/**
	 *
	 * \return 
	 */
	CameraServerFactory::CameraServerFactory()
	{
		
	}

	/**
	 *
	 * \return 
	 */
	CameraServerFactory::~CameraServerFactory()
	{

	}

	/**
	 *
	 * \return 
	 */
	String		CameraServerFactory::getTypeName() const
	{
		return CameraServerFactory::FactoryTypeName;
	}
	
	/**
	 *
	 * \param pm 
	 * \return 
	 */
	Server*		CameraServerFactory::createServer(const SSAdp& ssadp)
	{
		const SSdkCameraServerAdp& adp = static_cast<const SSdkCameraServerAdp&>(ssadp);

		// 获取世界服务
		WorldSpaceServer* pWorldSpace	= static_cast<WorldSpaceServer*>(
			System::getSingleton().getServer(adp.depServerName));
		
#ifdef _OUTPUT_LOG
		TKLogEvent("create server " + adp.typeName + " dependencie server " + (adp.depServerName.empty() ? "NULL" : adp.depServerName));
#endif
		return new CameraServer(adp.typeName, adp.name, adp.nMode,
			pWorldSpace, adp.vPos, adp.vLookAt, adp.fYaw, adp.fPitch, adp.fNearClipDistance, adp.fFarClipDistance);
	}
}
