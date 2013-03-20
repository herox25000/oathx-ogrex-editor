#ifndef MYENCRYPT_H
#define MYENCRYPT_H
#ifdef _MYENCRYPT_ 
#define  MYENCRYPT_DLLAPI  __declspec(dllimport )
#else
#define  MYENCRYPT_DLLAPI  __declspec(dllexport)
#endif

class MYENCRYPT_DLLAPI MyEncrypt
{
public:
MyEncrypt();
virtual ~MyEncrypt();
public:
public:
	//
	ULONG CompressBound(UINT uSize);
	// 数据加密
	virtual bool EncryptNetData(BYTE *pByte,UINT uSize);	/*网络数据TEA加密*/
	virtual bool DecryptNetData(BYTE *pByte,UINT uSize);	/*网络数据TEA解密*/
	virtual bool CompressNetData(BYTE *dest,ULONG *destLen, const BYTE *source, ULONG sourceLen);
	virtual bool UnCompressNetData(BYTE *dest,ULONG *destLen, const BYTE *source, ULONG sourceLen);
};

#endif