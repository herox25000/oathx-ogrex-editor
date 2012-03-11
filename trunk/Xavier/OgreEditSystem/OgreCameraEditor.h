#ifndef _____OgreCameraEditor_H
#define _____OgreCameraEditor_H

#include "OgreBaseEditor.h"

namespace Ogre
{
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
	class Ogre_EditSystem_Export_API CameraEditor : public BaseEditor
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

		/**
		 *
		 * \return 
		 */
		virtual Camera*				getCamera() const;

	protected:
		Camera*						m_pCamera;
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
	class Ogre_EditSystem_Export_API CameraEditorFactory : public BaseEditorFactory
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
