#include "StdAfx.h"
#include "XavierEditorManager.h"

namespace Ogre
{
	template<>	XavierEditorManager*	Singleton<XavierEditorManager>::msSingleton = NULL;
	XavierEditorManager&	XavierEditorManager::getSingleton()
	{
		assert(msSingleton != NULL); return (*msSingleton);
	}

	XavierEditorManager*	XavierEditorManager::getSingletonPtr()
	{
		assert(msSingleton != NULL); return msSingleton;
	}

	/**
	 *
	 * \param void 
	 * \return 
	 */
	XavierEditorManager::XavierEditorManager(void)
	{
	}

	/**
	 *
	 * \param void 
	 * \return 
	 */
	XavierEditorManager::~XavierEditorManager(void)
	{
	}

	/**
	 *
	 * \param name 
	 * \return 
	 */
	bool		XavierEditorManager::load(const String& name)
	{
		return 0;
	}

	/**
	 *
	 */
	void		XavierEditorManager::unload()
	{

	}
}
