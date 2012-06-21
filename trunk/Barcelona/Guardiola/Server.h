#ifndef _____Server_H
#define _____Server_H

namespace Barcelona
{
	// �����������
	typedef struct SSAdp{
		Ogre::String	defPopertyFile;		// ���Զ����ļ�
		Ogre::String	typeName;			// ��������
		Ogre::String	depServerName;		// ������������
	}*SSAdpPtr;

	/**
	* \ingroup : Guardiola
	*
	* \os&IDE  : Microsoft Windows XP (SP2)  &  Microsoft Visual C++ .NET 2008
	*
	* \VERSION : 1.0
	*
	* \date    : 2012-06-22
	*
	* \Author  : lp
	*
	* \Desc    : ��������������Ϸ��λ�Ļ�����
	*
	* \bug     : 
	*
	*/
	class GuardiolaDLL_Export_API Server : public Ogre::PropertySet
	{		
	public:
		/** ���캯��
		 *
		 * \param typeName	������������
		 * \return 
		 */
		Server(const Ogre::String& typeName, const SSAdp& ssadp);

		/** ��������
		 *
		 * \param void 
		 * \return 
		 */
		virtual ~Server(void);

		/** ��ȡ����������
		 *
		 * \return 
		 */
		virtual Ogre::String		getTypeName() const;

		/** ���÷���������
		 *
		 * \param typeName 
		 */
		virtual	void				setTypeName(const Ogre::String& typeName);
		
		/** ���ط������Զ����ļ�
		 *
		 * \param path 
		 */
		virtual	void				loadProperty(const Ogre::String& path);

		/** ж����������
		 *
		 */
		virtual	void				unloadProperty();
	protected:
		Ogre::String				m_typeName;
	};

	/**
	* \ingroup : Guardiola
	*
	* \os&IDE  : Microsoft Windows XP (SP2)  &  Microsoft Visual C++ .NET 2008
	*
	* \VERSION : 1.0
	*
	* \date    : 2012-06-22
	*
	* \Author  : lp
	*
	* \Desc    : ���񹤳�
	*
	* \bug     : 
	*
	*/
	class GuardiolaDLL_Export_API ServerFactory
	{
	public:
		// ���񹤳�������
		static const Ogre::String	FactoryTypeName;

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

		/** ��ȡ����������
		 *
		 * \return 
		 */
		virtual Ogre::String		getTypeName() const;

		/** ����һ������
		 *
		 * \param ssadp			�����������
		 * \return 
		 */
		virtual Server*				createServer(const SSAdp& ssadp);
	};
}

#endif
