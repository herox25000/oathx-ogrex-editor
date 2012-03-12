#ifndef _____OgreProperty_H
#define _____OgreProperty_H

#ifndef cmpXML
#define cmpXML(a, b) !strcmp(a, b)
#endif

namespace Ogre
{
	struct PropertyItem
	{
		String		Decribe;
		String		Name;
		Any			Value;
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
	class Ogre_EditSystem_Export_API Property
	{
	public:
		/**
		 *
		 * \param sName 
		 * \param val 
		 * \param describe 
		 * \return 
		 */
		Property(const String& sName, const Any& anyValue, const String& describe);

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
	protected:
		String						m_decribe;
		String						m_sName;
		Any							m_anyValue;
	};

	/**
	* \ingroup : OgreEditSystem
	*
	* \os&IDE  : Microsoft Windows XP (SP3)  &  Microsoft Visual C++ .NET 2008 & ogre1.8
	*
	* \VERSION : 1.0
	*
	* \@date   : 2012-03-12
	*
	* \Author  : lp
	*
	* \Desc    : 
	*
	* \bug     : 
	*
	*/
	class Ogre_EditSystem_Export_API PropertySet
	{
		typedef HashMap<String, Property*> HashProperty;
	public:
		/**
		 *
		 * \param sName 
		 * \param describe 
		 * \return 
		 */
		PropertySet();

		/**
		 *
		 * \return 
		 */
		virtual ~PropertySet();

		/**
		 *
		 * \param name 
		 * \param Value 
		 * \param describe 
		 */
		virtual	void				addProperty(const String& name, Any Value, const String& describe);

		/**
		 *
		 * \param name 
		 */
		virtual void				delProperty(const String& name);

		/**
		 *
		 * \param name 
		 * \return 
		 */
		virtual Property*			getProperty(const String& name);

		/**
		 *
		 * \param name 
		 * \param anyValue 
		 */
		virtual	void				setPropertyValue(const String& name, const Any& anyValue);

		/**
		 *
		 * \param name 
		 * \return 
		 */
		virtual Any&				getPropertyValue(const String& name);
	protected:
		HashProperty				m_HashProperty;
	};
}

#endif