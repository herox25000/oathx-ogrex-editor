#ifndef EXPLORER_H
#define EXPLORER_H

#include "OgreString.h"

namespace Ogre
{
	/**
	* \ingroup : explorer
	*
	* \os&IDE  : Microsoft Windows XP (SP3)  &  Microsoft Visual C++ .NET 2008 & ogre1.8
	*
	* \VERSION : 1.0
	*
	* \@date   : 2011-12-15
	*
	* \Author  : lp
	*
	* \Desc    : ������
	*
	* \bug     : 
	*
	*/
	class Explorer
	{
	public:
		/** ���캯��
		 *
		 * \param sName		��Ŀ����
		 * \param sPath		��Ŀ·��
		 * \return 
		 */
		Explorer(const String& sName, const String& sPath);

		/** ��������
		 *
		 * \param void 
		 * \return 
		 */
		virtual ~Explorer(void);

	public:
		/** ������Ŀ·��
		 *
		 * \param sPath			����·��
		 */
		virtual void			setPath(const String& sPath);

		/** ��ȡ��Ŀ����·��
		 *
		 * \return 
		 */
		virtual String			getPath() const;

		/** ������Ŀ��
		 *
		 * \param sName			��Ŀ��
		 */
		virtual void			setName(const String& sName);

		/**	��ȡ��Ŀ��
		 *
		 * \return 
		 */
		virtual String			getName() const;

	protected:
		String					m_sName;
		String					m_sPath;
	}; 
}

#endif
