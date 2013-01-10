#ifndef _____Og2dHash_H
#define _____Og2dHash_H

namespace Og2d
{
#ifdef __cplusplus
	extern "C" { 
#endif

		//!
		/**
		*
		* \param strString 
		* \return 
		*/
	_____inline
		Og2d_Export_API unsigned int __elfHash(const char* szText)
	{
		const char *p		= szText;
		unsigned int hash	= 0; 
		unsigned int x		= 0; 
		
		while(*p) 
		{ 
			hash = (hash << 4) + (*p++); 
			if ((x = hash & 0xF0000000L ) != 0) 
			{ 
				hash ^= (x >> 24); 
				hash &= ~ x; 
			} 
		} 

		return (hash & 0x7FFFFFFF); 
	}

		//!
		/**
		*
		* \param strString 
		* \return 
		*/
	_____inline
		Og2d_Export_API unsigned int __fvnHash(const char* szText)
	{
		const char *p		= szText; 
		unsigned int hash	= 0; 

		while(*p)
		{ 
			hash *= 16777619; 
			hash ^= (unsigned int)((unsigned char)(*p++)); 
		}

		return hash;
	}

		//!
		/**
		*
		* \param strString 
		* \return 
		*/
	_____inline
		Og2d_Export_API unsigned int __simpleHash(const char* szText)
	{
		unsigned int		 h; 
		const unsigned char* p; 

		for(h=0, p = (const unsigned char*)szText; *p; p++) 
			h = 31 * h + *p; 

		return h; 
	}
#ifdef __cplusplus
	}
#endif

}

#endif