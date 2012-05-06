#ifndef _____OgreSystem_H
#define _____OgreSystem_H

#include "OgreServer.h"

namespace Ogre
{
	typedef std::vector<Server*>	VServer;
	typedef HashMap<String, ServerFactory*>	HashServerFactory;
	typedef std::vector<Plugin*>	VPlugin;
	typedef std::vector<DynLib*>	VDynlib;

	/**
	* \ingroup : System
	*
	* \os&IDE  : Microsoft Windows XP (SP3)  &  Microsoft Visual C++ .NET 2008 & ogre1.8
	*
	* \VERSION : 1.0
	*
	* \@date   : 2012-04-06
	*
	* \Author  : lp
	*
	* \Desc    : ϵͳ����
	*
	* \bug     : 
	*
	*/
	class Ogre_System_Export_API System 
		: public Singleton<System>
	{
	public:
		/**
		 *
		 * \return 
		 */
		static	System&			getSingleton();

		/**
		 *
		 * \return 
		 */
		static	System*			getSingletonPtr();

	public:
		/** ���캯��
		 *
		 * \return 
		 */
		System();

		/** ��������
		 *
		 * \return 
		 */
		virtual ~System();

		/** ����ϵͳ
		 *
		 * \param pluginFileName	ϵͳ��������ļ�
		 * \param resourceFileName	ϵͳ��Դ�����ļ�
		 * \return 
		 */
		virtual bool				create(const String& pluginFileName, const String& resourceFileName, bool bAutoCreateWindow);
		
		/**
		 *
		 */
		virtual void				update();

		/** ����ϵͳ
		 *
		 */
		virtual void				destroy();
	
	public:
		/**
		 *
		 * \param pFactory 
		 */
		virtual void				registerServerFactory(ServerFactory* pFactory);

		/**
		 *
		 * \param typeName 
		 * \return 
		 */
		virtual ServerFactory*		getServerFactory(const String& typeName);

		/**
		 *
		 * \param pFactory 
		 */
		virtual void				unregisterServerFactory(ServerFactory* pFactory);

		/**
		 *
		 */
		virtual void				clearServerFactory();

	public:
		/** ����ӷ���
		 *
		 * \param pServer �������,���Զ����ø�����
		 * \return 
		 */
		virtual bool				addServer(Server* pServer);

		/** ��ȡ�ӷ���
		 *
		 * \param typeName 
		 * \return 
		 */
		virtual Server*				getServer(const String& typeName);

		/** ɾ������
		 *
		 * \param pServer 
		 */
		virtual void				delServer(Server* pServer);

		/** ������з��񣬷���ɾ��
		 *
		 */
		virtual void				clearServer();

		/**
		 *
		 * \return 
		 */
		virtual int					getServerCount() const;

	public:
		/** ������Ⱦ����
		 *
		 * \param hWnd 
		 * \param w 
		 * \param h 
		 * \param bFullScree 
		 */
		virtual void				createApplicationWindow(const String& name, HWND hWnd, int w, int h, bool bFullScreen);
		
		/** ��ȡ��Ⱦ����
		 *
		 * \return 
		 */
		virtual RenderWindow*		getApplicationWindow() const;

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
		HashServerFactory			m_hashFactory;
		VServer						m_vServer;
		VPlugin						m_vPlugin;
		VDynlib						m_vDynlib;
	};
}

#endif