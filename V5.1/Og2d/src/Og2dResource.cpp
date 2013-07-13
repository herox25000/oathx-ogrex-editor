#include "Og2dResource.h"
#include "Og2dDebug.h"

namespace Og2d
{
	/**
	 *
	 * \return 
	 */
	Resource::Resource()
	{

	}

	/**
	 *
	 * \param name 
	 * \return 
	 */
	Resource::Resource(const String& name)
		: m_szName(name)
	{

	}

	/**
	 *
	 * \return 
	 */
	Resource::~Resource()
	{

	}

	/**
	 *
	 * \return 
	 */
	const String&	Resource::getName() const
	{
		return m_szName;
	}

	/**
	 *
	 * \param name 
	 */
	void			Resource::setName(const String& name)
	{
		m_szName = name;
	}
}