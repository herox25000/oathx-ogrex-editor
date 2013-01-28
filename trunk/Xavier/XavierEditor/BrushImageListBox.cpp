#include "stdafx.h"
#include "BrushImageListBox.h"
#include "XavierEditorInclude.h"
#include "MainFrm.h"
#include <atlimage.h>


IMPLEMENT_DYNAMIC(CBrushImageListBox, CListCtrl)

/**
 *
 * \return 
 */
CBrushImageListBox::CBrushImageListBox()
{

}

/**
 *
 * \return 
 */
CBrushImageListBox::~CBrushImageListBox()
{
}


BEGIN_MESSAGE_MAP(CBrushImageListBox, CListCtrl)
	ON_NOTIFY_REFLECT(NM_CLICK, &CBrushImageListBox::OnNMClick)
END_MESSAGE_MAP()


/**
 *
 * \param *pNMHDR 
 * \param *pResult 
 */
void		CBrushImageListBox::OnNMClick(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	if (pNMItemActivate->iItem != -1)
	{
		m_cItemText = GetItemText(pNMItemActivate->iItem, pNMItemActivate->iSubItem);
		if (!m_cItemText.IsEmpty() && m_oldBrushName != m_cItemText)
		{
			CMainFrame* pMainFrame = (CMainFrame*)(AfxGetMainWnd());
			if (pMainFrame)
			{
				EditorTerrain* pPlugin = static_cast<EditorTerrain*>(
					EditorPluginManager::getSingletonPtr()->findPlugin(EDITOR_TERRAIN)
					);
				if (pPlugin)
				{
					MeshBrush* pBrush = pPlugin->getMeshBrush();
					if (pBrush)
					{
						pBrush->setBrushTexture(m_cItemText.GetBuffer());
					}
				}
			}

			TKLogEvent("Select brush image " + String(m_cItemText.GetBuffer()), LML_NORMAL);

			m_oldBrushName = m_cItemText;
		}
	}

	*pResult = 0;
}
