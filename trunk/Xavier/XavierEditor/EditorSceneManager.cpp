#include "stdafx.h"
#include "EditorSceneManager.h"

namespace Ogre
{
	enum {
		ESMP_PLUGIN_NAME,
		ESMP_SCENETYPEMASK,
		ESMP_AMBIENTLIGHT,
		ESMP_FOGMODE,
		ESMP_FOGCOLOUR,
		ESMP_EXPDENSITY,
		ESMP_LINEARSTART,
		ESMP_LINEAREND,

		ESMP_COUNT,
	};

	// 属性名
	static const String esmpName[] = {
		"Name",
		"SceneTypeMask",
		"AmbientLight",
		"FogMode",
		"FogColour",
		"ExpDensity",
		"LinearStart",
		"LinearEnd",
	};
	
	// 属性描述
	static const String esmpDesc[] = {
		"Name",
		"SceneTypeMask",
		"AmbientLight",
		"FogMode",
		"FogColour",
		"ExpDensity",
		"LinearStart",
		"LinearEnd",
	};

	/**
	 *
	 * \param name 
	 * \return 
	 */
	static int	convertSceneManagerPropertyType(const String& name)
	{
		for (int i=0; i<ESMP_COUNT; i++)
		{
			if (esmpName[i] == name)
				return i;
		}

		return -1;
	}
	/**
	 *
	 * \param pluginName 
	 * \param typeMask 
	 * \return 
	 */
	EditorSceneManager::EditorSceneManager(const String& pluginName, const SceneTypeMask& typeMask, 
		const ColourValue& clrAmbientLight, FogMode fogMode, const ColourValue& clrFog, float expDensity, float linearStart, float linearEnd)
		: EditorPlugin(pluginName), m_pSceneManager(NULL), m_pRayQuery(NULL)
	{
		if (configure(pluginName, typeMask, clrAmbientLight, fogMode, clrFog, expDensity, linearStart, linearEnd))
		{
			addProperty(esmpName[ESMP_PLUGIN_NAME],
				Any(pluginName), PVT_STRING, 0, esmpDesc[ESMP_PLUGIN_NAME]);
			addProperty(esmpName[ESMP_AMBIENTLIGHT],
				Any(clrAmbientLight), PVT_COLOUR, true, esmpDesc[ESMP_AMBIENTLIGHT]);
			addProperty(esmpName[ESMP_SCENETYPEMASK],
				Any(typeMask), PVT_USHORT, 0, esmpDesc[ESMP_SCENETYPEMASK]);
			addProperty(esmpName[ESMP_FOGMODE], 
				Any(fogMode), PVT_FOGMODE, true, esmpDesc[ESMP_FOGMODE]);
			addProperty(esmpName[ESMP_FOGCOLOUR], 
				Any(clrFog), PVT_COLOUR, true, esmpDesc[ESMP_FOGCOLOUR]);
			addProperty(esmpName[ESMP_EXPDENSITY], 
				Any(expDensity), PVT_REAL, true, esmpDesc[ESMP_EXPDENSITY]);
			addProperty(esmpName[ESMP_LINEARSTART], 
				Any(linearStart), PVT_REAL, true, esmpDesc[ESMP_LINEARSTART]);
			addProperty(esmpName[ESMP_LINEAREND], 
				Any(linearEnd), PVT_REAL, true, esmpDesc[ESMP_LINEAREND]);
		}
	}

	/**
	 *
	 * \return 
	 */
	EditorSceneManager::~EditorSceneManager()
	{
		destroyAllPlugin();

		if (m_pSceneManager)
		{
			if (m_pGrizemo)
			{
				delete m_pGrizemo;
				m_pGrizemo = NULL;
			}

			if (m_pRayQuery != NULL)
				m_pSceneManager->destroyQuery(m_pRayQuery);
		
			Root::getSingletonPtr()->destroySceneManager(m_pSceneManager);
		}
	}

	/**
	 *
	 * \param fogMode 
	 * \param clrFog 
	 * \param expDensity 
	 * \param linearStart 
	 * \param linearEnd 
	 */
	bool			EditorSceneManager::configure(const String& pluginName, const SceneTypeMask& typeMask, const ColourValue& clrAmbientLight,
		FogMode fogMode, const ColourValue& clrFog, float expDensity, float linearStart, float linearEnd)
	{
		m_pSceneManager = Root::getSingletonPtr()->createSceneManager(typeMask, pluginName);
		if (m_pSceneManager)
		{
			m_pRayQuery = m_pSceneManager->createRayQuery(Ogre::Ray());
			if (m_pRayQuery == NULL)
			{
				TKLogEvent("Can't create ogre scene query : " + pluginName,
					LML_CRITICAL);
			}

			// 设置漫反射
			m_pSceneManager->setAmbientLight(clrAmbientLight);

			// 设置雾
			m_pSceneManager->setFog(fogMode, clrFog, 
				expDensity, linearStart, linearEnd);
			

			m_pGrizemo = new Grizmo(m_pSceneManager,
				"axes.mesh", Vector3::ZERO, Vector3(80, 80, 80));
			return true;
		}
		else
		{
			TKLogEvent("Can't create ogre scene manager : " + pluginName,
				LML_CRITICAL);
		}

		return 0;
	}

	/**
	 *
	 * \return 
	 */
	SceneManager*	EditorSceneManager::getSceneManager() const
	{
		return m_pSceneManager;
	}

	/**
	 *
	 * \return 
	 */
	RaySceneQuery*	EditorSceneManager::getRaySceneQuery() const
	{
		return m_pRayQuery;
	}

	/**
	 *
	 * \param parentName 
	 * \param name 
	 * \param anyValue 
	 * \param nType 
	 * \return 
	 */
	bool			EditorSceneManager::OnPropertyChanged(const String& parentName, const String& name,
		const Any& anyValue, int nType)
	{
		int nPropertyType = convertSceneManagerPropertyType(parentName.empty() ? name : parentName);
		if (nPropertyType >= 0)
		{
			switch( nPropertyType )
			{
			case ESMP_AMBIENTLIGHT:
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

					setPropertyValue<ColourValue>(parentName.empty() ? name : parentName, 
						clrAmbientLight);
					m_pSceneManager->setAmbientLight(clrAmbientLight);
				}
				break;
			case ESMP_FOGMODE:
				{
					String	val		= any_cast<String>(anyValue);
					FogMode mode	= (FogMode)(convertFogModePropertyType(val));
					setPropertyValue<FogMode>(parentName.empty() ? name : parentName,
						mode);

					ColourValue clrFog;
					getPropertyValue<ColourValue>(esmpName[ESMP_FOGCOLOUR], 
						clrFog);

					float		fExpDensity;
					getPropertyValue<float>(esmpName[ESMP_EXPDENSITY], 
						fExpDensity);

					float		fLinearStart;
					getPropertyValue<float>(esmpName[ESMP_LINEARSTART], 
						fLinearStart);

					float		fLinearEnd;
					getPropertyValue<float>(esmpName[ESMP_LINEAREND], 
						fLinearEnd);

					m_pSceneManager->setFog(mode, clrFog, fExpDensity, fLinearStart, fLinearEnd);
				}
				break;
			case ESMP_FOGCOLOUR:
				{
					ColourValue clrFog = m_pSceneManager->getFogColour();

					int nNormal = convertNormalPropertyType(name);
					switch( nNormal )
					{
					case NORMAL_RGB:
						{
							uint32 rgb = any_cast<uint32>(anyValue);
							int a = GetR(rgb);
							int b = GetG(rgb);
							int c = GetB(rgb);

							clrFog.r = NormalValue(GetR(rgb));
							clrFog.g = NormalValue(GetG(rgb));
							clrFog.b = NormalValue(GetB(rgb));
						}
						break;
					case NORMAL_ALHPA:
						{
							clrFog.a = any_cast<float>(anyValue);
						}
						break;
					}
					setPropertyValue<ColourValue>(parentName.empty() ? name : parentName,
						clrFog);

					FogMode		mode;
					getPropertyValue<FogMode>(esmpName[ESMP_FOGMODE], mode);

					float		fExpDensity;
					getPropertyValue<float>(esmpName[ESMP_EXPDENSITY], 
						fExpDensity);

					float		fLinearStart;
					getPropertyValue<float>(esmpName[ESMP_LINEARSTART], 
						fLinearStart);

					float		fLinearEnd;
					getPropertyValue<float>(esmpName[ESMP_LINEAREND], 
						fLinearEnd);

					m_pSceneManager->setFog(mode, clrFog, fExpDensity, fLinearStart, fLinearEnd);

				}
				break;
			case ESMP_EXPDENSITY:
				{
					float fExpDensity = any_cast<float>(anyValue);
					setPropertyValue<float>(parentName.empty() ? name : parentName,
						fExpDensity);

					FogMode		mode;
					getPropertyValue<FogMode>(esmpName[ESMP_FOGMODE], mode);

					ColourValue clrFog;
					getPropertyValue<ColourValue>(esmpName[ESMP_FOGCOLOUR], 
						clrFog);

					float		fLinearStart;
					getPropertyValue<float>(esmpName[ESMP_LINEARSTART], 
						fLinearStart);

					float		fLinearEnd;
					getPropertyValue<float>(esmpName[ESMP_LINEAREND], 
						fLinearEnd);

					m_pSceneManager->setFog(mode, clrFog, fExpDensity, fLinearStart, fLinearEnd);

				}
				break;
			case ESMP_LINEARSTART:
				{
					float fLinearStart = any_cast<float>(anyValue);
					setPropertyValue<float>(parentName.empty() ? name : parentName,
						fLinearStart);

					FogMode		mode;
					getPropertyValue<FogMode>(esmpName[ESMP_FOGMODE], mode);

					ColourValue clrFog;
					getPropertyValue<ColourValue>(esmpName[ESMP_FOGCOLOUR], 
						clrFog);

					float		fExpDensity;
					getPropertyValue<float>(esmpName[ESMP_EXPDENSITY], 
						fExpDensity);

					float		fLinearEnd;
					getPropertyValue<float>(esmpName[ESMP_LINEAREND], 
						fLinearEnd);

					m_pSceneManager->setFog(mode, clrFog, fExpDensity, fLinearStart, fLinearEnd);
				}
				break;
			case ESMP_LINEAREND:
				{
					float fLinearEnd = any_cast<float>(anyValue);
					setPropertyValue<float>(parentName.empty() ? name : parentName,
						fLinearEnd);

					FogMode		mode;
					getPropertyValue<FogMode>(esmpName[ESMP_FOGMODE], mode);

					ColourValue clrFog;
					getPropertyValue<ColourValue>(esmpName[ESMP_FOGCOLOUR], 
						clrFog);

					float		fExpDensity;
					getPropertyValue<float>(esmpName[ESMP_EXPDENSITY], 
						fExpDensity);

					float		fLinearStart;
					getPropertyValue<float>(esmpName[ESMP_LINEARSTART], 
						fLinearStart);

					m_pSceneManager->setFog(mode, clrFog, fExpDensity, fLinearStart, fLinearEnd);
				}
				break;

			}
		}
		return true;
	}

	//////////////////////////////////////////////////////////////////////////
	/**
	 *
	 * \param factoryName 
	 * \return 
	 */
	EditorSceneManagerFactory::EditorSceneManagerFactory(const String& factoryName)
		: EditorPluginFactory(factoryName)
	{

	}

	/**
	 *
	 * \return 
	 */
	EditorSceneManagerFactory::~EditorSceneManagerFactory()
	{

	}

	/**
	 *
	 * \param ssadp 
	 * \param pParent 
	 * \return 
	 */
	EditorPlugin*		EditorSceneManagerFactory::createPlugin(const SEditorPluginAdp& ssadp, 
		EditorPlugin* pParent)
	{
		const SEditorPluginSceneManagerAdp& adp = static_cast<const SEditorPluginSceneManagerAdp&>(ssadp);

		EditorSceneManager* pEditorSceneManager = new EditorSceneManager(adp.pluginName, adp.typeMask, adp.clrAmbientLight, adp.fogMode, 
			adp.clrFog, adp.expDensity, adp.linearStart, adp.linearEnd);
		if (pEditorSceneManager)
		{
			// 设置删除优先级
			pEditorSceneManager->setPriority(PRIORITY_LOWEST);

			TKLogEvent("Create editor plugin : " + adp.pluginName,
				LML_NORMAL);

			if (pParent)
				pParent->registerPlugin(pEditorSceneManager);

			return pEditorSceneManager;
		}

		return NULL;
	}
}