#include "StdAfx.h"
#include "XavierFrameContext.h"

using namespace Ogre;

/**
 *
 * \param void 
 * \return 
 */
XavierFrameContext::XavierFrameContext(void) : m_nState(EDIT_STATE_INVALID)
{
}

/**
 *
 * \param void 
 * \return 
 */
XavierFrameContext::~XavierFrameContext(void)
{
}

/**
 *
 * \param evt 
 * \return 
 */
bool	XavierFrameContext::frameStarted(const FrameEvent& evt)
{
	return true;
}

/**
 *
 * \param evt 
 * \return 
 */
bool	XavierFrameContext::frameRenderingQueued(const FrameEvent& evt)
{
	return true;
}

/**
 *
 * \param evt 
 * \return 
 */
bool	XavierFrameContext::frameEnded(const FrameEvent& evt)
{
	return true;
}

/**
 *
 * \param nState 
 */
void	XavierFrameContext::changeState(int nState)
{
	m_nState = nState;
}
