#include "StdAfx.h"
#include "Resource.h"
#include "Information.h"
#include "DlgInsureCounter.h"
#include ".\dlginsurecounter.h"

//////////////////////////////////////////////////////////////////////////////////

BEGIN_MESSAGE_MAP(CDlgInsureSave, CDialog)
	ON_WM_CTLCOLOR()
	ON_WM_ERASEBKGND()
	ON_EN_CHANGE(IDC_SCORE, OnEnChangeScore)
	ON_BN_CLICKED(IDC_BT_SAVE_SCORE, OnBnClickedSaveScore)
	ON_BN_CLICKED(IDC_BT_TAKE_SCORE, OnBnClickedTakeScore)
	ON_STN_CLICKED(IDC_FORGET_INSURE, OnBnClickedForgetInsure)
END_MESSAGE_MAP()

BEGIN_MESSAGE_MAP(CDlgInsureTransfer, CDialog)
	ON_WM_CTLCOLOR()
	ON_WM_ERASEBKGND()
	ON_EN_CHANGE(IDC_SCORE, OnEnChangeScore)
	ON_STN_CLICKED(IDC_FORGET_INSURE, OnBnClickedForgetInsure)
	ON_BN_CLICKED(IDC_BT_TRANSFER_SCORE, OnBnClickedTransferScore)
	ON_BN_CLICKED(IDC_BY_ID, OnBnClickedById)
	ON_BN_CLICKED(IDC_BY_NAME, OnBnClickedByName)
END_MESSAGE_MAP()

BEGIN_MESSAGE_MAP(CDlgInsureMain, CSkinDialog)
	ON_BN_CLICKED(IDC_BT_QUERY_INFO, OnBnClickedQueryInfo)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB_CONTROL, OnTcnSelchangeInsureMode)
END_MESSAGE_MAP()

//////////////////////////////////////////////////////////////////////////////////

//���캯��
CDlgInsureItem::CDlgInsureItem()
{
}

//��������
CDlgInsureItem::~CDlgInsureItem()
{
}

//��ȡ��Ϸ��
SCORE CDlgInsureItem::GetUserControlScore(CWnd * pWndScore)
{
	//��������
	WORD wIndex=0;
	SCORE lScore=0L;

	//��ȡ��ֵ
	TCHAR szBuffer[32]=TEXT("");
	pWndScore->GetWindowText(szBuffer,CountArray(szBuffer));

	//������ֵ
	while (szBuffer[wIndex]!=0)
	{
		//��������
		WORD wCurrentIndex=wIndex++;

		//������ֵ
		if ((szBuffer[wCurrentIndex]>=TEXT('0'))&&(szBuffer[wCurrentIndex]<=TEXT('9')))
		{
			lScore=lScore*10L+(szBuffer[wCurrentIndex]-TEXT('0'));
		}
	}

	return lScore;
}

//�滭����
VOID CDlgInsureItem::DrawNumberString(CDC * pDC, SCORE lScore, INT nXPos, INT nYPos)
{
	//ת������
	TCHAR szControl[128]=TEXT("");
	SwitchScoreFormat(lScore,3L,szControl,CountArray(szControl));

	//��������
	INT nXDrawPos=nXPos;
	INT nScoreLength=lstrlen(szControl);

	//�滭�ж�
	if (nScoreLength>0L)
	{
		//������Դ
		CPngImage ImageNumber;
		ImageNumber.LoadImage(GetModuleHandle(SHARE_CONTROL_DLL_NAME),TEXT("SCORE_NUMBER"));

		//��ȡ��С
		CSize SizeNumber;
		SizeNumber.SetSize(ImageNumber.GetWidth()/12L,ImageNumber.GetHeight());

		//�滭����
		for (INT i=0;i<nScoreLength;i++)
		{
			//�滭����
			if (szControl[i]==TEXT(','))
			{
				ImageNumber.DrawImage(pDC,nXDrawPos,nYPos,SizeNumber.cx,SizeNumber.cy,SizeNumber.cx*10L,0L);
			}

			//�滭���
			if (szControl[i]==TEXT('.'))
			{
				ImageNumber.DrawImage(pDC,nXDrawPos,nYPos,SizeNumber.cx,SizeNumber.cy,SizeNumber.cx*11L,0L);
			}

			//�滭����
			if (szControl[i]>=TEXT('0')&&szControl[i]<=TEXT('9'))
			{
				ImageNumber.DrawImage(pDC,nXDrawPos,nYPos,SizeNumber.cx,SizeNumber.cy,SizeNumber.cx*(szControl[i]-TEXT('0')),0L);
			}

			//����λ��
			nXDrawPos+=SizeNumber.cx;
		}
	}

	return;
}

//ת���ַ�
VOID CDlgInsureItem::SwitchScoreString(SCORE lScore, LPTSTR pszBuffer, WORD wBufferSize)
{
	//��������
	LPCTSTR pszNumber[]={TEXT("��"),TEXT("Ҽ"),TEXT("��"),TEXT("��"),TEXT("��"),TEXT("��"),TEXT("½"),TEXT("��"),TEXT("��"),TEXT("��")};
	LPCTSTR pszWeiName[]={TEXT("ʰ"),TEXT("��"),TEXT("Ǫ"),TEXT("��"),TEXT("ʰ"),TEXT("��"),TEXT("Ǫ"),TEXT("��"),TEXT("ʰ"),TEXT("��"),TEXT("Ǫ"),TEXT("��")};

	//ת����ֵ
	TCHAR szSwitchScore[16]=TEXT("");
	_sntprintf(szSwitchScore,CountArray(szSwitchScore),TEXT("%I64d"),lScore);

	//��������
	bool bNeedFill=false;
	bool bNeedZero=false;
	UINT uTargetIndex=0,uSourceIndex=0;

	//�ַ�����
	UINT uItemLength=lstrlen(pszNumber[0]);
	UINT uSwitchLength=lstrlen(szSwitchScore);

	//ת������
	for (UINT i=0;i<uSwitchLength;i++)
	{
		//��������
		WORD wNumberIndex=szSwitchScore[i]-TEXT('0');

		//�������
		if ((bNeedZero==true)&&(wNumberIndex!=0L))
		{
			bNeedZero=false;
			_tcsncat(pszBuffer,pszNumber[0],wBufferSize-lstrlen(pszBuffer)-1);
		}

		//��������
		if (wNumberIndex!=0L)
		{
			_tcsncat(pszBuffer,pszNumber[wNumberIndex],wBufferSize-lstrlen(pszBuffer)-1);
		}

		//����λ��
		if ((wNumberIndex!=0L)&&((uSwitchLength-i)>=2))
		{
			bNeedZero=false;
			_tcsncat(pszBuffer,pszWeiName[uSwitchLength-i-2],wBufferSize-lstrlen(pszBuffer)-1);
		}

		//�����ж�
		if ((bNeedZero==false)&&(wNumberIndex==0))
		{
			bNeedZero=true;
		}

		//��λ�ж�
		if ((bNeedFill==false)&&(wNumberIndex!=0))
		{
			bNeedFill=true;
		}

		//�λ��
		if (((uSwitchLength-i)==5)||((uSwitchLength-i)==9))
		{
			//����λ��
			if ((bNeedFill==true)&&(wNumberIndex==0L))
			{
				_tcsncat(pszBuffer,pszWeiName[uSwitchLength-i-2],wBufferSize-lstrlen(pszBuffer)-1);
			}

			//���ñ���
			bNeedZero=false;
			bNeedFill=false;
		}
	}

	return;
}

//ת���ַ�
VOID CDlgInsureItem::SwitchScoreFormat(SCORE lScore, UINT uSpace, LPTSTR pszBuffer, WORD wBufferSize)
{
	//ת����ֵ
	TCHAR szSwitchScore[16]=TEXT("");
	_sntprintf(szSwitchScore,CountArray(szSwitchScore),TEXT("%I64d"),lScore);

	//��������
	WORD wTargetIndex=0;
	WORD wSourceIndex=0;
	UINT uSwitchLength=lstrlen(szSwitchScore);

	//ת���ַ�
	while (szSwitchScore[wSourceIndex]!=0)
	{
		//�����ַ�
		pszBuffer[wTargetIndex++]=szSwitchScore[wSourceIndex++];

		//���붺��
		if ((uSwitchLength!=wSourceIndex)&&(((uSwitchLength-wSourceIndex)%uSpace)==0L))
		{
			pszBuffer[wTargetIndex++]=TEXT(',');
		}
	}

	//�����ַ�
	pszBuffer[wTargetIndex++]=0;

	return;
}

//////////////////////////////////////////////////////////////////////////////////

//���캯��
CDlgInsureSave::CDlgInsureSave() : CDialog(IDD_INSURE_SAVE)
{
	//���ñ���
	m_bSwitchIng=false;

	return;
}

//��������
CDlgInsureSave::~CDlgInsureSave()
{
}

//�ؼ���
VOID CDlgInsureSave::DoDataExchange(CDataExchange * pDX)
{
	__super::DoDataExchange(pDX);

	//��ť�ؼ�
	DDX_Control(pDX, IDC_BT_TAKE_SCORE, m_btTakeScore);
	DDX_Control(pDX, IDC_BT_SAVE_SCORE, m_btSaveScore);

	//�ؼ�����
	DDX_Control(pDX, IDC_SCORE, m_edScore);
	DDX_Control(pDX, IDC_PASSWORD, m_PasswordControl);
	DDX_Control(pDX, IDC_FORGET_INSURE, m_ForgetInsure);
}

//��������
BOOL CDlgInsureSave::OnInitDialog()
{
	__super::OnInitDialog();

	//���ÿؼ�
	m_edScore.LimitText(16L);

	//���ð�ť
	HINSTANCE hResInstance=GetModuleHandle(SHARE_CONTROL_DLL_NAME);
	m_btSaveScore.SetButtonImage(IDB_BT_INSURE_SCORE,TEXT("BT_SAVE_SCORE"),hResInstance,false,false);
	m_btTakeScore.SetButtonImage(IDB_BT_INSURE_SCORE,TEXT("BT_TAKE_SCORE"),hResInstance,false,false);

	return TRUE;
}

//ȷ����ť
VOID CDlgInsureSave::OnOK()
{
	return;
}

//ȡ����ť
VOID CDlgInsureSave::OnCancel()
{
	return;
}

//������Ϣ
VOID CDlgInsureSave::OnEnChangeScore()
{
	//״̬����
	if (m_bSwitchIng==false)
	{
		//���ñ���
		m_bSwitchIng=true;

		//��������
		CWnd * pWndScore=GetDlgItem(IDC_SCORE);
		SCORE lScore=m_DlgInsureItem.GetUserControlScore(pWndScore);
		SCORE lMaxScore=__max(m_pUserInsureInfo->lUserScore, m_pUserInsureInfo->lUserInsure);
		if((m_pUserInsureInfo->lUserScore==0) || (m_pUserInsureInfo->lUserInsure==0))
			lMaxScore=__max(m_pUserInsureInfo->lUserScore, m_pUserInsureInfo->lUserInsure);

		//��������
		if(lScore > lMaxScore) lScore = lMaxScore;

		//���ý���
		if (lScore>0L)
		{
			//ת����ֵ
			TCHAR szString[128]=TEXT("");
			m_DlgInsureItem.SwitchScoreString(lScore,szString,CountArray(szString));

			//ת������
			TCHAR szControl[128]=TEXT("");
			m_DlgInsureItem.SwitchScoreFormat(lScore,3L,szControl,CountArray(szControl));

			//���ÿؼ�
			SetDlgItemText(IDC_SCORE,szControl);
			SetDlgItemText(IDC_SCORE_STRING,szString);

			//���ù��
			INT nScoreLength=m_edScore.GetWindowTextLength();
			m_edScore.SetSel(nScoreLength,nScoreLength,FALSE);
		}
		else
		{
			//���ÿؼ�
			SetDlgItemText(IDC_SCORE,TEXT(""));
			SetDlgItemText(IDC_SCORE_STRING,TEXT(""));
		}

		//���ñ���
		m_bSwitchIng=false;
	}

	return;
}

//ȡ�ť
VOID CDlgInsureSave::OnBnClickedTakeScore()
{
	//��ȡ����
	CWnd * pWndScore=GetDlgItem(IDC_SCORE);
	SCORE lTakeScore=m_DlgInsureItem.GetUserControlScore(pWndScore);

	//��ȡ����
	TCHAR szPassword[LEN_PASSWORD];
	m_PasswordControl.GetUserPassword(szPassword);

	//��������
	TCHAR szInsurePass[LEN_MD5];
	CWHEncrypt::MD5Encrypt(szPassword,szInsurePass);

	//�����ж�
	if (lTakeScore<=0L)
	{
		//��ʾ��Ϣ
		CInformation Information(this);
		Information.ShowMessageBox(TEXT("ȡ������Ϸ����������Ϊ�գ�������������Ϸ��������"),MB_ICONERROR,30);

		//���ý���
		m_edScore.SetFocus();

		return;
	}

	//��Ŀ�ж�
	if (lTakeScore>m_pUserInsureInfo->lUserInsure)
	{
		//��ʾ��Ϣ
		CInformation Information(this);
		Information.ShowMessageBox(TEXT("�����չ���Ϸ�ҵ���Ŀ���㣬������������Ϸ��������"),MB_ICONERROR,30);

		//���ý���
		m_edScore.SetFocus();

		return;
	}

	//�����ж�
	if (szPassword[0]==0)
	{
		//��ʾ��Ϣ
		CInformation Information(this);
		Information.ShowMessageBox(TEXT("���չ����벻��Ϊ�գ����������뱣�չ����룡"),MB_ICONERROR,30);

		//���ý���
		m_PasswordControl.SetFocus();

		return;
	}
	
	//�¼�֪ͨ
	m_pDlgInsureMain->OnMissionStart();
	m_pDlgInsureMain->PerformTakeScore(lTakeScore,szInsurePass);

	return;
}

//��ť
VOID CDlgInsureSave::OnBnClickedSaveScore()
{
	//��������
	CWnd * pWndScore=GetDlgItem(IDC_SCORE);
	SCORE lSaveScore=m_DlgInsureItem.GetUserControlScore(pWndScore);

	//�����ж�
	if (lSaveScore<=0L)
	{
		//��ʾ��Ϣ
		CInformation Information(this);
		Information.ShowMessageBox(TEXT("�������Ϸ����������Ϊ�գ�������������Ϸ��������"),MB_ICONERROR,30);

		//���ý���
		m_edScore.SetFocus();

		return;
	}

	//��Ŀ�ж�
	if (lSaveScore>m_pUserInsureInfo->lUserScore)
	{
		//��ʾ��Ϣ
		CInformation Information(this);
		Information.ShowMessageBox(TEXT("����Я����Ϸ�ҵ���Ŀ���㣬������������Ϸ��������"),MB_ICONERROR,30);

		//���ý���
		m_edScore.SetFocus();

		return;
	}

	//ִ�д��
	m_pDlgInsureMain->OnMissionStart();
	m_pDlgInsureMain->PerformSaveScore(lSaveScore);

	return;
}

//��������
VOID CDlgInsureSave::OnBnClickedForgetInsure()
{
	//�����ַ
	TCHAR szLogonLink[256]=TEXT("");
	_sntprintf(szLogonLink,CountArray(szLogonLink),TEXT("%s/LogonLink4.aspx"),szPlatformLink);

	//��ҳ��
	ShellExecute(NULL,TEXT("OPEN"),szLogonLink,NULL,NULL,SW_NORMAL);

	return;
}

//�滭����
BOOL CDlgInsureSave::OnEraseBkgnd(CDC * pDC)
{
	//��ȡλ��
	CRect rcClient;
	GetClientRect(&rcClient);

	//��������
	CImage ImageBuffer;
	ImageBuffer.Create(rcClient.Width(),rcClient.Height(),32);

	//���� DC
	CImageDC BufferDC(ImageBuffer);
	CDC * pDCBuffer=CDC::FromHandle(BufferDC);

	//���û���
	pDCBuffer->SetBkMode(TRANSPARENT);
	pDCBuffer->SelectObject(CSkinResourceManager::GetInstance()->GetDefaultFont());

	//�滭����
	pDCBuffer->FillSolidRect(&rcClient,CSkinDialog::m_SkinAttribute.m_crBackGround);

	//��ȡλ��
	CRect rcScore;
	m_edScore.GetWindowRect(&rcScore);

	//ת��λ��
	ScreenToClient(&rcScore);

	//�滭����
	pDCBuffer->FillSolidRect(rcScore.left-6,rcScore.top-5,rcScore.Width()+12,24L,CSkinEdit::m_SkinAttribute.m_crEnableBK);

	//�滭����
	COLORREF crColorBorad=CSkinEdit::m_SkinAttribute.m_crEnableBorad;
	pDCBuffer->Draw3dRect(rcScore.left-6,rcScore.top-5,rcScore.Width()+12,24L,crColorBorad,crColorBorad);

	//�滭����
	pDC->BitBlt(0,0,rcClient.Width(),rcClient.Height(),pDCBuffer,0,0,SRCCOPY);

	return TRUE;
}

//�ؼ���ɫ
HBRUSH CDlgInsureSave::OnCtlColor(CDC * pDC, CWnd * pWnd, UINT nCtlColor)
{
	switch (nCtlColor)
	{
	case CTLCOLOR_DLG:
	case CTLCOLOR_BTN:
	case CTLCOLOR_STATIC:
		{
			pDC->SetBkMode(TRANSPARENT);
			pDC->SetTextColor(CSkinDialog::m_SkinAttribute.m_crControlText);
			return CSkinDialog::m_SkinAttribute.m_brBackGround;
		}
	}

	return __super::OnCtlColor(pDC,pWnd,nCtlColor);
}

//////////////////////////////////////////////////////////////////////////////////

//���캯��
CDlgInsureTransfer::CDlgInsureTransfer() : CDialog(IDD_INSURE_TRANSFER)
{
	//���ñ���
	m_bSwitchIng=false;

	return;
}

//��������
CDlgInsureTransfer::~CDlgInsureTransfer()
{
}

//�ؼ���
VOID CDlgInsureTransfer::DoDataExchange(CDataExchange * pDX)
{
	__super::DoDataExchange(pDX);

	//�ؼ�����
	DDX_Control(pDX, IDC_SCORE, m_edScore);
	DDX_Control(pDX, IDC_NICKNAME, m_edNickName);
	DDX_Control(pDX, IDC_PASSWORD, m_PasswordControl);
	DDX_Control(pDX, IDC_FORGET_INSURE, m_ForgetInsure);
	DDX_Control(pDX, IDC_BT_TRANSFER_SCORE, m_btTransferScore);
}

//��������
BOOL CDlgInsureTransfer::OnInitDialog()
{
	__super::OnInitDialog();

	//���ÿؼ�
	m_edScore.LimitText(16L);
	m_edNickName.LimitText(LEN_NICKNAME-1);

	//���ð�ť
	HINSTANCE hResInstance=GetModuleHandle(SHARE_CONTROL_DLL_NAME);
	m_btTransferScore.SetButtonImage(IDB_BT_INSURE_SCORE,TEXT("BT_TRANSFER_SCORE"),hResInstance,false,false);
	((CButton *)GetDlgItem(IDC_BY_NAME))->SetCheck(1);

	return TRUE;
}

//ȷ����ť
VOID CDlgInsureTransfer::OnOK()
{
	//ת�˲���
	OnBnClickedTransferScore();

	return;
}

//ȡ����ť
VOID CDlgInsureTransfer::OnCancel()
{
	return;
}

//������Ϣ
VOID CDlgInsureTransfer::OnEnChangeScore()
{
	//״̬����
	if (m_bSwitchIng==false)
	{
		//���ñ���
		m_bSwitchIng=true;

		//��������
		CWnd * pWndScore=GetDlgItem(IDC_SCORE);
		SCORE lScore=m_DlgInsureItem.GetUserControlScore(pWndScore);

		//��������
		if(lScore > m_pUserInsureInfo->lUserInsure) lScore = m_pUserInsureInfo->lUserInsure;

		//���ý���
		if (lScore>0L)
		{
			//ת����ֵ
			TCHAR szString[128]=TEXT("");
			m_DlgInsureItem.SwitchScoreString(lScore,szString,CountArray(szString));

			//ת������
			TCHAR szControl[128]=TEXT("");
			m_DlgInsureItem.SwitchScoreFormat(lScore,3L,szControl,CountArray(szControl));

			//���ÿؼ�
			SetDlgItemText(IDC_SCORE,szControl);
			SetDlgItemText(IDC_SCORE_STRING,szString);

			//���ù��
			INT nScoreLength=m_edScore.GetWindowTextLength();
			m_edScore.SetSel(nScoreLength,nScoreLength,FALSE);
		}
		else
		{
			//���ÿؼ�
			SetDlgItemText(IDC_SCORE,TEXT(""));
			SetDlgItemText(IDC_SCORE_STRING,TEXT(""));
		}

		//���ñ���
		m_bSwitchIng=false;
	}

	return;
}


//��������
VOID CDlgInsureTransfer::OnBnClickedForgetInsure()
{
	//�����ַ
	TCHAR szLogonLink[256]=TEXT("");
	_sntprintf(szLogonLink,CountArray(szLogonLink),TEXT("%s/LogonLink4.aspx"),szPlatformLink);

	//��ҳ��
	ShellExecute(NULL,TEXT("OPEN"),szLogonLink,NULL,NULL,SW_NORMAL);

	return;
}

//ת�˰�ť
VOID CDlgInsureTransfer::OnBnClickedTransferScore()
{
	//�����ж�
	if (m_pUserInsureInfo->lUserInsure < m_pUserInsureInfo->lTransferPrerequisite)
	{
		//��ʾ��Ϣ
		TCHAR szTipInfo[128]={0};
		_sntprintf(szTipInfo,CountArray(szTipInfo),TEXT("�����չ���Ϸ�ҵ���Ŀ�������ת������ %I64d���޷�����ת�˲�����"),m_pUserInsureInfo->lTransferPrerequisite);
		CInformation Information(this);
		Information.ShowMessageBox(szTipInfo,MB_ICONERROR,30);

		return;
	}

	//��ȡ����
	CWnd * pWndScore=GetDlgItem(IDC_SCORE);
	SCORE lTransferScore=m_DlgInsureItem.GetUserControlScore(pWndScore);

	//��ȡ����
	TCHAR szPassword[LEN_PASSWORD];
	m_PasswordControl.GetUserPassword(szPassword);

	//��������
	TCHAR szInsurePass[LEN_MD5];
	CWHEncrypt::MD5Encrypt(szPassword,szInsurePass);

	//��ȡ�ǳ�
	CString strNickName;
	GetDlgItemText(IDC_NICKNAME,strNickName);

	//��ʽ�ǳ�
	strNickName.TrimLeft();
	strNickName.TrimRight();

	//�ǳ��ж�
	if (strNickName.GetLength()==0)
	{
		//��ʾ��Ϣ
		CInformation Information(this);
		if(((CButton *)GetDlgItem(IDC_BY_NAME))->GetCheck()==BST_CHECKED)
			Information.ShowMessageBox(TEXT("������Ҫ���͵�����ǳƣ�"),MB_ICONERROR,30);
		else
			Information.ShowMessageBox(TEXT("������Ҫ���͵����ID��"),MB_ICONERROR,30);

		//���ý���
		m_edNickName.SetFocus();

		return;
	}

	//ID���ж�
	if(((CButton *)GetDlgItem(IDC_BY_ID))->GetCheck()==BST_CHECKED)
	{
		int nlen = strNickName.GetLength();
		for(int i=0; i<nlen; i++)
		{
			if(strNickName[i] < '0' || strNickName[i] > '9')
			{
				//��ʾ��Ϣ
				CInformation Information(this);
				Information.ShowMessageBox(TEXT("��������ȷ�����ID��"),MB_ICONERROR,30);

				//���ý���
				m_edNickName.SetFocus();
				return;
			}
		}
	}

	//�����ж�
	if (lTransferScore<=0L)
	{
		//��ʾ��Ϣ
		CInformation Information(this);
		Information.ShowMessageBox(TEXT("���͵���Ϸ����������Ϊ�գ�������������Ϸ��������"),MB_ICONERROR,30);

		//���ý���
		m_edScore.SetFocus();

		return;
	}

	//��Ŀ�ж�
	if (lTransferScore>m_pUserInsureInfo->lUserInsure)
	{
		//��ʾ��Ϣ
		CInformation Information(this);
		Information.ShowMessageBox(TEXT("�����չ���Ϸ�ҵ���Ŀ���㣬������������Ϸ��������"),MB_ICONERROR,30);

		//���ý���
		m_edScore.SetFocus();

		return;
	}

	//��Ŀ�ж�
	if (lTransferScore<m_pUserInsureInfo->lTransferPrerequisite)
	{
		//��ʾ��Ϣ
		TCHAR szTipInfo[128]={0};
		_sntprintf(szTipInfo,CountArray(szTipInfo),TEXT("�ӱ��չ�ת�˵���Ϸ����Ŀ�������� %I64d���޷�����ת�˲�����"),m_pUserInsureInfo->lTransferPrerequisite);
		CInformation Information(this);
		Information.ShowMessageBox(szTipInfo,MB_ICONERROR,30);

		//���ý���
		m_edScore.SetFocus();

		return;
	}

	//�����ж�
	if (szPassword[0]==0)
	{
		//��ʾ��Ϣ
		CInformation Information(this);
		Information.ShowMessageBox(TEXT("���չ����벻��Ϊ�գ����������뱣�չ����룡"),MB_ICONERROR,30);

		//���ý���
		m_PasswordControl.SetFocus();

		return;
	}
	
	//�¼�֪ͨ
	m_pDlgInsureMain->OnMissionStart();
	m_pDlgInsureMain->PerformTransferScore(((CButton *)GetDlgItem(IDC_BY_NAME))->GetCheck(),strNickName,lTransferScore,szInsurePass);

	//���ý���
	m_PasswordControl.SetFocus();
	m_PasswordControl.SetUserPassword(TEXT(""));

	return;
}

//�滭����
BOOL CDlgInsureTransfer::OnEraseBkgnd(CDC * pDC)
{
	//��ȡλ��
	CRect rcClient;
	GetClientRect(&rcClient);

	//��������
	CImage ImageBuffer;
	ImageBuffer.Create(rcClient.Width(),rcClient.Height(),32);

	//���� DC
	CImageDC BufferDC(ImageBuffer);
	CDC * pDCBuffer=CDC::FromHandle(BufferDC);

	//���û���
	pDCBuffer->SetBkMode(TRANSPARENT);
	pDCBuffer->SelectObject(CSkinResourceManager::GetInstance()->GetDefaultFont());

	//�滭����
	pDCBuffer->FillSolidRect(&rcClient,CSkinDialog::m_SkinAttribute.m_crBackGround);

	//��ȡλ��
	CRect rcScore;
	CRect rcNickName;
	m_edScore.GetWindowRect(&rcScore);
	m_edNickName.GetWindowRect(&rcNickName);

	//ת��λ��
	ScreenToClient(&rcScore);
	ScreenToClient(&rcNickName);

	//�滭����
	pDCBuffer->FillSolidRect(rcScore.left-6,rcScore.top-5,rcScore.Width()+12,24L,CSkinEdit::m_SkinAttribute.m_crEnableBK);
	pDCBuffer->FillSolidRect(rcNickName.left-6,rcNickName.top-5,rcNickName.Width()+12,24L,CSkinEdit::m_SkinAttribute.m_crEnableBK);

	//�滭����
	COLORREF crColorBorad=CSkinEdit::m_SkinAttribute.m_crEnableBorad;
	pDCBuffer->Draw3dRect(rcScore.left-6,rcScore.top-5,rcScore.Width()+12,24L,crColorBorad,crColorBorad);
	pDCBuffer->Draw3dRect(rcNickName.left-6,rcNickName.top-5,rcNickName.Width()+12,24L,crColorBorad,crColorBorad);

	//�滭����
	pDC->BitBlt(0,0,rcClient.Width(),rcClient.Height(),pDCBuffer,0,0,SRCCOPY);

	return TRUE;
}

//�ؼ���ɫ
HBRUSH CDlgInsureTransfer::OnCtlColor(CDC * pDC, CWnd * pWnd, UINT nCtlColor)
{
	switch (nCtlColor)
	{
	case CTLCOLOR_DLG:
	case CTLCOLOR_BTN:
	case CTLCOLOR_STATIC:
		{
			pDC->SetBkMode(TRANSPARENT);
			pDC->SetTextColor(CSkinDialog::m_SkinAttribute.m_crControlText);
			return CSkinDialog::m_SkinAttribute.m_brBackGround;
		}
	}

	return __super::OnCtlColor(pDC,pWnd,nCtlColor);
}

void CDlgInsureTransfer::OnBnClickedById()
{
	// TODO: Add your control notification handler code here
	GetDlgItem(IDC_TRANSFER_TYPE_TIP)->SetWindowText(TEXT("������� I D��"));
	m_edNickName.SetFocus();
	m_edNickName.SetWindowText(TEXT(""));
}

void CDlgInsureTransfer::OnBnClickedByName()
{
	// TODO: Add your control notification handler code here
	GetDlgItem(IDC_TRANSFER_TYPE_TIP)->SetWindowText(TEXT("��������ǳƣ�"));
	m_edNickName.SetFocus();
	m_edNickName.SetWindowText(TEXT(""));
}
//////////////////////////////////////////////////////////////////////////////////

//���캯��
CDlgInsureMain::CDlgInsureMain() : CSkinDialog(IDD_INSURE_MAIN)
{
	//�������
	m_bSaveMission=false;
	m_bTakeMission=false;
	m_bQueryMission=false;

	//���ñ���
	m_bInitInfo=false;
	m_cbInsureMode=INSURE_SAVE;
	ZeroMemory(&m_UserInsureInfo,sizeof(m_UserInsureInfo));

	return;
}

//��������
CDlgInsureMain::~CDlgInsureMain()
{
}

//�ؼ���
VOID CDlgInsureMain::DoDataExchange(CDataExchange * pDX)
{
	__super::DoDataExchange(pDX);

	//�ؼ�����
	DDX_Control(pDX, IDC_TAB_CONTROL, m_TabControl);
	DDX_Control(pDX, IDC_BT_QUERY_INFO, m_btQueryInfo);
}

//��Ϣ����
BOOL CDlgInsureMain::PreTranslateMessage(MSG * pMsg)
{
	//��������
	if ((pMsg->message==WM_KEYDOWN)&&(pMsg->wParam==VK_ESCAPE))
	{
		return TRUE;
	}

	return __super::PreTranslateMessage(pMsg);
}

//��������
BOOL CDlgInsureMain::OnInitDialog()
{
	__super::OnInitDialog();

	//���ñ���
	SetWindowText(TEXT("���չ�"));

	//������Դ
	AfxSetResourceHandle(GetModuleHandle(NULL));

	//���ÿؼ�
	m_TabControl.SetItemSize(CSize(100,25));

	//��ȡ�ؼ�
	m_DlgInsureSave.m_pDlgInsureMain=this;
	m_DlgInsureSave.m_pUserInsureInfo=&m_UserInsureInfo;

	//ת�˿ؼ�
	m_DlgInsureTransfer.m_pDlgInsureMain=this;
	m_DlgInsureTransfer.m_pUserInsureInfo=&m_UserInsureInfo;

	//�����ǩ
	m_TabControl.InsertItem(INSURE_SAVE,TEXT(" �����ȡ�� "));
	m_TabControl.InsertItem(INSURE_TRANSFER,TEXT(" ������Ϸ�� "));

	//���ð�ť
	HINSTANCE hResInstance=GetModuleHandle(SHARE_CONTROL_DLL_NAME);
	m_btQueryInfo.SetButtonImage(IDB_BT_QUERY_INFO,hResInstance,false,false);

	//��ѯ��Ϣ
	QueryUserInsureInfo();

	//��ȡģʽ
	SwitchInsureModeView(INSURE_SAVE);

	return FALSE;
}

//ȷ����ť
VOID CDlgInsureMain::OnOK()
{
	//Ĭ�϶���
	switch (m_cbInsureMode)
	{
	case INSURE_SAVE:		//��ȡ��ʽ
		{
			m_DlgInsureSave.OnOK();
			break;
		}
	case INSURE_TRANSFER:	//ת�˷�ʽ
		{
			m_DlgInsureTransfer.OnOK();
			break;
		}
	}

	return;
}

//�滭��Ϣ
VOID CDlgInsureMain::OnDrawClientArea(CDC * pDC, INT nWidth, INT nHeight)
{
	//��ȡλ��
	CRect rcTabControl;
	m_TabControl.GetWindowRect(&rcTabControl);

	//ת��λ��
	ScreenToClient(&rcTabControl);

	//�滭����
	INT nLBorder=m_SkinAttribute.m_EncircleInfoView.nLBorder;
	INT nRBorder=m_SkinAttribute.m_EncircleInfoView.nRBorder;
	pDC->FillSolidRect(nLBorder,rcTabControl.bottom-1L,nWidth-nLBorder-nRBorder,1,RGB(145,168,183));

	//������Դ
	CPngImage ImageInsureInfo;
	ImageInsureInfo.LoadImage(GetModuleHandle(SHARE_CONTROL_DLL_NAME),TEXT("INFO_FRAME"));

	//�滭��Ϣ
	INT nYPosInfo=75L;
	INT nXPosInfo=(nWidth-ImageInsureInfo.GetWidth())/2L;
	ImageInsureInfo.DrawImage(pDC,nXPosInfo,nYPosInfo,ImageInsureInfo.GetWidth(),ImageInsureInfo.GetHeight(),0,0);

	//������Ϣ
	if (m_bInitInfo==true)
	{
		//������Դ
		CPngImage ImageInsureIcon;
		ImageInsureIcon.LoadImage(GetModuleHandle(SHARE_CONTROL_DLL_NAME),TEXT("INSURE_ICON"));

		//�滭��־
		ImageInsureIcon.DrawImage(pDC,nXPosInfo+10,nYPosInfo+17);

		//�滭����
		m_DlgInsureItem.DrawNumberString(pDC,m_UserInsureInfo.lUserScore,nXPosInfo+136,nYPosInfo+18L);
		m_DlgInsureItem.DrawNumberString(pDC,m_UserInsureInfo.lUserInsure,nXPosInfo+136,nYPosInfo+53L);

		//�滭��ʾ
		LPCTSTR pszScoreString=TEXT("��Ϸ�ң�");
		LPCTSTR pszInsureString=TEXT("���չ�");
		pDC->SetTextColor(RGB(50,50,50));
		pDC->TextOut(nXPosInfo+83,nYPosInfo+20L,pszScoreString,lstrlen(pszScoreString));
		pDC->TextOut(nXPosInfo+83,nYPosInfo+55L,pszInsureString,lstrlen(pszInsureString));

		//������ʾ
		TCHAR szString[128]=TEXT("");
		_sntprintf(szString,CountArray(szString),TEXT("��ܰ��ʾ��������Ϸ���������ѣ�ȡ�����۳�%ld��,���ͽ��۳�%ld���������"),m_UserInsureInfo.wRevenueTake,m_UserInsureInfo.wRevenueTransfer);

		//��ܰ��ʾ
		pDC->SetTextColor(RGB(50,50,50));
		pDC->TextOut(18,nHeight-28,szString,lstrlen(szString));
	}
	else
	{
	}

	return;
}

//��ʼ����
VOID CDlgInsureMain::OnMissionStart()
{
	return;
}

//��ֹ����
VOID CDlgInsureMain::OnMissionConclude()
{
	return;
}

//��ѯ����
VOID CDlgInsureMain::QueryUserInsureInfo()
{
	//���ñ���
	m_bSaveMission=false;
	m_bTakeMission=false;
	m_bQueryMission=true;
	m_bTransferMission=false;

	//�¼�����
	OnMissionStart();

	//ִ�в�ѯ
	PerformQueryInfo();

	return;
}

//����ģʽ
VOID CDlgInsureMain::SwitchInsureModeView(BYTE cbInsureMode)
{
	switch (cbInsureMode)
	{
	case INSURE_SAVE:			//��ȡ��ʽ
		{
			//���ñ���
			m_cbInsureMode=INSURE_SAVE;

			//���ÿؼ�
			if (m_DlgInsureSave.m_hWnd==NULL)
			{
				//��ȡλ��
				CRect rcClient;
				GetClientRect(&rcClient);

				//������Դ
				AfxSetResourceHandle(GetModuleHandle(SHARE_CONTROL_DLL_NAME));

				//�����ؼ�
				m_DlgInsureSave.Create(IDD_INSURE_SAVE,this);

				//������Դ
				AfxSetResourceHandle(GetModuleHandle(NULL));

				//�ƶ�λ��
				INT nLBorder=m_SkinAttribute.m_EncircleInfoFrame.nLBorder;
				INT nRBorder=m_SkinAttribute.m_EncircleInfoFrame.nRBorder;
				INT nTBorder=m_SkinAttribute.m_EncircleInfoFrame.nTBorder;
				INT nBBorder=m_SkinAttribute.m_EncircleInfoFrame.nBBorder;
				m_DlgInsureSave.SetWindowPos(NULL,nLBorder,nTBorder+130,rcClient.Width()-nLBorder-nRBorder,rcClient.Height()-nBBorder-nTBorder-130,SWP_NOZORDER|SWP_SHOWWINDOW);
			}
			else
			{
				//��ʾ����
				m_DlgInsureSave.ShowWindow(SW_SHOW);
			}

			//���ÿؼ�
			if (m_DlgInsureTransfer.m_hWnd!=NULL) m_DlgInsureTransfer.ShowWindow(SW_HIDE);

			//���ý���
			m_DlgInsureSave.SetFocus();

			//����ѡ��
			m_TabControl.SetCurSel(m_cbInsureMode);

			break;
		}
	case INSURE_TRANSFER:		//ת�˷�ʽ
		{
			//���ñ���
			m_cbInsureMode=INSURE_TRANSFER;

			//���ÿؼ�
			if (m_DlgInsureTransfer.m_hWnd==NULL)
			{
				//��ȡλ��
				CRect rcClient;
				GetClientRect(&rcClient);

				//������Դ
				AfxSetResourceHandle(GetModuleHandle(SHARE_CONTROL_DLL_NAME));

				//�����ؼ�
				m_DlgInsureTransfer.Create(IDD_INSURE_TRANSFER,this);

				//������Դ
				AfxSetResourceHandle(GetModuleHandle(NULL));

				//�ƶ�λ��
				INT nLBorder=m_SkinAttribute.m_EncircleInfoFrame.nLBorder;
				INT nRBorder=m_SkinAttribute.m_EncircleInfoFrame.nRBorder;
				INT nTBorder=m_SkinAttribute.m_EncircleInfoFrame.nTBorder;
				INT nBBorder=m_SkinAttribute.m_EncircleInfoFrame.nBBorder;
				m_DlgInsureTransfer.SetWindowPos(NULL,nLBorder,nTBorder+130,rcClient.Width()-nLBorder-nRBorder,rcClient.Height()-nBBorder-nTBorder-130,SWP_NOZORDER|SWP_SHOWWINDOW);
			}
			else
			{
				//��ʾ����
				m_DlgInsureTransfer.ShowWindow(SW_SHOW);
			}

			//���ÿؼ�
			if (m_DlgInsureSave.m_hWnd!=NULL) m_DlgInsureSave.ShowWindow(SW_HIDE);

			//���ý���
			m_DlgInsureTransfer.SetFocus();

			//����ѡ��
			m_TabControl.SetCurSel(m_cbInsureMode);

			break;
		}
	default:
		{
			ASSERT(FALSE);
		}
	}

	return;
}

//��ѯ��ť
VOID CDlgInsureMain::OnBnClickedQueryInfo()
{
	//��ѯ��Ϣ
	QueryUserInsureInfo();

	//���ý���
	switch (m_cbInsureMode)
	{
	case INSURE_SAVE:		//��ȡ��ʽ
		{
			m_DlgInsureSave.SetFocus();
			break;
		}
	case INSURE_TRANSFER:	//ת�˷�ʽ
		{
			m_DlgInsureTransfer.SetFocus();
			break;
		}
	}

	return;
}

//���͸ı�
VOID CDlgInsureMain::OnTcnSelchangeInsureMode(NMHDR * pNMHDR, LRESULT * pResult)
{
	switch (m_TabControl.GetCurSel())
	{
	case INSURE_SAVE:		//��ȡ��ʽ
		{
			SwitchInsureModeView(INSURE_SAVE);
			break;
		}
	case INSURE_TRANSFER:	//ת�˷�ʽ
		{
			SwitchInsureModeView(INSURE_TRANSFER);
			break;
		}
	default:
		{
			ASSERT(FALSE);
		}
	}

	return;
}

//////////////////////////////////////////////////////////////////////////////////

//���캯��
CDlgInsurePlaza::CDlgInsurePlaza()
{
	//��������
	m_MissionManager.InsertMissionItem(this);

	//���ñ���
	m_lScore=0L;
	ZeroMemory(m_szNickName,sizeof(m_szNickName));
	ZeroMemory(m_szInsurePass,sizeof(m_szInsurePass));

	return;
}

//��������
CDlgInsurePlaza::~CDlgInsurePlaza()
{
}

//��ѯ�¼�
VOID CDlgInsurePlaza::PerformQueryInfo()
{
	//��������
	if (m_MissionManager.AvtiveMissionItem(this,false)==false)  
	{
		OnMissionConclude();
		return;
	}

	return;
}

//�����¼�
VOID CDlgInsurePlaza::PerformSaveScore(SCORE lSaveScore)
{
	//���ñ���
	m_bSaveMission=true;
	m_bTakeMission=false;
	m_bQueryMission=false;
	m_bTransferMission=false;

	//���ñ���
	m_lScore=lSaveScore;

	//��������
	if (m_MissionManager.AvtiveMissionItem(this,false)==false)  
	{
		OnMissionConclude();
		return;
	}

	return;
}

//ȡ���¼�
VOID CDlgInsurePlaza::PerformTakeScore(SCORE lTakeScore, LPCTSTR pszInsurePass)
{
	//���ñ���
	m_bTakeMission=true;
	m_bSaveMission=false;
	m_bQueryMission=false;
	m_bTransferMission=false;

	//���ñ���
	m_lScore=lTakeScore;
	lstrcpyn(m_szInsurePass,pszInsurePass,CountArray(m_szInsurePass));

	//��������
	if (m_MissionManager.AvtiveMissionItem(this,false)==false)  
	{
		OnMissionConclude();
		return;
	}

	return;
}

//ת���¼�
VOID CDlgInsurePlaza::PerformTransferScore(BYTE cbByNickName, LPCTSTR pszNickName, SCORE lTransferScore, LPCTSTR pszInsurePass)
{
	//���ñ���
	m_bSaveMission=false;
	m_bTakeMission=false;
	m_bQueryMission=false;
	m_bTransferMission=true;

	//���ñ���
	m_cbByNickName=cbByNickName;
	m_lScore=lTransferScore;
	lstrcpyn(m_szNickName,pszNickName,CountArray(m_szNickName));
	lstrcpyn(m_szInsurePass,pszInsurePass,CountArray(m_szInsurePass));

	//��������
	if (m_MissionManager.AvtiveMissionItem(this,false)==false)  
	{
		OnMissionConclude();
		return;
	}

	return;
}

//�����¼�
bool CDlgInsurePlaza::OnEventMissionLink(INT nErrorCode)
{
	//���ӽ��
	if (nErrorCode!=0)
	{
		//��������
		if (m_MissionManager.AvtiveMissionItem(this,true)==true)
		{
			return true;
		}

		//�¼�����
		OnMissionConclude();

		//������ʾ
		if (m_bSaveMission==true)
		{
			//��ʾ��Ϣ
			CInformation Information(this);
			Information.ShowMessageBox(TEXT("���ӷ�������ʱ����Ϸ�Ҵ���ʧ�ܣ����Ժ��ٴ����ԣ�"),MB_OK|MB_ICONSTOP,30);
		}

		//������ʾ
		if (m_bTakeMission==true)
		{
			//��ʾ��Ϣ
			CInformation Information(this);
			Information.ShowMessageBox(TEXT("���ӷ�������ʱ����Ϸ��ȡ��ʧ�ܣ����Ժ��ٴ����ԣ�"),MB_OK|MB_ICONSTOP,30);
		}

		//������ʾ
		if (m_bQueryMission==true)
		{
			//��ʾ��Ϣ
			CInformation Information(this);
			Information.ShowMessageBox(TEXT("���ӷ�������ʱ�����չ����ϻ�ȡʧ�ܣ�"),MB_OK|MB_ICONSTOP,30);
		}

		//������ʾ
		if (m_bTransferMission==true)
		{
			//��ʾ��Ϣ
			CInformation Information(this);
			Information.ShowMessageBox(TEXT("���ӷ�������ʱ����Ϸ������ʧ�ܣ����Ժ��ٴ����ԣ�"),MB_OK|MB_ICONSTOP,30);
		}

		return true;
	}

	//��������
	if (m_bSaveMission==true)
	{
		//��������
		CMD_GP_UserSaveScore UserSaveScore;
		ZeroMemory(&UserSaveScore,sizeof(UserSaveScore));

		//��������
		CGlobalUserInfo * pGlobalUserInfo=CGlobalUserInfo::GetInstance();
		tagGlobalUserData * pGlobalUserData=pGlobalUserInfo->GetGlobalUserData();

		//���ñ���
		UserSaveScore.lSaveScore=m_lScore;
		UserSaveScore.dwUserID=pGlobalUserData->dwUserID;
		CWHService::GetMachineIDEx(UserSaveScore.szMachineID);

		//��������
		m_MissionManager.SendData(MDM_GP_USER_SERVICE,SUB_GP_USER_SAVE_SCORE,&UserSaveScore,sizeof(UserSaveScore));

		return true;
	}

	//ȡ������
	if (m_bTakeMission==true)
	{
		//��������
		CMD_GP_UserTakeScore UserTakeScore;
		ZeroMemory(&UserTakeScore,sizeof(UserTakeScore));

		//��������
		CGlobalUserInfo * pGlobalUserInfo=CGlobalUserInfo::GetInstance();
		tagGlobalUserData * pGlobalUserData=pGlobalUserInfo->GetGlobalUserData();

		//���ñ���
		UserTakeScore.lTakeScore=m_lScore;
		UserTakeScore.dwUserID=pGlobalUserData->dwUserID;
		CWHService::GetMachineIDEx(UserTakeScore.szMachineID);
		lstrcpyn(UserTakeScore.szPassword,m_szInsurePass,CountArray(UserTakeScore.szPassword));

		//��������
		m_MissionManager.SendData(MDM_GP_USER_SERVICE,SUB_GP_USER_TAKE_SCORE,&UserTakeScore,sizeof(UserTakeScore));

		return true;
	}

	//ת������
	if (m_bTransferMission==true)
	{
		//��������
		CMD_GP_QueryUserInfoRequest QueryUserInfoRequest;
		ZeroMemory(&QueryUserInfoRequest,sizeof(QueryUserInfoRequest));

		//���ñ���
		QueryUserInfoRequest.cbByNickName=m_cbByNickName;
		lstrcpyn(QueryUserInfoRequest.szNickName,m_szNickName,CountArray(QueryUserInfoRequest.szNickName));

		//��������
		m_MissionManager.SendData(MDM_GP_USER_SERVICE,SUB_GP_QUERY_USER_INFO_REQUEST,&QueryUserInfoRequest,sizeof(QueryUserInfoRequest));
	}

	//��ѯ����
	if (m_bQueryMission==true)
	{
		//��������
		CMD_GP_QueryInsureInfo QueryInsureInfo;
		ZeroMemory(&QueryInsureInfo,sizeof(QueryInsureInfo));

		//���ñ���
		CGlobalUserInfo * pGlobalUserInfo=CGlobalUserInfo::GetInstance();
		QueryInsureInfo.dwUserID=pGlobalUserInfo->GetGlobalUserData()->dwUserID;

		//��������
		m_MissionManager.SendData(MDM_GP_USER_SERVICE,SUB_GP_QUERY_INSURE_INFO,&QueryInsureInfo,sizeof(QueryInsureInfo));
	}

	return true;
}

//�ر��¼�
bool CDlgInsurePlaza::OnEventMissionShut(BYTE cbShutReason)
{
	//��ʾ��Ϣ
	if (cbShutReason!=SHUT_REASON_NORMAL)
	{
		//��������
		if (m_MissionManager.AvtiveMissionItem(this,true)==true)
		{
			return true;
		}

		//��������
		if (m_bSaveMission==true)
		{
			//��ʾ��Ϣ
			CInformation Information(this);
			Information.ShowMessageBox(TEXT("��������������쳣�Ͽ��ˣ���Ϸ�Ҵ���ʧ�ܣ�"),MB_ICONERROR,30);
		}

		//ȡ������
		if (m_bTakeMission==true)
		{
			//��ʾ��Ϣ
			CInformation Information(this);
			Information.ShowMessageBox(TEXT("��������������쳣�Ͽ��ˣ���Ϸ��ȡ��ʧ�ܣ�"),MB_ICONERROR,30);
		}

		//��ѯ����
		if (m_bQueryMission==true)
		{
			//��ʾ��Ϣ
			CInformation Information(this);
			Information.ShowMessageBox(TEXT("��������������쳣�Ͽ��ˣ����չ����ϻ�ȡʧ�ܣ�"),MB_ICONERROR,30);
		}
	}

	//�¼�����
	OnMissionConclude();

	return true;
}

//��ȡ�¼�
bool CDlgInsurePlaza::OnEventMissionRead(TCP_Command Command, VOID * pData, WORD wDataSize)
{
	//�����
	if (Command.wMainCmdID==MDM_GP_USER_SERVICE)
	{
		switch (Command.wSubCmdID)
		{
		case SUB_GP_USER_INSURE_INFO:		//��������
			{
				//Ч�����
				ASSERT(wDataSize==sizeof(CMD_GP_UserInsureInfo));
				if (wDataSize<sizeof(CMD_GP_UserInsureInfo)) return false;

				//��������
				CMD_GP_UserInsureInfo * pUserInsureInfo=(CMD_GP_UserInsureInfo *)pData;

				//���ñ���
				m_bInitInfo=true;
				m_UserInsureInfo.wRevenueTake=pUserInsureInfo->wRevenueTake;
				m_UserInsureInfo.wRevenueTransfer=pUserInsureInfo->wRevenueTransfer;
				m_UserInsureInfo.wServerID=pUserInsureInfo->wServerID;
				m_UserInsureInfo.lUserScore=pUserInsureInfo->lUserScore;
				m_UserInsureInfo.lUserInsure=pUserInsureInfo->lUserInsure;
				m_UserInsureInfo.lTransferPrerequisite=pUserInsureInfo->lTransferPrerequisite;

				//�ر�����
				m_MissionManager.ConcludeMissionItem(this,false);

				//���´���
				tagInsurePlazaUpdata InsureUpdata;
				InsureUpdata.lUserScore=pUserInsureInfo->lUserScore;
				InsureUpdata.lUserInsure=pUserInsureInfo->lUserInsure;
				AfxGetMainWnd()->SendMessage(WM_INSUREPLAZA_UPDATA,(WPARAM)&InsureUpdata,0);

				//���½���
				RedrawWindow(NULL,NULL,RDW_INVALIDATE|RDW_UPDATENOW|RDW_ERASE|RDW_ERASENOW);

				return true;
			}
		case SUB_GP_USER_INSURE_SUCCESS:	//���гɹ�
			{
				//Ч�����
				CMD_GP_UserInsureSuccess * pUserInsureSuccess=(CMD_GP_UserInsureSuccess *)pData;
				ASSERT(wDataSize>=(sizeof(CMD_GP_UserInsureSuccess)-sizeof(pUserInsureSuccess->szDescribeString)));
				if (wDataSize<(sizeof(CMD_GP_UserInsureSuccess)-sizeof(pUserInsureSuccess->szDescribeString))) return false;

				//���ñ���
				m_UserInsureInfo.lUserScore=pUserInsureSuccess->lUserScore;
				m_UserInsureInfo.lUserInsure=pUserInsureSuccess->lUserInsure;

				//�ر�����
				m_MissionManager.ConcludeMissionItem(this,false);

				//����ؼ�
				if(m_DlgInsureSave.m_PasswordControl.m_hWnd != NULL)
				{
					m_DlgInsureSave.m_PasswordControl.SetFocus();
					m_DlgInsureSave.m_PasswordControl.SetUserPassword(TEXT(""));
				}
				if(m_DlgInsureTransfer.m_PasswordControl.m_hWnd != NULL)
				{
					m_DlgInsureTransfer.m_PasswordControl.SetFocus();
					m_DlgInsureTransfer.m_PasswordControl.SetUserPassword(TEXT(""));
				}

				//���´���
				tagInsurePlazaUpdata InsureUpdata;
				InsureUpdata.lUserScore=pUserInsureSuccess->lUserScore;
				InsureUpdata.lUserInsure=pUserInsureSuccess->lUserInsure;
				AfxGetMainWnd()->SendMessage(WM_INSUREPLAZA_UPDATA,(WPARAM)&InsureUpdata,0);

				//���½���
				RedrawWindow(NULL,NULL,RDW_INVALIDATE|RDW_UPDATENOW|RDW_ERASE|RDW_ERASENOW);

				//��ʾ��Ϣ
				if (pUserInsureSuccess->szDescribeString[0]!=0)
				{
					CInformation Information(this);
					Information.ShowMessageBox(pUserInsureSuccess->szDescribeString,MB_ICONINFORMATION,60);
				}

				return true;
			}
		case SUB_GP_USER_INSURE_FAILURE:	//����ʧ��
			{
				//Ч�����
				CMD_GP_UserInsureFailure * pUserInsureFailure=(CMD_GP_UserInsureFailure *)pData;
				ASSERT(wDataSize>=(sizeof(CMD_GP_UserInsureFailure)-sizeof(pUserInsureFailure->szDescribeString)));
				if (wDataSize<(sizeof(CMD_GP_UserInsureFailure)-sizeof(pUserInsureFailure->szDescribeString))) return false;

				//ʧ�ܴ���
				OnMissionConclude();

				//�ر�����
				m_MissionManager.ConcludeMissionItem(this,false);

				//����ؼ�
				if(m_DlgInsureSave.m_PasswordControl.m_hWnd != NULL)
				{
					m_DlgInsureSave.m_PasswordControl.SetFocus();
					m_DlgInsureSave.m_PasswordControl.SetUserPassword(TEXT(""));
				}
				if(m_DlgInsureTransfer.m_PasswordControl.m_hWnd != NULL)
				{
					m_DlgInsureTransfer.m_PasswordControl.SetFocus();
					m_DlgInsureTransfer.m_PasswordControl.SetUserPassword(TEXT(""));
				}

				//��ʾ��Ϣ
				if (pUserInsureFailure->szDescribeString[0]!=0)
				{
					CInformation Information(this);
					Information.ShowMessageBox(pUserInsureFailure->szDescribeString,MB_ICONERROR,60);
				}

				return true;
			}
		case SUB_GP_QUERY_USER_INFO_RESULT:	//�û���Ϣ
			{
				//Ч�����
				ASSERT(wDataSize==sizeof(CMD_GP_UserTransferUserInfo));
				if (wDataSize<sizeof(CMD_GP_UserTransferUserInfo)) return false;

				//��������
				CMD_GP_UserTransferUserInfo * pTransferUserInfo=(CMD_GP_UserTransferUserInfo *)pData;

				//������Ϣ
				TCHAR szMessage[128]={0};
				_sntprintf(szMessage, CountArray(szMessage), TEXT("��ȷ��Ҫ��[%s], ID:%d ����%I64d ��Ϸ����?"), pTransferUserInfo->szNickName, pTransferUserInfo->dwTargetGameID, m_lScore);

				//��ʾ��Ϣ
				CInformation Information(this);
				if (Information.ShowMessageBox(szMessage,MB_ICONQUESTION|MB_YESNO,0)==IDYES)
				{
					//��������
					CMD_GP_UserTransferScore UserTransferScore;
					ZeroMemory(&UserTransferScore,sizeof(UserTransferScore));

					//��������
					CGlobalUserInfo * pGlobalUserInfo=CGlobalUserInfo::GetInstance();
					tagGlobalUserData * pGlobalUserData=pGlobalUserInfo->GetGlobalUserData();

					//���ñ���
					UserTransferScore.cbByNickName=m_cbByNickName;
					UserTransferScore.lTransferScore=m_lScore;
					UserTransferScore.dwUserID=pGlobalUserData->dwUserID;
					CWHService::GetMachineIDEx(UserTransferScore.szMachineID);
					lstrcpyn(UserTransferScore.szNickName,m_szNickName,CountArray(UserTransferScore.szNickName));
					lstrcpyn(UserTransferScore.szPassword,m_szInsurePass,CountArray(UserTransferScore.szPassword));

					//��������
					m_MissionManager.SendData(MDM_GP_USER_SERVICE,SUB_GP_USER_TRANSFER_SCORE,&UserTransferScore,sizeof(UserTransferScore));
				}

				return true;
			}
		}
	}

	return true;
}

//////////////////////////////////////////////////////////////////////////////////

//���캯��
CDlgInsureServer::CDlgInsureServer()
{
	//���ñ���
	m_pITCPSocket=NULL;
	m_pIMySelfUserItem=NULL;

	return;
}

//��������
CDlgInsureServer::~CDlgInsureServer()
{
}

//��ѯ�¼�
VOID CDlgInsureServer::PerformQueryInfo()
{
	//Ч�����
	ASSERT(m_pITCPSocket!=NULL);
	if (m_pITCPSocket==NULL) return;

	//��������
	CMD_GR_C_QueryInsureInfoRequest QueryInsureInfo;
	QueryInsureInfo.cbActivityGame=FALSE;

	//��������
	m_pITCPSocket->SendData(MDM_GR_INSURE,SUB_GR_QUERY_INSURE_INFO,&QueryInsureInfo,sizeof(QueryInsureInfo));

	return;
}

//�����¼�
VOID CDlgInsureServer::PerformSaveScore(SCORE lSaveScore)
{
	//Ч�����
	ASSERT(m_pITCPSocket!=NULL);
	if (m_pITCPSocket==NULL) return;

	//��������
	CMD_GR_C_SaveScoreRequest SaveScoreRequest;
	ZeroMemory(&SaveScoreRequest,sizeof(SaveScoreRequest));

	//���ñ���
	SaveScoreRequest.lSaveScore=lSaveScore;

	//��������
	m_pITCPSocket->SendData(MDM_GR_INSURE,SUB_GR_SAVE_SCORE_REQUEST,&SaveScoreRequest,sizeof(SaveScoreRequest));

	return;
}

//ȡ���¼�
VOID CDlgInsureServer::PerformTakeScore(SCORE lTakeScore, LPCTSTR pszInsurePass)
{
	//Ч�����
	ASSERT(m_pITCPSocket!=NULL);
	if (m_pITCPSocket==NULL) return;

	//��������
	CMD_GR_C_TakeScoreRequest TakeScoreRequest;
	ZeroMemory(&TakeScoreRequest,sizeof(TakeScoreRequest));

	//���ñ���
	TakeScoreRequest.lTakeScore=lTakeScore;
	lstrcpyn(TakeScoreRequest.szInsurePass,pszInsurePass,CountArray(TakeScoreRequest.szInsurePass));

	//��������
	m_pITCPSocket->SendData(MDM_GR_INSURE,SUB_GR_TAKE_SCORE_REQUEST,&TakeScoreRequest,sizeof(TakeScoreRequest));

	return;
}

//ת���¼�
VOID CDlgInsureServer::PerformTransferScore(BYTE cbByNickName, LPCTSTR pszNickName, SCORE lTransferScore, LPCTSTR pszInsurePass)
{
	//Ч�����
	ASSERT(m_pITCPSocket!=NULL);
	if (m_pITCPSocket==NULL) return;

	//���ñ���
	m_cbByNickName=cbByNickName;
	m_lScore=lTransferScore;
	lstrcpyn(m_szNickName,pszNickName,CountArray(m_szNickName));
	lstrcpyn(m_szInsurePass,pszInsurePass,CountArray(m_szInsurePass));

	//��������
	CMD_GR_C_QueryUserInfoRequest QueryUserInfoRequest;
	ZeroMemory(&QueryUserInfoRequest,sizeof(QueryUserInfoRequest));

	//���ñ���
	QueryUserInfoRequest.cbByNickName=cbByNickName;
	lstrcpyn(QueryUserInfoRequest.szNickName,pszNickName,CountArray(QueryUserInfoRequest.szNickName));

	//��������
	m_pITCPSocket->SendData(MDM_GR_INSURE,SUB_GR_QUERY_USER_INFO_REQUEST,&QueryUserInfoRequest,sizeof(QueryUserInfoRequest));

	return;
}

//��������
VOID CDlgInsureServer::Initialization(ITCPSocket * pITCPSocket, IClientUserItem * pIMySelfUserItem)
{
	//���ñ���
	m_pITCPSocket=pITCPSocket;
	m_pIMySelfUserItem=pIMySelfUserItem;

	return;
}

//������Ϣ
bool CDlgInsureServer::OnServerInsureMessage(WORD wMainCmdID, WORD wSubCmdID, VOID * pData, WORD wDataSize)
{
	//��Ϣ�ж�
	if (wMainCmdID==MDM_GR_INSURE)
	{
		switch (wSubCmdID)
		{
		case SUB_GR_USER_INSURE_INFO:		//��������
			{
				//Ч�����
				ASSERT(wDataSize==sizeof(CMD_GR_S_UserInsureInfo));
				if (wDataSize<sizeof(CMD_GR_S_UserInsureInfo)) return false;

				//��������
				CMD_GR_S_UserInsureInfo * pUserInsureInfo=(CMD_GR_S_UserInsureInfo *)pData;

				//���ñ���
				m_bInitInfo=true;
				m_UserInsureInfo.wRevenueTake=pUserInsureInfo->wRevenueTake;
				m_UserInsureInfo.wRevenueTransfer=pUserInsureInfo->wRevenueTransfer;
				m_UserInsureInfo.wServerID=pUserInsureInfo->wServerID;
				m_UserInsureInfo.lUserScore=pUserInsureInfo->lUserScore;
				m_UserInsureInfo.lUserInsure=pUserInsureInfo->lUserInsure;
				m_UserInsureInfo.lTransferPrerequisite=pUserInsureInfo->lTransferPrerequisite;

				//���´���
				tagInsurePlazaUpdata InsureUpdata;
				InsureUpdata.lUserScore=pUserInsureInfo->lUserScore;
				InsureUpdata.lUserInsure=pUserInsureInfo->lUserInsure;
				AfxGetMainWnd()->SendMessage(WM_INSUREPLAZA_UPDATA,(WPARAM)&InsureUpdata,0);

				//���½���
				RedrawWindow(NULL,NULL,RDW_INVALIDATE|RDW_UPDATENOW|RDW_ERASE|RDW_ERASENOW);

				return true;
			}
		case SUB_GR_USER_INSURE_SUCCESS:	//���гɹ�
			{
				//Ч�����
				CMD_GR_S_UserInsureSuccess * pUserInsureSuccess=(CMD_GR_S_UserInsureSuccess *)pData;
				ASSERT(wDataSize>=(sizeof(CMD_GR_S_UserInsureSuccess)-sizeof(pUserInsureSuccess->szDescribeString)));
				if (wDataSize<(sizeof(CMD_GR_S_UserInsureSuccess)-sizeof(pUserInsureSuccess->szDescribeString))) return false;

				//���ñ���
				m_UserInsureInfo.lUserScore=pUserInsureSuccess->lUserScore;
				m_UserInsureInfo.lUserInsure=pUserInsureSuccess->lUserInsure;

				//����ؼ�
				if(m_DlgInsureSave.m_PasswordControl.m_hWnd != NULL)
				{
					m_DlgInsureSave.m_PasswordControl.SetFocus();
					m_DlgInsureSave.m_PasswordControl.SetUserPassword(TEXT(""));
				}
				if(m_DlgInsureTransfer.m_PasswordControl.m_hWnd != NULL)
				{
					m_DlgInsureTransfer.m_PasswordControl.SetFocus();
					m_DlgInsureTransfer.m_PasswordControl.SetUserPassword(TEXT(""));
				}

				//���´���
				tagInsurePlazaUpdata InsureUpdata;
				InsureUpdata.lUserScore=pUserInsureSuccess->lUserScore;
				InsureUpdata.lUserInsure=pUserInsureSuccess->lUserInsure;
				AfxGetMainWnd()->SendMessage(WM_INSUREPLAZA_UPDATA,(WPARAM)&InsureUpdata,0);

				//���½���
				RedrawWindow(NULL,NULL,RDW_INVALIDATE|RDW_UPDATENOW|RDW_ERASE|RDW_ERASENOW);

				//��ʾ��Ϣ
				if (pUserInsureSuccess->szDescribeString[0]!=0)
				{
					CInformation Information(this);
					Information.ShowMessageBox(pUserInsureSuccess->szDescribeString,MB_ICONINFORMATION,60);
				}

				return true;
			}
		case SUB_GR_USER_INSURE_FAILURE:	//����ʧ��
			{
				//Ч�����
				CMD_GR_S_UserInsureFailure * pUserInsureFailure=(CMD_GR_S_UserInsureFailure *)pData;
				ASSERT(wDataSize>=(sizeof(CMD_GP_UserInsureFailure)-sizeof(pUserInsureFailure->szDescribeString)));
				if (wDataSize<(sizeof(CMD_GP_UserInsureFailure)-sizeof(pUserInsureFailure->szDescribeString))) return false;

				//ʧ�ܴ���
				OnMissionConclude();

				//����ؼ�
				if (m_bInitInfo==true)
				{
					if(m_DlgInsureSave.m_PasswordControl.m_hWnd != NULL)
					{
						m_DlgInsureSave.m_PasswordControl.SetFocus();
						m_DlgInsureSave.m_PasswordControl.SetUserPassword(TEXT(""));
					}
					if(m_DlgInsureTransfer.m_PasswordControl.m_hWnd != NULL)
					{
						m_DlgInsureTransfer.m_PasswordControl.SetFocus();
						m_DlgInsureTransfer.m_PasswordControl.SetUserPassword(TEXT(""));
					}
				}

				//��ʾ��Ϣ
				if (pUserInsureFailure->szDescribeString[0]!=0)
				{
					CInformation Information(this);
					Information.ShowMessageBox(pUserInsureFailure->szDescribeString,MB_ICONERROR,60);
				}

				return true;
			}
		case SUB_GR_USER_TRANSFER_USER_INFO:  //�û���Ϣ
			{
				//Ч�����
				ASSERT(wDataSize==sizeof(CMD_GR_S_UserTransferUserInfo));
				if (wDataSize<sizeof(CMD_GR_S_UserTransferUserInfo)) return false;

				//��������
				CMD_GR_S_UserTransferUserInfo * pTransferUserInfo=(CMD_GR_S_UserTransferUserInfo *)pData;

				//������Ϣ
				TCHAR szMessage[128]={0};
				_sntprintf(szMessage, CountArray(szMessage), TEXT("��ȷ��Ҫ��[%s], ID:%d ����%I64d ��Ϸ����?"), pTransferUserInfo->szNickName, pTransferUserInfo->dwTargetGameID, m_lScore);

				//��ʾ��Ϣ
				CInformation Information(this);
				if (Information.ShowMessageBox(szMessage,MB_ICONQUESTION|MB_YESNO,0)==IDYES)
				{
					//��������
					CMD_GP_C_TransferScoreRequest TransferScoreRequest;
					ZeroMemory(&TransferScoreRequest,sizeof(TransferScoreRequest));

					//���ñ���
					TransferScoreRequest.cbByNickName=m_cbByNickName;
					TransferScoreRequest.lTransferScore=m_lScore;
					lstrcpyn(TransferScoreRequest.szNickName,m_szNickName,CountArray(TransferScoreRequest.szNickName));
					lstrcpyn(TransferScoreRequest.szInsurePass,m_szInsurePass,CountArray(TransferScoreRequest.szInsurePass));

					//��������
					m_pITCPSocket->SendData(MDM_GR_INSURE,SUB_GR_TRANSFER_SCORE_REQUEST,&TransferScoreRequest,sizeof(TransferScoreRequest));
				}
				return true;
			}
		}
	}

	return true;
}

//////////////////////////////////////////////////////////////////////////////////

