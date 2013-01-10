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
	Mesh::Mesh(const String& name, int nVertexCount)
		: RenderTarget(name), m_nVertexCount(nVertexCount)
	{

	}

	/**
	 *
	 * \return 
	 */
	Mesh::~Mesh()
	{

	}

	/**
	 *
	 * \return 
	 */
	ulong		Mesh::getVertexCount() const
	{
		return m_nVertexCount;
	}
}