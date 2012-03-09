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
	* \Desc    : ����ռ���,���ཫ���ں˶��󴴽�ʱ������ں˶���һ������
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
		
		/** ��������ռ�
		 *
		 * \param vPos				�����λ��
		 * \param vLookAt			�۲��
		 * \param fFarClipDistance	�����
		 * \param NearClipDistance	��Զ��
		 * \return 
		 */
		virtual bool				createWorldSpace(const Vector3& vPos, const Vector3& vLookAt, float fFarClipDistance, float NearClipDistance);

		/** ��������
		 *
		 */
		virtual void				destroyWorldSpace();
		
		/** ��ȡ�����
		 *
		 * \return 
		 */
		virtual	Camera*				getCamera() const;

		/** ȡ����ͼ
		 *
		 * \return 
		 */
		virtual Viewport*			getViewport() const;

	protected:
		/** ��������ռ�
		 *
		 * \param vPos				�����λ��
		 * \param vLookAt			�۲��
		 * \param fFarClipDistance	�����
		 * \param NearClipDistance	��Զ��
		 * \return 
		 */
		virtual void				createCamera(const Vector3& vPos, const Vector3& vLookAt, 
			float fFarClipDistance, float NearClipDistance);

	protected:
		RenderWindow*				m_pRenderWindow;
		SceneManager*				m_pScene;
		Camera*						m_pCamera;
		Viewport*					m_pView;
		
	};
}

#endif

