#include "OgreSdkCamera.h"
#include "Ogre.h"

namespace Ogre
{
	template<> SdkCamera*	Singleton<SdkCamera>::msSingleton = NULL;
	SdkCamera&		SdkCamera::getSingleton()
	{
		assert(msSingleton != NULL); return (*msSingleton);
	}

	SdkCamera*		SdkCamera::getSingletonPtr()
	{
		assert(msSingleton != NULL); return msSingleton;
	}

	//////////////////////////////////////////////////////////////////////////
	//
	//////////////////////////////////////////////////////////////////////////
	SdkCamera::SdkCamera()
		:m_pCamera(NULL), m_pTarget(NULL)
	{
		
	}

	//////////////////////////////////////////////////////////////////////////
	SdkCamera::~SdkCamera()
	{

	}

	//////////////////////////////////////////////////////////////////////////
	void			SdkCamera::setCamera(Camera* pCamera)
	{
		m_pCamera = pCamera;
	}

	//////////////////////////////////////////////////////////////////////////
	Camera*			SdkCamera::getCamera() const
	{
		return m_pCamera;
	}

	//////////////////////////////////////////////////////////////////////////
	void			SdkCamera::setTarget(SceneNode* pTarget)
	{
		if (m_pTarget != pTarget)
		{
			m_pTarget = pTarget;
			if (m_pTarget)
			{
				m_pCamera->setAutoTracking(true, m_pTarget);
			}
			else
			{
				m_pCamera->setAutoTracking(false);
			}
		}
	}

	//////////////////////////////////////////////////////////////////////////
	SceneNode*		SdkCamera::getTarget() const
	{
		return m_pTarget;
	}

	//////////////////////////////////////////////////////////////////////////
	void			SdkCamera::setYawPitchDist(Radian yaw, Radian pitch, Real dist)
	{
		if (m_pTarget != NULL)
		{
			// ÉèÖÃÉãÏñÎ»ÖÃ
			m_pCamera->setPosition(
				m_pTarget->_getDerivedPosition()
				);
			m_pCamera->setOrientation(m_pTarget->_getDerivedOrientation());

			m_pCamera->yaw(yaw);
			m_pCamera->pitch(-pitch);

			m_pCamera->moveRelative(Vector3(0, 0, dist));
		}
	}

	//////////////////////////////////////////////////////////////////////////
	void			SdkCamera::setPosition(Vector3& vPos)
	{
		m_pCamera->setPosition(vPos);
	}

	//////////////////////////////////////////////////////////////////////////
	Vector3			SdkCamera::getPosition()
	{
		return m_pCamera->getPosition();
	}

	//////////////////////////////////////////////////////////////////////////
	void			SdkCamera::setMode(int nMode)
	{
		if (m_nMode != SDK_CS_ORBIT && nMode == SDK_CS_ORBIT)
		{
			setTarget(m_pTarget ? m_pTarget : m_pCamera->getSceneManager()->getRootSceneNode());
			m_pCamera->setFixedYawAxis(true);

			setYawPitchDist(Degree(0), Degree(15), 150);
		}
		else if (m_nMode != SDK_CS_FREELOOK && nMode == SDK_CS_FREELOOK)
		{
			m_pCamera->setAutoTracking(false);
			m_pCamera->setFixedYawAxis(true);
		}
		else if (m_nMode != SDK_CS_MANUAL && nMode == SDK_CS_MANUAL)
		{
			m_pCamera->setAutoTracking(false);
		}

		m_nMode = nMode;
	}

	//////////////////////////////////////////////////////////////////////////
	int				SdkCamera::getMode() const
	{
		return m_nMode;
	}
}