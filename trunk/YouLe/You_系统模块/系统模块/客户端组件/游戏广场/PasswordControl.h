#ifndef PASSWORD_CONTROL_HEAD_FILE
#define PASSWORD_CONTROL_HEAD_FILE

#pragma once
#define  LEN_PASSWORD 32

//����༭
class  CPasswordControl : public CWnd
{
	//״̬����
protected:
	bool							m_bModify;							//�޸ı�־
	bool							m_bFalsity;							//��ٱ�־
	bool							m_bDrawBorad;						//�滭�߿�
	bool							m_bRenderImage;						//��Ⱦ��־
	TCHAR							m_szPassword[LEN_PASSWORD];					//�û�����

	//�ؼ�����
public:
	CSkinEditEx						m_edPassword;						//����ؼ�

	//��������
public:
	//���캯��
	CPasswordControl();
	//��������
	virtual ~CPasswordControl();

	//���غ���
protected:
	//�󶨺���
	virtual VOID PreSubclassWindow();

	//״̬����
public:
	//�޸�״̬
	bool IsModifyPassword() { return m_bModify; }
	//���״̬
	bool IsFalsityPassword() { return m_bFalsity; }

	//���ܺ���
public:
	//�߿�����
	VOID SetDrawBorad(bool bDrawBorad);
	//��������
	VOID SetUserPassword(LPCTSTR pszPassword);
	//��ȡ����
	LPCTSTR GetUserPassword(TCHAR szPassword[LEN_PASSWORD]);
	//������ɫ
	VOID SetEnableColor(COLORREF crEnableText, COLORREF crEnableBK, COLORREF crEnableBorad);

	//��Ϣ����
protected:
	//�ػ���Ϣ
	VOID OnPaint();
	//�ػ���Ϣ
	VOID OnNcPaint();
	//�滭����
	BOOL OnEraseBkgnd(CDC * pDC);
	//��ȡ����
	VOID OnSetFocus(CWnd * pOldWnd);

	//�ؼ���Ϣ
protected:
	//����ı�
	VOID OnEnChangePassword();
	//���̰�ť
	VOID OnBnClickedKeyboard();

	DECLARE_MESSAGE_MAP()
};

//////////////////////////////////////////////////////////////////////////////////

#endif