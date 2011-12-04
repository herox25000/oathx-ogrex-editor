/*
--------------------------------------------------------------------------------
This source file is part of Hydrax editor.
Visit ---

Copyright (C) 2007 Xavier Verguín González <xavierverguin@hotmail.com>
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

#ifndef _WParametersWindow_H_
#define _WParametersWindow_H_

#include "../Prerequisites.h"
#include "RBGuiWindowBase.h"
#include "RBGuiHelp.h"

namespace HydraxEditor
{
    /** RBGui water parameters window class
	 */
	class WParametersWindow : public RBGuiWindowBase
	{
	public:
		/** Constructor
		    @param gm RBGui::GuiManager mocha pointer
		 */
		WParametersWindow(Mocha::RefPointer<RBGui::GuiManager> gm);

		/** Destructor
		 */
		~WParametersWindow();

		/** Create windows and set callbacks
		 */
		void create();

		/** Update all attributes
		    @remarks Call after hydrax's components change
		 */
		void updateAttributes();

	private:
		/// Our attribute edit widget
		RBGui::AttributeEditWidget* mAttributeEditWidget;

		/** Add main hydrax parameters/options to an attribute map
		    @param AttributeMap RBGui::AttributeMap&
		 */
		void addMainAttributes(RBGui::AttributeMap &AttributeMap);

		/** Update main attributes(Set step/max/min values)
		    @remarks Call after setMainAttributes();
		 */
		void updateMainAttributes();

		/** Add sun hydrax parameters/options to an attribute map
		    @param AttributeMap RBGui::AttributeMap&
		 */
		void addSunAttributes(RBGui::AttributeMap &AttributeMap);

		/** Update sun attributes(Set step/max/min values)
		    @remarks Call after setSunAttributes();
		 */
		void updateSunAttributes();

		/** Add foam hydrax parameters/options to an attribute map
		    @param AttributeMap RBGui::AttributeMap&
		 */
		void addFoamAttributes(RBGui::AttributeMap &AttributeMap);

		/** Update foam attributes(Set step/max/min values)
		    @remarks Call after setFoamAttributes();
		 */
		void updateFoamAttributes();

		/** Add depth hydrax parameters/options to an attribute map
		    @param AttributeMap RBGui::AttributeMap&
		 */
		void addDepthAttributes(RBGui::AttributeMap &AttributeMap);

		/** Update depth attributes(Set step/max/min values)
		    @remarks Call after setDepthAttributes();
		 */
		void updateDepthAttributes();

		/** Add smooth hydrax parameters/options to an attribute map
		    @param AttributeMap RBGui::AttributeMap&
		 */
		void addSmoothAttributes(RBGui::AttributeMap &AttributeMap);

		/** Update smooth attributes(Set step/max/min values)
		    @remarks Call after setSmoothAttributes();
		 */
		void updateSmoothAttributes();

		/** Add caustics hydrax parameters/options to an attribute map
		    @param AttributeMap RBGui::AttributeMap&
		 */
		void addCausticsAttributes(RBGui::AttributeMap &AttributeMap);

		/** Update caustics attributes(Set step/max/min values)
		    @remarks Call after setCausticsAttributes();
		 */
		void updateCausticsAttributes();

		/** Add god rays attributes
		    @param AttributeMap RBGui::AttributeMap&
		 */
		void addGodRaysAttributes(RBGui::AttributeMap &AttributeMap);

		/** Update god rays attributes(Set step/max/min values)
		    @remarks Call after setGodRaysAttributes();
		 */
		void updateGodRaysAttributes();

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