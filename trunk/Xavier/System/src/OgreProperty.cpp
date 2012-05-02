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
}