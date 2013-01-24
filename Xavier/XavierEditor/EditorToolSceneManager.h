#ifndef _____EditorToolSceneManager_H
#define _____EditorToolSceneManager_H

namespace Ogre
{
	/**
	* \ingroup : XavierEditor
	*
	* \os&IDE  : Microsoft Windows XP (SP3)  &  Microsoft Visual C++ .NET 2008
	*
	* \VERSION : 1.0
	*
	* \date    : 2013-01-22
	*
	* \Author  : lp
	*
	* \Desc    :
	*
	* \bug     : 
	*
	* \Copyright (c) 2012 lp All rights reserved.
	*/
	class EditorToolSceneManager : public EditorTool
	{
	public:
		static const String		DEFAULT_MAIN_CAMERA;

	public:
		/**
		 *
		 * \param name 
		 * \return 
		 */
		EditorToolSceneManager(const String& name, const String& worldName, const SceneTypeMask& typeMask, const ColourValue& clrAmbientLight,
			const Vector3& vPos, const Vector3& vLookAt, Real fYaw, Real fPitch, Real fNearClipDistance, Real fFarClipDistance, const ColourValue& background);

		/**
		 *
		 * \return 
		 */
		virtual ~EditorToolSceneManager();

				/**
		 *
		 * \return 
		 */
		virtual	SceneManager*	getSceneManager() const;
		
		/**
		 *
		 * \return 
		 */
		virtual	Camera*			getCamera() const;

		/**
		 *
		 * \return 
		 */
		virtual	Viewport*		getViewport() const;
		
		/**
		 *
		 */
		virtual	void			windowMovedOrResized();

	public:
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
		virtual	bool			OnRButtonUp(const Vector2& vPos);

		/**
		 *
		 * \param vPos 
		 * \return 
		 */
		virtual	bool			OnMouseMove(const Vector2& vPos);

		/**
		 *
		 * \param zDelta 
		 * \param vPos 
		 */
		virtual	bool			OnMouseWheel(float zDelta, const Vector2& vPos);

		/**
		 *
		 * \param cx 
		 * \param cy 
		 * \return 
		 */
		virtual	bool			OnSize(int cx, int cy);

		/**
		 *
		 * \param nChar 
		 * \param nRepCnt 
		 * \param nFlags 
		 */
		virtual bool			OnKeyDown(uint32 nChar, uint32 nRepCnt, uint32 nFlags);

		/**
		 *
		 * \param nChar 
		 * \param nRepCnt 
		 * \param nFlags 
		 */
		virtual bool			OnKeyUp(uint32 nChar, uint32 nRepCnt, uint32 nFlags);

		/**
		 *
		 * \param name 
		 * \param angValue 
		 * \param nValueType 
		 * \return 
		 */
		virtual	bool			OnPropertyChanged(const String& parentName, const String& name, Any anyValue, int nValueType);
	protected:
		/**
		 *
		 * \param vPos 
		 * \param vLookAt 
		 * \param fYaw 
		 * \param fPitch 
		 * \param fNearClipDistance 
		 * \param fFarClipDistance 
		 * \return 
		 */
		virtual	bool			configureDefault(const Vector3& vPos, const Vector3& vLookAt,
			Real fYaw, Real fPitch, Real fNearClipDistance, Real fFarClipDistance, const ColourValue& background);
	protected:
		SceneManager*			m_pSceneManager;
		Camera*					m_pCamera;
		Viewport*				m_pViewport;
		bool					m_bRMouseDown;
		Vector2					m_vRigthDwon;
	};
	
	struct SEditorSceneManagerAdp : public SEditorAdp
	{
		String					worldName;
		SceneTypeMask			typeMask;
		ColourValue				clrAmbientLight;
		Vector3					vPos;
		Vector3					vLookAt;
		float					fYaw;
		float					fPitch;
		float					fNearClipDistance;
		float					fFarClipDistance;
		ColourValue				background;
	};
	/**
	* \ingroup : XavierEditor
	*
	* \os&IDE  : Microsoft Windows XP (SP3)  &  Microsoft Visual C++ .NET 2008
	*
	* \VERSION : 1.0
	*
	* \date    : 2013-01-22
	*
	* \Author  : lp
	*
	* \Desc    :
	*
	* \bug     : 
	*
	* \Copyright (c) 2012 lp All rights reserved.
	*/
	class EditorToolSceneManagerFactory : public EditorToolFactory
	{
	public:
		/**
		 *
		 * \param name 
		 * \return 
		 */
		EditorToolSceneManagerFactory(const String& name);

		/**
		 *
		 * \return 
		 */
		virtual ~EditorToolSceneManagerFactory();

		/**
		 *
		 * \param seadp 
		 * \return 
		 */
		virtual	EditorTool*		createEditorTool(const SEditorAdp& seadp);
	};
}

#endif