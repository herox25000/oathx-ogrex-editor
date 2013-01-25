#include "stdafx.h"
#include "EditorPlugin.h"
#include "EditorSceneManager.h"
#include "EditorPluginManager.h"
#include "EditorCamera.h"

namespace Ogre
{
	//////////////////////////////////////////////////////////////////////////
	enum {
		CAMERA_PLUGIN_NAME,
		CAMERA_POS,
		CAMERA_Q,
		CAMERA_NEAR,
		CAMERA_FAR,
		CAMERA_FOV,
		CAMERA_AUTOASPECTRATIO,
		CAMERA_POLYGONMODE,

		CAMERA_COUNT,
	};

	// 属性名
	static const String cameraName[] = {
		"Name",
		"Position",
		"Quaternion",
		"NearClipDistance",
		"FarClipDistance",
		"Fov",
		"AutoAspectRatio",
		"PolygonMode",
	};

	// 属性描述
	static const String cameraDesc[] = {
		"Name",
		"Position",
		"Quaternion",
		"NearClipDistance",
		"FarClipDistance",
		"Fov",
		"AutoAspectRatio",
		"PolygonMode",
	};

		/**
	 *
	 * \param name 
	 * \return 
	 */
	static int	convertCameraPropertyType(const String& name)
	{
		for (int i=0; i<CAMERA_COUNT; i++)
		{
			if (cameraName[i] == name)
				return i;
		}

		return -1;
	}

	//////////////////////////////////////////////////////////////////////////

	/**
	 *
	 * \param pluginName 
	 * \param vPos 
	 * \param q 
	 * \param fNearClipDistance 
	 * \param fFarClipDistance 
	 * \param fFov 
	 * \param AutoAspectRatio 
	 * \param nQueryFlags 
	 * \return 
	 */
	EditorCamera::EditorCamera(const String& pluginName, const Vector3& vPos, const Quaternion& q, float fNearClipDistance,
		float fFarClipDistance, float fFov, bool bAutoAspectRatio,
		uint32 nQueryFlags) : EditorPlugin(pluginName), m_pCamera(NULL), m_bRMouseDown(0)
	{
		if (configure(pluginName, vPos, q, fNearClipDistance, fFarClipDistance, fFov, bAutoAspectRatio, nQueryFlags))
		{
			addProperty(cameraName[CAMERA_PLUGIN_NAME],
				Any(pluginName), PVT_STRING, true, cameraDesc[CAMERA_PLUGIN_NAME]);
			addProperty(cameraName[CAMERA_POS],
				Any(vPos), PVT_VECTOR3, true, cameraDesc[CAMERA_POS]);
			addProperty(cameraName[CAMERA_Q],
				Any(q), PVT_QUATERNION, true, cameraDesc[CAMERA_Q]);
			addProperty(cameraName[CAMERA_NEAR], 
				Any(fNearClipDistance), PVT_REAL, true, cameraDesc[CAMERA_NEAR]);
			addProperty(cameraName[CAMERA_FAR], 
				Any(fFarClipDistance), PVT_REAL, true, cameraDesc[CAMERA_FAR]);
			addProperty(cameraName[CAMERA_FOV], 
				Any(fFov), PVT_REAL, true, cameraDesc[CAMERA_FOV]);
			addProperty(cameraName[CAMERA_AUTOASPECTRATIO], 
				Any(bAutoAspectRatio), PVT_BOOL, true, cameraDesc[CAMERA_AUTOASPECTRATIO]);
			addProperty(cameraName[CAMERA_POLYGONMODE], 
				Any(PM_SOLID), PVT_POLYGONMODE, true, cameraDesc[CAMERA_POLYGONMODE]);
		}
	}

	/**
	 *
	 * \return 
	 */
	EditorCamera::~EditorCamera()
	{

	}

	/**
	 *
	 * \param vPos 
	 * \param q 
	 * \param fNearClipDistance 
	 * \param fFarClipDistance 
	 * \param fFov 
	 * \param bAutoAspectRatio 
	 * \param nQueryFlags 
	 */
	bool		EditorCamera::configure(const String& name, const Vector3& vPos, const Quaternion& q, float fNearClipDistance, 
		float fFarClipDistance, float fFov, bool bAutoAspectRatio, uint32 nQueryFlags)
	{
		// 获取场景插件
		EditorSceneManager* pSceneManagerPlugin = static_cast<EditorSceneManager*>(
			EditorPluginManager::getSingletonPtr()->findPlugin(EDITOR_SCENEPLUGIN_NAME)
			);
		if (!pSceneManagerPlugin)
		{
			LogManager::getSingleton().logMessage(LML_TRIVIAL,
				"Can't find plugin + " + EDITOR_SCENEPLUGIN_NAME);
			return 0;
		}
		
		// 创建摄像机
		m_pCamera = pSceneManagerPlugin->getSceneManager()->createCamera(name);
		if (m_pCamera)
		{
			m_pCamera->setPosition(vPos);
			m_pCamera->setOrientation(q);
			m_pCamera->setNearClipDistance(fNearClipDistance);
			m_pCamera->setFarClipDistance(fFarClipDistance);
			m_pCamera->setFOVy(Radian(fFov));
			m_pCamera->setAutoAspectRatio(bAutoAspectRatio);
			m_pCamera->setQueryFlags(0);

			return true;
		}
		else
		{
			LogManager::getSingleton().logMessage(LML_TRIVIAL,
				"Can't create ogre camera + " + name);
		}
		
		return 0;
	}

	/**
	 *
	 * \return 
	 */
	Camera*			EditorCamera::getCamera() const
	{
		return m_pCamera;
	}

	/**
	 *
	 * \param vPos 
	 * \return 
	 */
	bool			EditorCamera::OnRButtonDown(const Vector2& vPos)
	{
		m_bRMouseDown	= true;
		m_vRigthDwon	= vPos;

		return true;
	}

	/**
	 *
	 * \param vPos 
	 * \return 
	 */
	bool			EditorCamera::OnRButtonUp(const Vector2& vPos)
	{
		m_bRMouseDown	= 0;
		m_vRigthDwon	= vPos;
		
		return 0;
	}

	/**
	 *
	 * \param vPos 
	 * \return 
	 */
	bool			EditorCamera::OnMouseMove(const Vector2& vPos)
	{
		if (m_pCamera == NULL)
			return 0;
		
		if (m_bRMouseDown)
		{
			Vector2 vRel = vPos - m_vRigthDwon;
			m_pCamera->yaw(Degree(vRel.x * 0.15f));
			m_pCamera->pitch(Degree(vRel.y * 0.15f));
		}
		
		m_vRigthDwon = vPos;

		return true;
	}

	/**
	 *
	 * \param fzDelta 
	 * \param vPos 
	 * \return 
	 */
	bool			EditorCamera::OnMouseWheel(float fzDelta, const Vector2& vPos)
	{
		if (m_pCamera)
			m_pCamera->moveRelative(Ogre::Vector3(0, 0, fzDelta * 2 * 0.02f));

		return true;
	}

	//////////////////////////////////////////////////////////////////////////
	/**
	 *
	 * \param factoryName 
	 * \return 
	 */
	EditorCameraFactory::EditorCameraFactory(const String& factoryName)
		: EditorPluginFactory(factoryName)
	{

	}

	/**
	 *
	 * \return 
	 */
	EditorCameraFactory::~EditorCameraFactory()
	{

	}

	/**
	 *
	 * \param ssadp 
	 * \param pParent 
	 * \return 
	 */
	EditorPlugin*	EditorCameraFactory::createPlugin(const SEditorPluginAdp& ssadp, EditorPlugin* pParent)
	{
		const SEditorCamearAdp& adp = static_cast<const SEditorCamearAdp&>(ssadp);

		EditorCamera* pCameraPlugin = new EditorCamera(adp.pluginName, adp.vPos, adp.q, 
			adp.fNearClipDistance, adp.fFarClipDistance, adp.fFov, adp.bAutoAspectRatio, adp.nQueryFlags);
		if (pCameraPlugin)
		{
			// 设置删除优先级
			pCameraPlugin->setPriority(PRIORITY_LOW);

			LogManager::getSingleton().logMessage(LML_NORMAL, 
				"Create editor plugin : " + adp.pluginName);

			if (pParent)
				pParent->registerPlugin(pCameraPlugin);

			return pCameraPlugin;
		}

		return NULL;
	}
}