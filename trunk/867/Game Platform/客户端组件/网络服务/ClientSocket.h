#ifndef CLIENT_SOCKET_HEAD_FILE
#define CLIENT_SOCKET_HEAD_FILE

#pragma once

#include "NetworkService.h"

//////////////////////////////////////////////////////////////////////////

//����������
class CClientSocket : public CWnd, public ITCPSocket
{
	//״̬����
protected:
	BYTE							m_bCloseByServer;					//�رշ�ʽ
	tagProxyServerInfo				m_ProxyInfo;						//������Ϣ
	enSocketState					m_SocketState;						//����״̬
	ITCPSocketSink					* m_pITCPSocketSink;				//�ص��ӿ�

	//���ı���
protected:
	SOCKET							m_hSocket;							//���Ӿ��
	WORD							m_wRecvSize;						//���ճ���
	BYTE							m_cbRecvBuf[SOCKET_BUFFER*10];		//���ջ���

	//��������
protected:
	DWORD							m_dwSendTickCount;					//����ʱ��
	DWORD							m_dwRecvTickCount;					//����ʱ��
	DWORD							m_dwSendPacketCount;				//���ͼ���
	DWORD							m_dwRecvPacketCount;				//���ܼ���

	//��������
protected:
	BYTE							m_cbSendRound;						//�ֽ�ӳ��
	BYTE							m_cbRecvRound;						//�ֽ�ӳ��
	DWORD							m_dwSendXorKey;						//������Կ
	DWORD							m_dwRecvXorKey;						//������Կ
	//static BYTE						m_SendByteMap[256];					//�ֽ�ӳ���
	//static BYTE						m_RecvByteMap[256];					//�ֽ�ӳ���

	//��������
public:
	//���캯��
	CClientSocket();
	//��������
	virtual ~CClientSocket();

	//�����ӿ�
public:
	//�ͷŶ���
	virtual void __cdecl Release() { delete this; }
	//�Ƿ���Ч
	//virtual bool __cdecl IsValid() { return AfxIsValidAddress(this,sizeof(CClientSocket))?true:false; }
	//�ӿڲ�ѯ
	virtual void * __cdecl QueryInterface(const IID & Guid, DWORD dwQueryVer);

	//�ӿں���
public:
	//ȡ������
	virtual void __cdecl CancelProxyServer();
	//���������
	virtual void __cdecl SetProxyServerInfo(enProxyServerType ProxyServerType,tagProxyServerInfo & ProxyInfo);
	//���ýӿ�
	virtual bool __cdecl SetTCPSocketSink(IUnknownEx * pIUnknownEx);
	//��ȡ�ӿ�
	virtual void * __cdecl GetSocketSink(const IID & Guid, DWORD dwQueryVer);
	//��ȡ���ͼ��
	virtual DWORD __cdecl GetLastSendTick() { return m_dwSendTickCount; }
	//��ȡ���ռ��
	virtual DWORD __cdecl GetLastRecvTick() { return m_dwRecvTickCount; }
	//��ȡ������Ŀ
	virtual DWORD __cdecl GetSendPacketCount() { return m_dwSendPacketCount; }
	//��ȡ������Ŀ
	virtual DWORD __cdecl GetRecvPacketCount() { return m_dwRecvPacketCount; }
	//��ȡ״̬
	virtual enSocketState __cdecl GetSocketStatus() { return m_SocketState; }
	//���ӷ�����
	virtual BYTE __cdecl Connect(DWORD dwServerIP, WORD wPort);
	//���ӷ�����
	virtual BYTE __cdecl Connect(const LPCTSTR szServerIP, WORD wPort);
	//���ͺ���
	virtual bool __cdecl SendData(WORD wMainCmdID, WORD wSubCmdID);
	//���ͺ���
	virtual bool __cdecl SendData(WORD wMainCmdID, WORD wSubCmdID, void * pData, WORD wDataSize);
	//�ر�����
	virtual bool __cdecl CloseSocket();

	//��������
protected:
	//���͵�ַ
	DWORD TranslateAddr(LPCTSTR pszServerAddr);
	//���Ӵ���
	LPCTSTR GetConnectError(int iErrorCode, LPTSTR pszBuffer, WORD wBufferSize);
	//��������
	bool SendBuffer(void * pBuffer, WORD wSendSize);
	//��������
	WORD EncryptBuffer(BYTE * pcbDataBuffer, WORD wDataSize, WORD wBufferSize);
	//��������
	WORD CrevasseBuffer(BYTE pcbDataBuffer[], WORD wDataSize);

	//������
protected:
	//��������
	LRESULT OnSocketNotifyConnect(WPARAM wParam, LPARAM lParam);
	//�����ȡ
	LRESULT OnSocketNotifyRead(WPARAM wParam, LPARAM lParam);
	//����ر�
	LRESULT OnSocketNotifyClose(WPARAM wParam, LPARAM lParam);

	//��������
private:
	//���ӳ��
	inline WORD SeedRandMap(WORD wSeed);
	//ӳ�䷢������
	inline BYTE MapSendByte(BYTE const cbData);
	//ӳ���������
	inline BYTE MapRecvByte(BYTE const cbData);

	//��Ϣӳ��
protected:
	//SOCKET ��Ϣ�������
	LRESULT	OnSocketNotify(WPARAM wParam, LPARAM lParam);

	DECLARE_MESSAGE_MAP()
};

//////////////////////////////////////////////////////////////////////////

#endif