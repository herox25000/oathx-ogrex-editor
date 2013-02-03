#ifndef _____EditorHeightAction_H
#define _____EditorHeightAction_H

#include "EditorAction.h"
#include "EditorTerrainPage.h"

namespace Ogre
{
	/**
	* \ingroup : XavierEditor
	*
	* \os&IDE  : Microsoft Windows XP (SP2)  &  Microsoft Visual C++ .NET 2008
	*
	* \VERSION : 1.0
	*
	* \date    : 2013-02-02
	*
	* \Author  : lp
	*
	* \Desc    : 
	*
	* \bug     : 
	*
	* \Copyright (c) 2012 lp All rights reserved.
	*/
	class EditorHeightAction : public EditorAction
	{
	public:
		/**
		 *
		 * \param pHeightData 
		 * \param rect 
		 * \return 
		 */
		EditorHeightAction(const String& name, int nPageX, int nPageY, float* pHeightData, const Rect& area);
		/**
		 *
		 * \return 
		 */
		virtual ~EditorHeightAction();

		/**
		 *
		 */
		virtual	void		execute();
	protected:
		char				m_chSaveName[MAX_PATH];
		String				m_Name;
		Rect				m_Rect;
		int					m_nPageX;
		int					m_nPageY;
	};
}

#endif