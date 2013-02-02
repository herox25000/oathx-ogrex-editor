#ifndef _____OgreServerViewport_H
#define _____OgreServerViewport_H

namespace Ogre
{
	/**
	* \ingroup : XavierSystem
	*
	* \os&IDE  : Microsoft Windows XP (SP2)  &  Microsoft Visual C++ .NET 2008
	*
	* \VERSION : 1.0
	*
	* \date    : 2013-01-31
	*
	* \Author  : lp
	*
	* \Desc    : 
	*
	* \bug     : 
	*
	* \Copyright (c) 2012 lp All rights reserved.
	*/
	class Ogre_System_Export_API ServerViewport : public Server
	{
	public:
		/**
		 *
		 * \param pluginName 
		 * \param background 
		 * \param adp 
		 * \return 
		 */
		ServerViewport(const String& name, const ColourValue& background, const SServerCameraAdp& adp);

		/**
		 *
		 * \return 
		 */
		virtual ~ServerViewport();

		/**
		 *
		 * \return 
		 */
		virtual	Viewport*			getViewport() const;
		
		/**
		 *
		 */
		virtual	void				windowMovedOrResized();

		/**
		 *
		 * \param pActiveCamera 
		 */
		virtual	void				setActiveCamera(ServerCamera* pActiveCamera);

		/**
		 *
		 * \return 
		 */
		virtual	ServerCamera*		getActiveCamera() const;


		/**
		 *
		 * \param vPos 
		 * \param ray 
		 * \return 
		 */
		virtual bool				getMouseRay(const Vector2& vPos, Ray& ray);	

	protected:
		/**
		 *
		 * \param pluginName 
		 * \param background 
		 * \param adp 
		 * \return 
		 */
		virtual	bool				configure(const String& name, const ColourValue& background,
			const SServerCameraAdp& adp);

	protected:
		Viewport*					m_pViewport;
		ServerCamera*				m_pActiveCamera;
	};
}

#endif