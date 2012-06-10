#pragma once

#include "XavierEditor.h"

namespace Ogre
{
	class Terrain;
	
	struct STerrainGroupServerAdp;
	
	/**
	* \ingroup : Xavier
	*
	* \os&IDE  : Microsoft Windows XP (SP3)  &  Microsoft Visual C++ .NET 2008 & ogre1.8
	*
	* \VERSION : 1.0
	*
	* \@date   : 2012-06-03
	*
	* \Author  : lp
	*
	* \Desc    : 
	*
	* \bug     : 
	*
	*/
	class XavierTerrainEditor : public XavierEditor
	{
	public:
		/**
		 *
		 * \param typeName 
		 * \return 
		 */
		XavierTerrainEditor(const String& typeName, const STerrainGroupServerAdp& adp, const String& propertySetFile);

		/**
		 *
		 * \return 
		 */
		virtual ~XavierTerrainEditor();

		/** ÃÌº”ªÊ÷∆≤„
		 *
		 * \param nID 
		 * \param texture 
		 * \param normal 
		 * \param fWorldSize 
		 * \return 
		 */
		virtual	int					addLayer( const String& texture,  const String& normal, 
			float fWorldSize);

	protected:
		Terrain*					m_pTerrain;
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
	class XavierTerrainEditorFactory : public XavierEditorFactory
	{
	public:
		static const String					FACTORY_NAME;

	public:
		/**
		 *
		 * \param typeName 
		 * \return 
		 */
		XavierTerrainEditorFactory();

		/**
		 *
		 * \return 
		 */
		virtual ~XavierTerrainEditorFactory();

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
