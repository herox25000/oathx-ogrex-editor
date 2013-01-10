#include "Og2dPageScenePrerequisites.h"
#include "Og2dSceneNode.h"
#include "Og2dPageManager.h"

namespace Og2d
{
	/**
	 *
	 * \return 
	 */
	PageManager::PageManager()
	{

	}

	/**
	 *
	 * \return 
	 */
	PageManager::~PageManager()
	{
		destroyAllPage();
	}

	/**
	 *
	 * \param cSize 
	 * \return 
	 */
	Page*	PageManager::createPage(const String& szName, const Vector2D& vPos, const Size& cSize)
	{
		HashMapPage::iterator it = m_HashPage.find(szName);
		if ( it != m_HashPage.end() )
		{
			// construct new scene page
			Page* pPage = new Page(szName,
				Rect(vPos, cSize));
			
			// insert scene page
			m_HashPage.insert(HashMapPage::value_type(szName,
				pPage));
			
			// return this page
			return pPage;
		}

		return NULL;
	}
	
	/**
	 *
	 * \param vPos 
	 * \return 
	 */
	Page*	PageManager::getPage(const Vector2D& vPos)
	{
		HashMapPage::iterator it = m_HashPage.begin();
		while (it != m_HashPage.end())
		{
			// get this page bounding box
			Rect rcPage = it->second->getBoundingBox();
			if (rcPage.ptInRect(vPos))
				return it->second;
		}

		return NULL;
	}

	/**
	 *
	 * \param szName 
	 * \return 
	 */
	Page*	PageManager::getPage(const String& szName)
	{
		HashMapPage::iterator it = m_HashPage.find(szName);
		if ( it != m_HashPage.end() )
			return it->second;

		return NULL;
	}

	/**
	 *
	 * \param pPage 
	 */
	void	PageManager::destroyPage(Page* pPage)
	{
		HashMapPage::iterator it = m_HashPage.find(pPage->getName());
		if ( it != m_HashPage.end() )
		{
			SAFE_DELETE(it->second); m_HashPage.erase(it);
		}
	}

	/**
	 *
	 */
	void	PageManager::destroyAllPage()
	{
		HashMapPage::iterator it = m_HashPage.begin();
		while (it != m_HashPage.end())
		{
			SAFE_DELETE(it->second); it = m_HashPage.erase(it);
		}
	}
}