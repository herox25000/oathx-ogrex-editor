#pragma once

#include "DShow.h"
#pragma comment( lib, "Strmiids.lib" )

class CGraphBuilder
{
private:
	IGraphBuilder* m_pGraphBuilder; //ͼ��ӿ�
	IMediaControl* m_pMediaControl; //����ͼ��ؼ�
	IVideoWindow* m_pVideoWindow; //��Ƶ����
	IBaseFilter* m_pBaseFilter; //����ӿ�
public:
	CGraphBuilder(REFCLSID rclist);
	virtual ~CGraphBuilder(void);

	operator IGraphBuilder*( void ){ return m_pGraphBuilder; };
	IMediaControl* GetMediaControl(void){ return m_pMediaControl; };

	//��ʼ��
	HRESULT Initialize( REFCLSID rclist );

	//�ͷ�
	void Release( void );

	//��ʼ
	HRESULT Run( void );

	//��ͣ
	HRESULT Pause( void );

	//ֹͣ
	HRESULT Stop( void );

	//������ʾ����
	HRESULT SetupVideoWindow( HWND hWnd=NULL );

	//��ʾ
	HRESULT Visible( BOOL Visible=true );

	//ȡPIN
	IPin* GetPin(PIN_DIRECTION PinDirection = PINDIR_INPUT);

	//��ӹ�����
	HRESULT AddFilter( IBaseFilter* pBaseFilter, LPCWSTR pName=L"" );
	HRESULT RemoveFilter( IBaseFilter* pBaseFilter );

	//���
	HRESULT Connect( IPin* OutPin, IPin* InPin );
	HRESULT ConnectDirect( IPin* pOutPin, IPin* pInPin, AM_MEDIA_TYPE* pmt=0 );

	HRESULT Disconnect( IPin* Pin );

	//ȡ�ļ�
	HRESULT RenderFile( LPCWSTR lpFileName, LPCWSTR lpFilterName=NULL );
};
