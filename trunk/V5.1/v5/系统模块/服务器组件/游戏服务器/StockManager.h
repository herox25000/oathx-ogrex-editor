#ifndef STOCK_MANAGER_HEAD_FILE
#define STOCK_MANAGER_HEAD_FILE

#include "Stdafx.h"

//////////////////////////////////////////////////////////////////////////////////

//������
class CStockManager
{
	//��������
protected:
	SCORE							m_lStockScore;						//�����Ŀ
	DOUBLE							m_dDecreaseRate;					//���ٱ���

	//��������
public:
	//���캯��
	CStockManager();
	//��������
	virtual ~CStockManager();

	//��ѯ����
public:
	//��ȡ���
	SCORE GetStockScore() { return m_lStockScore; }
	//���ٱ���
	DOUBLE GetDecreaseRate() { return m_dDecreaseRate; }

	//���ú���
public:
	//���ÿ��
	SCORE SetStockScore(SCORE lStockScore);
	//���ñ���
	DOUBLE SetDecreaseRate(DOUBLE dDecreaseRate);

	//���ܺ���
public:
	//�޸Ŀ��
	VOID ModifyStockScore(SCORE lVariationScore);
	//���ô��
	VOID InitializationStock(SCORE lStockScore, DOUBLE dDecreaseRate);
};

//////////////////////////////////////////////////////////////////////////////////

#endif