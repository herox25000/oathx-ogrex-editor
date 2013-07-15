#ifndef ENCRYPT_HEAD_FILE
#define ENCRYPT_HEAD_FILE


//////////////////////////////////////////////////////////////////////////

//MD5 加密类
class CMD5Encrypt
{
	//函数定义
private:
	//构造函数
	CMD5Encrypt() {}

	//功能函数
public:
	//生成密文
	static void EncryptData(LPCTSTR pszSrcData, TCHAR szMD5Result[33]);
};

//////////////////////////////////////////////////////////////////////////

#endif