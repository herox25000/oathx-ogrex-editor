#ifndef TEMPLATE_HEAD_FILE
#define TEMPLATE_HEAD_FILE

/////////////////////////////////////////////////////////////////////////////////////////

//��������ά��
#define CountArray(Array) (sizeof(Array)/sizeof(Array[0]))

//�����ַ�����
#define CountString(String) ((UINT)((lstrlen(String)+1)*sizeof(TCHAR)))

//��ȫɾ��ָ��
#define  SafeDelete(pData)	{ try { delete pData; } catch (...) { } pData=NULL; } 

//��ȫɾ��ָ��
#define  SafeDeleteArray(pData)	{ try { delete [] pData; } catch (...) { } pData=NULL; } 

/////////////////////////////////////////////////////////////////////////////////////////

//ģ��ͷ�ļ�
#include "Array.h"
#include "Modelu.h"
#include "Factory.h"

/////////////////////////////////////////////////////////////////////////////////////////

#endif