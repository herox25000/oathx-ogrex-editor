#pragma once

#include "OgreLog.h"

/**
* \ingroup : Editor
*
* \os&IDE  : Microsoft Windows XP (SP3)  &  Microsoft Visual C++ .NET 2008 & ogre1.8
*
* \VERSION : 1.0
*
* \@date   : 2011-12-14
*
* \Author  : lp
*
* \Desc    : 
*
* \bug     : 
*
*/
class XavierLog : public Ogre::LogListener
{
public:
	/** ���캯��
	 *
	 * \param void 
	 * \return 
	 */
	XavierLog(void);

	/** ��������
	 *
	 * \param void 
	 * \return 
	 */
	virtual ~XavierLog(void);

public:
	/**	
	 *
	 * \param message			
	 * \param lml 
	 * \param maskDebug 
	 * \param &logName 
	 * \param skipThisMessage 
	 */
	virtual void	messageLogged( const Ogre::String& message, 
		Ogre::LogMessageLevel lml, bool maskDebug, const Ogre::String &logName, bool& skipThisMessage );

private:
	int				m_nLine;
};
