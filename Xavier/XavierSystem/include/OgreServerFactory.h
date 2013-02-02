#ifndef _____OgreServerFactory_H
#define _____OgreServerFactory_H

namespace Ogre
{
	/**
	* \ingroup : XavierSystem
	*
	* \os&IDE  : Microsoft Windows XP (SP2)  &  Microsoft Visual C++ .NET 2008
	*
	* \VERSION : 1.0
	*
	* \date    : 2013-01-31
	*
	* \Author  : lp
	*
	* \Desc    : 
	*
	* \bug     : 
	*
	* \Copyright (c) 2012 lp All rights reserved.
	*/
	class Ogre_System_Export_API ServerFactory
	{
	public:
		/**
		 *
		 * \param typeName 
		 * \return 
		 */
		ServerFactory(const String& typeName);

		/**
		 *
		 * \return 
		 */
		virtual ~ServerFactory();
		
		/**
		 *
		 * \param ssadp 
		 * \param pParent 
		 * \return 
		 */
		virtual	Server*			createServer(const SServerAdp& ssadp, Server* pParent) = 0;

		/**
		 *
		 * \param typeName 
		 */
		virtual	void			setTypeName(const String& typeName);

		/**
		 *
		 * \return 
		 */
		virtual	const String&	getTypeName() const;
	protected:
		String					m_TypeName;
	};
}

#endif