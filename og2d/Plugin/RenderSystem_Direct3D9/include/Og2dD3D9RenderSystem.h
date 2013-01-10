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
	* \Desc    : D3D9 渲染系统实现
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
		/** 获取渲染系统名
		 *
		 * \return 
		 */
		virtual	const String&		getTypeName() const;

		//! 创建图形设备
		/**
		*
		* \param hWnd			指定设备窗口
		* \param isFullScreen	指定是否全屏
		* \param bbSize			指定设备尺寸信息
		* \param isVsvy			指定是否开启垂直同步
		* \return 
		*/
		virtual bool				createGriaphicsDevice(
														HWND hWnd,
														bool isFullScreen,
														const Size& bbSize,
														bool isVsvy
														);


		//! 启动渲染
		/**
		*
		* \param clrBack	指定背景颜色
		*/
		virtual void				beginScene(const Colour clrBack=clrBLACK);

		//! 结束渲染
		/**
		*
		*/
		virtual void				endScene();


		//! 设置2D正交投影矩阵
		/**
		*
		* \param width		屏幕宽
		* \param height		屏幕高
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


		//! 获取D3D设备
		/**
		*
		* \return 
		*/
		virtual	IDirect3DDevice9*	getD3DDevice() const;

		//! 设置Alpha混合
		/**
		*
		* \param isOpen 是ture则打开，否则关闭
		*/
		virtual void				setAlphaBlend(bool isOpen);

		//! 设置混合模式
		/**
		*
		* \param dwMode 
		*/
		virtual	void				setBlendMode(DWORD dwMode);

		//! 设置Alpha测试
		/**
		*
		* \param isOpen 是否打开
		* \param clrKey 测试关键色
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

		/** 创建形状
		 *
		 * \param nLength	形状需要的顶点数
		 * \return 
		 */
		virtual	Shape*				createShape(int nLength);

		/** 由文件构造纹理对象
		 *
		 * \param szName	指定文件名
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