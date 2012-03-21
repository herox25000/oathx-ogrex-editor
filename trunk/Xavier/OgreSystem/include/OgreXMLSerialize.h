#ifndef _____OgreXMLSerialize_H
#define _____OgreXMLSerialize_H

#include "OgreProperty.h"
#include "tinyxml.h"

namespace Ogre
{
	/**
	* \ingroup : OgreAppEdit
	*
	* \os&IDE  : Microsoft Windows XP (SP3)  &  Microsoft Visual C++ .NET 2008 & ogre1.8
	*
	* \VERSION : 1.0
	*
	* \@date   : 2012-03-21
	*
	* \Author  : lp
	*
	* \Desc    : 
	*
	* \bug     : 
	*
	*/
	class OgreSystem_Export_API XMLSerialize : public PropertySet
	{
	public:
		/** 构造函数
		 *
		 */
		XMLSerialize();

		/**
		 *
		 * \param void 
		 * \return 
		 */
		virtual ~XMLSerialize(void);

	public:
		/** 创建文档
		 *
		 * \param sPath		文档路径
		 * \param sName		文档名称
		 * \return 
		 */
		virtual	bool			createSerialize(const String& sPath, const String& sName);

		/** 获取路径
		 *
		 * \return 
		 */
		virtual String			getPath() const;

		/** 获取名称
		 *
		 * \return 
		 */
		virtual String			getName() const;

		/** 获取完整路径
		 *
		 * \return 
		 */
		virtual String			getPathName() const;

		/** 加载文件
		 *
		 * \param sPathName 
		 * \return 
		 */
		virtual bool			load(const String& sPathName);

		/** 卸载文件
		 *
		 */
		virtual void			unload();
	protected:
		// 文档
		TiXmlDocument*			m_pDocument;
		String					m_sPath;
		String					m_sName;
	};
}

#endif
