#include "stdafx.h"
#include "EditorPlugin.h"
#include "EditorSceneManager.h"

namespace Ogre
{
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
		m_pSceneManager = Root::getSingletonPtr()->createSceneManager(typeMask, pluginName);
		if (m_pSceneManager)
		{
			// 设置漫反射
			m_pSceneManager->setAmbientLight(clrAmbientLight);

			// 设置雾
			m_pSceneManager->setFog(fogMode, clrFog, 
				expDensity, linearStart, linearEnd);

			// 添加属性
			addProperty(esmpName[ESMP_AMBIENTLIGHT],
				Any(clrAmbientLight), PVT_COLOUR, true,	esmpDesc[ESMP_AMBIENTLIGHT]);
			addProperty(esmpName[ESMP_SCENETYPEMASK],
				Any(typeMask), PVT_USHORT, 0, esmpDesc[ESMP_SCENETYPEMASK]);
			addProperty(esmpName[ESMP_FOGMODE], 
				Any((int)fogMode), PVT_INT, true, esmpDesc[ESMP_FOGMODE]);
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

	}

	/**
	 *
	 * \param fogMode 
	 * \param clrFog 
	 * \param expDensity 
	 * \param linearStart 
	 * \param linearEnd 
	 */
	void			EditorSceneManager::configureFog(FogMode fogMode, const ColourValue& clrFog, 
		float expDensity, float linearStart, float linearEnd)
	{
		if (m_pSceneManager)
		{
			m_pSceneManager->setFog(fogMode, clrFog, expDensity, linearStart, linearEnd);
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
}