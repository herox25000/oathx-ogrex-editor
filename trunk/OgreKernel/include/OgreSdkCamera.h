#ifndef _____OgreSdkCamera_H
#define _____OgreSdkCamera_H

#pragma once

#include "OgreKernelPrerequisites.h"
#include "OgreSingleton.h"

namespace Ogre
{
	// �����ģʽ
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
	* \Desc    : SDK ���������
	*
	* \bug     : 
	*
	*/
	class Ogre_Export_API SdkCamera : public Singleton<SdkCamera>
	{
	public:
		/** ��ȡ�����������
		 *
		 * \return 
		 */
		static	SdkCamera&				getSingleton();

		/** ��ȡ���������ƻ�
		 *
		 * \return 
		 */
		static	SdkCamera*				getSingletonPtr();
	
	public:
		/** ���캯��
		 *
		 * \return 
		 */
		SdkCamera();

		/** ��������
		 *
		 * \return 
		 */
		virtual ~SdkCamera();

		/** ���������
		 *
		 * \param pCamera 
		 */
		virtual	void					setCamera(Camera* pCamera);

		/** ��ȡ�����
		 *
		 * \return 
		 */
		virtual Camera*					getCamera() const;

		/** ����������۲�Ŀ��
		 *
		 * \param pTarget 
		 */
		virtual	void					setTarget(SceneNode* pTarget);

		/** ��ȡ������۲�Ŀ��
		 *
		 * \return 
		 */
		virtual SceneNode*				getTarget() const;

		/** ���������
		 *
		 * \param yaw 
		 * \param pitch 
		 * \param dist 
		 */
		virtual void					setYawPitchDist(Radian yaw, Radian pitch, Real dist);
		
		/** ���������λ��
		 *
		 * \param vPos 
		 */
		virtual void					setPosition(Vector3& vPos);

		/** ��ȡ�����λ��
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