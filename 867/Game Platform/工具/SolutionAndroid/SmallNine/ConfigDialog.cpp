// ConfigDialog.cpp : 实现文件
//

#include "stdafx.h"
#include "SmallNine.h"
#include "ConfigDialog.h"


// CConfigDialog 对话框

IMPLEMENT_DYNAMIC(CConfigDialog, CDialog)
CConfigDialog::CConfigDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CConfigDialog::IDD, pParent)
{
}

CConfigDialog::~CConfigDialog()
{
}

void CConfigDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CConfigDialog, CDialog)
END_MESSAGE_MAP()


// CConfigDialog 消息处理程序
