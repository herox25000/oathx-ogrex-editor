#ifndef _____OgreEditorPluginManager_H
#define _____OgreEditorPluginManager_H

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
	* \Desc    : �༭���������
	*
	* \bug     : 
	*
	* \Copyright (c) 2012 lp All rights reserved.
	*/
	class Ogre_EditorCore_Export_API EditorPluginManager : public Singleton<EditorPluginManager>
	{
	public:
		/**
		 *
		 * \return 
		 */
		static	EditorPluginManager&	getSingleton();

		/**
		 *
		 * \return 
		 */
		static	EditorPluginManager*	getSingletonPtr();

	public:
		/**
		 *
		 * \param rootName 
		 * \return 
		 */
		EditorPluginManager(const String& rootName);

		/**
		 *
		 * \return 
		 */
		virtual ~EditorPluginManager();

		/**
		 *
		 * \return 
		 */
		virtual	EditorPlugin*			getRootPlugin() const;

		/**
		 *
		 * \param name 
		 * \return 
		 */
		virtual	EditorPlugin*			findPlugin(const String& name);
		
		/** ���õ�ǰѡ����
		 *
		 * \param pPlugin 
		 */
		virtual	void					setSelectPlugin(EditorPlugin* pPlugin);

		/** ��ȡ��ǰѡ����
		 *
		 * \return 
		 */
		virtual	EditorPlugin*			getSelectPlugin() const;

		/**
		 *
		 * \param vPois 
		 * \return 
		 */
		virtual	bool					injectMouseMove(const Vector2& vPos);
	protected:
		// �����
		EditorPlugin*					m_pRootPlugin;
		// ��ǰѡ����
		EditorPlugin*					m_pSelectPlugin;
	};
}

#endif