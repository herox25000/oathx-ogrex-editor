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

			// ��ȡ��Ԫ��
			TiXmlElement* root = pDocument->RootElement();
			ASSERT(root != NULL);
			
			// ��һ���ڵ�
			TiXmlElement* node = root->FirstChildElement(
				XML_EDITOR_NAME
				);
			while( node != NULL)
			{
				// ȡ������
				String type = node->Attribute(XML_TYPE_NAME);
				if (!type.empty())
				{
					
				}

				node = root->NextSiblingElement(XML_EDITOR_NAME);
			}

		}catch(Ogre::Exception& e)
		{
			TKLogEvent(e.getFullDescription(), LML_TRIVIAL);

			// ����
			SAFE_DELETE(pDocument);
		}
		
		// �����ĵ�
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
