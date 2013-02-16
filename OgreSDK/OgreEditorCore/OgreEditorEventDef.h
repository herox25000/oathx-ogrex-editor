#pragma once


#define IDT_RENDER_TIMER		0x00000001

// 项目创建完成
#define WM_WIZARD_FNISHED		WM_USER + 1
struct wmProjectCreated
{
	char		Path[MAX_PATH];
	char		Name[MAX_PATH];	
};

// 选择工具项目
#define WM_FILEVIEW_FNISHED		WM_USER + 2

// 选择工具项目
#define WM_SELECT_EDITOR		WM_USER + 2
struct wmSelectEvent
{
	char		Name[MAX_PATH];	
};
