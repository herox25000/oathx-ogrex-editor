----------------------------------------------------------------------
-- ʱ�䣺2011-10-20
-- ��;�����ݻ���ͳ�ơ�
----------------------------------------------------------------------
USE QPTreasureDB
GO

SET QUOTED_IDENTIFIER ON 
GO

SET ANSI_NULLS ON 
GO

IF EXISTS (SELECT * FROM DBO.SYSOBJECTS WHERE ID = OBJECT_ID(N'[dbo].NET_PM_StatInfo') and OBJECTPROPERTY(ID, N'IsProcedure') = 1)
DROP PROCEDURE [dbo].NET_PM_StatInfo
GO

----------------------------------------------------------------------
CREATE PROC NET_PM_StatInfo
			
WITH ENCRYPTION AS

BEGIN
	-- ��������
	SET NOCOUNT ON;	
	--�û�ͳ��
	DECLARE @OnLineCount INT		--��������
	DECLARE @DisenableCount INT		--ͣȨ�û�
	DECLARE @AllCount INT			--ע��������
	SELECT  TOP 1 @OnLineCount=ISNULL(OnLineCountSum,0) FROM  QPPlatformDB.dbo.OnLineStreamInfo(NOLOCK) ORDER BY InsertDateTime DESC
	SELECT  @DisenableCount=COUNT(UserID) FROM QPAccountsDB.dbo.AccountsInfo(NOLOCK) WHERE Nullity = 1
	SELECT  @AllCount=COUNT(UserID) FROM QPAccountsDB.dbo.AccountsInfo(NOLOCK)

	--���ͳ��
	DECLARE @Score BIGINT		--�������
	DECLARE @InsureScore BIGINT	--��������
	DECLARE @AllScore BIGINT
	SELECT  @Score=SUM(Score),@InsureScore=SUM(InsureScore),@AllScore=SUM(Score+InsureScore) FROM QPTreasureDB.dbo.GameScoreInfo(NOLOCK)

	--����ͳ��
	DECLARE @RegGrantScore BIGINT		--ע������
	DECLARE @PresentScore BIGINT		--�ݷ�����
	DECLARE @ManagerGrantScore BIGINT	--����Ա��̨�ֶ�����
	SELECT  @RegGrantScore=SUM(GrantScore) FROM QPAccountsDB.dbo.SystemGrantCount(NOLOCK)
	SELECT  @PresentScore=ISNULL(SUM(PresentScore),0) FROM QPTreasureDB.dbo.StreamPlayPresent(NOLOCK)
	SELECT @ManagerGrantScore=ISNULL(SUM(CONVERT(BIGINT,AddGold)),0) FROM QPRecordDB.dbo.RecordGrantTreasure(NOLOCK)
	
	--����ͳ��
	DECLARE @LoveLiness BIGINT		--��������
	DECLARE @Present BIGINT		--�Ѷһ���������
	DECLARE @ConvertPresent BIGINT --�Ѷһ������
	SELECT  @LoveLiness=SUM(CONVERT(BIGINT,LoveLiness)),@Present=SUM(CONVERT(BIGINT,Present)) FROM QPAccountsDB.dbo.AccountsInfo(NOLOCK)
	SELECT  @ConvertPresent=SUM(CONVERT(BIGINT,ConvertPresent)*ConvertRate) FROM QPRecordDB.dbo.RecordConvertPresent(NOLOCK)

	--˰��ͳ��
	DECLARE @Revenue BIGINT			--˰������
	DECLARE @TransferRevenue BIGINT	--ת��˰��
	SELECT @Revenue=SUM(Revenue) FROM QPTreasureDB.dbo.GameScoreInfo(NOLOCK)
	SELECT @TransferRevenue=SUM(Revenue) FROM QPTreasureDB.dbo.RecordInsure(NOLOCK)
/*
	--��Ϸ˰�գ�
	SELECT KindID,SUM(Revenue) FROM RecordUserInout(NOLOCK) GROUP BY KindID
	--����˰��
	SELECT ServerID,SUM(Revenue) FROM RecordUserInout(NOLOCK) GROUP BY ServerID
*/
	--���ͳ��
	DECLARE @Waste FLOAT   --�������
	SELECT @Waste=SUM(Waste) FROM QPTreasureDB.dbo.RecordDrawInfo(NOLOCK)
	--SELECT * FROM QPTreasureDB.dbo.RecordDrawInfo(NOLOCK)
	/*--��Ϸ���
	SELECT KindID,SUM(Waste) FROM RecordDrawInfo(NOLOCK) GROUP BY KindID
	--�������
	SELECT ServerID,SUM(Waste) FROM RecordDrawInfo(NOLOCK) GROUP BY ServerID
*/
	--�㿨ͳ��
	DECLARE @CardCount INT			--��������
	DECLARE @CardGold BIGINT			--�������
	DECLARE @CardPrice DECIMAL(18,2)--�������
	SELECT  @CardCount=COUNT(CardID),@CardGold=SUM(CONVERT(BIGINT,CardGold)),@CardPrice=SUM(CardPrice) FROM QPTreasureDB.dbo.LivcardAssociator(NOLOCK)

	DECLARE @CardPayCount INT 		--��ֵ����
	DECLARE @CardPayGold BIGINT		--��ֵ���
	DECLARE @CardPayPrice DECIMAL(18,2)--��ֵ���������
	SELECT @CardPayCount=COUNT(CardID),@CardPayGold=SUM(CardGold),@CardPayPrice=SUM(CardPrice) FROM QPTreasureDB.dbo.LivcardAssociator(NOLOCK) WHERE ApplyDate IS NOT NULL 

	DECLARE @MemberCardCount INT	--��Ա������
	SELECT @MemberCardCount=COUNT(CardID) FROM QPTreasureDB.dbo.LivcardAssociator(NOLOCK) WHERE MemberOrder<>0

	--����
	SELECT  @OnLineCount AS	OnLineCount,				--��������
			@DisenableCount AS DisenableCount,			--ͣȨ�û�
			@AllCount AS AllCount,						--ע��������
			@Score AS Score,							--�������
			@InsureScore AS InsureScore,				--��������
			@AllScore AS AllScore,
			@RegGrantScore AS RegGrantScore,			--ע������
			@PresentScore AS PresentScore,				--�ݷ�����
			@ManagerGrantScore AS ManagerGrantScore,	--����Ա��̨�ֶ�����
			@LoveLiness AS LoveLiness,					--��������
			@Present AS Present,						--�Ѷһ���������
			(@LoveLiness-@Present) AS RemainLove,		--δ�һ���������
			@ConvertPresent AS ConvertPresent,			--�Ѷһ������
			@Revenue AS Revenue,						--˰������
			@TransferRevenue AS TransferRevenue,		--ת��˰��	
			@Waste AS Waste,							--�������
	
			@CardCount AS CardCount,					--��������
			@CardGold AS CardGold,						--�������
			@CardPrice AS CardPrice,					--�������
			@CardPayCount AS CardPayCount, 				--��ֵ����
			@CardPayGold AS CardPayGold,				--��ֵ���
			@CardPayPrice AS CardPayPrice,				--��ֵ���������
			@MemberCardCount AS MemberCardCount			--��Ա������
END































