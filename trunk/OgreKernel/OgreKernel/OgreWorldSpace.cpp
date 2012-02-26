#include "OgreWorldSpace.h"
#include "Ogre.h"

namespace Ogre
{
	template<> WorldSpace*	Singleton<WorldSpace>::msSingleton = NULL;
	WorldSpace&		WorldSpace::getSingleton()
	{
		assert(msSingleton != NULL);  return (*msSingleton);
	}

	//////////////////////////////////////////////////////////////////////////
	WorldSpace*		WorldSpace::getSingletonPtr()
	{
		return msSingleton;
	}

	//////////////////////////////////////////////////////////////////////////
	//
	//////////////////////////////////////////////////////////////////////////
	WorldSpace::WorldSpace(void)
		:m_pRoot(NULL)
	{
	}
	
	//////////////////////////////////////////////////////////////////////////
	WorldSpace::~WorldSpace(void)
	{

	}
	
	//////////////////////////////////////////////////////////////////////////
	bool			WorldSpace::createWorldSpace(const String& sPluginPath, const String& sResourceConfigFilePath, bool bAutoCreateWindow, const String& sTitle)
	{
		m_pRoot = new Root(sPluginPath);
		assert(m_pRoot != NULL);

		Ogre::ConfigFile cf;
		cf.load(sResourceConfigFilePath);

		Ogre::ConfigFile::SectionIterator seci = cf.getSectionIterator();

		Ogre::String secName, typeName, archName;
		while (seci.hasMoreElements())
		{
			secName = seci.peekNextKey();
			Ogre::ConfigFile::SettingsMultiMap *settings = seci.getNext();
			Ogre::ConfigFile::SettingsMultiMap::iterator i;

			for (i = settings->begin(); i != settings->end(); ++i)
			{
				typeName = i->first;
				archName = i->second;
				Ogre::ResourceGroupManager::getSingleton().addResourceLocation(
					archName, typeName, secName);
			}
		}

		/*
		 *	创建渲染系统
		 */
		Ogre::RenderSystemList::const_iterator pRend = m_pRoot->getAvailableRenderers().begin();
		while(pRend != m_pRoot->getAvailableRenderers().end())
		{
			Ogre::String rName = (*pRend)->getName();
			if (rName == "OpenGL Rendering Subsystem")
				break;

			pRend++;
		}
		Ogre::RenderSystem *rsys = *pRend;

		rsys->setConfigOption( "Colour Depth", "32" );
		rsys->setConfigOption( "Full Screen", "No" );
		rsys->setConfigOption( "VSync", "No" );
		rsys->setConfigOption( "Video Mode", "800 x 600" );
		rsys->setConfigOption( "Display Frequency", "60" );
		
		m_pRoot->setRenderSystem( rsys );

		m_pRoot->initialise(bAutoCreateWindow, sTitle);

		return true;
	}
	
	//////////////////////////////////////////////////////////////////////////
	void			WorldSpace::destroyWorldSpace()
	{
		if (m_pRoot != NULL)
			delete m_pRoot;

		m_pRoot = NULL;
	}
}

