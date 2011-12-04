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

#include "DebugWindow.h"
#include "../EditorApp.h"

namespace HydraxEditor
{
	DebugWindow::DebugWindow(Mocha::RefPointer<RBGui::GuiManager> gm, Ogre::RenderWindow* rw)
		: RBGuiWindowBase(gm)
		, mRenderWindow(rw)
		, mImageWidget_Normal(0)
		, mImageWidget_Reflection(0)
		, mImageWidget_Refraction(0)
		, mImageWidget_Depth(0)
		, mImageWidget_Depth_Reflection(0)
	{
	}

	DebugWindow::~DebugWindow()
	{
	}

	void DebugWindow::create()
	{
		mWindow = mGuiManager->createWindow();
		mWindow->setBorderVisible(true);
		mWindow->setHideOnClose(true);
		mWindow->setText("Debug");
		mWindow->setSize(Mocha::Vector2(200*2, 200*3));
		mWindow->setPosition(Mocha::Vector2(mRenderWindow->getWidth()-410,30));
		mWindow->setCallback(&DebugWindow::resizedCallback, this, "Resized");
		mWindow->setCallback(&DebugWindow::closedCallback,  this, "Close_Hide");
		// Hide by default
		mWindow->hide();

		mImageWidget_Normal = static_cast<RBGui::ImageWidget*>( mWindow->createWidget( "Image" ) );
		mImageWidget_Normal->setSize(Mocha::Vector2(200,200));
		mImageWidget_Normal->setPosition(Mocha::Vector2(0, 0));
		mImageWidget_Normal->setName("DebugWindow_ImageWidget_Normal");

		mImageWidget_Reflection = static_cast<RBGui::ImageWidget*>( mWindow->createWidget( "Image" ) );
		mImageWidget_Reflection->setSize(Mocha::Vector2(200,200));
		mImageWidget_Reflection->setPosition(Mocha::Vector2(200, 0));
		mImageWidget_Reflection->setName("DebugWindow_ImageWidget_Reflection");

		mImageWidget_Refraction = static_cast<RBGui::ImageWidget*>( mWindow->createWidget( "Image" ) );
		mImageWidget_Refraction->setSize(Mocha::Vector2(200,200));
		mImageWidget_Refraction->setPosition(Mocha::Vector2(0, 200));
		mImageWidget_Refraction->setName("DebugWindow_ImageWidget_Refraction");

		mImageWidget_Depth = static_cast<RBGui::ImageWidget*>( mWindow->createWidget( "Image" ) );
		mImageWidget_Depth->setSize(Mocha::Vector2(200,200));
		mImageWidget_Depth->setPosition(Mocha::Vector2(200, 200));
		mImageWidget_Depth->setName("DebugWindow_ImageWidget_Depth");

		mImageWidget_Depth_Reflection = static_cast<RBGui::ImageWidget*>( mWindow->createWidget( "Image" ) );
		mImageWidget_Depth_Reflection->setSize(Mocha::Vector2(200,200));
		mImageWidget_Depth_Reflection->setPosition(Mocha::Vector2(0, 400));
		mImageWidget_Depth_Reflection->setName("_Hydrax_GodRays_Depth_Map");
	}

	void DebugWindow::update()
	{
		if (mWindow->getVisible())
		{
			mImageWidget_Normal->setImage("HydraxNormalMap");
			mImageWidget_Reflection->setImage("HydraxReflectionMap");
			mImageWidget_Refraction->setImage("HydraxRefractionMap");
			mImageWidget_Depth->setImage("HydraxDepthMap");
			mImageWidget_Depth_Reflection->setImage("HydraxDepthReflectionMap");

			mWindow->setText("Debug - FPS: "+Ogre::StringConverter::toString(mRenderWindow->getLastFPS()));
			mWindow->flagDirty();
		}
	}
	
	void DebugWindow::resizedCallback(RBGui::GuiElement& vElement, const Mocha::ValueList& vData)
	{
		Mocha::Vector2 Size = mWindow->getClientRectangle().getSize(),
		               ImgsSize = Size/Mocha::Vector2(2, 3);

		mImageWidget_Normal->setSize(ImgsSize);
		mImageWidget_Reflection->setSize(ImgsSize);
		mImageWidget_Refraction->setSize(ImgsSize);
		mImageWidget_Depth->setSize(ImgsSize);
		mImageWidget_Depth_Reflection->setSize(ImgsSize);

		mImageWidget_Reflection->setPosition(Mocha::Vector2(ImgsSize.x, 0));
		mImageWidget_Refraction->setPosition(Mocha::Vector2(0, ImgsSize.y));
		mImageWidget_Depth->setPosition(ImgsSize);
		mImageWidget_Depth_Reflection->setPosition(Mocha::Vector2(0, ImgsSize.y*2));
	}

	void DebugWindow::closedCallback(RBGui::GuiElement& vElement, const Mocha::ValueList& vData)
	{
		TopMenu* mTopMenu = static_cast<TopMenu*>(EditorApp::getSingleton()->getRBGuiManager()->getWindow("TopMenu"));

		mTopMenu->setItemSelect("VIEW_DEBUG", false);
		mTopMenu->update();
	}
}