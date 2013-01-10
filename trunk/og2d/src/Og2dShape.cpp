#include "Og2dShape.h"
#include "Og2dDebug.h"

namespace Og2d
{
	/**
	 *
	 * \param nLength 
	 * \return 
	 */
	Shape::Shape(int nLength) 
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
	int		Shape::getLength() const
	{
		return m_nLength;
	}
}