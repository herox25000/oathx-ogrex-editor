#ifndef _____OgreProperty_H
#define _____OgreProperty_H

#ifndef cmpXML
#define cmpXML(a, b) !strcmp(a, b)
#endif

namespace Ogre
{
	//////////////////////////////////////////////////////////////////////////
	// XML ÎÄ¼þÊôÐÔ
	//////////////////////////////////////////////////////////////////////////
	class Ogre_EditSystem_Export_API Property
	{
	public:
		/**
		*
		* \return 
		*/
		Property();
		
		/**
		*
		* \return 
		*/		
		virtual ~Property();

	public:
		/**
		*
		* \return 
		*/
		virtual	float				getValueDouble(const String& sName);
		
		/**
		 *
		 * \param sName 
		 * \param fVal 
		 */
		virtual	void				setValueDouble(const String& sName, float fVal);

		/**
		*
		* \return 
		*/
		virtual int					getValueIntger(const String& sName);

		/**
		 *
		 * \param sName 
		 * \param nVal 
		 */
		virtual	void				setValueIntger(const String& sName, int nVal);
		
		/**
		*
		* \return 
		*/		
		virtual Vector2				getValueCPoint(const String& sName);

		/**
		 *
		 * \param sName 
		 * \param vPt 
		 */
		virtual	void				setValueCPoint(const String& sName, Vector2 vPt);

		/**
		 *
		 * \param sName 
		 * \return 
		 */
		virtual	Vector3				getValueVector(const String& sName);

		/**
		 *
		 * \param sName 
		 * \param vPos 
		 */
		virtual	void				setValueVector(const String& sName, Vector3 vPos);

		/**
		 *
		 * \param sName 
		 * \return 
		 */
		virtual ColourValue			getValueColour(const String& sName);
		
		/**
		 *
		 * \param sName 
		 * \param clrVal 
		 */
		virtual	void				setValueColour(const String& sName, ColourValue clrVal);
		/**
		*
		* \return 
		*/		
		virtual Size				getValueCCSize(const String& sName);
		
		/**
		 *
		 * \param sName 
		 * \param szVal 
		 */
		virtual	void				setValueCCSize(const String& sName, Size szVal);

		/**
		*
		* \return 
		*/	
		virtual	String				getValueString(const String& sName);
		
		/**
		 *
		 * \param sName 
		 * \param sVal 
		 */
		virtual	void				setValueString(const String& sName, String sVal);

		/**
		*
		* \return 
		*/
		virtual void				addProperty(Property* pParent, const String& sName, const String& val);

		/**
		 *
		 * \param sName 
		 */
		virtual	void				delProperty(const String& sName);

	protected:
		HashMap<String, String>		mSSValue;
		Property*					mParent;
	};
}

#endif