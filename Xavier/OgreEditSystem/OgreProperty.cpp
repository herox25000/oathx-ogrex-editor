#include "OgreEditSystemPrerequisites.h"
#include "OgreProperty.h"

namespace Ogre
{
	//////////////////////////////////////////////////////////////////////////
	// class Property
	//////////////////////////////////////////////////////////////////////////
	Property::Property()
	{

	}

	//////////////////////////////////////////////////////////////////////////
	Property::~Property()
	{
		mSSValue.clear();
	}

	//////////////////////////////////////////////////////////////////////////
	float			Property::getValueDouble(const String& sName)
	{
		float val = 0;
		sscanf(mSSValue[sName].c_str(), " %g", &val);

		return val;
	}

	//////////////////////////////////////////////////////////////////////////
	int				Property::getValueIntger(const String& sName)
	{
		int val = 0;
		sscanf(mSSValue[sName].c_str(), " %d", &val);

		return val;
	}

	//////////////////////////////////////////////////////////////////////////
	Vector2			Property::getValueCPoint(const String& sName)
	{
		Vector2 cPt;
		sscanf(mSSValue[sName].c_str(), " %g,%g", &cPt.x, &cPt.y);

		return cPt;
	}

	//////////////////////////////////////////////////////////////////////////
	Size			Property::getValueCCSize(const String& sName)
	{
		Size cSz;
		sscanf(mSSValue[sName].c_str(), " %g,%g", &cSz.width, &cSz.height);

		return cSz;
	}

	//////////////////////////////////////////////////////////////////////////
	String			Property::getValueString(const String& sName)
	{
		return mSSValue[sName];
	}

	//////////////////////////////////////////////////////////////////////////
	void			Property::addProperty(Property* pParent, const String& sName, const String& val)
	{
		if (pParent != NULL)
		{
			pParent->addProperty(NULL, sName, val);
		}
		else
		{
			mSSValue[sName] = val;
		}
	}
}