#include "OgreEditSystemPrerequisites.h"
#include "OgreProperty.h"

namespace Ogre
{
	Property::Property(const String& sName, const String& describe)
		:m_decribe(describe), m_sName(sName)
	{

	}

	Property::~Property()
	{

	}

	void		Property::setName(const String& sName)
	{
		m_sName = sName;
	}

	String		Property::getName() const
	{
		return m_sName;
	}

	void		Property::setDescribe(const String& describe)
	{
		m_decribe = describe;
	}

	String		Property::getDescribe() const
	{
		return m_decribe;
	}

	void		Property::addProperty(const String& name, Any Value, const String& describe)
	{
		
	}
}