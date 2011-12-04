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

#ifndef _WOptionsWindow_H_
#define _WOptionsWindow_H_

#include "../Prerequisites.h"
#include "RBGuiWindowBase.h"
#include "RBGuiHelp.h"

namespace HydraxEditor
{
    /** RBGui water options window class
	 */
	class WOptionsWindow : public RBGuiWindowBase
	{
	public:
		/** Constructor
		    @param gm RBGui::GuiManager mocha pointer
		 */
		WOptionsWindow(Mocha::RefPointer<RBGui::GuiManager> gm);

		/** Destructor
		 */
		~WOptionsWindow();

		/** Create windows and set callbacks
		 */
		void create();

		/** Get selected hydrax components
		    @return Hydrax::HydraxComponents
		 */
		Hydrax::HydraxComponent getHydraxComponents() const;

		/** Set selected Rtt options
		    @Rtt Rtt to change the size
			@Value Mocha value that contains the new size
		 */
		void setRttOptions(const Mocha::String& Rtt, const Mocha::Value& Value);

		/** Add all attributes
		    @param SelectedModule_ NULL to get current module, else to get specified module
			@param NoiseModule_ NULL to get current noise, else to get specified noise
		 */
		void addAttributes(const Ogre::String& SelectedModule_ = "NULL", const Ogre::String& SelectedNoise_ = "NULL");

	private:
		/// Our attribute edit widget
		RBGui::AttributeEditWidget* mAttributeEditWidget;

		/** Update attributes
		 */
		void updateAttributes();

		/** Add geometry module region attributes
		    @param AttributeMap RBGui::AttributeMap&
			@param SelectedModule_ NULL to get current module, else to get specified module
		 */
		void addGeometryModuleAttributes(RBGui::AttributeMap &AttributeMap, const Ogre::String& SelectedModule_ = "NULL");

		/** Add noise module region attributes
		    @param AttributeMap RBGui::AttributeMap&
			@param NoiseModule_ NULL to get current noise, else to get specified noise
		 */
		void addNoiseModuleAttributes(RBGui::AttributeMap &AttributeMap, const Ogre::String& SelectedNoise_ = "NULL");

		/** Add components region attributes
		    @param AttributeMap RBGui::AttributeMap&
		 */
		void addComponentsAttributes(RBGui::AttributeMap &AttributeMap);

		/** Add Rtt region attributes
		    @param AttributeMap RBGui::AttributeMap&
		 */
		void addRttAttributes(RBGui::AttributeMap &AttributeMap);

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