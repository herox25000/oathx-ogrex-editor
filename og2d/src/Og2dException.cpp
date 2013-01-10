#include "Og2dException.h"
#include "Og2dDebug.h"

namespace Og2d
{
	/**
	 *
	 * \param nCode 
	 * \param &description 
	 * \param &source 
	 * \return 
	 */
	Exception::Exception(int nCode, const String &description, const String &source)
		:m_line(0),m_description(description),m_source(source)
	{

	}

	/**
	 *
	 * \param nCode 
	 * \param &description 
	 * \param &source 
	 * \param type 
	 * \param file 
	 * \param line 
	 * \return 
	 */
	Exception::Exception(int nCode, const String &description, const String &source, const char* type, const char* file, long line)
		:m_line(line),m_code(nCode),m_typeName(type),m_description(description),m_source(source),m_file(file)
	{

	}

	/**
	 *
	 * \return 
	 */
	const String&	Exception::getFullDescription() const
	{
		if (m_fullDesc.empty())
		{
			std::ostringstream stream;
			stream <<"Exception "<<m_code<<" : "<<m_typeName<<" "<<m_description<<" in "<<m_source;

			if( m_line > 0 )
			{
				stream <<" at "<<m_file<<" line "<<m_line;
			}
			m_fullDesc = stream.str();
		}

		return m_fullDesc;
	}
}