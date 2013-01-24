#include "stdafx.h"
#include "EditorTool.h"
#include "EditorToolSceneManager.h"
#include "EditorSystem.h"

namespace Ogre
{
	//////////////////////////////////////////////////////////////////////////
	enum {
		EWP_WORLD_NAME,
		EWP_BACKGROUND,
		EWP_SCENETYPE,
		EWP_CLRAMBIENTLIGHT,
		EWP_CAMERA_POSITION,
		EWP_CAMERA_YAW,
		EWP_CAMERA_PITCH,
		EWP_CAMERA_NEAR,
		EWP_CAMERA_FAR,
		EWP_COUNT,
	};

	static const String EditorToolSceneManagerPropertyName[] = 
	{
		"WorldName",
		"Background",
		"SceneType",
		"AmbientLight",
		"CameraPosition",
		"Yaw",
		"Pitch",
		"NearClipDistance",
		"FarClipDistance"
	};

	static const String EditorToolSceneManagerPropertyDesc[] = 
	{
		"修改世界节点名",
		"修改视口背景颜色",
		"场景管理器类型",
		"环境光",
		"摄像机位置",
		"摄像机观察点",
		"Yaw",
		"Pitch",
		"NearClipDistance",
		"FarClipDistance"

	};

	// 默认摄像机名称
	const String	EditorToolSceneManager::DEFAULT_MAIN_CAMERA = ("MainWMC");

	/**
	 *
	 * \param name 
	 * \return 
	 */
	static int	convertSceneManagerPorpertyType(const String& name)
	{
		for (int i=0; i<EWP_COUNT; i++)
		{
			if (EditorToolSceneManagerPropertyName[i] == name)
				return i;
		}

		return -1;
	}
	//////////////////////////////////////////////////////////////////////////

	/**
	 *
	 * \param name 
	 * \return 
	 */
	EditorToolSceneManager::EditorToolSceneManager(const String& name, const String& worldName, const SceneTypeMask& typeMask, const ColourValue& clrAmbientLight,
		const Vector3& vPos, const Vector3& vLookAt, Real fYaw, Real fPitch, Real fNearClipDistance, Real fFarClipDistance, const ColourValue& background)
		: EditorTool(name),  m_bRMouseDown(false)
	{
		// 创建场景管理器
		m_pSceneManager = Root::getSingleton().createSceneManager(typeMask, name);
		if (m_pSceneManager)
		{
			// 设置环境光
			m_pSceneManager->setAmbientLight(clrAmbientLight);

			// 默认配置
			configureDefault(vPos, vLookAt, fYaw, fPitch, fNearClipDistance, fFarClipDistance, background);
		}

		addProperty(EditorToolSceneManagerPropertyName[EWP_WORLD_NAME], Any(worldName), PVT_STRING,0, 
			EditorToolSceneManagerPropertyDesc[EWP_WORLD_NAME]);
		addProperty(EditorToolSceneManagerPropertyName[EWP_BACKGROUND], Any(background),PVT_COLOUR, true, 
			EditorToolSceneManagerPropertyDesc[EWP_WORLD_NAME]);
		addProperty(EditorToolSceneManagerPropertyName[EWP_SCENETYPE], Any(typeMask),PVT_UNSIGNED_SHORT, 0, 
			EditorToolSceneManagerPropertyDesc[EWP_SCENETYPE]);
		addProperty(EditorToolSceneManagerPropertyName[EWP_CLRAMBIENTLIGHT], Any(clrAmbientLight), PVT_COLOUR, true, 
			EditorToolSceneManagerPropertyDesc[EWP_CLRAMBIENTLIGHT]);
		addProperty(EditorToolSceneManagerPropertyName[EWP_CAMERA_POSITION], Any(vPos), PVT_VECTOR3, true, 
			EditorToolSceneManagerPropertyDesc[EWP_CAMERA_POSITION]);
		addProperty(EditorToolSceneManagerPropertyName[EWP_CAMERA_YAW], Any(fYaw), PVT_REAL, true, 
			EditorToolSceneManagerPropertyDesc[EWP_CAMERA_YAW]);
		addProperty(EditorToolSceneManagerPropertyName[EWP_CAMERA_PITCH], Any(fPitch), PVT_REAL, true, 
			EditorToolSceneManagerPropertyDesc[EWP_CAMERA_PITCH]);
		addProperty(EditorToolSceneManagerPropertyName[EWP_CAMERA_NEAR], Any(fNearClipDistance), PVT_REAL, true, 
			EditorToolSceneManagerPropertyDesc[EWP_CAMERA_NEAR]);
		addProperty(EditorToolSceneManagerPropertyName[EWP_CAMERA_FAR], Any(fFarClipDistance), PVT_REAL, true, 
			EditorToolSceneManagerPropertyDesc[EWP_CAMERA_FAR]);
		
	}

	/**
	 *
	 * \return 
	 */
	EditorToolSceneManager::~EditorToolSceneManager()
	{
		// 移除视口
		EditorSystem::getSingleton().getRenderWindow()->removeViewport(
			m_pViewport->getZOrder()
			);

		// 销毁摄像机
		if (m_pCamera)
		{
			m_pCamera->getSceneManager()->destroyCamera(m_pCamera);
		}

		// 销毁场景
		Root::getSingletonPtr()->destroySceneManager(m_pSceneManager);
	}

	/**
	 *
	 * \return 
	 */
	SceneManager*	EditorToolSceneManager::getSceneManager() const
	{
		return m_pSceneManager;
	}

	/**
	 *
	 * \return 
	 */
	Camera*			EditorToolSceneManager::getCamera() const
	{
		return m_pCamera;
	}

	/**
	 *
	 * \return 
	 */
	Viewport*		EditorToolSceneManager::getViewport() const
	{
		return m_pViewport;
	}

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
	bool			EditorToolSceneManager::configureDefault(const Vector3& vPos, const Vector3& vLookAt, 
		Real fYaw, Real fPitch, Real fNearClipDistance, Real fFarClipDistance, const ColourValue& background)
	{
		if (m_pSceneManager == NULL)
			return 0;

		m_pCamera = m_pSceneManager->createCamera(DEFAULT_MAIN_CAMERA);
		m_pCamera->setPosition(vPos);
		m_pCamera->lookAt(vLookAt);

		m_pCamera->setNearClipDistance(fNearClipDistance);
		m_pCamera->setFarClipDistance(fFarClipDistance);

		m_pCamera->yaw(Degree(fYaw));
		m_pCamera->pitch(Degree(fPitch));
		
		/*
		* 添加视口
		*/
		RenderWindow* pRenderWindow = EditorSystem::getSingletonPtr()->getRenderWindow();
		if (pRenderWindow)
		{
			m_pViewport = pRenderWindow->addViewport(m_pCamera);
			if (m_pViewport)
			{
				m_pViewport->setBackgroundColour(background);

				pRenderWindow->windowMovedOrResized();
				m_pCamera->setAspectRatio(
					Ogre::Real(m_pViewport->getActualWidth()) / Ogre::Real(m_pViewport->getActualHeight())
					);			
			}
		}

		return true;
	}

	/**
	 *
	 */
	void			EditorToolSceneManager::windowMovedOrResized()
	{
		RenderWindow* pRenderWindow = EditorSystem::getSingleton().getRenderWindow();
		if (m_pCamera != NULL && pRenderWindow != NULL)
		{
			pRenderWindow->windowMovedOrResized();

			m_pCamera->setAspectRatio(
				Ogre::Real(m_pViewport->getActualWidth()) / Ogre::Real(m_pViewport->getActualHeight())
				);	
		}
	}

	/**
	 *
	 * \param vPos 
	 * \return 
	 */
	bool			EditorToolSceneManager::OnRButtonDown(const Vector2& vPos)
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
	bool			EditorToolSceneManager::OnRButtonUp(const Vector2& vPos)
	{
		m_bRMouseDown = false;
		return 0;
	}

	/**
	 *
	 * \param vPos 
	 * \return 
	 */
	bool			EditorToolSceneManager::OnMouseMove(const Vector2& vPos)
	{
		return true;
	}

	/**
	 *
	 * \param zDelta 
	 * \param vPos 
	 * \return 
	 */
	bool			EditorToolSceneManager::OnMouseWheel(float zDelta, const Vector2& vPos)
	{
		if (m_pCamera)
			m_pCamera->moveRelative(Ogre::Vector3(0, 0, zDelta * 0.02f));

		return true;
	}

	/**
	 *
	 * \param nChar 
	 * \param nRepCnt 
	 * \param nFlags 
	 * \return 
	 */
	bool			EditorToolSceneManager::OnKeyDown(uint32 nChar, uint32 nRepCnt, uint32 nFlags)
	{
		return 0;
	}

	/**
	 *
	 * \param nChar 
	 * \param nRepCnt 
	 * \param nFlags 
	 * \return 
	 */
	bool			EditorToolSceneManager::OnKeyUp(uint32 nChar, uint32 nRepCnt, uint32 nFlags)
	{
		return 0;
	}

	/**
	 *
	 * \param cx 
	 * \param cy 
	 * \return 
	 */
	bool			EditorToolSceneManager::OnSize(int cx, int cy)
	{
		return true;
	}

	/**
	 *
	 * \param name 
	 * \param angValue 
	 * \param nValueType 
	 * \return 
	 */
	bool			EditorToolSceneManager::OnPropertyChanged(const String& parentName, const String& name, Any anyValue, int nValueType)
	{
		int nType = convertSceneManagerPorpertyType(parentName.empty() ? name : parentName);
		if ( nType < 0)
		{
			LogManager::getSingleton().logMessage(LML_TRIVIAL, "Can't find property " + name);
			return 0;
		}

		switch( nType )
		{
		case EWP_BACKGROUND:
			{
				ColourValue background = m_pViewport->getBackgroundColour();

				int nNormal = convertNormalPropertyType(name);
				switch( nNormal )
				{
				case NORMAL_RGB:
					{
						uint32 rgb = any_cast<uint32>(anyValue);
						int a = GetR(rgb);
						int b = GetG(rgb);
						int c = GetB(rgb);

						background.r = NormalValue(GetR(rgb));
						background.g = NormalValue(GetG(rgb));
						background.b = NormalValue(GetB(rgb));
					}
					break;
				case NORMAL_ALHPA:
					{
						background.a = any_cast<float>(anyValue);
					}
					break;
				}

				m_pViewport->setBackgroundColour(background);
				
			}
			break;
		case EWP_CLRAMBIENTLIGHT:
			{
				ColourValue clrAmbientLight = m_pSceneManager->getAmbientLight();
				int nNormal = convertNormalPropertyType(name);
				switch( nNormal )
				{
				case NORMAL_RGB:
					{
						uint32 rgb = any_cast<uint32>(anyValue);
						int a = GetR(rgb);
						int b = GetG(rgb);
						int c = GetB(rgb);

						clrAmbientLight.r = NormalValue(GetR(rgb));
						clrAmbientLight.g = NormalValue(GetG(rgb));
						clrAmbientLight.b = NormalValue(GetB(rgb));
					}
					break;
				case NORMAL_ALHPA:
					{
						clrAmbientLight.a = any_cast<float>(anyValue);
					}
					break;
				}

				m_pSceneManager->setAmbientLight(clrAmbientLight);
			}
			break;
		case EWP_CAMERA_POSITION:
			{
				Vector3 vPos = m_pCamera->getPosition();
				float fValue = any_cast<float>(anyValue);
				switch( convertNormalPropertyType(name) )
				{
				case NORMAL_X:
					vPos.x = fValue;
					break;
				case NORMAL_Y:
					vPos.y = fValue;
					break;
				case NORMAL_Z:
					vPos.z = fValue;
					break;
				}
				m_pCamera->setPosition(vPos);
			}
			break;
		case EWP_CAMERA_YAW:
			{
				m_pCamera->yaw(Degree(any_cast<float>(anyValue)));
			}
			break;
		case EWP_CAMERA_PITCH:
			{
				m_pCamera->pitch(Degree(any_cast<float>(anyValue)));
			}
			break;
		case EWP_CAMERA_NEAR:
			{
				m_pCamera->setNearClipDistance(any_cast<float>(anyValue));
			}
			break;
		case EWP_CAMERA_FAR:
			{
				m_pCamera->setFarClipDistance(any_cast<float>(anyValue));	
			}
			break;
		}
		
		return true;
	}

	//////////////////////////////////////////////////////////////////////////
	/**
	 *
	 * \param name 
	 * \return 
	 */
	EditorToolSceneManagerFactory::EditorToolSceneManagerFactory(const String& name)
		: EditorToolFactory(name)
	{

	}

	/**
	 *
	 * \return 
	 */
	EditorToolSceneManagerFactory::~EditorToolSceneManagerFactory()
	{
		
	}

	/**
	 *
	 * \param seadp 
	 * \return 
	 */
	EditorTool*	EditorToolSceneManagerFactory::createEditorTool(const SEditorAdp& seadp)
	{
		const SEditorSceneManagerAdp& adp = static_cast<const SEditorSceneManagerAdp&>(seadp);

		return new EditorToolSceneManager(adp.name, adp.worldName, adp.typeMask, adp.clrAmbientLight,
			adp.vPos, adp.vLookAt, adp.fYaw, adp.fPitch, adp.fNearClipDistance, adp.fFarClipDistance,
			adp.background);
	}
}