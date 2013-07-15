#if !defined(__DB_H__)
#define __DB_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#import "c:\program files\common files\system\ado\msado15.dll" no_namespace \
	rename("EOF", "adoEOF") \
	rename("LockTypeEnum", "adoLockTypeEnum") \
	rename("DataTypeEnum", "adoDataTypeEnum")
#include "icrsint.h"
inline void TESTHR(HRESULT x) { if FAILED(x) _com_issue_error(x); }
inline BOOL IS_VT_NULL(unsigned short x) { return (x == VT_NULL ? TRUE : FALSE); }

class CDB
{
public:
	CDB();
	virtual ~CDB();
	_RecordsetPtr Exec(CString& strSql);
	void Close();

private:
	_ConnectionPtr m_Conn;

public:
	CString m_LinkString;

	BOOL    Conn();
};
#endif