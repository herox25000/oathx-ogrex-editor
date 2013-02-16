#ifndef _____OgreProperty_H
#define _____OgreProperty_H

#include "OgreEventArgs.h"
#include "OgreEventSet.h"

namespace Ogre
{
	enum {
		PVT_SHORT			= 0,
		PVT_USHORT			= 1,
		PVT_INT				= 2,
		PVT_UINT			= 3,
		PVT_LONG			= 4, 
		PVT_ULONG			= 5,
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
		PVT_FOGMODE			= 17,

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
	* \Desc    : 
	*
	* \bug     : 
	*
	*/
	class Ogre_EventSet_Export_API Property
	{
	public:
		/**
		 *
		 * \param sName 
		 * \param val 
		 * \param describe 
		 * \return 
		 */
		Property(const String& sName, const Any& anyValue, const String& describe, int typeProperty, bool bWrite=true);

		/**
		 *
		 * \return 
		 */
		virtual ~Property();

		/**
		 *
		 * \param sName 
		 */
		virtual	void				setName(const String& sName);

		/**
		 *
		 * \return 
		 */
		virtual	String				getName() const;

		/**
		 *
		 * \param describe 
		 */
		virtual	void				setDescribe(const String& describe);
		
		/**
		 *
		 * \return 
		 */
		virtual	String				getDescribe() const;
		
		/**
		 *
		 * \return 
		 */
		virtual Any&				getValue();

		/**
		 *
		 * \param anyValue 
		 */
		virtual	void				setValue(const Any& anyValue);

		/**
		 *
		 * \return 
		 */
		virtual int					getType() const;

		/**
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