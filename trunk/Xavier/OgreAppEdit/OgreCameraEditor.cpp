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
		Real fPitch, Real fNearClipDistance, Real fFarClipDistance) : m_pCamera(NULL)
	{
		SceneManager* pSceneManager = Root::getSingletonPtr()->getSceneManager(NAME_SCENEMANAGER);
		if (pSceneManager != NULL)
		{
			/*
			* ���������
			*/
			m_pCamera = pSceneManager->createCamera(NAME_CAMERA);
			
			// ����λ��
			m_pCamera->setPosition(vPos);
			// ���ù۲��
			m_pCamera->lookAt(vLookAt);

			// ���ý������Զ����
			m_pCamera->setNearClipDistance(fNearClipDistance);
			m_pCamera->setFarClipDistance(fFarClipDistance);
			
			// ���ýǶ�
			m_pCamera->yaw(Degree(fYaw));
			m_pCamera->pitch(Degree(fPitch));
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
	}
	
	/**
	 *
	 * \return 
	 */
	Camera*		CameraEditor::getCamera() const
	{
		return m_pCamera;
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
			* ����������༭��
			*/
			BaseEditor*	editor = new CameraEditor(cm->vPos,
				cm->vLookAt, cm->fYaw, cm->fPitch, cm->fNearClipDistance, cm->fFarClipDistance);

			return editor;
		}

		return NULL;
	}
}
