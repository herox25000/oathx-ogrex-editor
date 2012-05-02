#ifndef _____OgreProperty_H
#define _____OgreProperty_H

#include "OgreEventArgs.h"
#include "OgreEventSet.h"

namespace Ogre
{
	enum {
		PROPERTY_SHORT			= 0,
		PROPERTY_UNSIGNED_SHORT = 1,
		PROPERTY_INT			= 2,
		PROPERTY_UNSIGNED_INT	= 3,
		PROPERTY_LONG			= 4, 
		PROPERTY_UNSIGNED_LONG	= 5,
		PROPERTY_REAL			= 6,
		PROPERTY_STRING			= 7,
		PROPERTY_VECTOR2		= 8, 
		PROPERTY_VECTOR3		= 9,
		PROPERTY_VECTOR4		= 10, 
		PROPERTY_COLOUR			= 11,
		PROPERTY_BOOL			= 12,
		PROPERTY_QUATERNION		= 13, 
		PROPERTY_MATRIX3		= 14,
		PROPERTY_MATRIX4		= 15, 
		PROPERTY_POLYGONMODE	= 16,

		PROPERTY_UNKNOWN		= 999
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
	class Ogre_System_Export_API Property
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