#pragma once

/**
* \ingroup : OgreEditor
*
* \os&IDE  : Microsoft Windows XP (SP3)  &  Microsoft Visual C++ .NET 2008
*
* \VERSION : 1.0
*
* \date    : 2013-02-16
*
* \Author  : lp
*
* \Desc    :
*
* \bug     : 
*
* \Copyright (c) 2012 lp All rights reserved.
*/
class CTerrainEditorView : public CDockablePane
{
	DECLARE_DYNAMIC(CTerrainEditorView)

public:
	CTerrainEditorView();
	virtual ~CTerrainEditorView();

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg int		OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void	OnDestroy();
};


