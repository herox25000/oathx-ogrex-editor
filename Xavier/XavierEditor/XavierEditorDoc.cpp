
#include "stdafx.h"
#include "XavierEditor.h"
#include "XavierEditorDoc.h"
#include "XavierEditorInclude.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

IMPLEMENT_DYNCREATE(CXavierEditorDoc, CDocument)

BEGIN_MESSAGE_MAP(CXavierEditorDoc, CDocument)
END_MESSAGE_MAP()

/**
 *
 * \return 
 */
CXavierEditorDoc::CXavierEditorDoc()
{

}

/**
 *
 * \return 
 */
CXavierEditorDoc::~CXavierEditorDoc()
{
}

/**
 *
 * \return 
 */
BOOL CXavierEditorDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	return TRUE;
}

/**
 *
 * \param ar 
 */
void CXavierEditorDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		
	}
	else
	{

	}
}

#ifdef _DEBUG
void CXavierEditorDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CXavierEditorDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif

