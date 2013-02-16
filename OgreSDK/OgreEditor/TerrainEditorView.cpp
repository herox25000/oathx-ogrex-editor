#include "stdafx.h"
#include "OgreEditor.h"
#include "TerrainEditorView.h"


IMPLEMENT_DYNAMIC(CTerrainEditorView, CDockablePane)

/**
 *
 * \return 
 */
CTerrainEditorView::CTerrainEditorView()
{

}

/**
 *
 * \return 
 */
CTerrainEditorView::~CTerrainEditorView()
{
}


BEGIN_MESSAGE_MAP(CTerrainEditorView, CDockablePane)
	ON_WM_CREATE()
	ON_WM_DESTROY()
END_MESSAGE_MAP()

/**
 *
 * \param lpCreateStruct 
 * \return 
 */
int CTerrainEditorView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDockablePane::OnCreate(lpCreateStruct) == -1)
		return -1;

	try{
#ifdef _DEBUG
		EditorSystem::getSingletonPtr()->loadPlugin("OgreTerrainEditorPlugin_d.dll");
#else
		EditorSystem::getSingletonPtr()->loadPlugin("OgreTerrainEditorPlugin.dll");
#endif
	}
	catch(Exception& e)
	{
		AfxMessageBox(e.getFullDescription().c_str());
	}

	return 0;
}

/**
 *
 */
void CTerrainEditorView::OnDestroy()
{
	CDockablePane::OnDestroy();

//	try {
//#ifdef _DEBUG
//	EditorSystem::getSingletonPtr()->unloadPlugin("OgreTerrainEditorPlugin_d.dll");
//#else
//	EditorSystem::getSingletonPtr()->unloadPlugin("OgreTerrainEditorPlugin.dll");
//#endif
//	}
//	catch(Exception& e)
//	{
//		AfxMessageBox(e.getFullDescription().c_str());
//	}
}
