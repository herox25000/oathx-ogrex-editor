#ifndef _____Og2dDynlibManager_H
#define _____Og2dDynlibManager_H

#include "Og2dSingleton.h"
#include "Og2dDynlib.h"

namespace Og2d
{
	// ��̬���ӿ�ӳ���
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
	* \Desc    : ��̬���ӿ������
	*
	* \bug     : 
	*
	*/
	class Og2d_Export_API DynlibManager : public Singleton<DynlibManager>
	{
	public:
		/** ��ȡ��������
		 *
		 * \return 
		 */
		static	DynlibManager&		getSingleton();

		/** ��ȡ����ָ��
		 *
		 * \return 
		 */
		static	DynlibManager*		getSingletonPtr();

	public:
		/** ���캯��
		 *
		 * \return 
		 */
		DynlibManager();

		/** ��������
		 *
		 * \return 
		 */
		~DynlibManager();

        /** ���ض�̬���ӿ�
         *
         * \param name 
         * \return 
         */
        virtual DynLib*				load(const String& name);

		/**	ж�ض�̬���ӿ�
		 *
		 * \param lib 
		 */
		virtual void				unload(DynLib* pDynlib);

	protected:
		StringDynlib				m_dynlib;
	};
}

#endif