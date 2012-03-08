
// XavierDoc.cpp : CXavierDoc 类的实现
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


// CXavierDoc 构造/析构

CXavierDoc::CXavierDoc()
{
	// TODO: 在此添加一次性构造代码

}

CXavierDoc::~CXavierDoc()
{
}

BOOL CXavierDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 在此添加重新初始化代码
	// (SDI 文档将重用该文档)

	return TRUE;
}




// CXavierDoc 序列化

void CXavierDoc::Serialize(CArchive& ar)
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


// CXavierDoc 诊断

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


// CXavierDoc 命令
