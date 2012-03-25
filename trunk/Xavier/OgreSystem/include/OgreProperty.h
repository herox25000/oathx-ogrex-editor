#ifndef _____OgreProperty_H
#define _____OgreProperty_H

#include "OgreEventArgs.h"
#include "OgreEventSet.h"

namespace Ogre
{
	enum {
		PROPERTY_SHORT			= 0,
		PROPERTY_UNSIGNED_SHORT = 1,
		PROPERTY_INT			= 2,
		PROPERTY_UNSIGNED_INT	= 3,
		PROPERTY_LONG			= 4, 
		PROPERTY_UNSIGNED_LONG	= 5,
		PROPERTY_REAL			= 6,
		PROPERTY_STRING			= 7,
		PROPERTY_VECTOR2		= 8, 
		PROPERTY_VECTOR3		= 9,
		PROPERTY_VECTOR4		= 10, 
		PROPERTY_COLOUR			= 11,
		PROPERTY_BOOL			= 12,
		PROPERTY_QUATERNION		= 13, 
		PROPERTY_MATRIX3		= 14,
		PROPERTY_MATRIX4		= 15, 

		PROPERTY_UNKNOWN		= 999
	};

	/**
	* \ingroup : OgreEditSystem
	*
	* \os&IDE  : Microsoft Windows XP (SP2)  &  Microsoft Visual C++ .NET 2008
	*
	* \VERSION : 1.0
	*
	* \date    : 2012-03-12
	*
	* \Author  : lp
	*
	* \Desc    : 
	*
	* \bug     : 
	*
	*/
	class OgreSystem_Export_API Property
	{
	public:
		/**
		 *
		 * \param sName 
		 * \param val 
		 * \param describe 
		 * \return 
		 */
		Property(const String& sName, const Any& anyValue, const String& describe, int typeProperty);

		/**
		 *
		 * \return 
		 */
		virtual ~Property();

		/**
		 *
		 * \param sName 
		 */
		virtual	void				setName(const String& sName);

		/**
		 *
		 * \return 
		 */
		virtual	String				getName() const;

		/**
		 *
		 * \param describe 
		 */
		virtual	void				setDescribe(const String& describe);
		
		/**
		 *
		 * \return 
		 */
		virtual	String				getDescribe() const;
		
		/**
		 *
		 * \return 
		 */
		virtual Any&				getValue();

		/**
		 *
		 * \param anyValue 
		 */
		virtual	void				setValue(const Any& anyValue);

		/**
		 *
		 * \return 
		 */
		virtual int					getType() const;
	protected:
		String						m_decribe;
		String						m_sName;
		Any							m_anyValue;
		int							m_type;
	};

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
	class OgreSystem_Export_API PropertyEventArgs : public EventArgs
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
	typedef std::map<String, Property*> HashProperty;

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
	class OgreSystem_Export_API PropertySet : public EventSet
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
		virtual	void				addProperty(const String& name, const Any& anyValue, const String& describe, int typeProperty);

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