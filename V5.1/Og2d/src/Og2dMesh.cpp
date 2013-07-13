#include "Og2dRenderSystem.h"
#include "Og2dMesh.h"
#include "Og2dSystem.h"
#include "Og2dDebug.h"

namespace Og2d
{
	/**
	 *
	 * \param name 
	 * \param nVertexCount 
	 * \return 
	 */
	Mesh::Mesh(int nVertsPerRow, int nVertsPerCol, int nSpaceing)
		: m_nVertsPerRow(nVertsPerRow), m_nVertsPerCol(nVertsPerCol), m_nSpaceing(nSpaceing)
	{

	}

	/**
	 *
	 * \return 
	 */
	Mesh::~Mesh()
	{

	}
}