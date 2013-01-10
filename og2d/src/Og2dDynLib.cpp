#include "Og2dDynlib.h"
#include "Og2dDebug.h"

#if OG2D_PLATFORM == OG2D_PLATFORM_APPLE || OG2D_PLATFORM == OG2D_PLATFORM_IOS
#   include "macUtils.h"
#   include <dlfcn.h>
#endif

namespace Og2d
{
	/**
	 *
	 * \param name 
	 * \return 
	 */
	DynLib::DynLib( const String& name ) : m_Name(name), m_hInst(NULL)
	{
		load();
	}

	/**
	 *
	 * \return 
	 */
	DynLib::~DynLib()
	{
		unload();
	}

	/**
	 *
	 */
	void		DynLib::load()
	{
		String name = m_Name;
#if		OG2D_PLATFORM == OG2D_PLATFORM_LINUX || OG2D_PLATFORM == OG2D_PLATFORM_NACL
		if (name.find(".so") == String::npos)
			name += ".so";
#elif	OG2D_PLATFORM == OG2D_PLATFORM_APPLE
		if (name.substr(name.length() - 6, 6) != ".dylib")
			name += ".dylib";
#elif	OG2D_PLATFORM == OG2D_PLATFORM_WIN32
		if (name.substr(name.length() - 4, 4) != ".dll")
			name += ".dll";
#endif
		m_hInst = (DYNLIB_HANDLE)DYNLIB_LOAD( name.c_str() );
		assert(m_hInst != NULL);
	}

	/**
	 *
	 */
	void		DynLib::unload()
	{
		if( DYNLIB_UNLOAD( m_hInst ) )
		{

		}
	}


	/**
	 *
	 * \param strName 
	 * \return 
	 */
	Symbol		DynLib::getSymbol( const String& strName ) const throw()
	{
		return (void*)DYNLIB_GETSYM( m_hInst, strName.c_str() );
	}
	
	/**
	 *
	 * \param void 
	 * \return 
	 */
	String		DynLib::dynlibError( void ) 
	{
#if OG2D_PLATFORM == OG2D_PLATFORM_WIN32
		LPVOID lpMsgBuf; 
		FormatMessage( 
			FORMAT_MESSAGE_ALLOCATE_BUFFER | 
			FORMAT_MESSAGE_FROM_SYSTEM | 
			FORMAT_MESSAGE_IGNORE_INSERTS, 
			NULL, 
			GetLastError(), 
			MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), 
			(LPTSTR) &lpMsgBuf, 
			0, 
			NULL 
			); 
		String ret = (char*)lpMsgBuf;
		LocalFree( lpMsgBuf );
		return ret;
#elif OG2D_PLATFORM == OG2D_PLATFORM_LINUX || OG2D_PLATFORM == OG2D_PLATFORM_APPLE
		return String(dlerror());
#else
		return String("");
#endif
	}
}
