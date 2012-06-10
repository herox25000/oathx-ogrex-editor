#pragma once

#include "OgreString.h"

namespace Ogre
{
	class EventArgs;
	class Server;
	
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
	class XavierEditor
	{
	public:
		/**
		 *
		 * \param typeName 
		 * \return 
		 */
		XavierEditor(const String& typeName, const String& propertySetFile);

		/**
		 *
		 * \return 
		 */
		virtual ~XavierEditor();		
		/**
		 *
		 * \return 
		 */
		virtual	const String&		getTypeName() const;

		/**
		 *
		 * \param propertySetFile 
		 */
		virtual	void				loadProperty();
		
		/**
		 *
		 * \return 
		 */
		virtual HashPropertyIter	getHashPropertyIter();

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
		virtual	bool				OnLButtonUp(const Vector2& vPos);

		/**
		 *
		 * \param vPos 
		 * \return 
		 */
		virtual	bool				OnRButtonDown(const Vector2& vPos);

		/**
		 *
		 * \param vPos 
		 * \return 
		 */
		virtual	bool				OnRButtonUp(const Vector2& vPos);

		/**
		 *
		 * \param vPos 
		 * \return 
		 */
		virtual	bool				OnMouseMove(const Vector2& vPos);

		/**
		 *
		 * \param zDelta 
		 * \param vPos 
		 * \return 
		 */
		virtual	bool				OnMouseWheel(float zDelta, const Vector2& vPos);
	protected:
		String						m_typeName;
		String						m_propertySetFile;
		Server*						m_pServer;
	};

	struct SSAdp;

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
	class XavierEditorFactory
	{
	public:
		/**
		 *
		 * \param typeName 
		 * \return 
		 */
		XavierEditorFactory();

		/**
		 *
		 * \return 
		 */
		virtual ~XavierEditorFactory();

		/**
		 *
		 * \return 
		 */
		virtual const String&	getTypeName() const = 0;
		
		/**
		 *
		 * \param name 
		 */
		virtual	void			setPropertySetFile(const String& name);

		/**
		 *
		 * \param pNode 
		 * \return 
		 */
		virtual	XavierEditor*	create(const SSAdp& ssadp) = 0;
	protected:
		String					m_PropertySetFile;
	};
}
