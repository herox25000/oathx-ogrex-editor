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

#ifndef _RBGuiWindowBase_H_
#define _RBGuiWindowBase_H_

#include "../Prerequisites.h"

namespace HydraxEditor
{
    /** RBGuiWindowBase class
	 */
	class RBGuiWindowBase
	{
	public:
		/** Constructor
		    @param gm RBGui::GuiManager mocha pointer
		 */
		RBGuiWindowBase(Mocha::RefPointer<RBGui::GuiManager> gm);

		/** Destructor
		 */
		virtual ~RBGuiWindowBase();

		/** Create windows and set callbacks
		    Needs to override it
		 */
		virtual void create();

		/** Set window name
		    @param Name Window name
		 */
		inline void setName(const Ogre::String &Name)
		{
			mName = Name;
		}

		/** Get window name
		    @return Window name
		 */
		inline const Ogre::String& getName() const
		{
			return mName;
		}

		/** Is create() called?
		    @return true if create() has been called, else false
		 */
		inline const bool& isCreated() const
		{
			return mCreated;
		}

		/** Get the RBGui::Window mocha pointer
		    @return RBGui window mocha pointer
		 */
		inline Mocha::RefPointer<RBGui::Window> getWindow()
		{
			return mWindow;
		}

	protected:
		/// Our RBGui::GuiManager mocha pointer
		Mocha::RefPointer<RBGui::GuiManager> mGuiManager;
		/// Our RBGui::Window mocha pointer
		Mocha::RefPointer<RBGui::Window> mWindow;

		/// Window name
		Ogre::String mName;

		// Is created() called?
		bool mCreated;
	};
};

#endif