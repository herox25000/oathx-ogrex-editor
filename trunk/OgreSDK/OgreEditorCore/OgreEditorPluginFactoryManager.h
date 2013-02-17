#ifndef _____OgreEditorPluginFactoryManager_H
#define _____OgreEditorPluginFactoryManager_H

#include "OgreEditorSceneManager.h"
#include "OgreEditorCamera.h"
#include "OgreEditorViewport.h"

namespace Ogre
{
	enum {
		EPF_SCENEMANAGER,
		EPF_CAMERA,
		EPF_VIEWPORT,
		EPF_TERRAINGROUP,
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
	* \Desc    : �༭�������������
	*
	* \bug     : 
	*
	* \Copyright (c) 2012 lp All rights reserved.
	*/
	class Ogre_EditorCore_Export_API EditorPluginFactoryManager : public Singleton<EditorPluginFactoryManager>
	{
		typedef HashMap<String, EditorPluginFactory*>	HashMapEditorPluginFactory;
	public:
		/** ��ȡ�༭����
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
		/** ���캯��
		 *
		 * \return 
		 */
		EditorPluginFactoryManager();

		/** ��������
		 *
		 * \return 
		 */
		virtual ~EditorPluginFactoryManager();

		/** ע��༭����
		 *
		 * \param pFactory 
		 * \return 
		 */
		virtual	bool						registerEditorPluginFactory(EditorPluginFactory* pFactory);

		/** ��ȡ�༭����
		 *
		 * \param factoryName 
		 * \return 
		 */
		virtual	EditorPluginFactory*		getEditorPluginFactory(const String& factoryName);

		/** ��ȡ�༭����
		 *
		 * \param nType 
		 * \return 
		 */
		virtual	EditorPluginFactory*		getEditorPluginFactory(const int nType);

		/** ע���༭����
		 *
		 * \param factoryName 
		 */
		virtual	void						unregisterEditorPluginFactory(const String& factoryName);
	private:
		HashMapEditorPluginFactory			m_HashMapEditorPluginFactory;
	};
}

#endif