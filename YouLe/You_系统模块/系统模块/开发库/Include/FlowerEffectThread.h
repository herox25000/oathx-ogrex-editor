#ifndef FLOWER_EFFECT_THREAD
#define FLOWER_EFFECT_THREAD

#pragma once
#include "PropertyModule.h"

///////////////////////////////////////////////////////////////////////////////////

//Gif结构
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

//鲜花线程
class PROPERTY_MODULE_CLASS CFlowerEffectThread : public CServiceThread
{
	//变量定义
protected:
	HWND								m_hFlowerEffectControl;							//效果窗体
	WORD								m_wFlowerID;									//鲜花索引
	CImage								m_ImageBuffer;									//缓冲位图

	//装载变量
protected:
	HINSTANCE							m_hResource;									//资源变量
	HRSRC								m_hRSRC;										//资源变量
    DWORD								m_wGifSize;										//资源大小
	HGLOBAL								m_hGlobal;										//资源变量
    BYTE								*m_lpBy;										//图片数据

	//设备变量
protected:
	HDC									m_hDC;											//设备句柄
	CDC									m_DC;											//设备变量
	CDC									*m_pMemoryDC;									//内存设备

	//基础函数
public:
	//构造函数
	CFlowerEffectThread(void);
	//析构函数
	~CFlowerEffectThread(void);

	//设置函数
public:
	//初始函数
	void InitThread(HWND HWND, HDC hDC);
	//启动动画
	bool StartFlowerEffect(WORD wFlowerID);

	//事件函数
private:
	//开始事件
	virtual bool OnThreadStratEvent();
	//停止事件
	virtual bool OnThreadStopEvent();

	//内部函数
private:
	//运行函数
	bool RepetitionRun();
	//运行函数
	bool RepetitionRunBMP();
};
///////////////////////////////////////////////////////////////////////////////////

#endif

