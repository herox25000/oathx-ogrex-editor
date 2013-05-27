#pragma once


#define IDT_RENDER_UPDATE		0x00000001

// 项目创建完成
#define WM_WIZARD_FNISHED		WM_USER + 1

// 选择工具项目
#define WM_FILEVIEW_FNISHED		WM_USER + 2

// 选择工具项目
#define WM_SELECT_EDITOR		WM_USER + 3
struct wmSelectEvent
{
	char		Name[MAX_PATH];	
};

#define WM_CREATE_UNIT			WM_USER + 4
struct wmCreateUnit
{
	char		Name[MAX_PATH];
};