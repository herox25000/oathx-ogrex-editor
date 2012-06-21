#ifndef _____OgreProperty_H
#define _____OgreProperty_H

#include "OgreEventArgs.h"
#include "OgreEventSet.h"

namespace Ogre
{
	enum {
		PVT_SHORT			= 0,
		PVT_UNSIGNED_SHORT	= 1,
		PVT_INT				= 2,
		PVT_UNSIGNED_INT	= 3,
		PVT_LONG			= 4, 
		PVT_UNSIGNED_LONG	= 5,
		PVT_REAL			= 6,
		PVT_STRING			= 7,
		PVT_VECTOR2			= 8, 
		PVT_VECTOR3			= 9,
		PVT_VECTOR4			= 10, 
		PVT_COLOUR			= 11,
		PVT_BOOL			= 12,
		PVT_QUATERNION		= 13, 
		PVT_MATRIX3			= 14,
		PVT_MATRIX4			= 15, 
		PVT_POLYGONMODE		= 16,

		PVT_UNKNOWN			= 999
	};

	/**
	* \ingroup : OgreEditSystem
	*
	* \os&IDE  : Microsoft Windows XP (SP2)  &  Microsoft Visual C++ .NET 2008
	*
	* \VERSION : 1.0
	*
	* \date    : 2012-03-12
	*
	* \Author  : lp
	*
	* \Desc    : 序列化属性
	*
	* \bug     : 
	*
	*/
	class Ogre_EventSet_Export_API Property
	{
	public:
		/** 构造函数
		 *
		 * \param sName			属性名称
		 * \param val			属性变量值
		 * \param describe		属性描述
		 * \param typeProperty  属性类型
		 * \param bWrite		是否可写入
		 * \return 
		 */
		Property(const String& sName, const Any& anyValue, const String& describe, int typeProperty, bool bWrite=true);

		/** 析构函数
		 *
		 * \return 
		 */
		virtual ~Property();

		/** 设置属性名称
		 *
		 * \param sName 
		 */
		virtual	void				setName(const String& sName);

		/** 获取属性名称
		 *
		 * \return 
		 */
		virtual	String				getName() const;

		/** 设置属性描述
		 *
		 * \param describe 
		 */
		virtual	void				setDescribe(const String& describe);
		
		/** 获取属性描述
		 *
		 * \return 
		 */
		virtual	String				getDescribe() const;
		
		/** 获取属性变量值
		 *
		 * \return 
		 */
		virtual Any&				getValue();

		/** 设置属性变量值
		 *
		 * \param anyValue 
		 */
		virtual	void				setValue(const Any& anyValue);

		/** 获取属性类型
		 *
		 * \return 
		 */
		virtual int					getType() const;

		/** 检查是否可写入
		 *
		 * \return 
		 */
		virtual bool				canWrite() const;
	protected:
		String						m_decribe;
		String						m_sName;
		Any							m_anyValue;
		int							m_type;
		bool						m_bWrite;
	};
}

#endif