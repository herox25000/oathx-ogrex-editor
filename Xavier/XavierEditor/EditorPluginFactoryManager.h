#ifndef _____EditorPluginFactoryManager_H
#define _____EditorPluginFactoryManager_H

namespace Ogre
{
	enum {
		EPF_SCENEMANAGER,
		EPF_CAMERA,
		EPF_VIEWPORT,
		EPF_TERRAIN,
		EPF_TERRAINPAGE,
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
	class EditorPluginFactoryManager : public Singleton<EditorPluginFactoryManager>
	{
		typedef HashMap<String, EditorPluginFactory*>	HashMapEditorPluginFactory;
	public:
		/**
		 *
		 * \return 
		 */
		static	EditorPluginFactoryManager&	getSingleton();

		/**
		 *
		 * \return 
		 */
		static	EditorPluginFactoryManager*	getSingletonPtr();
	public:
		/**
		 *
		 * \return 
		 */
		EditorPluginFactoryManager();

		/**
		 *
		 * \return 
		 */
		virtual ~EditorPluginFactoryManager();

		/**
		 *
		 * \param pFactory 
		 * \return 
		 */
		virtual	bool						registerEditorPluginFactory(EditorPluginFactory* pFactory);
		/**
		 *
		 * \param factoryName 
		 * \return 
		 */
		virtual	EditorPluginFactory*		getEditorPluginFactory(const String& factoryName);

		/**
		 *
		 * \param nType 
		 * \return 
		 */
		virtual	EditorPluginFactory*		getEditorPluginFactory(const int nType);

		/**
		 *
		 * \param factoryName 
		 */
		virtual	void						unregisterEditorPluginFactory(const String& factoryName);
	private:
		HashMapEditorPluginFactory			m_HashMapEditorPluginFactory;
	};
}

#endif