#ifndef _____Og2dRenderSystem_H
#define _____Og2dRenderSystem_H

#include "Og2dShape.h"

namespace Og2d
{
	/**
	* \ingroup : Og2d
	*
	* \os&IDE  : Microsoft Windows XP (SP2)  &  Microsoft Visual C++ .NET 2008
	*
	* \VERSION : 1.0
	*
	* \date    : 2012-07-28
	*
	* \Author  : lp
	*
	* \Desc    : 渲染系统
	*
	* \bug     : 
	*
	* \Copyright (c) 2012 lp All rights reserved.
	*/
	class Og2d_Export_API RenderSystem
	{
	public:
		/** 构造函数
		 *
		 * \return 
		 */
		RenderSystem();

		/** 析构函数
		 *
		 * \return 
		 */
		virtual ~RenderSystem();

		/** 获取类型名
		 *
		 * \return 
		 */
		virtual	const String&		getTypeName() const = 0;

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
														) = 0;

		//! 启动渲染
		/**
		*
		* \param clrBack	指定背景颜色
		*/
		virtual void				beginScene(const Colour clrBack=clrBLACK) = 0;

		//! 结束渲染
		/**
		*
		*/
		virtual void				endScene() = 0;

		//! 设置2D正交投影矩阵
		/**
		*
		* \param width		屏幕宽
		* \param height		屏幕高
		*/
		virtual void				setMatrix2D(
										const float w, 
										const float h
										) = 0;

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
										) = 0;

		/** 创建形状
		 *
		 * \param nLength	形状需要的顶点数
		 * \return 
		 */
		virtual	Shape*				createShape(int nLength) = 0;

		/**
		 *
		 * \param quad 
		 */
		virtual	void				draw(const SQuad& quad) = 0;

		/** 由文件构造纹理对象
		 *
		 * \param szName	指定文件名
		 * \return 
		 */
		virtual Texture*			createTextureFromFile(
			const String& szName) = 0;

		/**
		 *
		 * \return 
		 */
		virtual	const Size&			getBackBufferSize() const = 0;
	};
}

#endif