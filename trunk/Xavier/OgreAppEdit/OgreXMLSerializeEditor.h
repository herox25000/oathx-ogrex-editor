#ifndef _____OgreXMLSerializeEditor_H
#define _____OgreXMLSerializeEditor_H

#include "OgreBaseEditor.h"

namespace Ogre
{
	class XMLSerialize;

	/**
	* \ingroup : OgreSystem
	*
	* \os&IDE  : Microsoft Windows XP (SP3)  &  Microsoft Visual C++ .NET 2008 & ogre1.8
	*
	* \VERSION : 1.0
	*
	* \@date   : 2012-03-21
	*
	* \Author  : lp
	*
	* \Desc    : 
	*
	* \bug     : 
	*
	*/
	class OgreAppEdit_Export_API XMLSerializeCreateEventArgs : public EventArgs
	{
	public:
		/**
		 *
		 * \param pThis 
		 * \return 
		 */
		XMLSerializeCreateEventArgs(XMLSerialize* pThis);
		
		/**
		 *
		 * \return 
		 */
		virtual ~XMLSerializeCreateEventArgs();

	public:
		// ÎÄµµÖ¸Õë
		XMLSerialize*			pSerialize;
	};

	/**
	* \ingroup : OgreAppEdit
	*
	* \os&IDE  : Microsoft Windows XP (SP3)  &  Microsoft Visual C++ .NET 2008 & ogre1.8
	*
	* \VERSION : 1.0
	*
	* \@date   : 2012-03-21
	*
	* \Author  : lp
	*
	* \Desc    : 
	*
	* \bug     : 
	*
	*/
	class OgreAppEdit_Export_API XMLSerializeEditor : public BaseEditor
	{
		typedef HashMap<String, XMLSerialize*> StringXMLSerialize;
	public:
		// Namespace for global events
		static const String			EventNamespace;
		static const String			EventXMLSerializeCreated;
	public:
		/**
		 *
		 * \param void 
		 * \return 
		 */
		XMLSerializeEditor();

		/**
		 *
		 * \param void 
		 * \return 
		 */
		virtual ~XMLSerializeEditor(void);
		
		/**
		 *
		 * \param sPath 
		 * \param sName 
		 * \return 
		 */
		virtual XMLSerialize*		createXMLSerialize(const String& sPath, const String& sName);

		/**
		 *
		 * \param sName 
		 */
		virtual void				destroyXMLSerialize(const String& sName);

		/**
		 *
		 */
		virtual void				clearAllXMLSerialize();
	protected:
		StringXMLSerialize			m_vXMLSerialize;
	};
	
	//
	struct SXMLSerializeCreateParam : public SBaseCreateParam
	{

	};

	/**
	* \ingroup : OgreAppEdit
	*
	* \os&IDE  : Microsoft Windows XP (SP3)  &  Microsoft Visual C++ .NET 2008 & ogre1.8
	*
	* \VERSION : 1.0
	*
	* \@date   : 2012-03-21
	*
	* \Author  : lp
	*
	* \Desc    : 
	*
	* \bug     : 
	*
	*/
	class OgreAppEdit_Export_API XMLSerializeEditorFactory : public BaseEditorFactory
	{
	public:
		/**
		 *
		 * \return 
		 */
		XMLSerializeEditorFactory();

		/**
		 *
		 * \return 
		 */
		virtual ~XMLSerializeEditorFactory();

		/**
		 *
		 * \param pm 
		 * \return 
		 */
		virtual BaseEditor*				create(const SBaseCreateParam* pm);
	};
}

#endif
