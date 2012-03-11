#ifndef _____OgreEditSystem_H
#define _____OgreEditSystem_H

#include "OgreSingleton.h"

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
	* \Desc    : 
	*
	* \bug     : 
	*
	*/
	class Ogre_EditSystem_Export_API EditSystem : public Singleton<EditSystem>
	{
	public:
		/** 获取编辑系统
		 *
		 * \return 
		 */
		static	EditSystem&			getSingleton();

		/** 获取编辑系统
		 *
		 * \return 
		 */
		static	EditSystem*			getSingletonPtr();

	public:
		/** construct function
		 *
		 * \param void 
		 * \return 
		 */
		EditSystem(void);

		/** deconstruct funcion
		 *
		 * \param void 
		 * \return 
		 */
		virtual ~EditSystem(void);

	public:
		/** create ogre editor system
		 *
		 * \param pluginFileName	ogre plugin config name
		 * \param resourceFileName  ogre plugin config name
		 * \return 
		 */
		virtual	bool				createSystem(const String& pluginFileName, const String& resourceFileName);

		/** destroy ogre editor system
		 *
		 */
		virtual void				destroySystem();

	protected:
		Root*						m_pRoot;	// ogre root object
	};
}

#endif
