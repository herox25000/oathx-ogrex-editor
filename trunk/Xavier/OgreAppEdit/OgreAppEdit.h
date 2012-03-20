#ifndef _____OgreAppEdit_H
#define _____OgreAppEdit_H

#include "OgreSingleton.h"

namespace Ogre
{
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
	class OgreAppEdit_Export_API AppEdit : public Singleton<AppEdit>
	{
		// �༭��������
		typedef HashMap<String, BaseEditorFactory*> StrEditorFactory;
		
		// �༭������
		typedef HashMap<String, BaseEditor*>		StrEditor;
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

		/** ϵͳ����
		 *
		 */
		virtual void				update();

		/** ע��༭��
		 *
		 * \param pFactory 
		 * \return 
		 */
		virtual bool				registerEditorFactory(BaseEditorFactory* pFactory);

		/** ��ȡ�༭��
		 *
		 * \param typeName 
		 * \return 
		 */
		virtual BaseEditorFactory*	getEditorFactory(const String& typeName);

		/** ע��༭����
		 *
		 * \param pEditor 
		 * \return 
		 */
		virtual bool				addEditor(BaseEditor* pEditor);

		/** ��ȡ�༭����
		 *
		 * \param typeName 
		 * \return 
		 */
		virtual BaseEditor*			getEditor(const String& typeName);

		/** ע���༭����
		 *
		 * \param pEditor 
		 */
		virtual void				delEditor(BaseEditor* pEditor);

		/** ע���༭����
		 *
		 * \param typeName 
		 */
		virtual void				delEditor(const String& typeName);

		/** ���ٱ༭ϵͳ
		 *
		 */
		virtual void				destroySystem();
		
	protected:
		Root*						m_pRoot;	// ogre root object
		StrEditorFactory			m_Factory;	// �༭����
		StrEditor					m_Editor;
	};
}

#endif
