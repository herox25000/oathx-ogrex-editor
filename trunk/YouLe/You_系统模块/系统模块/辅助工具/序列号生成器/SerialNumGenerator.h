// SerialNumGenerator.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error �ڰ������� PCH �Ĵ��ļ�֮ǰ������stdafx.h��
#endif

#include "resource.h"		// ������


// CSerialNumGeneratorApp:
// �йش����ʵ�֣������ SerialNumGenerator.cpp
//

class CSerialNumGeneratorApp : public CWinApp
{
public:
	CSerialNumGeneratorApp();

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CSerialNumGeneratorApp theApp;
