#include "Og2dColour.h"
#include "Og2dDebug.h"

namespace Og2d
{
	/**
	 *
	 * \param void 
	 * \return 
	 */
	Colour::Colour(void)
		:color(0)
	{
	}

	/**
	 *
	 * \param clr 
	 * \return 
	 */
	Colour::Colour(const unsigned long clr)
		:color(clr)
	{
	}


	/**
	 *
	 * \param a 
	 * \param r 
	 * \param g 
	 * \param b 
	 * \return 
	 */
	Colour::Colour(
		const unsigned int a,
		const unsigned int r,
		const unsigned int g,
		const unsigned int b
		)
		:color(((a & 0xff)<<24) | ((r & 0xff)<<16) | ((g & 0xff)<<8) | (b & 0xff))
	{

	}

	/**
	 *
	 * \param clr 
	 * \return 
	 */
	Colour::Colour(const Colour& clr)
	{
		color = clr.color;
	}

	/**
	 *
	 * \param clr 
	 * \return 
	 */
	bool Colour::operator == (const Colour& clr) const
	{
		return color == clr.color;
	}

	/**
	 *
	 * \param clr 
	 * \return 
	 */
	bool Colour::operator != (const Colour& clr) const
	{
		return color != clr.color;
	}

	/**
	 *
	 * \param clr 
	 * \return 
	 */
	bool Colour::operator == (const unsigned int& clr) const
	{
		return color == clr;
	}

	/**
	 *
	 * \param clr 
	 * \return 
	 */
	bool Colour::operator != (const unsigned int& clr) const
	{
		return color != clr;
	}

	/**
	 *
	 * \param clr 
	 * \return 
	 */
	Colour& Colour::operator = (const Colour& clr)
	{
		color = clr.color;

		return *this;
	}

	/**
	 *
	 * \return 
	 */
	unsigned int Colour::getAlpha() const
	{
		return color>> 24;
	}

	/**
	 *
	 * \return 
	 */
	unsigned int Colour::getRed() const
	{
		return (color>>16) & 0xff;
	}

	/**
	 *
	 * \return 
	 */
	unsigned int Colour::getGreen() const
	{
		return (color>>8) & 0xff;
	}

	/**
	 *
	 * \return 
	 */
	unsigned int Colour::getBlue() const
	{
		return color & 0xff;
	}

	/**
	 *
	 * \param alpha 
	 */
	void Colour::setAlpha(const unsigned int alpha)
	{
		color = ((alpha & 0xff)<<24) | (color & 0x00ffffff);
	}

	/**
	 *
	 * \param red 
	 */
	void Colour::setRed(const unsigned int red)
	{
		color = ((red & 0xff)<<16) | (color & 0xff00ffff);
	}

	/**
	 *
	 * \param greed 
	 */
	void Colour::setGreen(const unsigned int greed)
	{
		color = ((greed & 0xff)<<8) | (color & 0xffff00ff);
	}

	/**
	 *
	 * \param blue 
	 */
	void Colour::setBlue(const unsigned int blue)
	{
		color = (blue & 0xff) | (color & 0xffffff00);
	}


	/**
	 *
	 * \param &x 
	 */
	_____inline void colorClamp(float &x)
	{ 
		if(x<0.0f) x=0.0f; 
		if(x>1.0f) x=1.0f; 
	}

	//////////////////////////////////////////////////////////////////////////
	//
	//////////////////////////////////////////////////////////////////////////
	/**
	 *
	 * \param void 
	 * \return 
	 */
	Rgba::Rgba(void)
		:r(0),g(0),b(0),a(0)
	{

	}

	/**
	 *
	 * \param r 
	 * \param g 
	 * \param b 
	 * \param a 
	 * \return 
	 */
	Rgba::Rgba(float r, float g, float b, float a)
	{
		this->r = r;
		this->g = g;
		this->b = b;
		this->a = a;
	}

	/**
	 *
	 * \param clr 
	 * \return 
	 */
	Rgba::Rgba(unsigned long clr)
	{
		setColor(clr);
	}

	/**
	 *
	 * \param clr 
	 */
	void Rgba::setColor(unsigned long clr)
	{
		a = (clr>>24)/255.0f;
		r = ((clr>>16) & 0xFF)/255.0f; 
		g = ((clr>>8) & 0xFF)/255.0f; 
		b = (clr & 0xFF)/255.0f;
	}

	/**
	 *
	 * \param clr 
	 * \return 
	 */
	Rgba Rgba::operator + (const Rgba& clr) const
	{
		return Rgba(r+clr.r, g+clr.g, b+clr.b, a+clr.a);
	}

	/**
	 *
	 * \param clr 
	 * \return 
	 */
	Rgba Rgba::operator - (const Rgba& clr) const
	{
		return Rgba(r-clr.r, g-clr.g, b-clr.b, a-clr.a);
	}

	/**
	 *
	 * \param clr 
	 * \return 
	 */
	Rgba Rgba::operator * (const Rgba& clr) const
	{
		return Rgba(r*clr.r, g*clr.g, b*clr.b, a*clr.a);
	}

	/**
	 *
	 * \param scale 
	 * \return 
	 */
	Rgba Rgba::operator * (const float scale) const
	{
		return Rgba(r*scale, g*scale, b*scale, a*scale);
	}

	/**
	 *
	 * \param scale 
	 * \return 
	 */
	Rgba Rgba::operator / (const float scale) const
	{
		return Rgba(r/scale, g/scale, b/scale, a/scale);
	}

	/**
	 *
	 * \param clr 
	 * \return 
	 */
	Rgba& Rgba::operator += (const Rgba& clr)
	{
		r += clr.r;
		g += clr.g;
		b += clr.b;
		a += clr.a;

		return *this;
	}

	/**
	 *
	 * \param clr 
	 * \return 
	 */
	Rgba& Rgba::operator -= (const Rgba& clr)
	{
		r -= clr.r;
		g -= clr.g;
		b -= clr.b;
		a -= clr.a;

		return *this;
	}

	/**
	 *
	 * \param scale 
	 * \return 
	 */
	Rgba& Rgba::operator *= (const float scale)
	{
		r *= scale;
		g *= scale;
		b *= scale;
		a *= scale;

		return *this;
	}

	/**
	 *
	 * \param clr 
	 * \return 
	 */
	bool Rgba::operator != (const Rgba& clr) const
	{
		return (r!=clr.r || g!=clr.g || b!=clr.b || a!=clr.a);
	}

	/**
	 *
	 * \param clr 
	 * \return 
	 */
	bool Rgba::operator == (const Rgba& clr) const
	{
		return (r==clr.r && g==clr.g && b==clr.b && a==clr.a);
	}

	/**
	 *
	 * \return 
	 */
	unsigned long Rgba::getColor() const
	{
		return ((unsigned long)(a*255.0f)<<24) + ((unsigned long)(r*255.0f)<<16) + ((unsigned long)(g*255.0f)<<8) + (unsigned long)(b*255.0f);
	}

	/**
	 *
	 */
	void Rgba::clamp()
	{
		colorClamp(r);
		colorClamp(g);
		colorClamp(b);
		colorClamp(a);
	}
}