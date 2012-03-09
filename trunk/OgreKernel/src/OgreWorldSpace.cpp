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
		:m_pScene(NULL), m_pCamera(NULL), m_pView(NULL)
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
			创建场景管理器
		*/
		m_pScene = Root::getSingletonPtr()->createSceneManager(Ogre::ST_GENERIC);
		if (m_pScene != NULL)
		{
			createCamera(vPos, vLookAt, fFarClipDistance, NearClipDistance);
			
			// 创建视图
			m_pView = OgreKernel::getSingletonPtr()->getRenderWindow()->addViewport(m_pCamera);
			if ( m_pView != NULL )
			{
				// 设置背景颜色
				m_pView->setBackgroundColour(ColourValue(0,0,0,0));

				m_pCamera->setAspectRatio(
						Ogre::Real(m_pView->getActualWidth()) / Ogre::Real(m_pView->getActualHeight())
						);
			}
		}
		
		return true;
	}
	
	//////////////////////////////////////////////////////////////////////////
	void			WorldSpace::destroyWorldSpace()
	{

	}

	//////////////////////////////////////////////////////////////////////////
	void			WorldSpace::createCamera(const Vector3& vPos, const Vector3& vLookAt,
		float fFarClipDistance, float NearClipDistance)
	{
		m_pCamera = m_pScene->createCamera("WorldSpaceCamera");
		m_pCamera->setPosition(vPos);
		m_pCamera->lookAt(vLookAt);
		m_pCamera->setFarClipDistance(fFarClipDistance);
		m_pCamera->setNearClipDistance(fFarClipDistance);
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
}

