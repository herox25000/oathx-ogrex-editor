#include "stdafx.h"
#include "Barcelona.h"
#include "BarcelonaDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

IMPLEMENT_DYNCREATE(CBarcelonaDoc, CDocument)

BEGIN_MESSAGE_MAP(CBarcelonaDoc, CDocument)
END_MESSAGE_MAP()

/**
 *
 * \return 
 */
CBarcelonaDoc::CBarcelonaDoc()
{

}

/**
 *
 * \return 
 */
CBarcelonaDoc::~CBarcelonaDoc()
{
}

/**
 *
 * \return 
 */
BOOL	CBarcelonaDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	return TRUE;
}

/**
 *
 * \param ar 
 */
void	CBarcelonaDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add save code
	}
	else
	{
		// TODO: add load code
	}
}


#ifdef _DEBUG
/**
 *
 */
void	CBarcelonaDoc::AssertValid() const
{
	CDocument::AssertValid();
}

/**
 *
 * \param dc 
 */
void	CBarcelonaDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif
