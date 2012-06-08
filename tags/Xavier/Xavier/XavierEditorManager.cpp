#include "StdAfx.h"
#include "XavierEditorManager.h"
#include "tinyxml.h"
#include "OgreSSSDK.h"

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
		TiXmlDocument* pDocument = new TiXmlDocument();

		try{	
			if (!pDocument->LoadFile(name.c_str()))
				OGRE_EXCEPT(Exception::ERR_FILE_NOT_FOUND, "can not found file " + name, "XavierEditorManager::load");

			// 获取根元素
			TiXmlElement* root = pDocument->RootElement();
			ASSERT(root != NULL);
			
			// 第一个节点
			TiXmlElement* node = root->FirstChildElement(
				XML_EDITOR_NAME
				);
			while( node != NULL)
			{
				// 取得类型
				String type = node->Attribute(XML_TYPE_NAME);
				if (!type.empty())
				{
					
				}

				node = root->NextSiblingElement(XML_EDITOR_NAME);
			}

		}catch(Ogre::Exception& e)
		{
			TKLogEvent(e.getFullDescription(), LML_TRIVIAL);

			// 销毁
			SAFE_DELETE(pDocument);
		}
		
		// 销毁文档
		if (pDocument != NULL)
			delete pDocument;
				
		return 0;
	}

	/**
	 *
	 */
	void		XavierEditorManager::unload()
	{

	}
}
