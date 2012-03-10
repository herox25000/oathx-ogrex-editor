#include "OgreWorldSpace.h"
#include "OgreKernel.h"

namespace Ogre
{
	template<> WorldSpace*	Singleton<WorldSpace>::msSingleton = NULL;
	WorldSpace&		WorldSpace::getSingleton()
	{
		assert(msSingleton != NULL);  return (*msSingleton);
	}

	//////////////////////////////////////////////////////////////////////////
	WorldSpace*		WorldSpace::getSingletonPtr()
	{
		return msSingleton;
	}

	//////////////////////////////////////////////////////////////////////////
	//
	//////////////////////////////////////////////////////////////////////////
	WorldSpace::WorldSpace(void)
		:m_pScene(NULL), m_pCamera(NULL), m_pView(NULL), m_pDebugDrawer(NULL), m_pSdkCmaera(NULL)
	{
		
	}
	
	//////////////////////////////////////////////////////////////////////////
	WorldSpace::~WorldSpace(void)
	{

	}
	
	//////////////////////////////////////////////////////////////////////////
	bool			WorldSpace::createWorldSpace(const Vector3& vPos, const Vector3& vLookAt, float fFarClipDistance, float NearClipDistance)
	{
		/*
			��������������
		*/
		m_pScene = Root::getSingletonPtr()->createSceneManager(Ogre::ST_GENERIC);
		if (m_pScene != NULL)
		{
			createCamera(vPos, vLookAt, fFarClipDistance, NearClipDistance);
			
			// ������ͼ
			m_pView = OgreKernel::getSingletonPtr()->getRenderWindow()->addViewport(m_pCamera);
			if ( m_pView != NULL )
			{
				// ���ñ�����ɫ
				m_pView->setBackgroundColour(ColourValue(0,0,0,0));

				m_pCamera->setAspectRatio(
						Ogre::Real(m_pView->getActualWidth()) / Ogre::Real(m_pView->getActualHeight())
						);
			}

			m_pScene->setAmbientLight(Ogre::ColourValue(0.5, 0.5, 0.5));

			TextureManager::getSingleton().setDefaultNumMipmaps(5);
			ResourceGroupManager::getSingleton().initialiseAllResourceGroups();

			// �������Ի�����
			m_pDebugDrawer = new DebugDrawer(m_pScene, 0.5f);
		}
		
		return true;
	}
	
	//////////////////////////////////////////////////////////////////////////
	void			WorldSpace::destroyWorldSpace()
	{
		if (m_pDebugDrawer != NULL)
		{
			delete m_pDebugDrawer;
			m_pDebugDrawer = NULL;
		}

		if (m_pSdkCmaera)
			delete m_pSdkCmaera;
	}

	//////////////////////////////////////////////////////////////////////////
	void			WorldSpace::createCamera(const Vector3& vPos, const Vector3& vLookAt,
		float fFarClipDistance, float NearClipDistance)
	{
		// �����������
		m_pCamera = m_pScene->createCamera("WorldSpaceCamera");
		m_pCamera->setPosition(vPos);
		m_pCamera->lookAt(vLookAt);
		m_pCamera->setFarClipDistance(fFarClipDistance);
		m_pCamera->setNearClipDistance(NearClipDistance);
		
		// ���������������
		m_pSdkCmaera = new SdkCamera();
		m_pSdkCmaera->setCamera(m_pCamera);
	}

	//////////////////////////////////////////////////////////////////////////
	Camera*			WorldSpace::getCamera() const
	{
		return m_pCamera;
	}

	//////////////////////////////////////////////////////////////////////////
	Viewport*		WorldSpace::getViewport() const
	{
		return m_pView;
	}

	//////////////////////////////////////////////////////////////////////////
	SceneManager*	WorldSpace::getSceneManager() const
	{
		return m_pScene;
	}
}

