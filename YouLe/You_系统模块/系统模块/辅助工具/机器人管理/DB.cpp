// DB.cpp: implementation of the CDB class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "DB.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// CDB  Construction/Destruction
//////////////////////////////////////////////////////////////////////

CDB::CDB()
{
	m_LinkString="";
	m_Conn=NULL;
}

CDB::~CDB()
{
	if((m_Conn!=NULL) && (m_Conn->State))
	{
		m_Conn->Close();
	}
}

BOOL CDB::Conn()
{
	try
	{
		m_Conn.CreateInstance(__uuidof(Connection));
		_bstr_t connstr = m_LinkString;
		m_Conn->Open(connstr, L"", L"", adOpenUnspecified);
		m_Conn->CursorLocation = adUseClient;
	}
	catch(_com_error& e)
	{
		AfxMessageBox(e.Description());
		return FALSE;
	}

	return TRUE;
}

_RecordsetPtr CDB::Exec(CString& strSql)
{
	_RecordsetPtr rs;
	try
	{
		rs = m_Conn->Execute((_bstr_t)strSql, NULL, adCmdText);
	}
	catch(_com_error& e)
	{
		AfxMessageBox(e.Description());
		return NULL;
	}

	return rs;
}

void CDB::Close()
{
	if(m_Conn->State)
	{
		m_Conn->Close();
	}
}