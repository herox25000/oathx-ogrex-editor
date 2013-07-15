#pragma once

#include "Stdafx.h"
#include "AfxTempl.h"

//////////////////////////////////////////////////////////////////////////

//�Ի�����
class CSDKBuilderDlg : public CDialog
{
	//��������
protected:
	CString								m_strSourcePath;				//ԭ·��
	CString								m_strTargetPath;				//Ŀ��·��
	CArray<CString>						m_strConversion;				//ת���ַ�

	//�ؼ�����
protected:
	CSkinRichEdit						m_SDKFileList;					//ͷ�ļ��б�
	CSkinRichEdit						m_LIBFileList;					//ͷ�ļ��б�

	//��������
public:
	//���캯��
	CSDKBuilderDlg();

	//���غ���
protected:
	//�ؼ���
	virtual void DoDataExchange(CDataExchange * pDX);
	//��ʼ������
	virtual BOOL OnInitDialog();

	//���ܺ���
protected:
	//����ͷ�ļ�
	void LoadSDKFileList();
	//�������ӿ�
	void LoadLIBFileList();
	//����ת���ַ�
	void LoadConversionList();
	//����Ŀ¼
	void CreateDirectory(LPCTSTR pszDirectory);
	//ת���ļ�
	bool ConversionSDKFile(LPCTSTR pszSDKFile);
	//�����ļ�
	bool CopyBinaryFile(LPCTSTR pszSourceFile, LPCTSTR pszTargetPath);

	//��Ϣӳ��
public:
	//��������
	afx_msg void OnBnClickedBulid();

	DECLARE_MESSAGE_MAP()
};

//////////////////////////////////////////////////////////////////////////
