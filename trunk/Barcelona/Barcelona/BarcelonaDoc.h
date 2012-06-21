#pragma once


/**
* \ingroup : Barcelona
*
* \os&IDE  : Microsoft Windows XP (SP2)  &  Microsoft Visual C++ .NET 2008
*
* \VERSION : 1.0
*
* \date    : 2012-06-22
*
* \Author  : lp
*
* \Desc    : 
*
* \bug     : 
*
*/
class CBarcelonaDoc : public CDocument
{
protected:
	/**
	 *
	 * \return 
	 */
	CBarcelonaDoc();
	DECLARE_DYNCREATE(CBarcelonaDoc)

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
	virtual ~CBarcelonaDoc();
#ifdef _DEBUG
	/**
	 *
	 */
	virtual void AssertValid() const;

	/**
	 *
	 * \param dc 
	 */
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	DECLARE_MESSAGE_MAP()
};


