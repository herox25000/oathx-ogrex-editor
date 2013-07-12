#include "StdAfx.h"
#include "DlgBuyProperty.h"
#include "GamePropertyItem.h"
#include "GamePropertyManager.h"

//////////////////////////////////////////////////////////////////////////////////

//���캯��
CGamePropertyItem::CGamePropertyItem()
{
	//���ñ���
	ZeroMemory(&m_PropertyInfo,sizeof(m_PropertyInfo));
	ZeroMemory(&m_PropertyAttrib,sizeof(m_PropertyAttrib));

	return;
}

//��������
CGamePropertyItem::~CGamePropertyItem()
{
}

//��ʾ��Ϣ
LPCTSTR CGamePropertyItem::GetNotifyMessage(LPCTSTR szSourceNickName,LPCTSTR szTargerNickName,WORD wItemCount,LPTSTR szResultMessage)
{
	return szResultMessage;
}

//ʹ�õ���
VOID CGamePropertyItem::ShowBuyPropertyWnd(IGamePropertySink * pIGamePropertySink)
{
	//���򴰿�
	CDlgBuyProperty::ShowBuyPropertyWnd(this,pIGamePropertySink);

	return;
}

//�ı��¼�
VOID CGamePropertyItem::OnEventPerformCommand(WORD wCommandID,VOID * pCmdData)
{
	//���򴰿�
	CDlgBuyProperty::OnEventPerformCommand(wCommandID,pCmdData);
}

//////////////////////////////////////////////////////////////////////////////////

//���캯��
CGamePropertyCar::CGamePropertyCar()
{
	//���ñ���
	m_PropertyAttrib.wIndex=PROPERTY_ID_CAR;
	m_PropertyAttrib.wPropertyType=PT_TYPE_PRESENT;
	m_PropertyAttrib.wServiceArea=PT_SERVICE_AREA_PLAYER|PT_SERVICE_AREA_LOOKON;
	lstrcpyn(m_PropertyAttrib.szMeasuringunit,TEXT("��"),CountArray(m_PropertyAttrib.szMeasuringunit));
	lstrcpyn(m_PropertyAttrib.szPropertyName,TEXT("��������"),CountArray(m_PropertyAttrib.szPropertyName));
	lstrcpyn(m_PropertyAttrib.szRegulationsInfo,TEXT("�����ڻ�����ͷ�񸽽���������ɲ���Ķ�����Ч"),CountArray(m_PropertyAttrib.szRegulationsInfo));
	
	return;
}

//��������
CGamePropertyCar::~CGamePropertyCar()
{
}

//ͼƬ��Ϣ
VOID CGamePropertyCar::GetImageInfo(tagPropertyImage & PropertyImage)
{
	//���ñ���
	PropertyImage.pszFlash=TEXT("����.swf");
	PropertyImage.pszImageID=TEXT("IMAGE_CAR");
	PropertyImage.pszSymbolID=TEXT("SYMBOL_CAR");
	PropertyImage.hResInstance=GetModuleHandle(GAME_PROPERTY_DLL_NAME);

	return;
}

//��ʾ��Ϣ
LPCTSTR CGamePropertyCar::GetNotifyMessage(LPCTSTR szSourceNickName,LPCTSTR szTargerNickName,WORD wItemCount,LPTSTR szResultMessage)
{
	//�������
	TCHAR szMessage[128]=TEXT("");
	_sntprintf(szMessage,CountArray(szMessage),TEXT("[ %s ] �͸� [ %s ] %d �������ܳ��������簡��"),szSourceNickName,szTargerNickName,wItemCount);

	//��������
	CopyMemory(szResultMessage,szMessage,sizeof(szMessage));

	return szResultMessage;
}

//////////////////////////////////////////////////////////////////////////////////

//���캯��
CGamePropertyEgg::CGamePropertyEgg()
{
	//���ñ���
	m_PropertyAttrib.wIndex=PROPERTY_ID_EGG;
	m_PropertyAttrib.wPropertyType=PT_TYPE_PRESENT;
	m_PropertyAttrib.wServiceArea=PT_SERVICE_AREA_PLAYER|PT_SERVICE_AREA_LOOKON;
	lstrcpyn(m_PropertyAttrib.szMeasuringunit,TEXT("��"),CountArray(m_PropertyAttrib.szMeasuringunit));
	lstrcpyn(m_PropertyAttrib.szPropertyName,TEXT("��������"),CountArray(m_PropertyAttrib.szPropertyName));
	lstrcpyn(m_PropertyAttrib.szRegulationsInfo,TEXT("�����ڻ�����ͷ�񸽽������Գ����Ķ�����Ч"),CountArray(m_PropertyAttrib.szRegulationsInfo));
	
	return;
}

//��������
CGamePropertyEgg::~CGamePropertyEgg()
{
}

//ͼƬ��Ϣ
VOID CGamePropertyEgg::GetImageInfo(tagPropertyImage & PropertyImage)
{
	//���ñ���
	PropertyImage.pszFlash=TEXT("����.swf");
	PropertyImage.pszImageID=TEXT("IMAGE_EGG");
	PropertyImage.pszSymbolID=TEXT("SYMBOL_EGG");
	PropertyImage.hResInstance=GetModuleHandle(GAME_PROPERTY_DLL_NAME);

	return;
}

//��ʾ��Ϣ
LPCTSTR CGamePropertyEgg::GetNotifyMessage(LPCTSTR szSourceNickName,LPCTSTR szTargerNickName,WORD wItemCount,LPTSTR szResultMessage)
{
	//�������
	TCHAR  szMessage[128]=TEXT("");
	_sntprintf(szMessage,CountArray(szMessage),TEXT("[ %s ] ���� [ %s ] %d �ų�����������Զ���ˣ�"),szSourceNickName,szTargerNickName,wItemCount);

	//��������
	CopyMemory(szResultMessage,szMessage,sizeof(szMessage));

	return szResultMessage;
}

//////////////////////////////////////////////////////////////////////////////////

//���캯��
CGamePropertyClap::CGamePropertyClap()
{
	//���ñ���
	m_PropertyAttrib.wIndex=PROPERTY_ID_CLAP;
	m_PropertyAttrib.wPropertyType=PT_TYPE_PRESENT;
	m_PropertyAttrib.wServiceArea=PT_SERVICE_AREA_PLAYER|PT_SERVICE_AREA_LOOKON;
	lstrcpyn(m_PropertyAttrib.szMeasuringunit,TEXT("��"),CountArray(m_PropertyAttrib.szMeasuringunit));
	lstrcpyn(m_PropertyAttrib.szPropertyName,TEXT("��������"),CountArray(m_PropertyAttrib.szPropertyName));
	lstrcpyn(m_PropertyAttrib.szRegulationsInfo,TEXT("������ʹ����ͷ�񸽽��������ֶ�����Ч"),CountArray(m_PropertyAttrib.szRegulationsInfo));
	
	return;
}

//��������
CGamePropertyClap::~CGamePropertyClap()
{
}

//ͼƬ��Ϣ
VOID CGamePropertyClap::GetImageInfo(tagPropertyImage & PropertyImage)
{
	//���ñ���
	PropertyImage.pszFlash=TEXT("����.swf");
	PropertyImage.pszImageID=TEXT("IMAGE_CLAP");
	PropertyImage.pszSymbolID=TEXT("SYMBOL_CLAP");
	PropertyImage.hResInstance=GetModuleHandle(GAME_PROPERTY_DLL_NAME);

	return;
}

//��ʾ��Ϣ
LPCTSTR CGamePropertyClap::GetNotifyMessage(LPCTSTR szSourceNickName,LPCTSTR szTargerNickName,WORD wItemCount,LPTSTR szResultMessage)
{
	//�������
	TCHAR   szMessage[128]=TEXT("");
	_sntprintf(szMessage,CountArray(szMessage),TEXT("[ %s ] Ϊ [ %s ]���ҹ��ƣ���������ģ�"),szSourceNickName,szTargerNickName);

	//��������
	CopyMemory(szResultMessage,szMessage,sizeof(szMessage));

	return szResultMessage;
}

//////////////////////////////////////////////////////////////////////////////////

//���캯��
CGamePropertyKiss::CGamePropertyKiss()
{
	//���ñ���
	m_PropertyAttrib.wIndex=PROPERTY_ID_KISS;
	m_PropertyAttrib.wPropertyType=PT_TYPE_PRESENT;
	m_PropertyAttrib.wServiceArea=PT_SERVICE_AREA_PLAYER|PT_SERVICE_AREA_LOOKON;
	lstrcpyn(m_PropertyAttrib.szMeasuringunit,TEXT("��"),CountArray(m_PropertyAttrib.szMeasuringunit));
	lstrcpyn(m_PropertyAttrib.szPropertyName,TEXT("��������"),CountArray(m_PropertyAttrib.szPropertyName));
	lstrcpyn(m_PropertyAttrib.szRegulationsInfo,TEXT("�����ڻ�����ͷ�񸽽������ǵĶ�����Ч"),CountArray(m_PropertyAttrib.szRegulationsInfo));
	
	return;
}

//��������
CGamePropertyKiss::~CGamePropertyKiss()
{
}

//ͼƬ��Ϣ
VOID CGamePropertyKiss::GetImageInfo(tagPropertyImage & PropertyImage)
{
	//���ñ���
	PropertyImage.pszFlash=TEXT("����.swf");
	PropertyImage.pszImageID=TEXT("IMAGE_KISS");
	PropertyImage.pszSymbolID=TEXT("SYMBOL_KISS");
	PropertyImage.hResInstance=GetModuleHandle(GAME_PROPERTY_DLL_NAME);

	return;
}

//��ʾ��Ϣ
LPCTSTR CGamePropertyKiss::GetNotifyMessage(LPCTSTR szSourceNickName,LPCTSTR szTargerNickName,WORD wItemCount,LPTSTR szResultMessage)
{
	//�������
	TCHAR szMessage[128]=TEXT("");
	_sntprintf(szMessage,CountArray(szMessage),TEXT("[ %s ] �׸� [ %s ] %d �����ǣ��ú���ѽ��"),szSourceNickName,szTargerNickName,wItemCount);

	//��������
	CopyMemory(szResultMessage,szMessage,sizeof(szMessage));

	return szResultMessage;
}

//////////////////////////////////////////////////////////////////////////////////

//���캯��
CGamePropertyBeer::CGamePropertyBeer()
{
	//���ñ���
	m_PropertyAttrib.wIndex=PROPERTY_ID_BEER;
	m_PropertyAttrib.wPropertyType=PT_TYPE_PRESENT;
	m_PropertyAttrib.wServiceArea=PT_SERVICE_AREA_PLAYER|PT_SERVICE_AREA_LOOKON;
	lstrcpyn(m_PropertyAttrib.szMeasuringunit,TEXT("��"),CountArray(m_PropertyAttrib.szMeasuringunit));
	lstrcpyn(m_PropertyAttrib.szPropertyName,TEXT("ơ������"),CountArray(m_PropertyAttrib.szPropertyName));
	lstrcpyn(m_PropertyAttrib.szRegulationsInfo,TEXT("�����ڻ�����ͷ�񸽽����к�ơ�ƵĶ�����Ч"),CountArray(m_PropertyAttrib.szRegulationsInfo));
	
	return;
}

//��������
CGamePropertyBeer::~CGamePropertyBeer()
{
}

//ͼƬ��Ϣ
VOID CGamePropertyBeer::GetImageInfo(tagPropertyImage & PropertyImage)
{
	//���ñ���
	PropertyImage.pszFlash=TEXT("ơ��.swf");
	PropertyImage.pszImageID=TEXT("IMAGE_BEER");
	PropertyImage.pszSymbolID=TEXT("SYMBOL_BEER");
	PropertyImage.hResInstance=GetModuleHandle(GAME_PROPERTY_DLL_NAME);

	return;
}

//��ʾ��Ϣ
LPCTSTR CGamePropertyBeer::GetNotifyMessage(LPCTSTR szSourceNickName,LPCTSTR szTargerNickName,WORD wItemCount,LPTSTR szResultMessage)
{
	//�������
	TCHAR  szMessage[128]=TEXT("");
	_sntprintf(szMessage,CountArray(szMessage),TEXT("[ %s ] �� [ %s ]�ɱ���һ���ݣ�"),szSourceNickName,szTargerNickName);

	//��������
	CopyMemory(szResultMessage,szMessage,sizeof(szMessage));

	return szResultMessage;
}

//////////////////////////////////////////////////////////////////////////////////

//���캯��
CGamePropertyCake::CGamePropertyCake()
{
	//���ñ���
	m_PropertyAttrib.wIndex=PROPERTY_ID_CAKE;
	m_PropertyAttrib.wPropertyType=PT_TYPE_PRESENT;
	m_PropertyAttrib.wServiceArea=PT_SERVICE_AREA_PLAYER|PT_SERVICE_AREA_LOOKON;
	lstrcpyn(m_PropertyAttrib.szMeasuringunit,TEXT("��"),CountArray(m_PropertyAttrib.szMeasuringunit));
	lstrcpyn(m_PropertyAttrib.szPropertyName,TEXT("��������"),CountArray(m_PropertyAttrib.szPropertyName));
	lstrcpyn(m_PropertyAttrib.szRegulationsInfo,TEXT("�����ڻ�����ͷ�񸽽����������������ϵĶ�����Ч"),CountArray(m_PropertyAttrib.szRegulationsInfo));
	
	return;
}

//��������
CGamePropertyCake::~CGamePropertyCake()
{
}

//ͼƬ��Ϣ
VOID CGamePropertyCake::GetImageInfo(tagPropertyImage & PropertyImage)
{
	//���ñ���
	PropertyImage.pszFlash=TEXT("����.swf");
	PropertyImage.pszImageID=TEXT("IMAGE_CAKE");
	PropertyImage.pszSymbolID=TEXT("SYMBOL_CAKE");
	PropertyImage.hResInstance=GetModuleHandle(GAME_PROPERTY_DLL_NAME);

	return;
}

//��ʾ��Ϣ
LPCTSTR CGamePropertyCake::GetNotifyMessage(LPCTSTR szSourceNickName,LPCTSTR szTargerNickName,WORD wItemCount,LPTSTR szResultMessage)
{
	//�������
	TCHAR  szMessage[128]=TEXT("");
	_sntprintf(szMessage,CountArray(szMessage),TEXT("[ %s ] �͸� [ %s ] %d �鵰�⣬�����쳤�ؾã�"),szSourceNickName,szTargerNickName,wItemCount);

	//��������
	CopyMemory(szResultMessage,szMessage,sizeof(szMessage));

	return szResultMessage;
}

//////////////////////////////////////////////////////////////////////////////////

//���캯��
CGamePropertyRing::CGamePropertyRing()
{
	//���ñ���
	m_PropertyAttrib.wIndex=PROPERTY_ID_RING;
	m_PropertyAttrib.wPropertyType=PT_TYPE_PRESENT;
	m_PropertyAttrib.wServiceArea=PT_SERVICE_AREA_PLAYER|PT_SERVICE_AREA_LOOKON;
	lstrcpyn(m_PropertyAttrib.szMeasuringunit,TEXT("��"),CountArray(m_PropertyAttrib.szMeasuringunit));
	lstrcpyn(m_PropertyAttrib.szPropertyName,TEXT("�������"),CountArray(m_PropertyAttrib.szPropertyName));
	lstrcpyn(m_PropertyAttrib.szRegulationsInfo,TEXT("�����ڻ�����ͷ�񸽽����������ҫ�Ķ�����Ч"),CountArray(m_PropertyAttrib.szRegulationsInfo));
	
	return;
}

//��������
CGamePropertyRing::~CGamePropertyRing()
{
}

//ͼƬ��Ϣ
VOID CGamePropertyRing::GetImageInfo(tagPropertyImage & PropertyImage)
{
	//���ñ���
	PropertyImage.pszFlash=TEXT("���.swf");
	PropertyImage.pszImageID=TEXT("IMAGE_RING");
	PropertyImage.pszSymbolID=TEXT("SYMBOL_RING");
	PropertyImage.hResInstance=GetModuleHandle(GAME_PROPERTY_DLL_NAME);

	return;
}

//��ʾ��Ϣ
LPCTSTR CGamePropertyRing::GetNotifyMessage(LPCTSTR szSourceNickName,LPCTSTR szTargerNickName,WORD wItemCount,LPTSTR szResultMessage)
{
	//�������
	TCHAR  szMessage[128]=TEXT("");
	_sntprintf(szMessage,CountArray(szMessage),TEXT("[ %s ] �͸� [ %s ] %d õ��䣬�Ҹ����۵��˶���"),szSourceNickName,szTargerNickName,wItemCount);

	//��������
	CopyMemory(szResultMessage,szMessage,sizeof(szMessage));

	return szResultMessage;
}

//////////////////////////////////////////////////////////////////////////////////

//���캯��
CGamePropertyBeat::CGamePropertyBeat()
{
	//���ñ���
	m_PropertyAttrib.wIndex=PROPERTY_ID_BEAT;
	m_PropertyAttrib.wPropertyType=PT_TYPE_PRESENT;
	m_PropertyAttrib.wServiceArea=PT_SERVICE_AREA_PLAYER|PT_SERVICE_AREA_LOOKON;
	lstrcpyn(m_PropertyAttrib.szMeasuringunit,TEXT("��"),CountArray(m_PropertyAttrib.szMeasuringunit));
	lstrcpyn(m_PropertyAttrib.szPropertyName,TEXT("��������"),CountArray(m_PropertyAttrib.szPropertyName));
	lstrcpyn(m_PropertyAttrib.szRegulationsInfo,TEXT("�����ڻ�����ͷ�񸽽�����һ���ﱻ����Ķ�����Ч"),CountArray(m_PropertyAttrib.szRegulationsInfo));
	
	return;
}

//��������
CGamePropertyBeat::~CGamePropertyBeat()
{
}

//ͼƬ��Ϣ
VOID CGamePropertyBeat::GetImageInfo(tagPropertyImage & PropertyImage)
{
	//���ñ���
	PropertyImage.pszFlash=TEXT("����.swf");
	PropertyImage.pszImageID=TEXT("IMAGE_BEAT");
	PropertyImage.pszSymbolID=TEXT("SYMBOL_BEAT");
	PropertyImage.hResInstance=GetModuleHandle(GAME_PROPERTY_DLL_NAME);

	return;
}

//��ʾ��Ϣ
LPCTSTR CGamePropertyBeat::GetNotifyMessage(LPCTSTR szSourceNickName,LPCTSTR szTargerNickName,WORD wItemCount,LPTSTR szResultMessage)
{
	//�������
	TCHAR szMessage[128]=TEXT("");
	_sntprintf(szMessage,CountArray(szMessage),TEXT("[ %s ] �� [ %s ]������һ�٣������᲻̫��г��"),szSourceNickName,szTargerNickName);

	//��������
	CopyMemory(szResultMessage,szMessage,sizeof(szMessage));

	return szResultMessage;
}

//////////////////////////////////////////////////////////////////////////////////

//���캯��
CGamePropertyBomb::CGamePropertyBomb()
{
	//���ñ���
	m_PropertyAttrib.wIndex=PROPERTY_ID_BOMB;
	m_PropertyAttrib.wPropertyType=PT_TYPE_PRESENT;
	m_PropertyAttrib.wServiceArea=PT_SERVICE_AREA_PLAYER|PT_SERVICE_AREA_LOOKON;
	lstrcpyn(m_PropertyAttrib.szMeasuringunit,TEXT("��"),CountArray(m_PropertyAttrib.szMeasuringunit));
	lstrcpyn(m_PropertyAttrib.szPropertyName,TEXT("ը������"),CountArray(m_PropertyAttrib.szPropertyName));
	lstrcpyn(m_PropertyAttrib.szRegulationsInfo,TEXT("�����ڻ�����ͷ�񸽽�����ը����ը�Ķ�����Ч"),CountArray(m_PropertyAttrib.szRegulationsInfo));
	
	return;
}

//��������
CGamePropertyBomb::~CGamePropertyBomb()
{
}

//ͼƬ��Ϣ
VOID CGamePropertyBomb::GetImageInfo(tagPropertyImage & PropertyImage)
{
	//���ñ���
	PropertyImage.pszFlash=TEXT("ը��.swf");
	PropertyImage.pszImageID=TEXT("IMAGE_BOMB");
	PropertyImage.pszSymbolID=TEXT("SYMBOL_BOMB");
	PropertyImage.hResInstance=GetModuleHandle(GAME_PROPERTY_DLL_NAME);

	return;
}

//��ʾ��Ϣ
LPCTSTR CGamePropertyBomb::GetNotifyMessage(LPCTSTR szSourceNickName,LPCTSTR szTargerNickName,WORD wItemCount,LPTSTR szResultMessage)
{
	//�������
	TCHAR  szMessage[128]=TEXT("");
	_sntprintf(szMessage,CountArray(szMessage),TEXT("[ %s ] ���� %d ��ը���� [%s]���ɶ�ļһ"),szSourceNickName,wItemCount,szTargerNickName);

	//��������
	CopyMemory(szResultMessage,szMessage,sizeof(szMessage));

	return szResultMessage;
}

//////////////////////////////////////////////////////////////////////////////////

//���캯��
CGamePropertySmoke::CGamePropertySmoke()
{
	//���ñ���
	m_PropertyAttrib.wIndex=PROPERTY_ID_SMOKE;
	m_PropertyAttrib.wPropertyType=PT_TYPE_PRESENT;
	m_PropertyAttrib.wServiceArea=PT_SERVICE_AREA_PLAYER|PT_SERVICE_AREA_LOOKON;
	lstrcpyn(m_PropertyAttrib.szMeasuringunit,TEXT("��"),CountArray(m_PropertyAttrib.szMeasuringunit));
	lstrcpyn(m_PropertyAttrib.szPropertyName,TEXT("��������"),CountArray(m_PropertyAttrib.szPropertyName));
	lstrcpyn(m_PropertyAttrib.szRegulationsInfo,TEXT("�����ڻ�����ͷ�񸽽����г��̵Ķ�����Ч"),CountArray(m_PropertyAttrib.szRegulationsInfo));
	
	return;
}

//��������
CGamePropertySmoke::~CGamePropertySmoke()
{
}

//ͼƬ��Ϣ
VOID CGamePropertySmoke::GetImageInfo(tagPropertyImage & PropertyImage)
{
	//���ñ���
	PropertyImage.pszFlash=TEXT("����.swf");
	PropertyImage.pszImageID=TEXT("IMAGE_SMOKE");
	PropertyImage.pszSymbolID=TEXT("SYMBOL_SMOKE");
	PropertyImage.hResInstance=GetModuleHandle(GAME_PROPERTY_DLL_NAME);

	return;
}

//��ʾ��Ϣ
LPCTSTR CGamePropertySmoke::GetNotifyMessage(LPCTSTR szSourceNickName,LPCTSTR szTargerNickName,WORD wItemCount,LPTSTR szResultMessage)
{
	//�������
	TCHAR szMessage[128]=TEXT("");
	_sntprintf(szMessage,CountArray(szMessage),TEXT("[ %s ] �ݸ� [ %s ] %d ֧���̣����Ȥζ��Ͷ��"),szSourceNickName,szTargerNickName,wItemCount);

	//��������
	CopyMemory(szResultMessage,szMessage,sizeof(szMessage));

	return szResultMessage;
}

//////////////////////////////////////////////////////////////////////////////////

//���캯��
CGamePropertyVilla::CGamePropertyVilla()
{
	//���ñ���
	m_PropertyAttrib.wIndex=PROPERTY_ID_VILLA;
	m_PropertyAttrib.wPropertyType=PT_TYPE_PRESENT;
	m_PropertyAttrib.wServiceArea=PT_SERVICE_AREA_PLAYER|PT_SERVICE_AREA_LOOKON;
	lstrcpyn(m_PropertyAttrib.szMeasuringunit,TEXT("��"),CountArray(m_PropertyAttrib.szMeasuringunit));
	lstrcpyn(m_PropertyAttrib.szPropertyName,TEXT("��������"),CountArray(m_PropertyAttrib.szPropertyName));
	lstrcpyn(m_PropertyAttrib.szRegulationsInfo,TEXT("�����ڻ�����ͷ�񸽽����з��ӳ��ֵĶ�����Ч"),CountArray(m_PropertyAttrib.szRegulationsInfo));
	
	return;
}

//��������
CGamePropertyVilla::~CGamePropertyVilla()
{
}

//ͼƬ��Ϣ
VOID CGamePropertyVilla::GetImageInfo(tagPropertyImage & PropertyImage)
{
	//���ñ���
	PropertyImage.pszFlash=TEXT("����.swf");
	PropertyImage.pszImageID=TEXT("IMAGE_VILLA");
	PropertyImage.pszSymbolID=TEXT("SYMBOL_VILLA");
	PropertyImage.hResInstance=GetModuleHandle(GAME_PROPERTY_DLL_NAME);

	return;
}

//��ʾ��Ϣ
LPCTSTR CGamePropertyVilla::GetNotifyMessage(LPCTSTR szSourceNickName,LPCTSTR szTargerNickName,WORD wItemCount,LPTSTR szResultMessage)
{
	//�������
	TCHAR szMessage[128]=TEXT("");
	_sntprintf(szMessage,CountArray(szMessage),TEXT("[ %s ] �͸� [ %s ] %d ��������������¶��"),szSourceNickName,szTargerNickName,wItemCount);

	//��������
	CopyMemory(szResultMessage,szMessage,sizeof(szMessage));

	return szResultMessage;
}

//////////////////////////////////////////////////////////////////////////////////

//���캯��
CGamePropertyBrick::CGamePropertyBrick()
{
	//���ñ���
	m_PropertyAttrib.wIndex=PROPERTY_ID_BRICK;
	m_PropertyAttrib.wPropertyType=PT_TYPE_PRESENT;
	m_PropertyAttrib.wServiceArea=PT_SERVICE_AREA_PLAYER|PT_SERVICE_AREA_LOOKON;
	lstrcpyn(m_PropertyAttrib.szMeasuringunit,TEXT("��"),CountArray(m_PropertyAttrib.szMeasuringunit));
	lstrcpyn(m_PropertyAttrib.szPropertyName,TEXT("שͷ����"),CountArray(m_PropertyAttrib.szPropertyName));
	lstrcpyn(m_PropertyAttrib.szRegulationsInfo,TEXT("�����ڻ�����ͷ�񸽽�������שͷ�Ķ�����Ч"),CountArray(m_PropertyAttrib.szRegulationsInfo));
	
	return;
}

//��������
CGamePropertyBrick::~CGamePropertyBrick()
{
}

//ͼƬ��Ϣ
VOID CGamePropertyBrick::GetImageInfo(tagPropertyImage & PropertyImage)
{
	//���ñ���
	PropertyImage.pszFlash=TEXT("שͷ.swf");
	PropertyImage.pszImageID=TEXT("IMAGE_BRICK");
	PropertyImage.pszSymbolID=TEXT("SYMBOL_BRICK");
	PropertyImage.hResInstance=GetModuleHandle(GAME_PROPERTY_DLL_NAME);

	return;
}

//��ʾ��Ϣ
LPCTSTR CGamePropertyBrick::GetNotifyMessage(LPCTSTR szSourceNickName,LPCTSTR szTargerNickName,WORD wItemCount,LPTSTR szResultMessage)
{
	//�������
	TCHAR szMessage[128]=TEXT("");
	_sntprintf(szMessage,CountArray(szMessage),TEXT("[ %s ] ���� [ %s ] %d שͷ��[%s] ��������"),szSourceNickName,szTargerNickName,wItemCount,szTargerNickName);

	//��������
	CopyMemory(szResultMessage,szMessage,sizeof(szMessage));

	return szResultMessage;
}

//////////////////////////////////////////////////////////////////////////////////

//���캯��
CGamePropertyFlower::CGamePropertyFlower()
{
	//���ñ���
	m_PropertyAttrib.wIndex=PROPERTY_ID_FLOWER;
	m_PropertyAttrib.wPropertyType=PT_TYPE_PRESENT;
	m_PropertyAttrib.wServiceArea=PT_SERVICE_AREA_PLAYER|PT_SERVICE_AREA_LOOKON;
	lstrcpyn(m_PropertyAttrib.szMeasuringunit,TEXT("��"),CountArray(m_PropertyAttrib.szMeasuringunit));
	lstrcpyn(m_PropertyAttrib.szPropertyName,TEXT("�ʻ�����"),CountArray(m_PropertyAttrib.szPropertyName));
	lstrcpyn(m_PropertyAttrib.szRegulationsInfo,TEXT("�����ڻ�����ͷ�񸽽������ֳֻ��Ķ�����Ч"),CountArray(m_PropertyAttrib.szRegulationsInfo));
	
	return;
}

//��������
CGamePropertyFlower::~CGamePropertyFlower()
{
}

//ͼƬ��Ϣ
VOID CGamePropertyFlower::GetImageInfo(tagPropertyImage & PropertyImage)
{
	//���ñ���
	PropertyImage.pszFlash=TEXT("�ʻ�.swf");
	PropertyImage.pszImageID=TEXT("IMAGE_FLOWER");
	PropertyImage.pszSymbolID=TEXT("SYMBOL_FLOWER");
	PropertyImage.hResInstance=GetModuleHandle(GAME_PROPERTY_DLL_NAME);

	return;
}

//��ʾ��Ϣ
LPCTSTR CGamePropertyFlower::GetNotifyMessage(LPCTSTR szSourceNickName,LPCTSTR szTargerNickName,WORD wItemCount,LPTSTR szResultMessage)
{
	//�������
	TCHAR szMessage[128]=TEXT("");
	_sntprintf(szMessage,CountArray(szMessage),TEXT("[ %s ] �׸� [ %s ] %d ���ʻ���[%s]��������ͨͨ��"),szSourceNickName,szTargerNickName,wItemCount,szTargerNickName);

	//��������
	CopyMemory(szResultMessage,szMessage,sizeof(szMessage));

	return szResultMessage;
}

//////////////////////////////////////////////////////////////////////////////////

//���캯��
CGamePropertyTwoScoreCard::CGamePropertyTwoScoreCard()
{
	//���ñ���
	m_PropertyAttrib.wIndex=PROPERTY_ID_TWO_CARD;
	m_PropertyAttrib.wPropertyType=PT_TYPE_PROPERTY;
	m_PropertyAttrib.wServiceArea=PT_SERVICE_AREA_MESELF|PT_SERVICE_AREA_PLAYER|PT_SERVICE_AREA_LOOKON;
	lstrcpyn(m_PropertyAttrib.szMeasuringunit,TEXT("Сʱ"),CountArray(m_PropertyAttrib.szMeasuringunit));
	lstrcpyn(m_PropertyAttrib.szPropertyName,TEXT("˫�����ֿ�"),CountArray(m_PropertyAttrib.szPropertyName));
	lstrcpyn(m_PropertyAttrib.szRegulationsInfo,TEXT("ӵ��˫�����ֿ�����ϷӮ�ֽ����˫�����֣���ֲ���ۣ����˵��߿�ֻ���ڻ��ַ��乺���ҽ��ڹ������Ϸ������Ч����"),CountArray(m_PropertyAttrib.szRegulationsInfo));
}

//��������
CGamePropertyTwoScoreCard::~CGamePropertyTwoScoreCard()
{
}

//ͼƬ��Ϣ
VOID CGamePropertyTwoScoreCard::GetImageInfo(tagPropertyImage & PropertyImage)
{
	//���ñ���
	PropertyImage.pszFlash=TEXT("");
	PropertyImage.pszImageID=TEXT("IMAGE_TWO_SCORE_CARD");
	PropertyImage.pszSymbolID=TEXT("SYMBOL_TWO_SCORE_CARD");
	PropertyImage.hResInstance=GetModuleHandle(GAME_PROPERTY_DLL_NAME);

	return;
}

//��ʾ��Ϣ
LPCTSTR CGamePropertyTwoScoreCard::GetNotifyMessage(LPCTSTR szSourceNickName,LPCTSTR szTargerNickName,WORD wItemCount,LPTSTR szResultMessage)
{
	//�������
	TCHAR szMessage[128]=TEXT("");
	if(szSourceNickName==szTargerNickName)
		_sntprintf(szMessage,CountArray(szMessage),TEXT("��ϲ�������߹���ɹ���˫�����ֿ���ʱ��Ч��%dСʱ������ϷӮ�ֽ����˫�����֣���ֲ���ۡ�"),wItemCount);
	else
		_sntprintf(szMessage,CountArray(szMessage),TEXT("��ϲ����[ %s ]�����������˫�����ֿ����ߣ���ʱ��Ч��%dСʱ������ϷӮ�ֽ����˫�����֣�\n��ֲ���ۡ�"),szSourceNickName,wItemCount);

	//��������
	CopyMemory(szResultMessage,szMessage,sizeof(szMessage));

	return szResultMessage;
}

//////////////////////////////////////////////////////////////////////////////////

//���캯��
CGamePropertyFourScoreCard::CGamePropertyFourScoreCard()
{
	//���ñ���
	m_PropertyAttrib.wIndex=PROPERTY_ID_FOUR_CARD;
	m_PropertyAttrib.wPropertyType=PT_TYPE_PROPERTY;
	m_PropertyAttrib.wServiceArea=PT_SERVICE_AREA_MESELF|PT_SERVICE_AREA_PLAYER|PT_SERVICE_AREA_LOOKON;
	lstrcpyn(m_PropertyAttrib.szMeasuringunit,TEXT("Сʱ"),CountArray(m_PropertyAttrib.szMeasuringunit));
	lstrcpyn(m_PropertyAttrib.szPropertyName,TEXT("�ı����ֿ�"),CountArray(m_PropertyAttrib.szPropertyName));
	lstrcpyn(m_PropertyAttrib.szRegulationsInfo,TEXT("ӵ���ı����ֿ�����ϷӮ�ֽ�����ı����֣���ֲ���ۣ����˵��߿�ֻ���ڻ��ַ��乺���ҽ��ڹ������Ϸ������Ч����"),CountArray(m_PropertyAttrib.szRegulationsInfo));
}

//��������
CGamePropertyFourScoreCard::~CGamePropertyFourScoreCard()
{
}

//ͼƬ��Ϣ
VOID CGamePropertyFourScoreCard::GetImageInfo(tagPropertyImage & PropertyImage)
{
	//���ñ���
	PropertyImage.pszFlash=TEXT("");
	PropertyImage.pszImageID=TEXT("IMAGE_FOUR_SCORE_CARD");
	PropertyImage.pszSymbolID=TEXT("SYMBOL_FOUR_SCORE_CARD");
	PropertyImage.hResInstance=GetModuleHandle(GAME_PROPERTY_DLL_NAME);

	return;
}

//��ʾ��Ϣ
LPCTSTR CGamePropertyFourScoreCard::GetNotifyMessage(LPCTSTR szSourceNickName,LPCTSTR szTargerNickName,WORD wItemCount,LPTSTR szResultMessage)
{
	//�������
	TCHAR szMessage[128]=TEXT("");
	if(szSourceNickName==szTargerNickName)
		_sntprintf(szMessage,CountArray(szMessage),TEXT("��ϲ�������߹���ɹ����ı����ֿ���ʱ��Ч��%dСʱ������ϷӮ�ֽ�����ı����֣���ֲ���ۡ�"),wItemCount);
	else
		_sntprintf(szMessage,CountArray(szMessage),TEXT("��ϲ����[ %s ]������������ı����ֿ����ߣ���ʱ��Ч��%dСʱ������ϷӮ�ֽ�����ı����֣�\n��ֲ���ۡ�"),szSourceNickName,wItemCount);

	//��������
	CopyMemory(szResultMessage,szMessage,sizeof(szMessage));

	return szResultMessage;
}

//////////////////////////////////////////////////////////////////////////////////

//���캯��
CGamePropertyScoreClear::CGamePropertyScoreClear()
{
	//���ñ���
	m_PropertyAttrib.wIndex=PROPERTY_ID_SCORE_CLEAR;
	m_PropertyAttrib.wPropertyType=PT_TYPE_PROPERTY;
	m_PropertyAttrib.wServiceArea=PT_SERVICE_AREA_MESELF|PT_SERVICE_AREA_PLAYER;
	lstrcpyn(m_PropertyAttrib.szMeasuringunit,TEXT("��"),CountArray(m_PropertyAttrib.szMeasuringunit));
	lstrcpyn(m_PropertyAttrib.szPropertyName,TEXT("�������㿨"),CountArray(m_PropertyAttrib.szPropertyName));
	lstrcpyn(m_PropertyAttrib.szRegulationsInfo,TEXT("ʹ�øõ��ߺ�������Ϸ���ֽ��ָ�����ʼ״̬������Ϊ���ֶ����գ�"),CountArray(m_PropertyAttrib.szRegulationsInfo));
}

//��������
CGamePropertyScoreClear::~CGamePropertyScoreClear()
{
}

//ͼƬ��Ϣ
VOID CGamePropertyScoreClear::GetImageInfo(tagPropertyImage & PropertyImage)
{
	//���ñ���
	PropertyImage.pszFlash=TEXT("");
	PropertyImage.pszImageID=TEXT("IMAGE_SCORE_CLEAR");
	PropertyImage.pszSymbolID=TEXT("SYMBOL_SCORE_CLEAR");
	PropertyImage.hResInstance=GetModuleHandle(GAME_PROPERTY_DLL_NAME);

	return;
}

//��ʾ��Ϣ
LPCTSTR CGamePropertyScoreClear::GetNotifyMessage(LPCTSTR szSourceNickName,LPCTSTR szTargerNickName,WORD wItemCount,LPTSTR szResultMessage)
{
	//�������
	TCHAR szMessage[128]=TEXT("");
	if(szSourceNickName,szTargerNickName)
		_sntprintf(szMessage,CountArray(szMessage),TEXT("��ϲ�������߹���ɹ����������㼴ʱ��Ч��������Ϸ�����Ѿ��ָ���ʼ״̬��"),szSourceNickName,wItemCount);
	else
		_sntprintf(szMessage,CountArray(szMessage),TEXT("��ϲ����[ %s ]���������������������ߣ���ʱ��Ч��������Ϸ�����Ѿ��ָ���ʼ״̬�� "),szSourceNickName);

	//��������
	CopyMemory(szResultMessage,szMessage,sizeof(szMessage));

	return szResultMessage;
}

//////////////////////////////////////////////////////////////////////////////////

//���캯��
CGamePropertyEscapeClear::CGamePropertyEscapeClear()
{
	//���ñ���
	m_PropertyAttrib.wIndex=PROPERTY_ID_ESCAPE_CLEAR;
	m_PropertyAttrib.wPropertyType=PT_TYPE_PROPERTY;
	m_PropertyAttrib.wServiceArea=PT_SERVICE_AREA_MESELF|PT_SERVICE_AREA_PLAYER;
	lstrcpyn(m_PropertyAttrib.szMeasuringunit,TEXT("��"),CountArray(m_PropertyAttrib.szMeasuringunit));
	lstrcpyn(m_PropertyAttrib.szPropertyName,TEXT("���������㿨"),CountArray(m_PropertyAttrib.szPropertyName));
	lstrcpyn(m_PropertyAttrib.szRegulationsInfo,TEXT("ʹ�øõ��ߺ����������ʽ��ָ�����ʼ״̬������Ϊ���ܶ����գ����������ڹ��򱾿���Ϸ������Ч��"),CountArray(m_PropertyAttrib.szRegulationsInfo));
}

//��������
CGamePropertyEscapeClear::~CGamePropertyEscapeClear()
{
}

//ͼƬ��Ϣ
VOID CGamePropertyEscapeClear::GetImageInfo(tagPropertyImage & PropertyImage)
{
	//���ñ���
	PropertyImage.pszFlash=TEXT("");
	PropertyImage.pszImageID=TEXT("IMAGE_ESCAPE_CLEAR");
	PropertyImage.pszSymbolID=TEXT("SYMBOL_ESCAPE_CLEAR");
	PropertyImage.hResInstance=GetModuleHandle(GAME_PROPERTY_DLL_NAME);

	return;
}

//��ʾ��Ϣ
LPCTSTR CGamePropertyEscapeClear::GetNotifyMessage(LPCTSTR szSourceNickName,LPCTSTR szTargerNickName,WORD wItemCount,LPTSTR szResultMessage)
{
	//�������
	TCHAR szMessage[128]=TEXT("");
	if(szSourceNickName,szTargerNickName)
		_sntprintf(szMessage,CountArray(szMessage),TEXT("��ϲ�������߹���ɹ����������㼴ʱ��Ч�������������Ѿ��ָ���ʼ״̬��"),szSourceNickName,wItemCount);
	else
		_sntprintf(szMessage,CountArray(szMessage),TEXT("��ϲ����[ %s ]���������������������ߣ���ʱ��Ч�������������Ѿ��ָ���ʼ״̬�� "),szSourceNickName);

	//��������
	CopyMemory(szResultMessage,szMessage,sizeof(szMessage));

	return szResultMessage;
}

//////////////////////////////////////////////////////////////////////////////////

//���캯��
CGamePropertyTrumpet::CGamePropertyTrumpet()
{
	//���ñ���
	m_PropertyAttrib.wIndex=PROPERTY_ID_TRUMPET;
	m_PropertyAttrib.wPropertyType=PT_TYPE_PROPERTY;
	m_PropertyAttrib.wServiceArea=PT_SERVICE_AREA_MESELF|PT_SERVICE_AREA_PLAYER;
	lstrcpyn(m_PropertyAttrib.szMeasuringunit,TEXT("��"),CountArray(m_PropertyAttrib.szMeasuringunit));
	lstrcpyn(m_PropertyAttrib.szPropertyName,TEXT("С����"),CountArray(m_PropertyAttrib.szPropertyName));
	lstrcpyn(m_PropertyAttrib.szRegulationsInfo,TEXT("�����͵���Ϣ���ڷ��估�����ڵ�������Ϸ��������������Ŀ�ķ�ʽ��ʾ��"),CountArray(m_PropertyAttrib.szRegulationsInfo));
}

//��������
CGamePropertyTrumpet::~CGamePropertyTrumpet()
{
}

//ͼƬ��Ϣ
VOID CGamePropertyTrumpet::GetImageInfo(tagPropertyImage & PropertyImage)
{
	//���ñ���
	PropertyImage.pszFlash=TEXT("");
	PropertyImage.pszImageID=TEXT("IMAGE_TRUMPET");
	PropertyImage.pszSymbolID=TEXT("SYMBOL_TRUMPET");
	PropertyImage.hResInstance=GetModuleHandle(GAME_PROPERTY_DLL_NAME);

	return;
}

//��ʾ��Ϣ
LPCTSTR CGamePropertyTrumpet::GetNotifyMessage(LPCTSTR szSourceNickName,LPCTSTR szTargerNickName,WORD wItemCount,LPTSTR szResultMessage)
{
	//�������
	TCHAR szMessage[128]=TEXT("");
	_sntprintf(szMessage,CountArray(szMessage),TEXT("��ϲ����[ %s ]�������������%d��С���ȵ��ߣ����ͼ��á��õ������������͵���Ϣ���ڷ����ڵ������������Ŀ�ķ�ʽ��ʾ��"),szSourceNickName,wItemCount);

	//��������
	CopyMemory(szResultMessage,szMessage,sizeof(szMessage));

	return szResultMessage;
}

//////////////////////////////////////////////////////////////////////////////////

//���캯��
CGamePropertyTyphon::CGamePropertyTyphon()
{
	//���ñ���
	m_PropertyAttrib.wIndex=PROPERTY_ID_TYPHON;
	m_PropertyAttrib.wPropertyType=PT_TYPE_PROPERTY;
	m_PropertyAttrib.wServiceArea=PT_SERVICE_AREA_MESELF|PT_SERVICE_AREA_PLAYER;
	lstrcpyn(m_PropertyAttrib.szMeasuringunit,TEXT("��"),CountArray(m_PropertyAttrib.szMeasuringunit));
	lstrcpyn(m_PropertyAttrib.szPropertyName,TEXT("������"),CountArray(m_PropertyAttrib.szPropertyName));
	lstrcpyn(m_PropertyAttrib.szRegulationsInfo,TEXT("�����͵���Ϣ���ڴ�����ȫ����������Ϸ��������������Ŀ�ķ�ʽ��ʾ��"),CountArray(m_PropertyAttrib.szRegulationsInfo));
}

//��������
CGamePropertyTyphon::~CGamePropertyTyphon()
{
}

//ͼƬ��Ϣ
VOID CGamePropertyTyphon::GetImageInfo(tagPropertyImage & PropertyImage)
{
	//���ñ���
	PropertyImage.pszFlash=TEXT("");
	PropertyImage.pszImageID=TEXT("IMAGE_TYPHON");
	PropertyImage.pszSymbolID=TEXT("SYMBOL_TYPHON");
	PropertyImage.hResInstance=GetModuleHandle(GAME_PROPERTY_DLL_NAME);

	return;
}

//��ʾ��Ϣ
LPCTSTR CGamePropertyTyphon::GetNotifyMessage(LPCTSTR szSourceNickName,LPCTSTR szTargerNickName,WORD wItemCount,LPTSTR szResultMessage)
{
	//�������
	TCHAR szMessage[128]=TEXT("");
	_sntprintf(szMessage,CountArray(szMessage),TEXT("��ϲ����[ %s ]�������������%d�������ȵ��ߣ����ͼ��á��õ������������͵���Ϣ���ڴ�����ȫ����������Ϸ������Ŀ�ķ�ʽ��ʾ��"),szSourceNickName,wItemCount);

	//��������
	CopyMemory(szResultMessage,szMessage,sizeof(szMessage));

	return szResultMessage;
}

//////////////////////////////////////////////////////////////////////////////////

//���캯��
CGamePropertyGuardKickCard::CGamePropertyGuardKickCard()
{
	//���ñ���
	m_PropertyAttrib.wIndex=PROPERTY_ID_GUARDKICK_CARD;
	m_PropertyAttrib.wPropertyType=PT_TYPE_PROPERTY;
	m_PropertyAttrib.wServiceArea=PT_SERVICE_AREA_MESELF|PT_SERVICE_AREA_PLAYER;
	lstrcpyn(m_PropertyAttrib.szMeasuringunit,TEXT("Сʱ"),CountArray(m_PropertyAttrib.szMeasuringunit));
	lstrcpyn(m_PropertyAttrib.szPropertyName,TEXT("���߿�"),CountArray(m_PropertyAttrib.szPropertyName));
	lstrcpyn(m_PropertyAttrib.szRegulationsInfo,TEXT("����õ��ߺ������õ��ı���Ա�߳���Ϸ����"),CountArray(m_PropertyAttrib.szRegulationsInfo));
}

//��������
CGamePropertyGuardKickCard::~CGamePropertyGuardKickCard()
{
}

//ͼƬ��Ϣ
VOID CGamePropertyGuardKickCard::GetImageInfo(tagPropertyImage & PropertyImage)
{
	//���ñ���
	PropertyImage.pszFlash=TEXT("");
	PropertyImage.pszImageID=TEXT("IMAGE_GUARDKICK_CARD");
	PropertyImage.pszSymbolID=TEXT("SYMBOL_GUARDKICK_CARD");
	PropertyImage.hResInstance=GetModuleHandle(GAME_PROPERTY_DLL_NAME);

	return;
}

//��ʾ��Ϣ
LPCTSTR CGamePropertyGuardKickCard::GetNotifyMessage(LPCTSTR szSourceNickName,LPCTSTR szTargerNickName,WORD wItemCount,LPTSTR szResultMessage)
{
	//�������
	TCHAR szMessage[128]=TEXT("");
	if(szSourceNickName==szTargerNickName)
		_sntprintf(szMessage,CountArray(szMessage),TEXT("��ϲ�������߹���ɹ������߿���ʱ��Ч��%dСʱ�������õ��ı���Ա�߳���Ϸ����"),wItemCount);
	else
		_sntprintf(szMessage,CountArray(szMessage),TEXT(" ��ϲ����[ %s ]��������������߿����ߣ���ʱ��Ч��%dСʱ�ڣ������õ��ı���Ա�߳���Ϸ����"),szSourceNickName,wItemCount);

	//��������
	CopyMemory(szResultMessage,szMessage,sizeof(szMessage));

	return szResultMessage;
}

//////////////////////////////////////////////////////////////////////////////////

//���캯��
CGamePropertyPossess::CGamePropertyPossess()
{
	//���ñ���
	m_PropertyAttrib.wIndex=PROPERTY_ID_POSSESS;
	m_PropertyAttrib.wPropertyType=PT_TYPE_PROPERTY;
	m_PropertyAttrib.wServiceArea=PT_SERVICE_AREA_MESELF|PT_SERVICE_AREA_PLAYER;
	lstrcpyn(m_PropertyAttrib.szMeasuringunit,TEXT("Сʱ"),CountArray(m_PropertyAttrib.szMeasuringunit));
	lstrcpyn(m_PropertyAttrib.szPropertyName,TEXT("�����"),CountArray(m_PropertyAttrib.szPropertyName));
	lstrcpyn(m_PropertyAttrib.szRegulationsInfo,TEXT("����õ��ߺ�,����Ϸ��ֲ��۷�,Ӯ�������÷�,����Ϊ�۷ֶ�����! (�˵��߿�ֻ���ڻ��ַ��乺��,�ҽ��ڹ������Ϸ������Ч. )"),CountArray(m_PropertyAttrib.szRegulationsInfo));
}

//��������
CGamePropertyPossess::~CGamePropertyPossess()
{
}

//ͼƬ��Ϣ
VOID CGamePropertyPossess::GetImageInfo(tagPropertyImage & PropertyImage)
{
	//���ñ���
	PropertyImage.pszFlash=TEXT("");
	PropertyImage.pszImageID=TEXT("IMAGE_POSSESS");
	PropertyImage.pszSymbolID=TEXT("SYMBOL_POSSESS");
	PropertyImage.hResInstance=GetModuleHandle(GAME_PROPERTY_DLL_NAME);

	return;
}

//��ʾ��Ϣ
LPCTSTR CGamePropertyPossess::GetNotifyMessage(LPCTSTR szSourceNickName,LPCTSTR szTargerNickName,WORD wItemCount,LPTSTR szResultMessage)
{
	//�������
	TCHAR szMessage[128]=TEXT("");
	if(szSourceNickName==szTargerNickName)
		_sntprintf(szMessage,CountArray(szMessage),TEXT("��ϲ�������߹���ɹ����������ʱ��Ч��%dСʱ������Ϸ��ֲ��۷֣�Ӯ�������÷֡�"),wItemCount);
	else
		_sntprintf(szMessage,CountArray(szMessage),TEXT("��ϲ����[ %s ]�������������������ߣ���ʱ��Ч��%dСʱ������Ϸ��ֲ��۷֣�Ӯ�������÷֡�"),szSourceNickName,wItemCount);

	//��������
	CopyMemory(szResultMessage,szMessage,sizeof(szMessage));

	return szResultMessage;
}


//////////////////////////////////////////////////////////////////////////////////

//���캯��
CGamePropertyBlueRingCard::CGamePropertyBlueRingCard()
{
	//���ñ���
	m_PropertyAttrib.wIndex=PROPERTY_ID_BLUERING_CARD;
	m_PropertyAttrib.wPropertyType=PT_TYPE_PROPERTY;
	m_PropertyAttrib.wServiceArea=PT_SERVICE_AREA_MESELF|PT_SERVICE_AREA_PLAYER;
	lstrcpyn(m_PropertyAttrib.szMeasuringunit,TEXT("��"),CountArray(m_PropertyAttrib.szMeasuringunit));
	lstrcpyn(m_PropertyAttrib.szPropertyName,TEXT("�����Ա��"),CountArray(m_PropertyAttrib.szPropertyName));
	lstrcpyn(m_PropertyAttrib.szRegulationsInfo,TEXT("��Ա�����������ʱ�������ۿ��Żݣ�������ͨ��ҡ������Ա���л����Ա�����־����Ա�ڼ䣬����ID���û��б����Ժ�ɫ����ͻ����ʾ���������Ƚ�����Ա���䣡"),CountArray(m_PropertyAttrib.szRegulationsInfo));
}

//��������
CGamePropertyBlueRingCard::~CGamePropertyBlueRingCard()
{
}

//ͼƬ��Ϣ
VOID CGamePropertyBlueRingCard::GetImageInfo(tagPropertyImage & PropertyImage)
{
	//���ñ���
	PropertyImage.pszFlash=TEXT("");
	PropertyImage.pszImageID=TEXT("IMAGE_BLUERING_CARD");
	PropertyImage.pszSymbolID=TEXT("SYMBOL_BLUERING_CARD");
	PropertyImage.hResInstance=GetModuleHandle(GAME_PROPERTY_DLL_NAME);

	return;
}

//��ʾ��Ϣ
LPCTSTR CGamePropertyBlueRingCard::GetNotifyMessage(LPCTSTR szSourceNickName,LPCTSTR szTargerNickName,WORD wItemCount,LPTSTR szResultMessage)
{
	//�������
	TCHAR szMessage[128]=TEXT("");
	if(szSourceNickName==szTargerNickName)
		_sntprintf(szMessage,CountArray(szMessage),TEXT("��ϲ�������߹���ɹ��������Ա����ʱ��Ч��%d�������������������Ա�����Ȩ�ޡ�"),wItemCount);
	else
		_sntprintf(szMessage,CountArray(szMessage),TEXT("��ϲ����[ %s ]����������������Ա�����ߣ���ʱ��Ч��%d�������������������Ա�����Ȩ�ޡ�"),szSourceNickName,wItemCount);

	//��������
	CopyMemory(szResultMessage,szMessage,sizeof(szMessage));

	return szResultMessage;
}

//////////////////////////////////////////////////////////////////////////////////

//���캯��
CGamePropertyYellowRingCard::CGamePropertyYellowRingCard()
{
	//���ñ���
	m_PropertyAttrib.wIndex=PROPERTY_ID_YELLOWRING_CARD;
	m_PropertyAttrib.wPropertyType=PT_TYPE_PROPERTY;
	m_PropertyAttrib.wServiceArea=PT_SERVICE_AREA_MESELF|PT_SERVICE_AREA_PLAYER;
	lstrcpyn(m_PropertyAttrib.szMeasuringunit,TEXT("��"),CountArray(m_PropertyAttrib.szMeasuringunit));
	lstrcpyn(m_PropertyAttrib.szPropertyName,TEXT("�����Ա��"),CountArray(m_PropertyAttrib.szPropertyName));
	lstrcpyn(m_PropertyAttrib.szRegulationsInfo,TEXT("��Ա�����������ʱ�������ۿ��Żݣ�������ͨ��ҡ������Ա���л����Ա�����־����Ա�ڼ䣬����ID���û��б����Ժ�ɫ����ͻ����ʾ���������Ƚ�����Ա���䣡"),CountArray(m_PropertyAttrib.szRegulationsInfo));
}

//��������
CGamePropertyYellowRingCard::~CGamePropertyYellowRingCard()
{
}

//ͼƬ��Ϣ
VOID CGamePropertyYellowRingCard::GetImageInfo(tagPropertyImage & PropertyImage)
{
	//���ñ���
	PropertyImage.pszFlash=TEXT("");
	PropertyImage.pszImageID=TEXT("IMAGE_YELLOWRING_CARD");
	PropertyImage.pszSymbolID=TEXT("SYMBOL_YELLOWRING_CARD");
	PropertyImage.hResInstance=GetModuleHandle(GAME_PROPERTY_DLL_NAME);

	return;
}

//��ʾ��Ϣ
LPCTSTR CGamePropertyYellowRingCard::GetNotifyMessage(LPCTSTR szSourceNickName,LPCTSTR szTargerNickName,WORD wItemCount,LPTSTR szResultMessage)
{
	//�������
	TCHAR szMessage[128]=TEXT("");
	if(szSourceNickName==szTargerNickName)
		_sntprintf(szMessage,CountArray(szMessage),TEXT("��ϲ�������߹���ɹ��������Ա����ʱ��Ч��%d�������������ܻ����Ա�����Ȩ�ޡ�"),wItemCount);
	else
		_sntprintf(szMessage,CountArray(szMessage),TEXT("��ϲ����[ %s ]����������������Ա�����ߣ���ʱ��Ч��%d�������������ܻ����Ա�����Ȩ�ޡ�"),szSourceNickName,wItemCount);

	//��������
	CopyMemory(szResultMessage,szMessage,sizeof(szMessage));

	return szResultMessage;
}

//////////////////////////////////////////////////////////////////////////////////

//���캯��
CGamePropertyWhiteRingCard::CGamePropertyWhiteRingCard()
{
	//���ñ���
	m_PropertyAttrib.wIndex=PROPERTY_ID_WHITERING_CARD;
	m_PropertyAttrib.wPropertyType=PT_TYPE_PROPERTY;
	m_PropertyAttrib.wServiceArea=PT_SERVICE_AREA_MESELF|PT_SERVICE_AREA_PLAYER;
	lstrcpyn(m_PropertyAttrib.szMeasuringunit,TEXT("��"),CountArray(m_PropertyAttrib.szMeasuringunit));
	lstrcpyn(m_PropertyAttrib.szPropertyName,TEXT("�����Ա��"),CountArray(m_PropertyAttrib.szPropertyName));
	lstrcpyn(m_PropertyAttrib.szRegulationsInfo,TEXT("��Ա�����������ʱ�������ۿ��Żݣ�������ͨ��ҡ������Ա�ͻ����Ա���а����Ա�����־����Ա�ڼ䣬����ID���û��б����Ժ�ɫ����ͻ����ʾ���������Ƚ�����Ա���䣡"),CountArray(m_PropertyAttrib.szRegulationsInfo));
}

//��������
CGamePropertyWhiteRingCard::~CGamePropertyWhiteRingCard()
{
}

//ͼƬ��Ϣ
VOID CGamePropertyWhiteRingCard::GetImageInfo(tagPropertyImage & PropertyImage)
{
	//���ñ���
	PropertyImage.pszFlash=TEXT("");
	PropertyImage.pszImageID=TEXT("IMAGE_WHITERING_CARD");
	PropertyImage.pszSymbolID=TEXT("SYMBOL_WHITERING_CARD");
	PropertyImage.hResInstance=GetModuleHandle(GAME_PROPERTY_DLL_NAME);

	return;
}

//��ʾ��Ϣ
LPCTSTR CGamePropertyWhiteRingCard::GetNotifyMessage(LPCTSTR szSourceNickName,LPCTSTR szTargerNickName,WORD wItemCount,LPTSTR szResultMessage)
{
	//�������
	TCHAR szMessage[128]=TEXT("");
	if(szSourceNickName==szTargerNickName)
		_sntprintf(szMessage,CountArray(szMessage),TEXT("��ϲ�������߹���ɹ��������Ա����ʱ��Ч��%d�������������ܰ����Ա�����Ȩ�ޡ�"),wItemCount);
	else
		_sntprintf(szMessage,CountArray(szMessage),TEXT("��ϲ����[ %s ]����������������Ա�����ߣ���ʱ��Ч��%d�������������ܰ����Ա�����Ȩ�ޡ�"),szSourceNickName,wItemCount);

	//��������
	CopyMemory(szResultMessage,szMessage,sizeof(szMessage));

	return szResultMessage;
}

//////////////////////////////////////////////////////////////////////////////////

//���캯��
CGamePropertyRedRingCard::CGamePropertyRedRingCard()
{
	//���ñ���
	m_PropertyAttrib.wIndex=PROPERTY_ID_REDRING_CARD;
	m_PropertyAttrib.wPropertyType=PT_TYPE_PROPERTY;
	m_PropertyAttrib.wServiceArea=PT_SERVICE_AREA_MESELF|PT_SERVICE_AREA_PLAYER;
	lstrcpyn(m_PropertyAttrib.szMeasuringunit,TEXT("��"),CountArray(m_PropertyAttrib.szMeasuringunit));
	lstrcpyn(m_PropertyAttrib.szPropertyName,TEXT("�����Ա��"),CountArray(m_PropertyAttrib.szPropertyName));
	lstrcpyn(m_PropertyAttrib.szRegulationsInfo,TEXT("��Ա�����������ʱ�������ۿ��Żݣ�������ͨ��ҡ������Ա�������Ա�Ͱ����Ա���к����Ա�����־����Ա�ڼ䣬����ID���û��б����Ժ�ɫ����ͻ����ʾ���������Ƚ�����Ա���䣡"),CountArray(m_PropertyAttrib.szRegulationsInfo));
}

//��������
CGamePropertyRedRingCard::~CGamePropertyRedRingCard()
{
}

//ͼƬ��Ϣ
VOID CGamePropertyRedRingCard::GetImageInfo(tagPropertyImage & PropertyImage)
{
	//���ñ���
	PropertyImage.pszFlash=TEXT("");
	PropertyImage.pszImageID=TEXT("IMAGE_REDRING_CARD");
	PropertyImage.pszSymbolID=TEXT("SYMBOL_REDRING_CARD");
	PropertyImage.hResInstance=GetModuleHandle(GAME_PROPERTY_DLL_NAME);

	return;
}

//��ʾ��Ϣ
LPCTSTR CGamePropertyRedRingCard::GetNotifyMessage(LPCTSTR szSourceNickName,LPCTSTR szTargerNickName,WORD wItemCount,LPTSTR szResultMessage)
{
	//�������
	TCHAR szMessage[128]=TEXT("");
	if(szSourceNickName==szTargerNickName)
		_sntprintf(szMessage,CountArray(szMessage),TEXT("��ϲ�������߹���ɹ��������Ա����ʱ��Ч��%d�������������ܺ����Ա�����Ȩ�ޡ�"),wItemCount);
	else
		_sntprintf(szMessage,CountArray(szMessage),TEXT("��ϲ����[ %s ]����������������Ա�����ߣ���ʱ��Ч��%d�������������ܺ����Ա�����Ȩ�ޡ�"),szSourceNickName,wItemCount);

	//��������
	CopyMemory(szResultMessage,szMessage,sizeof(szMessage));

	return szResultMessage;
}

//////////////////////////////////////////////////////////////////////////////////

//���캯��
CGamePropertyVipRoomCard::CGamePropertyVipRoomCard()
{
	//���ñ���
	m_PropertyAttrib.wIndex=PROPERTY_ID_VIPROOM_CARD;
	m_PropertyAttrib.wPropertyType=PT_TYPE_PROPERTY;
	m_PropertyAttrib.wServiceArea=PT_SERVICE_AREA_MESELF|PT_SERVICE_AREA_PLAYER;
	lstrcpyn(m_PropertyAttrib.szMeasuringunit,TEXT("��"),CountArray(m_PropertyAttrib.szMeasuringunit));
	lstrcpyn(m_PropertyAttrib.szPropertyName,TEXT("VIP��Ա��"),CountArray(m_PropertyAttrib.szPropertyName));
	lstrcpyn(m_PropertyAttrib.szRegulationsInfo,TEXT("����õ��ߵ��û������Խ����ض���VIP������Ϸ�������������ʱ�������ۿ��Żݣ��������VIP��ɫ��־����Ա�ڼ䣬����ID���û��б����Ժ�ɫ����ͻ����ʾ���������Ƚ�����Ա���䣡"),CountArray(m_PropertyAttrib.szRegulationsInfo));
}

//��������
CGamePropertyVipRoomCard::~CGamePropertyVipRoomCard()
{
}

//ͼƬ��Ϣ
VOID CGamePropertyVipRoomCard::GetImageInfo(tagPropertyImage & PropertyImage)
{
	//���ñ���
	PropertyImage.pszFlash=TEXT("");
	PropertyImage.pszImageID=TEXT("IMAGE_VIPROOM_CARD");
	PropertyImage.pszSymbolID=TEXT("SYMBOL_VIPROOM_CARD");
	PropertyImage.hResInstance=GetModuleHandle(GAME_PROPERTY_DLL_NAME);

	return;
}

//��ʾ��Ϣ
LPCTSTR CGamePropertyVipRoomCard::GetNotifyMessage(LPCTSTR szSourceNickName,LPCTSTR szTargerNickName,WORD wItemCount,LPTSTR szResultMessage)
{
	//�������
	TCHAR szMessage[128]=TEXT("");
	if(szSourceNickName==szTargerNickName)
		_sntprintf(szMessage,CountArray(szMessage),TEXT("��ϲ�������߹���ɹ���VIP��Ա����ʱ��Ч��%d��������������VIP��Ա�����Ȩ�ޣ�"),wItemCount);
	else
		_sntprintf(szMessage,CountArray(szMessage),TEXT("��ϲ����[ %s ]�����������VIP��Ա�����ߣ���ʱ��Ч��%d��������������VIP��Ա�����Ȩ�ޣ�"),szSourceNickName,wItemCount);

	//��������
	CopyMemory(szResultMessage,szMessage,sizeof(szMessage));

	return szResultMessage;
}

//////////////////////////////////////////////////////////////////////////////////