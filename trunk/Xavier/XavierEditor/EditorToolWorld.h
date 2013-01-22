#ifndef _____EditorToolWorld_H
#define _____EditorToolWorld_H

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
	class EditorToolWorld : public EditorTool
	{
	public:
		/**
		 *
		 * \param name 
		 * \return 
		 */
		EditorToolWorld(const String& name, const String& worldName, const SceneTypeMask& typeMask, const ColourValue& clrAmbientLight,
			const Vector3& vPos, const Vector3& vLookAt, Real fYaw, Real fPitch, Real fNearClipDistance, Real fFarClipDistance, const ColourValue& background);

		/**
		 *
		 * \return 
		 */
		virtual ~EditorToolWorld();

		/**
		 *
		 * \param cx 
		 * \param cy 
		 * \return 
		 */
		virtual	bool			OnSize(int cx, int cy);
	protected:
		World*					m_pWorld;
	};
	
	struct SEditorWorldAdp : public SEditorAdp
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
	class EditorToolWorldFactory : public EditorToolFactory
	{
	public:
		/**
		 *
		 * \param name 
		 * \return 
		 */
		EditorToolWorldFactory(const String& name);

		/**
		 *
		 * \return 
		 */
		virtual ~EditorToolWorldFactory();

		/**
		 *
		 * \param seadp 
		 * \return 
		 */
		virtual	EditorTool*		createEditorTool(const SEditorAdp& seadp);
	};
}

#endif