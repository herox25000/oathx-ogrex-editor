#ifndef _____EditorViewport_H
#define _____EditorViewport_H

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
	* \Desc    : 视口编辑器
	*
	* \bug     : 
	*
	* \Copyright (c) 2012 lp All rights reserved.
	*/
	class EditorViewport : public EditorPlugin
	{
	public:
		/**
		 *
		 * \param pluginName 
		 * \param background 
		 * \param adp 
		 * \return 
		 */
		EditorViewport(const String& pluginName, const ColourValue& background, const SEditorCamearAdp& adp);

		/**
		 *
		 * \return 
		 */
		virtual ~EditorViewport();

		/**
		 *
		 * \return 
		 */
		virtual	Viewport*		getViewport() const;
		
		/**
		 *
		 */
		virtual	void			windowMovedOrResized();
		
		/**
		 *
		 * \return 
		 */
		virtual	EditorCamera*	getActiveCamera() const;

		/**
		 *
		 * \param vPos 
		 * \param ray 
		 * \return 
		 */
		virtual bool			getMouseRay(const Vector2& vPos, Ray& ray);
	public:
		/**
		 *
		 * \param cx 
		 * \param cy 
		 * \return 
		 */
		virtual	bool			OnSize(int cx, int cy);

		/**
		 *
		 * \param parentName 
		 * \param name 
		 * \param anyValue 
		 * \param nType 
		 * \return 
		 */
		virtual bool			OnPropertyChanged(const String& parentName, const String& name, 
			const Any& anyValue, int nType);

	protected:
		/**
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

	// 场景插件适配器
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
	* \Desc    : 插件工厂
	*
	* \bug     : 
	*
	* \Copyright (c) 2012 lp All rights reserved.
	*/
	class EditorViewportFactory : public EditorPluginFactory
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

		/**
		 *
		 * \param ssadp 
		 * \param pParent 
		 * \return 
		 */
		virtual	EditorPlugin*			createPlugin(const SEditorPluginAdp& ssadp, EditorPlugin* pParent);
	};
}

#endif