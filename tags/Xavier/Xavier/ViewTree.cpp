#include "stdafx.h"
#include "ViewTree.h"
#include "MainFrm.h"


/**
 *
 * \return 
 */
CViewTree::CViewTree()
{
}

/**
 *
 * \return 
 */
CViewTree::~CViewTree()
{
}

BEGIN_MESSAGE_MAP(CViewTree, CTreeCtrl)
	ON_NOTIFY_REFLECT(TVN_SELCHANGED,	&CViewTree::OnTvnSelchanged)
	ON_NOTIFY_REFLECT(NM_CLICK, &CViewTree::OnNMClick)
END_MESSAGE_MAP()


/**
 *
 * \param wParam 
 * \param lParam 
 * \param pResult 
 * \return 
 */
BOOL	CViewTree::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult)
{
	BOOL bRes = CTreeCtrl::OnNotify(wParam, lParam, pResult);

	NMHDR* pNMHDR = (NMHDR*)lParam;
	ASSERT(pNMHDR != NULL);

	if (pNMHDR && pNMHDR->code == TTN_SHOW && GetToolTips() != NULL)
	{
		GetToolTips()->SetWindowPos(&wndTop, -1, -1, -1, -1,
			SWP_NOMOVE | SWP_NOACTIVATE | SWP_NOSIZE);
	}

	return bRes;
}

/**
 *
 * \param *pNMHDR 
 * \param *pResult 
 */
void	CViewTree::OnTvnSelchanged(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
	
	CMainFrame* pMainFrame = (CMainFrame*)(AfxGetMainWnd());
	if (pMainFrame != NULL)
	{
		/*
		* ��ȡѡ����ı�
		*/
		CString text = GetItemText(pNMTreeView->itemNew.hItem);
		wmSelectEvent evt;
		strcpy(evt.Name, text.GetBuffer());
		
		/*
		* ����ѡ���¼�
		*/
		::SendMessage(pMainFrame->GetPropertyWnd()->m_hWnd, 
			WM_SELECT_EDITOR, (WPARAM)(&evt),NULL);
	}
	
	*pResult = 0;
}

/**
 *
 * \param *pNMHDR 
 * \param *pResult 
 */
void	CViewTree::OnNMClick(NMHDR *pNMHDR, LRESULT *pResult)
{
	
	*pResult = 0;
}
