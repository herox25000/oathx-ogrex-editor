#ifndef _____OgreSandBox_H
#define _____OgreSandBox_H

namespace Ogre
{
	// plugin register table
	typedef vector<Plugin*>::type	PluginRegister;
	// dynlib register table 
	typedef vector<DynLib*>::type	DynlibRegister;

	/**
	* \ingroup : OgreSandBoxCore
	*
	* \os&IDE  : Microsoft Windows XP (SP3)  &  Microsoft Visual C++ .NET 2008
	*
	* \VERSION : 1.0
	*
	* \date    : 2013-05-28
	*
	* \Author  : lp
	*
	* \Desc    : Sand box system classes
	*
	* \bug     : 
	*
	* \Copyright (c) 2012 lp All rights reserved.
	*/
	class Ogre_SandBox_Export_API SandBox : public Singleton<SandBox>
	{
	public:
		/** get sand box system single object
		 *
		 * \return 
		 */
		static	SandBox&			getSingleton();

		/** get sand box system single object ptr
		 *
		 * \return 
		 */
		static	SandBox*			getSingletonPtr();
	public:
		/** consturctor
		 *
		 * \return 
		 */
		SandBox();

		/** Analysis constructors
		 *
		 * \return 
		 */
		virtual ~SandBox();

		/**	Create a sandbox system initialization ogre engine
		 *
		 * \param pluginFileName		Ogre plugin config file
		 * \param resourceFileName		Ogre resource config file
		 * \param bAutoCreateWindow		Whether to automatically create a WIN32 window

		 * \return Returns true if successful, false otherwise
		 */
		virtual	bool				createSandBox(const String& pluginFileName, const String& resourceFileName,
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
		Root*						m_pRoot;				// ogre root object
		RenderWindow*				m_pWindow;				// ogre auto render window
		PluginRegister				m_vPluginRegister;		// plugin register table
		DynlibRegister				m_vDynlibRegister;		// dynlib register table
	};
}

#endif