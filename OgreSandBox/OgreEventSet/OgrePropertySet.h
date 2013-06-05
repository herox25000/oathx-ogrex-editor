#ifndef _____OgrePropertySet_H
#define _____OgrePropertySet_H

#include "OgreProperty.h"

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
	* \Desc    : 属性事件
	*
	* \bug     : 
	*
	*/
	class Ogre_EventSet_Export_API PropertyEventArgs : public EventArgs
	{
	public:
		/**
		 *
		 * \param pProperty 
		 * \return 
		 */
		PropertyEventArgs(Property* pProperty)
			:pProperty(pProperty)
		{

		}

		/**
		 *
		 * \return 
		 */
		virtual ~PropertyEventArgs()
		{

		}
		
		// 属性
		Property*					pProperty;
	};
	
	// 属性列表
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
	* \Desc    : 
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
		
	public:
		/**
		 *
		 * \param sName 
		 * \param describe 
		 * \return 
		 */
		PropertySet();

		/**
		 *
		 * \return 
		 */
		virtual ~PropertySet();

		/**
		 *
		 * \param name 
		 * \param Value 
		 * \param describe 
		 */
		virtual	void				addProperty(const String& name, Any anyValue, 
			 int typeProperty, bool bWrite=true, const String& describe="null");

		/**
		 *
		 * \param name 
		 */
		virtual void				delProperty(const String& name);

		/**
		 *
		 * \param name 
		 * \return 
		 */
		virtual Property*			getProperty(const String& name);

		/**
		 *
		 * \param name 
		 * \param anyValue 
		 */
		virtual	void				setPropertyValue(const String& name, const Any& anyValue);

		/**
		 *
		 * \param name 
		 * \return 
		 */
		virtual Any&				getPropertyValue(const String& name);

		/**
		 *
		 * \return 
		 */
		virtual HashProperty&		getHashProperty();
		
		/**
		 *
		 * \return 
		 */
		virtual HashPropertyIter	getHashPropertyIter();
	public:
		/**
		 *
		 * \param name 
		 * \param value 
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

		/**
		 *
		 * \param name 
		 * \param value 
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