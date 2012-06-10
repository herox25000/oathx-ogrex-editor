#ifndef _____XavierTerrainPageEditor_H
#define _____XavierTerrainPageEditor_H

#include "XavierEditor.h"

namespace Ogre
{
	struct STerrainPageServerAdp;

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
	class XavierTerrainPageEditor : public XavierEditor
	{
	public:
		/**
		 *
		 * \param typeName 
		 * \param adp 
		 * \param propertySetFile 
		 * \return 
		 */
		XavierTerrainPageEditor(const String& typeName, const STerrainPageServerAdp& adp, const String& propertySetFile);

		/**
		 *
		 * \return 
		 */
		virtual ~XavierTerrainPageEditor();
	};

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
	class XavierTerrainPageEditorFactory : public XavierEditorFactory
	{
	public:
		static const String					FACTORY_NAME;

	public:
		/**
		 *
		 * \param typeName 
		 * \return 
		 */
		XavierTerrainPageEditorFactory();

		/**
		 *
		 * \return 
		 */
		virtual ~XavierTerrainPageEditorFactory();

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