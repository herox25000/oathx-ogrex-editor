#include "StdAfx.h"
#include "SolutionXML.h"

//////////////////////////////////////////////////////////////////////////
SolutionXML::SolutionXML(void)
:m_pDocument(NULL)
{
}

//////////////////////////////////////////////////////////////////////////
SolutionXML::~SolutionXML(void)
{
	delete m_pDocument;
	m_pDocument = NULL;
}

//////////////////////////////////////////////////////////////////////////
BOOL		SolutionXML::Create(CString sPath, CString sName)
{
	if (m_pDocument != NULL)
	{
		delete m_pDocument;
		m_pDocument = NULL;
	}

	m_pDocument = new TiXmlDocument();
	ASSERT(m_pDocument != NULL);

	TiXmlDeclaration* pDecl = new TiXmlDeclaration("1.0", "UTF-8", "");
	m_pDocument->LinkEndChild(pDecl);

	TiXmlElement* root = new TiXmlElement("ogre");
	m_pDocument->LinkEndChild(root);

	m_sPath = sPath;
	m_sName	= sName;

	m_sPathName = m_sPath + "/" + sName + ".ogrexproject";
	
	return m_pDocument->SaveFile(m_sPathName);
}

//////////////////////////////////////////////////////////////////////////
BOOL		SolutionXML::Open(CString sPathName)
{
	if (m_pDocument != NULL)
	{
		m_pDocument->SaveFile(m_sPathName);
		
		delete m_pDocument;
		m_pDocument = NULL;
	}

	m_pDocument = new TiXmlDocument();
	ASSERT(m_pDocument != NULL);
	
	m_sPathName = sPathName;

	return m_pDocument->LoadFile(m_sPathName);
}

//////////////////////////////////////////////////////////////////////////
BOOL		SolutionXML::Save()
{
	return m_pDocument->SaveFile(m_sPathName);
}
