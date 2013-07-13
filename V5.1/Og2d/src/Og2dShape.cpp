#include "Og2dShape.h"
#include "Og2dDebug.h"

namespace Og2d
{
	/**
	 *
	 * \param nLength 
	 * \return 
	 */
	Shape::Shape(ulong nLength) 
		: m_nLength(nLength)
	{

	}

	/**
	 *
	 * \return 
	 */
	Shape::~Shape()
	{

	}

	/**
	 *
	 * \return 
	 */
	ulong	Shape::getLength() const
	{
		return m_nLength;
	}
}