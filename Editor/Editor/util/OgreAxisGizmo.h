#ifndef _____OgreAxisGizmo_H
#define _____OgreAxisGizmo_H

#include "OgreSceneManager.h"

namespace Ogre
{	
	/**
	* \ingroup : Editor
	*
	* \os&IDE  : Microsoft Windows XP (SP3)  &  Microsoft Visual C++ .NET 2008 & ogre1.8
	*
	* \VERSION : 1.0
	*
	* \@date   : 2012-02-27
	*
	* \Author  : lp
	*
	* \Desc    : 
	*
	* \bug     : 
	*
	*/
	class AxisGizmo : public Singleton<AxisGizmo>
	{
	public:
		/**
		 *
		 * \param pSceneManager 
		 * \return 
		 */
		AxisGizmo(SceneManager* pSceneManager);

		/**
		 *
		 * \return 
		 */
		virtual ~AxisGizmo();
		
		/**
		 *
		 * \param void 
		 * \return 
		 */
		static AxisGizmo&	getSingleton();

		/**
		 *
		 * \return 
		 */
		static AxisGizmo*	getSingletonPtr();
	
	public:
		/**
		 *
		 */
		virtual	void		showAxisGizmo(bool bVisible);

	protected:
		Ogre::SceneManager* m_pSceneManager;
		Ogre::SceneNode*	m_pAxisGizmo;
		
	};
}

#endif