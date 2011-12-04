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

#ifndef _HydraxManager_H_
#define _HydraxManager_H_

#include "Prerequisites.h"

namespace HydraxEditor
{
	class HydraxManager 
	{
	public:
        /** Constructor
		    @param sm Our Ogre::SceneManager pointer 
			@param c Our Ogre::Camera pointer
			@param v Our Ogre::Viewport pointer
		 */
		HydraxManager(Ogre::SceneManager* sm, Ogre::Camera *c, Ogre::Viewport *v);

		/** Destructor
		 */
		~HydraxManager();

		/** Create Hydrax
		 */
		void create();

		/** Get Hydrax pointer
		    @return Hydrax pointer
		 */
		inline Hydrax::Hydrax* getHydrax()
		{
			return mHydrax;
		}

		/** Get geometry module 
		    @Name Geometry module name
			@return Geometry module, NULL if the given name isn't in the list
	     */
		Hydrax::Module::Module* getGeometryModule(const Ogre::String& Name);

		/** Get noise module 
		    @Name Noise module name
			@return Noise module, NULL if the given name isn't in the list
	     */
		Hydrax::Noise::Noise* getNoiseModule(const Ogre::String& Name);

		/** Load config file
		    @param PathName Path + \ + FileName
		 */
		bool loadCfgFile(const Ogre::String& PathName);

		/** Save config file
		    @param PathName Path + \ + FileName
		 */
		bool saveCfgFile(const Ogre::String& PathName);

		/** Set SkyBox
		    @param SkyBox Our SkyBox's number
			@remarks SkyBox will be in [0,3] range
		 */
		inline void setSkyBox(const int &SkyBox)
		{
			if (SkyBox >= 0 && SkyBox <= 4)
			{
			    mCurrentSkyBox = SkyBox;
				_setSkyBox();
			}
		}

		/** Set SkyBox
		    @param SkyBox Skybox's name
		 */
		inline void setSkybox(const Ogre::String &SkyBox)
		{
			int Index = -1;

			for(int k = 0; k < 5; k++)
			{
				if (mSkyBoxes[k] == SkyBox)
				{
					Index = k;
					setSkyBox(Index);

					return;
				}
			}
		}

		/** Get the current SkyBox's name
		    @return Current SkyBox's name
		 */
		inline const Ogre::String& getCurrentSkyBox() const
		{
			return mSkyBoxes[mCurrentSkyBox];
		}
		
		/** Set palmiers visible or not visible
		    @param Visible true for visible, false for nor visible
		 */
		inline void setPalmsVisible(const bool& Visible)
		{
			mPalmsSceneNode->setVisible(Visible);
		}

		/** Get the name of the last saved config file
		    @return Last config file saved name(no path)
		 */
		inline Ogre::String getLastWaterFilenameSaved()
		{
			return mLastWaterFilenameSaved;
		}

		/** Get the name of the last loaded config file
		    @return Last config file loaded name(no path)
		 */
		inline Ogre::String getLastWaterFilenameLoaded()
		{
			return mLastWaterFilenameLoaded;
		}
		
	private:
		/// Our Hydrax pointer
		Hydrax::Hydrax* mHydrax;

		/// Our Hydrax geometry modules vector
		std::vector<Hydrax::Module::Module*> mModules;
		/// Our Hydrax noise modules vector
		std::vector<Hydrax::Noise::Noise*> mNoises;
	
		/// SkyBoxes names vector
		Ogre::String mSkyBoxes[5];
		/// SkyBoxes's sun positions
		Ogre::Vector3 mSunPosition[5];
		/// SkyBoxes's color positions
		Ogre::Vector3 mSunColor[5];
		/// Current SkyBox
		int mCurrentSkyBox;

		/// Palms scene node
		Ogre::SceneNode* mPalmsSceneNode;

		/// Our Ogre::SceneManager
		Ogre::SceneManager* mSceneMgr;
		/// Our camera
		Ogre::Camera* mCamera;
		/// Our viewport
		Ogre::Viewport *mViewport;

		/// Last water config filename(no path) saved name
		Ogre::String mLastWaterFilenameSaved;
		/// Last water config filename(no path) loaded name
		Ogre::String mLastWaterFilenameLoaded;

		/** Create palmiers
		 */
		void _createPalms();

		/** Add geometry module to the manager
		    @m Hydrax::Module::Module*
	     */
		void _addGeometryModule(Hydrax::Module::Module* m);

		/** Remove geometry module from manager
	    	@m Hydrax::Module::Module*
		 */
		void _removeGeometryModule(Hydrax::Module::Module* m);

		/** Remove all geometry modules
		 */
		void _removeGeometryModules();

		/** Add noise module to the manager
		    @n Hydrax::Noise::Noise*
	     */
		void _addNoiseModule(Hydrax::Noise::Noise* n);

		/** Remove noise module from manager
	    	@n Hydrax::Noise::Noise*
		 */
		void _removeNoiseModule(Hydrax::Noise::Noise* n);

		/** Remove all noise modules
		 */
		void _removeNoiseModules();

		/** Private funtion to update SkyBox
		 */
		void _setSkyBox();
	};

};

#endif