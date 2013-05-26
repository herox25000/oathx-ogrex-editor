#ifndef _____EditorGizmo_H
#define _____EditorGizmo_H

namespace Ogre
{
	/**
	* \ingroup : XavierEditor
	*
	* \os&IDE  : Microsoft Windows XP (SP3)  &  Microsoft Visual C++ .NET 2008
	*
	* \VERSION : 1.0
	*
	* \date    : 2013-05-27
	*
	* \Author  : lp
	*
	* \Desc    : 
	*
	* \bug     : 
	*
	* \Copyright (c) 2012 lp All rights reserved.
	*/
	class Grizmo : public Singleton<Grizmo>
	{
	public:
		/**
		 *
		 * \return 
		 */
		static	Grizmo&			getSingleton();

		/**
		 *
		 * \return 
		 */
		static	Grizmo*			getSingletonPtr();
	public:
		/**
		 *
		 * \param pSceneManager 
		 * \param szMeshFile 
		 * \param vPos 
		 * \param vScale 
		 * \return 
		 */
		Grizmo(SceneManager* pSceneManager, const String& szMeshFile, 
			const Vector3& vPos, const Vector3& vScale);

		/**
		 *
		 * \return 
		 */
		virtual ~Grizmo();

		/**
		 *
		 */
		virtual	void			show(SceneNode* pParent);

		/**
		 *
		 */
		virtual	void			hide(SceneNode* pParent);
	protected:
		/**
		 *
		 * \param szFileName 
		 * \param vPos 
		 * \param vScale 
		 * \return 
		 */
		virtual bool			configure(const String& szFileName,
			const Vector3& vPos, const Vector3& vScale);
	protected:
		Entity*					m_pEntity;
		SceneManager*			m_pSceneManager;
		SceneNode*				m_pNode;
	};
}

#endif