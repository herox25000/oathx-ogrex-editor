
// XavierEditorDoc.cpp : CXavierEditorDoc ���ʵ��
//

#include "stdafx.h"
#include "XavierEditor.h"

#include "XavierEditorDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CXavierEditorDoc

IMPLEMENT_DYNCREATE(CXavierEditorDoc, CDocument)

BEGIN_MESSAGE_MAP(CXavierEditorDoc, CDocument)
END_MESSAGE_MAP()


// CXavierEditorDoc ����/����

CXavierEditorDoc::CXavierEditorDoc()
{
	// TODO: �ڴ����һ���Թ������

}

CXavierEditorDoc::~CXavierEditorDoc()
{
}

BOOL CXavierEditorDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: �ڴ�������³�ʼ������
	// (SDI �ĵ������ø��ĵ�)

	return TRUE;
}




// CXavierEditorDoc ���л�

void CXavierEditorDoc::Serialize(CArchive& ar)
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


// CXavierEditorDoc ���

#ifdef _DEBUG
void CXavierEditorDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CXavierEditorDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CXavierEditorDoc ����
