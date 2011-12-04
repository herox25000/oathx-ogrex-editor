/*
--------------------------------------------------------------------------------
This source file is part of Hydrax editor.
Visit ---

Copyright (C) 2008 Xavier Vergu�n Gonz�lez <xavierverguin@hotmail.com>
                                           <xavyiy@gmail.com>

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software Foundation, Inc.,
59 Temple Place - Suite 330, Boston, MA  02111-1307, USA, or go to
http://www.gnu.org/copyleft/gpl.html.
--------------------------------------------------------------------------------
*/

#ifndef _EnvironementWindow_H_
#define _EnvironementWindow_H_

#include "../Prerequisites.h"
#include "RBGuiWindowBase.h"

namespace HydraxEditor
{
    /** RBGui environement window class
	 */
	class EnvironementWindow : public RBGuiWindowBase
	{
	public:
		/** Constructor
		    @param rbguiman RBGuiManager pointer
		 */
		EnvironementWindow(Mocha::RefPointer<RBGui::GuiManager> gm);

		/** Destructor
		 */
		~EnvironementWindow();

		/** Create
		 */
		void create();

	private:
		/// Our attribute edit widget
		RBGui::AttributeEditWidget* mAttributeEditWidget;

		/** Our's callback
		    @param vElement RBGui::GuiElement&
			@param vData Mocha::ValueList&
		 */
		void callback(RBGui::GuiElement& vElement, const Mocha::ValueList& vData);

		/** Resize callback
		    @param vElement RBGui::GuiElement&
			@param vData Mocha::ValueList&
		 */
		void resizedCallback(RBGui::GuiElement& vElement, const Mocha::ValueList& vData);

		/** Closed callback
		    @param vElement RBGui::GuiElement&
			@param vData Mocha::ValueList&
		 */
		void closedCallback(RBGui::GuiElement& vElement, const Mocha::ValueList& vData);
	};
};

#endif