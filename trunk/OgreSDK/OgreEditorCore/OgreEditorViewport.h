#ifndef _____OgreEditorViewport_H
#define _____OgreEditorViewport_H

#include "OgreEditorPlugin.h"

namespace Ogre
{
	/**
	* \ingroup : XavierEditor
	*
	* \os&IDE  : Microsoft Windows XP (SP3)  &  Microsoft Visual C++ .NET 2008
	*
	* \VERSION : 1.0
	*
	* \date    : 2013-01-24
	*
	* \Author  : lp
	*
	* \Desc    : �ӿڱ༭��
	*
	* \bug     : 
	*
	* \Copyright (c) 2012 lp All rights reserved.
	*/
	class Ogre_EditorCore_Export_API EditorViewport : public EditorPlugin
	{
	public:
		/** �����ӿڱ༭���
		 *
		 * \param pluginName	�����
		 * \param background	�ӿ�Ĭ����ɫ
		 * \param adp			�ӿ�Ĭ��������������
		 * \return 
		 */
		EditorViewport(const String& pluginName, const ColourValue& background, const SEditorCamearAdp& adp);

		/** ��������
		 *
		 * \return 
		 */
		virtual ~EditorViewport();

		/** ��ȡ��װ���ӿڶ���
		 *
		 * \return 
		 */
		virtual	Viewport*		getViewport() const;
		
		/** ���ڳߴ�ı�
		 *
		 */
		virtual	void			windowMovedOrResized();
		
		/** ��ȡ��ǰ����������
		 *
		 * \return 
		 */
		virtual	EditorCamera*	getActiveCamera() const;

		/** ��ȡ�������
		 *
		 * \param vPos	��ǰ�����Ļλ��
		 * \param ray 
		 * \return 
		 */
		virtual bool			getMouseRay(const Vector2& vPos, Ray& ray);
	public:
		/**	����ܴ��ڳߴ�ı�ʱ����
		 *
		 * \param cx 
		 * \param cy 
		 * \return 
		 */
		virtual	bool			OnSize(int cx, int cy);

		/** ���༭������Ըı�ʱ����
		 *
		 * \param parentName	������
		 * \param name			������
		 * \param anyValue		����ֵ
		 * \param nType			����ֵ����
		 * \return 
		 */
		virtual bool			OnPropertyChanged(const String& parentName, const String& name, 
			const Any& anyValue, int nType);

	protected:
		/** ��������
		 *
		 * \param pluginName 
		 * \param background 
		 * \param adp 
		 * \return 
		 */
		virtual	bool			configure(const String& pluginName, const ColourValue& background,
			const SEditorCamearAdp& adp);
	protected:
		Viewport*				m_pViewport;
		EditorCamera*			m_pCamera;
	};

	// �������������
	struct SEditorPluginViewportAdp : public SEditorPluginAdp
	{
		ColourValue				background;
		SEditorCamearAdp		cameraAdp;
	};

	/**
	* \ingroup : XavierEditor
	*
	* \os&IDE  : Microsoft Windows XP (SP2)  &  Microsoft Visual C++ .NET 2008
	*
	* \VERSION : 1.0
	*
	* \date    : 2013-01-24
	*
	* \Author  : lp
	*
	* \Desc    : �������
	*
	* \bug     : 
	*
	* \Copyright (c) 2012 lp All rights reserved.
	*/
	class Ogre_EditorCore_Export_API EditorViewportFactory : public EditorPluginFactory
	{
	public:
		/**
		 *
		 * \param factoryName 
		 * \return 
		 */
		EditorViewportFactory(const String& factoryName);

		/**
		 *
		 * \return 
		 */
		virtual ~EditorViewportFactory();

		/**	�����༭���
		 *
		 * \param ssadp			����������
		 * \param pParent		�����
		 * \return 
		 */
		virtual	EditorPlugin*			createPlugin(const SEditorPluginAdp& ssadp, EditorPlugin* pParent);
	};
}

#endif