#include "StdAfx.h"
#include ".\uifont.h"

UIFont::UIFont(void)
{
	m_TitleFont = CreateFont(18,12,0,0,2,false,false,false,
		DEFAULT_CHARSET,OUT_CHARACTER_PRECIS,
		CLIP_CHARACTER_PRECIS,DEFAULT_QUALITY,
		FF_MODERN,"宋体");

	m_InfoFont = CreateFont(15,9,0,0,700,false,false,false,
		DEFAULT_CHARSET,OUT_CHARACTER_PRECIS,
		CLIP_CHARACTER_PRECIS,DEFAULT_QUALITY,
		FF_MODERN,"宋体");

	m_NickFont = CreateFont(11,5,0,0,0,false,false,false,
		DEFAULT_CHARSET,OUT_CHARACTER_PRECIS,
		CLIP_CHARACTER_PRECIS,DEFAULT_QUALITY,
		FF_MODERN,"宋体");

	m_StatusFont = CreateFont(15,9,0,0,0,false,false,false,
		DEFAULT_CHARSET,OUT_CHARACTER_PRECIS,
		CLIP_CHARACTER_PRECIS,DEFAULT_QUALITY,
		FF_MODERN,"宋体");
}

UIFont::~UIFont(void)
{
}
