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

#ifndef _EditorPrerequisites_H_
#define _EditorPrerequisites_H_

// Editor defines
#define HYDRAX_EDITOR_VERSION 0.5

// Ogre headers
#include <Ogre.h>

#if OGRE_PLATFORM == OGRE_PLATFORM_APPLE
#include <CoreFoundation/CoreFoundation.h>
#endif

// Hydrax headers
#include "Hydrax/Hydrax.h"
#include "Hydrax/Noise/Perlin/Perlin.h"
#include "Hydrax/Noise/FFT/FFT.h"
#include "Hydrax/Modules/ProjectedGrid/ProjectedGrid.h"
#include "Hydrax/Modules/SimpleGrid/SimpleGrid.h"
#include "Hydrax/Modules/RadialGrid/RadialGrid.h"

// OIS headers.
// Use this define to signify OIS will be used as a DLL
// (so that dll import/export macros are in effect)
#define OIS_DYNAMIC_LIB
#include <OIS/OIS.h>

// Mocha headers
#include "Mocha/DataSection.h"
#include "Mocha/Stream.h"
#include "Mocha/Timer.h"

// RBGui headers
#if defined(WIN32)
#include "RBGui/Win32PlatformManager.h"
#include "RBGui/Win32CursorManager.h"
#elif defined(POSIX)
#include "RBGui/PosixPlatformManager.h"
#elif defined(MACOS)
#include "RBGui/MacOSPlatformManager.h"
#else
#error "No platform manager available"
#endif

#include "RBGui/BrushCursorManager.h"

#include "RBGui/Core.h"

#include "RBGui/Exception.h"
#include "RBGui/WobbleWindowAnimator.h"
#include "RBGui/SimpleWindowFader.h"

#include "RBGui/OgreSupport/OgreTextureManager.h"
#include "RBGui/OgreSupport/OgreRenderQueueListener.h"
#include "RBGui/OgreSupport/OgreResourceManager.h"
#include "RBGui/OgreSupport/OgreBrush.h"

#include "RBGui/Widgets/AttributeEditWidget.h"
#include "RBGui/Widgets/AttributeWidget.h"
#include "RBGui/Widgets/ButtonWidget.h"
#include "RBGui/Widgets/ColorRangeWidget.h"
#include "RBGui/Widgets/ColorSelectWidget.h"
#include "RBGui/Widgets/ContainerWidget.h"
#include "RBGui/Widgets/CheckWidget.h"
#include "RBGui/Widgets/DirectoryListWidget.h"
#include "RBGui/Widgets/DropListWidget.h"
#include "RBGui/Widgets/DropSplineWidget.h"
#include "RBGui/Widgets/EvaluatorWidget.h"
#include "RBGui/Widgets/GroupWidget.h"
#include "RBGui/Widgets/HSVWidget.h"
#include "RBGui/Widgets/ImageWidget.h"
#include "RBGui/Widgets/ListWidget.h"
#include "RBGui/Widgets/MenuEntry.h"
#include "RBGui/Widgets/MenuEntryWidget.h"
#include "RBGui/Widgets/MenuWidget.h"
#include "RBGui/Widgets/OptionWidget.h"
#include "RBGui/Widgets/ProgressWidget.h"
#include "RBGui/Widgets/RectangleWidget.h"
#include "RBGui/Widgets/ScrollWidget.h"
#include "RBGui/Widgets/SplineWidget.h"
#include "RBGui/Widgets/TextEntryWidget.h"
#include "RBGui/Widgets/TextWidget.h"

#include "RBGui/Widgets/AttributeWidgets/BoolAttributeWidget.h"
#include "RBGui/Widgets/AttributeWidgets/ButtonAttributeWidget.h"
#include "RBGui/Widgets/AttributeWidgets/ColorAttributeWidget.h"
#include "RBGui/Widgets/AttributeWidgets/EvaluatorAttributeWidget.h"
#include "RBGui/Widgets/AttributeWidgets/FileAttributeWidget.h"
#include "RBGui/Widgets/AttributeWidgets/IntAttributeWidget.h"
#include "RBGui/Widgets/AttributeWidgets/ListAttributeWidget.h"
#include "RBGui/Widgets/AttributeWidgets/SliderAttributeWidget.h"
#include "RBGui/Widgets/AttributeWidgets/SplineAttributeWidget.h"
#include "RBGui/Widgets/AttributeWidgets/TextAttributeWidget.h"
#include "RBGui/Widgets/AttributeWidgets/Vector2AttributeWidget.h"
#include "RBGui/Widgets/AttributeWidgets/Vector3AttributeWidget.h"

// Log macro
#define LOG(msg) Ogre::LogManager::getSingleton().logMessage(msg);

#endif