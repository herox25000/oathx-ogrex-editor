#include "StdAfx.h"
#include "XavDocSerialize.h"

/**
 *
 * \param void 
 * \return 
 */
XavDocSerialize::XavDocSerialize(void) : m_pDocument(NULL)
{
}

/**
 *
 * \param void 
 * \return 
 */
XavDocSerialize::~XavDocSerialize(void)
{
	if (m_pDocument != NULL)
	{
		m_pDocument->SaveFile(GetPathName().GetBuffer());
		delete m_pDocument;
	}
}

/**
 *
 * \param sPath 
 * \param sName 
 * \return 
 */
BOOL	XavDocSerialize::Create(const CString& sPath, const CString& sName)
{
	if (m_pDocument != NULL)
	{
		m_pDocument->SaveFile(GetPathName().GetBuffer());
		
		delete m_pDocument;
		m_pDocument = NULL;
	}

	m_sPath = sPath; 
	m_sName = sName;

	if (::CreateDirectory(GetPathName().GetBuffer(), NULL))
		return TRUE;
	
	return FALSE;
}

/**
 *
 */
void	XavDocSerialize::Clear()
{

}

/**
 *
 */
void	XavDocSerialize::Close()
{

}

/**
 *
 * \return 
 */
CString	XavDocSerialize::GetPathName()
{
	return m_sPath + "/" + m_sName;
}

