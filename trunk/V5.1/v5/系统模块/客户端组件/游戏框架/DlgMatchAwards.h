#ifndef DLG_MATCH_AWARDS_HEAD_FILE
#define DLG_MATCH_AWARDS_HEAD_FILE

#pragma once

#include "afxwin.h"
#include "GameFrameHead.h"

//////////////////////////////////////////////////////////////////////////

//������״
class GAME_FRAME_CLASS CDlgMatchAwards :public CDialog
{
	//�ؼ�����
public:
	CSkinButton						m_btCloseAwards;					//�رհ�ť
	CMD_GR_MatchResult				*m_pMatchResult;					//�������

	//����ؼ�
protected:
	CSkinLayered					m_SkinLayered;						//�ֲ㴰��

	//��������
public:
	//���캯��
	CDlgMatchAwards(void);
	//��������
	virtual ~CDlgMatchAwards(void);
	//���ò���
	void SetMatchResult(CMD_GR_MatchResult *pMatchResult){m_pMatchResult=pMatchResult;}

	//���غ���
protected:
	//ȷ������
	virtual VOID OnOK();

	afx_msg void OnPaint();

	virtual void DoDataExchange(CDataExchange* pDX);
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnWindowPosChanged(WINDOWPOS* lpwndpos);

	DECLARE_MESSAGE_MAP()

};

#endif