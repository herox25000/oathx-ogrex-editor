// RobotDialog.cpp : 实现文件
//

#include "stdafx.h"
#include "SmallNine.h"
#include "RobotDialog.h"
#include "RobotManager.h"
#include ".\robotdialog.h"


IMPLEMENT_DYNAMIC(CRobotDialog, CDialog)
CRobotDialog::CRobotDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CRobotDialog::IDD, pParent)
{
	m_dwGameID = 0;
}

CRobotDialog::~CRobotDialog()
{
}

void CRobotDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CRobotDialog, CDialog)
	ON_EN_CHANGE(IDC_EDIT1, OnEnChangeEdit1)
	ON_BN_CLICKED(IDC_BUTTON3, OnBnClickedButton3)
	ON_EN_CHANGE(IDC_EDIT4, OnEnChangeEdit4)
	ON_BN_CLICKED(IDC_BUTTON_SAVE, OnBnClickedButtonSave)
	ON_BN_CLICKED(IDC_BUTTON_GET, OnBnClickedButtonGet)
END_MESSAGE_MAP()


BOOL CRobotDialog::OnInitDialog()
{
	CDialog::OnInitDialog();

	return TRUE; 
}

void CRobotDialog::OnEnChangeEdit1()
{
	CString buffer;
	GetDlgItemText(IDC_EDIT1, buffer);
	if (buffer.GetLength() >= 6)
	{
		m_dwGameID		= atol(buffer.GetBuffer());
		IRobot* pRobot	= RobotManager::GetSingleton().SearchRobotByGameID(m_dwGameID);
		if (pRobot != NULL)
		{
			tagUserInfo* pUserInfo = pRobot->GetUserInfo();
			SetDlgItemText(IDC_EDIT2, pUserInfo->szName);

			char szTmp[128];
			sprintf(szTmp, "%I64d", pUserInfo->lScore);
			SetDlgItemText(IDC_EDIT3, szTmp);
		}
	}
}

void CRobotDialog::OnBnClickedButton3()
{
	if (m_dwGameID)
	{
		IRobot* pRobot	= RobotManager::GetSingleton().SearchRobotByGameID(m_dwGameID);
		if (pRobot)
		{
			pRobot->SetState(ROBOT_INVALID);
		}
	}
}

void CRobotDialog::OnEnChangeEdit4()
{
	CString buffer;
	GetDlgItemText(IDC_EDIT4, buffer);
	if (buffer.GetLength() >= 6)
	{
		m_dwGameID		= atol(buffer.GetBuffer());
		IRobot* pRobot	= RobotManager::GetSingleton().SearchRobotByGameID(m_dwGameID);
		if (pRobot != NULL)
		{
			tagUserInfo* pUserInfo = pRobot->GetUserInfo();
			SetDlgItemText(IDC_EDIT5, pUserInfo->szName);

			char szTmp[128];
			sprintf(szTmp, "%I64d", pUserInfo->lScore);
			SetDlgItemText(IDC_EDIT6, szTmp);
		}
	}
}

void CRobotDialog::OnBnClickedButtonSave()
{
	CString buffer;
	GetDlgItemText(IDC_EDIT4, buffer);
	DWORD dwID	= atol(buffer.GetBuffer());
	IRobot* pRobot	= RobotManager::GetSingleton().SearchRobotByGameID(dwID);
	if (pRobot)
	{
		GetDlgItemText(IDC_EDIT7, buffer);
		INT64 nScore = _atoi64(buffer.GetBuffer());
		pRobot->BankSaveScore(nScore);
	}
}

void CRobotDialog::OnBnClickedButtonGet()
{
	CString buffer;
	GetDlgItemText(IDC_EDIT4, buffer);
	DWORD dwID	= atol(buffer.GetBuffer());
	IRobot* pRobot	= RobotManager::GetSingleton().SearchRobotByGameID(dwID);
	if (pRobot)
	{
		GetDlgItemText(IDC_EDIT7, buffer);
		INT64 nScore = _atoi64(buffer.GetBuffer());
		pRobot->BankGetScore(nScore);
	}
}
