#include "Og2dReference.h"

namespace Og2d
{
	/**
	 *
	 * \return 
	 */
	Reference::Reference()
		: m_nReferenceCount(1)
	{

	}

	/**
	 *
	 * \return 
	 */
	Reference::~Reference()
	{

	}

	/**
	 *
	 * \return 
	 */
	void	Reference::grab()
	{
		++ m_nReferenceCount;
	}
	
	/**
	 *
	 * \return 
	 */
	int		Reference::getReferenceCount() const
	{
		return m_nReferenceCount;
	}

	/**
	 *
	 */
	void	Reference::drop()
	{
		if (--m_nReferenceCount == 0)
		{
			delete this;
		}
	}
}