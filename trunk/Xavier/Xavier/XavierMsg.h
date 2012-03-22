#ifndef _____XavierMsg_H
#define _____XavierMsg_H

// 项目创建完成
#define WM_CREATE_FNISHED		WM_USER + 1

// 选择工具项目
#define WM_SELECT_EDITOR		WM_USER + 2
struct wmSelectEvent
{
	char		Name[MAX_PATH];	
};

#endif