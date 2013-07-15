#include "StdAfx.h"
#include "graphbuilder.h"

//��ⷵ��ֵ
#ifndef V_RETURN
	#define V_RETURN(x)	{ hr = x; if( hr!=S_OK ) { /*DXTrace( __FILE__, (DWORD)__LINE__, hr, L#x, true );*/ return hr; } }
#endif

//��ȫ�ͷ�
#ifndef SAFE_RELEASE
	#define SAFE_RELEASE(p)	{ if(p) { (p)->Release(); (p)=NULL; } }
#endif

CGraphBuilder::CGraphBuilder(REFCLSID rclist)
{
	m_pGraphBuilder = NULL;
	m_pMediaControl = NULL;
	m_pVideoWindow = NULL;
	m_pBaseFilter = NULL;

	if( FAILED(CoInitialize(NULL)) )
	{
		AfxMessageBox("CoInitialize Failed!\r\n");
	}

	Initialize(rclist);
}

CGraphBuilder::~CGraphBuilder(void)
{
	Release();
	CoUninitialize();
}

//��ʼ��
HRESULT CGraphBuilder::Initialize( REFCLSID rclist )
{
	HRESULT hr = S_FALSE;
	// ����IGraphBuilder�ӿ�
	hr = CoCreateInstance(CLSID_FilterGraph, NULL, CLSCTX_INPROC_SERVER, IID_IGraphBuilder, (void **)&m_pGraphBuilder);
	if( hr!=S_OK )
	{
		goto InitializeError;
	}

	//�õ�IMediaControl�ӿ�
	hr = m_pGraphBuilder->QueryInterface(IID_IMediaControl, (void **)&m_pMediaControl);
	if( hr!=S_OK )
	{
		goto InitializeError;
	}

	//�õ�IVideoWindow�ӿ�
	hr = m_pGraphBuilder->QueryInterface(IID_IVideoWindow, (LPVOID *) &m_pVideoWindow);
	if( hr!=S_OK )
	{
		goto InitializeError;
	}

	//��ʼ��BaseFilter�ӿ�
	hr = CoCreateInstance( rclist, NULL, CLSCTX_INPROC_SERVER, IID_IBaseFilter, (void **)&m_pBaseFilter);
	if( hr!=S_OK )
	{
		goto InitializeError;
	}

	hr = m_pGraphBuilder->AddFilter( m_pBaseFilter, L"" );
	if( hr!=S_OK )
	{
		goto InitializeError;
	}
	return hr;

InitializeError:
	Release();
	return hr;
}

//�ͷ�
void CGraphBuilder::Release( void )
{
	if(m_pMediaControl)
	{
		m_pMediaControl->Stop();
	}

	if( m_pBaseFilter )
	{
		m_pBaseFilter->Stop();
		m_pGraphBuilder->Disconnect( GetPin() );
		m_pGraphBuilder->RemoveFilter( m_pBaseFilter );
		m_pBaseFilter->Release();
		m_pBaseFilter=NULL;
	}

	//�ͷ�
	SAFE_RELEASE(m_pMediaControl);
	SAFE_RELEASE(m_pVideoWindow);
	SAFE_RELEASE(m_pGraphBuilder);
}

//��ʼ
HRESULT CGraphBuilder::Run( void )
{
	if( m_pMediaControl )
	{
		return m_pMediaControl->Run();
	}
	return S_FALSE;
}

//��ͣ
HRESULT CGraphBuilder::Pause( void )
{
	if( m_pMediaControl )
	{
		return m_pMediaControl->Pause();
	}
	return S_FALSE;
}

//ֹͣ
HRESULT CGraphBuilder::Stop( void )
{
	if( m_pMediaControl )
	{
		return m_pMediaControl->Stop();
	}
	return S_FALSE;
}

HRESULT CGraphBuilder::SetupVideoWindow( HWND hWnd )
{
	//���ؼ��;��
	if( !m_pVideoWindow )
		return S_FALSE;

	HRESULT hr;

	//���þ��
	V_RETURN( m_pVideoWindow->put_Owner( (OAHWND)hWnd ) );

	if( hWnd )
	{
		//��������
		V_RETURN( m_pVideoWindow->put_WindowStyle( WS_CHILD | WS_CLIPCHILDREN ) );

		//��ͼ�������������
		CRect rc;
		::GetClientRect( hWnd, &rc );
		V_RETURN( m_pVideoWindow->SetWindowPosition( 0, 0, rc.right, rc.bottom ) );

		//��ʾ
		//V_RETURN( m_pVideoWindow->put_Visible( OATRUE ) );
	}
	else
	{
		//��������
		V_RETURN( m_pVideoWindow->put_WindowStyle( WS_POPUPWINDOW | WS_CAPTION ) );

		//��ͼ�������������
		V_RETURN( m_pVideoWindow->SetWindowPosition( 0, 0, 320, 240 ) );
	}

	return hr;
}

HRESULT CGraphBuilder::Visible( BOOL Visible )
{
	if(m_pVideoWindow)
	{
		HRESULT hr;
		V_RETURN( m_pVideoWindow->put_Visible(OAFALSE) );
		return hr;
	}
	return S_FALSE;
}

//ȡ�豸���Pin
IPin* CGraphBuilder::GetPin(PIN_DIRECTION PinDirection)
{
	IPin * foundPin = NULL;

	if( m_pBaseFilter )
	{
		//����ö��
		IEnumPins * pinEnum = NULL;
		if ( m_pBaseFilter->EnumPins(&pinEnum)==S_OK )
		{
			//��λ
			pinEnum->Reset();

			//ѭ��ÿ��PIN
			ULONG fetchCount = 0;
			IPin * pin = NULL;
			while ( !foundPin && S_OK==(pinEnum->Next(1, &pin, &fetchCount)) && fetchCount )
			{
				if (pin)
				{
					//�õ�PIN��Ϣ
					PIN_INFO pinInfo;
					if ( S_OK==pin->QueryPinInfo(&pinInfo) )
					{
						//����Ƿ������PIN
						if (pinInfo.dir == PinDirection)
						{
							pin->AddRef(); //��һ����
							foundPin = pin; //����PIN
						}
						pinInfo.pFilter->Release();
					}
					pin->Release();
				}
			}
			pinEnum->Release();
		}
	}
	if (foundPin)
	{
		foundPin->Release();
	}
    return foundPin;
}

HRESULT CGraphBuilder::AddFilter( IBaseFilter* pBaseFilter, LPCWSTR pName )
{
	if( !m_pGraphBuilder )
		return S_FALSE;
	return m_pGraphBuilder->AddFilter( pBaseFilter, pName );
	
}

HRESULT CGraphBuilder::RemoveFilter( IBaseFilter* pBaseFilter )
{
	if( !m_pGraphBuilder || !pBaseFilter )
		return S_FALSE;
	return m_pGraphBuilder->RemoveFilter( pBaseFilter );
}

HRESULT CGraphBuilder::Connect( IPin* pOutPin, IPin* pInPin )
{
	if( !m_pGraphBuilder )
		return S_FALSE;
	return m_pGraphBuilder->Connect( pOutPin, pInPin );
}

HRESULT CGraphBuilder::ConnectDirect( IPin* pOutPin, IPin* pInPin, AM_MEDIA_TYPE* pmt )
{
	if( !m_pGraphBuilder )
		return S_FALSE;
	return m_pGraphBuilder->ConnectDirect( pOutPin, pInPin, pmt );
}

HRESULT CGraphBuilder::Disconnect( IPin* Pin )
{
	if( !m_pGraphBuilder )
		return S_FALSE;
	return m_pGraphBuilder->Disconnect( Pin );
}

HRESULT CGraphBuilder::RenderFile( LPCWSTR lpFileName, LPCWSTR lpFilterName )
{
    HRESULT hr;
	V_RETURN( Stop() );

	if( !m_pGraphBuilder )
		return S_FALSE;
    return m_pGraphBuilder->RenderFile( lpFileName, NULL );
}