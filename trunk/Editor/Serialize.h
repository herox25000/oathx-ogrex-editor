#pragma once

#include "tinyxml.h"

class Serialize
{
public:
	static	Serialize&		GetSingleton()
	{
		static Serialize instance;
		return instance;
	}

public:
	TiXmlDocument*			GetDocument() const {return m_pDocument;}
	BOOL					Create(CString sPath, CString sName);
	BOOL					Open(CString sPathName);
	BOOL					Save();
	CString					GetPathName() {return m_sPathName;}

protected:
	Serialize(void);
	virtual ~Serialize(void);

protected:
	TiXmlDocument*			m_pDocument;
	CString					m_sPath;
	CString					m_sName;
	CString					m_sPathName;
};
