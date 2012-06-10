#ifndef _____XavierBaseGridEditor_H
#define _____XavierBaseGridEditor_H

#include "XavierEditor.h"

namespace Ogre
{
	struct SBaseGridServerAdp;

	/**
	* \ingroup : Xavier
	*
	* \os&IDE  : Microsoft Windows XP (SP3)  &  Microsoft Visual C++ .NET 2008 & ogre1.8
	*
	* \VERSION : 1.0
	*
	* \@date   : 2012-06-10
	*
	* \Author  : lp
	*
	* \Desc    : 
	*
	* \bug     : 
	*
	*/
	class XavierBaseGridEditor : public XavierEditor
	{
	public:
		/**
		 *
		 * \param typeName 
		 * \param adp 
		 * \param propertySetFile 
		 * \return 
		 */
		XavierBaseGridEditor(const String& typeName, const SBaseGridServerAdp& adp, const String& propertySetFile);

		/**
		 *
		 * \return 
		 */
		virtual ~XavierBaseGridEditor();
	};


	/**
	* \ingroup : Xavier
	*
	* \os&IDE  : Microsoft Windows XP (SP3)  &  Microsoft Visual C++ .NET 2008 & ogre1.8
	*
	* \VERSION : 1.0
	*
	* \@date   : 2012-06-09
	*
	* \Author  : lp
	*
	* \Desc    : 
	*
	* \bug     : 
	*
	*/
	class XavierBaseGridEditorFactory : public XavierEditorFactory
	{
	public:
		static const String					FACTORY_NAME;

	public:
		/**
		 *
		 * \param typeName 
		 * \return 
		 */
		XavierBaseGridEditorFactory();

		/**
		 *
		 * \return 
		 */
		virtual ~XavierBaseGridEditorFactory();

		/**
		 *
		 * \return 
		 */
		virtual const String&	getTypeName() const;

		/**
		 *
		 * \param pNode 
		 * \return 
		 */
		virtual	XavierEditor*	create(const SSAdp& ssadp);
	};
}

#endif