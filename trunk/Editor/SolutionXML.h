#pragma once

#include "tinyxml.h"

class SolutionXML
{
public:
	static	SolutionXML&	GetSingleton()
	{
		static SolutionXML instance;
		return instance;
	}

public:
	TiXmlDocument*			GetDocument() const {return m_pDocument;}
	BOOL					Create(CString sPath, CString sName);
	BOOL					Open(CString sPathName);
	BOOL					Save();
	CString					GetPathName() {return m_sPathName;}
protected:
	SolutionXML(void);
	virtual ~SolutionXML(void);

protected:
	TiXmlDocument*			m_pDocument;
	CString					m_sPath;
	CString					m_sName;
	CString					m_sPathName;
};
