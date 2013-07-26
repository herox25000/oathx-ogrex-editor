
#ifndef PNG_BUTTON_HEAD_FILE
#define PNG_BUTTON_HEAD_FILE


#pragma once

#include <vector>
using namespace std;
enum BUTTON_STATE
{
	BUTTON_ENABLE = 0,
	BUTTON_HOVER = 1,
	BUTTON_CLICK = 2,
	//BUTTON_CHECK = 3,
	BUTTON_DISABLE= 3, 
};               //按钮状态
// PngButton.h
class ButtonCallback
{
public:
	ButtonCallback(){};
	virtual void CallBackId(int id, WPARAM wParam = 0, LPARAM lParam = 0) =NULL;
};

class PngButton
{
public:
	PngButton(ButtonCallback* pbtnCallback);
	virtual ~PngButton();
public:
	//得到宽度
	INT GetWidth(){return m_nSliceWidth;}
	//得到高度
	INT GetHeight(){return m_nHeight;};

	//得到ID
	int  GetID() {return m_buttonID;}
	//自绘Button
	void DrawButton(CDC * pDC);
	//弹起
	void OnLButtonUp(UINT nFlags, CPoint point);
	//按下
	void OnLButtonDown(UINT nFlags, CPoint point);
	//移动
	void OnMouseHover(WPARAM wparam, LPARAM lparam);
	//离开
	void OnMouseLeave(WPARAM wparam, LPARAM lparam);
	
	//初始化Button
	void  InitButton(int x,int y,int theId,HINSTANCE hInstance, LPCTSTR pszResourceName);
    //设置文字
	void  SetButtonString(CFont *FontEx,int Startx,int Starty,CString StrLabel,COLORREF	TextColor = RGB(255,255,255));
	//得到当前点
	CPoint getButtonPos(){return m_Point;};
	//设置可用
	void setEnable(bool enable =true);
	//得到可用
	BOOL getEnable(){return m_bEnable;};
	//设置隐藏
	void setVisable(bool visable =true){ m_bVisable = visable;};
	//得到隐藏标示
	BOOL getVisable(){return m_bVisable;};
	//得到状态
	BUTTON_STATE getbuttonState(){return m_buttonState;};
    //得到区域
	CRect GetButtonRect() {return m_rectButton;}
	//鼠标移动事件
	bool OnMouseMoveEvent(CPoint ClientPoint);
	//鼠标左键事件
	bool OnLMouseDownEvent(CPoint ClientPoint);
	//鼠标左键事件
	bool OnLMouseUpEvent(CPoint ClientPoint);
	//鼠标左键事件
	bool OnLMouseDoubleEvent(CPoint ClientPoint);
	//鼠标右键事件
	bool OnRMouseDownEvent(CPoint ClientPoint);
	//鼠标右键事件
	bool OnRMouseUpEvent(CPoint ClientPoint);
	//鼠标右键事件
	bool OnRMouseDoubleEvent(CPoint ClientPoint);

private:
	//加载底图
	void SetButtonImage(LPCTSTR pszFileName,int picStateNum =4);
	//加载底图
	void SetButtonImage(HINSTANCE hInstance, LPCTSTR pszResourceName,int picStateNum =4);

private:
	BOOL			m_bEnable;			// 按钮是否禁用		
	BOOL			m_bCursorOnButton; 	// 鼠标是否在按钮上
	BOOL			m_bPress;			// 按钮是否被按下
	BOOL			m_bChecked;			// checkbutton check状态
	
	BOOL			m_bVisable;
	int				m_nWidth;				//图片宽
	int				m_nHeight;			    //图片高
	int				m_statePicNum;
	int				m_nSliceWidth;			//每一块图片的宽
	CPngImage		m_btnImage;				//按钮图片
	CRect			m_rectButton;           //按钮区域
	CPoint			m_Point;
	ButtonCallback* m_pbtnCallback;
	BUTTON_STATE    m_buttonState;
	int				m_buttonID;
   
	CString         m_Label;              //文字描述
	bool            m_bText;              //是否有文字描述
	COLORREF        m_ColRGB;             //个性颜色
	int             m_TextX;
	int             m_TextY;
	CFont           *mFontEx;
};

typedef vector<PngButton*>  VpngBtn;
typedef vector<PngButton*>::iterator VpngBtnItem;
class PngBtnManager
{
public:
	PngBtnManager(){};
	~PngBtnManager();
	void addBtn(PngButton* btn);
	void DrawBtn(CDC *pDc);

	//鼠标移动事件
	bool OnMouseMoveEvent(CPoint ClientPoint);
	//鼠标左键事件
	bool OnLMouseDownEvent(CPoint ClientPoint);
	//鼠标左键事件
	bool OnLMouseUpEvent(CPoint ClientPoint);
	//鼠标左键事件
	bool OnLMouseDoubleEvent(CPoint ClientPoint);
	//鼠标右键事件
	bool OnRMouseDownEvent(CPoint ClientPoint);
	//鼠标右键事件
	bool OnRMouseUpEvent(CPoint ClientPoint);
	//鼠标右键事件
	bool OnRMouseDoubleEvent(CPoint ClientPoint);
	//测试是否落在按钮上
	bool   GetPointButton(CPoint ClientPoint);

private:
	VpngBtn  m_pngbtnManager;
};

#endif

