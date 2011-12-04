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

#include "RBGuiHelp.h"

namespace HydraxEditor
{
	RBGui::Widget* RBGuiHelp::getFromWidgetListByText(const RBGui::WidgetList &WidgetList, const Mocha::String &Text)
	{
		for(unsigned int k = 0; k < WidgetList.size(); k++)
		{
			if(WidgetList.at(k)->getText() == Text)
			{
				return WidgetList.at(k);
			}
		}

		return static_cast<RBGui::Widget*>(NULL);
	}

	Mocha::StringList RBGuiHelp::getVectorAttributeWidgetParams(const float &Step, const float &Min, const float &Max)
	{
		Mocha::StringList Params;

		Params.reserve(3);
		Params.resize(3);

		Params[0] = Ogre::StringConverter::toString(Step);
		Params[1] = Ogre::StringConverter::toString(Min);
		Params[2] = Ogre::StringConverter::toString(Max);

		return Params;
	}

	Mocha::Value RBGuiHelp::getValueFromAttributeWidget(RBGui::AttributeEditWidget* AttributeEditWidget, const Mocha::String &vID)
	{
		Mocha::Value Value;

		AttributeEditWidget->getAttribute(vID, Value);

		return Value;
	}

	Hydrax::TextureQuality RBGuiHelp::MochaValueToHydraxTQ(const Mocha::Value &Value)
	{
		Mocha::String ValueToString = Value.getAsString();

		int Size = Ogre::StringConverter::parseInt(
			Ogre::StringUtil::split(ValueToString, "x")[0]);

		return static_cast<Hydrax::TextureQuality>(Size);
	}

	Hydrax::Size RBGuiHelp::MochaValueToHydraxSize(const Mocha::Value &Value)
	{
		Mocha::String ValueToString = Value.getAsString();

		if (ValueToString == "Auto")
		{
			return Hydrax::Size(0);
		}

		return Hydrax::Size(Ogre::StringConverter::parseInt(Ogre::StringUtil::split(ValueToString, "x")[0]),
			                Ogre::StringConverter::parseInt(Ogre::StringUtil::split(ValueToString, "x")[1]));
	}

	Mocha::Color RBGuiHelp::OgreVector3ToMochaColor(const Ogre::Vector3 &Color)
	{
		Mocha::Color c;

		c.a = 1;
		c.r = Color.x;
		c.g = Color.y;
		c.b = Color.z;

		return c;
	}

	Ogre::Vector3 RBGuiHelp::MochaColorToOgreVector3(const Mocha::Color &Color)
	{
		Ogre::Vector3 c;

		c.x = Color.r;
		c.y = Color.g;
		c.z = Color.b;

		return c;
	}

	Mocha::Vector2 RBGuiHelp::OgreVector2ToMochaVector2(const Ogre::Vector2 &Vector)
	{
		Mocha::Vector2 v;

		v.x = Vector.x;
		v.y = Vector.y;

		return v;
	}

	Ogre::Vector2 RBGuiHelp::MochaVector2ToOgreVector2(const Mocha::Vector2 &Vector)
	{
		Ogre::Vector2 v;

		v.x = Vector.x;
		v.y = Vector.y;

		return v;
	}

	Mocha::Vector3 RBGuiHelp::OgreVector3ToMochaVector3(const Ogre::Vector3 &Vector)
	{
		Mocha::Vector3 v;

		v.x = Vector.x;
		v.y = Vector.y;
		v.z = Vector.z;

		return v;
	}

	Ogre::Vector3 RBGuiHelp::MochaVector3ToOgreVector3(const Mocha::Vector3 &Vector)
	{
		Ogre::Vector3 v;

		v.x = Vector.x;
		v.y = Vector.y;
		v.z = Vector.z;

		return v;
	}
}