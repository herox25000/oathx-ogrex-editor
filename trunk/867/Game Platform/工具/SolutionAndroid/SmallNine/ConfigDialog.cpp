// ConfigDialog.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "SmallNine.h"
#include "ConfigDialog.h"


// CConfigDialog �Ի���

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


// CConfigDialog ��Ϣ�������
