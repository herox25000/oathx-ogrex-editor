#ifndef _____EditorCamera_H
#define _____EditorCamera_H

#include "EditorPlugin.h"

namespace Ogre
{
	/**
	* \ingroup : XavierEditor
	*
	* \os&IDE  : Microsoft Windows XP (SP3)  &  Microsoft Visual C++ .NET 2008
	*
	* \VERSION : 1.0
	*
	* \date    : 2013-01-24
	*
	* \Author  : lp
	*
	* \Desc    :
	*
	* \bug     : 
	*
	* \Copyright (c) 2012 lp All rights reserved.
	*/
	class EditorCamera : public EditorPlugin
	{
	public:
		/**
		 *
		 * \param pluginName 
		 * \param vPos 
		 * \param q 
		 * \param fNearClipDistance 
		 * \param fFarClipDistance 
		 * \param fFov 
		 * \param AutoAspectRatio 
		 * \param nQueryFlags 
		 * \return 
		 */
		EditorCamera(const String& pluginName, const Vector3& vPos, const Quaternion& q,  
			float fNearClipDistance, float fFarClipDistance, float fFov, bool bAutoAspectRatio, 
			uint32 nQueryFlags);

		/**
		 *
		 * \return 
		 */
		virtual ~EditorCamera();

		/**
		 *
		 * \return 
		 */
		virtual	Camera*			getCamera() const;
	public:
		/**
		 *
		 * \param parentName 
		 * \param name 
		 * \param anyValue 
		 * \param nType 
		 * \return 
		 */
		virtual	bool			OnPropertyChanged(const String& parentName, const String& name, 
			const Any& anyValue, int nType);

		/**
		 *
		 * \param vPos 
		 * \return 
		 */
		virtual	bool			OnRButtonDown(const Vector2& vPos);

		/**
		 *
		 * \param vPos 
		 * \return 
		 */
		virtual bool			OnRButtonUp(const Vector2& vPos);

		/**
		 *
		 * \param vPos 
		 * \return 
		 */
		virtual	bool			OnMouseMove(const Vector2& vPos);

		/**
		 *
		 * \param fzDelta 
		 * \param vPos 
		 * \return 
		 */
		virtual	bool			OnMouseWheel(float fzDelta, const Vector2& vPos);
	protected:
		/**
		 *
		 * \param vPos 
		 * \param q 
		 * \param fNearClipDistance 
		 * \param fFarClipDistance 
		 * \param fFov 
		 * \param bAutoAspectRatio 
		 * \param nQueryFlags 
		 */
		virtual bool			configure(const String& name, const Vector3& vPos, const Quaternion& q,  
			float fNearClipDistance, float fFarClipDistance, float fFov, bool bAutoAspectRatio, 
			uint32 nQueryFlags);
	protected:
		Camera*					m_pCamera;
		bool					m_bRMouseDown;
		Vector2					m_vRigthDwon;
	};

	// …„œÒª˙±‡º≠  ≈‰≤Œ ˝
	struct SEditorCamearAdp : public SEditorPluginAdp
	{
		Vector3					vPos;
		Quaternion				q;  
		float					fNearClipDistance; 
		float					fFarClipDistance; 
		float					fFov; 
		bool					bAutoAspectRatio; 
		uint32					nQueryFlags;
	};

	/**
	* \ingroup : XavierEditor
	*
	* \os&IDE  : Microsoft Windows XP (SP2)  &  Microsoft Visual C++ .NET 2008
	*
	* \VERSION : 1.0
	*
	* \date    : 2013-01-24
	*
	* \Author  : lp
	*
	* \Desc    : 
	*
	* \bug     : 
	*
	* \Copyright (c) 2012 lp All rights reserved.
	*/
	class EditorCameraFactory : public EditorPluginFactory
	{
	public:
		/**
		 *
		 * \param factoryName 
		 * \return 
		 */
		EditorCameraFactory(const String& factoryName);

		/**
		 *
		 * \return 
		 */
		virtual ~EditorCameraFactory();

		/**
		 *
		 * \param ssadp 
		 * \param pParent 
		 * \return 
		 */
		virtual	EditorPlugin*		createPlugin(const SEditorPluginAdp& ssadp, EditorPlugin* pParent);
	};
}

#endif