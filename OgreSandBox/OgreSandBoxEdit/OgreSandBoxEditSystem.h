#ifndef _____OgreSandBoxEditSystem_H
#define _____OgreSandBoxEditSystem_H

namespace Ogre
{
	/**
	* \ingroup : OgreSandBoxEdit
	*
	* \os&IDE  : Microsoft Windows XP (SP3)  &  Microsoft Visual C++ .NET 2008
	*
	* \VERSION : 1.0
	*
	* \date    : 2013-05-31
	*
	* \Author  : lp
	*
	* \Desc    :
	*
	* \bug     : 
	*
	* \Copyright (c) 2012 lp All rights reserved.
	*/
	class Ogre_SandBoxEdit_Export_API EditSystem : public Singleton<EditSystem>
	{
	public:
		/**
		 *
		 * \return 
		 */
		static	EditSystem&			getSingleton();

		/**
		 *
		 * \return 
		 */
		static	EditSystem*			getSingletonPtr();
	public:
		/**
		 *
		 * \return 
		 */
		EditSystem();

		/**
		 *
		 * \return 
		 */
		virtual ~EditSystem();

		/**	Create a sandbox system initialization ogre engine
		 *
		 * \param pluginFileName		Ogre plugin config file
		 * \param resourceFileName		Ogre resource config file
		 * \param bAutoCreateWindow		Whether to automatically create a WIN32 window

		 * \return Returns true if successful, false otherwise
		 */
		virtual	bool				createEditSystem(const String& pluginFileName, const String& resourceFileName,
			bool bAutoCreateWindow);

		/**
		* start Periodic updates
		 */
		virtual	void				go();

		/**
		 * clear up sand box
		 */
		virtual	void				clearUp();

	public:
		/** create ogre render window
		 *
		 * \param name			render window name
		 * \param hWnd			Windows handle
		 * \param cSize			window size
		 * \param bFullScreen	Whether to use full screen mode
		 * \return 
		 */
		virtual bool				createWindow(const String& name, HWND hWnd, 
			int w, int h, bool bFullScreen);

		/** Return ogre render window object
		 *
		 * \return NULL if failed
		 */
		virtual	RenderWindow*		getWindow() const;

	public:
		/** load a sand box plugin
		 *
		 * \param name 
		 */
		virtual	void				loadPlugin(const String& name);

		/** unload a sand box plugin
		 *
		 * \param name 
		 */
		virtual void				unloadPlugin(const String& name);

		/** install a sand box plugin to system
		 *
		 * \param pPlugin	plugin object
		 * \return ture if seccussful, false failed
		 */
		virtual	void				installPlugin(Plugin* pPlugin);

		/** uninstall a sand box plugin from system
		 *
		 * \param pPlugin plugin object
		 */
		virtual	void				uninstallPlugin(Plugin* pPlugin);

		/** destory all sand box plugin
		 *
		 */
		virtual void				destoryAllPlugin();
	protected:
		SandBox*					m_pSandBox;
	};
}

#endif