USE QPTreasureDB
GO

-- ��Ա������
TRUNCATE TABLE GlobalLivcard
GO

INSERT [dbo].[GlobalLivcard] ( [CardName], [CardPrice], [CardGold], [MemberOrder], [MemberDays], [UserRight], [ServiceRight]) VALUES ( N'ˮ���¿�', CAST(10.00 AS Decimal(18, 2)), 100000, 1, 30, 512, 0)
INSERT [dbo].[GlobalLivcard] ( [CardName], [CardPrice], [CardGold], [MemberOrder], [MemberDays], [UserRight], [ServiceRight]) VALUES ( N'�ƽ𼾿�', CAST(30.00 AS Decimal(18, 2)), 300000, 2, 90, 512, 0)
INSERT [dbo].[GlobalLivcard] ( [CardName], [CardPrice], [CardGold], [MemberOrder], [MemberDays], [UserRight], [ServiceRight]) VALUES ( N'�׽���꿨', CAST(60.00 AS Decimal(18, 2)), 600000, 3, 180, 512, 0)
INSERT [dbo].[GlobalLivcard] ( [CardName], [CardPrice], [CardGold], [MemberOrder], [MemberDays], [UserRight], [ServiceRight]) VALUES ( N'��ʯ�꿨', CAST(120.00 AS Decimal(18, 2)), 1200000, 4, 360, 512, 0)

GO