#include "StdAfx.h"
#include "XavierDecalCursor.h"
#include "OgreSdk.h"

using namespace Ogre;

static const String		XAVIER_DECAL_CURSOR_MATERIAL_NAME	= "XavierDecalCursor";
static const String		XAVIER_DECAL_CURSOR_TEXTURE			= "";
static const String		XAVIER_DECAL_CURSOR_NAME			= "XavierDecalCursorDecal";

/**
 *
 * \param void 
 * \return 
 */
XavierDecalCursor::XavierDecalCursor(Ogre::WorldSpaceServer* pWorldServer, const Ogre::String& name, const Ogre::Vector2& vSize)
: m_vSize(vSize),m_name(name),m_bVaisible(true)
{
	createDecalCursor(m_vSize);	
}

/**
 *
 * \param void 
 * \return 
 */
XavierDecalCursor::~XavierDecalCursor(void)
{
}

/**
 *
 * \param vSize 
 * \param name 
 */
void	XavierDecalCursor::createDecalCursor(const Ogre::Vector2& vSize)
{
	
}

/**
 *
 * \param vSize 
 */
void	XavierDecalCursor::setDecalSize(const Ogre::Vector2& vSize)
{

}

