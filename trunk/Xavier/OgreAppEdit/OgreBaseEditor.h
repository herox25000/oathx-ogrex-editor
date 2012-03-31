#ifndef _____OgreBaseEditor_H
#define _____OgreBaseEditor_H

#include "OgreProperty.h"

namespace Ogre
{
	class BaseEditor;
	class BaseEditorFactory;

	// �ӱ༭��
	typedef std::deque<BaseEditor*>			VEditor;
	typedef std::deque<BaseEditorFactory*>	VEditorFactory;

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
	* \Desc    : �༭���߻���
	*
	* \bug     : 
	*
	*/
	class OgreAppEdit_Export_API BaseEditor : public PropertySet
	{
	public:
		/** ���캯��
		 *
		 * \param void 
		 * \return 
		 */
		BaseEditor();

		/** ��������
		 *
		 * \param void 
		 * \return 
		 */
		virtual ~BaseEditor(void);

		/** ��ȡ�༭������
		 *
		 * \return 
		 */
		virtual	String				getTypeName() const;

		/** ���ñ༭������
		 *
		 * \param typeName 
		 */
		virtual void				setTypeName(const String& typeName);

		/** ���ر༭��
		 *
		 * \param sPath 
		 * \return 
		 */
		virtual bool				load(const String& sPath);

		/** ж�ر༭��
		 *
		 */
		virtual void				unload();

		/** ����ӱ༭��
		 *
		 * \param pEditor 
		 */
		virtual void				addEditor(BaseEditor* pEditor);

		/**
		 *
		 * \param name 
		 * \return 
		 */
		virtual BaseEditor*			getEditor(const String& name);	

		/**
		 *
		 * \param pEditor 
		 */
		virtual void				delEditor(BaseEditor* pEditor);

		/**
		 *
		 */
		virtual void				clearEditor();

		/**
		 *
		 * \return 
		 */
		virtual BaseEditor*			getEditor(int index);

		/**
		 *
		 * \return 
		 */
		virtual size_t				getEditorCount() const;

		/** ע��༭��
		 *
		 * \param pFactory 
		 * \return 
		 */
		virtual void				registerEditorFactory(BaseEditorFactory* pFactory);

		/**
		 *
		 * \param pFactory 
		 */
		virtual void				unregisterEditorFactory(BaseEditorFactory* pFactory);

		/** ��ȡ�༭��
		 *
		 * \param typeName 
		 * \return 
		 */
		virtual BaseEditorFactory*	getEditorFactory(const String& typeName);

		/** ��ձ༭��
		 *
		 */
		virtual void				clearEditorFactory();

		/** ���ø��༭��
		 *
		 * \param pEditor 
		 */
		virtual void				setParent(BaseEditor* pEditor);

		/** ��ȡ���༭��
		 *
		 * \return 
		 */
		virtual BaseEditor*			getParent() const;
	protected:
		String						m_typeName;
		VEditor						m_vEditor;
		VEditorFactory				m_vFactory;
		BaseEditor*					m_pParent;
	};

	// ������������
	struct SBaseCreateParam
	{
		String		typeName;		
	};

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
	class OgreAppEdit_Export_API BaseEditorFactory
	{
	public:
		/** ���캯��
		 *
		 * \param void 
		 * \return 
		 */
		BaseEditorFactory(void);

		/** ��������
		 *
		 * \param void 
		 * \return 
		 */
		virtual ~BaseEditorFactory(void);

		/** ��ȡ�༭������
		 *
		 * \return 
		 */
		virtual String					getTypeName() const;

		/** ���ñ༭������
		 *
		 * \param typeName 
		 */
		virtual void					setTypeName(const String& typeName);

		/** ����
		 *
		 * \param pm 
		 * \return 
		 */
		virtual BaseEditor*				create(const SBaseCreateParam* pm) = 0;

	protected:
		String							m_typeName;
	};
}

#endif
