#ifndef _____OgreGlobalEventSet_h_
#define _____OgreGlobalEventSet_h_

#include "OgreEventSet.h"
#include "OgreSingleton.h"

#if defined(_MSC_VER)
#	pragma warning(push)
#	pragma warning(disable : 4275)
#endif

namespace Ogre
{

	/**
	* \ingroup : OgreSystem
	*
	* \os&IDE  : Microsoft Windows XP (SP3)  &  Microsoft Visual C++ .NET 2008 & ogre1.8
	*
	* \VERSION : 1.0
	*
	* \@date   : 2012-03-16
	*
	* \Author  : CEGUI
	*
	* \Desc    : 
	*
	* \bug     : 
	*
	*/
	class Ogre_System_Export_API GlobalEventSet : public EventSet, public Singleton<GlobalEventSet>
	{
	public:
		/**
		 *
		 * \return 
		 */
		GlobalEventSet();

		/**
		 *
		 * \return 
		 */
		~GlobalEventSet();


		/**
		 *
		 * \param void 
		 * \return 
		 */
		static	GlobalEventSet&	getSingleton(void);


		/**
		 *
		 * \param void 
		 * \return 
		 */
		static	GlobalEventSet*	getSingletonPtr(void);

		/**
		 *
		 * \param name 
		 * \param args 
		 * \param eventNamespace 
		 */
		virtual void			fireEvent(const String& name, EventArgs& args, const String& eventNamespace = "");
	};
}

#if defined(_MSC_VER)
#	pragma warning(pop)
#endif

#endif
