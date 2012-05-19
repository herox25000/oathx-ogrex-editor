#ifndef _____OgreServerBaseGrid_H
#define _____OgreServerBaseGrid_H

#include "OgreServer.h"

namespace Ogre
{
	// 格子线渲染层
	enum{
		GRID_LINE_BEHIND,
		GRID_LINE_INFRONT
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
	class Ogre_System_Export_API BaseGridServer : public Server
	{
	public:
		/**
		 *
		 * \param fWidth 
		 * \param fSize 
		 * \param fDepth 
		 * \return 
		 */
		BaseGridServer(const String& typeName, WorldSpaceServer* pWorldSpace, Real fWidth, Real fSize, Real fDepth);

		/**
		 *
		 * \param void 
		 * \return 
		 */
		virtual ~BaseGridServer(void);
	
		/**
		 *
		 */
		virtual void				show();

		/**
		 *
		 * \return 
		 */
		virtual	bool				isVisible() const;

		/**
		 *
		 */
		virtual void				hide();

		/**
		 *
		 * \param fSize 
		 */
		virtual	void				setSize(float fSize);
		
		/**
		 *
		 * \return 
		 */
		virtual float				getSize() const;

		/**
		 *
		 * \param fDepth 
		 */
		virtual	void				setDepth(float fDepth);
		
		/**
		 *
		 * \return 
		 */
		virtual	float				getDepth() const;

		/**
		 *
		 * \param fWidth 
		 */
		virtual	void				setWidth(float fWidth);
		
		/**
		 *
		 */
		virtual	void				getWidth() const;

		/**
		 *
		 */
		virtual	void				invalidate();
	protected:
		/** 创建格子
		 *
		 */
		virtual void				createGird();

		/**
		 *
		 */
		virtual void				destroy();

		/**
		 *
		 * \param args 
		 * \return 
		 */
		virtual bool				onPropertyChanaged(const EventArgs& args);
	protected:
		WorldSpaceServer*			m_pWorldSpace;
		Real						m_fWidth;
		Real						m_fSize;
		Real						m_fDepth;
		SceneNode*					m_pLine;
		ManualObject*				m_pGrid;
		bool						m_bDisplay;
	};

	//////////////////////////////////////////////////////////////////////////
	struct SBaseGridServerAdp : public SSAdp
	{
		Real						fWidth;
		Real						fSize;
		Real						fDepth;
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
	class Ogre_System_Export_API BaseGridServerFactory : public ServerFactory
	{
	public:
		static const String			FactoryTypeName;

		/**
		 *
		 * \return 
		 */
		BaseGridServerFactory();

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