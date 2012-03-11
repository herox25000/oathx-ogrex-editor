#ifndef _____OgreEditSystem_H
#define _____OgreEditSystem_H

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
	class Ogre_EditSystem_Export_API EditSystem : public Singleton<EditSystem>
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
		static	EditSystem&			getSingleton();

		/** ��ȡ�༭ϵͳ
		 *
		 * \return 
		 */
		static	EditSystem*			getSingletonPtr();

	public:
		/** ���캯��
		 *
		 * \param void 
		 * \return 
		 */
		EditSystem(void);

		/** ��������
		 *
		 * \param void 
		 * \return 
		 */
		virtual ~EditSystem(void);

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
