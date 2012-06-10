#ifndef _____XavierViewportEditor_H
#define _____XavierViewportEditor_H

#include "XavierEditor.h"

namespace Ogre
{
	struct SViewportServerAdp;

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
	class XavierViewportEditor : public XavierEditor
	{
	public:
		/**
		 *
		 * \param typeName 
		 * \param adp 
		 * \param propertySetFile 
		 * \return 
		 */
		XavierViewportEditor(const String& typeName, const SViewportServerAdp& adp, const String& propertySetFile);

		/**
		 *
		 * \return 
		 */
		virtual ~XavierViewportEditor();

		/**
		 *
		 */
		virtual	void				windowMovedOrResized();
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
	class XavierViewportEditorFactory : public XavierEditorFactory
	{
	public:
		static const String					FACTORY_NAME;

	public:
		/**
		 *
		 * \param typeName 
		 * \return 
		 */
		XavierViewportEditorFactory();

		/**
		 *
		 * \return 
		 */
		virtual ~XavierViewportEditorFactory();

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