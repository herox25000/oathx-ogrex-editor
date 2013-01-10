#ifndef _____Og2dDynlibManager_H
#define _____Og2dDynlibManager_H

#include "Og2dSingleton.h"
#include "Og2dDynlib.h"

namespace Og2d
{
	// 动态链接库映射表
	typedef map<String, DynLib*>::type	StringDynlib;

	/**
	* \ingroup : Og2d
	*
	* \os&IDE  : Microsoft Windows XP (SP2)  &  Microsoft Visual C++ .NET 2008
	*
	* \VERSION : 1.0
	*
	* \date    : 2012-07-22
	*
	* \Author  : lp
	*
	* \Desc    : 动态链接库管理器
	*
	* \bug     : 
	*
	*/
	class Og2d_Export_API DynlibManager : public Singleton<DynlibManager>
	{
	public:
		/** 获取单件引用
		 *
		 * \return 
		 */
		static	DynlibManager&		getSingleton();

		/** 获取单件指针
		 *
		 * \return 
		 */
		static	DynlibManager*		getSingletonPtr();

	public:
		/** 构造函数
		 *
		 * \return 
		 */
		DynlibManager();

		/** 析构函数
		 *
		 * \return 
		 */
		virtual ~DynlibManager();

        /** 加载动态链接库
         *
         * \param name 
         * \return 
         */
        virtual DynLib*				load(const String& name);

		/**	卸载动态链接库
		 *
		 * \param lib 
		 */
		virtual void				unload(DynLib* pDynlib);

	protected:
		StringDynlib				m_dynlib;
	};
}

#endif