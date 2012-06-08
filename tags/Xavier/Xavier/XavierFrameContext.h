#ifndef _____XavierFrameContext_H
#define _____XavierFrameContext_H

#include "OgreFrameListener.h"

enum{
	EDIT_STATE_INVALID,
	EDIT_STATE_DEFORM,
	EDIT_STATE_PAINT,
	EDIT_STATE_ADDLAYER,
};

namespace Ogre
{
	class Terrain;

	/**
	* \ingroup : Xavier
	*
	* \os&IDE  : Microsoft Windows XP (SP3)  &  Microsoft Visual C++ .NET 2008 & ogre1.8
	*
	* \VERSION : 1.0
	*
	* \@date   : 2012-05-14
	*
	* \Author  : lp
	*
	* \Desc    : 
	*
	* \bug     : 
	*
	*/
	class XavierFrameContext : public Ogre::FrameListener
	{
	public:
		/**
		 *
		 * \param void 
		 * \return 
		 */
		XavierFrameContext(void);

		/**
		 *
		 * \param void 
		 * \return 
		 */
		virtual ~XavierFrameContext(void);

		/**
		 *
		 * \param evt 
		 * \return 
		 */
		virtual bool				frameStarted(const Ogre::FrameEvent& evt);
			
		/**
		 *
		 * \param evt 
		 * \return 
		 */
		virtual bool				frameRenderingQueued(const Ogre::FrameEvent& evt);

		/**
		 *
		 * \param evt 
		 * \return 
		 */
		virtual bool				frameEnded(const Ogre::FrameEvent& evt);

	public:
		/** ÇÐ»»±à¼­×´Ì¬
		 *
		 * \param nState 
		 */
		virtual	void				changeState(int nState);

	protected:
		int							m_nState;
	};
}

#endif