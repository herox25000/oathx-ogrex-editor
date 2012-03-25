#include "OgreSystemPrerequisites.h"
#include "OgreProperty.h"
#include "Ogre.h"

namespace Ogre
{
	/**
	 *
	 * \param sName 
	 * \param anyValue 
	 * \param describe 
	 * \return 
	 */
	Property::Property(const String& sName, const Any& anyValue, const String& describe, int typeProperty, bool bWrite)
		:m_decribe(describe), m_sName(sName), m_anyValue(anyValue), m_type(typeProperty), m_bWrite(bWrite)
	{

	}

	/**
	 *
	 * \return 
	 */
	Property::~Property()
	{

	}

	/**
	 *
	 * \return 
	 */
	int				Property::getType() const
	{
		return m_type;
	}

	/**
	 *
	 * \param sName 
	 */
	void			Property::setName(const String& sName)
	{
		m_sName = sName;
	}

	/**
	 *
	 * \return 
	 */
	String			Property::getName() const
	{
		return m_sName;
	}

	/**
	 *
	 * \param describe 
	 */
	void			Property::setDescribe(const String& describe)
	{
		m_decribe = describe;
	}

	/**
	 *
	 * \return 
	 */
	String			Property::getDescribe() const
	{
		return m_decribe;
	}

	/**
	 *
	 * \param anyValue 
	 */
	void			Property::setValue(const Any& anyValue)
	{
		m_anyValue = anyValue;
	}

	/**
	 *
	 * \return 
	 */
	Any&			Property::getValue()
	{
		return m_anyValue;
	}

	/**
	 *
	 * \return 
	 */
	bool			Property::canWrite() const
	{
		return m_bWrite;
	}

	// event name
	const String	PropertySet::EventNamespace		=	"PropertySet";
	const String	PropertySet::EventAddProperty	=	"AddProperty";
	const String	PropertySet::EventValueChanged	=	"ValueChanged";

	/**
	 *
	 * \param sName 
	 * \param describe 
	 * \return 
	 */
	PropertySet::PropertySet()
	{

	}

	/**
	 *
	 * \return 
	 */
	PropertySet::~PropertySet()
	{
		HashProperty::iterator it = m_HashProperty.begin();
		while( it != m_HashProperty.end() )
		{
			delete it->second; it = m_HashProperty.erase(it);
		}
	}

	/**
	 *
	 * \param name 
	 * \param Value 
	 * \param describe 
	 */
	void			PropertySet::addProperty(const String& name, const Any& anyValue, const String& describe, 
		int typeProperty, bool bWrite/* =true */)
	{
		HashProperty::iterator it = m_HashProperty.find(name);
		if ( it == m_HashProperty.end() )
		{
			m_HashProperty[name] = new Property(name, anyValue, describe, typeProperty, bWrite);
			
			PropertyEventArgs args(m_HashProperty[name]);

			fireEvent(EventAddProperty, args, EventNamespace);
		}
	}

	/**
	 *
	 * \param name 
	 */
	void			PropertySet::delProperty(const String& name)
	{
		HashProperty::iterator it = m_HashProperty.find(name);
		if ( it != m_HashProperty.end() )
		{
			delete it->second; it = m_HashProperty.erase(it);
		}
	}

	/**
	 *
	 * \param name 
	 * \return 
	 */
	Property*		PropertySet::getProperty(const String& name)
	{
		HashProperty::iterator it = m_HashProperty.find(name);
		if ( it != m_HashProperty.end() )
		{
			return it->second;
		}

		return NULL;
	}

	/**
	 *
	 * \param name 
	 * \return 
	 */
	Any&			PropertySet::getPropertyValue(const String& name)
	{
		Property* pProperty = getProperty(name);
		assert(pProperty != NULL);

		return pProperty->getValue();
	}

	/**
	 *
	 * \param name 
	 * \param anyValue 
	 */
	void			PropertySet::setPropertyValue(const String& name, const Any& anyValue)
	{
		Property* pProperty = getProperty(name);
		if (pProperty != NULL)
		{
			pProperty->setValue(anyValue);

			PropertyEventArgs args(pProperty);
			fireEvent(EventValueChanged, args, EventNamespace);
		}
	}

	/**
	 *
	 * \return 
	 */
	HashProperty&	PropertySet::getHashProperty()
	{
		return m_HashProperty;
	}
}