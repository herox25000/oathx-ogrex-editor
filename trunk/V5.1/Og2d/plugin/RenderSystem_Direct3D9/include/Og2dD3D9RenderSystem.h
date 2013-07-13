#ifndef _____Og2dD3D9RenderSystem_H
#define _____Og2dD3D9RenderSystem_H

#include <d3d9.h>
#include <d3dx9.h>
#include "Og2dRenderSystem.h"

namespace Og2d
{
	/**
	* \ingroup : RenderSystem_Direct3D9
	*
	* \os&IDE  : Microsoft Windows XP (SP2)  &  Microsoft Visual C++ .NET 2008
	*
	* \VERSION : 1.0
	*
	* \date    : 2012-07-22
	*
	* \Author  : lp
	*
	* \Desc    : D3D9 ��Ⱦϵͳʵ��
	*
	* \bug     : 
	*
	* \Copyright (c) 2012 lp All rights reserved.
	*/
	class Og2d_D3D9_Export_API D3D9RenderSystem : public RenderSystem
	{
	public:
		/**
		 *
		 * \return 
		 */
		D3D9RenderSystem();

		/**
		 *
		 * \return 
		 */
		virtual ~D3D9RenderSystem();

	public:
		/** ��ȡ��Ⱦϵͳ��
		 *
		 * \return 
		 */
		virtual	const String&		getTypeName() const;

		//! ����ͼ���豸
		/**
		*
		* \param hWnd			ָ���豸����
		* \param isFullScreen	ָ���Ƿ�ȫ��
		* \param bbSize			ָ���豸�ߴ���Ϣ
		* \param isVsvy			ָ���Ƿ�����ֱͬ��
		* \return 
		*/
		virtual bool				createGriaphicsDevice(
														HWND hWnd,
														bool isFullScreen,
														const Size& bbSize,
														bool isVsvy
														);


		//! ������Ⱦ
		/**
		*
		* \param clrBack	ָ��������ɫ
		*/
		virtual void				beginScene(const Colour clrBack=clrBLACK);

		//! ������Ⱦ
		/**
		*
		*/
		virtual void				endScene();


		//! ����2D����ͶӰ����
		/**
		*
		* \param width		��Ļ��
		* \param height		��Ļ��
		*/
		virtual void				setMatrix2D(
										const float w, 
										const float h
										);

		/**
		 *
		 * \param x 
		 * \param y 
		 * \param w 
		 * \param h 
		 */
		virtual void				setMatrix2D(
										const float x,
										const float y,
										const float w, 
										const float h
										);


		//! ��ȡD3D�豸
		/**
		*
		* \return 
		*/
		virtual	IDirect3DDevice9*	getD3DDevice() const;

		//! ����Alpha���
		/**
		*
		* \param isOpen ��ture��򿪣�����ر�
		*/
		virtual void				setAlphaBlend(bool isOpen);

		//! ���û��ģʽ
		/**
		*
		* \param dwMode 
		*/
		virtual	void				setBlendMode(DWORD dwMode);

		//! ����Alpha����
		/**
		*
		* \param isOpen �Ƿ��
		* \param clrKey ���Թؼ�ɫ
		*/
		virtual void				setAlphaTest(
												bool bOpen,
												const Colour clrKey
												);

		
		/**
		 *
		 * \param quad 
		 */
		virtual	void				draw(const SQuad& quad);

		/** ������״
		 *
		 * \param nLength	��״��Ҫ�Ķ�����
		 * \return 
		 */
		virtual	Shape*				createShape(int nLength);

		/** ���ļ������������
		 *
		 * \param szName	ָ���ļ���
		 * \return 
		 */
		virtual Texture*			createTextureFromFile(const String& szName);

		/**
		 *
		 * \return 
		 */
		virtual	const Size&			getBackBufferSize() const;
	protected:
		IDirect3DDevice9*			m_pd3dDevice;
		IDirect3D9*					m_pD3D;
		String						m_szVendorName;
		Size						m_bbSize;
		DWORD						m_curMode;
	};
}

#endif