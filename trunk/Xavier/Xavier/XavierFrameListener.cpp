#include "StdAfx.h"
#include "XavierFrameListener.h"
#include "OgreDebugDrawer.h"
#include "OgreKernel.h"

namespace Ogre
{
	XavierFrameListener::XavierFrameListener(void)
	{

	}

	XavierFrameListener::~XavierFrameListener(void)
	{
	}

	bool	XavierFrameListener::frameStarted(const FrameEvent& evt)
	{
		//DebugDrawer::getSingleton().drawCircle(Vector3(0,0,0), 10, 10, ColourValue(1,0,0,1));
		//
		for (int i = 0; i < 5; ++i)
		{
			for (int j = 0; j < 5; j++)
			{
				for (int k = 0; k < 5; k++)
				{
					Ogre::AxisAlignedBox box (Ogre::Vector3(i * 10.0f + 2.0f, j * 10.0f + 2.0f, k * 10.0f + 2.0f),
						Ogre::Vector3((i + 1) * 10.0f - 2.0f, (j + 1) * 10.0f - 2.0f, (k + 1) * 10.0f - 2.0f));
					DebugDrawer::getSingleton().drawCuboid(box.getAllCorners(),
						Ogre::ColourValue(51.0f * i / 255.0f, 51.0f * j / 255.0f, 51.0f * k / 255.0f), true);
				}
			}
		}

		DebugDrawer::getSingleton().build();
		return true;
	}

	bool	XavierFrameListener::frameRenderingQueued(const FrameEvent& evt)
	{
		return true;
	}

	bool	XavierFrameListener::frameEnded(const FrameEvent& evt)
	{
		DebugDrawer::getSingleton().clear();
		return true;
	}
}
