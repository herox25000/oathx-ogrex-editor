#include "stdafx.h"
#include "EditorPlugin.h"
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
		: EditorPlugin(pluginName)
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
			// 设置漫反射
			m_pSceneManager->setAmbientLight(clrAmbientLight);

			// 设置雾
			m_pSceneManager->setFog(fogMode, clrFog, 
				expDensity, linearStart, linearEnd);
			
			return true;
		}
		else
		{
			TKLogEvent("Can't create ogre scene manager : " + pluginName,
				LML_TRIVIAL);
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