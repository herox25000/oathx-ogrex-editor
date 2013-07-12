#include "StdAfx.h"
#include "StockManager.h"

//////////////////////////////////////////////////////////////////////////////////

//���캯��
CStockManager::CStockManager()
{
	//���ñ���
	m_lStockScore=0L;
	m_dDecreaseRate=1.0;

	return;
}

//��������
CStockManager::~CStockManager()
{
}

//���ÿ��
SCORE CStockManager::SetStockScore(SCORE lStockScore)
{
	//���ñ���
	m_lStockScore=lStockScore;

	return m_lStockScore;
}

//���ñ���
DOUBLE CStockManager::SetDecreaseRate(DOUBLE dDecreaseRate)
{
	//���ñ���
	m_dDecreaseRate=dDecreaseRate;

	return m_dDecreaseRate;
}

//�޸Ŀ��
VOID CStockManager::ModifyStockScore(SCORE lVariationScore)
{
	//Ч�����
	m_lStockScore-=lVariationScore;

	//���ü���
	if (m_lStockScore>0L)
	{
		m_lStockScore=(SCORE)(m_lStockScore*m_dDecreaseRate);
	}

	return;
}

//���ô��
VOID CStockManager::InitializationStock(SCORE lStockScore, DOUBLE dDecreaseRate)
{
	//���ñ���
	m_lStockScore=lStockScore;
	m_dDecreaseRate=dDecreaseRate;

	return;
}

//////////////////////////////////////////////////////////////////////////////////
