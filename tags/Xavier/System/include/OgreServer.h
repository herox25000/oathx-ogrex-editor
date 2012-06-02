#ifndef _____OgreServer_H
#define _____OgreServer_H

#include "OgrePropertySet.h"

namespace Ogre
{
;

	/**
	* \ingroup : System
	*
	* \os&IDE  : Microsoft Windows XP (SP3)  &  Microsoft Visual C++ .NET 2008 & ogre1.8
	*
	* \VERSION : 1.0
	*
	* \@date   : 2012-04-06
	*
	* \Author  : lp
	*
	* \Desc    : ��������ӿ�
	*
	* \bug     : 
	*
	*/
	class Ogre_System_Export_API Server : public PropertySet
	{
	public:
		/** ���캯��
		 *
		 * \param typeName	ָ���÷�����
		 * \return 
		 */
		Server(const String& typeName);

		/** ��������
		 *
		 * \return 
		 */
		virtual ~Server();

	public:
		/** ��ȡ������
		 *
		 * \return 
		 */
		virtual	String				getTypeName() const;

		/** ���÷�����
		 *
		 * \param name 
		 */
		virtual void				setTypeName(const String& typeName);

		/**
		 *
		 */
		virtual bool				load();

		/**
		 *
		 */
		virtual void				unload();

	protected:
		String						m_typeName;
	};

	// ���񴴽���������ṹ
	struct SSAdp
	{
		String						typeName;		// the server type name
		String						depServerName;	// dependencie server name
	};

	/**
	* \ingroup : System
	*
	* \os&IDE  : Microsoft Windows XP (SP3)  &  Microsoft Visual C++ .NET 2008 & ogre1.8
	*
	* \VERSION : 1.0
	*
	* \@date   : 2012-04-06
	*
	* \Author  : lp
	*
	* \Desc    : ���񴴽�����
	*
	* \bug     : 
	*
	*/
	class Ogre_System_Export_API ServerFactory
	{
	public:
		static const String		FactoryTypeName;

		/** ���캯��
		 *
		 * \return 
		 */
		ServerFactory();

		/** ��������
		 *
		 * \return 
		 */
		virtual ~ServerFactory();

	public:
		/** ��ȡ������
		 *
		 * \return 
		 */
		virtual String			getTypeName() const = 0;
	
		/** ��������
		 *
		 * \param pAdp	�����������
		 * \return 
		 */
		virtual Server*			createServer(const SSAdp& ssadp) = 0;
	};
}

#endif