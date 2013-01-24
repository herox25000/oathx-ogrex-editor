#ifndef _____EditorSystem_H
#define _____EditorSystem_H

namespace Ogre
{
	/**
	* \ingroup : OgreSystem
	*
	* \os&IDE  : Microsoft Windows XP (SP3)  &  Microsoft Visual C++ .NET 2008
	*
	* \VERSION : 1.0
	*
	* \date    : 2013-01-15
	*
	* \Author  : lp
	*
	* \Desc    :
	*
	* \bug     : 
	*
	* \Copyright (c) 2012 lp All rights reserved.
	*/
	class EditorSystem : public Singleton<EditorSystem>
	{
	public:
		/**
		 *
		 * \return 
		 */
		static	EditorSystem&				getSingleton();

		/**
		 *
		 * \return 
		 */
		static	EditorSystem*				getSingletonPtr();
	public:
		/**
		 *
		 * \return 
		 */
		EditorSystem();

		/**
		 *
		 * \return 
		 */
		virtual ~EditorSystem();

		/** ����ϵͳ
		 *
		 * \param pluginFileName	ϵͳ��������ļ�
		 * \param resourceFileName	ϵͳ��Դ�����ļ�
		 * \param bAutoCreateWindow 
		 * \return 
		 */
		virtual bool				createEditorSystem(const String& pluginFileName, const String& resourceFileName, bool bAutoCreateWindow);
		
		/**
		 *
		 */
		virtual void				update();

		/** ����ϵͳ
		 *
		 */
		virtual void				clearUp();

	public:
		/** ������Ⱦ����
		 *
		 * \param hWnd 
		 * \param w 
		 * \param h 
		 * \param bFullScree 
		 */
		virtual bool				createRenderWindow(const String& name, HWND hWnd, 
			int w, int h, bool bFullScreen);
		
		/** ��ȡ��Ⱦ����
		 *
		 * \return 
		 */
		virtual RenderWindow*		getRenderWindow() const;

	protected:
		Root*						m_pRoot;
		RenderWindow*				m_pRenderWindow;
	};
}

#endif