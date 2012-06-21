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
	* \Desc    : ���л�����
	*
	* \bug     : 
	*
	*/
	class Ogre_EventSet_Export_API Property
	{
	public:
		/** ���캯��
		 *
		 * \param sName			��������
		 * \param val			���Ա���ֵ
		 * \param describe		��������
		 * \param typeProperty  ��������
		 * \param bWrite		�Ƿ��д��
		 * \return 
		 */
		Property(const String& sName, const Any& anyValue, const String& describe, int typeProperty, bool bWrite=true);

		/** ��������
		 *
		 * \return 
		 */
		virtual ~Property();

		/** ������������
		 *
		 * \param sName 
		 */
		virtual	void				setName(const String& sName);

		/** ��ȡ��������
		 *
		 * \return 
		 */
		virtual	String				getName() const;

		/** ������������
		 *
		 * \param describe 
		 */
		virtual	void				setDescribe(const String& describe);
		
		/** ��ȡ��������
		 *
		 * \return 
		 */
		virtual	String				getDescribe() const;
		
		/** ��ȡ���Ա���ֵ
		 *
		 * \return 
		 */
		virtual Any&				getValue();

		/** �������Ա���ֵ
		 *
		 * \param anyValue 
		 */
		virtual	void				setValue(const Any& anyValue);

		/** ��ȡ��������
		 *
		 * \return 
		 */
		virtual int					getType() const;

		/** ����Ƿ��д��
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