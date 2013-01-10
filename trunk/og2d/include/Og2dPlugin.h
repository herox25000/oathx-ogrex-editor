#ifndef _____Og2dPlugin_H
#define _____Og2dPlugin_H

#include "Og2dTypes.h"

namespace Og2d
{
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
	* \Desc    : ���֧�ֻ���
	*
	* \bug     : 
	*
	*/
	class Og2d_Export_API Plugin
	{
	public:
		/** ���캯��
		 *
		 * \return 
		 */
		Plugin();

		/** ��������
		 *
		 * \return 
		 */
		virtual ~Plugin();

		/** ��ȡ�����
		 *
		 * \return 
		 */
		virtual const String&	getTypeName() const = 0;

		/** ��װ���
		 *
		 */
		virtual void			install() = 0;

		/** ж�ز��
		 *
		 */
		virtual void			uninstall() = 0;
	};
}

#endif