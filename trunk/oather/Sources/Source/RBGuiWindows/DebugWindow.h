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

#ifndef _DebugWindow_H_
#define _DebugWindow_H_

#include "../Prerequisites.h"
#include "RBGuiWindowBase.h"

namespace HydraxEditor
{
    /** RBGui debug window class
	 */
	class DebugWindow : public RBGuiWindowBase
	{
	public:
		/** Constructor
		    @param rbguiman RBGuiManager pointer
			@param rw Ogre::RenderWindow pointer (just used for get the size)
		 */
		DebugWindow(Mocha::RefPointer<RBGui::GuiManager> gm, Ogre::RenderWindow* rw);

		/** Destructor
		 */
		~DebugWindow();

		/** Create
		 */
		void create();

		/** We need to update it each frame for update our dynamic
		    textures
		 */
		void update();

	private:
		/// Ogre::RenderWindow pointer (just use for get the size)
		Ogre::RenderWindow* mRenderWindow;

		/// RBGui image widget for normal map pointer
		RBGui::ImageWidget* mImageWidget_Normal;
		/// RBGui image widget for reflection map pointer
		RBGui::ImageWidget* mImageWidget_Reflection;
		/// RBGui image widget for refraction map pointer
		RBGui::ImageWidget* mImageWidget_Refraction;
		/// RBGui image widget for depth map pointer
		RBGui::ImageWidget* mImageWidget_Depth;
		/// RBGui image widget for depth reflection map pointer
		RBGui::ImageWidget* mImageWidget_Depth_Reflection;

		/** Resize callback
		    @param vElement RBGui::GuiElement&
			@param vData Mocha::ValueList&
		 */
		void resizedCallback(RBGui::GuiElement& vElement, const Mocha::ValueList& vData);

		/** Closed callback
		    @param vElement RBGui::GuiElement&
			@param vData Mocha::ValueList&
		 */
		void closedCallback(RBGui::GuiElement& vElement, const Mocha::ValueList& vData);
	};
};

#endif