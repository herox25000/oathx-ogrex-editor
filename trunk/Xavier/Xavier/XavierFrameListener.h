#pragma once

#include "OgreFrameListener.h"

namespace Ogre
{
	/**
	* \ingroup : Xavier
	*
	* \os&IDE  : Microsoft Windows XP (SP3)  &  Microsoft Visual C++ .NET 2008 & ogre1.8
	*
	* \VERSION : 1.0
	*
	* \@date   : 2012-03-10
	*
	* \Author  : lp
	*
	* \Desc    : ±à¼­Æ÷äÖÈ¾¼àÌýÆ÷
	*
	* \bug     : 
	*
	*/
	class XavierFrameListener : public FrameListener
	{
	public:
		/**
		 *
		 * \param void 
		 * \return 
		 */
		XavierFrameListener(void);

		/**
		 *
		 * \param void 
		 * \return 
		 */
		virtual ~XavierFrameListener(void);

		/**
		 *
		 * \param evt 
		 * \return 
		 */
		virtual bool	frameStarted(const FrameEvent& evt);
		
		/**
		 *
		 * \param evt 
		 * \return 
		 */
		virtual bool	frameRenderingQueued(const FrameEvent& evt);

        /**
         *
         * \param evt 
         * \return 
         */
        virtual bool	frameEnded(const FrameEvent& evt);
	};
}

