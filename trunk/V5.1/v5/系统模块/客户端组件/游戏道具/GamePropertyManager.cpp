#include "StdAfx.h"
#include "GamePropertyManager.h"

//////////////////////////////////////////////////////////////////////////////////

//��̬����
CGamePropertyManager * CGamePropertyManager::m_pGamePropertyManager=NULL;//����ָ��

//////////////////////////////////////////////////////////////////////////////////

//���캯��
CGamePropertyManager::CGamePropertyManager()
{
	//���ñ���
	ASSERT(m_pGamePropertyManager==NULL);
	if (m_pGamePropertyManager==NULL) m_pGamePropertyManager=this;

	return;
}

//��������
CGamePropertyManager::~CGamePropertyManager()
{
	//���ñ���
	ASSERT(m_pGamePropertyManager==this);
	if (m_pGamePropertyManager==this) m_pGamePropertyManager=NULL;

	return;
}

//��ȡ����
CGamePropertyItem * CGamePropertyManager::GetPropertyItem(WORD wIndex)
{
	//���ҵ���
	CGamePropertyItem * pGamePropertyItem=NULL;
	m_MapPropertyItem.Lookup(wIndex,pGamePropertyItem);

	return pGamePropertyItem;
}

//��������
CGamePropertyItem * CGamePropertyManager::CreatePropertyItem(tagPropertyInfo & PropertyInfo)
{
	//�����ִ�
	CGamePropertyItem * pGamePropertyItem=NULL;
	m_MapPropertyItem.Lookup(PropertyInfo.wIndex,pGamePropertyItem);

	//�ִ��ж�
	if (pGamePropertyItem!=NULL)
	{
		//���õ���
		pGamePropertyItem->m_PropertyInfo=PropertyInfo;

		//���ȹ���
		if(PropertyInfo.wIndex==PROPERTY_ID_TRUMPET || PropertyInfo.wIndex==PROPERTY_ID_TYPHON)
			return NULL;
		else
			return pGamePropertyItem;
	}

	//��������
	switch (PropertyInfo.wIndex)
	{
	case PROPERTY_ID_CAR:			//��������
		{
			try
			{
				pGamePropertyItem=new CGamePropertyCar;
			}
			catch (...)
			{
				ASSERT(FALSE);
			}

			break;
		}
	case PROPERTY_ID_EGG:			//��������
		{
			try
			{
				pGamePropertyItem=new CGamePropertyEgg;
			}
			catch (...)
			{
				ASSERT(FALSE);
			}

			break;
		}
	case PROPERTY_ID_CLAP:			//��������
		{
			try
			{
				pGamePropertyItem=new CGamePropertyClap;
			}
			catch (...)
			{
				ASSERT(FALSE);
			}

			break;
		}
	case PROPERTY_ID_KISS:			//��������
		{
			try
			{
				pGamePropertyItem=new CGamePropertyKiss;
			}
			catch (...)
			{
				ASSERT(FALSE);
			}

			break;
		}
	case PROPERTY_ID_BEER:			//ơ������
		{
			try
			{
				pGamePropertyItem=new CGamePropertyBeer;
			}
			catch (...)
			{
				ASSERT(FALSE);
			}

			break;
		}
	case PROPERTY_ID_CAKE:			//��������
		{
			try
			{
				pGamePropertyItem=new CGamePropertyCake;
			}
			catch (...)
			{
				ASSERT(FALSE);
			}

			break;
		}
	case PROPERTY_ID_RING:			//�������
		{
			try
			{
				pGamePropertyItem=new CGamePropertyRing;
			}
			catch (...)
			{
				ASSERT(FALSE);
			}

			break;
		}
	case PROPERTY_ID_BEAT:			//��������
		{
			try
			{
				pGamePropertyItem=new CGamePropertyBeat;
			}
			catch (...)
			{
				ASSERT(FALSE);
			}

			break;
		}
	case PROPERTY_ID_BOMB:			//ը������
		{
			try
			{
				pGamePropertyItem=new CGamePropertyBomb;
			}
			catch (...)
			{
				ASSERT(FALSE);
			}

			break;
		}
	case PROPERTY_ID_SMOKE:			//��������
		{
			try
			{
				pGamePropertyItem=new CGamePropertySmoke;
			}
			catch (...)
			{
				ASSERT(FALSE);
			}

			break;
		}
	case PROPERTY_ID_VILLA:			//��������
		{
			try
			{
				pGamePropertyItem=new CGamePropertyVilla;
			}
			catch (...)
			{
				ASSERT(FALSE);
			}

			break;
		}
	case PROPERTY_ID_BRICK:			//שͷ����
		{
			try
			{
				pGamePropertyItem=new CGamePropertyBrick;
			}
			catch (...)
			{
				ASSERT(FALSE);
			}

			break;
		}
	case PROPERTY_ID_FLOWER:		//�ʻ�����
		{
			try
			{
				pGamePropertyItem=new CGamePropertyFlower;
			}
			catch (...)
			{
				ASSERT(FALSE);
			}

			break;
		}
	case PROPERTY_ID_TWO_CARD:    //˫������
		{
			try
			{
				pGamePropertyItem=new CGamePropertyTwoScoreCard;
			}
			catch (...)
			{
				ASSERT(FALSE);
			}

			break;
		}
	case PROPERTY_ID_FOUR_CARD:    //�ı�����
		{
			try
			{
				pGamePropertyItem=new CGamePropertyFourScoreCard;
			}
			catch (...)
			{
				ASSERT(FALSE);
			}

			break;
		}
	case PROPERTY_ID_SCORE_CLEAR:    //��������
		{
			try
			{
				pGamePropertyItem=new CGamePropertyScoreClear;
			}
			catch (...)
			{
				ASSERT(FALSE);
			}

			break;
		}
	case PROPERTY_ID_ESCAPE_CLEAR:    //��������
		{
			try
			{
				pGamePropertyItem=new CGamePropertyEscapeClear;
			}
			catch (...)
			{
				ASSERT(FALSE);
			}

			break;
		}
	case PROPERTY_ID_TRUMPET:		  //С����
		{
			try
			{
				pGamePropertyItem=new CGamePropertyTrumpet;
			}
			catch (...)
			{
				ASSERT(FALSE);
			}

			break;
		}
	case PROPERTY_ID_TYPHON:		  //������
		{
			try
			{
				pGamePropertyItem=new CGamePropertyTyphon;
			}
			catch (...)
			{
				ASSERT(FALSE);
			}

			break;
		}
	case PROPERTY_ID_GUARDKICK_CARD:   //���߿�
		{
			try
			{
				pGamePropertyItem=new CGamePropertyGuardKickCard;
			}
			catch (...)
			{
				ASSERT(FALSE);
			}

			break;
		}
	case PROPERTY_ID_POSSESS:		  //�����
		{
			try
			{
				pGamePropertyItem=new CGamePropertyPossess;
			}
			catch (...)
			{
				ASSERT(FALSE);
			}

			break;
		}
	case PROPERTY_ID_BLUERING_CARD:	  //�����Ա��
		{
			try
			{
				pGamePropertyItem=new CGamePropertyBlueRingCard;
			}
			catch (...)
			{
				ASSERT(FALSE);
			}

			break;
		}
	case PROPERTY_ID_YELLOWRING_CARD:	//�����Ա��
		{
			try
			{
				pGamePropertyItem=new CGamePropertyYellowRingCard;
			}
			catch (...)
			{
				ASSERT(FALSE);
			}

			break;
		}
	case PROPERTY_ID_WHITERING_CARD:	//�����Ա��
		{
			try
			{
				pGamePropertyItem=new CGamePropertyWhiteRingCard;
			}
			catch (...)
			{
				ASSERT(FALSE);
			}

			break;
		}
	case PROPERTY_ID_REDRING_CARD:		//�����Ա��
		{
			try
			{
				pGamePropertyItem=new CGamePropertyRedRingCard;
			}
			catch (...)
			{
				ASSERT(FALSE);
			}

			break;
		}
	case PROPERTY_ID_VIPROOM_CARD:		//VIP����
		{
			try
			{
				pGamePropertyItem=new CGamePropertyVipRoomCard;
			}
			catch (...)
			{
				ASSERT(FALSE);
			}

			break;
		}
	}

	//�����ж�
	if (pGamePropertyItem!=NULL)
	{
		//���õ���
		pGamePropertyItem->m_PropertyInfo=PropertyInfo;
		m_MapPropertyItem[PropertyInfo.wIndex]=pGamePropertyItem;

		//���ȹ���
		if(PropertyInfo.wIndex==PROPERTY_ID_TRUMPET || PropertyInfo.wIndex==PROPERTY_ID_TYPHON)
			return NULL;
		else
			return pGamePropertyItem;
	}

	//�������
	ASSERT(FALSE);

	return NULL;
}

//////////////////////////////////////////////////////////////////////////////////
