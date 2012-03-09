#ifndef _____OgreKernel_H
#define _____OgreKernel_H

#include "OgreKernelPrerequisites.h"
#include "Ogre.h"

namespace Ogre
{
	// 世界空间
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
		/**	获取单件
		 *
		 * \return 
		 */
		static	OgreKernel&			getSingleton();

		/** 获取单件指针
		 *
		 * \return 
		 */
		static	OgreKernel*			getSingletonPtr();

	public:
		/**	构造函数
		 *
		 * \return 
		 */
		OgreKernel();

		/** 析构函数
		 *
		 * \param void 
		 * \return 
		 */
		virtual ~OgreKernel(void);

		/**	创建世界
		 *
		 * \param sPluginPath				插件配置文件路径
		 * \param sResourceConfigFilePath	资源配置文件路径
		 * \return 
		 */
		virtual bool				createKernel(const String& sPluginPath, const String& sResourceConfigFilePath);

		/** 渲染
		 *
		 */
		virtual void				renderOneFrame();

		/** 销毁内核
		 *
		 */
		virtual void				destroyKernel();
		
		/** 创建渲染窗口
		 *
		 * \param hWnd						窗口句柄 若为NULL则由内核自动创建渲染窗口
		 * \param w							窗口宽
		 * \param h							窗口高
		 * \param bFullScreen				是否全屏
		 * \param sName						窗口名称
		 * \return 
		 */
		virtual bool				createRenderWindow(HWND hWnd, int w, int h, 
			bool bFullScreen, const String& sName);

		/** 获取渲染窗口
		 *
		 * \return 
		 */
		virtual RenderWindow*		getRenderWindow() const;

		/** 渲染窗口改变
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

