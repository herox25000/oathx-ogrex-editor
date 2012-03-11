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
	* \Desc    : 摄像机编辑器
	*
	* \bug     : 
	*
	*/
	class Ogre_EditSystem_Export_API CameraEditor : public BaseEditor
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

		/**
		 *
		 * \return 
		 */
		virtual Camera*				getCamera() const;

	protected:
		Camera*						m_pCamera;
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
	class Ogre_EditSystem_Export_API CameraEditorFactory : public BaseEditorFactory
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
