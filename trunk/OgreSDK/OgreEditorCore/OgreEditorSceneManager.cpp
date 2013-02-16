#include "OgreEditorCoreStdAfx.h"
#include "OgreEditorSceneManager.h"

namespace Ogre
{
	enum {
		SM_PLUGIN_NAME,
		SM_SCENETYPEMASK,
		SM_AMBIENTLIGHT,

		ESMP_COUNT,
	};

	// 属性名
	static const String smName[] = {
		"Name",
		"SceneTypeMask",
		"AmbientLight",
	};
	
	// 属性描述
	static const String smDesc[] = {
		"Name",
		"SceneTypeMask",
		"AmbientLight",
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
			if (smName[i] == name)
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
		: EditorPlugin(pluginName)
	{
		if (configure(pluginName, typeMask, clrAmbientLight, fogMode, clrFog, expDensity, linearStart, linearEnd))
		{
			addProperty(smName[SM_PLUGIN_NAME],
				Any(pluginName), PVT_STRING, 0,	smDesc[SM_PLUGIN_NAME]);
			addProperty(smName[SM_AMBIENTLIGHT],
				Any(clrAmbientLight), PVT_COLOUR, true, smDesc[SM_AMBIENTLIGHT]);
			addProperty(smName[SM_SCENETYPEMASK],
				Any(typeMask), PVT_USHORT, 0, smDesc[SM_SCENETYPEMASK]);
		}
	}

	/**
	 *
	 * \return 
	 */
	EditorSceneManager::~EditorSceneManager()
	{
		destroy();
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
			// 设置漫反射
			m_pSceneManager->setAmbientLight(clrAmbientLight);

			// 设置雾
			m_pSceneManager->setFog(fogMode, clrFog, 
				expDensity, linearStart, linearEnd);
			
			return true;
		}
		else
		{
			LogManager::getSingleton().logMessage("Can't create ogre scene manager : " + pluginName,
				LML_CRITICAL);
		}

		return 0;
	}

	/**
	 *
	 */
	void			EditorSceneManager::destroy()
	{
		destroyAllPlugin();

		if (m_pSceneManager)
		{
			Root::getSingletonPtr()->destroySceneManager(m_pSceneManager);
		}
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
			case SM_AMBIENTLIGHT:
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
			LogManager::getSingleton().logMessage("Create editor plugin : " + adp.pluginName,
				LML_NORMAL);

			// 设置删除优先级
			pEditorSceneManager->setPriority(PRIORITY_LOWEST);

			if (pParent)
				pParent->registerPlugin(pEditorSceneManager);

			return pEditorSceneManager;
		}

		return NULL;
	}
}