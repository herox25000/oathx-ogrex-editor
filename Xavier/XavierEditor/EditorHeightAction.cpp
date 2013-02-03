#include "stdafx.h"
#include "OgreDataStream.h"
#include "OgreStreamSerialiser.h"
#include "OgreTerrain.h"
#include "OgreTerrainGroup.h"
#include "OgreTerrainQuadTreeNode.h"
#include "OgreTerrainMaterialGeneratorA.h"
#include "OgreTerrainPaging.h"
#include "EditorHeightAction.h"
#include "EditorPluginManager.h"
#include "EditorActionManager.h"

namespace Ogre
{
	static uint32	nHeightActionCount = 0;
	/**
	 *
	 * \param pHeightData 
	 * \param rect 
	 * \return 
	 */
	EditorHeightAction::EditorHeightAction(const String& name, int nPageX, int nPageY, float* pHeightData, const Rect& area)
		: m_Name(name), m_Rect(area), m_nPageX(nPageX), m_nPageY(nPageY)
	{
		uint32 nSize = area.width() * area.height();

		char szFileDir[MAX_PATH];
		::GetModuleFileName(NULL, szFileDir, MAX_PATH);

		String path(szFileDir);
		size_t iPos = path.find_last_of('\\');
		if (iPos == String::npos)
		{
			iPos = path.find_last_of('/');
		}

		if (iPos != String::npos)
		{
			path = path.substr(0,  iPos);

			sprintf_s(m_chSaveName, "%s/temp/%s%d.esh", path.c_str(), name.c_str(), nHeightActionCount++);
			
			std::fstream fsm(m_chSaveName, 
				std::ios::out|std::ios::binary);

			DataStreamPtr stream = DataStreamPtr(new FileStreamDataStream(&fsm, 0));

			StreamSerialiser ss(stream);
			ss.writeChunkBegin(1, 1);
			ss.write((const float*)pHeightData, nSize);
			ss.writeChunkEnd(1);

			stream.setNull();
		}
	}

	/**
	 *
	 * \return 
	 */
	EditorHeightAction::~EditorHeightAction()
	{
		::DeleteFile(m_chSaveName);
	}

	/**
	 *
	 */
	void	EditorHeightAction::execute()
	{
		uint32	nSize	= m_Rect.width() * m_Rect.height();
		float*	pData	= new float [nSize];
		
		std::fstream fsm(m_chSaveName,
			std::ios::in|std::ios::binary);

		DataStreamPtr stream = DataStreamPtr(new FileStreamDataStream(&fsm, 0));
		Ogre::StreamSerialiser ss(stream);
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