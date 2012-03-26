#ifndef _____OgreCameraEditor_H
#define _____OgreCameraEditor_H

#include "OgreBaseEditor.h"

namespace Ogre
{
	// �����ģʽ
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
	* \Desc    : ������༭��
	*
	* \bug     : 
	*
	*/
	class OgreAppEdit_Export_API CameraEditor : public BaseEditor
	{
	public:
		/** ���캯��
		 *
		 * \param vPos				�����λ��
		 * \param vLookAt			�۲��
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

		/** ��ȡ�����
		 *
		 * \return 
		 */
		virtual Camera*				getCamera() const;
		
		/** ���������
		 *
		 * \param pCamera 
		 */
		virtual void				setCamera(Camera* pCamera);

		/** ���ù۲�Ŀ��
		 *
		 * \param pTarget 
		 */
		virtual void				setTarget(SceneNode* pTarget);

		/** ��ȡĿ��
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

		/**
		 *
		 * \param args 
		 */
		virtual bool				onPropertyChanaged(const EventArgs& args);
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

	// �������������
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
	* \Desc    : ������༭����
	*
	* \bug     : 
	*
	*/
	class OgreAppEdit_Export_API CameraEditorFactory : public BaseEditorFactory
	{
	public:
		/** ���캯��
		 *
		 * \return 
		 */
		CameraEditorFactory();

		/** ��������
		 *
		 * \return 
		 */
		virtual ~CameraEditorFactory();

		/** ����
		 *
		 * \param pm 
		 * \return 
		 */
		virtual BaseEditor*				create(const SBaseCreateParam* pm);
	};
}

#endif
