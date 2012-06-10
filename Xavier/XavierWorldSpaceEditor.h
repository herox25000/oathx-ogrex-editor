#ifndef _____XavierWorldSpaceEditor_H
#define _____XavierWorldSpaceEditor_H

#include "XavierEditor.h"

namespace Ogre
{
	struct SWorldSpaceServerAdp;

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
	* \Desc    :  ¿ΩÁ±‡º≠
	*
	* \bug     : 
	*
	*/
	class XavierWorldSpaceEditor : public XavierEditor
	{
	public:
		/**
		 *
		 * \param typeName 
		 * \return 
		 */
		XavierWorldSpaceEditor(const String& typeName, const SWorldSpaceServerAdp& adp, const String& propertySetFile);

		/**
		 *
		 * \return 
		 */
		virtual ~XavierWorldSpaceEditor();

		/**
		 *
		 * \param args 
		 * \return 
		 */
		virtual	bool		onPropertyChanaged(const EventArgs& args);
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
	class XavierWorldSpaceEditorFactory : public XavierEditorFactory
	{
	public:
		static const String					FACTORY_NAME;

	public:
		/**
		 *
		 * \param typeName 
		 * \return 
		 */
		XavierWorldSpaceEditorFactory();

		/**
		 *
		 * \return 
		 */
		virtual ~XavierWorldSpaceEditorFactory();

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