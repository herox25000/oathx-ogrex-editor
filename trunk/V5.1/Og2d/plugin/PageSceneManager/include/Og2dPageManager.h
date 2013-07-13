#ifndef _____Og2dPageManager_H
#define _____Og2dPageManager_H

#include "Og2dPage.h"

namespace Og2d
{
	// ≥°æ∞“≥”≥…‰±Ì
	typedef HashMap<String, Page*>	HashMapPage;

	/**
	* \ingroup : PageSceneManager
	*
	* \os&IDE  : Microsoft Windows XP (SP2)  &  Microsoft Visual C++ .NET 2008
	*
	* \VERSION : 1.0
	*
	* \date    : 2012-08-04
	*
	* \Author  : lp
	*
	* \Desc    : 
	*
	* \bug     : 
	*
	* \Copyright (c) 2012 lp All rights reserved.
	*/
	class Og2d_PSM_Export_API PageManager
	{
	public:
		/**
		 *
		 * \return 
		 */
		PageManager();

		/**
		 *
		 * \return 
		 */
		virtual ~PageManager();

		/**
		 *
		 * \param cSize 
		 * \return 
		 */
		virtual	Page*		createPage(const String& szName, const Vector2D& vPos, const Size& cSize);

		/**
		 *
		 * \param pPage 
		 */
		virtual	void		destroyPage(Page* pPage);
		
		/**
		 *
		 * \param vPos 
		 * \return 
		 */
		virtual	Page*		getPage(const Vector2D& vPos);
		
		/**
		 *
		 * \param szName 
		 * \return 
		 */
		virtual	Page*		getPage(const String& szName);

		/**
		 *
		 */
		virtual	void		destroyAllPage();
	protected:
		HashMapPage			m_HashPage;
	};
}

#endif