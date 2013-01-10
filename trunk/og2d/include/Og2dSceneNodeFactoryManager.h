#ifndef _____Og2dSceneNodeFactoryManager_H
#define _____Og2dSceneNodeFactoryManager_H

#include "Og2dSingleton.h"
#include "Og2dSceneNodeFactory.h"

namespace Og2d
{
	typedef map<String, SceneNodeFactory*>::type SceneNodeFactoryRegister;

	/**
	* \ingroup : Og2d
	*
	* \os&IDE  : Microsoft Windows XP (SP2)  &  Microsoft Visual C++ .NET 2008
	*
	* \VERSION : 1.0
	*
	* \date    : 2013-01-10
	*
	* \Author  : lp
	*
	* \Desc    : 
	*
	* \bug     : 
	*
	* \Copyright (c) 2012-2013 lp All rights reserved.
	*/
	class Og2d_Export_API SceneNodeFactoryManager : public Singleton<SceneNodeFactoryManager>
	{
	public:
		/**
		 *
		 * \return 
		 */
		static SceneNodeFactoryManager&	getSingleton();

		/**
		 *
		 * \return 
		 */
		static SceneNodeFactoryManager*	getSingletonPtr();

	public:
		/**
		 *
		 * \return 
		 */
		SceneNodeFactoryManager();

		/**
		 *
		 * \return 
		 */
		virtual ~SceneNodeFactoryManager();

		/**
		 *
		 * \param pFactory 
		 * \return 
		 */
		virtual	bool					registerSceneNodeFactory(SceneNodeFactory* pFactory);

		/**
		 *
		 * \param name 
		 * \return 
		 */
		virtual	SceneNodeFactory*		getSceneNodeFactory(const String& name);

		/**
		 *
		 * \param pFactory 
		 */
		virtual	void					unregisterSceneNodeFactory(SceneNodeFactory* pFactory);
	protected:
		SceneNodeFactoryRegister		m_SceneNodeFactoryRegister;
	};
}

#endif