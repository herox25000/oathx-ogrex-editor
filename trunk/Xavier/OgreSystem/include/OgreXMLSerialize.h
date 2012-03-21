#ifndef _____OgreXMLSerialize_H
#define _____OgreXMLSerialize_H

#include "OgreProperty.h"
#include "tinyxml.h"

namespace Ogre
{
	/**
	* \ingroup : OgreAppEdit
	*
	* \os&IDE  : Microsoft Windows XP (SP3)  &  Microsoft Visual C++ .NET 2008 & ogre1.8
	*
	* \VERSION : 1.0
	*
	* \@date   : 2012-03-21
	*
	* \Author  : lp
	*
	* \Desc    : 
	*
	* \bug     : 
	*
	*/
	class OgreSystem_Export_API XMLSerialize : public PropertySet
	{
	public:
		/** ���캯��
		 *
		 */
		XMLSerialize();

		/**
		 *
		 * \param void 
		 * \return 
		 */
		virtual ~XMLSerialize(void);

	public:
		/** �����ĵ�
		 *
		 * \param sPath		�ĵ�·��
		 * \param sName		�ĵ�����
		 * \return 
		 */
		virtual	bool			createSerialize(const String& sPath, const String& sName);

		/** ��ȡ·��
		 *
		 * \return 
		 */
		virtual String			getPath() const;

		/** ��ȡ����
		 *
		 * \return 
		 */
		virtual String			getName() const;

		/** ��ȡ����·��
		 *
		 * \return 
		 */
		virtual String			getPathName() const;

		/** �����ļ�
		 *
		 * \param sPathName 
		 * \return 
		 */
		virtual bool			load(const String& sPathName);

		/** ж���ļ�
		 *
		 */
		virtual void			unload();
	protected:
		// �ĵ�
		TiXmlDocument*			m_pDocument;
		String					m_sPath;
		String					m_sName;
	};
}

#endif
