#ifndef FLOWER_EFFECT_THREAD
#define FLOWER_EFFECT_THREAD

#pragma once
#include "PropertyModule.h"

///////////////////////////////////////////////////////////////////////////////////

//Gif�ṹ
typedef struct tagGifImage{
	WORD lWidth;
	WORD lHeight;
	WORD width;
	WORD height;
	struct flag{
		BYTE d:3;
		BYTE c:1;
		BYTE b:3;
        BYTE a:1;
	}Flag;
}GifImage,*PGifImage;
///////////////////////////////////////////////////////////////////////////////////

//�ʻ��߳�
class PROPERTY_MODULE_CLASS CFlowerEffectThread : public CServiceThread
{
	//��������
protected:
	HWND								m_hFlowerEffectControl;							//Ч������
	WORD								m_wFlowerID;									//�ʻ�����
	CImage								m_ImageBuffer;									//����λͼ

	//װ�ر���
protected:
	HINSTANCE							m_hResource;									//��Դ����
	HRSRC								m_hRSRC;										//��Դ����
    DWORD								m_wGifSize;										//��Դ��С
	HGLOBAL								m_hGlobal;										//��Դ����
    BYTE								*m_lpBy;										//ͼƬ����

	//�豸����
protected:
	HDC									m_hDC;											//�豸���
	CDC									m_DC;											//�豸����
	CDC									*m_pMemoryDC;									//�ڴ��豸

	//��������
public:
	//���캯��
	CFlowerEffectThread(void);
	//��������
	~CFlowerEffectThread(void);

	//���ú���
public:
	//��ʼ����
	void InitThread(HWND HWND, HDC hDC);
	//��������
	bool StartFlowerEffect(WORD wFlowerID);

	//�¼�����
private:
	//��ʼ�¼�
	virtual bool OnThreadStratEvent();
	//ֹͣ�¼�
	virtual bool OnThreadStopEvent();

	//�ڲ�����
private:
	//���к���
	bool RepetitionRun();
	//���к���
	bool RepetitionRunBMP();
};
///////////////////////////////////////////////////////////////////////////////////

#endif

