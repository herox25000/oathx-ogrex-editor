#ifndef _____OgreSceneManagerEditor_H
#define _____OgreSceneManagerEditor_H

#include "OgreBaseEditor.h"

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
	* \Desc    : �����������༭����
	*
	* \bug     : 
	*
	*/
	class OgreAppEdit_Export_API SceneManagerEditor : public BaseEditor
	{
	public:
		/** ���캯��
		 *
		 * \param void 
		 * \return 
		 */
		SceneManagerEditor(SceneTypeMask typeMask, const String& sName);

		/** ��������
		 *
		 * \param void 
		 * \return 
		 */
		virtual ~SceneManagerEditor(void);

		/** ��ȡ����������
		 *
		 * \return 
		 */
		virtual SceneManager*		getSceneManager() const;
	protected:
		// OGRE ����������
		SceneManager*				m_pSceneManager;
	};

	// ������������������
	struct SSceneManagerCreateParam : public SBaseCreateParam
	{
		String						sName;
		SceneTypeMask				typeMask;
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
	class OgreAppEdit_Export_API SceneManagerEditorFactory : public BaseEditorFactory
	{
	public:
		/**
		 *
		 * \return 
		 */
		SceneManagerEditorFactory();

		/**
		 *
		 * \return 
		 */
		virtual ~SceneManagerEditorFactory();

		/**
		 *
		 * \param pm 
		 * \return 
		 */
		virtual BaseEditor*			create(const SBaseCreateParam* pm);
	};
}

#endif
