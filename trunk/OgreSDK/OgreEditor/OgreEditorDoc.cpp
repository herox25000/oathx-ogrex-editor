
// OgreEditorDoc.cpp : COgreEditorDoc ���ʵ��
//

#include "stdafx.h"
#include "OgreEditor.h"

#include "OgreEditorDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// COgreEditorDoc

IMPLEMENT_DYNCREATE(COgreEditorDoc, CDocument)

BEGIN_MESSAGE_MAP(COgreEditorDoc, CDocument)
END_MESSAGE_MAP()


// COgreEditorDoc ����/����

COgreEditorDoc::COgreEditorDoc()
{
	// TODO: �ڴ����һ���Թ������

}

COgreEditorDoc::~COgreEditorDoc()
{
}

BOOL COgreEditorDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: �ڴ�������³�ʼ������
	// (SDI �ĵ������ø��ĵ�)

	return TRUE;
}




// COgreEditorDoc ���л�

void COgreEditorDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: �ڴ���Ӵ洢����
	}
	else
	{
		// TODO: �ڴ���Ӽ��ش���
	}
}


// COgreEditorDoc ���

#ifdef _DEBUG
void COgreEditorDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void COgreEditorDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// COgreEditorDoc ����
