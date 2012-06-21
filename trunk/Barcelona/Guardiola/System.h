#ifndef _____System_H
#define _____System_H

namespace Barcelona
{
	typedef std::vector<Server*>					VServer;
	typedef HashMap<Ogre::String, ServerFactory*>	HashServerFactory;
	typedef Ogre::MapIterator<HashServerFactory>	ServerFactoryIter;

	/**
	* \ingroup : Guardiola
	*
	* \os&IDE  : Microsoft Windows XP (SP2)  &  Microsoft Visual C++ .NET 2008
	*
	* \VERSION : 1.0
	*
	* \date    : 2012-06-22
	*
	* \Author  : lp
	*
	* \Desc    : ϵͳ���󣬸����ʼ�������Լ��������еķ�������
	*			 ��ʵ���࣬������Ӧ�ó����ʼ��ʱ���ȴ���
	*
	* \bug     : 
	*
	*/
	class GuardiolaDLL_Export_API System : public Singleton<System>
	{
	public:
		/** ��ȡ��ʵ����������
		 *
		 * \return 
		 */
		static	System&			getSingleton();

		/** ��ȡ��ʵ������ָ��
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

		/** ���캯��
		 *
		 * \param pluginFileName		ϵͳ��������ļ�
		 * \param resourceFileName		ϵͳ��Դ�����ļ�
		 * \param bAutoCreateWindow		�Ƿ��Զ���������
		 * \return 
		 */
		System(const Ogre::String& pluginFileName, const Ogre::String& resourceFileName,
			bool bAutoCreateWindow);

		/** ��������
		 *
		 * \param void 
		 * \return 
		 */
		virtual ~System(void);

		/** ����ϵͳ
		 *
		 * \param pluginFileName		ϵͳ��������ļ�
		 * \param resourceFileName		ϵͳ��Դ�����ļ� 
		 * \param bAutoCreateWindow		�Ƿ��Զ���������
		 * \return 
		 */
		virtual bool				create(const Ogre::String& pluginFileName, const Ogre::String& resourceFileName,
			bool bAutoCreateWindow);
		

		/** ����Ӧ�ó���
		 *
		 * \param name					Ӧ�ó�������
		 * \param hWnd					ҽ�ó��򴰿ھ��
		 * \param w						�������ؿ��
		 * \param h						�������ظ߶�
		 * \param bFullScreen			�Ƿ�ȫ��
		 * \return 
		 */
		virtual void				createApplication(const Ogre::String& name, HWND hWnd, 
			int w, int h, bool bFullScreen);

		/** ����ϵͳ
		 *
		 */
		virtual void				update();

		/** ����ϵͳ
		 *
		 */
		virtual void				destroy();

		/**	ע����񹤳�
		 *
		 * \param pFactory	��������
		 */
		virtual void				registerServerFactory(ServerFactory* pFactory);

		/** ��ȡ���񹤳�
		 *
		 * \param typeName	��������
		 * \return 
		 */
		virtual ServerFactory*		getServerFactory(const Ogre::String& typeName);

		/** ע�����񹤳�
		 *
		 * \param pFactory	��������
		 */
		virtual void				unregisterServerFactory(ServerFactory* pFactory);

		/** ע�����񹤳�
		 *
		 * \param typeName	��������
		 */
		virtual void				unregisterServerFactory(const Ogre::String& typeName);

		/** ��ȡ���񹤳�������
		 *
		 * \return 
		 */
		virtual ServerFactoryIter	getHashServerFactory();

		/** ��շ��񹤳�
		 *
		 */
		virtual void				clearServerFactory();

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
		virtual Server*				getServer(const Ogre::String& typeName);

		/**
		 *
		 * \param idx 
		 * \return 
		 */
		virtual Server*				getServer(int idx);

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
	protected:
		Ogre::Root*					m_pRoot;
		Ogre::RenderWindow*			m_pRenderWindow;
		HashServerFactory			m_hashFactory;
		VServer						m_vServer;
	};
}

#endif
