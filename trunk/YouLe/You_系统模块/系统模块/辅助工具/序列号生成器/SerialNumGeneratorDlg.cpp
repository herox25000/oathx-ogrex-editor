// SerialNumGeneratorDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "SerialNumGenerator.h"
#include "SerialNumGeneratorDlg.h"
#include ".\serialnumgeneratordlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CSerialNumGeneratorDlg �Ի���



CSerialNumGeneratorDlg::CSerialNumGeneratorDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSerialNumGeneratorDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CSerialNumGeneratorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_xEdit);
}

BEGIN_MESSAGE_MAP(CSerialNumGeneratorDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
END_MESSAGE_MAP()


// CSerialNumGeneratorDlg ��Ϣ�������

BOOL CSerialNumGeneratorDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	
	return TRUE;  // ���������˿ؼ��Ľ��㣬���򷵻� TRUE
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CSerialNumGeneratorDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ��������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù����ʾ��
HCURSOR CSerialNumGeneratorDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

BOOL IsDigit(TCHAR ch)
{
	if(ch>=48 && ch<=57) return TRUE;
	return FALSE;
}

int CharToInt(TCHAR ch)
{
	return (ch-48);
}

void CSerialNumGeneratorDlg::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString strResult=_T("���к��������");
	CString strTemp=_T("");
	CString strText=_T("");

	TCHAR szText[256];
	memset(szText,0,sizeof(szText));
	m_xEdit.SendMessage(WM_GETTEXT,256,(LPARAM)szText);
	strText.Format(_T("%s"),szText);
	
	//m_xEdit.SendMessage(WM_GETTEXT,256,(LPARAM)strText.GetBuffer());
	//strText.ReleaseBuffer();

	if(strText.GetLength()<16)
	{
		m_xEdit.SendMessage(WM_SETTEXT,0,(LPARAM)strResult.GetBuffer());
		strResult.ReleaseBuffer();
		return;
	}

	strResult="";

	if(IsDigit(strText.GetAt(0)))
	{
		strTemp.Format(_T("%d"),CharToInt(strText.GetAt(0))*5);
		strResult+=strTemp;
	}
	else
	{
		strResult+=strText.GetAt(0);
		strResult+="F";
	}
	
	if(IsDigit(strText.GetAt(1)))
	{
		strTemp.Format(_T("%d"),CharToInt(strText.GetAt(1))*2);
		strResult+=strTemp;
	}
	else
	{
		strResult+="ku";
	}

	if(IsDigit(strText.GetAt(2)))
	{
		strTemp.Format(_T("%d"),CharToInt(strText.GetAt(2))*8);
		strResult+=strTemp;
	}
	else
	{
		strResult+="9K";
	}


	if(IsDigit(strText.GetAt(3)))
	{
		strTemp.Format(_T("%d"),CharToInt(strText.GetAt(3))*14);
		strResult+=strTemp;
	}
	else
	{
		strResult+="fFQ";
	}

	if(IsDigit(strText.GetAt(4)))
	{
		strTemp.Format(_T("%d"),CharToInt(strText.GetAt(4))*7);
		strResult+=strTemp;
	}
	else
	{
		strResult+="PUB";
	}

	if(IsDigit(strText.GetAt(5)))
	{
		strTemp.Format(_T("%d"),CharToInt(strText.GetAt(5))*8);
		strResult+=strTemp;
	}
	else
	{
		strResult+="H";
	}

	if(IsDigit(strText.GetAt(6)))
	{
		strTemp.Format(_T("%d"),CharToInt(strText.GetAt(6))+65);
		strResult+=strTemp;
	}
	else
	{
		strResult+="O";
	}

	if(IsDigit(strText.GetAt(7)))
	{
		strTemp.Format(_T("%d"),CharToInt(strText.GetAt(7))+75);
		strResult+=strTemp;
	}
	else
	{
		strResult+="W";
	}


	if(IsDigit(strText.GetAt(8)))
	{
		strTemp.Format(_T("%d"),CharToInt(strText.GetAt(8))*4);
		strResult+=strTemp;
	}
	else
	{
		strResult+="b";
	}


	if(IsDigit(strText.GetAt(9)))
	{
		strTemp.Format(_T("%d"),CharToInt(strText.GetAt(9))*3);
		strResult+=strTemp;
	}
	else
	{
		strResult+="V";
	}


	if(IsDigit(strText.GetAt(10)))
	{
		strTemp.Format(_T("%d"),CharToInt(strText.GetAt(10))*2);
		strResult+=strTemp;
	}
	else
	{
		strResult+="G";
	}


	if(IsDigit(strText.GetAt(11)))
	{
		strTemp.Format(_T("%d"),CharToInt(strText.GetAt(11))*1);
		strResult+=strTemp;
	}
	else
	{
		strResult+="Y";
	}


	if(IsDigit(strText.GetAt(12)))
	{
		strTemp.Format(_T("%d"),CharToInt(strText.GetAt(12))*45);
		strResult+=strTemp;
	}
	else
	{
		strResult+="wqY";
	}


	if(IsDigit(strText.GetAt(13)))
	{
		strTemp.Format(_T("%d"),CharToInt(strText.GetAt(13))*14);
		strResult+=strTemp;
	}
	else
	{
		strResult+="SD";
	}

	m_xEdit.SendMessage(WM_SETTEXT,0,(LPARAM)strResult.GetBuffer());

}
