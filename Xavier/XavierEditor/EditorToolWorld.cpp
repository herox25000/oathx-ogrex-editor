#include "stdafx.h"
#include "EditorTool.h"
#include "EditorToolWorld.h"

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

	static const String EditorToolWorldPropertyName[] = 
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

	static const String EditorToolWorldPropertyDesc[] = 
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

	/**
	 *
	 * \param name 
	 * \return 
	 */
	static int	convertWorldPorpertyType(const String& name)
	{
		for (int i=0; i<EWP_COUNT; i++)
		{
			if (EditorToolWorldPropertyName[i] == name)
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
	EditorToolWorld::EditorToolWorld(const String& name, const String& worldName, const SceneTypeMask& typeMask, const ColourValue& clrAmbientLight,
		const Vector3& vPos, const Vector3& vLookAt, Real fYaw, Real fPitch, Real fNearClipDistance, Real fFarClipDistance, const ColourValue& background)
		: EditorTool(name), m_pWorld(NULL), m_bRMouseDown(false)
	{
		m_pWorld = new World(worldName, typeMask, clrAmbientLight, 
			vPos, vLookAt, fYaw, fPitch, fNearClipDistance, fFarClipDistance,
			background);
		if (m_pWorld)
		{
			addProperty(EditorToolWorldPropertyName[EWP_WORLD_NAME], Any(worldName), PVT_STRING,0, 
				EditorToolWorldPropertyDesc[EWP_WORLD_NAME]);
			addProperty(EditorToolWorldPropertyName[EWP_BACKGROUND], Any(background),PVT_COLOUR, true, 
				EditorToolWorldPropertyDesc[EWP_WORLD_NAME]);
			addProperty(EditorToolWorldPropertyName[EWP_SCENETYPE], Any(typeMask),PVT_UNSIGNED_SHORT, 0, 
				EditorToolWorldPropertyDesc[EWP_SCENETYPE]);
			addProperty(EditorToolWorldPropertyName[EWP_CLRAMBIENTLIGHT], Any(clrAmbientLight), PVT_COLOUR, true, 
				EditorToolWorldPropertyDesc[EWP_CLRAMBIENTLIGHT]);
			addProperty(EditorToolWorldPropertyName[EWP_CAMERA_POSITION], Any(vPos), PVT_VECTOR3, true, 
				EditorToolWorldPropertyDesc[EWP_CAMERA_POSITION]);
			addProperty(EditorToolWorldPropertyName[EWP_CAMERA_YAW], Any(fYaw), PVT_REAL, true, 
				EditorToolWorldPropertyDesc[EWP_CAMERA_YAW]);
			addProperty(EditorToolWorldPropertyName[EWP_CAMERA_PITCH], Any(fPitch), PVT_REAL, true, 
				EditorToolWorldPropertyDesc[EWP_CAMERA_PITCH]);
			addProperty(EditorToolWorldPropertyName[EWP_CAMERA_NEAR], Any(fNearClipDistance), PVT_REAL, true, 
				EditorToolWorldPropertyDesc[EWP_CAMERA_NEAR]);
			addProperty(EditorToolWorldPropertyName[EWP_CAMERA_FAR], Any(fFarClipDistance), PVT_REAL, true, 
				EditorToolWorldPropertyDesc[EWP_CAMERA_FAR]);
		}
	}

	/**
	 *
	 * \return 
	 */
	EditorToolWorld::~EditorToolWorld()
	{
		if (m_pWorld)
		{
			delete m_pWorld;
			m_pWorld = NULL;
		}
	}

	/**
	 *
	 * \param vPos 
	 * \return 
	 */
	bool	EditorToolWorld::OnRButtonDown(const Vector2& vPos)
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
	bool	EditorToolWorld::OnRButtonUp(const Vector2& vPos)
	{
		m_bRMouseDown = false;
		return 0;
	}

	/**
	 *
	 * \param vPos 
	 * \return 
	 */
	bool	EditorToolWorld::OnMouseMove(const Vector2& vPos)
	{
		Camera* pCamera = m_pWorld->getCamera();
		if (pCamera)
		{
			if (m_bRMouseDown)
			{
				Vector2 vRel = vPos - m_vRigthDwon;
				pCamera->yaw(Degree(vRel.x * 0.15f));
				pCamera->pitch(Degree(vRel.y * 0.15f));
			}
		}
		
		m_vRigthDwon = vPos;

		return true;
	}

	/**
	 *
	 * \param zDelta 
	 * \param vPos 
	 * \return 
	 */
	bool	EditorToolWorld::OnMouseWheel(float zDelta, const Vector2& vPos)
	{
		Camera* pCamera = m_pWorld->getCamera();
		if (pCamera)
			pCamera->moveRelative(Ogre::Vector3(0, 0, zDelta * 0.02f));

		return true;
	}

	/**
	 *
	 * \param nChar 
	 * \param nRepCnt 
	 * \param nFlags 
	 * \return 
	 */
	bool	EditorToolWorld::OnKeyDown(uint32 nChar, uint32 nRepCnt, uint32 nFlags)
	{
		Camera* pCamera = m_pWorld->getCamera();
		if (!pCamera)
			return 0;

		switch( nChar )
		{
		case 'W':
			{
				Ogre::Vector3 accel = Ogre::Vector3::ZERO;
				accel += pCamera->getDirection();
				pCamera->move(accel);
			}
			break;
		case 'S':
			{
				Ogre::Vector3 accel = Ogre::Vector3::ZERO;
				accel -= pCamera->getDirection();
				pCamera->move(accel);
			}
			break;
		case 'A':
			{
				Ogre::Vector3 accel = Ogre::Vector3::ZERO;
				accel -= pCamera->getRight();
				pCamera->move(accel);
			}
			break;
		case 'D':
			{
				Ogre::Vector3 accel = Ogre::Vector3::ZERO;
				accel += pCamera->getRight();
				pCamera->move(accel);
			}
			break;
		}
		return 0;
	}

	/**
	 *
	 * \param nChar 
	 * \param nRepCnt 
	 * \param nFlags 
	 * \return 
	 */
	bool	EditorToolWorld::OnKeyUp(uint32 nChar, uint32 nRepCnt, uint32 nFlags)
	{
		return 0;
	}

	/**
	 *
	 * \param cx 
	 * \param cy 
	 * \return 
	 */
	bool	EditorToolWorld::OnSize(int cx, int cy)
	{
		if (m_pWorld)
			m_pWorld->windowMovedOrResized();

		return true;
	}

	/**
	 *
	 * \param name 
	 * \param angValue 
	 * \param nValueType 
	 * \return 
	 */
	bool	EditorToolWorld::OnPropertyChanged(const String& parentName, const String& name, Any anyValue, int nValueType)
	{
		int nType = convertWorldPorpertyType(parentName.empty() ? name : parentName);
		if ( nType < 0)
		{
			LogManager::getSingleton().logMessage(LML_TRIVIAL, "Can't find property " + name);
			return 0;
		}

		switch( nType )
		{
		case EWP_BACKGROUND:
			{
				Viewport* pViewport = m_pWorld->getViewport();
				if (pViewport)
				{
					ColourValue background = pViewport->getBackgroundColour();

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

					pViewport->setBackgroundColour(background);
				}
			}
			break;
		case EWP_CLRAMBIENTLIGHT:
			{
				SceneManager* pSceneManager = m_pWorld->getSceneManager();
				if (pSceneManager)
				{
					ColourValue clrAmbientLight = pSceneManager->getAmbientLight();
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
					pSceneManager->setAmbientLight(clrAmbientLight);
				}
			}
			break;
		case EWP_CAMERA_POSITION:
			{
				Camera* pCamera = m_pWorld->getCamera();
				if (pCamera)
				{
					Vector3 vPos = pCamera->getPosition();
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
					pCamera->setPosition(vPos);
				}
			}
			break;
		case EWP_CAMERA_YAW:
			{
				Camera* pCamera = m_pWorld->getCamera();
				if (pCamera)
				{
					pCamera->yaw(Degree(any_cast<float>(anyValue)));
				}
			}
			break;
		case EWP_CAMERA_PITCH:
			{
				Camera* pCamera = m_pWorld->getCamera();
				if (pCamera)
				{
					pCamera->pitch(Degree(any_cast<float>(anyValue)));
				}
			}
			break;
		case EWP_CAMERA_NEAR:
			{
				Camera* pCamera = m_pWorld->getCamera();
				if (pCamera)
				{
					pCamera->setNearClipDistance(any_cast<float>(anyValue));
				}
			}
			break;
		case EWP_CAMERA_FAR:
			{
				Camera* pCamera = m_pWorld->getCamera();
				if (pCamera)
				{
					pCamera->setFarClipDistance(any_cast<float>(anyValue));	
				}
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
	EditorToolWorldFactory::EditorToolWorldFactory(const String& name)
		: EditorToolFactory(name)
	{

	}

	/**
	 *
	 * \return 
	 */
	EditorToolWorldFactory::~EditorToolWorldFactory()
	{
		
	}

	/**
	 *
	 * \param seadp 
	 * \return 
	 */
	EditorTool*	EditorToolWorldFactory::createEditorTool(const SEditorAdp& seadp)
	{
		const SEditorWorldAdp& adp = static_cast<const SEditorWorldAdp&>(seadp);

		return new EditorToolWorld(adp.name, adp.worldName, adp.typeMask, adp.clrAmbientLight,
			adp.vPos, adp.vLookAt, adp.fYaw, adp.fPitch, adp.fNearClipDistance, adp.fFarClipDistance,
			adp.background);
	}
}