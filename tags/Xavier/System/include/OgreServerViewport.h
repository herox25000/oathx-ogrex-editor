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
		/**	���캯��
		 *
		 * \param pWindow		��Ⱦ����
		 * \param pCamera		�����
		 * \param background	������ɫ
		 * \return 
		 */
		ViewportServer(const String& typeName, Camera* pCamera, const ColourValue& background);

		/** ��������
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

		/** �����ƶ����߸ı��С
		 *
		 */
		virtual void					windowMovedOrResized();
		
	protected:
		// �ӿ�
		Viewport*						m_pViewPort;
		Camera*							m_pCamera;
	};

	//* �ӿڴ�������
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