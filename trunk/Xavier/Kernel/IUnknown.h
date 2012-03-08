#ifndef _____IUnknown_H
#define _____IUnknown_H

namespace Xavier
{
	/**
	* \ingroup : Kernel
	*
	* \os&IDE  : Microsoft Windows XP (SP3)  &  Microsoft Visual C++ .NET 2008 & ogre1.8
	*
	* \VERSION : 1.0
	*
	* \@date   : 2012-03-08
	*
	* \Author  : lp
	*
	* \Desc    : 
	*
	* \bug     : 
	*
	*/
	class IUnknown
	{
	public:
		/**
		 *
		 * \return 
		 */
		IUnknown()
		{

		}

		/**
		 *
		 * \return 
		 */
		virtual ~IUnknown()
		{

		}

		/**
		 *
		 * \return 
		 */
		virtual	int			drop()
		{
			return 0;
		}

		/**
		 *
		 * \return 
		 */
		virtual int			grab()
		{
			return 0;
		}
	};
}

#endif