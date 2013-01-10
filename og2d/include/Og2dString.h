#ifndef _____Og2dString_H
#define _____Og2dString_H

#include "Og2dTypes.h"

namespace Og2d
{
#if OG2D_WCHAR_T_STRINGS
	typedef std::wstring	 _StringBase;
#else
	typedef std::string		_StringBase;
#endif

#if OG2D_WCHAR_T_STRINGS
	typedef std::basic_stringstream<wchar_t,std::char_traits<wchar_t>,std::allocator<wchar_t> > _StringStreamBase;
#else
	typedef std::basic_stringstream<char,std::char_traits<char>,std::allocator<char> > _StringStreamBase;
#endif

typedef _StringBase			String;
typedef _StringStreamBase	StringStream;
typedef StringStream		stringstream;

	/**
	* \ingroup : Og2d
	*
	* \os&IDE  : Microsoft Windows XP (SP2)  &  Microsoft Visual C++ .NET 2008
	*
	* \VERSION : 1.0
	*
	* \date    : 2012-07-28
	*
	* \Author  : lp
	*
	* \Desc    : 
	*
	* \bug     : 
	*
	* \Copyright (c) 2012 lp All rights reserved.
	*/
	class Og2d_Export_API StringUtil
	{
	public:
		/**
		 *
		 * \param szValue 
		 * \param nValue 
		 * \return 
		 */
		static unsigned int		ToUINT(const String& szValue, unsigned int nValue=0)
		{
			StringStream str(szValue);
			unsigned int ret = nValue;
			str >> ret;

			return ret;
		}

		/** Converts an int to a String. */
		/**
		 *
		 * \param nValue 
		 * \param width 
		 * \param fill 
		 * \param flags 
		 * \return 
		 */
		static String			ToSTRING(int nValue, unsigned short width = 0, 
			char fill = ' ', 
			std::ios::fmtflags flags = std::ios::fmtflags(0) )
		{
			stringstream stream;
			stream.width(width);
			stream.fill(fill);
			if (flags)
				stream.setf(flags);
			stream << nValue;
			return stream.str();
		}

#if OG2D_PLATFORM != OG2D_PLATFORM_NACL &&  ( OG2D_ARCH_TYPE == OG2D_ARCHITECTURE_64 || OG2D_PLATFORM == OG2D_PLATFORM_APPLE || OG2D_PLATFORM == OG2D_PLATFORM_IOS )
		/** Converts an unsigned int to a String. */
		/**
		 *
		 * \param nValue 
		 * \param width 
		 * \param fill 
		 * \param flags 
		 * \return 
		 */
		static String			ToSTRING(unsigned int nValue, 
			unsigned short width = 0, char fill = ' ', 
			std::ios::fmtflags flags = std::ios::fmtflags(0) )
		{
			stringstream stream;
			stream.width(width);
			stream.fill(fill);
			if (flags)
				stream.setf(flags);
			stream << nValue;
			return stream.str();
		}

		/** Converts a size_t to a String. */
		/**
		 *
		 * \param nValue 
		 * \param width 
		 * \param fill 
		 * \param flags 
		 * \return 
		 */
		static String			ToSTRING(size_t nValue, 
			unsigned short width = 0, char fill = ' ', 
			std::ios::fmtflags flags = std::ios::fmtflags(0) )
		{
			stringstream stream;
			stream.width(width);
			stream.fill(fill);
			if (flags)
				stream.setf(flags);
			stream << nValue;
			return stream.str();
		}

#	if OG2D_COMPILER == OG2D_COMPILER_MSVC
		/** Converts an unsigned long to a String. */
		/**
		 *
		 * \param nValue 
		 * \param width 
		 * \param fill 
		 * \param flags 
		 * \return 
		 */
		static String			ToSTRING(unsigned long nValue, 
			unsigned short width = 0, char fill = ' ', 
			std::ios::fmtflags flags = std::ios::fmtflags(0) )
		{
			stringstream stream;
			stream.width(width);
			stream.fill(fill);
			if (flags)
				stream.setf(flags);
			stream << nValue;
			return stream.str();
		}

#	endif

#else
		/** Converts a size_t to a String. */
		/**
		 *
		 * \param nValue 
		 * \param width 
		 * \param fill 
		 * \param flags 
		 * \return 
		 */
		static String			ToSTRING(size_t nValue, 
			unsigned short width = 0, char fill = ' ', 
			std::ios::fmtflags flags = std::ios::fmtflags(0) )
		{
			stringstream stream;
			stream.width(width);
			stream.fill(fill);
			if (flags)
				stream.setf(flags);
			stream << nValue;
			return stream.str();
		}

		/** Converts an unsigned long to a String. */
		/**
		 *
		 * \param nValue 
		 * \param width 
		 * \param fill 
		 * \param flags 
		 * \return 
		 */
		static String			ToSTRING(unsigned long nValue, 
			unsigned short width = 0, char fill = ' ', 
			std::ios::fmtflags flags = std::ios::fmtflags(0) )
		{
			stringstream stream;
			stream.width(width);
			stream.fill(fill);
			if (flags)
				stream.setf(flags);
			stream << nValue;
			return stream.str();
		}
#endif

		/** Converts a long to a String. */
        /**
         *
         * \param nValue 
         * \param width 
         * \param fill 
         * \param flags 
         * \return 
         */
        static String			ToSTRING(long nValue, 
            unsigned short width = 0, char fill = ' ', 
            std::ios::fmtflags flags = std::ios::fmtflags(0) )
		{
			stringstream stream;
			stream.width(width);
			stream.fill(fill);
			if (flags)
				stream.setf(flags);
			stream << nValue;
			return stream.str();
		}

        /** Converts a boolean to a String. */
        /**
         *
         * \param bValue 
         * \return 
         */
        static String			ToSTRING(bool bValue)
		{
			return bValue ? "true" : "false";
		}

		/**
		 *
		 * \param szValue 
		 * \return 
		 */
		static bool				ToBOOL(const String& szValue)
		{
			return szValue == "true" ? true : 0;
		}
	};
}

#endif