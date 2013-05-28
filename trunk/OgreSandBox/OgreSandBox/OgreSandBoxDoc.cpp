
// OgreSandBoxDoc.cpp : COgreSandBoxDoc 类的实现
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


// COgreSandBoxDoc 构造/析构

COgreSandBoxDoc::COgreSandBoxDoc()
{
	// TODO: 在此添加一次性构造代码

}

COgreSandBoxDoc::~COgreSandBoxDoc()
{
}

BOOL COgreSandBoxDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 在此添加重新初始化代码
	// (SDI 文档将重用该文档)

	return TRUE;
}




// COgreSandBoxDoc 序列化

void COgreSandBoxDoc::Serialize(CArchive& ar)
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


// COgreSandBoxDoc 诊断

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


// COgreSandBoxDoc 命令
