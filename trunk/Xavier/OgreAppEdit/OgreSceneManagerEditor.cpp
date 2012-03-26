#include "OgreAppEditPrerequisites.h"
#include "OgreSceneManagerEditor.h"
#include "OgreDebugDrawer.h"

namespace Ogre
{
	/** ���캯��
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
		
		setTypeName(EDIT_SCENEMANAGER);

		new DebugDrawer(m_pSceneManager, 0.5);
	}

	/** ��������
	 *
	 * \param void 
	 * \return 
	 */
	SceneManagerEditor::~SceneManagerEditor(void)
	{
		// ɾ���������Ի�����
		delete DebugDrawer::getSingletonPtr();

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
			* ת������
			*/
			SSceneManagerCreateParam* cm = (SSceneManagerCreateParam*)(pm);
			
			/*
				�����༭����
			*/
			BaseEditor* editor = new SceneManagerEditor(cm->typeMask, cm->sName);
	
			return editor;
		}

		return NULL;
	}
}
