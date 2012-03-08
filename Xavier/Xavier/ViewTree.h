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
class CViewTree : public CTreeCtrl
{
public:
	/**
	 *
	 * \return 
	 */
	CViewTree();

protected:
	/**
	 *
	 * \param wParam 
	 * \param lParam 
	 * \param pResult 
	 * \return 
	 */
	virtual BOOL		OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult);

public:
	/**
	 *
	 * \return 
	 */
	virtual ~CViewTree();

protected:
	DECLARE_MESSAGE_MAP()
};
