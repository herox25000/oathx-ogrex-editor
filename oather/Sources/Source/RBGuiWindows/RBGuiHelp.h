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

#ifndef _RBGuiHelp_H_
#define _RBGuiHelp_H_

#include "../Prerequisites.h"

namespace HydraxEditor
{
    class RBGuiHelp
	{
	public:
		/** Constructor
		 */
		RBGuiHelp(){};

		/** Destructor
		 */
		~RBGuiHelp(){};

		/** Return a RBGui::Widget pointer by text
		    @param WidgetList WidgetList
			@param Text Text to found
			@return The widget pointer or NULL if widget isn't found
		 */
		static RBGui::Widget* getFromWidgetListByText(const RBGui::WidgetList &WidgetList, const Mocha::String& Text);

		/** Gets the string for RBGui Vector1(float)/2/3(and int) attribute widget params
		    @param Step Step
			@param Min Min value
			@param Max Max value
			@return The string list params of _Number tipe_ attribute widgets
			@remarks This string list can be used in all number-user-entry attribute widget(like int, ...)
		 */
		static Mocha::StringList getVectorAttributeWidgetParams(const float &Step, const float &Min, const float &Max);

		/** Get the value from an attribute editr widget
		    @param Widget AttributeEditWidget pointer
			@param vID ID
			@return The mocha attribute widget value
		 */
		static Mocha::Value getValueFromAttributeWidget(RBGui::AttributeEditWidget* AttributeEditWidget, const Mocha::String &vID);

		/** Get the Hydrax::TextureQuality from Mocha::Value
		    @param Value Mocha::Value
			@return Hydrax::TextureQuality
		 */
		static Hydrax::TextureQuality MochaValueToHydraxTQ(const Mocha::Value &Value);

		/** Get the Hydrax::Size from Mocha::Value
		    @param Value Mocha::Value
			@return Hydrax::Size
		 */
		static Hydrax::Size MochaValueToHydraxSize(const Mocha::Value &Value);

		/** Get the Mocha::Color from Ogre::Vector3
		    @param Color Ogre::Vector3&
			@return Mocha::Color
		 */
		static Mocha::Color OgreVector3ToMochaColor(const Ogre::Vector3 &Color);

		/** Get the Ogre::Vector3 from Mocha::Color
		    @param Color Mocha::Color&
			@return Ogre::Vector3
		 */
		static Ogre::Vector3 MochaColorToOgreVector3(const Mocha::Color &Color);

		/** Get the Mocha::Vector2 from Ogre::Vector2
		    @param Vector Ogre::Vector2&
			@return Mocha::Vector2
		 */
		static Mocha::Vector2 OgreVector2ToMochaVector2(const Ogre::Vector2 &Vector);

		/** Get the Ogre::Vector2 from Mocha::Vector2
		    @param Vector Mocha::Vector2&
			@return Ogre::Vector2
		 */
		static Ogre::Vector2 MochaVector2ToOgreVector2(const Mocha::Vector2 &Vector);

		/** Get the Mocha::Vector3 from Ogre::Vector3
		    @param Vector Ogre::Vector3&
			@return Mocha::Vector3
		 */
		static Mocha::Vector3 OgreVector3ToMochaVector3(const Ogre::Vector3 &Vector);

		/** Get the Ogre::Vector3 from Mocha::Vector3
		    @param Vector Mocha::Vector3&
			@return Ogre::Vector3
		 */
		static Ogre::Vector3 MochaVector3ToOgreVector3(const Mocha::Vector3 &Vector);

	};
};

#endif