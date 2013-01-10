#ifndef _____Og2dPageScene_H
#define _____Og2dPageScene_H

#include "Og2dScene.h"
#include "Og2dPage.h"

namespace Og2d
{
	/**
	* \ingroup : PageSceneManager
	*
	* \os&IDE  : Microsoft Windows XP (SP2)  &  Microsoft Visual C++ .NET 2008
	*
	* \VERSION : 1.0
	*
	* \date    : 2012-08-03
	*
	* \Author  : lp
	*
	* \Desc    : “≥≥°æ∞π‹¿Ì∆˜
	*
	* \bug     : 
	*
	* \Copyright (c) 2012 lp All rights reserved.
	*/
	class Og2d_PSM_Export_API PageScene : public Scene
	{
	public:
		/**
		 *
		 * \return 
		 */
		PageScene(const String& szName, const Vector2D& vOrigin, const Size& cSize, 
			const Rect& rcView);

		/**
		 *
		 * \return 
		 */
		virtual ~PageScene();

		/**
		 *
		 * \param fElapsed 
		 */
		virtual	void			update(float fElapsed);
	};
}

#endif