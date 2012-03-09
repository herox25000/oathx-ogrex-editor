#ifndef _____OgreKernel_H
#define _____OgreKernel_H

#include "OgreKernelPrerequisites.h"
#include "Ogre.h"

namespace Ogre
{
	// ����ռ�
	class WorldSpace;

	/**
	* \ingroup : OgreKernel
	*
	* \os&IDE  : Microsoft Windows XP (SP3)  &  Microsoft Visual C++ .NET 2008 & ogre1.8
	*
	* \VERSION : 1.0
	*
	* \@date   : 2012-03-09
	*
	* \Author  : lp
	*
	* \Desc    : 
	*
	* \bug     : 
	*
	*/
	class Ogre_Export_API OgreKernel : public Singleton<OgreKernel>
	{
	public:
		/**	��ȡ����
		 *
		 * \return 
		 */
		static	OgreKernel&			getSingleton();

		/** ��ȡ����ָ��
		 *
		 * \return 
		 */
		static	OgreKernel*			getSingletonPtr();

	public:
		/**	���캯��
		 *
		 * \return 
		 */
		OgreKernel();

		/** ��������
		 *
		 * \param void 
		 * \return 
		 */
		virtual ~OgreKernel(void);

		/**	��������
		 *
		 * \param sPluginPath				��������ļ�·��
		 * \param sResourceConfigFilePath	��Դ�����ļ�·��
		 * \return 
		 */
		virtual bool				createKernel(const String& sPluginPath, const String& sResourceConfigFilePath);

		/** ��Ⱦ
		 *
		 */
		virtual void				renderOneFrame();

		/** �����ں�
		 *
		 */
		virtual void				destroyKernel();
		
		/** ������Ⱦ����
		 *
		 * \param hWnd						���ھ�� ��ΪNULL�����ں��Զ�������Ⱦ����
		 * \param w							���ڿ�
		 * \param h							���ڸ�
		 * \param bFullScreen				�Ƿ�ȫ��
		 * \param sName						��������
		 * \return 
		 */
		virtual bool				createRenderWindow(HWND hWnd, int w, int h, 
			bool bFullScreen, const String& sName);

		/** ��ȡ��Ⱦ����
		 *
		 * \return 
		 */
		virtual RenderWindow*		getRenderWindow() const;

		/** ��Ⱦ���ڸı�
		 *
		 */
		virtual void				windowMovedOrResized();
	protected:
		Ogre::Root*					m_pRoot;
		Ogre::RenderWindow*			m_pRenderWindow;
		WorldSpace*					m_pWorldSpace;
	};
}

#endif

