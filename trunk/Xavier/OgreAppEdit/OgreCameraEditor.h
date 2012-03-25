#ifndef _____OgreCameraEditor_H
#define _____OgreCameraEditor_H

#include "OgreBaseEditor.h"

namespace Ogre
{
	// 摄像机模式
	enum
	{
		CS_FREELOOK,
		CS_ORBIT,
		CS_MANUAL
	};

	/**
	* \ingroup : OgreEditSystem
	*
	* \os&IDE  : Microsoft Windows XP (SP3)  &  Microsoft Visual C++ .NET 2008 & ogre1.8
	*
	* \VERSION : 1.0
	*
	* \@date   : 2012-03-11
	*
	* \Author  : lp
	*
	* \Desc    : 摄像机编辑器
	*
	* \bug     : 
	*
	*/
	class OgreAppEdit_Export_API CameraEditor : public BaseEditor
	{
	public:
		/** 构造函数
		 *
		 * \param vPos				摄像机位置
		 * \param vLookAt			观察点
		 * \param fYaw				
		 * \param fPitch 
		 * \param fNearClipDistance 
		 * \param fNearClipDistance 
		 * \return 
		 */
		CameraEditor(const Vector3& vPos, const Vector3& vLookAt,
			Real fYaw, Real fPitch, Real fNearClipDistance, Real fFarClipDistance);
		
		/**
		 *
		 * \param void 
		 * \return 
		 */
		virtual ~CameraEditor(void);

		/** 获取摄像机
		 *
		 * \return 
		 */
		virtual Camera*				getCamera() const;
		
		/** 设置摄像机
		 *
		 * \param pCamera 
		 */
		virtual void				setCamera(Camera* pCamera);

		/** 设置观察目标
		 *
		 * \param pTarget 
		 */
		virtual void				setTarget(SceneNode* pTarget);

		/** 获取目标
		 *
		 * \return 
		 */
		virtual SceneNode*			getTarget() const;

		/**
		 *
		 * \param yaw 
		 * \param pitch 
		 * \param dist 
		 */
		virtual void				setYawPitchDist(Radian yaw, Radian pitch, Real dist);

		/**
		 *
		 * \param nMode 
		 */
		virtual void				setMode(int nMode);

		/**
		 *
		 * \return 
		 */
		virtual int					getMode() const;

		/**
		 *
		 * \param x 
		 * \param y 
		 * \param z 
		 */
		virtual void				injectMouseMove(float x, float y);

		/**
		 *
		 * \param z 
		 */
		virtual void				injectMouseWheel(float z);

		/**
		 *
		 * \param key 
		 */
		virtual void				injectKeyDown(int key);
	protected:
		Camera*						m_pCamera;
		SceneNode*					m_pTarget;
		int							m_nMode;
		bool						m_bOrbiting;
		bool						m_bZooming;
		Real						m_fTopSpeed;
		Vector3						m_vVelocity;
		bool						m_bGoingForward;
		bool						m_bGoingBack;
		bool						m_bGoingLeft;
		bool						m_bGoingRight;
		bool						m_bGoingUp;
		bool						m_bGoingDown;
		bool						m_bFastMove;
	};

	// 摄像机创建参数
	struct SCameraCreateParam : public SBaseCreateParam
	{
		Vector3						vPos;
		Vector3						vLookAt;
		Real						fYaw;
		Real						fPitch;
		Real						fNearClipDistance;
		float						fFarClipDistance;
	};

	/**
	* \ingroup : OgreEditSystem
	*
	* \os&IDE  : Microsoft Windows XP (SP3)  &  Microsoft Visual C++ .NET 2008 & ogre1.8
	*
	* \VERSION : 1.0
	*
	* \@date   : 2012-03-11
	*
	* \Author  : lp
	*
	* \Desc    : 摄像机编辑工厂
	*
	* \bug     : 
	*
	*/
	class OgreAppEdit_Export_API CameraEditorFactory : public BaseEditorFactory
	{
	public:
		/** 构造函数
		 *
		 * \return 
		 */
		CameraEditorFactory();

		/** 析构函数
		 *
		 * \return 
		 */
		virtual ~CameraEditorFactory();

		/** 创建
		 *
		 * \param pm 
		 * \return 
		 */
		virtual BaseEditor*				create(const SBaseCreateParam* pm);
	};
}

#endif
