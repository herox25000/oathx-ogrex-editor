#include "Og2dDynlibManager.h"
#include "Og2dDebug.h"

namespace Og2d
{
	template<>	DynlibManager*	Singleton<DynlibManager>::mpSingleton = NULL;
	/**
	 *
	 * \return 
	 */
	DynlibManager&		DynlibManager::getSingleton()
	{
		assert(mpSingleton != NULL); return (*mpSingleton);
	}

	/**
	 *
	 * \return 
	 */
	DynlibManager*		DynlibManager::getSingletonPtr()
	{
		assert(mpSingleton != NULL); return mpSingleton;
	}
	

	/**
	 *
	 * \return 
	 */
	DynlibManager::DynlibManager()
	{

	}

	/**
	 *
	 * \return 
	 */
	DynlibManager::~DynlibManager()
	{
		StringDynlib::iterator it = m_dynlib.begin();
		while (it != m_dynlib.end())
		{
			delete it->second; it = m_dynlib.erase(it);
		}
	}

	/**
	 *
	 * \param name 
	 * \return 
	 */
	DynLib*		DynlibManager::load(const String& name)
	{
		StringDynlib::iterator it = m_dynlib.find(name);
		if ( it != m_dynlib.end() )
		{
			return it->second;
		}
		else
		{
			// 构造新的动态链接库
			DynLib* pLib = new DynLib(name);
			if (pLib)
			{
				m_dynlib.insert(StringDynlib::value_type(name, pLib));
				return pLib;
			}
		}

		return NULL;
	}
	
	/**
	 *
	 * \param lib 
	 */
	void		DynlibManager::unload(DynLib* pDynlib)
	{
		if (pDynlib)
		{
			StringDynlib::iterator it = m_dynlib.find(pDynlib->getName());
			if ( it != m_dynlib.end() )
			{
				delete it->second; m_dynlib.erase(it);
			}
		}
	}
}

