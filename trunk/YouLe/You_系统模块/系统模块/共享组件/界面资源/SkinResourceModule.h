#ifndef SKIN_RESOURCE_MODULE_HEAD_FILE
#define SKIN_RESOURCE_MODULE_HEAD_FILE

//////////////////////////////////////////////////////////////////////////

//ƽ̨ͷ�ļ�
//#include "..\..\ģ���\Template.h"
#include "..\..\�����ļ�\GlobalProperty.h"
#include "..\..\�������\����ؼ�\SkinControls.h"

//////////////////////////////////////////////////////////////////////////
//�����궨��
#define RESOURCE_DEFAULT			0									//��ɫ��Դ
#define RESOURCE_BLACK				1									//��ɫ��Դ
#define RESOURCE_RED				2									//��ɫ��Դ

//////////////////////////////////////////////////////////////////////////

//ģ�鶨��
#ifndef _DEBUG
	#define SKIN_RESOURCE_DLL_NAME	TEXT("SkinResource.dll")			//��� DLL ����
#else
	#define SKIN_RESOURCE_DLL_NAME	TEXT("SkinResourceD.dll")			//��� DLL ����
#endif

//////////////////////////////////////////////////////////////////////////
//�ṹ����

//�¿����Դ
struct tagPlatformFrameImageNew
{
	LPCTSTR							pszImageHead;
	LPCTSTR							pszImageLeft;
	LPCTSTR							pszImageRight;
	LPCTSTR							pszImageMiddle;

	LPCTSTR							pszBtFrameSet;
	LPCTSTR							pszBtMin;
	LPCTSTR							pszBtClose;

	LPCTSTR							pszBtBagpack;
	LPCTSTR							pszBtIm;
	LPCTSTR							pszBtSquare;
	LPCTSTR							pszBtTill;

	LPCTSTR							pszBtReflash;
	LPCTSTR							pszBtUserSet;
	LPCTSTR							pszBtUserSexHead;

	LPCTSTR							pszEnquireBack;
	LPCTSTR							pszEnquireCancel;
	LPCTSTR							pszEnquirePlaza;
	LPCTSTR							pszEnquireSwitch;
	LPCTSTR							pszEnquireQuit;

	LPCTSTR							pszFrameSet;
	LPCTSTR							pszBtConfirn;
	LPCTSTR							pszBtCancel;

	//��½���
	LPCTSTR							pszLoginBack;
	LPCTSTR							pszRegisterBack;
	LPCTSTR							pszPassLevel;
	LPCTSTR							pszEighteen;
	LPCTSTR							pszLimitprompt;
	LPCTSTR							pszBtCheckBack;
	LPCTSTR							pszBtLogin;
	LPCTSTR							pszBtQuit;
	LPCTSTR							pszBtWebHome;
	LPCTSTR							pszBtRegister;
	LPCTSTR							pszBtChongzhi;
	LPCTSTR							pszBtVersion;
	LPCTSTR							pszBtCloseRegister;
	LPCTSTR							pszBtChose;
	LPCTSTR							pszBtRegisterOk;

	LPCTSTR							pszBtNormalKey[12];
	LPCTSTR							pszBtLowKey[26];
	LPCTSTR							pszBtUpperKey[26];
};

//�¹㳡��Դ
struct tagPlatViewImageNew
{
	LPCTSTR							pszBtGame;
	LPCTSTR							pszBtMatch;
	LPCTSTR							pszBtProperty;
	LPCTSTR							pszBtPrize;
	LPCTSTR							pszBtRecharge;

	LPCTSTR							pszGameBack;
	LPCTSTR							pszGameItemBill;
	LPCTSTR							pszGameItemRegular;
	LPCTSTR							pszGameItemJoin;
	LPCTSTR							pszGameRoomJoin;
	LPCTSTR							pszGameRoomBill;
	LPCTSTR							pszPageMatch;
	LPCTSTR							pszGameTableJoin;
	LPCTSTR							pszGameTableBill;
	LPCTSTR							pszGameTabGame;
	LPCTSTR							pszGameTabCard;
	LPCTSTR							pszGameTabMahj;
	LPCTSTR							pszGameTabLeis;
	LPCTSTR							pszBtReturn;
	LPCTSTR							pszBtFastJoin;
	LPCTSTR							pszTilteImage;
	LPCTSTR							pszGLLast;
	LPCTSTR							pszGLNext;

	LPCTSTR							pszUserInfo;
	LPCTSTR							pszBtModifyUser;
	LPCTSTR							pszBtModifyInfo;
	LPCTSTR							pszBtModifyPassword;
	LPCTSTR							pszModifyUserInfoBack;
	LPCTSTR							pszModifyPasswordBack;
	LPCTSTR							pszBtModifyConfirn;
	LPCTSTR							pszBtModifyCancel;
};


//�����Դ
struct tagPlatformFrameImage
{
	//�����Դ
	UINT							uFrameML;							//��Դ��ʶ
	UINT							uFrameMR;							//��Դ��ʶ
	UINT							uFrameTL;							//��Դ��ʶ
	UINT							uFrameTM;							//��Դ��ʶ
	UINT							uFrameTR;							//��Դ��ʶ
	UINT							uFrameBL;							//��Դ��ʶ
	UINT							uFrameBM;							//��Դ��ʶ
	UINT							uFrameBR;							//��Դ��ʶ

	//�б���Դ
	UINT							uServerML;							//��Դ��ʶ
	UINT							uServerMR;							//��Դ��ʶ
	UINT							uServerTL;							//��Դ��ʶ
	UINT							uServerTM;							//��Դ��ʶ
	UINT							uServerTR;							//��Դ��ʶ
	UINT							uServerBL;							//��Դ��ʶ
	UINT							uServerBM;							//��Դ��ʶ
	UINT							uServerBR;							//��Դ��ʶ

	//��ܰ�ť
	UINT							uBtFrameMin;						//��Դ��ʶ
	UINT							uBtFrameClose;						//��Դ��ʶ
	UINT							uBtFrameMax;						//��Դ��ʶ
	UINT							uBtFrameResore;						//��Դ��ʶ

	UINT							uBtFrameSwitch;						//��Դ��ʶ
	UINT							uBtFrameSelfSet;					//��Դ��ʶ
	UINT							uBtFrameOption;						//��Դ��ʶ

	UINT							uFrameServiceBtShow1;				//��Դ��ʶ
	UINT							uFrameServiceBtHide1;				//��Դ��ʶ
	UINT							uFrameServiceBtShow2;				//��Դ��ʶ
	UINT							uFrameServiceBtHide2;				//��Դ��ʶ

	//�л���ť
	UINT							uBtShowGameList;					//��Դ��ʶ
	UINT							uBtHideGameList;					//��Դ��ʶ
	UINT							uBtFrameItemNormal;					//��Դ��ʶ
	UINT							uBtFrameItemActive;					//��Դ��ʶ

	//������ť
	UINT							uFrameNavigation[5];				//��Դ��ʶ
};

//�㳡��Դ
struct tagPlazaViewImage
{
	//�����Դ
	UINT							uBrowseML;							//��Դ��ʶ
	UINT							uBrowseMR;							//��Դ��ʶ
	UINT							uBrowseTL;							//��Դ��ʶ
	UINT							uBrowseTM;							//��Դ��ʶ
	UINT							uBrowseTR;							//��Դ��ʶ
	UINT							uBrowseBL;							//��Դ��ʶ
	UINT							uBrowseBM;							//��Դ��ʶ
	UINT							uBrowseBR;							//��Դ��ʶ

	//��ť��Դ
	UINT							uBtWebLast;							//��Դ��ʶ
	UINT							uBtWebNext;							//��Դ��ʶ
	UINT							uBtWebStop;							//��Դ��ʶ
	UINT							uBtWebHome;							//��Դ��ʶ
	UINT							uBtWebReload;						//��Դ��ʶ
};

//������Դ
struct tagServerViewImage
{
	//������Դ
	UINT							uChatML;							//��Դ��ʶ
	UINT							uChatMR;							//��Դ��ʶ
	UINT							uChatTL;							//��Դ��ʶ
	UINT							uChatTM;							//��Դ��ʶ
	UINT							uChatTR;							//��Դ��ʶ
	UINT							uChatBL;							//��Դ��ʶ
	UINT							uChatBM;							//��Դ��ʶ
	UINT							uChatBR;							//��Դ��ʶ

	//������Դ
	UINT							uTableML;							//��Դ��ʶ
	UINT							uTableMR;							//��Դ��ʶ
	UINT							uTableTL;							//��Դ��ʶ
	UINT							uTableTM;							//��Դ��ʶ
	UINT							uTableTR;							//��Դ��ʶ
	UINT							uTableBL;							//��Դ��ʶ
	UINT							uTableBM;							//��Դ��ʶ
	UINT							uTableBR;							//��Դ��ʶ

	//�б���Դ
	UINT							uUserListML;						//��Դ��ʶ
	UINT							uUserListMR;						//��Դ��ʶ
	UINT							uUserListTL;						//��Դ��ʶ
	UINT							uUserListTM;						//��Դ��ʶ
	UINT							uUserListTR;						//��Դ��ʶ
	UINT							uUserListBL;						//��Դ��ʶ
	UINT							uUserListBM;						//��Դ��ʶ
	UINT							uUserListBR;						//��Դ��ʶ

	//���찴ť
	UINT							uBtColorSet;						//��Դ��ʶ
	UINT							uBtSendChat;						//��Դ��ʶ
	UINT							uBtExpression;						//��Դ��ʶ
	UINT							uBtBugle;							//��Դ��ʶ
	UINT							uBtCleanScreen;						//��Դ��ʶ
	//UINT							uBtPhrase;							//��Դ��ʶ
	//UINT							uBtSaveChat;						//��Դ��ʶ
	//UINT							uBtChatShort;						//��Դ��ʶ
	//UINT							uBtMoreFunction;					//��Դ��ʶ

	//���Ӱ�ť
	UINT							uBtAutoJoin;						//��Դ��ʶ
	UINT							uBtBank;							//��Դ��ʶ
	UINT							uBtSearchUser;						//��Դ��ʶ
	UINT							uBtQuitRoom;						//��Դ��ʶ
	//UINT							uBtViewMode;						//��Դ��ʶ
	//UINT							uBtCallMaster;						//��Դ��ʶ
	//UINT							uBtGoldManager;						//��Դ��ʶ
	//UINT							uBtServerManage;					//��Դ��ʶ

	//�л���ť
	UINT							uBtShowUserList;					//��Դ��ʶ
	UINT							uBtHideUserList;					//��Դ��ʶ
	//UINT							uBtCustomUserNormal;				//��Դ��ʶ
	//UINT							uBtNormalUserNormal;				//��Դ��ʶ
	//UINT							uBtCustomUserActive;				//��Դ��ʶ
	//UINT							uBtNormalUserActive;				//��Դ��ʶ
};

//˽����Դ
struct tagWhisperViewImage
{
	//������Դ
	UINT							uChatML;							//��Դ��ʶ
	UINT							uChatMR;							//��Դ��ʶ
	UINT							uChatTL;							//��Դ��ʶ
	UINT							uChatTM;							//��Դ��ʶ
	UINT							uChatTR;							//��Դ��ʶ
	UINT							uChatBL;							//��Դ��ʶ
	UINT							uChatBM;							//��Դ��ʶ
	UINT							uChatBR;							//��Դ��ʶ

	//�û���Դ
	UINT							uUserML;							//��Դ��ʶ
	UINT							uUserMR;							//��Դ��ʶ
	UINT							uUserTL;							//��Դ��ʶ
	UINT							uUserTM;							//��Դ��ʶ
	UINT							uUserTR;							//��Դ��ʶ
	UINT							uUserBL;							//��Դ��ʶ
	UINT							uUserBM;							//��Դ��ʶ
	UINT							uUserBR;							//��Դ��ʶ

	//������Դ
	UINT							uInputML;							//��Դ��ʶ
	UINT							uInputMR;							//��Դ��ʶ
	UINT							uInputTL;							//��Դ��ʶ
	UINT							uInputTM;							//��Դ��ʶ
	UINT							uInputTR;							//��Դ��ʶ
	UINT							uInputBL;							//��Դ��ʶ
	UINT							uInputBM;							//��Դ��ʶ
	UINT							uInputBR;							//��Դ��ʶ

	//��ť��Դ
	UINT							uBtAddUser;							//��Դ��ʶ
	UINT							uBtColorSet;						//��Դ��ʶ
	UINT							uBtLeaveChat;						//��Դ��ʶ
	UINT							uBtExpression;						//��Դ��ʶ
	UINT							uBtCleanScreen;						//��Դ��ʶ
	UINT							uBtMoreFunction;					//��Դ��ʶ

	//���ư�ť
	UINT							uBtWhisper;							//��Դ��ʶ
	UINT							uBtSendControl;						//��Դ��ʶ

	//������Դ
	UINT							uChatSplitter;						//��Դ��ʶ
};

//�ؼ���Դ
struct tagControlViewImage
{
	//�û���Ϣ
	UINT							uUserInfoL;							//��Դ��ʶ
	UINT							uUserInfoM;							//��Դ��ʶ
	UINT							uUserInfoR;							//��Դ��ʶ
	//UINT							uBtUserInfoMenu;					//��Դ��ʶ

	//������Դ
	UINT							uCollocateBarActive;				//��Դ��ʶ
	UINT							uCollocateBarBackground;			//��Դ��ʶ
	UINT							uCollocateBarHot;					//��Դ��ʶ
	UINT							uCollocateBarNormal;				//��Դ��ʶ
};

//������Դ
struct tagPropertyViewImage
{
	//��ť��Դ
	UINT							uBtGift[FLOWER_COUNT];				//��Դ��ʶ
	UINT							uBtProperty[PROPERTY_COUNT];		//��Դ��ʶ

	//��ͼ��Դ
	UINT							uPropertyFormer[PROPERTY_COUNT];	//��Դ��ʶ

	//�һ���Դ
	LPCTSTR							pszExChagneArrowhead;				//��Դ��ʶ

	//������Դ
	UINT							uBtBugleColorSet;						//��Դ��ʶ
	UINT							uBtBugleExpression;						//��Դ��ʶ

	//�����Դ
	UINT							uPropertyFrameL;						//��Դ��ʶ
	UINT							uPropertyFrameM;						//��Դ��ʶ
	UINT							uPropertyFrameR;						//��Դ��ʶ
	UINT							uBtPropertyToLeft;						//��Դ��ʶ
	UINT							uBtPropertyToRight;						//��Դ��ʶ
};

//������Դ
struct tagChatExpViewImage
{
	//�Ŀ���Դ
	UINT							uChatBugle;							//��Դ��ʶ
	UINT							uChatGift[FLOWER_COUNT];			//��Դ��ʶ
};

//��Ϸ���
struct tagGameFrameImage
{
	//������Դ
	UINT							uChatML;							//��Դ��ʶ
	UINT							uChatMR;							//��Դ��ʶ
	UINT							uChatTL;							//��Դ��ʶ
	UINT							uChatTM;							//��Դ��ʶ
	UINT							uChatTR;							//��Դ��ʶ
	UINT							uChatBL;							//��Դ��ʶ
	UINT							uChatBM;							//��Դ��ʶ
	UINT							uChatBR;							//��Դ��ʶ

	//�б���Դ
	UINT							uUserListML;						//��Դ��ʶ
	UINT							uUserListMR;						//��Դ��ʶ
	UINT							uUserListTL;						//��Դ��ʶ
	UINT							uUserListTM;						//��Դ��ʶ
	UINT							uUserListTR;						//��Դ��ʶ
	UINT							uUserListBL;						//��Դ��ʶ
	UINT							uUserListBM;						//��Դ��ʶ
	UINT							uUserListBR;						//��Դ��ʶ

	//�û���Դ
	UINT							uBtExchangeCharm;					//��Դ��ʶ
	UINT							uFemaleFace;						//��Դ��ʶ
	UINT							uMaleFace;							//��Դ��ʶ

	//���찴ť
	UINT							uBtColorSet;						//��Դ��ʶ
	UINT							uBtSendChat;						//��Դ��ʶ
	UINT							uBtExpression;						//��Դ��ʶ
	UINT							uBtBugle;							//��Դ��ʶ
	UINT							uBtCleanScreen;						//��Դ��ʶ

	//�л���ť
	UINT							uBtShowUserList;					//��Դ��ʶ
	UINT							uBtHideUserList;					//��Դ��ʶ

	//���ð�ť
	UINT							uBtGameOption;						//��Դ��ʶ
	UINT							uBtGameRule;						//��Դ��ʶ
	UINT							uBtGameLookOn;						//��Դ��ʶ
	UINT							uBtGameUnLookOn;					//��Դ��ʶ
	UINT							uBtGameSound;						//��Դ��ʶ
	UINT							uBtGameUnSound;						//��Դ��ʶ
};

//��Ƶ��Դ
struct tagVideoFrameImage 
{
	//���ܰ�ť
	UINT							uBtBigFlower  ; 					//��Դ��ʶ
	UINT							uBtBigMore    ; 					//��Դ��ʶ
	UINT							uBtBigNosee   ; 					//��Դ��ʶ
	UINT							uBtBigNotalk  ; 					//��Դ��ʶ
	UINT							uBtBigResore  ; 					//��Դ��ʶ
	UINT							uBtBigSee     ; 					//��Դ��ʶ
	UINT							uBtBigTalk    ; 					//��Դ��ʶ
	UINT							uBtSmallFlower; 					//��Դ��ʶ
	UINT							uBtSmallMore  ; 					//��Դ��ʶ
	UINT							uBtSmallNosee ; 					//��Դ��ʶ
	UINT							uBtSmallNotalk; 					//��Դ��ʶ
	UINT							uBtSmallResore; 					//��Դ��ʶ
	UINT							uBtSmallSee   ; 					//��Դ��ʶ
	UINT							uBtSmallTalk  ; 					//��Դ��ʶ

	//�����Դ
	UINT							uBigFemale		; 					//��Դ��ʶ
	UINT							uBigFrame		 ; 					//��Դ��ʶ 
	UINT							uBigMale		 ; 					//��Դ��ʶ 
	UINT							uBigPhoto		; 					//��Դ��ʶ
	UINT							uBigVolume		; 					//��Դ��ʶ
	UINT							uBigVolumeEx	 ; 					//��Դ��ʶ 
	UINT							uSmallFemale	 ; 					//��Դ��ʶ   
	UINT							uSmallFrame	; 					//��Դ��ʶ  
	UINT							uSmallMale		; 					//��Դ��ʶ
	UINT							uSmallPhoto	; 					//��Դ��ʶ  
	UINT							uSmallVolume	; 					//��Դ��ʶ  
	UINT							uSmallVolumeEx; 					//��Դ��ʶ 
};

//���߲˵�
struct tagPropertyMenuImage
{
	UINT							uMenuGift[FLOWER_COUNT];			//��Դ��ʶ	
};

//������Դ
struct tagGiftFlashImage
{
	//�ƶ���Դ
	LPCTSTR							pszGiftMove[FLOWER_COUNT];			//��Դ��ʶ	
};

//////////////////////////////////////////////////////////////////////////

#ifdef _UNICODE
	#define VER_IPlatformResource INTERFACE_VERSION(1,1)
	static const GUID IID_IPlatformResource={0x91931013,0x9969,0x44f4,0x0096,0xb6,0x88,0x61,0x49,0xba,0x52,0xa0};
#else
	#define VER_IPlatformResource INTERFACE_VERSION(1,1)
	static const GUID IID_IPlatformResource={0xd280055a,0x12cb,0x429e,0x00ab,0x09,0x96,0xf4,0x27,0xa5,0xb0,0xc5};
#endif

//��Ϸ��Դ
interface IPlatformResource : public IUnknownEx
{
	//�ں˽ӿ�
public:
	//��Դ���
	virtual HINSTANCE __cdecl GetResInstance()=NULL;
	//��ȡԤ��
	virtual bool __cdecl GetSkinPreview(CImage & ImagePreview)=NULL;

	//��Դ����
public:
	//��Դ����
	virtual void __cdecl SetResourceType(BYTE cbResourceType)=NULL;

	//������Դ
public:
	//������Դ
	virtual VOID * __cdecl GetSkinResource(REFGUID Guid, DWORD dwQueryVer)=NULL;

	//������Դ
public:
	//�㳡��Դ
	virtual bool __cdecl GetPlazaViewImage(tagPlatViewImageNew * PlazaViewImage)=NULL;
	//������Դ
	virtual bool __cdecl GetServerViewImage(tagServerViewImage * ServerViewImage)=NULL;
	//�����Դ
	virtual bool __cdecl GetPlatformFrameImage(tagPlatformFrameImageNew * PlatformFrameImage)=NULL;

	//������Դ
public:
	//˽����Դ
	virtual bool __cdecl GetWhisperViewImage(tagWhisperViewImage * WhisperViewImage)=NULL;
	//�ؼ���Դ
	virtual bool __cdecl GetControlViewImage(tagControlViewImage * ControlViewImage)=NULL;
	//������Դ
	virtual bool __cdecl GetPropertyViewImage(tagPropertyViewImage * PropertyViewImage)=NULL;
	//������Դ
	virtual bool __cdecl GetChatExpViewImage(tagChatExpViewImage * ChatExpViewImage)=NULL;
	//��Ϸ���
	virtual bool __cdecl GetGameFrameImage(tagGameFrameImage * GameFrameImage)=NULL;
	//��Ƶ��Դ
	virtual bool __cdecl GetVideoFrameImage(tagVideoFrameImage * VideoFrameImage)=NULL;
	//���߲˵�
	virtual bool __cdecl GetPropertyMenuImage(tagPropertyMenuImage * PropertyMenuImage)=NULL;
	//������Դ
	virtual bool __cdecl GetGiftFlashImage(tagGiftFlashImage * GiftFlashImage)=NULL;
};

//////////////////////////////////////////////////////////////////////////
//���������

DECLARE_MODULE_HELPER(SkinResource,SKIN_RESOURCE_DLL_NAME,"CreateSkinResource")
DECLARE_MODULE_HELPER(PlatformResource,SKIN_RESOURCE_DLL_NAME,"CreatePlatformResource")

//////////////////////////////////////////////////////////////////////////

#endif