#pragma once

#include <windows.h>

//��ini�ļ�
class CIniFile
{
protected:
	TCHAR m_FileName[MAX_PATH]; //�ļ���
public:
	CIniFile(void);
	~CIniFile(void);

	void Load( LPCTSTR FileName ); //ȡ�ļ�

	int GetInt(LPCTSTR pszSectionName, LPCTSTR pszKeyName); //��int����ֵ
	int SetInt(LPCTSTR pszSectionName, LPCTSTR pszKeyName, int nValue); //����int����ֵ

	int GetString(LPCTSTR pszSectionName, LPCTSTR pszKeyName, LPTSTR pszBuffer, int nLen); //�õ��ַ�������ֵ
	//int GetString(CString strSectionName, CString strKeyName, CString &strBuffer,int nLen);
	int SetString(LPCTSTR pszSectionName, LPCTSTR pszKeyName, LPCTSTR pszBuffer); //�����ַ�������ֵ
};
