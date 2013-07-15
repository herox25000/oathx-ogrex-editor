#ifndef SKIN_ATTRIBUTE_HEAD_FILE
#define SKIN_ATTRIBUTE_HEAD_FILE

#pragma once

#include "Attribute.h"
#include "SkinControls.h"

//////////////////////////////////////////////////////////////////////////
//
////�궨��
//#define CLASS_NAME					32									//���ֳ���
//#define MAX_SKIN					64									//����������Ŀ
//
////��������
//#define SKIN_CONTROL_CLASS_NAME_STRING		TEXT("������")				// TCHAR * ���� ��ֻ����
//
////////////////////////////////////////////////////////////////////////////
//
////���Լ�¼��
//class SKIN_CONTROL_CLASS CSkinRecordFile : public ISkinRecord
//{
//	//��������
//protected:
//	TCHAR							m_szIniFileName[MAX_PATH];			//�����ļ�
//	TCHAR							m_szResDirectory[MAX_PATH];			//��ԴĿ¼
//
//	//��������
//public:
//	//���캯��
//	CSkinRecordFile();
//	//��������
//	virtual ~CSkinRecordFile();
//
//	//�����ӿ�
//public:
//	//�ͷŶ���
//	virtual void __cdecl Release() { delete this; }
//	//�ӿڲ�ѯ
//	virtual void * __cdecl QueryInterface(const IID & Guid, DWORD dwQueryVer);
//
//	//�ӿں���
//public:
//	//��ȡĿ¼
//	virtual LPCTSTR __cdecl GetResourceDirectory();
//	//��ȡ����
//	virtual int __cdecl ReadInt(LPCTSTR pszClassName, LPCTSTR pszItem, int iDefValue);
//	//��ȡ����
//	virtual COLORREF __cdecl ReadColor(LPCTSTR pszClassName, LPCTSTR pszItem, COLORREF crDefValue);
//	//��ȡ����
//	virtual RECT __cdecl ReadRect(LPCTSTR pszClassName, LPCTSTR pszItem, const RECT & rcDefValue);
//	//��ȡ����
//	virtual POINT __cdecl ReadPoint(LPCTSTR pszClassName, LPCTSTR pszItem, const POINT & ptDefValue);
//	//��ȡ����
//	virtual CString __cdecl ReadString(LPCTSTR pszClassName, LPCTSTR pszItem, LPCTSTR pszDefValue);
//	//д�����
//	virtual bool __cdecl WriteInt(LPCTSTR pszClassName, LPCTSTR pszItem, int iValue) { return false; }
//	//д�����
//	virtual bool __cdecl WriteColor(LPCTSTR pszClassName, LPCTSTR pszItem, COLORREF crValue) { return false; }
//	//д�����
//	virtual bool __cdecl WriteRect(LPCTSTR pszClassName, LPCTSTR pszItem, const RECT & rcValue) { return false; }
//	//д�����
//	virtual bool __cdecl WritePoint(LPCTSTR pszClassName, LPCTSTR pszItem, const POINT & ptValue) { return false; }
//	//д�����
//	virtual bool __cdecl WriteString(LPCTSTR pszClassName, LPCTSTR pszItem, LPCTSTR pszValue) { return false; }
//
//	//���ܺ���
//public:
//	//����Ŀ¼
//	bool InitSkinRecordFile(LPCTSTR pszIniFileName, LPCTSTR pszResDirectory);
//};

//////////////////////////////////////////////////////////////////////////
//
////��������
//class SKIN_CONTROL_CLASS CSkinAttribute : public ISkinAttribute, public CAttributeManager
//{
//	//��������
//protected:
//	TCHAR							m_szClassName[CLASS_NAME];			//��������
//
//	//��Դ����
//public:
//	static CFont					m_DefaultFont;						//Ĭ������
//
//	//�ڲ�����
//private:
//	static bool						m_bFlags;							//�ڲ���־
//	static ISkinRecord				* m_pISkinRecord;					//���ýӿ�
//	static ISkinAttribute			* m_SkinPtrArray[MAX_SKIN];			//��������
//	
//	//��������
//protected:
//	//���캯��
//	CSkinAttribute(LPCTSTR pszClassName);
//	//��������
//	virtual ~CSkinAttribute();
//
//	//�����ӿ�
//public:
//	//�ͷŶ���
//	virtual void __cdecl Release() { delete this; }
//	//�ӿڲ�ѯ
//	virtual void * __cdecl QueryInterface(const IID & Guid, DWORD dwQueryVer);
//
//	//�ӿں���
//public:
//	//��ȡ����
//	virtual LPCTSTR __cdecl GetClassName() { return m_szClassName; }
//	//��ȡ����
//	virtual HFONT __cdecl GetDefaultFont() { return m_DefaultFont; }
//
//	//���ú���
//protected:
//	//��ȡ����
//	int ReadInt(LPCTSTR pszItem, int iDefValue);
//	//��ȡ����
//	COLORREF ReadColor(LPCTSTR pszItem, COLORREF crDefValue);
//	//��ȡ����
//	RECT ReadRect(LPCTSTR pszItem, const RECT & rcDefValue);
//	//��ȡ����
//	POINT ReadPoint(LPCTSTR pszItem, const POINT & ptDefValue);
//	//��ȡ����
//	CString ReadString(LPCTSTR pszItem, LPCTSTR pszDefValue);
//	//д�����
//	bool WriteInt(LPCTSTR pszItem, int iValue);
//	//д�����
//	bool WriteColor(LPCTSTR pszItem, COLORREF crValue);
//	//д�����
//	bool WriteRect(LPCTSTR pszItem, const RECT & rcValue);
//	//д�����
//	bool WritePoint(LPCTSTR pszItem, const POINT & ptValue);
//	//д�����
//	bool WriteString(LPCTSTR pszItem, LPCTSTR pszValue);
//
//	//���ܺ���
//public:
//	//���ؽ�����Ϣ
//	static bool LoadSkinAttribute(IUnknownEx * pIUnknownEx);
//	//���������Ϣ
//	//static bool SaveSkinAttribute();
//	//��ԴĿ¼
//	static LPCTSTR GetResourceDirectory();
//	//ö������
//	static void * GetAttributeManager(INT_PTR nIndex, const IID & Guid, DWORD dwQueryVer);
//
//	//�ڲ�����
//private:
//	//ע�������
//	static bool RegisterSkinClass(IUnknownEx * pIUnknownEx);
//	//ע��������
//	static bool UnRegisterSkinClass(IUnknownEx * pIUnknownEx);
//};

//////////////////////////////////////////////////////////////////////////

#endif
