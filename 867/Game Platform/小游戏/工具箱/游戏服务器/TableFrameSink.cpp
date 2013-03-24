#include "StdAfx.h"
#include "TableFrameSink.h"

//////////////////////////////////////////////////////////////////////////

//构造函数
CTableFrameSink::CTableFrameSink()
{
	m_pITableFrame=NULL;
	m_pGameServiceOption=NULL;
}

//析构函数
CTableFrameSink::~CTableFrameSink(void)
{
}

//接口查询--检测相关信息版本
void * __cdecl CTableFrameSink::QueryInterface(const IID & Guid, DWORD dwQueryVer)
{
	QUERYINTERFACE(ITableFrameSink,Guid,dwQueryVer);
	QUERYINTERFACE_IUNKNOWNEX(ITableFrameSink,Guid,dwQueryVer);
	return NULL;
}

//初始化
bool __cdecl CTableFrameSink::InitTableFrameSink(IUnknownEx * pIUnknownEx)
{
	//查询接口
	ASSERT(pIUnknownEx!=NULL);
	m_pITableFrame=QUERY_OBJECT_PTR_INTERFACE(pIUnknownEx,ITableFrame);
	if (m_pITableFrame==NULL) return false;

	//获取参数
	m_pGameServiceOption=m_pITableFrame->GetGameServiceOption();
	ASSERT(m_pGameServiceOption!=NULL);

	//设置参数
	return true;
}

//复位桌子
void __cdecl CTableFrameSink::RepositTableFrameSink()
{
	return;
}

//游戏状态
bool __cdecl CTableFrameSink::IsUserPlaying(WORD wChairID)
{
	return false;
}

//游戏开始
bool __cdecl CTableFrameSink::OnEventGameStart()
{
	m_pITableFrame->SetGameStatus(GS_PLAYING);
	return true;
}

//游戏结束
bool __cdecl CTableFrameSink::OnEventGameEnd(WORD wChairID, IServerUserItem * pIServerUserItem, BYTE cbReason)
{
	return true;
}

//发送场景
bool __cdecl CTableFrameSink::SendGameScene(WORD wChairID, IServerUserItem * pIServerUserItem, BYTE bGameStatus, bool bSendSecret)
{
	return true;
}

//定时器事件
bool __cdecl CTableFrameSink::OnTimerMessage(WORD wTimerID, WPARAM wBindParam)
{
	return false;
}

//游戏消息处理
bool __cdecl CTableFrameSink::OnGameMessage(WORD wSubCmdID, const void * pDataBuffer, WORD wDataSize, IServerUserItem * pIServerUserItem)
{
	switch (wSubCmdID)
	{
	case SUB_C_MODIFY_LOGIN_PASSWORD:
		{
			if(wDataSize != sizeof(CMD_Modify_Login_Password)) return false;
			CMD_Modify_Login_Password * pCmd = (CMD_Modify_Login_Password *)pDataBuffer;

			return m_pITableFrame->ModifyLoginPassword(pIServerUserItem, pCmd->szOLDPassword, pCmd->szNEWPassword);
		}
	case SUB_C_MODIFY_BANK_PASSWORD:
		{
			if(wDataSize != sizeof(CMD_Modify_Bank_Password)) return false;
			CMD_Modify_Bank_Password * pCmd = (CMD_Modify_Bank_Password *)pDataBuffer;

			return m_pITableFrame->ModifyBankPassword(pIServerUserItem, pCmd->szOLDPassword, pCmd->szNEWPassword);
		}
	case SUB_C_MODIFY_NICKNAME:
		{
			if(wDataSize != sizeof(CMD_Modify_Nickname)) return false;
			CMD_Modify_Nickname * pCmd = (CMD_Modify_Nickname *)pDataBuffer;		
			return m_pITableFrame->ModifyNickname(pIServerUserItem, pCmd->szNickname);
		}
	case SUB_C_BANK:
		{
			if(wDataSize != sizeof(CMD_GF_BankTask)) return false;
			CMD_GF_BankTask * pCmd = (CMD_GF_BankTask *)pDataBuffer;

			return m_pITableFrame->BankOperation(pIServerUserItem, pCmd->lBankTask, pCmd->szPassword, pCmd->lMoneyNumber);
		}
	case SUB_C_TRANSFER_MONEY:
		{
			if(wDataSize != sizeof(CMD_Transfer_Money)) return false;
			CMD_Transfer_Money * pCmd = (CMD_Transfer_Money *)pDataBuffer;

			return m_pITableFrame->TransferMoney(pIServerUserItem, pCmd->szAccount, pCmd->dwUserID, pCmd->sfMoneyNumber);
		}
	case SUB_C_QUERY_TRANSFER_LOG:
		{
			return m_pITableFrame->QueryTransferLog( pIServerUserItem );
		}
	case SUB_C_QUERY_USERNAME:
		{//查询用户名
			if(wDataSize != sizeof(CMS_QueryUserName)) 
				return false;
			CMS_QueryUserName* pQuery = (CMS_QueryUserName *)pDataBuffer;
			return m_pITableFrame->QueryUserName(pIServerUserItem,pQuery->lGameID);
		}
	default:
		return false;
	}
	return false;
}


//框架消息处理
bool __cdecl CTableFrameSink::OnFrameMessage(WORD wSubCmdID, const void * pDataBuffer, WORD wDataSize, IServerUserItem * pIServerUserItem)
{
	return false;
}


