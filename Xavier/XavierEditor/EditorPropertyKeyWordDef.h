#pragma once

namespace Ogre
{
	enum {
		NORMAL_ALHPA,
		NORMAL_RGB,
		NORMAL_X,
		NORMAL_Y,
		NORMAL_Z,
		NORMAL_COUNT,
	};

	static const String NormalPropertyName[] = {
		"Alpha",
		"RGB",
		"x",
		"y",
		"z",
	};

	static int convertNormalPropertyType(const String& name)
	{
		for (int i=0; i<NORMAL_COUNT; i++)
		{
			if (NormalPropertyName[i] == name)
				return i;
		}

		return -1;
	}

	static const String		EDITOR_TOOL_WORLD_NAME		= "World";
	static const String		EDITOR_TOOL_TERRAIN_NAME	= "Terrain";
}