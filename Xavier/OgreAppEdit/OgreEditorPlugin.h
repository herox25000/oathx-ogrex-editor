#ifndef _____OgreEditorPlugin_H
#define _____OgreEditorPlugin_H

namespace Ogre
{
	typedef void (*DLLPluginStart)(void);
	typedef void (*DLLPluginStop)(void);

	/**
	* \ingroup : OgreAppEdit
	*
	* \os&IDE  : Microsoft Windows XP (SP3)  &  Microsoft Visual C++ .NET 2008 & ogre1.8
	*
	* \VERSION : 1.0
	*
	* \@date   : 2012-03-27
	*
	* \Author  : lp
	*
	* \Desc    : 编辑器插件
	*
	* \bug     : 
	*
	*/
	class OgreAppEdit_Export_API EditorPlugin
	{
	public:
		/** 构造函数
		 *
		 * \param void 
		 * \return 
		 */
		EditorPlugin(void);

		/** 析构函数
		 *
		 * \param void 
		 * \return 
		 */
		virtual ~EditorPlugin(void);

		/**
		 *
		 * \return 
		 */
		virtual const String&	getName() const = 0;

		/** 安装插件
		 *
		 * \return 
		 */
		virtual bool			install() = 0;

		/** 卸载插件
		 *
		 */
		virtual void			uninstall() = 0;

		/**
		 *
		 */
		virtual void			initialise() = 0;

		/**
		 *
		 */
		virtual void			shutdown() = 0;
	};
}

#endif
