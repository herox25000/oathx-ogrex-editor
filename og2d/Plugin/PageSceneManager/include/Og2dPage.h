#ifndef _____Og2dPage_H
#define _____Og2dPage_H

namespace Og2d
{
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
	class Og2d_PSM_Export_API Page : public SceneNode
	{
	public:
		/**
		 *
		 * \param vPos 
		 * \param cSize 
		 * \return 
		 */
		Page(const String& szName, const Rect& rcBoundingBox);

		/**
		 *
		 * \return 
		 */
		virtual ~Page();

		/** 更新场景节点
		 *
		 * \param fElapsed 
		 */
		virtual	void		update(float fElapsed);
	};
}

#endif