
// OgreSandBoxDoc.cpp : COgreSandBoxDoc ���ʵ��
//

#include "stdafx.h"
#include "OgreSandBox.h"

#include "OgreSandBoxDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// COgreSandBoxDoc

IMPLEMENT_DYNCREATE(COgreSandBoxDoc, CDocument)

BEGIN_MESSAGE_MAP(COgreSandBoxDoc, CDocument)
END_MESSAGE_MAP()


// COgreSandBoxDoc ����/����

COgreSandBoxDoc::COgreSandBoxDoc()
{
	// TODO: �ڴ����һ���Թ������

}

COgreSandBoxDoc::~COgreSandBoxDoc()
{
}

BOOL COgreSandBoxDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: �ڴ�������³�ʼ������
	// (SDI �ĵ������ø��ĵ�)

	return TRUE;
}




// COgreSandBoxDoc ���л�

void COgreSandBoxDoc::Serialize(CArchive& ar)
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


// COgreSandBoxDoc ���

#ifdef _DEBUG
void COgreSandBoxDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void COgreSandBoxDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// COgreSandBoxDoc ����
