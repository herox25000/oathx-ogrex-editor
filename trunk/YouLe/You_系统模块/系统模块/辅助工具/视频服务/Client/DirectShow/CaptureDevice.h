#pragma once

#include "DShow.h"
#pragma comment( lib, "Strmiids.lib" )

typedef HRESULT (CALLBACK *ENUMCALLBACK)( int index, VARIANT* var/*����ֵ*/, IMoniker *pM/*�豸*/, LPVOID lp/*����*/, BOOL& bCancel/*�Ƿ��˳�ѭ��*/ );
typedef HRESULT (CALLBACK *ENUMINPUTCALLBACK)( const char* pName/*����ֵ*/, IPin * pin /*�豸*/, LPVOID lp/*����*/, BOOL& bCancel/*�Ƿ��˳�ѭ��*/ );

//��ȡ��
class CCaptureDevice
{
private:
	IBaseFilter* m_pBaseFilter; //Filter�ӿ� ����ѡ���豸
public:
	CCaptureDevice(void);
	virtual ~CCaptureDevice(void);

	operator IBaseFilter*( void ){ return m_pBaseFilter; };

	//ö���豸 ����1���豸ID ����CLSID_VideoInputDeviceCategory //��F12��������
	HRESULT EnumDevices( REFCLSID clsidDeviceClass, ENUMCALLBACK pEnumCallBack, LPVOID lp );

	//�ͷ�
	void Release( void );

	//�ﶨ�豸
	HRESULT BindFilter( REFCLSID clsidDeviceClass/*�豸����ID*/, int DeviceIndex/*�豸�������,��ö��˳��õ�*/ );

	//ȡ�豸���Pin
	IPin* GetPin(void);

	//��ʽ
	void AdjustOutput(void);
	AM_MEDIA_TYPE * SelectMediaType(void);
	IAMStreamConfig * GetStreamConfig(void);
	void EnumInputList( ENUMINPUTCALLBACK EnumInputCallBack, LPVOID lp );
	void SelectInput( char* pName = "��˷�" );
	void SetCaptureBufferSize(void);
};
