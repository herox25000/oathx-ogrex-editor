#ifndef _____OgreBaseEditor_H
#define _____OgreBaseEditor_H

#include "OgreEventSet.h"
#include "OgreProperty.h"

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
	* \Desc    : �༭���߻���
	*
	* \bug     : 
	*
	*/
	class Ogre_EditSystem_Export_API BaseEditor : public EventSet, public PropertySet
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

	protected:
		String						m_typeName;
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
	class Ogre_EditSystem_Export_API BaseEditorFactory
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
