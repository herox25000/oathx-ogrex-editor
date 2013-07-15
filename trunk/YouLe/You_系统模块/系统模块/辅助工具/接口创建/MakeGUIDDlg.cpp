#include "Stdafx.h"
#include "MakeGUID.h"
#include "MakeGUIDDlg.h"

//////////////////////////////////////////////////////////////////////////

BEGIN_MESSAGE_MAP(CMakeGUIDDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_XOR, OnBnClickedXOR)
	ON_BN_CLICKED(IDC_MD5, OnBnClickedMD5)
	ON_BN_CLICKED(IDC_COPY, OnBnClickedCopy)
	ON_BN_CLICKED(IDC_GET_PRIME, OnBnClickedPrime)
	ON_BN_CLICKED(IDC_MAKE_VERSION, OnBnClickedVersion)
END_MESSAGE_MAP()

//////////////////////////////////////////////////////////////////////////

//���캯��
CMakeGUIDDlg::CMakeGUIDDlg() : CDialog(IDD_MAKEGUID_DIALOG)
{
}

//�ؼ���
void CMakeGUIDDlg::DoDataExchange(CDataExchange* pDX)
{
	__super::DoDataExchange(pDX);
}

//��ʼ������
BOOL CMakeGUIDDlg::OnInitDialog()
{
	__super::OnInitDialog();

	//����ͼ��
	HICON hIcon=AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	SetIcon(hIcon,TRUE);
	SetIcon(hIcon,FALSE);

	return TRUE;
}

//ȷ������
void CMakeGUIDDlg::OnOK()
{
	//��ȡ����
	CString strInterface;
	GetDlgItemText(IDC_INTERFACE,strInterface);
	strInterface.TrimLeft();
	strInterface.TrimRight();
	if (strInterface.IsEmpty())
	{
		AfxMessageBox("�ӿ����ֲ���Ϊ�գ����������룡");
		GetDlgItem(IDC_INTERFACE)->SetFocus();
		return;
	}

	//��ʾ���
	GUID Guid,Guid2;
	CString strBuffer;
	CoCreateGuid(&Guid);
	CoCreateGuid(&Guid2);
	strBuffer.Format(
		TEXT("#ifdef _UNICODE\r\n")
		TEXT("\t#define VER_%s INTERFACE_VERSION(1,1)\r\n\tstatic const GUID IID_%s=")
		TEXT("{0x%08x,0x%04x,0x%04x,0x%04x,0x%02x,0x%02x,0x%02x,0x%02x,0x%02x,0x%02x,0x%02x};\r\n")
		TEXT("#else\r\n")
		TEXT("\t#define VER_%s INTERFACE_VERSION(1,1)\r\n\tstatic const GUID IID_%s=")
		TEXT("{0x%08x,0x%04x,0x%04x,0x%04x,0x%02x,0x%02x,0x%02x,0x%02x,0x%02x,0x%02x,0x%02x};\r\n")
		TEXT("#endif\r\n"),

		strInterface,strInterface,Guid.Data1,Guid.Data2,Guid.Data3,Guid.Data4[0],Guid.Data4[1],
		Guid.Data4[2],Guid.Data4[3],Guid.Data4[4],Guid.Data4[5],Guid.Data4[6],Guid.Data4[7],

		strInterface,strInterface,Guid2.Data1,Guid2.Data2,Guid2.Data3,Guid2.Data4[0],Guid2.Data4[1],
		Guid2.Data4[2],Guid2.Data4[3],Guid2.Data4[4],Guid2.Data4[5],Guid2.Data4[6],Guid2.Data4[7]);

	SetDlgItemText(IDC_GUDI_SHOW,strBuffer);

	//���ý���
	GetDlgItem(IDC_INTERFACE)->SetFocus();

	//��������
	OnBnClickedCopy();

	return;
}

//XOR ��ť
void CMakeGUIDDlg::OnBnClickedXOR()
{
	//��ȡ����
	CString strSourceData;
	GetDlgItemText(IDC_SOURCE_DATA,strSourceData);
	strSourceData.TrimLeft();
	strSourceData.TrimRight();
	if (strSourceData.IsEmpty())
	{
		AfxMessageBox("�������ݲ���Ϊ�գ����������룡");
		GetDlgItem(IDC_SOURCE_DATA)->SetFocus();
		return;
	}

	//��������
	TCHAR szResult[1024]=TEXT("");
	CXOREncrypt::EncryptData(strSourceData,szResult,CountArray(szResult));

	//���ý��
	SetDlgItemText(IDC_RESULT_DATA,szResult);

	return;
}

//MD5 ��ť
void CMakeGUIDDlg::OnBnClickedMD5()
{
	//��ȡ����
	CString strSourceData;
	GetDlgItemText(IDC_SOURCE_DATA,strSourceData);
	strSourceData.TrimLeft();
	strSourceData.TrimRight();
	if (strSourceData.IsEmpty())
	{
		AfxMessageBox("�������ݲ���Ϊ�գ����������룡");
		GetDlgItem(IDC_SOURCE_DATA)->SetFocus();
		return;
	}

	//��������
	TCHAR szResult[33]=TEXT("");
	CMD5Encrypt::EncryptData(strSourceData,szResult);

	//���ý��
	SetDlgItemText(IDC_RESULT_DATA,szResult);

	return;
}

//������ť
void CMakeGUIDDlg::OnBnClickedCopy()
{
	//��ȡ���� 
	CString strBuffer;
	GetDlgItemText(IDC_GUDI_SHOW,strBuffer);
	if (strBuffer.IsEmpty()) return;

	//�򿪼��а�
	if (OpenClipboard()==FALSE) return;
	if (EmptyClipboard()==FALSE) 
	{
		CloseClipboard();
		return;
	}

	//��������
	HANDLE hData=GlobalAlloc(GMEM_MOVEABLE|GMEM_ZEROINIT,strBuffer.GetLength()+sizeof(TCHAR));
	if (hData==NULL) 
	{
		CloseClipboard();
		return;
	}
	LPTSTR szBuffer=(LPTSTR)GlobalLock(hData);
	lstrcpy(szBuffer,strBuffer);
	SetClipboardData(CF_TEXT,hData);
	GlobalUnlock(hData);
	CloseClipboard();

	return;
}

//������ť
void CMakeGUIDDlg::OnBnClickedPrime()
{
	//��ȡ����
	CString strInterface;
	GetDlgItemText(IDC_PRIME_VALUE,strInterface);
	strInterface.TrimLeft();
	strInterface.TrimRight();
	if (strInterface.IsEmpty())
	{
		AfxMessageBox("��������Ϊ�գ����������룡");
		GetDlgItem(IDC_PRIME_VALUE)->SetFocus();
		return;
	}

	//��ȡ����
	UINT uLessNum=atol(strInterface);
	uLessNum=__max(uLessNum,1);
	for (UINT uPrime=uLessNum;uPrime>2;uPrime++)
	{
		for (UINT i=2;i<=uPrime/2;i++)
		{
			if (uPrime%i==0) break;
		}
		if (i>uPrime/2) break;
	}

	//������
	GetDlgItem(IDC_PRIME_VALUE)->SetFocus();
	SetDlgItemInt(IDC_PRIME_RUSULT,uPrime,FALSE);

	return;
}

//�汾��ť
void CMakeGUIDDlg::OnBnClickedVersion()
{
	//��ȡ����
	CString strVersion;
	GetDlgItemText(IDC_VERSION,strVersion);
	strVersion.TrimLeft();
	strVersion.TrimRight();
	if (strVersion.IsEmpty())
	{
		AfxMessageBox("�汾���벻��Ϊ�գ����������룡");
		GetDlgItem(IDC_VERSION)->SetFocus();
		return;
	}

	//��������
	BYTE cbVersion[4];
	for (int i=0;i<4;i++)
	{
		CString strResult;
		if (AfxExtractSubString(strResult,strVersion,i,TEXT(','))==FALSE)
		{
			AfxMessageBox("�汾������󣬸�ʽΪ 6,0,1,0 ���������룡");
			GetDlgItem(IDC_VERSION)->SetFocus();
			return;
		}
		else cbVersion[i]=atoi(strResult);
	}

	//������
	SetDlgItemInt(IDC_VERSION_RESULT,MAKELONG(MAKEWORD(cbVersion[0],cbVersion[1]),MAKEWORD(cbVersion[2],cbVersion[3])));

	return;
}

//////////////////////////////////////////////////////////////////////////

