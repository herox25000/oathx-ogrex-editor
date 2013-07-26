
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
};               //��ť״̬
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
	//�õ����
	INT GetWidth(){return m_nSliceWidth;}
	//�õ��߶�
	INT GetHeight(){return m_nHeight;};

	//�õ�ID
	int  GetID() {return m_buttonID;}
	//�Ի�Button
	void DrawButton(CDC * pDC);
	//����
	void OnLButtonUp(UINT nFlags, CPoint point);
	//����
	void OnLButtonDown(UINT nFlags, CPoint point);
	//�ƶ�
	void OnMouseHover(WPARAM wparam, LPARAM lparam);
	//�뿪
	void OnMouseLeave(WPARAM wparam, LPARAM lparam);
	
	//��ʼ��Button
	void  InitButton(int x,int y,int theId,HINSTANCE hInstance, LPCTSTR pszResourceName);
    //��������
	void  SetButtonString(CFont *FontEx,int Startx,int Starty,CString StrLabel,COLORREF	TextColor = RGB(255,255,255));
	//�õ���ǰ��
	CPoint getButtonPos(){return m_Point;};
	//���ÿ���
	void setEnable(bool enable =true);
	//�õ�����
	BOOL getEnable(){return m_bEnable;};
	//��������
	void setVisable(bool visable =true){ m_bVisable = visable;};
	//�õ����ر�ʾ
	BOOL getVisable(){return m_bVisable;};
	//�õ�״̬
	BUTTON_STATE getbuttonState(){return m_buttonState;};
    //�õ�����
	CRect GetButtonRect() {return m_rectButton;}
	//����ƶ��¼�
	bool OnMouseMoveEvent(CPoint ClientPoint);
	//�������¼�
	bool OnLMouseDownEvent(CPoint ClientPoint);
	//�������¼�
	bool OnLMouseUpEvent(CPoint ClientPoint);
	//�������¼�
	bool OnLMouseDoubleEvent(CPoint ClientPoint);
	//����Ҽ��¼�
	bool OnRMouseDownEvent(CPoint ClientPoint);
	//����Ҽ��¼�
	bool OnRMouseUpEvent(CPoint ClientPoint);
	//����Ҽ��¼�
	bool OnRMouseDoubleEvent(CPoint ClientPoint);

private:
	//���ص�ͼ
	void SetButtonImage(LPCTSTR pszFileName,int picStateNum =4);
	//���ص�ͼ
	void SetButtonImage(HINSTANCE hInstance, LPCTSTR pszResourceName,int picStateNum =4);

private:
	BOOL			m_bEnable;			// ��ť�Ƿ����		
	BOOL			m_bCursorOnButton; 	// ����Ƿ��ڰ�ť��
	BOOL			m_bPress;			// ��ť�Ƿ񱻰���
	BOOL			m_bChecked;			// checkbutton check״̬
	
	BOOL			m_bVisable;
	int				m_nWidth;				//ͼƬ��
	int				m_nHeight;			    //ͼƬ��
	int				m_statePicNum;
	int				m_nSliceWidth;			//ÿһ��ͼƬ�Ŀ�
	CPngImage		m_btnImage;				//��ťͼƬ
	CRect			m_rectButton;           //��ť����
	CPoint			m_Point;
	ButtonCallback* m_pbtnCallback;
	BUTTON_STATE    m_buttonState;
	int				m_buttonID;
   
	CString         m_Label;              //��������
	bool            m_bText;              //�Ƿ�����������
	COLORREF        m_ColRGB;             //������ɫ
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

	//����ƶ��¼�
	bool OnMouseMoveEvent(CPoint ClientPoint);
	//�������¼�
	bool OnLMouseDownEvent(CPoint ClientPoint);
	//�������¼�
	bool OnLMouseUpEvent(CPoint ClientPoint);
	//�������¼�
	bool OnLMouseDoubleEvent(CPoint ClientPoint);
	//����Ҽ��¼�
	bool OnRMouseDownEvent(CPoint ClientPoint);
	//����Ҽ��¼�
	bool OnRMouseUpEvent(CPoint ClientPoint);
	//����Ҽ��¼�
	bool OnRMouseDoubleEvent(CPoint ClientPoint);
	//�����Ƿ����ڰ�ť��
	bool   GetPointButton(CPoint ClientPoint);

private:
	VpngBtn  m_pngbtnManager;
};

#endif

