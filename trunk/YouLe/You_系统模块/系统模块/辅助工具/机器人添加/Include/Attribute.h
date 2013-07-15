#ifndef ATTRIBUTE_HEAD_FILE
#define ATTRIBUTE_HEAD_FILE

#pragma once

#include "SkinControls.h"

//////////////////////////////////////////////////////////////////////////

//��������
class SKIN_CONTROL_CLASS CAttribute : public IAttribute
{
	//����ָ��������
	union Attribute_Data
	{
		VOID							* m_Void;						//VOID ָ��
		INT								* m_Int;						//INT ָ��
		BYTE							* m_Byte;						//BYTE ָ��
		WORD							* m_Word;						//WORD ָ��
		LONG							* m_Long;						//LONG ָ��
		DWORD							* m_Dword;						//DWORD ָ��
		DOUBLE							* m_Double;						//DOUBLE ָ��
		CString							* m_String;						//CString ָ��
	};

	//��������
protected:
	bool								m_bReadOnly;					//�Ƿ�ֻ��
	DWORD								m_dwHash;						//��ϣ��ֵ
	CString								m_strName;						//��������
	Attribute_Data						m_Data;							//��������
	enAttributeType						m_Type;							//��������
	
	//��������
public:
	//���캯��
	CAttribute()
	{
		m_dwHash=0L;
		m_bReadOnly=false;
		m_Type=Type_EMPTY;
		m_Data.m_Int=NULL;
	}
	//���캯��
	CAttribute(LPCTSTR pszName, VOID * pVoid, bool bReadOnly)
	{
		m_Type=Type_VOID;
		m_Data.m_Void=pVoid;
		m_strName=pszName;
		m_bReadOnly=bReadOnly;
		m_dwHash=HashAttribute(pszName);
	}
	//���캯��
	CAttribute(LPCTSTR pszName, INT * pInt, bool bReadOnly)
	{
		m_Type=Type_INT;
		m_Data.m_Int=pInt;
		m_strName=pszName;
		m_bReadOnly=bReadOnly;
		m_dwHash=HashAttribute(pszName);
	}
	//���캯��
	CAttribute(LPCTSTR pszName, BYTE * pByte, bool bReadOnly)
	{
		m_Type=Type_BYTE;
		m_Data.m_Byte=pByte;
		m_strName=pszName;
		m_bReadOnly=bReadOnly;
		m_dwHash=HashAttribute(pszName);
	}
	//���캯��
	CAttribute(LPCTSTR pszName, WORD * pWord, bool bReadOnly)
	{
		m_Type=Type_WORD;
		m_Data.m_Word=pWord;
		m_strName=pszName;
		m_bReadOnly=bReadOnly;
		m_dwHash=HashAttribute(pszName);
	}
	//���캯��
	CAttribute(LPCTSTR pszName, LONG * pLong, bool bReadOnly)
	{
		m_Type=Type_LONG;
		m_Data.m_Long=pLong;
		m_strName=pszName;
		m_bReadOnly=bReadOnly;
		m_dwHash=HashAttribute(pszName);
	}
	//���캯��
	CAttribute(LPCTSTR pszName, DWORD * pDword, bool bReadOnly)
	{
		m_Type=Type_DWORD;
		m_Data.m_Dword=pDword;
		m_strName=pszName;
		m_bReadOnly=bReadOnly;
		m_dwHash=HashAttribute(pszName);
	}
	//���캯��
	CAttribute(LPCTSTR pszName, DOUBLE * pDouble, bool bReadOnly)
	{
		m_Type=Type_DOUBLE;
		m_Data.m_Double=pDouble;
		m_strName=pszName;
		m_bReadOnly=bReadOnly;
		m_dwHash=HashAttribute(pszName);
	}
	//���캯��
	CAttribute(LPCTSTR pszName, CString * pString, bool bReadOnly)
	{
		m_Type=Type_STRING;
		m_Data.m_String=pString;
		m_strName=pszName;
		m_bReadOnly=bReadOnly;
		m_dwHash=HashAttribute(pszName);
	}
	//��������
	virtual ~CAttribute() { }

	//�����ӿ�
public:
	//�ͷŶ���
	virtual bool __cdecl Release() { if (IsValid()) delete this; return true; }
	//�Ƿ���Ч
	virtual bool __cdecl IsValid() { return AfxIsValidAddress(this,sizeof(CAttribute))?true:false; }
	//�ӿڲ�ѯ
	virtual void * __cdecl QueryInterface(const IID & Guid, DWORD dwQueryVer)
	{
		QUERYINTERFACE(IAttribute,Guid,dwQueryVer);
		QUERYINTERFACE_IUNKNOWNEX(IAttribute,Guid,dwQueryVer);
		return NULL;
	}

	//�ӿں���
public:
	//��ȡ��ϣֵ
	virtual DWORD __cdecl GetHashValue() { return m_dwHash; }
	//�Ƿ�ֻ��
	virtual bool __cdecl IsReadOnly() { return m_bReadOnly; }
	//��ȡ����
	virtual LPCTSTR __cdecl GetAttributeName() { return m_strName; }
	//��ȡ����
	virtual enAttributeType __cdecl GetAttributeType() { return m_Type; }
	//��ȡ PTR
	virtual bool __cdecl GetValue(VOID * * ppvValue)
	{
		ASSERT(m_Type==Type_VOID);
		if (m_Type!=Type_VOID) 
		{
			*ppvValue=NULL;
			return false;
		}
		*ppvValue=m_Data.m_Void;
		return true;
	};
	//��ȡ INT
	virtual bool __cdecl GetValue(INT & iValue)
	{
		ASSERT(m_Type==Type_INT);
		if (m_Type!=Type_INT) 
		{
			iValue=0;
			return false;
		}
		iValue=*m_Data.m_Int;
		return true;
	};
	//��ȡ BYTE
	virtual bool __cdecl GetValue(BYTE & cbValue)
	{
		ASSERT(m_Type==Type_BYTE);
		if (m_Type!=Type_BYTE) 
		{
			cbValue=0;
			return false;
		}
		cbValue=*m_Data.m_Byte;
		return true;
	};
	//��ȡ WORD
	virtual bool __cdecl GetValue(WORD & wValue)
	{
		ASSERT(m_Type==Type_WORD);
		if (m_Type!=Type_WORD) 
		{
			wValue=0;
			return false;
		}
		wValue=*m_Data.m_Word;
		return true;
	};
	//��ȡ LONG
	virtual bool __cdecl GetValue(LONG & lValue)
	{
		ASSERT(m_Type==Type_LONG);
		if (m_Type!=Type_LONG) 
		{
			lValue=0;
			return false;
		}
		lValue=*m_Data.m_Long;
		return true;
	};
	//��ȡ DWORD
	virtual bool __cdecl GetValue(DWORD & dwValue)
	{
		ASSERT(m_Type==Type_DWORD);
		if (m_Type!=Type_DWORD) 
		{
			dwValue=0;
			return false;
		}
		dwValue=*m_Data.m_Dword;
		return true;
	};
	//��ȡ DOUBLE
	virtual bool __cdecl GetValue(DOUBLE & dValue)
	{
		ASSERT(m_Type==Type_DOUBLE);
		if (m_Type!=Type_DOUBLE) 
		{
			dValue=0.0;
			return false;
		}
		dValue=*m_Data.m_Double;
		return true;
	};
	//��ȡ�ַ���
	virtual bool __cdecl GetValue(CString & strValue)
	{
		ASSERT(m_Type==Type_STRING);
		if (m_Type!=Type_STRING) 
		{
			strValue.Empty();
			return false;
		}
		strValue=*m_Data.m_String;
		return true;
	}
	//��ȡ����
	virtual bool __cdecl GetVarValue(CString & strValue)
	{
		switch (m_Type)
		{
		case Type_INT:
			{
				strValue.Format(TEXT("%d"),*m_Data.m_Int);
				return true;
			}
		case Type_BYTE:
			{
				strValue.Format(TEXT("%d"),*m_Data.m_Byte);
				return true;
			}
		case Type_WORD:
			{
				strValue.Format(TEXT("%u"),*m_Data.m_Word);
				return true;
			}
		case Type_LONG:
			{
				strValue.Format(TEXT("%ld"),*m_Data.m_Long);
				return true;
			}
		case Type_DWORD:
			{
				strValue.Format(TEXT("%lu"),*m_Data.m_Dword);
				return true;
			}
		case Type_DOUBLE:
			{
				strValue.Format(TEXT("%f"),*m_Data.m_Double);
				return true;
			}
		case Type_STRING:
			{
				strValue=*m_Data.m_String;
				return true;
			}
		default:
			{
				ASSERT(0);
				break;
			}
		}
		return false;
	}
	//���� PTR
	virtual bool __cdecl SetValue(void * pValue)
	{
		ASSERT(m_Type==Type_VOID);
		ASSERT(m_bReadOnly==false);
		if (m_bReadOnly) return false;
		if (m_Type!=Type_VOID) return false;
		m_Data.m_Void=pValue;
		return true;
	};
	//���� INT
	virtual bool __cdecl SetValue(INT iValue)
	{
		ASSERT(m_Type==Type_INT);
		ASSERT(m_bReadOnly==false);
		if (m_bReadOnly) return false;
		if (m_Type!=Type_INT) return false;
		*m_Data.m_Int=iValue;
		return true;
	};
	//���� BYTE
	virtual bool __cdecl SetValue(BYTE cbValue)
	{
		ASSERT(m_Type==Type_BYTE);
		ASSERT(m_bReadOnly==false);
		if (m_bReadOnly) return false;
		if (m_Type!=Type_BYTE) return false;
		*m_Data.m_Byte=cbValue;
		return true;
	};
	//���� WORD
	virtual bool __cdecl SetValue(WORD wValue)
	{
		ASSERT(m_Type==Type_WORD);
		ASSERT(m_bReadOnly==false);
		if (m_bReadOnly) return false;
		if (m_Type!=Type_WORD) return false;
		*m_Data.m_Word=wValue;
		return true;
	};
	//���� LONG
	virtual bool __cdecl SetValue(LONG lValue)
	{
		ASSERT(m_Type==Type_LONG);
		ASSERT(m_bReadOnly==false);
		if (m_bReadOnly) return false;
		if (m_Type!=Type_LONG) return false;
		*m_Data.m_Long=lValue;
		return true;
	};
	//���� DWORD
	virtual bool __cdecl SetValue(DWORD dwValue)
	{
		ASSERT(m_Type==Type_DWORD);
		ASSERT(m_bReadOnly==false);
		if (m_bReadOnly) return false;
		if (m_Type!=Type_DWORD) return false;
		*m_Data.m_Dword=dwValue;
		return true;
	};
	//���� DOUBLE
	virtual bool __cdecl SetValue(DOUBLE dValue)
	{
		ASSERT(m_Type==Type_DOUBLE);
		ASSERT(m_bReadOnly==false);
		if (m_bReadOnly) return false;
		if (m_Type!=Type_DOUBLE) return false;
		*m_Data.m_Double=dValue;
		return true;
	};
	//���� STRING
	virtual bool __cdecl SetValue(LPCTSTR pszValue)
	{
		ASSERT(m_Type==Type_STRING);
		ASSERT(m_bReadOnly==false);
		if (m_bReadOnly) return false;
		if (m_Type!=Type_STRING) return false;
		*m_Data.m_String=pszValue;
		return true;
	};

	//��ϣ����
public:
	//��ϣת��
	static DWORD HashAttribute(LPCTSTR pszString)
	{
		DWORD dwHash=0L;
		CString strString=pszString;
		strString.MakeLower();
		int nLen=strString.GetLength();
		for (int i=0;i<nLen;i++)
		{
			dwHash^=strString[i];
			dwHash<<=1;
		}
		return dwHash;
	};
};

//////////////////////////////////////////////////////////////////////////

//���Թ�����
class SKIN_CONTROL_CLASS CAttributeManager : public IAttributeManager, public IAttributeService
{
	//��������
protected:
	CArrayTemplate<CAttribute>			m_Attribute;				//��������

	//��������
public:
	//���캯��
	CAttributeManager();
	//��������
	virtual ~CAttributeManager();

	//�����ӿ�
public:
	//�ͷŶ���
	virtual bool __cdecl Release() { if (IsValid()) delete this; return true; }
	//�Ƿ���Ч
	virtual bool __cdecl IsValid() { return AfxIsValidAddress(this,sizeof(CAttributeManager))?true:false; }
	//�ӿڲ�ѯ
	virtual void * __cdecl QueryInterface(const IID & Guid, DWORD dwQueryVer);

	//�ӿں���
public:
	//��ѯ����
	virtual IAttribute * __cdecl QueryAttribute(WORD wIndex);
	//��ѯ����
	virtual IAttribute * __cdecl QueryAttribute(LPCTSTR pszName);
	//ע������
	virtual bool __cdecl UnRegisterAttribute(LPCTSTR pszName);
	//ע������
	virtual bool __cdecl RegisterAttribute(LPCTSTR pszName, void * pPtr, bool bReadOnly);
	//ע������
	virtual bool __cdecl RegisterAttribute(LPCTSTR pszName, INT * pInt, bool bReadOnly);
	//ע������
	virtual bool __cdecl RegisterAttribute(LPCTSTR pszName, BYTE * pByte, bool bReadOnly);
	//ע������
	virtual bool __cdecl RegisterAttribute(LPCTSTR pszName, WORD * pWord, bool bReadOnly);
	//ע������
	virtual bool __cdecl RegisterAttribute(LPCTSTR pszName, LONG * pLong, bool bReadOnly);
	//ע������
	virtual bool __cdecl RegisterAttribute(LPCTSTR pszName, DWORD * pDword, bool bReadOnly);
	//ע������
	virtual bool __cdecl RegisterAttribute(LPCTSTR pszName, DOUBLE * pDouble, bool bReadOnly);
	//ע������
	virtual bool __cdecl RegisterAttribute(LPCTSTR pszName, CString * pString, bool bReadOnly);

	//�ӿں���
public:
	//��ȡ����
	virtual bool __cdecl GetAttributeValue(LPCTSTR pszName, VOID * * ppvValue);
	//��ȡ����
	virtual bool __cdecl GetAttributeValue(LPCTSTR pszName, INT & iValue);
	//��ȡ����
	virtual bool __cdecl GetAttributeValue(LPCTSTR pszName, BYTE & cbValue);
	//��ȡ����
	virtual bool __cdecl GetAttributeValue(LPCTSTR pszName, WORD & wValue);
	//��ȡ����
	virtual bool __cdecl GetAttributeValue(LPCTSTR pszName, LONG & lValue);
	//��ȡ����
	virtual bool __cdecl GetAttributeValue(LPCTSTR pszName, DWORD & dwValue);
	//��ȡ����
	virtual bool __cdecl GetAttributeValue(LPCTSTR pszName, DOUBLE & dValue);
	//��ȡ����
	virtual bool __cdecl GetAttributeValue(LPCTSTR pszName, CString & strValue);
	//��ȡ����
	virtual bool __cdecl GetAttributeVarValue(LPCTSTR pszName, CString & strValue);
	//��������
	virtual bool __cdecl SetAttributeValue(LPCTSTR pszName, void * pValue);
	//��������
	virtual bool __cdecl SetAttributeValue(LPCTSTR pszName, INT iValue);
	//��������
	virtual bool __cdecl SetAttributeValue(LPCTSTR pszName, BYTE cbValue);
	//��������
	virtual bool __cdecl SetAttributeValue(LPCTSTR pszName, WORD wValue);
	//��������
	virtual bool __cdecl SetAttributeValue(LPCTSTR pszName, LONG lValue);
	//��������
	virtual bool __cdecl SetAttributeValue(LPCTSTR pszName, DWORD dwValue);
	//��������
	virtual bool __cdecl SetAttributeValue(LPCTSTR pszName, DOUBLE dValue);
	//��������
	virtual bool __cdecl SetAttributeValue(LPCTSTR pszName, LPCTSTR pszValue);
};

//////////////////////////////////////////////////////////////////////////

#endif
