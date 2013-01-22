#include "OgreSystemStdAfx.h"
#include "OgreWorld.h"
#include "OgreSystem.h"

namespace Ogre
{

	template<>	World*	Singleton<World>::msSingleton = NULL;
	/**
	 *
	 * \return 
	 */
	World&		World::getSingleton()
	{
		assert(msSingleton != NULL); return (*msSingleton);
	}

	/**
	 *
	 * \return 
	 */
	World*		World::getSingletonPtr()
	{
		assert(msSingleton != NULL); return msSingleton;
	}
	
	// Ĭ�����������
	const String	World::DEFAULT_MAIN_CAMERA = ("WMC");

	/**
	 *
	 * \return 
	 */
	World::World(const String& name, const SceneTypeMask& typeMask, const ColourValue& clrAmbientLight, 
		const Vector3& vPos, const Vector3& vLookAt, Real fYaw, Real fPitch, Real fNearClipDistance, Real fFarClipDistance, const ColourValue& background)
	{
		// ��������������
		m_pSceneManager = Root::getSingleton().createSceneManager(typeMask, name);
		if (m_pSceneManager)
		{
			// ���û�����
			m_pSceneManager->setAmbientLight(clrAmbientLight);
			
			// Ĭ������
			configureDefault(vPos, vLookAt, fYaw, fPitch, fNearClipDistance, fFarClipDistance, background);
		}	
	}

	/**
	 *
	 * \return 
	 */
	World::~World()
	{
		// �Ƴ��ӿ�
		System::getSingleton().getRenderWindow()->removeViewport(
			m_pViewport->getZOrder()
			);

		// ���������
		if (m_pCamera)
		{
			m_pCamera->getSceneManager()->destroyCamera(m_pCamera);
		}

		// ���ٳ���
		Root::getSingletonPtr()->destroySceneManager(m_pSceneManager);
	}

	/**
	 *
	 * \return 
	 */
	SceneManager*	World::getSceneManager() const
	{
		return m_pSceneManager;
	}

	/**
	 *
	 * \return 
	 */
	Camera*			World::getCamera() const
	{
		return m_pCamera;
	}

	/**
	 *
	 * \return 
	 */
	Viewport*		World::getViewport() const
	{
		return m_pViewport;
	}

	/**
	 *
	 * \param vPos 
	 * \param vLookAt 
	 * \param fYaw 
	 * \param fPitch 
	 * \param fNearClipDistance 
	 * \param fFarClipDistance 
	 * \return 
	 */
	bool			World::configureDefault(const Vector3& vPos, const Vector3& vLookAt, 
		Real fYaw, Real fPitch, Real fNearClipDistance, Real fFarClipDistance, const ColourValue& background)
	{
		if (m_pSceneManager == NULL)
			return 0;

		m_pCamera = m_pSceneManager->createCamera(DEFAULT_MAIN_CAMERA);
		m_pCamera->setPosition(vPos);
		m_pCamera->lookAt(vLookAt);

		m_pCamera->setNearClipDistance(fNearClipDistance);
		m_pCamera->setFarClipDistance(fFarClipDistance);

		m_pCamera->yaw(Degree(fYaw));
		m_pCamera->pitch(Degree(fPitch));
		
		/*
		* ����ӿ�
		*/
		RenderWindow* pRenderWindow = System::getSingletonPtr()->getRenderWindow();
		if (pRenderWindow)
		{
			m_pViewport = pRenderWindow->addViewport(m_pCamera);
			if (m_pViewport)
			{
				m_pViewport->setBackgroundColour(background);

				pRenderWindow->windowMovedOrResized();
				m_pCamera->setAspectRatio(
					Ogre::Real(m_pViewport->getActualWidth()) / Ogre::Real(m_pViewport->getActualHeight())
					);			
			}
		}

		return true;
	}

	/**
	 *
	 */
	void			World::windowMovedOrResized()
	{
		RenderWindow* pRenderWindow = System::getSingleton().getRenderWindow();
		if (m_pCamera != NULL && pRenderWindow != NULL)
		{
			pRenderWindow->windowMovedOrResized();

			m_pCamera->setAspectRatio(
				Ogre::Real(m_pViewport->getActualWidth()) / Ogre::Real(m_pViewport->getActualHeight())
				);	
		}
	}
}