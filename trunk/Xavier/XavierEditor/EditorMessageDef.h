#pragma once


#define IDT_RENDER_UPDATE		0x00000001

// ��Ŀ�������
#define WM_WIZARD_FNISHED		WM_USER + 1

// ѡ�񹤾���Ŀ
#define WM_FILEVIEW_FNISHED		WM_USER + 2

// ѡ�񹤾���Ŀ
#define WM_SELECT_EDITOR		WM_USER + 2
struct wmSelectEvent
{
	char		Name[MAX_PATH];	
};
