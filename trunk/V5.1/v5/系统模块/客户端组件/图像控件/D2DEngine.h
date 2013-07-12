#ifndef D2D_ENGINE_HEAD_FILE
#define D2D_ENGINE_HEAD_FILE

#pragma once

#include "WHImageHead.h"
#include "D2DInterface.h"
class WH_IMAGE_CLASS CD2DEngine
{
	//����
private:
	static CD2DEngine*				m_pObject;		//ȫ�ֶ���
	static bool						m_bCreate;		//������ʾ

	//����
private:
	HINSTANCE						m_hInst;
	ID2DInterface*					m_pD2DInterface;
	CWnd*							m_pCurrentWnd;	//��ǰ�滭����

private:
	CD2DEngine(void);
	~CD2DEngine(void);

public:
	// ��������ӿ�
	inline static ID2DInterface* GetD2DEngine() 
	{
		if ( !m_bCreate && m_pObject == NULL )
		{
			m_pObject = new CD2DEngine;
			m_bCreate = true;
		}

		if ( m_pObject == NULL )
		{
			return NULL;
		}
		return m_pObject->m_pD2DInterface;
	}

	// ��ʼ�滭
	inline static bool BeginDraw( CWnd* pWnd )
	{
		if ( m_pObject->m_pD2DInterface == NULL )
			return false;
		
		m_pObject->m_pD2DInterface->BeginDraw(pWnd);
		m_pObject->m_pCurrentWnd = pWnd;
		return true;
	}

	// �����滭
	inline static bool EndDraw( CWnd* pWnd )
	{
		if ( m_pObject->m_pD2DInterface == NULL )
			return false;

		m_pObject->m_pD2DInterface->EndDraw(pWnd);
		m_pObject->m_pCurrentWnd = NULL;
		return true;
	}

	//��ȡ��ǰ�Ự����
	inline static CWnd* GetCurrentWnd()
	{
		return m_pObject->m_pCurrentWnd;
	}

	//ɾ������
	inline static void Delete()
	{
		if( m_pObject )
		{
			delete m_pObject;
			m_pObject = NULL;
		}
	}
	
};

#endif
