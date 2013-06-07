#include "stdafx.h"
#include "OgreSandBoxUnity.h"

namespace Ogre
{
	/**
	 *
	 * \param szName 
	 * \return 
	 */
	bool		Unity::createDirectory(const String& szName)
	{
#ifdef _WIN32
		return ::CreateDirectory(szName.c_str(), NULL) ? true : 0;
#endif
	}

	/**
	 *
	 * \param szPath 
	 * \return 
	 */
	String		Unity::getPath(const String& szPath)
	{
		size_t iPos = szPath.find_last_of('/');
		if (iPos == String::npos)
		{
			iPos = szPath.find_last_of('\\');
		}

		String szResult;

		if (iPos != String::npos)
		{
			szResult = szPath.substr(0, iPos);
		}

		return szResult;
	}

	/**
	 *
	 * \param szPath 
	 * \return 
	 */
	String		Unity::getName(const String& szPath)
	{
		size_t iPos = szPath.find_last_of('/');
		if (iPos == String::npos)
		{
			iPos = szPath.find_last_of('\\');
		}

		String szResult;

		if (iPos != String::npos)
		{
			szResult = szPath.substr(iPos, szPath.length());			
		}

		return szResult;
	}
}