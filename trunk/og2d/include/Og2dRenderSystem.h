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
	* \Desc    : ��Ⱦϵͳ
	*
	* \bug     : 
	*
	* \Copyright (c) 2012 lp All rights reserved.
	*/
	class Og2d_Export_API RenderSystem
	{
	public:
		/** ���캯��
		 *
		 * \return 
		 */
		RenderSystem();

		/** ��������
		 *
		 * \return 
		 */
		virtual ~RenderSystem();

		/** ��ȡ������
		 *
		 * \return 
		 */
		virtual	const String&		getTypeName() const = 0;

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
														) = 0;

		//! ������Ⱦ
		/**
		*
		* \param clrBack	ָ��������ɫ
		*/
		virtual void				beginScene(const Colour clrBack=clrBLACK) = 0;

		//! ������Ⱦ
		/**
		*
		*/
		virtual void				endScene() = 0;

		//! ����2D����ͶӰ����
		/**
		*
		* \param width		��Ļ��
		* \param height		��Ļ��
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

		/** ������״
		 *
		 * \param nLength	��״��Ҫ�Ķ�����
		 * \return 
		 */
		virtual	Shape*				createShape(int nLength) = 0;

		/**
		 *
		 * \param quad 
		 */
		virtual	void				draw(const SQuad& quad) = 0;

		/** ���ļ������������
		 *
		 * \param szName	ָ���ļ���
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