#include "stdafx.h"
#include "Xavier.h"
#include "XavierDoc.h"

IMPLEMENT_DYNCREATE(CXavierDoc, CDocument)

BEGIN_MESSAGE_MAP(CXavierDoc, CDocument)
END_MESSAGE_MAP()


/**
 *
 * \return 
 */
CXavierDoc::CXavierDoc()
{

}

/**
 *
 * \return 
 */
CXavierDoc::~CXavierDoc()
{
}

/**
 *
 * \return 
 */
BOOL	CXavierDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	return TRUE;
}

/**
 *
 * \param ar 
 */
void	CXavierDoc::Serialize(CArchive& ar)
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

void	CXavierDoc::SetTitle(LPCTSTR lpszTitle)
{
	CDocument::SetTitle("Ogre");
}

#ifdef _DEBUG
/**
 *
 */
void	CXavierDoc::AssertValid() const
{
	CDocument::AssertValid();
}

/**
 *
 * \param dc 
 */
void	CXavierDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif

