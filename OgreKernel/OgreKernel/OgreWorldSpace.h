#ifndef _____WorldSpace
#define _____WorldSpace

#include "OgreKernelPrerequisites.h"
#include <OgreSingleton.h>

namespace Ogre
{
	/**
	* \ingroup : OgreKernel
	*
	* \os&IDE  : Microsoft Windows XP (SP3)  &  Microsoft Visual C++ .NET 2008 & ogre1.8
	*
	* \VERSION : 1.0
	*
	* \@date   : 2011-12-19
	*
	* \Author  : lp
	*
	* \Desc    : 世界空间类
	*
	* \bug     : 
	*
	*/
	class _OgreKenrnelExport WorldSpace : public Singleton<WorldSpace>
	{
	public:
		/**	获取单件
		 *
		 * \return 
		 */
		static	WorldSpace&			getSingleton();

		/** 获取单件指针
		 *
		 * \return 
		 */
		static	WorldSpace*			getSingletonPtr();

	public:
		/**
		 *
		 * \param void 
		 * \return 
		 */
		WorldSpace(void);

		/**
		 *
		 * \param void 
		 * \return 
		 */
		virtual ~WorldSpace(void);
		
		/**	创建世界
		 *
		 * \param sPluginPath				插件配置文件路径
		 * \param sResourceConfigFilePath	资源配置文件路径
		 * \param bAutoCreateWindow			是否自动创建窗口
		 * \param sTitle					窗口标题
		 * \return 
		 */
		virtual bool				createWorldSpace(const String& sPluginPath, const String& sResourceConfigFilePath, bool bAutoCreateWindow, const String& sTitle);

		/** 销毁世界
		 *
		 */
		virtual void				destroyWorldSpace();
	protected:
		Root*						m_pRoot;
	};
}

#endif

