
// EditorDoc.cpp : CEditorDoc ���ʵ��
//

#include "stdafx.h"
#include "Editor.h"
#include "EditorDoc.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CEditorDoc

IMPLEMENT_DYNCREATE(CEditorDoc, CDocument)

BEGIN_MESSAGE_MAP(CEditorDoc, CDocument)
END_MESSAGE_MAP()


// CEditorDoc ����/����
//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////
CEditorDoc::CEditorDoc()
{

}

//////////////////////////////////////////////////////////////////////////
CEditorDoc::~CEditorDoc()
{
}

//////////////////////////////////////////////////////////////////////////
BOOL CEditorDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	return TRUE;
}

//////////////////////////////////////////////////////////////////////////
void CEditorDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{

	}
	else
	{
		CString sPath = ar.GetFile()->GetFilePath();

		CMainFrame* pMain = (CMainFrame*)(AfxGetMainWnd());
		ASSERT(pMain != NULL);
		pMain->GetFileView()->OpenSolution(sPath);
	}
}

//////////////////////////////////////////////////////////////////////////
#ifdef _DEBUG
void CEditorDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CEditorDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

