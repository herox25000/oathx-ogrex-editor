#pragma once

namespace Ogre
{

	/**
	* \ingroup : OgreEditor
	*
	* \os&IDE  : Microsoft Windows XP (SP3)  &  Microsoft Visual C++ .NET 2008
	*
	* \VERSION : 1.0
	*
	* \date    : 2013-02-16
	*
	* \Author  : lp
	*
	* \Desc    :
	*
	* \bug     : 
	*
	* \Copyright (c) 2012 lp All rights reserved.
	*/
	class EditorDebug : public LogListener
	{
		typedef std::deque<String>	VString;
	public:
		/** ���캯��
		 *
		 * \param void 
		 * \return 
		 */
		EditorDebug(void);

		/** ��������
		 *
		 * \param void 
		 * \return 
		 */
		virtual ~EditorDebug(void);

	public:
		/**	
		 *
		 * \param message			
		 * \param lml 
		 * \param maskDebug 
		 * \param &logName 
		 * \param skipThisMessage 
		 */
		virtual void	messageLogged( const String& message, 
			LogMessageLevel lml, bool maskDebug, const String &logName, bool& skipThisMessage );

	private:
		int				m_nLine;
		VString			m_vString;
		
	};


}