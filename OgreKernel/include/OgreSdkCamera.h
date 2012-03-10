#ifndef _____OgreSdkCamera_H
#define _____OgreSdkCamera_H

#pragma once

#include "OgreKernelPrerequisites.h"
#include "OgreSingleton.h"

namespace Ogre
{
	// 摄像机模式
	enum{
		SDK_CS_FREELOOK,
		SDK_CS_ORBIT,
		SDK_CS_MANUAL
	};

	/**
	* \ingroup : OgreKernel
	*
	* \os&IDE  : Microsoft Windows XP (SP3)  &  Microsoft Visual C++ .NET 2008 & ogre1.8
	*
	* \VERSION : 1.0
	*
	* \@date   : 2012-03-10
	*
	* \Author  : lp
	*
	* \Desc    : SDK 摄像机控制
	*
	* \bug     : 
	*
	*/
	class Ogre_Export_API SdkCamera : public Singleton<SdkCamera>
	{
	public:
		/** 获取摄像机控制器
		 *
		 * \return 
		 */
		static	SdkCamera&				getSingleton();

		/** 获取摄像器控制机
		 *
		 * \return 
		 */
		static	SdkCamera*				getSingletonPtr();
	
	public:
		/** 构造函数
		 *
		 * \return 
		 */
		SdkCamera();

		/** 析构函数
		 *
		 * \return 
		 */
		virtual ~SdkCamera();

		/** 设置摄像机
		 *
		 * \param pCamera 
		 */
		virtual	void					setCamera(Camera* pCamera);

		/** 获取摄像机
		 *
		 * \return 
		 */
		virtual Camera*					getCamera() const;

		/** 设置摄像机观察目标
		 *
		 * \param pTarget 
		 */
		virtual	void					setTarget(SceneNode* pTarget);

		/** 获取摄像机观察目标
		 *
		 * \return 
		 */
		virtual SceneNode*				getTarget() const;

		/** 设置摄像机
		 *
		 * \param yaw 
		 * \param pitch 
		 * \param dist 
		 */
		virtual void					setYawPitchDist(Radian yaw, Radian pitch, Real dist);
		
		/** 设置摄像机位置
		 *
		 * \param vPos 
		 */
		virtual void					setPosition(Vector3& vPos);

		/** 获取摄像机位置
		 *
		 * \return 
		 */
		virtual Vector3					getPosition();

		/**
		 *
		 * \param nMode 
		 */
		virtual void					setMode(int nMode);

		/**
		 *
		 * \return 
		 */
		virtual int						getMode() const;
	protected:
		Camera*							m_pCamera;
		SceneNode*						m_pTarget;
		int								m_nMode;
	};
}

#endif