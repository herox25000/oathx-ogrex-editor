#ifndef _____OgreEditorSceneManager_H
#define _____OgreEditorSceneManager_H

#include "OgreEditorPlugin.h"

namespace Ogre
{
	/**
	* \ingroup : XavierEditor
	*
	* \os&IDE  : Microsoft Windows XP (SP3)  &  Microsoft Visual C++ .NET 2008
	*
	* \VERSION : 1.0
	*
	* \date    : 2013-01-24
	*
	* \Author  : lp
	*
	* \Desc    :
	*
	* \bug     : 
	*
	* \Copyright (c) 2012 lp All rights reserved.
	*/
	class Ogre_EditorCore_Export_API EditorSceneManager : public EditorPlugin
	{	
	public:
		/**
		 *
		 * \param pluginName 
		 * \param typeMask 
		 * \param clrAmbientLight 
		 * \param fogMode 
		 * \param clrFog 
		 * \param expDensity 
		 * \param linearStart 
		 * \param linearEnd 
		 * \return 
		 */
		EditorSceneManager(const String& pluginName, const SceneTypeMask& typeMask, const ColourValue& clrAmbientLight,
			FogMode fogMode, const ColourValue& clrFog, float expDensity, float linearStart, float linearEnd);

		/**
		 *
		 * \return 
		 */
		virtual ~EditorSceneManager();

		/**
		 *
		 * \return 
		 */
		virtual	SceneManager*		getSceneManager() const;

	public:
		/** �������Ըı��¼�
		 *
		 * \param parentName 
		 * \param name 
		 * \param anyValue 
		 * \param nType 
		 * \return 
		 */
		virtual	bool				OnPropertyChanged(const String& parentName, const String& name, 
			const Any& anyValue, int nType);

	protected:
		/**
		 *
		 * \param pluginName 
		 * \param typeMask 
		 * \param fogMode 
		 * \param clrFog 
		 * \param expDensity 
		 * \param linearStart 
		 * \param linearEnd 
		 */
		virtual	bool				configure(const String& pluginName, const SceneTypeMask& typeMask, const ColourValue& clrAmbientLight,
			FogMode fogMode, const ColourValue& clrFog, float expDensity, float linearStart, float linearEnd);
		
		/**
		 *
		 * \return 
		 */
		virtual	void				destroy();
	protected:
		SceneManager*				m_pSceneManager;
	};

	// �������������
	struct SEditorPluginSceneManagerAdp : public SEditorPluginAdp
	{
		SceneTypeMask				typeMask;
		ColourValue					clrAmbientLight;
		FogMode						fogMode; 
		ColourValue					clrFog; 
		float						expDensity; 
		float						linearStart; 
		float						linearEnd;
	};

	/**
	* \ingroup : XavierEditor
	*
	* \os&IDE  : Microsoft Windows XP (SP2)  &  Microsoft Visual C++ .NET 2008
	*
	* \VERSION : 1.0
	*
	* \date    : 2013-01-24
	*
	* \Author  : lp
	*
	* \Desc    : �����������
	*
	* \bug     : 
	*
	* \Copyright (c) 2012 lp All rights reserved.
	*/
	class Ogre_EditorCore_Export_API EditorSceneManagerFactory : public EditorPluginFactory
	{
	public:
		/**
		 *
		 * \param factoryName 
		 * \return 
		 */
		EditorSceneManagerFactory(const String& factoryName);

		/**
		 *
		 * \return 
		 */
		virtual ~EditorSceneManagerFactory();

		/**
		 *
		 * \param ssadp 
		 * \param pParent 
		 * \return 
		 */
		virtual	EditorPlugin*			createPlugin(const SEditorPluginAdp& ssadp, EditorPlugin* pParent);
	};
}

#endif