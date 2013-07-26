
#include "stdafx.h"
#include "PngButton.h"

// PngButton

PngButton::PngButton(ButtonCallback* pbtnCallback)
{
	m_bEnable			= TRUE;
	m_bCursorOnButton	= FALSE;
	m_bPress			= FALSE;
	m_bChecked          =FALSE;
	m_bVisable			= TRUE;
	m_pbtnCallback		= pbtnCallback;
	m_nWidth =0;       //图
	m_nHeight=0;     //图
	m_statePicNum=5;
	m_nSliceWidth =0;  //每
	m_Point.x=0;
	m_Point.y=0;
	m_buttonState = BUTTON_ENABLE;
     
	//文字方面
	m_bText = false;
	m_ColRGB = RGB(255,255,255);
	m_Label = "";
}
PngButton::~PngButton()
{ 
	  
}
 
void PngButton::InitButton(int x,int y,int theId,HINSTANCE hInstance, LPCTSTR pszResourceName)
{
	SetButtonImage(hInstance,pszResourceName);

	m_Point.x =x;
	m_Point.y = y;
	m_rectButton.left=x;
	m_rectButton.top =y;
	m_rectButton.right	= m_rectButton.left + m_nSliceWidth;
	m_rectButton.bottom	= m_rectButton.top  + m_nHeight;
	m_buttonID = theId;
}

void PngButton::SetButtonString(CFont *FontEx,int Startx,int Starty,CString StrLabel,COLORREF TextColor /* = RGB */)
{
	m_bText = true;
	m_Label = StrLabel;
	m_ColRGB = TextColor;
    m_TextX = Startx; 
	m_TextY = Starty;
	mFontEx = FontEx;
	 return ;
}

void PngButton::setEnable(bool enable)
{
	m_bEnable = enable;
	if(m_bEnable == FALSE)
	{
		 m_buttonState = BUTTON_DISABLE;
	}
	else
	{
		 m_buttonState = BUTTON_ENABLE;
	}
 
}

void PngButton::SetButtonImage( HINSTANCE hInstance, LPCTSTR pszResourceName,int picStateNum )
{
	m_statePicNum = picStateNum;
	m_btnImage.LoadImage(hInstance,pszResourceName);//创建BITMAP对象
	m_nWidth = m_btnImage.GetWidth();
	m_nHeight = m_btnImage.GetHeight();
	m_nSliceWidth = m_nWidth/picStateNum;   //图片切分

}

void PngButton::SetButtonImage( LPCTSTR pszFileName,int picStateNum )
{
	m_statePicNum = picStateNum;
	m_btnImage.LoadImage(pszFileName);//创建BITMAP对象
	m_nWidth = m_btnImage.GetWidth();
	m_nHeight = m_btnImage.GetHeight();
	m_nSliceWidth = m_nWidth/picStateNum;   //图片切分
}
void PngButton::DrawButton( CDC * pDC )
{
	m_btnImage.DrawImage(pDC,m_rectButton.left,m_rectButton.top,m_nSliceWidth,m_nHeight,m_nSliceWidth*m_buttonState,0);
	
	if(m_bText)
	{   
		CFont	*oldfont;
		oldfont = pDC->SelectObject((mFontEx));
		pDC->SetTextColor(m_ColRGB);
		pDC->SetBkMode(TRANSPARENT);
		pDC->TextOut(m_TextX,m_TextY,m_Label);
		pDC->SelectObject(&oldfont);
	}
}


void PngButton::OnMouseLeave(WPARAM wparam, LPARAM lparam)
{
	m_bCursorOnButton	= FALSE;
	m_bPress	= FALSE;

}

void PngButton::OnMouseHover(WPARAM wparam, LPARAM lparam)
{
	m_bPress = TRUE;
}


void PngButton::OnLButtonDown(UINT nFlags, CPoint point)
{
	 
}

void PngButton::OnLButtonUp(UINT nFlags, CPoint point)
{
	 
}
 
bool PngButton::OnMouseMoveEvent( CPoint ClientPoint )
{
	if (m_bVisable && m_bEnable && (!m_bChecked) &&(m_rectButton.PtInRect(ClientPoint) ))
	{
		m_buttonState = BUTTON_HOVER;
		return true;
	}	
	else if(m_bVisable && m_bEnable && (!m_bChecked) )
	{
		m_buttonState = BUTTON_ENABLE;
	}
	return false;
}


bool PngButton::OnLMouseDownEvent( CPoint ClientPoint )
{

	if (m_bVisable && m_bEnable && (!m_bChecked) &&(m_rectButton.PtInRect(ClientPoint) ))
	{
		m_bPress =true;
		m_buttonState = BUTTON_CLICK;
			return true;
	}	
	else if(m_bVisable && m_bEnable && (!m_bChecked) )
	{
		m_bPress =false;
		m_buttonState = BUTTON_ENABLE;
	}
	return false;
}

bool PngButton::OnLMouseUpEvent( CPoint ClientPoint )
{
	if (m_bVisable && m_bEnable && (!m_bChecked)&&(m_rectButton.PtInRect(ClientPoint)))
	{
		m_buttonState = BUTTON_ENABLE;
		
		if (m_bPress  )
		{
			m_pbtnCallback->CallBackId(m_buttonID);
		}
				return true;
	}
	return false;
}

bool PngButton::OnLMouseDoubleEvent( CPoint ClientPoint )
{
	return false;
}

bool PngButton::OnRMouseDownEvent( CPoint ClientPoint )
{
	return false;
}

bool PngButton::OnRMouseUpEvent( CPoint ClientPoint )
{
	return false;
}

bool PngButton::OnRMouseDoubleEvent( CPoint ClientPoint )
{
	return false;
}

PngBtnManager::~PngBtnManager()
{
	VpngBtnItem itr =m_pngbtnManager.begin();
	for (;itr!=m_pngbtnManager.end();++itr)
	{
		PngButton* pTemp = *itr;
		SafeDelete(pTemp);
	}
	m_pngbtnManager.clear();
}

void PngBtnManager::addBtn( PngButton* btn )
{
m_pngbtnManager.push_back(btn);
}


bool PngBtnManager::GetPointButton(CPoint ClientPoint)
{
	VpngBtnItem itr =m_pngbtnManager.begin();
	for (;itr!=m_pngbtnManager.end();++itr)
	{
		if ((*itr)->getVisable() && (*itr)->getEnable())
		{
			if((*itr)->GetButtonRect().PtInRect(ClientPoint))
			{
				 return true;
			}
		}
	}
	return false;
}
void PngBtnManager::DrawBtn( CDC *pDc )
{
	VpngBtnItem itr =m_pngbtnManager.begin();
	for (;itr!=m_pngbtnManager.end();++itr)
	{
		if ((*itr)->getVisable())
		{
			(*itr)->DrawButton(pDc);
		}
	}
}

bool PngBtnManager::OnMouseMoveEvent( CPoint ClientPoint )
{
	VpngBtnItem itr =m_pngbtnManager.begin();
	for (;itr!=m_pngbtnManager.end();++itr)
	{
		if ((*itr)->getVisable())
		{
			if((*itr)->OnMouseMoveEvent(ClientPoint)) return true;
			
		}
	}
	return false;
}

bool PngBtnManager::OnLMouseDownEvent( CPoint ClientPoint )
{
	VpngBtnItem itr =m_pngbtnManager.begin();
	for (;itr!=m_pngbtnManager.end();++itr)
	{
		if ((*itr)->getVisable())
		{
			if((*itr)->OnLMouseDownEvent(ClientPoint)) return true;
		}
	}
	return false;
}

bool PngBtnManager::OnLMouseUpEvent( CPoint ClientPoint )
{
	VpngBtnItem itr =m_pngbtnManager.begin();
	for (;itr!=m_pngbtnManager.end();++itr)
	{
		if ((*itr)->getVisable())
		{
			if((*itr)->OnLMouseUpEvent(ClientPoint)) return true;
		}
	}
		return false;
}

bool PngBtnManager::OnLMouseDoubleEvent( CPoint ClientPoint )
{
	VpngBtnItem itr =m_pngbtnManager.begin();
	for (;itr!=m_pngbtnManager.end();++itr)
	{
		if ((*itr)->getVisable())
		{
			if((*itr)->OnLMouseDoubleEvent(ClientPoint))  return true;
		}
	}
		return false;
}

bool PngBtnManager::OnRMouseDownEvent( CPoint ClientPoint )
{
	VpngBtnItem itr =m_pngbtnManager.begin();
	for (;itr!=m_pngbtnManager.end();++itr)
	{
		if ((*itr)->getVisable())
		{
			if((*itr)->OnRMouseDownEvent(ClientPoint)) return true;
		}
	}
		return false;
}

bool PngBtnManager::OnRMouseUpEvent( CPoint ClientPoint )
{
	VpngBtnItem itr =m_pngbtnManager.begin();
	for (;itr!=m_pngbtnManager.end();++itr)
	{
		if ((*itr)->getVisable())
		{
			if((*itr)->OnRMouseUpEvent(ClientPoint)) return true;
		}
	}
		return false;
}

bool PngBtnManager::OnRMouseDoubleEvent( CPoint ClientPoint )
{
	VpngBtnItem itr =m_pngbtnManager.begin();
	for (;itr!=m_pngbtnManager.end();++itr)
	{
		if ((*itr)->getVisable())
		{
			if((*itr)->OnRMouseDoubleEvent(ClientPoint)) return true;
		}
	}
		return false;
}





