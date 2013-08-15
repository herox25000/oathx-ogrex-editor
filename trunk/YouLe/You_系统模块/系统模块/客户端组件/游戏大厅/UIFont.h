#pragma once

class UIFont
{
public:
	UIFont(void);
	~UIFont(void);
public:
	HFONT m_TitleFont;
	HFONT m_InfoFont;
	HFONT m_NickFont;
	HFONT m_StatusFont;
};
