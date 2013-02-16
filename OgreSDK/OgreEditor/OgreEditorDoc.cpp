
// OgreEditorDoc.cpp : COgreEditorDoc 类的实现
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


// COgreEditorDoc 构造/析构

COgreEditorDoc::COgreEditorDoc()
{
	// TODO: 在此添加一次性构造代码

}

COgreEditorDoc::~COgreEditorDoc()
{
}

BOOL COgreEditorDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 在此添加重新初始化代码
	// (SDI 文档将重用该文档)

	return TRUE;
}




// COgreEditorDoc 序列化

void COgreEditorDoc::Serialize(CArchive& ar)
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


// COgreEditorDoc 诊断

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


// COgreEditorDoc 命令
