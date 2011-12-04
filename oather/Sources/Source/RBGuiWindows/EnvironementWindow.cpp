/*
--------------------------------------------------------------------------------
This source file is part of Hydrax editor.
Visit ---

Copyright (C) 2008 Xavier Verguín González <xavierverguin@hotmail.com>
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

#include "EnvironementWindow.h"
#include "../EditorApp.h"

namespace HydraxEditor
{
	EnvironementWindow::EnvironementWindow(Mocha::RefPointer<RBGui::GuiManager> gm)
		: RBGuiWindowBase(gm)
		, mAttributeEditWidget(0)
	{
	}

	EnvironementWindow::~EnvironementWindow()
	{
	}

	void EnvironementWindow::create()
	{
		mWindow = mGuiManager->createWindow();
		mWindow->setBorderVisible(true);
		mWindow->setHideOnClose(true);
		mWindow->setText("Environement");
		mWindow->setSize(Mocha::Vector2(165, 222));
		mWindow->setPosition(Mocha::Vector2(410,30));
		mWindow->setCallback(&EnvironementWindow::resizedCallback, this, "Resized");
		mWindow->setCallback(&EnvironementWindow::closedCallback,  this, "Close_Hide");
		mWindow->show();

		mAttributeEditWidget = static_cast<RBGui::AttributeEditWidget*>(mWindow->createWidget( "AttributeEdit" ));
		mAttributeEditWidget->setCallback(&EnvironementWindow::callback, this);
		mAttributeEditWidget->setSize( mWindow->getClientRectangle().getSize());
		mAttributeEditWidget->setName( "EnvironementWindow_AttributeEditWidget" );

		RBGui::AttributeMap AttributeMap;

		AttributeMap["1-Palms"].
			push_back( RBGui::AttributeEntry( "Show palms",   "PALMS", "bool", true ));
		AttributeMap["2-Skybox"].
			push_back( RBGui::AttributeEntry( "Select skybox", "SKYBOX", "list|ClubTropicana|Stormy|EarlyMorning|Evening|Clouds", "ClubTropicana" ));
		AttributeMap["3-Polygon mode"].
			push_back( RBGui::AttributeEntry( "Polygon mode", "POLYGONMODE", "list|Solid|Wireframe|Points", "Solid" ));

		// Set our attribute map
	    mAttributeEditWidget->setAttributes(AttributeMap);
	}

	void EnvironementWindow::callback(RBGui::GuiElement& vElement, const Mocha::ValueList& vData)
	{
		// Get the name of the attribute
	    const Mocha::String& Name = vData[0].getAsString();

	    // Get the value of the attribute
	    const Mocha::Value& Value = vData[1];

	    // Proccess
		// Palms
	    if (Name == "PALMS")
		{
			EditorApp::getSingleton()->getHydraxManager()
				->setPalmsVisible(Value.getAsBool());
		}
		// Skybox
		else if (Name == "SKYBOX")
		{
			EditorApp::getSingleton()->getHydraxManager()
				->setSkybox("Sky/" + Value.getAsString());
		}
		// Polygon mode
		else if (Name == "POLYGONMODE")
		{
			const Mocha::String& PMString = Value.getAsString();
			Ogre::PolygonMode PM = Ogre::PM_SOLID;

			if (PMString == "Wireframe")
			{
				PM = Ogre::PM_WIREFRAME;
			}
			else if (PMString == "Points")
			{
				PM = Ogre::PM_POINTS;
			}

			EditorApp::getSingleton()->getHydraxManager()->getHydrax()
				->setPolygonMode(PM);
		}
	}

	void EnvironementWindow::resizedCallback(RBGui::GuiElement& vElement, const Mocha::ValueList& vData)
	{
		mAttributeEditWidget->setSize(mWindow->getClientRectangle().getSize());
	}

	void EnvironementWindow::closedCallback(RBGui::GuiElement& vElement, const Mocha::ValueList& vData)
	{
		TopMenu* mTopMenu = static_cast<TopMenu*>(EditorApp::getSingleton()->getRBGuiManager()->getWindow("TopMenu"));

		mTopMenu->setItemSelect("VIEW_ENVIRONEMENT", false);
		mTopMenu->update();
	}
}