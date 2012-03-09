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
	* \Desc    : ����ռ���
	*
	* \bug     : 
	*
	*/
	class Ogre_Export_API WorldSpace : public Singleton<WorldSpace>
	{
	public:
		/**	��ȡ����
		 *
		 * \return 
		 */
		static	WorldSpace&			getSingleton();

		/** ��ȡ����ָ��
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
		
		/**	��������
		 *
		 * \param sPluginPath				��������ļ�·��
		 * \param sResourceConfigFilePath	��Դ�����ļ�·��
		 * \param bAutoCreateWindow			�Ƿ��Զ���������
		 * \param sTitle					���ڱ���
		 * \return 
		 */
		virtual bool				createWorldSpace(const String& sPluginPath, const String& sResourceConfigFilePath, bool bAutoCreateWindow, const String& sTitle);

		/** ��������
		 *
		 */
		virtual void				destroyWorldSpace();
	protected:
		Root*						m_pRoot;
	};
}

#endif

