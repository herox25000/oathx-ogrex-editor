#ifndef ENCRYPT_HEAD_FILE
#define ENCRYPT_HEAD_FILE


//////////////////////////////////////////////////////////////////////////

//MD5 ������
class CMD5Encrypt
{
	//��������
private:
	//���캯��
	CMD5Encrypt() {}

	//���ܺ���
public:
	//��������
	static void EncryptData(LPCTSTR pszSrcData, TCHAR szMD5Result[33]);
};

//////////////////////////////////////////////////////////////////////////

#endif