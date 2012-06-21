#include "OgrePyEvtSetDllExport.h"
#include "OgreProperty.h"
#include "OgrePropertySet.h"

namespace Ogre
{
	// event name
	const String	PropertySet::EventNamespace		=	"PropertySet";
	const String	PropertySet::EventAddProperty	=	"AddProperty";
	const String	PropertySet::EventValueChanged	=	"ValueChanged";
	const String	PropertySet::EventDelProperty	=	"DelProperty";

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
		clearProperty();
	}

	/**
	 *
	 * \param name 
	 * \param Value 
	 * \param describe 
	 */
	void				PropertySet::addProperty(const String& name, Any anyValue,int typeProperty,
		bool bWrite/* =true */, const String& describe/*="null"*/)
	{
		HashProperty::iterator it = m_HashProperty.find(name);
		if ( it == m_HashProperty.end() )
		{
			m_HashProperty[name] = new Property(name, anyValue, describe, typeProperty, bWrite);
			
#ifdef _DEBUG_LOG
			TKLogEvent("add property [" + name + "] describe [" + describe + "]");
#endif
			PropertyEventArgs args(m_HashProperty[name]);

			// 发送事件
			fireEvent(EventAddProperty,
				args,
				EventNamespace
				);
		}
	}

	/**
	 *
	 * \param name 
	 */
	void				PropertySet::delProperty(const String& name)
	{
		HashProperty::iterator it = m_HashProperty.find(name);
		if ( it != m_HashProperty.end() )
		{
			PropertyEventArgs args(it->second);
	
			// 发送属性事件删除
			fireEvent(EventDelProperty, args, EventNamespace);

#ifdef _DEBUG_LOG
			TKLogEvent("delete property [" + name + "] describe [" + it->second->getDescribe() + "]");
#endif

			delete it->second; it = m_HashProperty.erase(it);
		}
	}

	/**
	 *
	 * \param name 
	 * \return 
	 */
	Property*			PropertySet::getProperty(const String& name)
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
	Any&				PropertySet::getPropertyValue(const String& name)
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
	void				PropertySet::setPropertyValue(const String& name, const Any& anyValue)
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
	HashProperty&		PropertySet::getHashProperty()
	{
		return m_HashProperty;
	}

	/**
	 *
	 * \return 
	 */
	HashPropertyIter	PropertySet::getHashPropertyIter()
	{
		return HashPropertyIter(m_HashProperty.begin(),
			m_HashProperty.end());
	}

	/**
	 *
	 */
	void				PropertySet::clearProperty()
	{
		HashProperty::iterator it = m_HashProperty.begin();
		while( it != m_HashProperty.end() )
		{
#ifdef _DEBUG_LOG
			TKLogEvent("remove property [" + it->second->getName() + "] describe " + it->second->getDescribe());
#endif
			delete it->second; it = m_HashProperty.erase(it);
		}
	}
}