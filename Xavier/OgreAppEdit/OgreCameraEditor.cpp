#include "OgreAppEditPrerequisites.h"
#include "OgreCameraEditor.h"

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
	CameraEditor::CameraEditor(const Vector3& vPos, const Vector3& vLookAt, Real fYaw,
		Real fPitch, Real fNearClipDistance, Real fFarClipDistance) : m_pCamera(NULL), m_pTarget(NULL), m_nMode(CS_FREELOOK)
	{
		SceneManager* pSceneManager = Root::getSingletonPtr()->getSceneManager(NAME_SCENEMANAGER);
		if (pSceneManager != NULL)
		{
			/*
			* 创建摄像机
			*/
			m_pCamera = pSceneManager->createCamera(NAME_CAMERA);
			
			// 设置位置
			m_pCamera->setPosition(vPos);
			// 设置观察点
			m_pCamera->lookAt(vLookAt);

			// 设置近截面和远截面
			m_pCamera->setNearClipDistance(1);
			m_pCamera->setFarClipDistance(3000);
			
			// 设置角度
			//m_pCamera->yaw(Degree(fYaw));
			//m_pCamera->pitch(Degree(fPitch));

			setMode(CS_FREELOOK);
		}

		setTypeName(EDIT_CAMERA);
	}

	/**
	 *
	 * \param void 
	 * \return 
	 */
	CameraEditor::~CameraEditor(void)
	{
		SceneManager* pSceneManager = m_pCamera->getSceneManager();
		if (pSceneManager)
			pSceneManager->destroyCamera(m_pCamera);
	}
	
	/**
	 *
	 * \return 
	 */
	Camera*		CameraEditor::getCamera() const
	{
		return m_pCamera;
	}

	/**
	 *
	 * \param pCamera 
	 */
	void		CameraEditor::setCamera(Camera* pCamera)
	{
		m_pCamera = pCamera;
	}

	/**
	 *
	 * \param pTarget 
	 */
	void		CameraEditor::setTarget(SceneNode* pTarget)
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
	SceneNode*	CameraEditor::getTarget() const
	{
		return m_pTarget;
	}

	/**
	 *
	 * \param nMode 
	 */
	void		CameraEditor::setMode(int nMode)
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
	int			CameraEditor::getMode() const
	{
		return m_nMode;
	}

	/**
	 *
	 * \param x 
	 * \param y 
	 * \param z 
	 */
	void		CameraEditor::injectMouseMove(float x, float y)
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
	void		CameraEditor::injectMouseWheel(float z)
	{
		m_pCamera->moveRelative(Ogre::Vector3(0, 0, z * 0.01f));
	}

	/**
	 *
	 * \param key 
	 */
	void		CameraEditor::injectKeyDown(int key)
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
	void		CameraEditor::setYawPitchDist(Radian yaw, Radian pitch, Real dist)
	{
		m_pCamera->setPosition(m_pTarget->_getDerivedPosition());
		m_pCamera->setOrientation(m_pTarget->_getDerivedOrientation());
		m_pCamera->yaw(yaw);
		m_pCamera->pitch(-pitch);
		m_pCamera->moveRelative(Ogre::Vector3(0, 0, dist));
	}

	//////////////////////////////////////////////////////////////////////////
	//
	//////////////////////////////////////////////////////////////////////////
	/**
	 *
	 * \return 
	 */
	CameraEditorFactory::CameraEditorFactory()
	{
		setTypeName(FACTORY_CAMERA);
	}

	/**
	 *
	 * \return 
	 */
	CameraEditorFactory::~CameraEditorFactory()
	{

	}
	
	/**
	 *
	 * \param pm 
	 * \return 
	 */
	BaseEditor*		CameraEditorFactory::create(const SBaseCreateParam* pm)
	{
		if (pm != NULL)
		{
			SCameraCreateParam* cm = (SCameraCreateParam*)(pm);

			/*
			* 创建摄像机编辑器
			*/
			BaseEditor*	editor = new CameraEditor(cm->vPos,
				cm->vLookAt, cm->fYaw, cm->fPitch, cm->fNearClipDistance, cm->fFarClipDistance);

			return editor;
		}

		return NULL;
	}
}
