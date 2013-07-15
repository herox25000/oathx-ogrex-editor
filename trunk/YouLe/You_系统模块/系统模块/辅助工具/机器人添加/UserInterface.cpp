#include "StdAfx.h"
#include ".\userinterface.h"
#include "..\..\开发库\Include\Encrypt.h"
#include "define.h"
#include "Resource.h"
#define OUTCARDTIME 100

extern struct TableInfo      mTableInfo[TABLE_NUM];
extern BOOL bIsHaveMannage;

CUserInterface::CUserInterface(void)
{
	DelayTime=0;
	m_TableNum=0;
	m_ChairNum=0;
	m_GameNum=0;
	TableOldID=255;
	m_CurrentGameNum=0;
	bIsMannageTableInfo=FALSE;
	UserStatus=NOCONNECT;
	GameStatus=US_NULL;
	ExitGameStatus=GAMEPLAYING;
	bIsReSel=FALSE;
	bIsInvite=FALSE;
	bIsExitByUser=false;
}

CUserInterface::~CUserInterface(void)
{
}
void   CUserInterface::CreateSocketInstance()
{
	this->CreateInstance();
	this->GetInterface()->SetSocketSink(this);
}
//接口查询
void * __cdecl CUserInterface::QueryInterface(const IID & Guid, DWORD dwQueryVer)
{
	QUERYINTERFACE(IClientSocketSink,Guid,dwQueryVer);
	QUERYINTERFACE_IUNKNOWNEX(IClientSocketSink,Guid,dwQueryVer);
	return NULL;
}
void   CUserInterface::SetUserStatus(BYTE mUserStatus)
{
	ExitGameStatus=mUserStatus;
	if(GameStatus<=US_READY)
	{
		DelayTime=(rand()%100)*50;
		UserStatus=mUserStatus;
	}
}
void   CUserInterface::SetUserID(DWORD mUserID)
{
	UserID=mUserID;
}
void   CUserInterface::SetUserPass(TCHAR *mUserPass)
{
	CMD5Encrypt::EncryptData(mUserPass,szPassword);
}
void   CUserInterface::SetTable(BYTE mTable,BYTE mChair)
{
	TableID=mTable;
	ChairID=mChair;
}
void   CUserInterface::SetConnectInfo(DWORD	mIP,WORD mPort)
{
	dwIP=mIP;
	wPort=mPort;
}
void   CUserInterface::SetDealyTime(int mDelayTime)
{
	DelayTime=mDelayTime;
}
BYTE   CUserInterface::GetUserStatus()
{
	return UserStatus;
}
DWORD  CUserInterface::GetUserID()
{
	return  UserID;
}
BYTE   CUserInterface::GetTableID()
{
	return TableID;
}
BYTE   CUserInterface::GetChairID()
{
	return ChairID;
}
bool   CUserInterface::ConnectSever()
{
	return this->GetInterface()->Connect(dwIP,wPort);
}
//发送登陆消息
void   CUserInterface::SendLogonData()
{
	BYTE cbBuffer[SOCKET_PACKAGE];
			//登陆数据包
	CMD_GR_LogonByUserID * pLogonByUserID=(CMD_GR_LogonByUserID *)cbBuffer;
	pLogonByUserID->dwUserID=UserID;
	pLogonByUserID->dwPlazaVersion=VER_PLAZA_FRAME;
	lstrcpyn(pLogonByUserID->szPassWord,szPassword,sizeof(szPassword));
	this->GetInterface()->SendData(MDM_GR_LOGON,SUB_GR_LOGON_USERID,cbBuffer,sizeof(CMD_GR_LogonByUserID));
	DelayTime=5000;
	UserStatus=GAMEPLAYING;
}
//发送请求坐下消息
void   CUserInterface::SendReqSiteData()
{
	CMD_GR_UserSitReq  pUserSitReq;
	pUserSitReq.wTableID=TableID;
	pUserSitReq.wChairID=ChairID;
	memset(pUserSitReq.szTablePass,0,33);
	pUserSitReq.wNetTimelag=0;
	pUserSitReq.cbPassLen=CountString(pUserSitReq.szTablePass);
	//发送数据包
	WORD wSendSize=sizeof(pUserSitReq)-sizeof(pUserSitReq.szTablePass)+pUserSitReq.cbPassLen;
	if(this->GetInterface()->SendData(MDM_GR_USER,SUB_GR_USER_SIT_REQ,&pUserSitReq,wSendSize))
	{
		DelayTime=50+20*(rand()%10);
		UserStatus=SITINDESK;
	}
	else
		DelayTime=100;
}
//发送请求起立消息
void   CUserInterface::SendReqStandUpData()
{
	if(this->GetInterface()->SendData(MDM_GR_USER,SUB_GR_USER_STANDUP_REQ))
	{
		DelayTime=1000+(rand()%100)*200;
		UserStatus=STILLINROOM;
	}
	else
		DelayTime=100;
}
//发送准备消息
void   CUserInterface::SendUserReadyData()
{
	if(this->GetInterface()->SendData(MDM_GF_FRAME,SUB_GF_USER_READY))
	{
		DelayTime=5000+100*(rand()%200);
		UserStatus=GAMEFINISH;
	}
	else
		DelayTime=100;
}
//发送游戏数据
bool   CUserInterface::SendGameData(WORD wSubCmdID)
{
	return this->GetInterface()->SendData(MDM_GF_GAME,wSubCmdID);
}
bool   CUserInterface::SendGameData(WORD wSubCmdID, void * pData, WORD wDataSize)
{
	return this->GetInterface()->SendData(MDM_GF_GAME,wSubCmdID,pData,wDataSize);
}
//网络读取消息
bool __cdecl CUserInterface::OnSocketRead(CMD_Command Command, void * pBuffer, WORD wDataSize, IClientSocket * pIClientSocke)
{
	switch (Command.wMainCmdID)
	{
	//登录消息
	case MDM_GR_LOGON:			
		{
			switch(Command.wSubCmdID)
			{
			case SUB_GR_LOGON_FINISH:		//登录成功
				m_GameNum=3+(rand()%10);
				m_CurrentGameNum=0;
				/*if(ExitGameStatus==OFFLINE)
				{
					if(mTableInfo[TableID].TableStatus==TABLEPLAYING)
					{
						this->GetInterface()->SendData(MDM_GR_USER,SUB_GR_USER_LEFT_GAME_REQ);
						this->GetInterface()->SendData(MDM_GR_USER,SUB_GR_USER_STANDUP_REQ);
						mTableInfo[TableID].TableStatus=TABLEFREE;
					}
				}*/
				DelayTime=100+50*(rand()%100);
				UserStatus=STILLINROOM;
				return true;
			case SUB_GR_LOGON_ERROR:
				{
					//DelayTime=60000;
					//UserStatus=OFFLINE;
					return true;
				}
			}
		}
			//用户消息
	case MDM_GR_USER:			
		{
			switch(Command.wSubCmdID)
			{
			case SUB_GR_USER_STATUS:
				{
					CMD_GR_UserStatus  *p=(CMD_GR_UserStatus *)pBuffer;
					if(p->dwUserID==UserID)
					{
						GameStatus=p->cbUserStatus;
					}
					if(bIsMannageTableInfo)
					{
						if(p->wTableID<TABLE_NUM&&p->wChairID<CHAIR_NUM&&p->cbUserStatus!=US_LOOKON)
						{
							mTableInfo[p->wTableID].ChairStatus[p->wChairID]=p->cbUserStatus;
							mTableInfo[p->wTableID].ChairUserID[p->wChairID]=p->dwUserID;
						}
						else
						{
								for (int n=0;n<m_TableNum;n++)
								{
									for(int m=0;m<m_ChairNum;m++)
									{
										if(mTableInfo[n].ChairUserID[m]==p->dwUserID)
										{
											mTableInfo[n].ChairStatus[m]=US_FREE;
										}
									}
								}
						}
					}
					return true;
				}
			case SUB_GR_USER_COME:
				{
					tagUserInfoHead * p=(tagUserInfoHead *)pBuffer;
					if(p->dwUserID==UserID)
					{
						GameStatus=p->cbUserStatus;
					}
					if(bIsMannageTableInfo)
					{
						if(p->wTableID<TABLE_NUM&&p->wChairID<CHAIR_NUM)
						{
							mTableInfo[p->wTableID].ChairUserID[p->wChairID]=p->dwUserID;
							mTableInfo[p->wTableID].ChairStatus[p->wChairID]=p->cbUserStatus;
						}
					}
					return true;
				}
			case SUB_GR_SIT_FAILED:
				{
					if(TableID<TABLE_NUM&&ChairID<CHAIR_NUM)
						mTableInfo[TableID].ChairStatus[ChairID]=US_FREE;
					DelayTime=10000+500*(rand()%100);
					UserStatus=STILLINROOM;
					return true;
				}
			case  SUB_GR_USER_INVITE:
				{
                      CMD_GR_UserInvite * p=(CMD_GR_UserInvite *)pBuffer;
					 // TableID=p->wTableID;
					  DelayTime=100;
					  bIsInvite=TRUE;
					  UserStatus=STILLINROOM;
				}
			}
			return true;
		}
			//配置信息
	case MDM_GR_INFO:			
		{
			switch(Command.wSubCmdID)
			{
			case SUB_GR_SERVER_INFO:
				{
					CMD_GR_ServerInfo *p=(CMD_GR_ServerInfo *)pBuffer;
					if(m_ChairNum==0&&m_TableNum==0)
					{
						m_ChairNum=p->wChairCount;
						m_TableNum=p->wTableCount;
					}
					return true;
				}
			}
			return true;
		}
		//状态信息
	case MDM_GR_STATUS:			
		{
			switch(Command.wSubCmdID)
			{
			case SUB_GR_TABLE_STATUS:
				{
					if(bIsMannageTableInfo)
					{
						CMD_GR_TableStatus *p=(CMD_GR_TableStatus *)pBuffer;
						if(TableID<TABLE_NUM)
						{
							if(p->bPlayStatus<US_FREE)
								mTableInfo[p->wTableID].TableStatus=TABLEFREE;
							else
								mTableInfo[p->wTableID].TableStatus=TABLEPLAYING;
						}
					}
					return true;
				}
			}
		}
		//游戏消息
	case MDM_GF_GAME:			
	//框架消息
	case MDM_GF_FRAME:			
		{
			//发送数据
			OnGameMessage(Command.wSubCmdID,pBuffer,wDataSize);
			return true;
		}
	}
	return true;
}
//网络关闭消息
bool __cdecl CUserInterface::OnSocketClose(IClientSocket * pIClientSocke, bool bCloseByServer)
{
	if(!bIsExitByUser)
	{
		if(bIsMannageTableInfo)
		{
			bIsHaveMannage=FALSE;
			bIsMannageTableInfo=FALSE;
		}
		DelayTime=100000;
		m_TableNum=0;
		m_ChairNum=0;
		bIsMannageTableInfo=FALSE;
		//m_wCurrentOutCard=255;
		UserStatus=OFFLINE;
	}
	return true;
}
//网络连接消息
bool __cdecl CUserInterface::OnSocketConnect(int iErrorCode, LPCTSTR pszErrorDesc, IClientSocket * pIClientSocke)
{
	if (iErrorCode==0)
	{
		DelayTime=0;
		UserStatus=NOCONNECT;
	}
	return true;
}
//出牌逻辑判断
bool CUserInterface::SearchTableChair()
{
	BOOL bIsSearch=FALSE;   //是否找到位置
	int  mTablePlaerCount=0;
	if(bIsInvite)
	{
		for(int m=0;m<m_ChairNum;m++)
		{
			if(mTableInfo[TableID].ChairStatus[m]==US_NULL||mTableInfo[TableID].ChairStatus[m]==US_FREE)
			{
				ChairID=m;
				bIsSearch=TRUE;
			}
		}
		bIsInvite=FALSE;
	}
	else
	{
		for (int n=0;n<m_TableNum;n++)
		{
			if(mTableInfo[n].TableStatus==TABLEPLAYING)
			{
				continue;
			}
			if(TableOldID==n)
				continue;
			if(!bIsSearch)
			{
				for(int m=0;m<m_ChairNum;m++)
				{
					if(mTableInfo[n].ChairStatus[m]==US_NULL||mTableInfo[n].ChairStatus[m]==US_FREE)
					{
						TableID=n;
						ChairID=m;
						bIsSearch=TRUE;
					}
				}
			}
			else
			{
				int mTempChairCount=0;
				BOOL bIsHaveFreeChair=FALSE;
				BYTE TempChair=255;
				for(int m=0;m<m_ChairNum;m++)
				{
					if(mTableInfo[n].ChairStatus[m]>US_FREE)
					{
						mTempChairCount++;
					}
					else
					{
						if(!bIsHaveFreeChair)
							TempChair=m;
						bIsHaveFreeChair=TRUE;
					}
				}
				if(mTempChairCount>mTablePlaerCount&&bIsHaveFreeChair)
				{
					TableID=n;
					ChairID=TempChair;
					mTablePlaerCount=mTempChairCount;
				}
			}
		}
	}
	if(!bIsSearch)
		DelayTime=10000;
	mTableInfo[TableID].ChairStatus[ChairID]=US_SIT;
	UserStatus=READYTOSIT;
	DelayTime=0;
	TableOldID=TableID;
	return false;
}
bool  CUserInterface::OnGameMessage(WORD wSubCmdID, const void * pBuffer, WORD wDataSize)
{
	return true;
}
bool   CUserInterface::SubDelayTime()
{
	if(DelayTime<-1)
		return true;
	DelayTime--;
	if(DelayTime>0)
	{
		return true;
	}
	switch(UserStatus)
	{
	case NOCONNECT:              //没有进入房间
		{
			//if(GameStatus==US_NULL)
				SendLogonData();
			//else
			//	DelayTime=100;
			return true;
		}
	case STILLINROOM:     			//在房间大厅
		{
			//if(GameStatus<US_SIT)
				SearchTableChair();
			//else
			//	DelayTime=100;
			return	false;
		}
	case SITINDESK:       			//坐在位子上
		{
			if(ExitGameStatus==CLOSECONNECT)
			{
				UserStatus=CLOSECONNECT;
				DelayTime=(rand()%10)*10;
				return true;
			}
			//if(GameStatus==US_SIT)
				SendUserReadyData();
			//else
			//	DelayTime=100;
			return	false;
		}
	case READYTOSIT:       			//已经同意开始
		{
			SendReqSiteData();
			return	true;
		}
	case GAMEPLAYING:               //游戏状态
		{
			return	false;
		}
	case  GAMEFINISH:         	    //游戏结束状态
		{
			//if(GameStatus<=US_READY)
				SendReqStandUpData();
			//else
		//	{
		//		UserStatus=GAMEPLAYING;
		//	}
			return true;
		}
	case  OFFLINE:         			//断线重入状态状态
		{
			//if(GameStatus==US_OFFLINE)
			//{
				ExitGameStatus=OFFLINE;
				if(!this->GetInterface()->Connect(dwIP,wPort))
				{
					DelayTime=60000;
					UserStatus=OFFLINE;
				}
			//}
			return true;
		}
		case CLOSECONNECT:
		{
			this->GetInterface()->SendData(MDM_GR_USER,SUB_GR_USER_LEFT_GAME_REQ);
			this->GetInterface()->CloseSocket(false);
			return true;
		}
	}
	return true;
}