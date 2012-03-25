#ifndef _____OgreGirdEditor_H
#define _____OgreGirdEditor_H

#include "OgreBaseEditor.h"

namespace Ogre
{
	/**
	* \ingroup : OgreAppEdit
	*
	* \os&IDE  : Microsoft Windows XP (SP3)  &  Microsoft Visual C++ .NET 2008 & ogre1.8
	*
	* \VERSION : 1.0
	*
	* \@date   : 2012-03-25
	*
	* \Author  : lp
	*
	* \Desc    : 
	*
	* \bug     : 
	*
	*/
	class GridEditor : public BaseEditor
	{
	public:
		/**
		 *
		 * \param fWidth 
		 * \param fSize 
		 * \param fDepth 
		 * \return 
		 */
		GridEditor(SceneManager* pSceneManager, Real fWidth, Real fSize, Real fDepth);

		/**
		 *
		 * \param void 
		 * \return 
		 */
		virtual ~GridEditor(void);

		/**
		 *
		 */
		virtual void				show();

		/**
		 *
		 */
		virtual void				hide();
	protected:
		SceneManager*				m_pSceneManager;
		Real						m_fWidth;
		Real						m_fSize;
		Real						m_fDepth;
		SceneNode*					m_pGridNode;
		SceneNode*					m_axisNode;
	};

	//////////////////////////////////////////////////////////////////////////
	struct SGridCreateParam : public SBaseCreateParam
	{
		Real						fWidth;
		Real						fSize;
		Real						fDepth;
	};

	/**
	* \ingroup : OgreAppEdit
	*
	* \os&IDE  : Microsoft Windows XP (SP3)  &  Microsoft Visual C++ .NET 2008 & ogre1.8
	*
	* \VERSION : 1.0
	*
	* \@date   : 2012-03-25
	*
	* \Author  : lp
	*
	* \Desc    : 
	*
	* \bug     : 
	*
	*/
	class OgreAppEdit_Export_API GridEditorFactory : public BaseEditorFactory
	{
	public:
		/**
		 *
		 * \return 
		 */
		GridEditorFactory();

		/**
		 *
		 * \param pm 
		 * \return 
		 */
		virtual BaseEditor*			create(const SBaseCreateParam* pm);
	};
}

#endif
