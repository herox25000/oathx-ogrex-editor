#include "stdafx.h"
#include "DecalImageListBox.h"
#include "XavierEditorInclude.h"
#include "MainFrm.h"
#include <atlimage.h>


IMPLEMENT_DYNAMIC(CDecalImageListBox, CListCtrl)

/**
 *
 * \return 
 */
CDecalImageListBox::CDecalImageListBox()
{

}

/**
 *
 * \return 
 */
CDecalImageListBox::~CDecalImageListBox()
{
}


BEGIN_MESSAGE_MAP(CDecalImageListBox, CListCtrl)
	
	ON_NOTIFY_REFLECT(NM_CLICK, &CDecalImageListBox::OnNMClick)
END_MESSAGE_MAP()

/**
 *
 * \param *pNMHDR 
 * \param *pResult 
 */
void		CDecalImageListBox::OnNMClick(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	if (pNMItemActivate->iItem != -1)
	{
		m_cItemText = GetItemText(pNMItemActivate->iItem, pNMItemActivate->iSubItem);
		if (!m_cItemText.IsEmpty() && m_oldDecalName != m_cItemText)
		{
			CMainFrame* pMainFrame = (CMainFrame*)(AfxGetMainWnd());
			if (pMainFrame)
			{
				EditorTerrain* pPlugin = static_cast<EditorTerrain*>(
					EditorPluginManager::getSingletonPtr()->findPlugin(EDITOR_TERRAIN)
					);
				if (pPlugin)
				{
					String s(m_cItemText.GetBuffer());
					size_t iPos = s.find_last_of('_');
					if (iPos != String::npos)
					{
						String name = s.substr(0, iPos+1);
						
						String specular		= name + "diffusespecular.dds";
						String normalheight = name + "normalheight.dds";
						
						pPlugin->setBlendTexture(specular, normalheight);
					}
					else
					{
						TKLogEvent("file name error: " + String(m_cItemText.GetBuffer()), LML_TRIVIAL);
					}
				}
			}

			TKLogEvent("Select decal image " + String(m_cItemText.GetBuffer()), LML_NORMAL);

			m_oldDecalName = m_cItemText;
		}
	}

	*pResult = 0;
}
