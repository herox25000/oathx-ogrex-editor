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

#ifndef _TopMenu_H_
#define _TopMenu_H_

#include "../Prerequisites.h"
#include "RBGuiWindowBase.h"

namespace HydraxEditor
{
    /** RBGui top menu class
	 */
	class TopMenu : public RBGuiWindowBase
	{
	public:
		/** Constructor
		    @param rbguiman RBGuiManager pointer
			@param rw Ogre::RenderWindow pointer (just used for get the size)
		 */
		TopMenu(Mocha::RefPointer<RBGui::GuiManager> gm, Ogre::RenderWindow* rw);

		/** Destructor
		 */
		~TopMenu();

		/** Create windows and set callbacks
		 */
		void create();

		/** We need to update it each frame because we can't
		    delete a menu entry/item in its own callback.
			@remarks It'll be called onMouseReleased()
		 */
		void update();

		/** Set select value to an Item
		    @param ID Item's id
			@param Active Select/Not select
		 */
		void setItemSelect(const Ogre::String &ID, const bool &Select);

	private:
        /** Struct for store Menu Items's data
		 */
		struct MenuItemData
		{
			/// Entry's name
			Ogre::String Entry;
            /// Item's name
			Ogre::String Item;
			/// Entry/Items's ID
			Ogre::String ID;
			/// Is select? (Ask Xavyiy about this)
			bool Select;

			/** Default constructor
			 */
			MenuItemData()
				: Entry("")
				, Item("")
				, ID("")
                , Select(false)
			{
			}

			/** Constructor
			    @param Entry_ Menu entry's name
				@param Item_ Item's name
				@param ID_ Entry/Item's ID
				@param Select_ is select? (Ask Xavyiy about this)
			 */
			MenuItemData(const Ogre::String &Entry_,
				         const Ogre::String &Item_,
				         const Ogre::String &ID_,
				         const bool &Select_)
				: Entry(Entry_)
				, Item(Item_)
				, ID(ID_)
				, Select(Select_)
			{
			}
		};

		/// Our RBGui::MenuWidget mocha pointer
		Mocha::RefPointer<RBGui::MenuWidget> mMenuWidget;
		/// Ogre::RenderWindow pointer (just use for get the size)
		Ogre::RenderWindow* mRenderWindow;
		/// Vector of MenuItemData
		std::vector<MenuItemData> mMenuItemData;
		/// Need update items?
		bool needUpdate;

		/** Init our MenuWidget
		 */
		void initMenuWidget();

		/** Set items data from mMenuItemData 
		 */
		void setItems();

		/** Is the item select? 
		    @param ID Item's ID
			@return Item's state(Select/Not select)
		 */
		bool isItemSelect(const Ogre::String &ID) const;

		/** MenuWidget callback
		    @param vElement RBGui::GuiElement&
			@param vData Mocha::ValueList&
		 */
		void callback(RBGui::GuiElement& vElement, const Mocha::ValueList& vData);

		/** FileSelectWindow callback
		    @param vElement RBGui::GuiElement&
			@param vData Mocha::ValueList&
		 */
		void fileSelectedCallback(RBGui::GuiElement& vElement, const Mocha::ValueList& vData);

		/** LoadEnvironmentQuestionWindow callback
		    @param vElement RBGui::GuiElement&
			@param vData Mocha::ValueList&
		 */
		void loadEnvironmentQuestionWindow(RBGui::GuiElement& vElement, const Mocha::ValueList& vData);

		/** SaveSelectWindow callback
		    @param vElement RBGui::GuiElement&
			@param vData Mocha::ValueList&
		 */
		void saveSelectedCallback(RBGui::GuiElement& vElement, const Mocha::ValueList& vData);

		/** LoadEnvironmentQuestionWindow callback
		    @param vElement RBGui::GuiElement&
			@param vData Mocha::ValueList&
		 */
		void saveEnvironmentQuestionWindow(RBGui::GuiElement& vElement, const Mocha::ValueList& vData);
	};
};

#endif