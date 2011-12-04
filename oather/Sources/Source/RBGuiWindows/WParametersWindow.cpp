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

#include "WParametersWindow.h"
#include "../EditorApp.h"

namespace HydraxEditor
{
	WParametersWindow::WParametersWindow(Mocha::RefPointer<RBGui::GuiManager> gm)
		: RBGuiWindowBase(gm)
		, mAttributeEditWidget(0)
	{
	}

	WParametersWindow::~WParametersWindow()
	{
	}

	void WParametersWindow::create()
	{
		mWindow = mGuiManager->createWindow();
		mWindow->setBorderVisible(true);
		mWindow->setHideOnClose(true);
		mWindow->setText("Water parameters");
		mWindow->setSize(Mocha::Vector2(200, 520));
		mWindow->setPosition(Mocha::Vector2(210,30));
	    mWindow->setCallback(&WParametersWindow::resizedCallback, this, "Resized");
	    mWindow->setCallback(&WParametersWindow::closedCallback,  this, "Close_Hide");
		mWindow->show();

		mAttributeEditWidget = static_cast<RBGui::AttributeEditWidget*>( mWindow->createWidget( "AttributeEdit" ) );
		mAttributeEditWidget->setCallback(&WParametersWindow::callback, this);
		mAttributeEditWidget->setSize( mWindow->getClientRectangle().getSize());
		mAttributeEditWidget->setName( "WParametersWindow_AttributeEditWidget" );

		updateAttributes();
	}

	void WParametersWindow::updateAttributes()
	{
		// Get our Hydrax pointer
		Hydrax::Hydrax* Hydrax = EditorApp::getSingleton()->getHydraxManager()->getHydrax();

		// Be sure that it isn't NULL
		if(!Hydrax)
		{
			return;
		}

		RBGui::AttributeMap AttributeMap;

		// Add main(common) hydrax attributes
		addMainAttributes(AttributeMap);

		// Add sun/depth... hydrax attributes if they're select
		if(Hydrax->isComponent(Hydrax::HYDRAX_COMPONENT_SUN))
		{
			addSunAttributes(AttributeMap);
		}
		if(Hydrax->isComponent(Hydrax::HYDRAX_COMPONENT_FOAM))
		{
			addFoamAttributes(AttributeMap);
		}
		if(Hydrax->isComponent(Hydrax::HYDRAX_COMPONENT_DEPTH))
		{
			addDepthAttributes(AttributeMap);
		}
		if(Hydrax->isComponent(Hydrax::HYDRAX_COMPONENT_SMOOTH))
		{
			addSmoothAttributes(AttributeMap);
		}
		if(Hydrax->isComponent(Hydrax::HYDRAX_COMPONENT_CAUSTICS))
		{
			addCausticsAttributes(AttributeMap);
		}
		if(Hydrax->isComponent(Hydrax::HYDRAX_COMPONENT_UNDERWATER_GODRAYS))
		{
			addGodRaysAttributes(AttributeMap);
		}

		// Set attributes in our AttributeEditWidget
		mAttributeEditWidget->setAttributes(AttributeMap);

		// Update main(common) hydrax attributes step/min/max values
		updateMainAttributes();

		// Update sun/depth... hydrax attributes if they're select
		if(Hydrax->isComponent(Hydrax::HYDRAX_COMPONENT_SUN))
		{
			updateSunAttributes();
		}
		if(Hydrax->isComponent(Hydrax::HYDRAX_COMPONENT_FOAM))
		{
			updateFoamAttributes();
		}
		if(Hydrax->isComponent(Hydrax::HYDRAX_COMPONENT_DEPTH))
		{
			updateDepthAttributes();
		}
		if(Hydrax->isComponent(Hydrax::HYDRAX_COMPONENT_SMOOTH))
		{
			updateSmoothAttributes();
		}
		if(Hydrax->isComponent(Hydrax::HYDRAX_COMPONENT_CAUSTICS))
		{
			updateCausticsAttributes();
		}
		if(Hydrax->isComponent(Hydrax::HYDRAX_COMPONENT_UNDERWATER_GODRAYS))
		{
			updateGodRaysAttributes();
		}
	}

	void WParametersWindow::resizedCallback(RBGui::GuiElement& vElement, const Mocha::ValueList& vData)
	{
		mAttributeEditWidget->setSize(mWindow->getClientRectangle().getSize());
	}

	void WParametersWindow::closedCallback(RBGui::GuiElement& vElement, const Mocha::ValueList& vData)
	{
		TopMenu* mTopMenu = static_cast<TopMenu*>(EditorApp::getSingleton()->getRBGuiManager()->getWindow("TopMenu"));

		mTopMenu->setItemSelect("VIEW_PARAMETERS", false);
		mTopMenu->update();
	}

	void WParametersWindow::addMainAttributes(RBGui::AttributeMap &AttributeMap)
	{
		Hydrax::Hydrax* Hydrax = EditorApp::getSingleton()->getHydraxManager()->getHydrax();

		AttributeMap["1-Main options"].
			push_back( RBGui::AttributeEntry( "Full reflection distance", "1_FULL_R_D", "float", Hydrax->getFullReflectionDistance()));
		AttributeMap["1-Main options"].
			push_back( RBGui::AttributeEntry( "Global transparency",      "1_GLOBAL_T", "float", Hydrax->getGlobalTransparency()));
		AttributeMap["1-Main options"].
			push_back( RBGui::AttributeEntry( "Normal distortion",        "1_NORMAL_D", "float", Hydrax->getNormalDistortion()));
		AttributeMap["1-Main options"].
			push_back( RBGui::AttributeEntry( "Color", "1_COLOR", "color", RBGuiHelp::OgreVector3ToMochaColor(Hydrax->getWaterColor())));
	}

	void WParametersWindow::updateMainAttributes()
	{
		mAttributeEditWidget->updateOptions("1_FULL_R_D", RBGuiHelp::getVectorAttributeWidgetParams(500000, 0, 100000000000));
		mAttributeEditWidget->updateOptions("1_GLOBAL_T", RBGuiHelp::getVectorAttributeWidgetParams(0.01,   0, 1));
		mAttributeEditWidget->updateOptions("1_NORMAL_D", RBGuiHelp::getVectorAttributeWidgetParams(0.005,  0, 10));
	}

	void WParametersWindow::addSunAttributes(RBGui::AttributeMap &AttributeMap)
	{
		Hydrax::Hydrax* Hydrax = EditorApp::getSingleton()->getHydraxManager()->getHydrax();

		AttributeMap["2-Sun"].
			push_back( RBGui::AttributeEntry( "Position", "2_SUN_POS",      "vector3", RBGuiHelp::OgreVector3ToMochaVector3(Hydrax->getSunPosition())));
		AttributeMap["2-Sun"].
			push_back( RBGui::AttributeEntry( "Strength", "2_SUN_STRENGTH", "float",   Hydrax->getSunStrength()));
		AttributeMap["2-Sun"].
			push_back( RBGui::AttributeEntry( "Area", "2_SUN_AREA",         "float",   Hydrax->getSunArea()));
		AttributeMap["2-Sun"].
			push_back( RBGui::AttributeEntry( "Color", "2_SUN_COLOR",       "color",   RBGuiHelp::OgreVector3ToMochaColor(Hydrax->getSunColor())));
	}

	void WParametersWindow::updateSunAttributes()
	{
		mAttributeEditWidget->updateOptions("2_SUN_POS", RBGuiHelp::getVectorAttributeWidgetParams(100, -100000000000, 100000000000));
		mAttributeEditWidget->updateOptions("2_SUN_STRENGTH", RBGuiHelp::getVectorAttributeWidgetParams(0.1,  0, 3));
		mAttributeEditWidget->updateOptions("2_SUN_AREA", RBGuiHelp::getVectorAttributeWidgetParams(1, 0, 1000));
	}

	void WParametersWindow::addFoamAttributes(RBGui::AttributeMap &AttributeMap)
	{
		Hydrax::Hydrax* Hydrax = EditorApp::getSingleton()->getHydraxManager()->getHydrax();

		AttributeMap["3-Foam"].
			push_back( RBGui::AttributeEntry( "Max. distance", "3_FOAM_MD",   "float", Hydrax->getFoamMaxDistance()));
		AttributeMap["3-Foam"].
			push_back( RBGui::AttributeEntry( "Scale", "3_FOAM_SCALE",        "float", Hydrax->getFoamScale()));
		AttributeMap["3-Foam"].
			push_back( RBGui::AttributeEntry( "Start", "3_FOAM_START",        "float", Hydrax->getFoamStart()));
		AttributeMap["3-Foam"].
			push_back( RBGui::AttributeEntry( "Transparency", "3_FOAM_TRANS", "float", Hydrax->getFoamTransparency()));
	}

	void WParametersWindow::updateFoamAttributes()
	{
		mAttributeEditWidget->updateOptions("3_FOAM_MD", RBGuiHelp::getVectorAttributeWidgetParams(500000,    0, 100000000000));
		mAttributeEditWidget->updateOptions("3_FOAM_SCALE", RBGuiHelp::getVectorAttributeWidgetParams(0.1, 0, 100));
		mAttributeEditWidget->updateOptions("3_FOAM_START", RBGuiHelp::getVectorAttributeWidgetParams(0.01,   0, 1));
		mAttributeEditWidget->updateOptions("3_FOAM_TRANS", RBGuiHelp::getVectorAttributeWidgetParams(0.01,   0, 3));
	}

	void WParametersWindow::addDepthAttributes(RBGui::AttributeMap &AttributeMap)
	{
		Hydrax::Hydrax* Hydrax = EditorApp::getSingleton()->getHydraxManager()->getHydrax();

		AttributeMap["4-Depth"].
			push_back( RBGui::AttributeEntry( "Limit", "4_DEPTH_LIMIT", "float", Hydrax->getDepthLimit()));
	}

	void WParametersWindow::updateDepthAttributes()
	{
		mAttributeEditWidget->updateOptions("4_DEPTH_LIMIT", RBGuiHelp::getVectorAttributeWidgetParams(1, -500, 500));
	}

	void WParametersWindow::addSmoothAttributes(RBGui::AttributeMap &AttributeMap)
	{
		Hydrax::Hydrax* Hydrax = EditorApp::getSingleton()->getHydraxManager()->getHydrax();

		AttributeMap["5-Smooth"].
			push_back( RBGui::AttributeEntry( "Power", "5_SMOOTH_POWER", "float", Hydrax->getSmoothPower()));
	}

	void WParametersWindow::updateSmoothAttributes()
	{
		mAttributeEditWidget->updateOptions("5_SMOOTH_POWER", RBGuiHelp::getVectorAttributeWidgetParams(1, 0, 100));
	}

	void WParametersWindow::addCausticsAttributes(RBGui::AttributeMap &AttributeMap)
	{
		Hydrax::Hydrax* Hydrax = EditorApp::getSingleton()->getHydraxManager()->getHydrax();

		AttributeMap["6-Caustics"].
			push_back( RBGui::AttributeEntry( "Scale", "6_CAUSTICS_SCALE", "float", Hydrax->getCausticsScale()));
		AttributeMap["6-Caustics"].
			push_back( RBGui::AttributeEntry( "Power", "6_CAUSTICS_POWER", "float", Hydrax->getCausticsPower()));
		AttributeMap["6-Caustics"].
			push_back( RBGui::AttributeEntry( "End",   "6_CAUSTICS_END",   "float", Hydrax->getCausticsEnd()));
	}

	void WParametersWindow::updateCausticsAttributes()
	{
	    mAttributeEditWidget->updateOptions("6_CAUSTICS_SCALE", RBGuiHelp::getVectorAttributeWidgetParams(1,    0, 500));
		mAttributeEditWidget->updateOptions("6_CAUSTICS_POWER", RBGuiHelp::getVectorAttributeWidgetParams(0.25, 0, 30));
		mAttributeEditWidget->updateOptions("6_CAUSTICS_END",   RBGuiHelp::getVectorAttributeWidgetParams(0.01, 0, 1));
	}

	void WParametersWindow::addGodRaysAttributes(RBGui::AttributeMap &AttributeMap)
	{
		Hydrax::Hydrax* Hydrax = EditorApp::getSingleton()->getHydraxManager()->getHydrax();

		AttributeMap["7-GodRays"].
			push_back( RBGui::AttributeEntry( "Exposure", "7_GODRAYS_EXPOSURE", "vector3", RBGuiHelp::OgreVector3ToMochaVector3(Hydrax->getGodRaysExposure())));
		AttributeMap["7-GodRays"].
			push_back( RBGui::AttributeEntry( "Intensity", "7_GODRAYS_INTENSITY", "float", Hydrax->getGodRaysIntensity()));
	}

	void WParametersWindow::updateGodRaysAttributes()
	{
	    mAttributeEditWidget->updateOptions("7_GODRAYS_EXPLOSURE", RBGuiHelp::getVectorAttributeWidgetParams(0.01, 0, 10));
		mAttributeEditWidget->updateOptions("7_GODRAYS_INTENSITY", RBGuiHelp::getVectorAttributeWidgetParams(0.05, 0, 10));
	}

	void WParametersWindow::callback(RBGui::GuiElement& vElement, const Mocha::ValueList& vData)
	{
		// Get the name of the attribute
	    const Mocha::String& Name = vData[0].getAsString( );

	    // Get the value of the attribute
	    const Mocha::Value& Value = vData[1];

		// Get our Hydrax pointer
		Hydrax::Hydrax* Hydrax = EditorApp::getSingleton()->getHydraxManager()->getHydrax();

	    // Proccess
		// Main options
	    if (Name == "1_FULL_R_D")
		{
		    Hydrax->setFullReflectionDistance(
				static_cast<Ogre::Real>(Value.getAsNumber()));
		}
		else if (Name == "1_GLOBAL_T")
		{
			Hydrax->setGlobalTransparency(
				static_cast<Ogre::Real>(Value.getAsNumber()));
		}
		else if (Name == "1_NORMAL_D")
		{
			Hydrax->setNormalDistortion(
				static_cast<Ogre::Real>(Value.getAsNumber()));
		}
		else if (Name == "1_COLOR")
		{
			Hydrax->setWaterColor(
				RBGuiHelp::MochaColorToOgreVector3(Value.getAsColor()));
		}
		// Sun options
		else if (Name == "2_SUN_POS")
		{
			Hydrax->setSunPosition(
				RBGuiHelp::MochaVector3ToOgreVector3(Value.getAsVector3()));

			EditorApp::getSingleton()->getSceneManager()->
				getLight("Light0")->setPosition(
				   RBGuiHelp::MochaVector3ToOgreVector3(Value.getAsVector3()));
		}
		else if (Name == "2_SUN_STRENGTH")
		{
			Hydrax->setSunStrength(
				static_cast<Ogre::Real>(Value.getAsNumber()));
		}
		else if (Name == "2_SUN_AREA")
		{
			Hydrax->setSunArea(
				static_cast<Ogre::Real>(Value.getAsNumber()));
		}
		else if (Name == "2_SUN_COLOR")
		{
			Hydrax->setSunColor(
				RBGuiHelp::MochaColorToOgreVector3(Value.getAsColor()));

			EditorApp::getSingleton()->getSceneManager()->
				getLight("Light0")->setSpecularColour(
				   RBGuiHelp::MochaColorToOgreVector3(Value.getAsColor()).x,
				   RBGuiHelp::MochaColorToOgreVector3(Value.getAsColor()).y,
				   RBGuiHelp::MochaColorToOgreVector3(Value.getAsColor()).z);
		}
		// Foam
		else if (Name == "3_FOAM_MD")
		{
			Hydrax->setFoamMaxDistance(
				static_cast<Ogre::Real>(Value.getAsNumber()));
		}
		else if (Name == "3_FOAM_SCALE")
		{
			Hydrax->setFoamScale(
				static_cast<Ogre::Real>(Value.getAsNumber()));
		}
		else if (Name == "3_FOAM_START")
		{
			Hydrax->setFoamStart(
				static_cast<Ogre::Real>(Value.getAsNumber()));
		}
		else if (Name == "3_FOAM_TRANS")
		{
			Hydrax->setFoamTransparency(
				static_cast<Ogre::Real>(Value.getAsNumber()));
		}
		// Depth
		else if (Name == "4_DEPTH_LIMIT")
		{
			Hydrax->setDepthLimit(
				static_cast<Ogre::Real>(Value.getAsNumber()));
		}
		// Smooth
		else if (Name == "5_SMOOTH_POWER")
		{
			Hydrax->setSmoothPower(
				static_cast<Ogre::Real>(Value.getAsNumber()));
		}
		// Caustics
		else if (Name == "6_CAUSTICS_SCALE")
		{
			Hydrax->setCausticsScale(
				static_cast<Ogre::Real>(Value.getAsNumber()));
		}
		else if (Name == "6_CAUSTICS_POWER")
		{
			Hydrax->setCausticsPower(
				static_cast<Ogre::Real>(Value.getAsNumber()));
		}
		else if (Name == "6_CAUSTICS_END")
		{
			Hydrax->setCausticsEnd(
				static_cast<Ogre::Real>(Value.getAsNumber()));
		}
		else if (Name == "7_GODRAYS_EXPOSURE")
		{
			Hydrax->setGodRaysExposure(
				RBGuiHelp::MochaVector3ToOgreVector3(Value.getAsVector3()));
		}
		else if (Name == "7_GODRAYS_INTENSITY")
		{
			Hydrax->setGodRaysIntensity(
				static_cast<Ogre::Real>(Value.getAsNumber()));
		}
	}
}