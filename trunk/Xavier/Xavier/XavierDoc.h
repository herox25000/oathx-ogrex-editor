#pragma once

/**
* \ingroup : Xavier
*
* \os&IDE  : Microsoft Windows XP (SP2)  &  Microsoft Visual C++ .NET 2008
*
* \VERSION : 1.0
*
* \date    : 2012-03-08
*
* \Author  : lp
*
* \Desc    : 
*
* \bug     : 
*
*/
class CXavierDoc : public CDocument
{
protected:
	CXavierDoc();
	DECLARE_DYNCREATE(CXavierDoc)

public:
	/**
	 *
	 * \return 
	 */
	virtual BOOL		OnNewDocument();

	/**
	 *
	 * \param ar 
	 */
	virtual void		Serialize(CArchive& ar);

public:
	virtual ~CXavierDoc();
#ifdef _DEBUG
	/**
	 *
	 */
	virtual void		AssertValid() const;

	/**
	 *
	 * \param dc 
	 */
	virtual void		Dump(CDumpContext& dc) const;
#endif

protected:
	DECLARE_MESSAGE_MAP()
};


