#ifndef _____OgreServerViewport_H
#define _____OgreServerViewport_H

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
	* \@date   : 2012-04-16
	*
	* \Author  : lp
	*
	* \Desc    : 
	*
	* \bug     : 
	*
	*/
	class Ogre_System_Export_API ViewportServer : public Server
	{		
	public:
		/**	构造函数
		 *
		 * \param pWindow		渲染窗口
		 * \param pCamera		摄像机
		 * \param background	背景颜色
		 * \return 
		 */
		ViewportServer(const String& typeName, Camera* pCamera, const ColourValue& background);

		/** 析构函数
		 *
		 * \param void 
		 * \return 
		 */
		virtual ~ViewportServer(void);
		
		/**
		 *
		 * \return 
		 */
		virtual Viewport*				getViewPort() const;

		/**
		 *
		 * \param clrBackground 
		 */
		virtual	void					setBackgroundColour(const ColourValue& clrBackground);

		/**
		 *
		 * \return 
		 */
		virtual	ColourValue				getBackgroundColour() const;

		/** 窗口移动或者改变大小
		 *
		 */
		virtual void					windowMovedOrResized();
		
	protected:
		// 视口
		Viewport*						m_pViewPort;
		Camera*							m_pCamera;
	};

	//* 视口创建参数
	struct SViewportServerAdp : public SSAdp
	{
		ColourValue						background;
	};


	/**
	* \ingroup : System
	*
	* \os&IDE  : Microsoft Windows XP (SP3)  &  Microsoft Visual C++ .NET 2008 & ogre1.8
	*
	* \VERSION : 1.0
	*
	* \@date   : 2012-04-16
	*
	* \Author  : lp
	*
	* \Desc    : 
	*
	* \bug     : 
	*
	*/
	class Ogre_System_Export_API ViewportServerFactory : public ServerFactory
	{
	public:
		static const String				FactoryTypeName;
	
		/**
		 *
		 * \return 
		 */
		ViewportServerFactory();

		/**
		 *
		 * \return 
		 */
		virtual ~ViewportServerFactory();

		/**
		 *
		 * \return 
		 */
		virtual String				getTypeName() const;

		/**
		 *
		 * \param pm 
		 * \return 
		 */
		virtual Server*				createServer(const SSAdp& ssadp);
	};
}

#endif