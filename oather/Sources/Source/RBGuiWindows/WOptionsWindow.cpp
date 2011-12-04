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

#include "WOptionsWindow.h"
#include "../EditorApp.h"

namespace HydraxEditor
{
	WOptionsWindow::WOptionsWindow(Mocha::RefPointer<RBGui::GuiManager> gm)
		: RBGuiWindowBase(gm)
		, mAttributeEditWidget(0)
	{
	}

	WOptionsWindow::~WOptionsWindow()
	{
	}

	void WOptionsWindow::create()
	{
		mWindow = mGuiManager->createWindow();
		mWindow->setBorderVisible(true);
		mWindow->setHideOnClose(true);
		mWindow->setText("Water options");
		mWindow->setSize(Mocha::Vector2(200, 520));
		mWindow->setPosition(Mocha::Vector2(10,30));
		mWindow->setCallback(&WOptionsWindow::resizedCallback, this, "Resized");
		mWindow->setCallback(&WOptionsWindow::closedCallback,  this, "Close_Hide");
		mWindow->show();

		mAttributeEditWidget = static_cast<RBGui::AttributeEditWidget*>( mWindow->createWidget( "AttributeEdit" ) );
		mAttributeEditWidget->setCallback(&WOptionsWindow::callback, this);
		mAttributeEditWidget->setSize( mWindow->getClientRectangle().getSize());
		mAttributeEditWidget->setName( "WOptionsWindow_AttributeEditWidget" );
		
		addAttributes();
	}

	void WOptionsWindow::addAttributes(const Ogre::String& SelectedModule_, const Ogre::String& SelectedNoise_)
	{
		// Get our Hydrax pointer
		Hydrax::Hydrax* Hydrax = EditorApp::getSingleton()->getHydraxManager()->getHydrax();

		// Be sure that it isn't NULL
		if(!Hydrax)
		{
			return;
		}

		RBGui::AttributeMap AttributeMap;

		// Add attributes
		addGeometryModuleAttributes(AttributeMap, SelectedModule_);
		addNoiseModuleAttributes(AttributeMap, SelectedNoise_);
		addComponentsAttributes(AttributeMap);
		addRttAttributes(AttributeMap);

		// Set our attribute map
	    mAttributeEditWidget->setAttributes(AttributeMap);

		// Update attributes
		updateAttributes();
	}

	void WOptionsWindow::updateAttributes()
	{
		// PG module
		mAttributeEditWidget->updateOptions("1_PG_COMPLEXITY", RBGuiHelp::getVectorAttributeWidgetParams(1, 2, 700));
		mAttributeEditWidget->updateOptions("1_PG_ELEVATION", RBGuiHelp::getVectorAttributeWidgetParams(0.5, 0, 50));
		mAttributeEditWidget->updateOptions("1_PG_STRENGTH", RBGuiHelp::getVectorAttributeWidgetParams(0.75, 0, 200));

		// SG module
		mAttributeEditWidget->updateOptions("1_SG_COMPLEXITY", RBGuiHelp::getVectorAttributeWidgetParams(1, 2, 700));
		mAttributeEditWidget->updateOptions("1_SG_STRENGTH", RBGuiHelp::getVectorAttributeWidgetParams(0.75, 0, 200));

		// RG module
        

		// Perlin noise
		mAttributeEditWidget->updateOptions("2_PERLIN_OCTAVES", RBGuiHelp::getVectorAttributeWidgetParams(1, 0, 32));
		mAttributeEditWidget->updateOptions("2_PERLIN_SCALE", RBGuiHelp::getVectorAttributeWidgetParams(0.05, 0, 100));
		mAttributeEditWidget->updateOptions("2_PERLIN_FALLOFF", RBGuiHelp::getVectorAttributeWidgetParams(0.05, 0, 30));
		mAttributeEditWidget->updateOptions("2_PERLIN_ANIM_SPEED", RBGuiHelp::getVectorAttributeWidgetParams(0.2, 0, 30));
		mAttributeEditWidget->updateOptions("2_PERLIN_TIME_MULTI", RBGuiHelp::getVectorAttributeWidgetParams(0.2, 0, 30));

		// FFT noise
        mAttributeEditWidget->updateOptions("2_FFT_PHY_RESOLUTION", RBGuiHelp::getVectorAttributeWidgetParams(1, 0, 1000));
		mAttributeEditWidget->updateOptions("2_FFT_SCALE", RBGuiHelp::getVectorAttributeWidgetParams(0.025, 0, 1000));
		mAttributeEditWidget->updateOptions("2_FFT_KWPOWER", RBGuiHelp::getVectorAttributeWidgetParams(2, 2, 400));
	}

	void WOptionsWindow::addGeometryModuleAttributes(RBGui::AttributeMap &AttributeMap, const Ogre::String& SelectedModule_)
	{
		Hydrax::Hydrax* Hydrax = EditorApp::getSingleton()->getHydraxManager()->getHydrax();

		Ogre::String SelectedModule = "NULL";

		if (SelectedModule_ == "NULL")
		{
			SelectedModule = Hydrax->getModule()->getName();
		}
		else
		{
			SelectedModule = SelectedModule_;
		}

		AttributeMap["1-Geometry module"].push_back( RBGui::AttributeEntry( "Module",  "1_MODULE", "list|ProjectedGridVertex|ProjectedGridRtt|SimpleGridVertex|SimpleGridRtt|RadialGridVertex|RadialGridRtt", SelectedModule));
		
		if (SelectedModule == "ProjectedGridVertex" || SelectedModule == "ProjectedGridRtt")
		{ 
			Hydrax::Module::ProjectedGrid::Options PG_Options = 
				static_cast<Hydrax::Module::ProjectedGrid*>
				   (EditorApp::getSingleton()->getHydraxManager()->getGeometryModule(SelectedModule))
				       ->getOptions();

			AttributeMap["1-Geometry module"].push_back( RBGui::AttributeEntry( "Complexity", "1_PG_COMPLEXITY", "int", PG_Options.Complexity ));
			AttributeMap["1-Geometry module"].push_back( RBGui::AttributeEntry( "Elevation", "1_PG_ELEVATION", "float", PG_Options.Elevation ));
			AttributeMap["1-Geometry module"].push_back( RBGui::AttributeEntry( "Smooth", "1_PG_SMOOTH", "bool", PG_Options.Smooth ));
			AttributeMap["1-Geometry module"].push_back( RBGui::AttributeEntry( "Strength", "1_PG_STRENGTH", "float", PG_Options.Strength ));
			AttributeMap["1-Geometry module"].push_back( RBGui::AttributeEntry( "Force recalculate geom.", "1_PG_FORCE_RECALCULATE_GEOMETRY", "bool", PG_Options.ForceRecalculateGeometry ));
			AttributeMap["1-Geometry module"].push_back( RBGui::AttributeEntry( "Choppy waves", "1_PG_CHOPPY_WAVES", "bool", PG_Options.ChoppyWaves ));
			AttributeMap["1-Geometry module"].push_back( RBGui::AttributeEntry( "Choppy strength", "1_PG_CHOPPY_WAVES_STRENGTH", "float", PG_Options.ChoppyStrength ));
		} 
		else if (SelectedModule == "SimpleGridVertex" || SelectedModule == "SimpleGridRtt")
		{
			Hydrax::Module::SimpleGrid::Options SG_Options = 
				static_cast<Hydrax::Module::SimpleGrid*>
				   (EditorApp::getSingleton()->getHydraxManager()->getGeometryModule(SelectedModule))
				       ->getOptions();
			
			AttributeMap["1-Geometry module"].push_back( RBGui::AttributeEntry( "Complexity", "1_SG_COMPLEXITY", "int", SG_Options.Complexity ));
			AttributeMap["1-Geometry module"].push_back( RBGui::AttributeEntry( "Size", "1_SG_SIZE", "vector2", 
				Mocha::Vector2(SG_Options.MeshSize.Width, SG_Options.MeshSize.Height) ));
			AttributeMap["1-Geometry module"].push_back( RBGui::AttributeEntry( "Smooth", "1_SG_SMOOTH", "bool", SG_Options.Smooth ));
			AttributeMap["1-Geometry module"].push_back( RBGui::AttributeEntry( "Strength", "1_SG_STRENGTH", "float", SG_Options.Strength ));
			AttributeMap["1-Geometry module"].push_back( RBGui::AttributeEntry( "Choppy waves", "1_SG_CHOPPY_WAVES", "bool", SG_Options.ChoppyWaves ));
			AttributeMap["1-Geometry module"].push_back( RBGui::AttributeEntry( "Choppy strength", "1_SG_CHOPPY_WAVES_STRENGTH", "float", SG_Options.ChoppyStrength ));
		} 
		else if (SelectedModule == "RadialGridVertex" || SelectedModule == "RadialGridRtt")
		{
			Hydrax::Module::RadialGrid::Options RG_Options = 
				static_cast<Hydrax::Module::RadialGrid*>
				   (EditorApp::getSingleton()->getHydraxManager()->getGeometryModule(SelectedModule))
				       ->getOptions();

			AttributeMap["1-Geometry module"].push_back( RBGui::AttributeEntry( "Steps", "1_RG_STEPS", "int", RG_Options.Steps ));
			AttributeMap["1-Geometry module"].push_back( RBGui::AttributeEntry( "Circles", "1_RG_CIRCLES", "int", RG_Options.Circles ));
			AttributeMap["1-Geometry module"].push_back( RBGui::AttributeEntry( "Radius", "1_RG_RADIUS", "float", RG_Options.Radius ));
			AttributeMap["1-Geometry module"].push_back( RBGui::AttributeEntry( "Step size lin", "1_RG_SSL", "float", RG_Options.StepSizeLin ));
			AttributeMap["1-Geometry module"].push_back( RBGui::AttributeEntry( "Step size cube", "1_RG_SS3", "float", RG_Options.StepSizeCube ));
			AttributeMap["1-Geometry module"].push_back( RBGui::AttributeEntry( "Step size five", "1_RG_SS5", "float", RG_Options.StepSizeFive ));
			AttributeMap["1-Geometry module"].push_back( RBGui::AttributeEntry( "Smooth", "1_RG_SMOOTH", "bool", RG_Options.Smooth ));
			AttributeMap["1-Geometry module"].push_back( RBGui::AttributeEntry( "Strength", "1_RG_STRENGTH", "float", RG_Options.Strength ));
			AttributeMap["1-Geometry module"].push_back( RBGui::AttributeEntry( "Choppy waves", "1_RG_CHOPPY_WAVES", "bool", RG_Options.ChoppyWaves ));
			AttributeMap["1-Geometry module"].push_back( RBGui::AttributeEntry( "Choppy strength", "1_RG_CHOPPY_WAVES_STRENGTH", "float", RG_Options.ChoppyStrength ));
		}
	}

	void WOptionsWindow::addNoiseModuleAttributes(RBGui::AttributeMap &AttributeMap, const Ogre::String& SelectedNoise_)
	{
		Hydrax::Hydrax* Hydrax = EditorApp::getSingleton()->getHydraxManager()->getHydrax();

		Ogre::String SelectedNoise = "NULL";

		if (SelectedNoise_ == "NULL")
		{
			SelectedNoise = Hydrax->getModule()->getNoise()->getName();
		}
		else
		{
			SelectedNoise = SelectedNoise_;
		}

		AttributeMap["2-Noise module"].push_back( RBGui::AttributeEntry( "Module", "2_NOISE", "list|Perlin|FFT", SelectedNoise));

		if (SelectedNoise == "Perlin")
		{
			Hydrax::Noise::Perlin::Options PN_Options = 
				static_cast<Hydrax::Noise::Perlin*>
				(EditorApp::getSingleton()->getHydraxManager()->getNoiseModule(SelectedNoise))
				    ->getOptions();

			AttributeMap["2-Noise module"].push_back( RBGui::AttributeEntry( "Octaves(2^n)", "2_PERLIN_OCTAVES", "int", PN_Options.Octaves ));
			AttributeMap["2-Noise module"].push_back( RBGui::AttributeEntry( "Scale", "2_PERLIN_SCALE", "float", PN_Options.Scale ));
			AttributeMap["2-Noise module"].push_back( RBGui::AttributeEntry( "Fall off", "2_PERLIN_FALLOFF", "float", PN_Options.Falloff ));
			AttributeMap["2-Noise module"].push_back( RBGui::AttributeEntry( "Anim. Speed", "2_PERLIN_ANIM_SPEED", "float", PN_Options.Animspeed ));
			AttributeMap["2-Noise module"].push_back( RBGui::AttributeEntry( "Time multi.", "2_PERLIN_TIME_MULTI", "float", PN_Options.Timemulti ));
			AttributeMap["2-Noise module"].push_back( RBGui::AttributeEntry( "GPU Strength", "2_PERLIN_GPU_STRENGTH", "float", PN_Options.GPU_Strength ));
			AttributeMap["2-Noise module"].push_back( RBGui::AttributeEntry( "GPU LOD", "2_PERLIN_GPU_LOD", "vector3", RBGuiHelp::OgreVector3ToMochaVector3(PN_Options.GPU_LODParameters) ));
		} 
		else if (SelectedNoise == "FFT")
		{
			Hydrax::Noise::FFT::Options FFT_Options = 
				static_cast<Hydrax::Noise::FFT*>
				(EditorApp::getSingleton()->getHydraxManager()->getNoiseModule(SelectedNoise))
				    ->getOptions();

			AttributeMap["2-Noise module"].push_back( RBGui::AttributeEntry( "Resolution(2^n)", "2_FFT_RESOLUTION", "int", FFT_Options.Resolution ));
			AttributeMap["2-Noise module"].push_back( RBGui::AttributeEntry( "Physical resolution", "2_FFT_PHY_RESOLUTION", "float", FFT_Options.PhysicalResolution ));
			AttributeMap["2-Noise module"].push_back( RBGui::AttributeEntry( "Scale", "2_FFT_SCALE", "float", FFT_Options.Scale ));
			AttributeMap["2-Noise module"].push_back( RBGui::AttributeEntry( "Wind direction", "2_FFT_WIND", "vector2", RBGuiHelp::OgreVector2ToMochaVector2(FFT_Options.WindDirection) ));
			AttributeMap["2-Noise module"].push_back( RBGui::AttributeEntry( "Animation speed", "2_FFT_AN_SPEED", "float", FFT_Options.AnimationSpeed ));
			AttributeMap["2-Noise module"].push_back( RBGui::AttributeEntry( "KwPower(2n)", "2_FFT_KWPOWER", "float", FFT_Options.KwPower ));
			AttributeMap["2-Noise module"].push_back( RBGui::AttributeEntry( "Amplitude", "2_FFT_AMPLITUDE", "float", FFT_Options.Amplitude ));
			AttributeMap["2-Noise module"].push_back( RBGui::AttributeEntry( "GPU Strength", "2_FFT_GPU_STRENGTH", "float", FFT_Options.GPU_Strength ));
			AttributeMap["2-Noise module"].push_back( RBGui::AttributeEntry( "GPU LOD", "2_FFT_GPU_LOD", "vector3", RBGuiHelp::OgreVector3ToMochaVector3(FFT_Options.GPU_LODParameters) ));
		}
	}

	void WOptionsWindow::addComponentsAttributes(RBGui::AttributeMap &AttributeMap)
	{
		Hydrax::Hydrax* Hydrax = EditorApp::getSingleton()->getHydraxManager()->getHydrax();

		AttributeMap["3-Components"].push_back( RBGui::AttributeEntry( "Sun",               "3_SUN", "bool", 
			Hydrax->isComponent(Hydrax::HYDRAX_COMPONENT_SUN)));
		AttributeMap["3-Components"].push_back( RBGui::AttributeEntry( "Foam",              "3_FOAM", "bool", 
			Hydrax->isComponent(Hydrax::HYDRAX_COMPONENT_FOAM)));
		AttributeMap["3-Components"].push_back( RBGui::AttributeEntry( "Depth",             "3_DEPTH", "bool", 
			Hydrax->isComponent(Hydrax::HYDRAX_COMPONENT_DEPTH)));
		AttributeMap["3-Components"].push_back( RBGui::AttributeEntry( "Smooth transitions","3_SMOOTH", "bool", 
			Hydrax->isComponent(Hydrax::HYDRAX_COMPONENT_SMOOTH)));
		AttributeMap["3-Components"].push_back( RBGui::AttributeEntry( "Caustics",          "3_CAUSTICS","bool", 
			Hydrax->isComponent(Hydrax::HYDRAX_COMPONENT_CAUSTICS)));
		AttributeMap["3-Components"].push_back( RBGui::AttributeEntry( "Underwater",        "3_UNDERWATER","bool", 
			Hydrax->isComponent(Hydrax::HYDRAX_COMPONENT_UNDERWATER)));
		AttributeMap["3-Components"].push_back( RBGui::AttributeEntry( "Und. Reflections",  "3_UNDERWATER_REFLECTIONS","bool", 
			Hydrax->isComponent(Hydrax::HYDRAX_COMPONENT_UNDERWATER_REFLECTIONS)));
		AttributeMap["3-Components"].push_back( RBGui::AttributeEntry( "God rays",          "3_GODRAYS","bool", 
			Hydrax->isComponent(Hydrax::HYDRAX_COMPONENT_UNDERWATER_GODRAYS)));
	}

	void WOptionsWindow::addRttAttributes(RBGui::AttributeMap &AttributeMap)
	{
		AttributeMap["4-Rtt quality"].push_back( RBGui::AttributeEntry( "Reflection", "4_REFLECTION_QUA", "list|128x128|256x256|512x512|1024x1024|Auto", "Auto" ));
		AttributeMap["4-Rtt quality"].push_back( RBGui::AttributeEntry( "Refraction", "4_REFRACTION_QUA", "list|128x128|256x256|512x512|1024x1024|Auto", "Auto" ));
		AttributeMap["4-Rtt quality"].push_back( RBGui::AttributeEntry( "Depth",      "4_DEPTH_QUA", "list|128x128|256x256|512x512|1024x1024|Auto", "Auto" ));
		AttributeMap["4-Rtt quality"].push_back( RBGui::AttributeEntry( "Underater reflections depth", "4_UNDERWATER_REFLECTIONS_DEPTH_QUA", "list|128x128|256x256|512x512|1024x1024|Auto", "Auto" ));
	}

	void WOptionsWindow::callback(RBGui::GuiElement& vElement, const Mocha::ValueList& vData)
	{
		// Get the name of the attribute
	    const Mocha::String& Name = vData[0].getAsString();

	    // Get the value of the attribute
	    const Mocha::Value& Value = vData[1];

		// Split our name
		std::vector<Ogre::String> NameSplitted = Ogre::StringUtil::split(Name.c_str(), "_");

	    // Proccess
		// Geometry module options
	    if (NameSplitted[0] == "1" || Name == "1_MODULE")
		{
			if (Name == "1_MODULE")
			{
				Mocha::String Module = Value.getAsString();
			    addAttributes(Module, "NULL");
			}

			Mocha::Value Module = RBGuiHelp::getValueFromAttributeWidget(mAttributeEditWidget, "1_MODULE");
			Mocha::Value Noise  = RBGuiHelp::getValueFromAttributeWidget(mAttributeEditWidget, "2_NOISE");

			Hydrax::Hydrax* Hydrax = EditorApp::getSingleton()->getHydraxManager()->getHydrax();

			// Projected grid module
			if (Module.getAsString() == "ProjectedGridVertex" || Module.getAsString() == "ProjectedGridRtt")
			{
				if ((Hydrax->getModule()->getName() == "ProjectedGridVertex" && Module.getAsString() != "ProjectedGridRtt") || 
					(Hydrax->getModule()->getName() == "ProjectedGridRtt"    && Module.getAsString() != "ProjectedGridVertex"))
				{
					// Only update the options
					Hydrax::Module::ProjectedGrid::Options PG_Options;

					PG_Options.Complexity = static_cast<int>(RBGuiHelp::getValueFromAttributeWidget(mAttributeEditWidget, "1_PG_COMPLEXITY").getAsNumber());
					PG_Options.Elevation = RBGuiHelp::getValueFromAttributeWidget(mAttributeEditWidget, "1_PG_ELEVATION").getAsNumber();
					PG_Options.ForceRecalculateGeometry = RBGuiHelp::getValueFromAttributeWidget(mAttributeEditWidget, "1_PG_FORCE_RECALCULATE_GEOMETRY").getAsBool();
					PG_Options.Smooth = RBGuiHelp::getValueFromAttributeWidget(mAttributeEditWidget, "1_PG_SMOOTH").getAsBool();
					PG_Options.Strength = RBGuiHelp::getValueFromAttributeWidget(mAttributeEditWidget, "1_PG_STRENGTH").getAsNumber();
					PG_Options.ChoppyWaves = RBGuiHelp::getValueFromAttributeWidget(mAttributeEditWidget, "1_PG_CHOPPY_WAVES").getAsBool();
					PG_Options.ChoppyStrength = RBGuiHelp::getValueFromAttributeWidget(mAttributeEditWidget, "1_PG_CHOPPY_WAVES_STRENGTH").getAsNumber();

					static_cast<Hydrax::Module::ProjectedGrid*>
						(Hydrax->getModule())->setOptions(PG_Options);

				}
				else // Change the module
				{
					Hydrax->setModule(EditorApp::getSingleton()->getHydraxManager()->getGeometryModule(Module.getAsString()), false);
					// Change noise
					Hydrax->getModule()->setNoise(EditorApp::getSingleton()->getHydraxManager()->getNoiseModule(Noise.getAsString()), EditorApp::getSingleton()->getHydraxManager()->getHydrax()->getGPUNormalMapManager(), false);
					// Add our components attributes
			        addAttributes();
				}
			}

			// Simple grid module
			if (Module.getAsString() == "SimpleGridVertex" || Module.getAsString() == "SimpleGridRtt")
			{
				if ((Hydrax->getModule()->getName() == "SimpleGridVertex" && Module.getAsString() != "SimpleGridRtt") || 
					(Hydrax->getModule()->getName() == "SimpleGridRtt"    && Module.getAsString() != "SimpleGridVertex"))
				{
					// Only update the options
					Hydrax::Module::SimpleGrid::Options SG_Options;

					SG_Options.Complexity = static_cast<int>(RBGuiHelp::getValueFromAttributeWidget(mAttributeEditWidget, "1_SG_COMPLEXITY").getAsNumber());
					SG_Options.Smooth = RBGuiHelp::getValueFromAttributeWidget(mAttributeEditWidget, "1_SG_SMOOTH").getAsBool();
					SG_Options.Strength = RBGuiHelp::getValueFromAttributeWidget(mAttributeEditWidget, "1_SG_STRENGTH").getAsNumber();
					SG_Options.MeshSize = Hydrax::Size(
						RBGuiHelp::getValueFromAttributeWidget(mAttributeEditWidget, "1_SG_SIZE").getAsVector2().x,
						RBGuiHelp::getValueFromAttributeWidget(mAttributeEditWidget, "1_SG_SIZE").getAsVector2().y);
					SG_Options.ChoppyWaves = RBGuiHelp::getValueFromAttributeWidget(mAttributeEditWidget, "1_SG_CHOPPY_WAVES").getAsBool();
					SG_Options.ChoppyStrength = RBGuiHelp::getValueFromAttributeWidget(mAttributeEditWidget, "1_SG_CHOPPY_WAVES_STRENGTH").getAsNumber();

					static_cast<Hydrax::Module::SimpleGrid*>
						(Hydrax->getModule())->setOptions(SG_Options);

				}
				else // Change the module
				{
					Hydrax->setModule(EditorApp::getSingleton()->getHydraxManager()->getGeometryModule(Module.getAsString()), false);
					// Change noise
					Hydrax->getModule()->setNoise(EditorApp::getSingleton()->getHydraxManager()->getNoiseModule(Noise.getAsString()), EditorApp::getSingleton()->getHydraxManager()->getHydrax()->getGPUNormalMapManager(), false);
					// Add our components attributes
			        addAttributes();
				}
			}

		    // Radial grid module
			if (Module.getAsString() == "RadialGridVertex" || Module.getAsString() == "RadialGridRtt")
			{
				if ((Hydrax->getModule()->getName() == "RadialGridVertex" && Module.getAsString() != "RadialGridRtt") || 
					(Hydrax->getModule()->getName() == "RadialGridRtt"    && Module.getAsString() != "RadialGridVertex"))
				{
					// Only update the options
					Hydrax::Module::RadialGrid::Options RG_Options;

					RG_Options.Steps = static_cast<int>(RBGuiHelp::getValueFromAttributeWidget(mAttributeEditWidget, "1_RG_STEPS").getAsNumber());
					RG_Options.Circles = static_cast<int>(RBGuiHelp::getValueFromAttributeWidget(mAttributeEditWidget, "1_RG_CIRCLES").getAsNumber());
                    RG_Options.Radius = RBGuiHelp::getValueFromAttributeWidget(mAttributeEditWidget, "1_RG_RADIUS").getAsNumber();
					RG_Options.Smooth = RBGuiHelp::getValueFromAttributeWidget(mAttributeEditWidget, "1_RG_SMOOTH").getAsBool();
					RG_Options.Strength = RBGuiHelp::getValueFromAttributeWidget(mAttributeEditWidget, "1_RG_STRENGTH").getAsNumber();
					RG_Options.ChoppyWaves = RBGuiHelp::getValueFromAttributeWidget(mAttributeEditWidget, "1_RG_CHOPPY_WAVES").getAsBool();
					RG_Options.ChoppyStrength = RBGuiHelp::getValueFromAttributeWidget(mAttributeEditWidget, "1_RG_CHOPPY_WAVES_STRENGTH").getAsNumber();
					RG_Options.StepSizeLin = RBGuiHelp::getValueFromAttributeWidget(mAttributeEditWidget, "1_RG_SSL").getAsNumber();
					RG_Options.StepSizeCube = RBGuiHelp::getValueFromAttributeWidget(mAttributeEditWidget, "1_RG_SS3").getAsNumber();
					RG_Options.StepSizeFive = RBGuiHelp::getValueFromAttributeWidget(mAttributeEditWidget, "1_RG_SS5").getAsNumber();

					static_cast<Hydrax::Module::RadialGrid*>
						(Hydrax->getModule())->setOptions(RG_Options);

				}
				else // Change the module
				{
					Hydrax->setModule(EditorApp::getSingleton()->getHydraxManager()->getGeometryModule(Module.getAsString()), false);
					// Change noise
					Hydrax->getModule()->setNoise(EditorApp::getSingleton()->getHydraxManager()->getNoiseModule(Noise.getAsString()), EditorApp::getSingleton()->getHydraxManager()->getHydrax()->getGPUNormalMapManager(), false);
					// Add our components attributes
			        addAttributes();
				}
			}
		}
		// Noise module options
		else if (NameSplitted[0] == "2" || Name == "2_NOISE")
		{
			if (Name == "2_NOISE")
			{
				Mocha::String Module = Value.getAsString();
			    addAttributes("NULL", Module);
			}

			Mocha::Value Noise = RBGuiHelp::getValueFromAttributeWidget(mAttributeEditWidget, "2_NOISE");
			Hydrax::Hydrax* Hydrax = EditorApp::getSingleton()->getHydraxManager()->getHydrax();

			// Perlin
			if (Noise.getAsString() == "Perlin")
			{
				if (Hydrax->getModule()->getNoise()->getName() == "Perlin")
				{
					// Update options
					Hydrax::Noise::Perlin::Options PN_Options;

					PN_Options.Octaves = static_cast<int>(RBGuiHelp::getValueFromAttributeWidget(mAttributeEditWidget, "2_PERLIN_OCTAVES").getAsNumber());
					PN_Options.Falloff = RBGuiHelp::getValueFromAttributeWidget(mAttributeEditWidget, "2_PERLIN_FALLOFF").getAsNumber();
					PN_Options.Animspeed = RBGuiHelp::getValueFromAttributeWidget(mAttributeEditWidget, "2_PERLIN_ANIM_SPEED").getAsNumber();
					PN_Options.Scale = RBGuiHelp::getValueFromAttributeWidget(mAttributeEditWidget, "2_PERLIN_SCALE").getAsNumber();
					PN_Options.Timemulti = RBGuiHelp::getValueFromAttributeWidget(mAttributeEditWidget, "2_PERLIN_TIME_MULTI").getAsNumber();
					PN_Options.GPU_Strength = RBGuiHelp::getValueFromAttributeWidget(mAttributeEditWidget, "2_PERLIN_GPU_STRENGTH").getAsNumber();
					PN_Options.GPU_LODParameters = RBGuiHelp::MochaVector3ToOgreVector3(RBGuiHelp::getValueFromAttributeWidget(mAttributeEditWidget, "2_PERLIN_GPU_LOD").getAsVector3());

					static_cast<Hydrax::Noise::Perlin*>
						(Hydrax->getModule()->getNoise())
					    	->setOptions(PN_Options);
				}
				else
				{
					// Change noise
					Hydrax->getModule()->setNoise(EditorApp::getSingleton()->getHydraxManager()->getNoiseModule(Noise.getAsString()), EditorApp::getSingleton()->getHydraxManager()->getHydrax()->getGPUNormalMapManager(), false);
				}
			}
			// FFT
			else if (Noise.getAsString() == "FFT")
			{
				if (Hydrax->getModule()->getNoise()->getName() == "FFT")
				{
					// Update options
					Hydrax::Noise::FFT::Options FFT_Options;

					FFT_Options.Resolution = static_cast<int>(RBGuiHelp::getValueFromAttributeWidget(mAttributeEditWidget, "2_FFT_RESOLUTION").getAsNumber());
					FFT_Options.PhysicalResolution = RBGuiHelp::getValueFromAttributeWidget(mAttributeEditWidget, "2_FFT_PHY_RESOLUTION").getAsNumber();
					FFT_Options.Scale = RBGuiHelp::getValueFromAttributeWidget(mAttributeEditWidget, "2_FFT_SCALE").getAsNumber();
					FFT_Options.WindDirection = RBGuiHelp::MochaVector2ToOgreVector2(RBGuiHelp::getValueFromAttributeWidget(mAttributeEditWidget, "2_FFT_WIND").getAsVector2());
					FFT_Options.AnimationSpeed = RBGuiHelp::getValueFromAttributeWidget(mAttributeEditWidget, "2_FFT_AN_SPEED").getAsNumber();
					FFT_Options.KwPower = RBGuiHelp::getValueFromAttributeWidget(mAttributeEditWidget, "2_FFT_KWPOWER").getAsNumber();
					FFT_Options.Amplitude =  RBGuiHelp::getValueFromAttributeWidget(mAttributeEditWidget, "2_FFT_AMPLITUDE").getAsNumber();
					FFT_Options.GPU_Strength = RBGuiHelp::getValueFromAttributeWidget(mAttributeEditWidget, "2_FFT_GPU_STRENGTH").getAsNumber();
					FFT_Options.GPU_LODParameters = RBGuiHelp::MochaVector3ToOgreVector3(RBGuiHelp::getValueFromAttributeWidget(mAttributeEditWidget, "2_FFT_GPU_LOD").getAsVector3());

					static_cast<Hydrax::Noise::FFT*>
						(Hydrax->getModule()->getNoise())
					    	->setOptions(FFT_Options);
				}
				else
				{
					// Change noise
					Hydrax->getModule()->setNoise(EditorApp::getSingleton()->getHydraxManager()->getNoiseModule(Noise.getAsString()), EditorApp::getSingleton()->getHydraxManager()->getHydrax()->getGPUNormalMapManager(), false);
				}
			}
		}
		// Components region
		else if (NameSplitted[0] == "3")
		{
			// Set current components
			EditorApp::getSingleton()->getHydraxManager()->getHydrax()
				->setComponents(getHydraxComponents());

			// Update our parameters window
			WParametersWindow* mWParametersWindow = static_cast<WParametersWindow*>(EditorApp::getSingleton()->getRBGuiManager()->getWindow("WParametersWindow"));
			mWParametersWindow->updateAttributes();

			// Add our components attributes
			addAttributes();
		}
		// Rtt textures's quality region
		else if (NameSplitted[0] == "4")
		{
			// Set current Rtt options
			setRttOptions(NameSplitted[1], Value);
		}
	}

	void WOptionsWindow::resizedCallback(RBGui::GuiElement& vElement, const Mocha::ValueList& vData)
	{
		mAttributeEditWidget->setSize(mWindow->getClientRectangle().getSize());
	}

	void WOptionsWindow::closedCallback(RBGui::GuiElement& vElement, const Mocha::ValueList& vData)
	{
		TopMenu* mTopMenu = static_cast<TopMenu*>(EditorApp::getSingleton()->getRBGuiManager()->getWindow("TopMenu"));

		mTopMenu->setItemSelect("VIEW_OPTIONS", false);
		mTopMenu->update();
	}

	Hydrax::HydraxComponent WOptionsWindow::getHydraxComponents() const
	{
		bool Sun = RBGuiHelp::getValueFromAttributeWidget(mAttributeEditWidget, "3_SUN").getAsBool();
		bool Foam = RBGuiHelp::getValueFromAttributeWidget(mAttributeEditWidget, "3_FOAM").getAsBool();
		bool Depth = RBGuiHelp::getValueFromAttributeWidget(mAttributeEditWidget, "3_DEPTH").getAsBool();
		bool Smooth = RBGuiHelp::getValueFromAttributeWidget(mAttributeEditWidget, "3_SMOOTH").getAsBool();
		bool Caustics = RBGuiHelp::getValueFromAttributeWidget(mAttributeEditWidget, "3_CAUSTICS").getAsBool();
		bool Underwater = RBGuiHelp::getValueFromAttributeWidget(mAttributeEditWidget, "3_UNDERWATER").getAsBool();
		bool UReflections = RBGuiHelp::getValueFromAttributeWidget(mAttributeEditWidget, "3_UNDERWATER_REFLECTIONS").getAsBool();
		bool GodRays = RBGuiHelp::getValueFromAttributeWidget(mAttributeEditWidget, "3_GODRAYS").getAsBool();

		Hydrax::HydraxComponent s  = Hydrax::HYDRAX_COMPONENTS_NONE,
			                    f  = Hydrax::HYDRAX_COMPONENTS_NONE,
								d  = Hydrax::HYDRAX_COMPONENTS_NONE,
								sm = Hydrax::HYDRAX_COMPONENTS_NONE,
								c  = Hydrax::HYDRAX_COMPONENTS_NONE,
								u  = Hydrax::HYDRAX_COMPONENTS_NONE,
								ur = Hydrax::HYDRAX_COMPONENTS_NONE,
								g  = Hydrax::HYDRAX_COMPONENTS_NONE;

		if (Sun)
		{
			s = Hydrax::HYDRAX_COMPONENT_SUN;
		}
		if (Foam)
		{
			f = Hydrax::HYDRAX_COMPONENT_FOAM;
		}
		if (Depth)
		{
			d = Hydrax::HYDRAX_COMPONENT_DEPTH;
		}
		if (Depth && Smooth)
		{
			sm = Hydrax::HYDRAX_COMPONENT_SMOOTH;
		}
		if (Depth && Caustics)
		{
			c = Hydrax::HYDRAX_COMPONENT_CAUSTICS;
		}
		if (Underwater)
		{
			u = Hydrax::HYDRAX_COMPONENT_UNDERWATER;
		}
		if (UReflections && Underwater)
		{
			ur = Hydrax::HYDRAX_COMPONENT_UNDERWATER_REFLECTIONS;
		}
		if (GodRays && Underwater && Depth)
		{
			g = Hydrax::HYDRAX_COMPONENT_UNDERWATER_GODRAYS;
		}

		return static_cast<Hydrax::HydraxComponent>(s|f|d|sm|c|u|ur|g);	
	}

	void WOptionsWindow::setRttOptions(const Mocha::String& Rtt, const Mocha::Value& Value)
	{
		Hydrax::Size RTT_Size = RBGuiHelp::MochaValueToHydraxSize(Value);

		Hydrax::RttManager* mRttManager = EditorApp::getSingleton()->getHydraxManager()->getHydrax()->getRttManager();
		Hydrax::RttManager::RttType RttType;

		if (Rtt == "REFLECTION")
		{
		    RttType = Hydrax::RttManager::RTT_REFLECTION;
		}
		else if (Rtt == "REFRACTION")
		{
			RttType = Hydrax::RttManager::RTT_REFRACTION;
		}
		else if (Rtt == "DEPTH")
		{
			RttType = Hydrax::RttManager::RTT_DEPTH;
		}
		else if (Rtt == "UNDERWATER")
		{
			RttType = Hydrax::RttManager::RTT_DEPTH_REFLECTION;
		}

		mRttManager->setTextureSize(RttType, RTT_Size);
	}
}