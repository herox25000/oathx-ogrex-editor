
// XavierDoc.cpp : CXavierDoc ���ʵ��
//

#include "stdafx.h"
#include "Xavier.h"

#include "XavierDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CXavierDoc

IMPLEMENT_DYNCREATE(CXavierDoc, CDocument)

BEGIN_MESSAGE_MAP(CXavierDoc, CDocument)
END_MESSAGE_MAP()


// CXavierDoc ����/����

CXavierDoc::CXavierDoc()
{
	// TODO: �ڴ����һ���Թ������

}

CXavierDoc::~CXavierDoc()
{
}

BOOL CXavierDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: �ڴ�������³�ʼ������
	// (SDI �ĵ������ø��ĵ�)

	return TRUE;
}




// CXavierDoc ���л�

void CXavierDoc::Serialize(CArchive& ar)
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


// CXavierDoc ���

#ifdef _DEBUG
void CXavierDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CXavierDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CXavierDoc ����
