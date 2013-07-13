#ifndef _____Og2dTexture_H
#define _____Og2dTexture_H

#include "Og2dResource.h"
#include "Og2dMath.h"

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
	* \Desc    : ����ӿ�
	*
	* \bug     : 
	*
	*/
	class Og2d_Export_API Texture : public Resource
	{
	public:
		/**
		 *
		 * \return 
		 */
		Texture();

		/**
		 *
		 * \return 
		 */
		virtual ~Texture();
		
		/** ��ȡ����ԭʼ�ߴ磨�ļ��ߴ磩
		 *
		 * \return 
		 */
		virtual	Size			getOriginalSize() const = 0;

		/** ��ȡ�����ڴ�ߴ�
		 *
		 * \return 
		 */
		virtual	Size			getSize() const = 0;
	};
}

#endif