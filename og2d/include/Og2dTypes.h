#ifndef _____Og2dTypes_H
#define _____Og2dTypes_H

#include "Og2dPlatform.h"
#include "Og2dStdHead.h"
#include "Og2dString.h"

//////////////////////////////////////////////////////////////////////////
//! 关闭常见警告
#pragma warning (disable : 4786)

#pragma warning (disable : 4503)

#pragma warning (disable : 4244)

#pragma warning (disable : 4305)

#pragma warning (disable : 4251)

#pragma warning (disable : 4275)

#pragma warning (disable : 4290)

#pragma warning (disable:  4661)

#pragma warning (disable:  4996)

#pragma warning (disable : 201)


//////////////////////////////////////////////////////////////////////////

#ifndef NULL
#	define NULL 0
#endif

#define SAFE_DELETE(p)       { if(p) { delete (p);     (p)=NULL; } }
#define SAFE_DELETE_ARRAY(p) { if(p) { delete[] (p);   (p)=NULL; } }
#define SAFE_RELEASE(p)      { if(p) { (p)->Release(); (p)=NULL; } }

namespace Og2d
{
    #if OG2D_COMPILER == OG2D_COMPILER_GNUC && OG2D_COMP_VER >= 310 && !defined(STLPORT)
	#   if OG2D_COMP_VER >= 430
	#       define HashMap ::std::tr1::unordered_map
	#		define HashSet ::std::tr1::unordered_set
	#    else
	#       define HashMap ::__gnu_cxx::hash_map
	#       define HashSet ::__gnu_cxx::hash_set
	#    endif
    #elif OG2D_COMPILER == OG2D_COMPILER_CLANG
    #    if defined(_LIBCPP_VERSION)
    #       define HashMap ::std::unordered_map
    #       define HashSet ::std::unordered_set
    #    else
    #       define HashMap ::std::tr1::unordered_map
    #       define HashSet ::std::tr1::unordered_set
    #    endif
    #else
    #   if OG2D_COMPILER == OG2D_COMPILER_MSVC
    #       if OG2D_COMP_VER >= 1600 // VC++ 10.0
	#			define HashMap ::std::tr1::unordered_map
	#           define HashSet ::std::tr1::unordered_set
	#		elif OG2D_COMP_VER > 1300 && !defined(_STLP_MSVC)
    #           define HashMap ::stdext::hash_map
	#           define HashSet ::stdext::hash_set
    #       else
    #           define HashMap ::std::hash_map
	#           define HashSet ::std::hash_set
    #       endif
    #   else
    #       define HashMap ::std::hash_map
	#       define HashSet ::std::hash_set
    #   endif
    #endif

    #define OG2D_DEFINE_STATIC_LOCAL(type, name, arguments) \
        static type& name = *new type arguments

    /** In order to avoid finger-aches :)
    */
    typedef unsigned char		uchar;
    typedef unsigned short		ushort;
    typedef unsigned int		uint;
	typedef unsigned long		ulong;
	typedef unsigned char		byte;

#ifndef DWORD
	typedef unsigned long		DWORD;
#endif
	
	template <typename T> struct deque 
	{ 
		typedef typename std::deque<T> type;
		typedef typename std::deque<T>::iterator iterator;
		typedef typename std::deque<T>::const_iterator const_iterator;
	}; 

	template <typename T> 
	struct vector 
	{ 
		typedef typename std::vector<T> type;
		typedef typename std::vector<T>::iterator iterator;
		typedef typename std::vector<T>::const_iterator const_iterator;
	}; 

	template <typename T> 
	struct list 
	{ 
		typedef typename std::list<T> type;
		typedef typename std::list<T>::iterator iterator;
		typedef typename std::list<T>::const_iterator const_iterator;
	}; 

	template <typename T, typename P = std::less<T> > 
	struct set 
	{ 
		typedef typename std::set<T, P> type;
		typedef typename std::set<T, P>::iterator iterator;
		typedef typename std::set<T, P>::const_iterator const_iterator;
	}; 

	template <typename K, typename V, typename P = std::less<K> > 
	struct map 
	{ 
		typedef typename std::map<K, V, P> type;
		typedef typename std::map<K, V, P>::iterator iterator;
		typedef typename std::map<K, V, P>::const_iterator const_iterator;
	};
	
	// defing string value (first=name, second=value)
	typedef map<String, String>::type	StringValue;

	template <typename K, typename V, typename P = std::less<K> > 
	struct multimap 
	{ 
		typedef typename std::multimap<K, V, P> type;
		typedef typename std::multimap<K, V, P>::iterator iterator;
		typedef typename std::multimap<K, V, P>::const_iterator const_iterator;
	}; 

	class DynLib;
	class DynlibManager;
	class Log;
	class LogListener;
	class LogManager;
	class InputListener;
	class InputManager;
	class Plugin;
	class Resource;
	class Texture;
	class Shape;
	class RenderTarget;
	class Quad;
	class RenderListener;
	class RenderSystem;
	class Node;
	class SceneNode;
	class Scene;
	class SceneFactory;
	class World;
}

#endif

