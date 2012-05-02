#ifndef _____OgreServerCamera_H
#define _____OgreServerCamera_H

#include "OgreServer.h"

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
	* \ingroup : System
	*
	* \os&IDE  : Microsoft Windows XP (SP3)  &  Microsoft Visual C++ .NET 2008 & ogre1.8
	*
	* \VERSION : 1.0
	*
	* \@date   : 2012-04-16
	*
	* \Author  : lp
	*
	* \Desc    : 
	*
	* \bug     : 
	*
	*/
	class Ogre_System_Export_API CameraServer : public Server
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
		CameraServer(const String& typeName, const String& name, int nMode, WorldSpaceServer* pWorldSpace, const Vector3& vPos, const Vector3& vLookAt,
			Real fYaw, Real fPitch, Real fNearClipDistance, Real fFarClipDistance);
		
		/**
		 *
		 * \param void 
		 * \return 
		 */
		virtual ~CameraServer(void);

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
	};

	// �������������
	struct SSdkCameraServerAdp : public SSAdp
	{
		String						name;
		Vector3						vPos;
		Vector3						vLookAt;
		Real						fYaw;
		Real						fPitch;
		Real						fNearClipDistance;
		float						fFarClipDistance;
		int							nMode;
	};

	/**
	* \ingroup : System
	*
	* \os&IDE  : Microsoft Windows XP (SP3)  &  Microsoft Visual C++ .NET 2008 & ogre1.8
	*
	* \VERSION : 1.0
	*
	* \@date   : 2012-04-16
	*
	* \Author  : lp
	*
	* \Desc    : 
	*
	* \bug     : 
	*
	*/
	class Ogre_System_Export_API CameraServerFactory : public ServerFactory
	{
	public:
		static const String			FactoryTypeName;

		/** ���캯��
		 *
		 * \return 
		 */
		CameraServerFactory();

		/** ��������
		 *
		 * \return 
		 */
		virtual ~CameraServerFactory();

		/**
		 *
		 * \return 
		 */
		virtual String				getTypeName() const;

		/**
		 *
		 * \param ssadp 
		 * \return 
		 */
		virtual Server*				createServer(const SSAdp& ssadp);
	};
}

#endif