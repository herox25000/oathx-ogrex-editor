#include "OgreEditSystemPrerequisites.h"
#include "OgreSceneManagerEditor.h"

namespace Ogre
{
	/** 构造函数
	 *
	 * \param typeMask 
	 * \param sName 
	 * \return 
	 */
	SceneManagerEditor::SceneManagerEditor(SceneTypeMask typeMask, const String& sName)
		:m_pSceneManager(NULL)
	{
		m_pSceneManager = Ogre::Root::getSingletonPtr()->createSceneManager(typeMask, sName);
		assert( m_pSceneManager != NULL);

		setTypeName(EDIT_SCENEMANAGER);
	}

	/** 析构函数
	 *
	 * \param void 
	 * \return 
	 */
	SceneManagerEditor::~SceneManagerEditor(void)
	{
	}

	//////////////////////////////////////////////////////////////////////////
	//
	//////////////////////////////////////////////////////////////////////////
	SceneManagerEditorFactory::SceneManagerEditorFactory()
	{
		setTypeName(FACTORY_SCENEMANAGER);
	}

	/**
	 *
	 * \return 
	 */
	SceneManagerEditorFactory::~SceneManagerEditorFactory()
	{

	}

	/**
	 *
	 * \param pm 
	 * \return 
	 */
	BaseEditor*		SceneManagerEditorFactory::create(const SBaseCreateParam* pm)
	{
		if (pm != NULL)
		{
			/*
			* 转换参数
			*/
			SSceneManagerCreateParam* cm = (SSceneManagerCreateParam*)(pm);
			
			/*
				创建编辑工具
			*/
			BaseEditor* editor = new SceneManagerEditor(cm->typeMask, cm->sName);
	
			return editor;
		}

		return NULL;
	}
}
