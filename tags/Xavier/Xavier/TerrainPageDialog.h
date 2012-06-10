#pragma once

/**
* \ingroup : Xavier
*
* \os&IDE  : Microsoft Windows XP (SP3)  &  Microsoft Visual C++ .NET 2008 & ogre1.8
*
* \VERSION : 1.0
*
* \@date   : 2012-06-10
*
* \Author  : lp
*
* \Desc    : 
*
* \bug     : 
*
*/
class CTerrainPageDialog : public CDialog
{
	DECLARE_DYNAMIC(CTerrainPageDialog)

public:
	/**
	 *
	 * \param pParent 
	 * \return 
	 */
	CTerrainPageDialog(CWnd* pParent = NULL);

	/**
	 *
	 * \return 
	 */
	virtual ~CTerrainPageDialog();

	enum { IDD = IDD_DIALOG_TERRAIN_PAGE };

protected:
	/**
	 *
	 * \param pDX 
	 */
	virtual void DoDataExchange(CDataExchange* pDX);

	DECLARE_MESSAGE_MAP()

public:
	/**
	 *
	 */
	afx_msg void OnBnClickedOk();

	/**
	 *
	 */
	afx_msg void OnBnClickedCancel();

	/**
	 *
	 * \return 
	 */
	virtual BOOL OnInitDialog();
};
