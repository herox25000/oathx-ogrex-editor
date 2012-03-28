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
	* \Desc    : �༭�����
	*
	* \bug     : 
	*
	*/
	class OgreAppEdit_Export_API EditorPlugin
	{
	public:
		/** ���캯��
		 *
		 * \param void 
		 * \return 
		 */
		EditorPlugin(void);

		/** ��������
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

		/** ��װ���
		 *
		 * \return 
		 */
		virtual bool			install() = 0;

		/** ж�ز��
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
