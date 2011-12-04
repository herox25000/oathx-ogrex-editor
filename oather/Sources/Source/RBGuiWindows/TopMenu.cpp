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

#include "TopMenu.h"
#include "../EditorApp.h"

namespace HydraxEditor
{
	TopMenu::TopMenu(Mocha::RefPointer<RBGui::GuiManager> gm, Ogre::RenderWindow *rw)
		: RBGuiWindowBase(gm)
		, mMenuWidget(0)
		, mRenderWindow(rw)
		, needUpdate(false)
	{
	}

	TopMenu::~TopMenu()
	{
	}

	void TopMenu::create()
	{
		// Call base create() funtion
		RBGuiWindowBase::create();

		mWindow = mGuiManager->createWindow();
		mWindow->setBorderVisible(false);
		mWindow->setSize(Mocha::Vector2(mRenderWindow->getWidth(), 22.0f));
		mWindow->show();

		initMenuWidget();
	}

	void TopMenu::initMenuWidget()
	{
		mMenuItemData.reserve(11);
		mMenuItemData.resize(11);

		// File field
		mMenuItemData[0] = MenuItemData("File","Open File",    "FILE_OPEN",      false);
		mMenuItemData[1] = MenuItemData("File","-",            "",               false);
		mMenuItemData[2] = MenuItemData("File","Save File",    "FILE_SAVE",      false);
		mMenuItemData[3] = MenuItemData("File","-",            "",               false);
		mMenuItemData[4] = MenuItemData("File","Quit",         "FILE_QUIT",      false);

		// View field
		mMenuItemData[5] = MenuItemData("View","Water options",    "VIEW_OPTIONS",     true);
		mMenuItemData[6] = MenuItemData("View","Water parameters", "VIEW_PARAMETERS",  true);
		mMenuItemData[7] = MenuItemData("View","Environement",     "VIEW_ENVIRONEMENT",true);
		mMenuItemData[8] = MenuItemData("View","-",                "",                 false);
		mMenuItemData[9]= MenuItemData("View","Debug",            "VIEW_DEBUG",       false);

		// About field
		mMenuItemData[10] = MenuItemData("Help","About", "HELP_ABOUT",  false);

		// Create our menu widget
		mMenuWidget = static_cast<RBGui::MenuWidget*>(mWindow->createWidget("Menu"));

		mMenuWidget->setName("TopMenu");
		mMenuWidget->setSize(mWindow->getSize());
		mMenuWidget->setCallback(&TopMenu::callback, this);

		setItems();
	}

	void TopMenu::setItems()
	{
		mMenuWidget->clear();
		
		Ogre::String addToName;

		for (unsigned int k = 0; k < mMenuItemData.size(); k++)
		{
			 addToName = "";

			 if (mMenuItemData[k].Select)
			 {
			 	 addToName = "- ";
			 }

			 mMenuWidget->addEntry(// Name
			 	                   mMenuItemData[k].Entry + "." + addToName + mMenuItemData[k].Item, 
								   // ID
								   mMenuItemData[k].ID);
		}
	}

	void TopMenu::setItemSelect(const Ogre::String &ID, const bool &Select)
	{
        needUpdate = true;

		for (unsigned int k = 0; k < mMenuItemData.size(); k++)
		{
			if(mMenuItemData[k].ID == ID)
			{
				mMenuItemData[k].Select = Select;
		        return;
			}
		}
	}

	bool TopMenu::isItemSelect(const Ogre::String &ID) const
	{
		for (unsigned int k = 0; k < mMenuItemData.size(); k++)
		{
			if(mMenuItemData[k].ID == ID)
			{
				return mMenuItemData[k].Select;
			}
		}

		return false;
	}

	void TopMenu::update()
	{
		if(needUpdate)
		{
			setItems();

			needUpdate = false;
		}
	}

	void TopMenu::callback(RBGui::GuiElement& vElement, const Mocha::ValueList& vData)
	{
		// Get the ID of the menu that was picked
	    const Mocha::String& Id = vData[0].getAsString();

		// File field
		if(Id == "FILE_OPEN")
		{
			EditorApp::getSingleton()->getRBGuiManager()->getGuiManager()->createFileSelectWindow("Select hydrax config file (*.hdx)", "saved", "hdx", new RBGui::MemberGuiCallback<TopMenu>(&TopMenu::fileSelectedCallback, this), RBGui::FILESELECTWINDOW_OPEN)->show();
		}
		else if(Id == "FILE_SAVE")
		{
			EditorApp::getSingleton()->getRBGuiManager()->getGuiManager()->createFileSelectWindow("Save hydrax config file (*.hdx)", "saved", "hdx", new RBGui::MemberGuiCallback<TopMenu>(&TopMenu::saveSelectedCallback, this), RBGui::FILESELECTWINDOW_SAVE)->show();
		}
		else if(Id == "FILE_QUIT")
		{
			HydraxEditor::EditorApp::getSingleton()->end();
		}
		// View field
		else if(Id == "VIEW_OPTIONS")
		{
			if(isItemSelect(Id))
			{
			    EditorApp::getSingleton()->getRBGuiManager()->getWindow("WOptionsWindow")->getWindow()->hide();
			}
			else
			{
				EditorApp::getSingleton()->getRBGuiManager()->getWindow("WOptionsWindow")->getWindow()->show();
			}

			setItemSelect(Id, !isItemSelect(Id));
		}
		else if(Id == "VIEW_PARAMETERS")
		{
			if(isItemSelect(Id))
			{
			    EditorApp::getSingleton()->getRBGuiManager()->getWindow("WParametersWindow")->getWindow()->hide();
			}
			else
			{
				EditorApp::getSingleton()->getRBGuiManager()->getWindow("WParametersWindow")->getWindow()->show();
			}

		    setItemSelect(Id, !isItemSelect(Id));
		}
		else if(Id == "VIEW_ENVIRONEMENT")
		{
			if(isItemSelect(Id))
			{
			    EditorApp::getSingleton()->getRBGuiManager()->getWindow("EnvironementWindow")->getWindow()->hide();
			}
			else
			{
				EditorApp::getSingleton()->getRBGuiManager()->getWindow("EnvironementWindow")->getWindow()->show();
			}

		    setItemSelect(Id, !isItemSelect(Id));
		}
		else if(Id == "VIEW_DEBUG")
		{
			if(isItemSelect(Id))
			{
			    EditorApp::getSingleton()->getRBGuiManager()->getWindow("DebugWindow")->getWindow()->hide();
			}
			else
			{
				EditorApp::getSingleton()->getRBGuiManager()->getWindow("DebugWindow")->getWindow()->show();
			}

			setItemSelect(Id, !isItemSelect(Id));
		}
		// Help field
		else if (Id == "HELP_ABOUT")
		{
			mGuiManager->createMessageBox("About", "Hydrax editor v"+Ogre::StringConverter::toString(static_cast<float>(HYDRAX_EDITOR_VERSION))+
				                          "\nXavier Verguin Gonzalez"+
										  "\nUsing RBGui 0.1.3" )->show();
		}
	}

	void TopMenu::fileSelectedCallback(RBGui::GuiElement& vElement, const Mocha::ValueList& vData)
	{
		// Get the file path + name
	    const Mocha::String& Id = vData[0].getAsString();

		EditorApp::getSingleton()->getHydraxManager()->loadCfgFile(Id);

		// Update gui settings
		static_cast<WOptionsWindow*>(EditorApp::getSingleton()->getRBGuiManager()->getWindow("WOptionsWindow"))->addAttributes();
		static_cast<WParametersWindow*>(EditorApp::getSingleton()->getRBGuiManager()->getWindow("WParametersWindow"))->updateAttributes();

		if (Ogre::ResourceGroupManager::getSingleton().resourceExists("General", EditorApp::getSingleton()->getHydraxManager()->getLastWaterFilenameLoaded()+"_"))
		{
		    EditorApp::getSingleton()->getRBGuiManager()->getGuiManager()->createQuestionWindow("Load environment settings?", "This hydrax config file has an asociated Hydrax editor environment\nLoad environment settings?\n(Skybox and camera settings)","No,Yes", new RBGui::MemberGuiCallback<TopMenu>(&TopMenu::loadEnvironmentQuestionWindow, this))->show();
		}
	}

    void TopMenu::loadEnvironmentQuestionWindow(RBGui::GuiElement& vElement, const Mocha::ValueList& vData)
	{
		// Get the file path + name
	    const Mocha::String& Id = vData[0].getAsString();

		if (Id == "Yes")
		{
			Ogre::ConfigFile CfgFile;
			CfgFile.load(EditorApp::getSingleton()->getHydraxManager()->getLastWaterFilenameLoaded()+"_", "General", "\x09:=", true);

			EditorApp::getSingleton()->getHydraxManager()->setSkybox(CfgFile.getSetting("SkyBox"));
			EditorApp::getSingleton()->getCamera()->setPosition(Ogre::StringConverter::parseVector3(CfgFile.getSetting("CameraPosition")));
			EditorApp::getSingleton()->getCamera()->setOrientation(Ogre::StringConverter::parseQuaternion(CfgFile.getSetting("CameraOrientation")));
		}
	}

	void TopMenu::saveSelectedCallback(RBGui::GuiElement& vElement, const Mocha::ValueList& vData)
	{
		// Get the file path + name
	    const Mocha::String& Id = vData[0].getAsString();

		EditorApp::getSingleton()->getHydraxManager()->saveCfgFile(Id);

		EditorApp::getSingleton()->getRBGuiManager()->getGuiManager()->createQuestionWindow("Save environment settings?", "Do you want to save current environment settings?\n(Selected skybox and camera settings)","No,Yes", new RBGui::MemberGuiCallback<TopMenu>(&TopMenu::saveEnvironmentQuestionWindow, this))->show();
	}

	void TopMenu::saveEnvironmentQuestionWindow(RBGui::GuiElement& vElement, const Mocha::ValueList& vData)
	{
		// Get the pressed button name
	    const Mocha::String& Id = vData[0].getAsString();

		if (Id == "Yes")
		{
		    Ogre::String EnvironmentData = Ogre::String(
			   "SkyBox=") + EditorApp::getSingleton()->getHydraxManager()->getCurrentSkyBox() + "\n" +
			   "CameraPosition=" + Ogre::StringConverter::toString(EditorApp::getSingleton()->getCamera()->getDerivedPosition()) + "\n" +
			   "CameraOrientation=" + Ogre::StringConverter::toString(EditorApp::getSingleton()->getCamera()->getDerivedOrientation()) + "\n";

			FILE *DestinationFile = fopen(("savedEnv/"+EditorApp::getSingleton()->getHydraxManager()->getLastWaterFilenameSaved()+"_").c_str(), "w");

			if (!DestinationFile)
			{
				return;
			}

			fprintf(DestinationFile, "%s", EnvironmentData.c_str());
			fclose(DestinationFile);

			try
			{
				Ogre::ResourceGroupManager::getSingleton().removeResourceLocation("savedEnv/", "General");
			}
			catch(...)
			{
			}

			Ogre::ResourceGroupManager::getSingleton().addResourceLocation("savedEnv/", "FileSystem", "General");
		}
	}
}
