#ifndef _____Og2dColour_H
#define _____Og2dColour_H

#include "Og2dTypes.h"

#define	BLEND_ADD				1
#define	BLEND_MUL				0
#define	BLEND_ALPHABLEND		2
#define	BLEND_AADD				0
#define	BLEND_ZWRITE			4
#define	BLEND_NOZWRITE			0

#define DEF_BLEND				(BLEND_MUL | BLEND_ALPHABLEND | BLEND_NOZWRITE)
#define DEF_BLEND_Z				(BLEND_MUL | BLEND_ALPHABLEND | BLEND_ZWRITE)

#ifndef SetAlpha
#define SetAlpha(col,a)			(((col) & 0x00FFFFFF) + (DWORD(a)<<24))
#endif

#ifndef	GetAlpha
#define GetAlpha(argb)			((BYTE)(((DWORD)(argb))>>24))
#endif

#define ARGBNORMAL(a, r, g, b)	(((DWORD)(a*255.0f)<<24)|((DWORD)(r*255.0f)<<16)|((DWORD)(g*255.0f)<<8)|((BYTE)(b*255.0f)))

#define GetB(argb)				((BYTE)(argb))
#define GetG(argb)				((BYTE)(((WORD)(argb))>>8))
#define GetR(argb)				((BYTE)((((DWORD)(argb))>>16) & 0xff))


#define SetB(col,r)				(((col) & 0xFF00FFFF) + (DWORD(r)<<16))
#define SetG(col,g)				(((col) & 0xFFFF00FF) + (DWORD(g)<<8))
#define SetR(col,b)				(((col) & 0xFFFFFF00) + DWORD(b))


#define NormalValue(a)	(a/255.0f)

namespace Og2d
{

#ifdef __cplusplus
	extern "C" { 
#endif

		//!
		/**
		*
		* \param r 
		* \param g 
		* \param b 
		* \param a 
		* \return 
		*/
		_____inline
			Og2d_Export_API  unsigned short rgba16(
			unsigned int r,
			unsigned int g,
			unsigned int b,
			unsigned int a
			);


		//!
		/**
		*
		* \param r 
		* \param g 
		* \param b 
		* \return 
		*/
		_____inline
			Og2d_Export_API unsigned short rgb16(
			unsigned int r,
			unsigned int g,
			unsigned int b
			);

		//!
		/**
		*
		* \param r 
		* \param g 
		* \param b 
		* \return 
		*/
		_____inline
			Og2d_Export_API unsigned short rgb16Form16(
			unsigned int r,
			unsigned int g,
			unsigned int b
			);

		//!
		/**
		*
		* \param color 
		* \return 
		*/
		_____inline
			Og2d_Export_API unsigned short x8r8g8b8Toa1r5g5b5(unsigned int color);

		//!
		/**
		*
		* \param color 
		* \return 
		*/
		_____inline
			Og2d_Export_API unsigned short a8r8g8b8Toa1r5g5b5(unsigned int color);


#ifdef __cplusplus
	}
#endif

	/**
	* \ingroup : Og2d
	*
	* \os&IDE  : Microsoft Windows XP (SP2)  &  Microsoft Visual C++ .NET 2008
	*
	* \VERSION : 1.0
	*
	* \date    : 2012-07-23
	*
	* \Author  : lp
	*
	* \Desc    : 
	*
	* \bug     : 
	*
	* \Copyright (c) 2012 lp All rights reserved.
	*/
	class Og2d_Export_API Colour
	{
	public:
		//!
		/**
		 *
		 * \param void 
		 * \return 
		 */
		Colour(void);

		//!
		/**
		 *
		 * \param a 
		 * \param r 
		 * \param g 
		 * \param b 
		 * \return 
		 */
		Colour(
				const unsigned int a,
				const unsigned int r,
				const unsigned int g,
				const unsigned int b
				);
		//!
		/**
		 *
		 * \param clr 
		 * \return 
		 */
		Colour(const unsigned long clr);

		//!
		/**
		 *
		 * \param clr 
		 * \return 
		 */
		Colour(const Colour& clr);

		//!
		/**
		 *
		 * \param clr 
		 * \return 
		 */
		Colour& operator = (const Colour& clr);

		//!
		/**
		 *
		 * \param clr 
		 * \return 
		 */
		bool operator == (const Colour& clr) const;

		//!
		/**
		 *
		 * \param clr 
		 * \return 
		 */
		bool operator != (const Colour& clr) const;

		//!
		/**
		 *
		 * \param clr 
		 * \return 
		 */
		bool operator == (const unsigned int& clr) const;

		//!
		/**
		 *
		 * \param clr 
		 * \return 
		 */
		bool operator != (const unsigned int& clr) const;

		//!
		/**
		 *
		 * \return 
		 */
		unsigned int	getAlpha() const;

		//!
		/**
		 *
		 * \return 
		 */
		unsigned int	getRed() const;

		//!
		/**
		 *
		 * \return 
		 */
		unsigned int	getGreen() const;

		//!
		/**
		 *
		 * \return 
		 */
		unsigned int	getBlue() const;

		//!
		/**
		 *
		 * \param alpha 
		 */
		void			setAlpha(const unsigned int alpha);

		//!
		/**
		 *
		 * \param red 
		 */
		void			setRed(const unsigned int red);

		//!
		/**
		 *
		 * \param greed 
		 */
		//!
		/**
		 *
		 * \param greed 
		 */
		void			setGreen(const unsigned int greed);

		//!
		/**
		 *
		 * \param blue 
		 */
		void			setBlue(const unsigned int blue);
	public:
		unsigned long	color;
	};

	static const Colour clrBLACK = 0xff000000;
	static const Colour clrWHITE = 0xffffffff;

	static const Colour clrGRAY  = 0xff868182;
	static const Colour clrYELLOW= 0xfffff000;
	static const Colour clrRED   = 0xffff0000;
	static const Colour clrBLUE  = 0xff0000ff;

	/**
	* \ingroup : Og2d
	*
	* \os&IDE  : Microsoft Windows XP (SP2)  &  Microsoft Visual C++ .NET 2008
	*
	* \VERSION : 1.0
	*
	* \date    : 2012-07-23
	*
	* \Author  : lp
	*
	* \Desc    : 
	*
	* \bug     : 
	*
	* \Copyright (c) 2012 lp All rights reserved.
	*/
	class Og2d_Export_API Rgba
	{
	public:

		//!
		/**
		*
		* \param void 
		* \return 
		*/
		Rgba(void);

		//!
		/**
		*
		* \param clr 
		* \return 
		*/
		Rgba(unsigned long clr);

		//!
		/**
		*
		* \param r 
		* \param g 
		* \param b 
		* \param a 
		* \return 
		*/
		Rgba(float r, float g, float b, float a);

		//!
		/**
		*
		* \param clr 
		* \return 
		*/
		Rgba			operator + (const Rgba& clr) const;

		//!
		/**
		*
		* \param clr 
		* \return 
		*/
		Rgba			operator - (const Rgba& clr) const;

		//!
		/**
		*
		* \param clr 
		* \return 
		*/
		Rgba			operator * (const Rgba& clr) const;

		//!
		/**
		*
		* \param scale 
		* \return 
		*/
		Rgba			operator / (const float scale) const;

		//!
		/**
		*
		* \param scale 
		* \return 
		*/
		Rgba			operator * (const float scale) const;

		//!
		/**
		*
		* \param clr 
		* \return 
		*/
		Rgba&			operator += (const Rgba& clr);

		//!
		/**
		*
		* \param clr 
		* \return 
		*/
		Rgba&			operator -= (const Rgba& clr);

		//!
		/**
		*
		* \param scale 
		* \return 
		*/
		Rgba&			operator *= (const float scale);

		//!
		/**
		*
		* \param clr 
		* \return 
		*/
		bool			operator == (const Rgba& clr) const;

		//!
		/**
		*
		* \param clr 
		* \return 
		*/
		bool			operator != (const Rgba& clr) const;

		//!
		/**
		*
		*/
		void			clamp();

		//!
		/**
		*
		* \param clr 
		*/
		void			setColor(unsigned long clr);

		//!
		/**
		*
		* \return 
		*/
		unsigned long	getColor() const;

	public:
		float			r;
		float			g;
		float			b;
		float			a;
	};
}

#endif