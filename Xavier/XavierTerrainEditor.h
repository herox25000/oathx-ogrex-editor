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

		/**
		 *
		 * \return 
		 */
		virtual TerrainGroupServer*	getTerrainGroupServer();

		/**
		 *
		 * \param index 
		 * \param texture 
		 * \return 
		 */
		virtual	bool				createTerrainBlend(const int index, const String& texture);

		/**
		 *
		 * \param vPos 
		 * \return 
		 */
		virtual	bool				OnLButtonDown(const Vector2& vPos);

		/**
		 *
		 * \param vPos 
		 * \return 
		 */
		virtual	bool				OnMouseMove(const Vector2& vPos);

		/**
		 *
		 * \param vPos 
		 * \return 
		 */
		virtual	bool				OnLButtonUp(const Vector2& vPos);

	protected:
		Terrain*					m_pTerrain;
		int							m_nBlend;
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
