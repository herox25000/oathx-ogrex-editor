#ifndef _____Og2dSceneNodeFactory_H
#define _____Og2dSceneNodeFactory_H

#include "Og2dSceneNode.h"

namespace Og2d
{
	/**
	* \ingroup : Og2d
	*
	* \os&IDE  : Microsoft Windows XP (SP2)  &  Microsoft Visual C++ .NET 2008
	*
	* \VERSION : 1.0
	*
	* \date    : 2013-01-10
	*
	* \Author  : lp
	*
	* \Desc    : 
	*
	* \bug     : 
	*
	* \Copyright (c) 2012-2013 lp All rights reserved.
	*/
	class Og2d_Export_API SceneNodeFactory
	{
	public:
		static  String		TypeName;

	public:
		/**
		 *
		 * \param szName 
		 * \return 
		 */
		SceneNodeFactory(const String& szName);

		/**
		 *
		 * \return 
		 */
		virtual ~SceneNodeFactory();

		/**
		 *
		 * \param szName 
		 * \param vPos 
		 * \param cSize 
		 * \return 
		 */
		virtual SceneNode*	create(const String& szName, const Vector2D& vPos);

		/**
		 *
		 * \param szName 
		 */
		virtual void		setName(const String& szName);

		/**
		 *
		 * \return 
		 */
		virtual String		getName() const;
	protected:
		String				m_szName;
	};
}

#endif