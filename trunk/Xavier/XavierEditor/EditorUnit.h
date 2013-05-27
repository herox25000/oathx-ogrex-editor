#ifndef _____EditorUnit_H
#define _____EditorUnit_H

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
	* \date    : 2013-05-25
	*
	* \Author  : lp
	*
	* \Desc    : 
	*
	* \bug     : 
	*
	* \Copyright (c) 2012 lp All rights reserved.
	*/
	class EditorUnit : public EditorPlugin
	{
	public:
		/**
		 *
		 * \param pluginName 
		 * \param szFileName 
		 * \param vPos 
		 * \param vScale 
		 * \param fDegree 
		 * \return 
		 */
		EditorUnit(const String& pluginName, const String& szFileName,
			const Vector3& vPos, const Vector3& vScale, float fDegree);

		/**
		 *
		 * \return 
		 */
		virtual ~EditorUnit();

	public:
		/**
		 *
		 * \param vPos 
		 * \return 
		 */
		virtual	bool			OnSetFocus();

		/**
		 *
		 * \param vPos 
		 * \return 
		 */
		virtual	bool			OnLoseFocus();
		
		/**
		 *
		 * \param vPos 
		 * \return 
		 */
		virtual bool			OnLButtonDown(const Vector2& vPos);

		/**
		 *
		 * \param vPos 
		 * \return 
		 */
		virtual	bool			OnMouseMove(const Vector2& vPos);

		/**
		 *
		 * \param vPos 
		 * \return 
		 */
		virtual	bool			OnLButtonUp(const Vector2& vPos);

		/**
		 *
		 * \param nChar 
		 * \param nRepCnt 
		 * \param nFlags 
		 * \return 
		 */
		virtual	bool			OnKeyDown(uint32 nChar, uint32 nRepCnt, uint32 nFlags);

		/**
		 *
		 * \param nChar 
		 * \param nRepCnt 
		 * \param nFlags 
		 * \return 
		 */
		virtual	bool			OnKeyUp(uint32 nChar, uint32 nRepCnt, uint32 nFlags);
	protected:
		/**
		 *
		 * \param name 
		 * \param szFileName 
		 * \param vPos 
		 * \param vScale 
		 * \param fDegree 
		 * \return 
		 */
		virtual bool			configure(const String& szFileName,
			const Vector3& vPos, const Vector3& vScale, float fDegree);

	protected:
		Entity*					m_pEntity;
		Entity*					m_pAxis;
		SceneManager*			m_pSceneManager;
		SceneNode*				m_pNode;
		SceneNode*				m_pAxisNode;
		bool					m_bLDown;
		int						m_nRot;
	};

	struct SEditorUnitAdp : public SEditorPluginAdp
	{
		String				szFileName;
		Vector3				vPos;
		float				fDegree;
		Vector3				vScale;
	};

	/**
	* \ingroup : XavierEditor
	*
	* \os&IDE  : Microsoft Windows XP (SP3)  &  Microsoft Visual C++ .NET 2008
	*
	* \VERSION : 1.0
	*
	* \date    : 2013-05-25
	*
	* \Author  : lp
	*
	* \Desc    : 
	*
	* \bug     : 
	*
	* \Copyright (c) 2012 lp All rights reserved.
	*/
	class EditorUnitFactory : public EditorPluginFactory
	{
	public:
		/**
		 *
		 * \param factoryName 
		 * \return 
		 */
		EditorUnitFactory(const String& factoryName);

		/**
		 *
		 * \return 
		 */
		virtual ~EditorUnitFactory();

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