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

#ifndef _RBGuiManager_H_
#define _RBGuiManager_H_

#include "Prerequisites.h"

#include "RBGuiWindows/RBGuiWindowBase.h"
#include "RBGuiWindows/TopMenu.h"
#include "RBGuiWindows/WOptionsWindow.h"
#include "RBGuiWindows/WParametersWindow.h"
#include "RBGuiWindows/EnvironementWindow.h"
#include "RBGuiWindows/DebugWindow.h"

namespace HydraxEditor
{
	class RBGuiManager
	{
	public:
		/** EditorCursorManager class
		 */
		class EditorCursorManager : public RBGui::Win32CursorManager
		{
		public:
			/** Constructor
			 */
			EditorCursorManager() : Win32CursorManager(){};

			/** Destructor
			 */
			~EditorCursorManager(){};

			/** Events
			 */ 
		    void onMouseMoved(const Mocha::Vector2& vPosition);
			void onMousePressed(RBGui::MouseButtonID vButton);
			void onMouseReleased(RBGui::MouseButtonID vButton);
		};

		/** Constructor
		    @param v Ogre::Viewport pointer
			@param sm Ogre::SceneManager pointer
		 */
		RBGuiManager(Ogre::Viewport* v, Ogre::SceneManager* sm);
		
		/** Destructor
		 */
		~RBGuiManager();

		/** Setup RBGui
		    @return false if RBGui setup fails
		 */
		bool setup();

		/** Add a window
		    @param Window RBGuiWindowBase base class pointer
			@param Name Window's name
		    @remarks Add a HydraxEditor::RBGuiWindowBase, not a RBGui::Window
		 */
		void addWindow(RBGuiWindowBase* Window, const Ogre::String &Name);

		/** Get a especified RBGuiWindowBase
		    @param Window Window name
		    @return HydraxEditor::RBGuiWindowBase pointer
		 */
		RBGuiWindowBase* getWindow(const Ogre::String &Window);

		/** Delete a window
		    @param Window RBGuiWindowBase base class pointer
		    @remarks Delete a HydraxEditor::RBGuiWindowBase, not a RBGui::Window
		 */
		void deleteWindow(RBGuiWindowBase* Window);

		/** Delete a window
		    @param Name Window's name
		    @remarks Delete a HydraxEditor::RBGuiWindowBase, not a RBGui::Window
		 */
		void deleteWindow(const Ogre::String &Name);

		/** Delete all windows
		 */
		void deleteWindows();

		/** Create all windows
		 */
		void createWindows();

		/** Set default RBGui theme
		    @param Theme Theme's name
		 */
		bool setDefaultTheme(const Mocha::String &Theme);

		/** Get gui core 
		    @return RBGui::Core mocha pointer
		 */
		inline Mocha::RefPointer<RBGui::Core> getGuiCore()
		{
			return mGuiCore;
		}

		/** Get gui manager 
		    @return RBGui::GuiManager mocha pointer
		 */
		inline Mocha::RefPointer<RBGui::GuiManager> getGuiManager()
		{
			return mGuiManager;
		}

		/** Get cursor manager
		    @return EditorCursorManager mocha pointer
		 */
		inline Mocha::RefPointer<EditorCursorManager> getCursorManager()
		{
			return mEditorCursorManager;
		}

	private:
		/// RBGui::Core mocha pointer
		Mocha::RefPointer<RBGui::Core> mGuiCore;
		/// RBGui::GuiManager mocha pointer
	    Mocha::RefPointer<RBGui::GuiManager> mGuiManager;
		/// EditorCursorManager pointer
		Mocha::RefPointer<EditorCursorManager> mEditorCursorManager;

		/// std::vector of all RBGuiWindowBase windows
		std::vector<RBGuiWindowBase*> mWindows;

		/// Was setup() called?
		bool isSetup;

		/// Ogre::Viewport pointer
		Ogre::Viewport* mViewport;
		/// Ogre::SceneManager pointer
		Ogre::SceneManager* mSceneMgr;
	};
};

#endif