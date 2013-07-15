// SerialNumGeneratorDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "SerialNumGenerator.h"
#include "SerialNumGeneratorDlg.h"
#include ".\serialnumgeneratordlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CSerialNumGeneratorDlg 对话框



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


// CSerialNumGeneratorDlg 消息处理程序

BOOL CSerialNumGeneratorDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	
	return TRUE;  // 除非设置了控件的焦点，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CSerialNumGeneratorDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标显示。
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
	// TODO: 在此添加控件通知处理程序代码
	CString strResult=_T("序列号输入错误！");
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
