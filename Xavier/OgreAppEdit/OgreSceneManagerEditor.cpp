#include "OgreAppEditPrerequisites.h"
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
		:m_pSceneManager(NULL), m_pOgreHead(NULL)
	{
		m_pSceneManager = Ogre::Root::getSingletonPtr()->createSceneManager(typeMask, sName);
		assert( m_pSceneManager != NULL);

		m_pSceneManager->setAmbientLight( Ogre::ColourValue( 0.5f, 0.5f, 0.5f ) );
		
		//showHead();
		setTypeName(EDIT_SCENEMANAGER);
	}

	/** 析构函数
	 *
	 * \param void 
	 * \return 
	 */
	SceneManagerEditor::~SceneManagerEditor(void)
	{
		//hideHead();
		Root::getSingletonPtr()->destroySceneManager(m_pSceneManager);
	}

	/**
	 *
	 * \return 
	 */
	SceneManager*	SceneManagerEditor::getSceneManager() const
	{
		return m_pSceneManager;
	}

	/**
	 *
	 */
	void			SceneManagerEditor::showHead()
	{
		Ogre::Entity *entity = m_pSceneManager->createEntity( "AxisEntity", "ogrehead.mesh", 
			ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME );
		m_pOgreHead			 = m_pSceneManager->getRootSceneNode()->createChildSceneNode();
		m_pOgreHead->attachObject( entity );
		m_pOgreHead->setScale(0.1,0.1,0.1);

		entity->setRenderQueueGroup( Ogre::RENDER_QUEUE_SKIES_LATE );
	}

	/**
	 *
	 */
	void			SceneManagerEditor::hideHead()
	{
		if( m_pOgreHead )
		{
			Ogre::Entity *entity = static_cast<Ogre::Entity*>(m_pOgreHead->getAttachedObject(0));
			m_pOgreHead->getParentSceneNode()->removeAndDestroyChild( m_pOgreHead->getName() );
			m_pSceneManager->destroyEntity( entity );
		}
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
