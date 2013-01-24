#ifndef _____EditorPluginManager_H
#define _____EditorPluginManager_H

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
	class EditorPluginManager : public Singleton<EditorPluginManager>
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

		/** �������
		 *
		 * \param factoryName 
		 * \param seadp 
		 * \param pParent 
		 * \return 
		 */
		virtual	EditorPlugin*			createEditorPlugin(const int factoryType,
			const SEditorPluginAdp& seadp, EditorPlugin* pParent);
	protected:
		// �����
		EditorPlugin*					m_pRootPlugin;
		// ��ǰѡ����
		EditorPlugin*					m_pSelectPlugin;
	};
}

#endif