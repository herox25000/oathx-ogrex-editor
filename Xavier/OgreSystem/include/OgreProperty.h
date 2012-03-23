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
		static int					getTypeForValue(const short& val) 
		{
			return PROPERTY_SHORT; 
		}
		
		static int					getTypeForValue(const unsigned short& val)
		{
			return PROPERTY_UNSIGNED_SHORT; 
		}
		
		static int					getTypeForValue(const int& val)
		{
			return PROPERTY_INT;
		}
		
		static int					getTypeForValue(const unsigned int& val) 
		{
			return PROPERTY_UNSIGNED_INT;
		}

		static int					getTypeForValue(const long& val) 
		{
			return PROPERTY_LONG;
		}

		static int					getTypeForValue(const unsigned long& val)
		{
			return PROPERTY_UNSIGNED_LONG;
		}

		static int					getTypeForValue(const Ogre::Real& val)
		{ 
			return PROPERTY_REAL;
		}

		static int					getTypeForValue(const Ogre::String& val) 
		{ 
			return PROPERTY_STRING;
		}
		
		static int					getTypeForValue(const Ogre::Vector2& val) 
		{
			return PROPERTY_VECTOR2; 
		}
		
		static int					getTypeForValue(const Ogre::Vector3& val) 
		{
			return PROPERTY_VECTOR3; 
		}
		
		static int					getTypeForValue(const Ogre::Vector4& val)
		{ 
			return PROPERTY_VECTOR4; 
		}
		
		static int					getTypeForValue(const Ogre::ColourValue& val) 
		{ 
			return PROPERTY_COLOUR; 
		}
		
		static int					getTypeForValue(const bool& val) 
		{ 
			return PROPERTY_BOOL; 
		}

		static int					getTypeForValue(const Ogre::Quaternion& val)
		{
			return PROPERTY_QUATERNION;
		}

		static int					getTypeForValue(const Ogre::Matrix3& val)
		{ 
			return PROPERTY_MATRIX3; 
		}

		static int					getTypeForValue(const Ogre::Matrix4& val) 
		{ 
			return PROPERTY_MATRIX4;
		}
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
		virtual	void				addProperty(const String& name, Any Value, const String& describe, int typeProperty);

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
		template<typename T>
		void						getPropertyValue(const String& name, T& value)
		{
			Property* pProperty = getProperty(name);
			if (pProperty != NULL)
			{
				value = any_cast<T>(pProperty->getValue());
			}
		}
	protected:
		HashProperty				m_HashProperty;
	};
}

#endif