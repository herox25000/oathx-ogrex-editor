#ifndef _____Og2dSystem_H
#define _____Og2dSystem_H

#include "Og2dWorld.h"

namespace Og2d
{	
	typedef vector<DynLib*>::type	VectorDynlib;
	typedef map<String, RenderSystem*>::type MapRenderSystem;
	typedef vector<Plugin*>::type	VectorPlugin;
	typedef map<int, SceneFactory*>::type MapSceneFactory;

	/**
	* \ingroup : Og2d
	*
	* \os&IDE  : Microsoft Windows XP (SP2)  &  Microsoft Visual C++ .NET 2008
	*
	* \VERSION : 1.0
	*
	* \date    : 2012-07-22
	*
	* \Author  : lp
	*
	* \Desc    : Og2dϵͳ��
	*
	* \bug     : 
	*
	*/
	class Og2d_Export_API System : public Singleton<System>
	{
	public:
		/** ʵ�ֻ�ȡ��������
		 *
		 * \return 
		 */
		static	System&				getSingleton();

		/** ʹ�û�ȡ����ָ��
		 *
		 * \return 
		 */
		static	System*				getSingletonPtr();

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
		~System();
		
	public:
		/** ϵͳ����
		 *
		 * \param szPlginFile		�����ļ���
		 * \param szLogFile			LOG�ļ���
		 * \param Value 
		 * \return 
		 */
		virtual	bool				startup(const String& szPlginFile, const String& szLogFile,
			const StringValue& Value);
		
		/** ϵͳ����
		 *
		 */
		virtual	bool				run(float fElapsed);

		/** �ر�ϵͳ
		 *
		 */
		virtual	void				shutdown();

	public:
		/** �����Ⱦϵͳ
		 *
		 * \param pRenderSystem
		 */
		virtual	void				addRenderSystem(RenderSystem* pRenderSystem);

		/** �Ƴ���Ⱦϵͳ
		 *
		 * \param pRenderSystem 
		 */
		virtual	void				removeRenderSystem(
			RenderSystem* pRenderSystem
			);

		/** ��ȡ��Ⱦϵͳ
		 *
		 * \param name 
		 * \return 
		 */
		virtual	RenderSystem*		getRenderSystem(const String& name);

		/** ������Ⱦϵͳ
		 *
		 * \param pRenderSystem 
		 */
		virtual	void				setRenderSystem(
			RenderSystem* pRenderSystem
			);

		/** ��ȡ��ǰ��Ⱦϵͳ
		 *
		 * \return 
		 */
		virtual	RenderSystem*		getRenderSystem() const;
	
	public:
		/** ��ӳ�������
		 *
		 * \param pFactory 
		 * \return 
		 */
		virtual	void				addSceneFactory(SceneFactory* pFactory);

		/** ��ȡ��������
		 *
		 * \param szName 
		 * \return 
		 */
		virtual	SceneFactory*		getSceneFactory(int nType);

		/** �Ƴ���������
		 *
		 * \param pFactory 
		 */
		virtual void				removeFactory(SceneFactory* pFactory);
		
		/** ������г�������
		 *
		 */
		virtual	void				clearSceneFactory();

		/** ��������
		 *
		 * \param szName 
		 * \param vOrigin ����ԭ��
		 * \return 
		 */
		virtual	World*				createWorld(const String& szName);
		
		/**
		 *
		 */
		virtual	void				destroyWorld();
	public:
		/** ���ز��
		 *
		 * \param name 
		 */
		virtual	void				loadPlugin(const String& name);

		/** ж�ز��
		 *
		 * \param name 
		 */
		virtual	void				unloadPlugin(const String& name);

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
		virtual	void				clearPlugin();
	protected:
		MapRenderSystem				m_vRenderSystem;
		RenderSystem*				m_pRenderSystem;
		VectorDynlib				m_vDynlib;
		VectorPlugin				m_vPlugin;
		MapSceneFactory				m_vSceneFactory;
		World*						m_pWorld;
	};
}

#endif