
// XavierEditorDoc.cpp : CXavierEditorDoc 类的实现
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


// CXavierEditorDoc 构造/析构

CXavierEditorDoc::CXavierEditorDoc()
{
	// TODO: 在此添加一次性构造代码

}

CXavierEditorDoc::~CXavierEditorDoc()
{
}

BOOL CXavierEditorDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 在此添加重新初始化代码
	// (SDI 文档将重用该文档)

	return TRUE;
}




// CXavierEditorDoc 序列化

void CXavierEditorDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: 在此添加存储代码
	}
	else
	{
		// TODO: 在此添加加载代码
	}
}


// CXavierEditorDoc 诊断

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


// CXavierEditorDoc 命令
