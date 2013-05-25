#pragma once


/**
* \ingroup : XavierEditor
*
* \os&IDE  : Microsoft Windows XP (SP2)  &  Microsoft Visual C++ .NET 2008
*
* \VERSION : 1.0
*
* \date    : 2013-02-04
*
* \Author  : lp
*
* \Desc    : 
*
* \bug     : 
*
* \Copyright (c) 2012 lp All rights reserved.
*/
class CXavierEditorDoc : public CDocument
{
protected:
	/**
	 *
	 * \return 
	 */
	CXavierEditorDoc();
	DECLARE_DYNCREATE(CXavierEditorDoc)

public:
	/**
	 *
	 * \return 
	 */
	virtual BOOL OnNewDocument();

	/**
	 *
	 * \param ar 
	 */
	virtual void Serialize(CArchive& ar);

public:
	virtual ~CXavierEditorDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	DECLARE_MESSAGE_MAP()
};


