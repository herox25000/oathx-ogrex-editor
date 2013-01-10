#include "Og2dTexture.h"
#include "Og2dVertex.h"

namespace Og2d
{
	/**
	 *
	 * \param alpha 
	 */
	void	SQuad::setAlpha(const short alpha)
	{
		for (int i=0; i<4; i++)
		{
			vQuad[i].color.setAlpha(alpha);
		}
	}

	/**
	 *
	 * \param nIdx 
	 * \param clr 
	 */
	void	SQuad::setVertexColor(int nIdx, const Colour clr)
	{
		if (nIdx == -1)
		{
			for (int i=0; i<4; i++)
			{
				vQuad[i].color = clr;
			}
		}
		else
		{
			if (nIdx >= 0 && nIdx < 4)
			{
				vQuad[nIdx].color = clr;
			}
		}
	}

	/**
	 *
	 * \param pNewTexture 
	 */
	void	SQuad::setTexture(Texture* pNewTexture)
	{
		if (pTexture != pNewTexture)
		{
			pTexture = pNewTexture;
		}
	}

	/**
	 *
	 * \param dwMode 
	 */
	void	SQuad::setBlend(DWORD dwMode)
	{
		blend = dwMode;
	}
}