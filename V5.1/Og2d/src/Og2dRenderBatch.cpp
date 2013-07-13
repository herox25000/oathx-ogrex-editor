#include "Og2dRenderBatch.h"

namespace Og2d
{
	/**
	 *
	 * \param szName 
	 * \param nBatch 
	 * \return 
	 */
	RenderBatch::RenderBatch(const String& szName, int nBatch)
		: m_szName(szName), m_nBatch(nBatch)
	{

	}

	/**
	 *
	 * \return 
	 */
	RenderBatch::~RenderBatch()
	{

	}

	/**
	 *
	 * \param szName 
	 */
	void	RenderBatch::setName(const String& szName)
	{
		m_szName = szName;
	}

	/**
	 *
	 * \return 
	 */
	String	RenderBatch::getName() const
	{
		return m_szName;
	}

	/**
	 *
	 * \param nBatch 
	 */
	void	RenderBatch::setBatch(int nBatch)
	{
		m_nBatch = nBatch;
	}
	
	/**
	 *
	 * \return 
	 */
	int		RenderBatch::getBatch() const
	{
		return m_nBatch;
	}
}