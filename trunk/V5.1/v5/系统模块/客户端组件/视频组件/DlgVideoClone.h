#pragma once


class CDlgVideoClone : public CDialog
{
	//��������
public:
	HICON							m_hIcon;						//ͼ����Դ

	//��������
public:
	//���캯��
	CDlgVideoClone(CWnd* pParent = NULL);
	//��������
	virtual ~CDlgVideoClone();

	//���ܺ���
public:
	//������Ƶ
	void DrawUserVideo(DWORD dwUserid, LPVOID lpBuf, DWORD dwLen, BITMAPINFOHEADER bmiHeader);

	//�̳к���
protected:
	//���ݰ�
	virtual void DoDataExchange(CDataExchange* pDX);

	DECLARE_MESSAGE_MAP()
	DECLARE_DYNAMIC(CDlgVideoClone)
public:
	virtual BOOL OnInitDialog();
};
