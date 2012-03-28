#include "OgreAppEditPrerequisites.h"
#include "OgreGridEditor.h"
#include "OgreDebugDrawer.h"

namespace Ogre
{
	/**
	 *
	 * \param fWidth 
	 * \param fSize 
	 * \param fDepth 
	 * \return 
	 */
	GridEditor::GridEditor(SceneManager* pSceneManager, Real fWidth, Real fSize, Real fDepth)
		: m_pSceneManager(pSceneManager), m_fDepth(fDepth), m_fSize(fSize), m_fWidth(fWidth), m_pGrid(NULL), m_pLine(NULL)
	{
		setTypeName(EDIT_GRIDEDIROR);
		createGird();

		addProperty("display", 
			Any(true),
			"辅助格线是否显示", PROPERTY_BOOL);
		
		// 订阅事件
		subscribeEvent(PropertySet::EventValueChanged, Event::Subscriber(&GridEditor::onPropertyChanaged, this));
	}

	/**
	 *
	 * \param void 
	 * \return 
	 */
	GridEditor::~GridEditor(void)
	{
		destroy();
	}
	
	/**
	 *
	 */
	void	GridEditor::createGird()
	{
		if (m_pGrid == NULL && m_pLine == NULL)
		{
			m_pGrid = m_pSceneManager->createManualObject("GridEditor/Line3D");
			m_pGrid->begin("Editor/GridLine3D",RenderOperation::OT_LINE_LIST);

			Vector3	vStart(m_fWidth / 2, 0, m_fDepth / 2);
			Real	fStartZ = vStart.z;

			while(fStartZ >= -vStart.z)
			{
				m_pGrid->position(-vStart.x,	0, fStartZ);
				m_pGrid->colour(0,1,0,1);
				m_pGrid->position(vStart.x,		0, fStartZ);

				fStartZ -= m_fSize;
			}

			Real	fStartX = -vStart.x;
			while(fStartX <= vStart.x)
			{
				m_pGrid->position(fStartX,		0, vStart.z);
				m_pGrid->colour(0,1,0,1);
				m_pGrid->position(fStartX,		0, -vStart.z);

				fStartX += m_fSize;
			}

			m_pGrid->end();

			m_pLine = m_pSceneManager->getRootSceneNode()->createChildSceneNode("GridEditor/Line3DNode");
			m_pLine->attachObject(m_pGrid);
		}
	}

	/**
	 *
	 */
	void	GridEditor::destroy()
	{
		m_pSceneManager->destroyManualObject(m_pGrid);
		m_pGrid = NULL;

		m_pSceneManager->destroySceneNode(m_pLine->getName());
		m_pLine = NULL;
	}

	/**
	 *
	 * \param args 
	 * \return 
	 */
	bool	GridEditor::onPropertyChanaged(const EventArgs& args)
	{
		const PropertyEventArgs& evt = static_cast<const PropertyEventArgs&>(args);
		if (evt.pProperty != NULL)
		{
			String name = evt.pProperty->getName();
			if (name == "display")
			{
				bool bDisplay = any_cast<bool>(evt.pProperty->getValue());
				if (bDisplay)
					createGird();
				else
					destroy();
			}
		}

		return true;
	}

	/**
	 *
	 * \return 
	 */
	GridEditorFactory::GridEditorFactory()
	{
		setTypeName(FACTORY_GRID);
	}

	/**
	 *
	 * \param pm 
	 * \return 
	 */
	BaseEditor*	GridEditorFactory::create(const SBaseCreateParam* pm)
	{
		SGridCreateParam* cm = (SGridCreateParam*)(pm);

		/*
		* 获取场景管理器
		*/
		SceneManager* pMgr = Root::getSingletonPtr()->getSceneManager(NAME_SCENEMANAGER);
		assert(pMgr != NULL);

		return new GridEditor(pMgr, cm->fWidth, cm->fSize, cm->fDepth);
	}
}
