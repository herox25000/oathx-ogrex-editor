#pragma once

#include <windows.h>

class CCircularBuffer
{
protected:
	char* m_pBuffer; // ����

	int m_iBufSize; // �����С
	int m_iHeadPos; // ͷλ��
	int m_iTailPos; // βλ��

public:
	CCircularBuffer(int size);
	~CCircularBuffer(void);

	void PutData(char* pData, int len); // ���ݴ��뻺��
	// ����洦
	int IsOverFlowCondition(int &len){return (len >= m_iBufSize-GetValidCount()) ? TRUE: FALSE;}
	int GetValidCount(void); //�õ����ݴ�С
	void BufferResize(void); //�������ӻ�������
	bool IsIndexOverFlow(int &len){return (len+m_iTailPos>=m_iBufSize) ? TRUE:FALSE;} //�ж��Ƿ񳬹�����
	void GetData(char* pData, int len); //�õ�����
	int& GetHeadPos(void){return m_iHeadPos;} //�õ���ʼλ��
	int& GetTailPos(){return m_iTailPos;} //�õ�����λ��
	BOOL HeadIncrease(int increasement=1); //��������ʼλ��
	void SetEmpty() {m_iHeadPos=0; m_iTailPos=0;} // ��ʼͷβ��λ��
};

inline void CCircularBuffer::PutData(char* pData, int len)
{
	if (len<=0) {return;}
	while (IsOverFlowCondition(len)) BufferResize();
	if (IsIndexOverFlow(len))
	{
		int FirstCopyLen = m_iBufSize-m_iTailPos;
		int SecondCopyLen = len - FirstCopyLen;
//		ASSERT(FirstCopyLen);
		CopyMemory(m_pBuffer+m_iTailPos, pData, FirstCopyLen);
		if (SecondCopyLen)
		{
			CopyMemory(m_pBuffer, pData+FirstCopyLen, SecondCopyLen);
			m_iTailPos = SecondCopyLen;
		}
		else m_iTailPos = 0;
	}
	else
	{
		CopyMemory(m_pBuffer+m_iTailPos, pData, len);
		m_iTailPos += len;
	}
}

inline int CCircularBuffer::GetValidCount(void)
{
	int count = m_iTailPos-m_iHeadPos;
	if (count<0) count = m_iBufSize+count;
	return count;
}

inline void CCircularBuffer::BufferResize(void)
{
	int prevBufSize = m_iBufSize;
	m_iBufSize <<= 1;
	char *pNewData = new char[m_iBufSize];
	CopyMemory(pNewData, m_pBuffer, prevBufSize);
	if (m_iTailPos<m_iHeadPos) 
	{
		CopyMemory(pNewData+prevBufSize, m_pBuffer, m_iTailPos);
		m_iTailPos += prevBufSize;
	}
	delete [] m_pBuffer;
	m_pBuffer = pNewData;
}


inline void CCircularBuffer::GetData(char* pData, int len)
{
	//ASSERT(len>0&&len<=GetValidCount());
	if (len < m_iBufSize-m_iHeadPos)
		CopyMemory(pData, m_pBuffer+m_iHeadPos, len);
	else
	{
		int fc, sc;
		fc = m_iBufSize-m_iHeadPos;
		sc = len - fc;
		CopyMemory(pData, m_pBuffer+m_iHeadPos, fc);
		if (sc) CopyMemory(pData+fc, m_pBuffer, sc);
	}
}

inline BOOL CCircularBuffer::HeadIncrease(int increasement)
{
	//ASSERT(increasement<=GetValidCount());
	m_iHeadPos += increasement;
	m_iHeadPos %= m_iBufSize;
	return m_iHeadPos!=m_iTailPos;
}