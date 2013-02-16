#ifndef _____OgreEditorSystem_H
#define _____OgreEditorSystem_H

#include "OgreEditorPluginFactoryManager.h"
#include "OgreEditorPluginManager.h"

namespace Ogre
{
	typedef std::vector<Plugin*>	PluginRegister;
	typedef std::vector<DynLib*>	DynlibRegister;

	/**
	* \ingroup : OgreSystem
	*
	* \os&IDE  : Microsoft Windows XP (SP3)  &  Microsoft Visual C++ .NET 2008
	*
	* \VERSION : 1.0
	*
	* \date    : 2013-01-15
	*
	* \Author  : lp
	*
	* \Desc    :
	*
	* \bug     : 
	*
	* \Copyright (c) 2012 lp All rights reserved.
	*/
	class Ogre_EditorCore_Export_API EditorSystem : public Singleton<EditorSystem>
	{
	public:
		/**
		 *
		 * \return 
		 */
		static	EditorSystem&		getSingleton();

		/**
		 *
		 * \return 
		 */
		static	EditorSystem*		getSingletonPtr();
	public:
		/**
		 *
		 * \return 
		 */
		EditorSystem();

		/**
		 *
		 * \return 
		 */
		virtual ~EditorSystem();

		/** ����ϵͳ
		 *
		 * \param pluginFileName	ϵͳ��������ļ�
		 * \param resourceFileName	ϵͳ��Դ�����ļ�
		 * \param bAutoCreateWindow 
		 * \return 
		 */
		virtual bool				createEditorSystem(const String& pluginFileName, const String& resourceFileName, bool bAutoCreateWindow);
		
		/**
		 *
		 */
		virtual void				drawFrame();

		/** ����ϵͳ
		 *
		 */
		virtual void				clearUp();

	public:
		/** ������Ⱦ����
		 *
		 * \param hWnd 
		 * \param w 
		 * \param h 
		 * \param bFullScree 
		 */
		virtual bool				createRenderWindow(const String& name, HWND hWnd, 
			int w, int h, bool bFullScreen);
		
		/** ��ȡ��Ⱦ����
		 *
		 * \return 
		 */
		virtual RenderWindow*		getRenderWindow() const;

		/** ���ز��
		 *
		 * \param name 
		 */
		virtual	void				loadPlugin(const String& name);

		/** ж�ز��
		 *
		 * \param name 
		 */
		virtual void				unloadPlugin(const String& name);

		/** ��װ���
		 *
		 * \param pPlugin 
		 */
		virtual void				installPlugin(Plugin* pPlugin);

		/** ж�ز��
		 *
		 * \param pPlugin 
		 */
		virtual void				uninstallPlugin(Plugin* pPlugin);

		/** ��ղ��
		 *
		 */
		virtual void				clearPlugin();
	protected:
		Root*						m_pRoot;
		RenderWindow*				m_pRenderWindow;
		PluginRegister				m_vPluginRegister;
		DynlibRegister				m_vDynlibRegister;
	};
}

#endif