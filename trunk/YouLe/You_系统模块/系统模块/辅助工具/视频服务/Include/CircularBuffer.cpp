#include "StdAfx.h"
#include "CircularBuffer.h"

CCircularBuffer::CCircularBuffer(int size)
: m_iBufSize(0) //��ʼ��
, m_pBuffer(NULL)
, m_iHeadPos(0)
, m_iTailPos(0)
{
	m_iBufSize=size; //�����С
	m_pBuffer = new char[m_iBufSize]; //��������
}

CCircularBuffer::~CCircularBuffer(void)
{
	delete [] m_pBuffer; //ɾ������
	m_pBuffer = NULL; //����Ϊ��
}
