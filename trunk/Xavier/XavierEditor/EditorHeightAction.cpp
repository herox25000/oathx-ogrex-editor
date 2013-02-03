#include "stdafx.h"
#include "EditorPlugin.h"
#include "EditorHeightAction.h"
#include "EditorPluginManager.h"
#include "EditorActionManager.h"
#include "EditorSystem.h"

namespace Ogre
{
	using namespace std;

	static uint32	nHeightActionCount = 0;

	/**
	 *
	 * \param pHeightData 
	 * \param rect 
	 * \return 
	 */
	EditorHeightAction::EditorHeightAction(const String& name, int nPageX, int nPageY, float* pHeightData, const Rect& area)
		: EditorAction(name), m_nPageX(nPageX), m_nPageY(nPageY),  m_Rect(area)
	{
		String curPath = EditorSystem::getSingleton().getModulePath();
		sprintf_s(m_chFileName, "%s/temp/%s_%d.action", curPath.c_str(), name.c_str(), nHeightActionCount++);
		
		uint32 nSize = area.width() * area.height();

		fstream fsm(m_chFileName, 
			ios::out|ios::binary);

		DataStreamPtr stream = DataStreamPtr(new FileStreamDataStream(&fsm, 0));

		StreamSerialiser ss(stream);
		ss.writeChunkBegin(1, 1);
		ss.write((const float*)pHeightData, nSize);
		ss.writeChunkEnd(1);

		stream.setNull();
		
	}

	/**
	 *
	 * \return 
	 */
	EditorHeightAction::~EditorHeightAction()
	{
		::DeleteFile(m_chFileName);
	}

	/**
	 *
	 */
	void	EditorHeightAction::execute()
	{
		uint32	nSize	= m_Rect.width() * m_Rect.height();
		float*	pData	= new float [nSize];
		
		fstream fsm(m_chFileName,
			ios::in|std::ios::binary);

		DataStreamPtr stream = DataStreamPtr(new FileStreamDataStream(&fsm, 0));

		StreamSerialiser ss(stream);
		ss.readChunkBegin(1, 1);
		ss.read((float*)pData, nSize);
		stream.setNull();

		EditorTerrainPage* pPage = static_cast<EditorTerrainPage *>(
			EditorPluginManager::getSingleton().findPlugin(m_Name)
			);
		if(pPage)
		{
			pPage->swapHeight(m_Rect, pData);
		}

		delete [] pData;
	}
}