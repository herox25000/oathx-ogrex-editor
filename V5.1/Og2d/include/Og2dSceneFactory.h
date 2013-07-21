#ifndef _____Og2dSceneFactory_H
#define _____Og2dSceneFactory_H

#include "Og2dScene.h"

namespace Og2d
{
	/**
	* \ingroup : Og2d
	*
	* \os&IDE  : Microsoft Windows XP (SP2)  &  Microsoft Visual C++ .NET 2008
	*
	* \VERSION : 1.0
	*
	* \date    : 2012-08-03
	*
	* \Author  : lp
	*
	* \Desc    : ��������
	*
	* \bug     : 
	*
	* \Copyright (c) 2012 lp All rights reserved.
	*/
	class Og2d_Export_API SceneFactory
	{
	public:
		/** ���캯��
		 *
		 * \return 
		 */
		SceneFactory(int nType);

		/** ��������
		 *
		 * \return 
		 */
		virtual ~SceneFactory();

		/** ��ȡ����������
		 *
		 * \return 
		 */
		virtual	int				getType() const;

		/** ��������������
		 *
		 * \param szName	������
		 * \param vOrigin	����ԭ��
		 * \param cSize		�����ߴ�
		 * \param rcView	�ӿڳߴ�
		 * \return 
		 */
		virtual	Scene*			createScene(const String& szName, const Rect& rcBound);
	protected:
		int						m_nType;
	};
}

#endif