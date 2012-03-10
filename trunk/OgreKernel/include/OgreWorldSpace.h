#ifndef _____WorldSpace
#define _____WorldSpace

#include "OgreKernelPrerequisites.h"
#include "OgreDebugDrawer.h"
#include "OgreSdkCamera.h"

namespace Ogre
{
	/**
	* \ingroup : OgreKernel
	*
	* \os&IDE  : Microsoft Windows XP (SP3)  &  Microsoft Visual C++ .NET 2008 & ogre1.8
	*
	* \VERSION : 1.0
	*
	* \@date   : 2011-12-19
	*
	* \Author  : lp
	*
	* \Desc    : 世界空间类,该类将在内核对象创建时构造和内核对象一起被销毁
	*
	* \bug     : 
	*
	*/
	class Ogre_Export_API WorldSpace : public Singleton<WorldSpace>
	{
	public:
		/**	获取单件
		 *
		 * \return 
		 */
		static	WorldSpace&			getSingleton();

		/** 获取单件指针
		 *
		 * \return 
		 */
		static	WorldSpace*			getSingletonPtr();

	public:
		/**
		 *
		 * \param void 
		 * \return 
		 */
		WorldSpace(void);

		/**
		 *
		 * \param void 
		 * \return 
		 */
		virtual ~WorldSpace(void);
		
		/** 创建世界空间
		 *
		 * \param vPos				摄像机位置
		 * \param vLookAt			观察点
		 * \param fFarClipDistance	最近点
		 * \param NearClipDistance	最远点
		 * \return 
		 */
		virtual bool				createWorldSpace(const Vector3& vPos, const Vector3& vLookAt, float fFarClipDistance, float NearClipDistance);

		/** 销毁世界
		 *
		 */
		virtual void				destroyWorldSpace();
		
		/** 获取摄像机
		 *
		 * \return 
		 */
		virtual	Camera*				getCamera() const;

		/** 取得视图
		 *
		 * \return 
		 */
		virtual Viewport*			getViewport() const;

		/** 获取场景管理器
		 *
		 * \return 
		 */
		virtual SceneManager*		getSceneManager() const;

	protected:
		/** 创建世界空间
		 *
		 * \param vPos				摄像机位置
		 * \param vLookAt			观察点
		 * \param fFarClipDistance	最近点
		 * \param NearClipDistance	最远点
		 * \return 
		 */
		virtual void				createCamera(const Vector3& vPos, const Vector3& vLookAt, 
			float fFarClipDistance, float NearClipDistance);

	protected:
		RenderWindow*				m_pRenderWindow;
		SceneManager*				m_pScene;
		Camera*						m_pCamera;
		Viewport*					m_pView;
		DebugDrawer*				m_pDebugDrawer;
		SdkCamera*					m_pSdkCmaera;		
	};
}

#endif

