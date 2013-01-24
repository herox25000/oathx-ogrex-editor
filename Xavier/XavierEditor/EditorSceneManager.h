#ifndef _____EditorSceneManager_H
#define _____EditorSceneManager_H

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
	class EditorSceneManager : public EditorPlugin
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
	protected:
		/**
		 *
		 * \param fogMode 
		 * \param clrFog 
		 * \param expDensity 
		 * \param linearStart 
		 * \param linearEnd 
		 */
		virtual	void				configureFog(FogMode fogMode, const ColourValue& clrFog, 
			float expDensity, float linearStart, float linearEnd);
	protected:
		SceneManager*				m_pSceneManager;
	};


}

#endif