#ifndef _____OgrePropertySet_H
#define _____OgrePropertySet_H

namespace Ogre
{
	/**
	* \ingroup : OgreEditSystem
	*
	* \os&IDE  : Microsoft Windows XP (SP2)  &  Microsoft Visual C++ .NET 2008
	*
	* \VERSION : 1.0
	*
	* \date    : 2012-03-13
	*
	* \Author  : lp
	*
	* \Desc    : �����¼�����ĳ���Ըı�ʱ���͸��¼�
	*
	* \bug     : 
	*
	*/
	class Ogre_EventSet_Export_API PropertyEventArgs : public EventArgs
	{
	public:
		/** ���캯��
		 *
		 * \param pProperty		�������¼������Զ���
		 * \return 
		 */
		PropertyEventArgs(Property* pProperty)
			:pProperty(pProperty)
		{

		}

		/** ��������
		 *
		 * \return 
		 */
		virtual ~PropertyEventArgs()
		{

		}
		
		// ����
		Property*					pProperty;
	};
	
	// �����б�
	typedef HashMap<String, Property*>		HashProperty;
	typedef MapIterator<HashProperty>		HashPropertyIter;

	/**
	* \ingroup : OgreEditSystem
	*
	* \os&IDE  : Microsoft Windows XP (SP3)  &  Microsoft Visual C++ .NET 2008 & ogre1.8
	*
	* \VERSION : 1.0
	*
	* \@date   : 2012-03-12
	*
	* \Author  : lp
	*
	* \Desc    : �����¼���
	*
	* \bug     : 
	*
	*/
	class Ogre_EventSet_Export_API PropertySet : public EventSet
	{
	public:
		// Namespace for global events
		static const String			EventNamespace;
		// add property
		static const String			EventAddProperty;
		// change value
		static const String			EventValueChanged;
		// del property
		static const String			EventDelProperty;
	public:
		/** ���캯��
		 *
		 * \return 
		 */
		PropertySet();

		/** ��������
		 *
		 * \return 
		 */
		virtual ~PropertySet();

		/** ���һ���µ�����
		 *
		 * \param name			��������
		 * \param Value			���Ա���ֵ
		 * \param describe		��������
		 * \param typeProperty	��������
		 * \param bWrite		�Ƿ��д��
		 * \param describe		���Ա���
		 */
		virtual	void				addProperty(const String& name, Any anyValue, 
			 int typeProperty, bool bWrite=true, const String& describe="null");

		/** ɾ��ָ������
		 *
		 * \param name			��������
		 */
		virtual void				delProperty(const String& name);

		/** ��ȡ���Զ���
		 *
		 * \param name			��������
		 * \return 
		 */
		virtual Property*			getProperty(const String& name);

		/** �������Ա���
		 *
		 * \param name			��������
		 * \param anyValue		���Ա���ֵ
		 */
		virtual	void				setPropertyValue(const String& name, const Any& anyValue);

		/** ��ȡ���Ա���ֵ
		 *
		 * \param name			��������
		 * \return 
		 */
		virtual Any&				getPropertyValue(const String& name);

		/** ��ȡ���Ա�����
		 *
		 * \return 
		 */
		virtual HashProperty&		getHashProperty();

		/** ��ȡ���Ա���������
		 *
		 * \return 
		 */
		virtual HashPropertyIter	getHashPropertyIter();

		/** �����������
		 *
		 */
		virtual	void				clearProperty();
	public:
		/** ��ȡ���Ա���ֵ
		 *
		 * \param name		��������
		 * \param value		���ر���ֵ
		 */
		template<typename T>
		void						getPropertyValue(const String& name, T& anyValue)
		{
			Property* pProperty = getProperty(name);
			if (pProperty != NULL)
			{
				try {
					anyValue = any_cast<T>(pProperty->getValue());
				}catch(Exception& e) {
					TKLogEvent(e.getFullDescription(), LML_CRITICAL);
				}
			}
			else
			{
				TKLogEvent("error: can't find property " + name);
			}
		}

		/** �������Ա���ֵ
		 *
		 * \param name		��������
		 * \param value		���Ա���ֵ
		 */
		template<typename T>
		void						setPropertyValue(const String& name, const T& anyValue)
		{
			Property* pProperty = getProperty(name);
			if (pProperty != NULL)
			{
				try {
					pProperty->setValue(Any(anyValue));
					
					PropertyEventArgs args(pProperty);
					fireEvent(EventValueChanged, args, EventNamespace);

				}catch(Exception& e) {
					TKLogEvent(e.getFullDescription(), LML_CRITICAL);
				}
			}
			else
			{
				TKLogEvent("error: can't find property " + name, LML_CRITICAL);
			}
		}
	protected:
		HashProperty				m_HashProperty;
	};
}

#endif