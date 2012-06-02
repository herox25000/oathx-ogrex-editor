#ifndef _____OgreServerWorldSpace_H
#define _____OgreServerWorldSpace_H

#include "OgreServer.h"

namespace Ogre
{
	/**
	* \ingroup : System
	*
	* \os&IDE  : Microsoft Windows XP (SP3)  &  Microsoft Visual C++ .NET 2008 & ogre1.8
	*
	* \VERSION : 1.0
	*
	* \@date   : 2012-04-08
	*
	* \Author  : lp
	*
	* \Desc    : 世界服务
	*
	* \bug     : 
	*
	*/
	class Ogre_System_Export_API WorldSpaceServer : public Server
	{
	public:
		/**
		 *
		 * \return 
		 */
		WorldSpaceServer(const String& typeName, const String& name, const SceneTypeMask& typeMask, const ColourValue& clrAmbientLight);

		/**
		 *
		 * \return 
		 */
		virtual ~WorldSpaceServer();

		/**
		 *
		 * \param name 
		 */
		virtual void					setName(const String& name);

		/**
		 *
		 * \return 
		 */
		virtual String					getName() const;

		/**
		 *
		 * \param clrAmbientLight 
		 */
		virtual void					setAmbientLight(const ColourValue& clrAmbientLight);

		/**
		 *
		 * \return 
		 */
		virtual	ColourValue				getAmbientLight() const;

		/**
		 *
		 * \return 
		 */
		virtual SceneManager*			getSceneManager() const;
	protected:
		SceneManager*					m_pSceneManager;
		String							m_name;
		
	};

	// 世界空间创建参数
	struct SWorldSpaceServerAdp : public SSAdp
	{
		String							name;
		SceneTypeMask					typeMask;
		ColourValue						clrAmbientLight;
	};

	/**
	* \ingroup : System
	*
	* \os&IDE  : Microsoft Windows XP (SP3)  &  Microsoft Visual C++ .NET 2008 & ogre1.8
	*
	* \VERSION : 1.0
	*
	* \@date   : 2012-04-09
	*
	* \Author  : lp
	*
	* \Desc    : 
	*
	* \bug     : 
	*
	*/
	class Ogre_System_Export_API WorldSpaceServerFactory : public ServerFactory
	{
	public:
		static const String			FactoryTypeName;

		/**
		 *
		 * \param typeName 
		 * \return 
		 */
		WorldSpaceServerFactory();

		/**
		 *
		 * \return 
		 */
		virtual ~WorldSpaceServerFactory();

		/**
		 *
		 * \return 
		 */
		virtual String				getTypeName() const;

		/**
		 *
		 * \param pAdp 
		 * \param pParent 
		 * \return 
		 */
		virtual Server*				createServer(const SSAdp& ssadp);
	};

}

#endif