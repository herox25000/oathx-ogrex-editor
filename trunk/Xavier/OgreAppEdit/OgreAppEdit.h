#ifndef _____OgreAppEdit_H
#define _____OgreAppEdit_H

#include "OgreSingleton.h"
#include "OgreBaseEditor.h"

namespace Ogre
{
	class EditorPlugin;

	/**
	* \ingroup : OgreEditSystem
	*
	* \os&IDE  : Microsoft Windows XP (SP3)  &  Microsoft Visual C++ .NET 2008 & ogre1.8
	*
	* \VERSION : 1.0
	*
	* \@date   : 2012-03-11
	*
	* \Author  : lp
	*
	* \Desc    : 
	*
	* \bug     : 
	*
	*/
	class OgreAppEdit_Export_API AppEdit : public BaseEditor, public Singleton<AppEdit>
	{
		// �༭�����
		typedef std::vector<EditorPlugin*>				VEditorPlugin;
		typedef std::vector<DynLib*>					VDynLib;
	public:
		/** ��ȡ�༭ϵͳ
		 *
		 * \return 
		 */
		static	AppEdit&			getSingleton();

		/** ��ȡ�༭ϵͳ
		 *
		 * \return 
		 */
		static	AppEdit*			getSingletonPtr();

	public:
		/** ���캯��
		 *
		 * \param void 
		 * \return 
		 */
		AppEdit(void);

		/** ��������
		 *
		 * \param void 
		 * \return 
		 */
		virtual ~AppEdit(void);

	public:
		/** �����༭ϵͳ
		 *
		 * \param pluginFileName	
		 * \param resourceFileName  
		 * \return 
		 */
		virtual	bool				createSystem(const String& pluginFileName, const String& resourceFileName);
		
		/** ������Ⱦ����
		 *
		 * \param hWnd 
		 * \param w 
		 * \param h 
		 * \param bFullScree 
		 */
		virtual void				createRenderWindow(HWND hWnd, int w, int h, bool bFullScreen);
		
		/** ��ȡ��Ⱦ����
		 *
		 * \return 
		 */
		virtual RenderWindow*		getRenderWindow() const;

		/** ϵͳ����
		 *
		 */
		virtual void				update();

		/** ���ر༭���
		 *
		 * \param name 
		 */
		virtual void				loadPlugin(const String& name);

		/** ж�ر༭���
		 *
		 * \param name 
		 */
		virtual void				unloadPlugin(const String& name);

		/** ��װ�༭���
		 *
		 * \param pPlugin 
		 */
		virtual void				installPlugin(EditorPlugin* pPlugin);

		/** ɾ���༭���
		 *
		 * \param pPlugin 
		 */
		virtual void				uninstallPlugin(EditorPlugin* pPlugin);

		/**
		 *
		 */
		virtual void				clearPlugin();

		/** ���ٱ༭ϵͳ
		 *
		 */
		virtual void				destroySystem();
		
	protected:
		Root*						m_pRoot;			// ogre root object
		RenderWindow*				m_pRenderWindow;
		VEditorPlugin				m_vPlugin;
		VDynLib						m_vDynlib;
	};
}

#endif
