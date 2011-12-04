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

#include "HydraxManager.h"

namespace HydraxEditor
{
	HydraxManager::HydraxManager(Ogre::SceneManager *sm, Ogre::Camera *c, Ogre::Viewport *v)
		: mSceneMgr(sm)
		, mCamera(c)
		, mViewport(v)
		, mPalmsSceneNode(0)
		, mHydrax(0)
		, mCurrentSkyBox(0)
		, mLastWaterFilenameSaved("")
	{
		// Set some skybox/sun info
		Ogre::String mSkyBoxes_[5] = {"Sky/ClubTropicana",
			"Sky/Stormy",
			"Sky/EarlyMorning",
			"Sky/Evening",
		    "Sky/Clouds"};

		Ogre::Vector3 mSunPosition_[5] = {Ogre::Vector3(0,10000,0),
			Ogre::Vector3(0,10000,-90000),
			Ogre::Vector3(0,10000,90000),
			Ogre::Vector3(-62000,2000,50000),
		    Ogre::Vector3(0,10000,0)};

		Ogre::Vector3 mSunColor_[5] = {Ogre::Vector3(1, 0.9, 0.6),
			Ogre::Vector3(0.75, 0.65, 0.45),
			Ogre::Vector3(1,0.6,0.4),
			Ogre::Vector3(1,0.4,0.1),
		    Ogre::Vector3(0.45,0.45,0.45)};

		// Copy to our arrays
		for (int k = 0; k < 5; k++)
		{
			 mSkyBoxes[k] = mSkyBoxes_[k];
			 mSunPosition[k] = mSunPosition_[k];
             mSunColor[k] = mSunColor_[k];
		}
	}

	HydraxManager::~HydraxManager()
	{
		_removeNoiseModules();
		_removeGeometryModules();

		if (mPalmsSceneNode)
		{
			mPalmsSceneNode->detachAllObjects();
            mPalmsSceneNode->getParentSceneNode()->removeAndDestroyChild(mPalmsSceneNode->getName());
			mPalmsSceneNode = 0;

			for (int k = 0; k < 12; k++)
			{
				mSceneMgr->destroyEntity("Palm"+Ogre::StringConverter::toString(k));
			}
		}

		delete mHydrax;
	}

	void HydraxManager::create()
	{
        // Create the SkyBox
        mSceneMgr->setSkyBox(true, mSkyBoxes[mCurrentSkyBox], 99999*3, true);

		// Set some camera params
        mCamera->setFarClipDistance(99999*6);
		mCamera->setPosition(312.902,206.419,1524.02);
		mCamera->setOrientation(Ogre::Quaternion(0.998, -0.0121, -0.0608, -0.00074));

        // Create Hydrax object
		mHydrax = new Hydrax::Hydrax(mSceneMgr, mCamera, mViewport);

		// Add perlin noise module to our manager
		Hydrax::Noise::Noise* PerlinNoiseModule = new Hydrax::Noise::Perlin();
		_addNoiseModule(PerlinNoiseModule);

		// Add fft noise module to our manager
		Hydrax::Noise::Noise* FFTNoiseModule = new Hydrax::Noise::FFT();
		_addNoiseModule(FFTNoiseModule);

		// Add projected grid geometry module to the manager(Vertex normals)
		Hydrax::Module::ProjectedGrid *ProjectedGridGeometryModuleVertex 
			= new Hydrax::Module::ProjectedGrid(// Hydrax parent pointer
			                                    mHydrax,
												// Noise module
			                                    PerlinNoiseModule,
												// Base plane
												Ogre::Plane(Ogre::Vector3(0,1,0), Ogre::Vector3(0,0,0)),
												// Normal mode
												Hydrax::MaterialManager::NM_VERTEX,
												// Projected grid options (Can be updated each frame -> setOptions(...))
										        Hydrax::Module::ProjectedGrid::Options(/* See more constructors */));
		_addGeometryModule(ProjectedGridGeometryModuleVertex);

		// Add projected grid geometry module to the manager(Rtt normals)
		Hydrax::Module::ProjectedGrid *ProjectedGridGeometryModuleRtt
			= new Hydrax::Module::ProjectedGrid(// Hydrax parent pointer
			                                    mHydrax,
												// Noise module
			                                    PerlinNoiseModule,
												// Base plane
												Ogre::Plane(Ogre::Vector3(0,1,0), Ogre::Vector3(0,0,0)),
												// Normal mode
												Hydrax::MaterialManager::NM_RTT,
												// Projected grid options (Can be updated each frame -> setOptions(...))
										        Hydrax::Module::ProjectedGrid::Options(/* Default constructor */));
		_addGeometryModule(ProjectedGridGeometryModuleRtt);

		// Add the simple grid geometry module to our manager(Vertex normals)
		Hydrax::Module::SimpleGrid *SimpleGridGeometryModuleVertex
			= new Hydrax::Module::SimpleGrid(// Hydrax parent pointer
			                                 mHydrax,
									     	 // Noise module
			                                 PerlinNoiseModule,
											 // Normal mode
											 Hydrax::MaterialManager::NM_VERTEX,
											 // Simple grid options (Can be updated each frame -> setOptions(...))
											 Hydrax::Module::SimpleGrid::Options(512, Hydrax::Size(10000,10000) /* See more constructors */));
		_addGeometryModule(SimpleGridGeometryModuleVertex);

		// Add the simple grid geometry module to our manager(Rtt normals)
		Hydrax::Module::SimpleGrid *SimpleGridGeometryModuleRtt
			= new Hydrax::Module::SimpleGrid(// Hydrax parent pointer
			                                 mHydrax,
									     	 // Noise module
			                                 PerlinNoiseModule,
											 // Normal mode
											 Hydrax::MaterialManager::NM_RTT,
											 // Simple grid options (Can be updated each frame -> setOptions(...))
											 Hydrax::Module::SimpleGrid::Options(128, Hydrax::Size(10000,10000) /* See more constructors */));
		_addGeometryModule(SimpleGridGeometryModuleRtt);

		// Add the radial grid geometry module to our manager(Vertex normals)
		Hydrax::Module::RadialGrid *RadialGridGeometryModuleVertex
			= new Hydrax::Module::RadialGrid(// Hydrax parent pointer
			                                 mHydrax,
									     	 // Noise module
			                                 PerlinNoiseModule,
											 // Normal mode
											 Hydrax::MaterialManager::NM_VERTEX,
											 // Simple grid options (Can be updated each frame -> setOptions(...))
											 Hydrax::Module::RadialGrid::Options(250, 250, 6000  /* See more constructors */));
		_addGeometryModule(RadialGridGeometryModuleVertex);

		// Add the radial grid geometry module to our manager(Rtt normals)
		Hydrax::Module::RadialGrid *RadialGridGeometryModuleRtt
			= new Hydrax::Module::RadialGrid(// Hydrax parent pointer
			                                 mHydrax,
									     	 // Noise module
			                                 PerlinNoiseModule,
											 // Normal mode
											 Hydrax::MaterialManager::NM_RTT,
											 // Simple grid options (Can be updated each frame -> setOptions(...))
											 Hydrax::Module::RadialGrid::Options(80, 10, 6000  /* See more constructors */));
		_addGeometryModule(RadialGridGeometryModuleRtt);

	   /* // Set our shader mode
		mHydrax->setShaderMode(Hydrax::MaterialManager::SM_HLSL);

		// Set components
		mHydrax->setComponents(
            static_cast<Hydrax::HydraxComponent>(Hydrax::HYDRAX_COMPONENT_SUN        |
                                                 Hydrax::HYDRAX_COMPONENT_FOAM       |
                                                 Hydrax::HYDRAX_COMPONENT_DEPTH      |
                                                 Hydrax::HYDRAX_COMPONENT_SMOOTH     |
                                                 Hydrax::HYDRAX_COMPONENT_CAUSTICS   |
												 Hydrax::HYDRAX_COMPONENT_UNDERWATER |
												 Hydrax::HYDRAX_COMPONENT_UNDERWATER_REFLECTIONS |
												 Hydrax::HYDRAX_COMPONENT_UNDERWATER_GODRAYS));*/

		// Set our module (Initial module)
		mHydrax->setModule(static_cast<Hydrax::Module::Module*>(ProjectedGridGeometryModuleVertex));
mHydrax->loadCfg("DefaultEditorWater.hdx");

        // Create water
        mHydrax->create();

        // Adjust some options
     /*   mHydrax->setPosition(Ogre::Vector3(1500,100,1500)); // Just for simple grid (Projected grid doesn't use it)
        mHydrax->setPlanesError(10.5);
        mHydrax->setDepthLimit(90);
        mHydrax->setSunPosition(mSunPosition[mCurrentSkyBox]);
        mHydrax->setSunColor(mSunColor[mCurrentSkyBox]);
        mHydrax->setNormalDistortion(0.075);
        mHydrax->setWaterColor(Ogre::Vector3(0.139765,0.359464,0.425373));
        mHydrax->setSmoothPower(5);
		mHydrax->setCausticsScale(135);
		mHydrax->setCausticsEnd(0.8);
		mHydrax->setCausticsPower(10.5);
        mHydrax->setFullReflectionDistance(99999997952);
		mHydrax->setGlobalTransparency(0); 

		mHydrax->saveCfg("HydraxWater1.hdx");
		mHydrax->loadCfg("HydraxWater1.hdx");*/

        // Lights
		mSceneMgr->setAmbientLight(Ogre::ColourValue(1, 1, 1));
		Ogre::Light *mLight = mSceneMgr->createLight("Light0");
		mLight->setPosition(mSunPosition[mCurrentSkyBox]);
		mLight->setDiffuseColour(1, 1, 1);
		mLight->setSpecularColour(mSunColor[mCurrentSkyBox].x,mSunColor[mCurrentSkyBox].y,mSunColor[mCurrentSkyBox].z);

		// Island
		mSceneMgr->setWorldGeometry("Island.cfg");
		
		mHydrax->getMaterialManager()->addDepthTechnique(
			static_cast<Ogre::MaterialPtr>(Ogre::MaterialManager::getSingleton().getByName("Island"))
			->createTechnique());

		// Palmiers...
		_createPalms();
/*
		mHydrax->getMaterialManager()->addDepthTextureTechnique(
			static_cast<Ogre::MaterialPtr>(Ogre::MaterialManager::getSingleton().getByName("Palm"))
			->createTechnique(), "PalmAlpha.png", "a");*/

		// Shadows...
		//mSceneMgr->setShadowTechnique(Ogre::SHADOWTYPE_TEXTURE_ADDITIVE);
		//mSceneMgr->setShadowColour(Ogre::ColourValue(0.2,0.2,0.2));

		// Try decals
		//mHydrax->getDecalsManager()->add("SeaStar.png")->getSceneNode()->setPosition(0, 25, 0);
		/*
		for(int k = 0; k < 5; k++)
		{
			Hydrax::Decal *NewDecal = mHydrax->getDecalsManager()->add("WaterVegetable.png");

			NewDecal->setPosition(Ogre::Vector2(Ogre::Math::RangeRandom(-600,600),
												Ogre::Math::RangeRandom(-600,600)));

			NewDecal->setOrientation(Ogre::Degree(Ogre::Math::RangeRandom(0, 360)));
			NewDecal->setSize(Ogre::Vector2(80,80));
			NewDecal->setTransparency(Ogre::Math::RangeRandom(0,1));
		}*/

	/*	Hydrax::Noise::Noise *mFFT = new Hydrax::Noise::FFT();
		mFFT->create();
		mFFT->update(0.001f);

		for(int k = 0; k < 10000; k ++)
		{
			mFFT->update(0.001*k);
			std::cout << mFFT->getValue(123.3f, 12344.45f) << "      " << 0.001*k << std::endl;
		}

	    mFFT->remove();

	    delete mFFT;*/
	}

	/** Just to locate palmiers with a pseudo-random algoritm
	 */
	float seed_ = 801;
	float rnd_(const float& min, const float& max)
	{
		seed_ += Ogre::Math::PI*2.8574f + seed_*(0.3424f - 0.12434f + 0.452345f);
		if (seed_ > 10000000000) seed_ -= 10000000000;
		return ((max-min)*Ogre::Math::Abs(Ogre::Math::Sin(Ogre::Radian(seed_))) + min);
	}

	void HydraxManager::_createPalms()
	{
		const int NumberOfPalms = 12;

		mPalmsSceneNode = mSceneMgr->getRootSceneNode()->createChildSceneNode();
		
		for (int k = 0; k < NumberOfPalms; k++)
		{
			Ogre::Vector3 RandomPos = Ogre::Vector3(rnd_(500,2500),
				                                    0,
				                                    rnd_(500,2500));

			Ogre::RaySceneQuery * raySceneQuery = mSceneMgr->
			     createRayQuery(Ogre::Ray(RandomPos + Ogre::Vector3(0,1000000,0), 
				                          Ogre::Vector3::NEGATIVE_UNIT_Y));

		    Ogre::RaySceneQueryResult& qryResult = raySceneQuery->execute();
            Ogre::RaySceneQueryResult::iterator i = qryResult.begin();

			if (i != qryResult.end() && i->worldFragment)
			{
				if (i->worldFragment->singleIntersection.y>105 || i->worldFragment->singleIntersection.y<20)
				{
					k--;
					continue;
				}

				RandomPos.y = i->worldFragment->singleIntersection.y;
			}
			else
			{
				k--;
				continue;
			}

			Ogre::Entity *mPalmEnt = mSceneMgr->createEntity("Palm"+Ogre::StringConverter::toString(k), "Palm.mesh");
			Ogre::SceneNode *mPalmSN = mPalmsSceneNode->createChildSceneNode();

			mPalmSN->rotate(Ogre::Vector3(-1,0,rnd_(-0.3,0.3)), Ogre::Degree(90));
			mPalmSN->attachObject(mPalmEnt);
			Ogre::Real Scale = rnd_(50,75);
			mPalmSN->scale(Scale,Scale,Scale);
			mPalmSN->setPosition(RandomPos);
		}
	}

	bool HydraxManager::loadCfgFile(const Ogre::String& PathName)
	{
		std::vector<Ogre::String> PathNameSpplited = Ogre::StringUtil::split(PathName, "/");
		size_t PathNameSpplitedSize = PathNameSpplited.size();

		// Check if the selected file is in Hydrax resource group and if not, add to it.
		if (!Ogre::ResourceGroupManager::getSingleton().resourceExists("Hydrax", PathNameSpplited[PathNameSpplitedSize-1]))
		{
			Ogre::String Path = "";

			for (unsigned int k = 0; k < PathNameSpplitedSize-1; k++)
			{
				Path += PathNameSpplited[k];

				if (k != PathNameSpplitedSize-1)
				{
					Path += "/";
				}
			}

			try
		    {
			    Ogre::ResourceGroupManager::getSingleton().removeResourceLocation(Path, "Hydrax");
		    }
		    catch(...)
		    {
		    }

			Ogre::ResourceGroupManager::getSingleton().addResourceLocation(Path, "FileSystem", "Hydrax");
		}

		// Select the new module
		Ogre::ConfigFile CfgFile;
		CfgFile.load(Ogre::ResourceGroupManager::getSingleton().openResource(PathNameSpplited[PathNameSpplitedSize-1], "Hydrax"));
		mHydrax->setModule(getGeometryModule(CfgFile.getSetting("Module")), false);
		mHydrax->getModule()->setNoise(getNoiseModule(CfgFile.getSetting("Noise")), mHydrax->getGPUNormalMapManager(), false);

		mLastWaterFilenameLoaded = PathNameSpplited[PathNameSpplitedSize-1];

		return mHydrax->loadCfg(PathNameSpplited[PathNameSpplitedSize-1]);
	}

	bool HydraxManager::saveCfgFile(const Ogre::String& PathName)
	{
		std::vector<Ogre::String> PathNameSpplited = Ogre::StringUtil::split(PathName, "/");
		size_t PathNameSpplitedSize = PathNameSpplited.size();

		Ogre::String Path = "";
		for (unsigned int k = 0; k < PathNameSpplitedSize-1; k++)
		{
			Path += PathNameSpplited[k];

			if (k != PathNameSpplitedSize-1)
			{
				Path += "/";
			}
		}

		mLastWaterFilenameSaved = PathNameSpplited[PathNameSpplitedSize-1];

		return mHydrax->saveCfg(PathNameSpplited[PathNameSpplitedSize-1], Path);
	}

	void HydraxManager::_addGeometryModule(Hydrax::Module::Module* m)
	{
		mModules.push_back(m);
	}

	Hydrax::Module::Module* HydraxManager::getGeometryModule(const Ogre::String& Name)
	{
		std::vector<Hydrax::Module::Module*>::iterator It;

		for (It = mModules.begin(); It != mModules.end(); It++)
		{
			if ((*It)->getName() == Name)
			{
				return (*It);
			}
		}

		return static_cast<Hydrax::Module::Module*>(NULL);
	}

	void HydraxManager::_removeGeometryModule(Hydrax::Module::Module* m)
	{
		std::vector<Hydrax::Module::Module*>::iterator It;

		for (It = mModules.begin(); It != mModules.end(); It++)
		{
			if ((*It) == m)
			{
				delete (*It);
				mModules.erase(It);

				return;
			}
		}
	}

	void HydraxManager::_removeGeometryModules()
	{
		std::vector<Hydrax::Module::Module*>::iterator It;

		for (It = mModules.begin(); It != mModules.end(); It++)
		{
			delete (*It);
			mModules.erase(It);
		}
	}

	void HydraxManager::_addNoiseModule(Hydrax::Noise::Noise* n)
	{
		mNoises.push_back(n);
	}

	Hydrax::Noise::Noise* HydraxManager::getNoiseModule(const Ogre::String& Name)
	{
		std::vector<Hydrax::Noise::Noise*>::iterator It;

		for (It = mNoises.begin(); It != mNoises.end(); It++)
		{
			if ((*It)->getName() == Name)
			{
				return (*It);
			}
		}

		return static_cast<Hydrax::Noise::Noise*>(NULL);
	}

	void HydraxManager::_removeNoiseModule(Hydrax::Noise::Noise* n)
	{
		std::vector<Hydrax::Noise::Noise*>::iterator It;

		for (It = mNoises.begin(); It != mNoises.end(); It++)
		{
			if ((*It) == n)
			{
				delete (*It);
				mNoises.erase(It);

				return;
			}
		}
	}

	void HydraxManager::_removeNoiseModules()
	{
		std::vector<Hydrax::Noise::Noise*>::iterator It;

		for (It = mNoises.begin(); It != mNoises.end(); It++)
		{
			delete (*It);
			mNoises.erase(It);
		}
	}

	void HydraxManager::_setSkyBox()
	{
		// Change skybox
        mSceneMgr->setSkyBox(true, mSkyBoxes[mCurrentSkyBox], 99999* 3, true);

        // Update Hydrax sun position and colour
        mHydrax->setSunPosition(mSunPosition[mCurrentSkyBox]);
        mHydrax->setSunColor(mSunColor[mCurrentSkyBox]);

        // Update light 0 light position and colour
        mSceneMgr->getLight("Light0")->setPosition(mSunPosition[mCurrentSkyBox]);
        mSceneMgr->getLight("Light0")->setSpecularColour(mSunColor[mCurrentSkyBox].x,mSunColor[mCurrentSkyBox].y,mSunColor[mCurrentSkyBox].z);

        LOG("Skybox " + mSkyBoxes[mCurrentSkyBox] + " selected. ("+Ogre::StringConverter::toString(mCurrentSkyBox+1)+"/"+Ogre::StringConverter::toString(4)+")");
	}
}