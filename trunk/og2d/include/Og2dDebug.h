#ifndef _____Og2dDebug_H
#define _____Og2dDebug_H


#if OG2D_PLATFORM == OG2D_PLATFORM_WIN32

//! 内存泄露检查

#include<crtdbg.h>

#ifdef _DEBUG 
#	define DEBUG_CLIENTBLOCK  new( _CLIENT_BLOCK, __FILE__, __LINE__) 
#else 
#	define DEBUG_CLIENTBLOCK 
#endif 
#	define _CRTDBG_MAP_ALLOC 
#		include <crtdbg.h> 
#ifdef _DEBUG 
#	define new DEBUG_CLIENTBLOCK 
#endif


//////////////////////////////////////////////////////////////////////////
//! 内存检查
#ifndef dump_memory_leaks
#	define dump_memory_leaks() _CrtDumpMemoryLeaks(); 
#endif

#endif

#endif // end _____Og2dDebug_H