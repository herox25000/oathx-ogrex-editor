#pragma once

#include "tinyxml.h"

/**
* \ingroup : Xavier
*
* \os&IDE  : Microsoft Windows XP (SP3)  &  Microsoft Visual C++ .NET 2008 & ogre1.8
*
* \VERSION : 1.0
*
* \@date   : 2012-03-14
*
* \Author  : lp
*
* \Desc    : 
*
* \bug     : 
*
*/
class XavDocSerialize
{
public:
	/**
	 *
	 * \return 
	 */
	static XavDocSerialize&		GetSingleton()
	{
		static XavDocSerialize ins;
		return ins;
	}
public:
	/**
	 *
	 * \param void 
	 * \return 
	 */
	XavDocSerialize(void);

	/**
	 *
	 * \param void 
	 * \return 
	 */
	virtual ~XavDocSerialize(void);

	/**
	 *
	 * \param sPath 
	 * \param sName 
	 * \return 
	 */
	BOOL						Create(const CString& sPath, const CString& sName);

	/**
	 *
	 */
	void						Clear();

	/**
	 *
	 */
	void						Close();

	/**
	 *
	 * \return 
	 */
	CString						GetPath() const {return m_sPath;}

	/**
	 *
	 * \return 
	 */
	CString						GetName() const {return m_sName;}

	/**
	 *
	 * \return 
	 */
	CString						GetPathName();
protected:
	CString						m_sPath;
	CString						m_sName;

	TiXmlDocument*				m_pDocument;
};
