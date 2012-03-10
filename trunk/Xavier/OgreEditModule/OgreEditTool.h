#pragma once

#include "OgreEditToolPrerequisites.h"
#include "OgreEditPluginFactroy.h"

namespace Ogre
{
	/**
	* \ingroup : OgreEditModule
	*
	* \os&IDE  : Microsoft Windows XP (SP3)  &  Microsoft Visual C++ .NET 2008 & ogre1.8
	*
	* \VERSION : 1.0
	*
	* \@date   : 2012-03-10
	*
	* \Author  : lp
	*
	* \Desc    : Ogre EditTool Manager
	*
	* \bug     : 
	*
	*/
	class OgreEditTool_Export_API EditTool : public Singleton<EditTool>
	{
		// �༭��
		typedef std::map<String, EditPluginFactroy*>	StrPluginFactroy;
	public:
		/**
		 *
		 * \return 
		 */
		static	EditTool&				getSingleton();

		/**
		 *
		 * \return 
		 */
		static	EditTool*				getSingletonPtr();

	public:
		/**
		 *
		 * \param void 
		 * \return 
		 */
		EditTool(void);

		/**
		 *
		 * \param void 
		 * \return 
		 */
		virtual ~EditTool(void);

		 /** ע��༭����
		  *
		  * \param pDescribe			�������
		  * \param pPluginFactroy		�������
		  */
		virtual void					registerEditorFactory(void* pDescribe, EditPluginFactroy* pPluginFactroy);

		/**
		 *
		 * \param pPluginFactroy 
		 */
		virtual void					registerEditorFactory(EditPluginFactroy* pPluginFactroy);

		/**
		 *
		 * \param sName 
		 * \return 
		 */
		virtual EditPluginFactroy*		getEditorFactory(const String& sName);

	protected:
		StrPluginFactroy				m_StrPluginFactroy;
	};
}


