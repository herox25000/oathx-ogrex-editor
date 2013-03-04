

#include "StdAfx.h"
#include "GameLogic.h"


//扑克数据
const BYTE CGameLogic::m_cbCardListData[32]=
{
   0x02,  0x04,0x05,0x06,0x07,0x08,0x09, 0x0A,0x0B,0x0C,		//方块 A - K
		  0x14,	    0x16,0x17,0x18,      0x1A,								//梅花 A - K
   0x22,  0x24,0x25,0x26,0x27,0x28,0x29, 0x2A,0x2B,0x2C,		//红桃 A - K
0x31,0x33,0x34,     0x36,0x37,0x38,      0x3A,						//黑桃 A - K
};


//构造函数
CGameLogic::CGameLogic()
{
}

//析构函数
CGameLogic::~CGameLogic()
{
}

//混乱扑克
void CGameLogic::RandCardList(BYTE cbCardBuffer[], BYTE cbBufferCount)
{
	SuperRand();
	//混乱准备
	BYTE cbCardData[CountArray(m_cbCardListData)];
	CopyMemory(cbCardData,m_cbCardListData,sizeof(m_cbCardListData));

	//混乱扑克
	BYTE cbRandCount=0,cbPosition=0;
	do
	{
		cbPosition=rand()%(CountArray(cbCardData)-cbRandCount);
		cbCardBuffer[cbRandCount++]=cbCardData[cbPosition];
		cbCardData[cbPosition]=cbCardData[CountArray(cbCardData)-cbRandCount];
	} while (cbRandCount<cbBufferCount);

	return;
}

//获取牌点
BYTE CGameLogic::GetCardPip(BYTE cbCardData)
{
	//计算牌点
	BYTE cbCardValue=GetCardValue(cbCardData);
	BYTE cbPipCount=(cbCardValue>=10)?0:cbCardValue;

	return cbPipCount;
}

//获取牌点
BYTE CGameLogic::GetCardListPip(const BYTE cbCardData[], BYTE cbCardCount)
{
	//变量定义
	BYTE cbPipCount=0;

	//获取牌点
	for (BYTE i=0;i<cbCardCount;i++)
	{
		cbPipCount=(GetCardPip(cbCardData[i])+cbPipCount)%10;
	}

	return cbPipCount;
}


//--牌九
//判断对子
BYTE CGameLogic::GetCardType(BYTE bCardList[], BYTE bCardCount)
{
	BYTE Value1=GetCardValue(bCardList[0]);
	BYTE Value2=GetCardValue(bCardList[1]);

	if(Value1==Value2) return CT_DOUBLE;
	if( Value1>10&&Value1!=21&&Value2>10&&Value2!=21 ) return CT_SPECIAL;
	return CT_SINGLE;
}

int CGameLogic::GetMaxSingleValue(BYTE bCardList[])//最小为最大
{
	int nValue1=GetSingleTypeLevel(bCardList[0]);
	int nValue2=GetSingleTypeLevel(bCardList[1]);
	return (nValue1<nValue2) ? nValue1 : nValue2;
}

//单张类型大小:红12 > 红2 > 红8 > 红4 > 黑10 6 4 > 红6 7 10 11 > 黑7 8 红9 5
//				0	  1		2	  3		4			5				6
int CGameLogic::GetSingleTypeLevel(BYTE bSingleCard)
{
	BYTE bValue=GetCardValue(bSingleCard);
	BYTE bColor=GetCardColor(bSingleCard)/0x0F;

	if(bValue==12)
	{
		return 0;
	}
	else if(bValue==2)
	{
		return 1;
	}
	else if(bValue==8 && bColor%2==0)
	{
		return 2;
	}
	else if(bValue==4 && bColor%2==0)
	{
		return 3;
	}
	else if(bColor%2==1 && (bValue==10 || bValue==6 || bValue==4))
	{
		return 4;
	}
	else if(bColor%2==0 &&(bValue==6 || bValue==7 || bValue==10|| bValue==11))
	{
		return 5;
	}
	else if((bColor%2==1 && (bValue==7 || bValue==8)) || (bColor%2==0 &&(bValue==9 || bValue== 5)))
	{
		return 6;
	}
	return 7;
}

BYTE CGameLogic::GetMaxColor(BYTE bCardList[])
{
	BYTE Value1=GetCardValue(bCardList[0]);
	BYTE Value2=GetCardValue(bCardList[1]);
	return (Value1>Value2) ? GetCardColor(bCardList[0]) : GetCardColor(bCardList[1]);
}

stCardType CGameLogic::GetCardLevel(BYTE bCardList[])//两张牌
{
	stCardType sCardType;
	if(GetCardValue(bCardList[0])==12 && GetCardValue(bCardList[1])==12)//对天
	{
		sCardType.nCardType=CT_DOUBLE;
		sCardType.nLevel=0;
		return sCardType;
	}

	if(GetCardValue(bCardList[0])==2 && GetCardValue(bCardList[1])==2)//对地
	{
		sCardType.nCardType=CT_DOUBLE;
		sCardType.nLevel=1;
		return sCardType;
	}
	if(GetCardValue(bCardList[0])==1 && GetCardValue(bCardList[1])==3 || GetCardValue(bCardList[0])==3 && GetCardValue(bCardList[1])==1)//皇帝
	{
		sCardType.nCardType=CT_SPECIAL;
		sCardType.nLevel=2;
		return sCardType;
	}
	if(bCardList[0]==0x08 && bCardList[1]==0x28 || bCardList[0]==0x28 && bCardList[1]==0x08)//对人
	{
		sCardType.nCardType=CT_DOUBLE;
		sCardType.nLevel=3;
		return sCardType;
	}
	if(bCardList[0]==0x04 && bCardList[1]==0x24 || bCardList[0]==0x24 && bCardList[1]==0x04)
	{
		sCardType.nCardType=CT_DOUBLE;
		sCardType.nLevel=4;
		return sCardType;
	}
	//10  6  4  黑
	if( bCardList[0]==0x1A && bCardList[1]==0x3A || bCardList[0]==0x3A && bCardList[1]==0x1A ||	\
		bCardList[0]==0x16 && bCardList[1]==0x36 || bCardList[0]==0x36 && bCardList[1]==0x16 ||	\
		bCardList[0]==0x14 && bCardList[1]==0x34 || bCardList[0]==0x3A && bCardList[1]==0x14 
		)
	{
		sCardType.nCardType=CT_DOUBLE;
		sCardType.nLevel=5;
		return sCardType;
	}

	//红  6 7 10   J
	if( bCardList[0]==0x06 && bCardList[1]==0x26 || bCardList[0]==0x26 && bCardList[1]==0x06 ||	\
		bCardList[0]==0x07 && bCardList[1]==0x27 || bCardList[0]==0x27 && bCardList[1]==0x07 ||	\
		bCardList[0]==0x0A && bCardList[1]==0x2A || bCardList[0]==0x2A && bCardList[1]==0x0A ||	\
		bCardList[0]==0x0B && bCardList[1]==0x2B || bCardList[0]==0x2B && bCardList[1]==0x0B 
		)
	{
		sCardType.nCardType=CT_DOUBLE;
		sCardType.nLevel=6;
		return sCardType;
	}

	//黑 7 8  红   9  5
	if( bCardList[0]==0x17 && bCardList[1]==0x37 || bCardList[0]==0x37 && bCardList[1]==0x17 ||	\
		bCardList[0]==0x18 && bCardList[1]==0x38 || bCardList[0]==0x38 && bCardList[1]==0x18 ||	\
		bCardList[0]==0x09 && bCardList[1]==0x29 || bCardList[0]==0x29 && bCardList[1]==0x09 ||	\
		bCardList[0]==0x05 && bCardList[1]==0x25 || bCardList[0]==0x25 && bCardList[1]==0x05 
		)
	{
		sCardType.nCardType=CT_DOUBLE;
		sCardType.nLevel=7;
		return sCardType;
	}

	if(GetCardValue(bCardList[0])==12 && GetCardValue(bCardList[1])==9 || GetCardValue(bCardList[0])==9 && GetCardValue(bCardList[1])==12)
	{
		sCardType.nCardType=CT_SPECIAL;
		sCardType.nLevel=8;
		return sCardType;
	}
	if(GetCardValue(bCardList[0])==12 && GetCardValue(bCardList[1])==8 || GetCardValue(bCardList[0])==8 && GetCardValue(bCardList[1])==12)
	{
		sCardType.nCardType=CT_SPECIAL;
		sCardType.nLevel=9;
		return sCardType;
	}
	if(GetCardValue(bCardList[0])==2 && GetCardValue(bCardList[1])==8 || GetCardValue(bCardList[0])==8 && GetCardValue(bCardList[1])==2)
	{
		sCardType.nCardType=CT_SPECIAL;
		sCardType.nLevel=10;
		return sCardType;
	}

	sCardType.nCardType=CT_SINGLE;
	sCardType.nLevel=11;
	return sCardType;
}
bool CGameLogic::CompareCard(BYTE bFirstList[], BYTE bNextList[], BYTE bCardCount)//庄   闲  庄赢为true
{
	stCardType sFirstCard,sNextCard;
	sFirstCard=GetCardLevel(bFirstList);
	sNextCard=GetCardLevel(bNextList);
	if(sFirstCard.nLevel==sNextCard.nLevel)
	{
		if(sFirstCard.nCardType==CT_SINGLE && sNextCard.nCardType==CT_SINGLE)
		{
			BYTE FirstTotalValue=(GetCardLogicValue(bFirstList[0])+GetCardLogicValue(bFirstList[1]))%10;
			BYTE NextTotalValue=(GetCardLogicValue(bNextList[0])+GetCardLogicValue(bNextList[1]))%10;

			if(FirstTotalValue==NextTotalValue) 
			{
				if(FirstTotalValue==0)return true;
				int bValue1=GetMaxSingleValue(bFirstList);//庄
				int bValue2=GetMaxSingleValue(bNextList);
				if(bValue1>bValue2)
				{
					return false;
				}
				return true;
			}
			else 
			{
				return FirstTotalValue>NextTotalValue;
			}
		}
		else
		{
			return true;
		}
	}
	else
	{
		return sFirstCard.nLevel<sNextCard.nLevel ? true: false;
	}
	return false;
}

//排列扑克
void CGameLogic::SortCard(BYTE bCardData[], BYTE bCardCount)
{
	//转换数值
	BYTE bLogicVolue[2];
	for (BYTE i=0;i<bCardCount;i++)	bLogicVolue[i]=GetCardLogicValue(bCardData[i]);

	//排序操作
	bool bSorted=true;
	BYTE bTempData,bLast=bCardCount-1;
	do
	{
		bSorted=true;
		for (BYTE i=0;i<bLast;i++)
		{
			if ((bLogicVolue[i]<bLogicVolue[i+1])||
				((bLogicVolue[i]==bLogicVolue[i+1])&&(bCardData[i]<bCardData[i+1])))
			{
				//交换位置
				bTempData=bCardData[i];
				bCardData[i]=bCardData[i+1];
				bCardData[i+1]=bTempData;
				bTempData=bLogicVolue[i];
				bLogicVolue[i]=bLogicVolue[i+1];
				bLogicVolue[i+1]=bTempData;
				bSorted=false;
			}	
		}
		bLast--;
	} while(bSorted==false);
	return;
}
CString CGameLogic::GetCardNick(BYTE bCardList[])
{
	if(sizeof(bCardList)<2)return NULL;
	if(GetCardValue(bCardList[0])==12 && GetCardValue(bCardList[1])==12)
		return "对天";
	if(GetCardValue(bCardList[0])==2 && GetCardValue(bCardList[1])==2)
		return "对地";
	if(GetCardValue(bCardList[0])==1 && GetCardValue(bCardList[1])==3 || GetCardValue(bCardList[0])==3 && GetCardValue(bCardList[1])==1)
		return "皇帝";
	if(bCardList[0]==0x08 && bCardList[1]==0x28 || bCardList[0]==0x28 && bCardList[1]==0x08)
		return "对人";
	if(bCardList[0]==0x04 && bCardList[1]==0x24 || bCardList[0]==0x24 && bCardList[1]==0x04)
		return "对合";
	if(GetCardValue(bCardList[0])==12 && GetCardValue(bCardList[1])==9 || GetCardValue(bCardList[0])==9 && GetCardValue(bCardList[1])==12)
		return "天九王";
	if(GetCardValue(bCardList[0])==12 && GetCardValue(bCardList[1])==8 || GetCardValue(bCardList[0])==8 && GetCardValue(bCardList[1])==12)
		return "天杠";
	if(GetCardValue(bCardList[0])==2 && GetCardValue(bCardList[1])==8 || GetCardValue(bCardList[0])==8 && GetCardValue(bCardList[1])==2)
		return "地杠";


	//10  6  4  黑
	if( bCardList[0]==0x1A && bCardList[1]==0x3A || bCardList[0]==0x3A && bCardList[1]==0x1A ||	\
		bCardList[0]==0x16 && bCardList[1]==0x36 || bCardList[0]==0x36 && bCardList[1]==0x16 ||	\
		bCardList[0]==0x14 && bCardList[1]==0x34 || bCardList[0]==0x3A && bCardList[1]==0x14 
		)
	{
		return "对(黑 10 ,6,4)";
	}

	//红  6 7 10   J
	if( bCardList[0]==0x06 && bCardList[1]==0x26 || bCardList[0]==0x26 && bCardList[1]==0x06 ||	\
		bCardList[0]==0x07 && bCardList[1]==0x27 || bCardList[0]==0x27 && bCardList[1]==0x07 ||	\
		bCardList[0]==0x0A && bCardList[1]==0x2A || bCardList[0]==0x2A && bCardList[1]==0x0A ||	\
		bCardList[0]==0x0B && bCardList[1]==0x2B || bCardList[0]==0x2B && bCardList[1]==0x0B 
		)
	{
		return "对(红 6 7 10 J)";
	}

	//黑 7 8  红   9  5
	if( bCardList[0]==0x17 && bCardList[1]==0x37 || bCardList[0]==0x37 && bCardList[1]==0x17 ||	\
		bCardList[0]==0x18 && bCardList[1]==0x38 || bCardList[0]==0x38 && bCardList[1]==0x18 ||	\
		bCardList[0]==0x09 && bCardList[1]==0x29 || bCardList[0]==0x29 && bCardList[1]==0x09 ||	\
		bCardList[0]==0x05 && bCardList[1]==0x25 || bCardList[0]==0x25 && bCardList[1]==0x05 
		)
	{
		return "对(黑 7 8 红 9 5)";
	}


	BYTE TotalValue=(GetCardLogicValue(bCardList[0])+GetCardLogicValue(bCardList[1]))%10;
	CString str;
	str.Format("%u点",TotalValue);
	return str;
}

//////////////////////////////////////////////////////////////////////////
