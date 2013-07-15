----------------------------------------------------------------------
-- ��Ȩ��2011
-- ʱ�䣺2011-09-1
-- ��;�����ȡ��
----------------------------------------------------------------------

USE [QPTreasureDB]
GO

IF EXISTS (SELECT * FROM DBO.SYSOBJECTS WHERE ID = OBJECT_ID(N'[dbo].NET_PW_InsureOut') AND OBJECTPROPERTY(ID, N'IsProcedure') = 1)
DROP PROCEDURE [dbo].NET_PW_InsureOut
GO

SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO

--------------------------------------------------------------------------------
-- ȡ��
CREATE PROCEDURE NET_PW_InsureOut
	@dwUserID			INT,						-- �û���ʶ
	
	@strInsurePass 		NCHAR(32),					-- ��������
	@dwSwapScore		BIGINT,						-- �����
	@dwMinSwapScore		BIGINT,						-- ��Сת����Ŀ

	@strClientIP		NVARCHAR(15),				-- ������ַ
	@strCollectNote		NVARCHAR(63),				-- ��ע
	@strErrorDescribe	NVARCHAR(127) OUTPUT		-- �����Ϣ
WITH ENCRYPTION AS

-- ��������
SET NOCOUNT ON

-- ������Ϣ
DECLARE @UserID			INT
DECLARE @ProtectID		INT
DECLARE @Nullity		TINYINT
DECLARE @StunDown		TINYINT
DECLARE @InsurePass		NVARCHAR(32)

-- �����Ϣ	
DECLARE @Score BIGINT			
DECLARE @InsureScore BIGINT

-- ������
DECLARE @ScoreBalance	BIGINT
DECLARE @InsureBalance	BIGINT

-- ����˰��
DECLARE @InsureRevenue BIGINT
DECLARE @RevenueRate INT

-- ִ���߼�
BEGIN
	DECLARE @EnjoinInsure INT
	-- ϵͳ��ͣ
	SELECT @EnjoinInsure=StatusValue FROM QPAccountsDBLink.QPAccountsDB.dbo.SystemStatusInfo WHERE StatusName=N'EnjoinInsure'
	IF @EnjoinInsure IS NOT NULL AND @EnjoinInsure<>0
	BEGIN
		SELECT @strErrorDescribe=StatusString FROM QPAccountsDBLink.QPAccountsDB.dbo.SystemStatusInfo WHERE StatusName=N'EnjoinInsure'
		RETURN 1
	END

	-- ��ѯ�û�	
	SELECT	@UserID=UserID,@ProtectID=ProtectID, @Nullity=Nullity, @StunDown=StunDown,@InsurePass=InsurePass		
	FROM QPAccountsDBLink.QPAccountsDB.dbo.AccountsInfo WHERE UserID=@dwUserID

	-- ��֤�û�
	IF @UserID IS NULL
	BEGIN
		SET @strErrorDescribe=N'�����ʺŲ����ڻ������������������֤���ٴγ��Ե�¼��'
		RETURN 1
	END

	-- �ʺŷ�ͣ
	IF @Nullity<>0
	BEGIN
		SET @strErrorDescribe=N'�����ʺ���ʱ���ڶ���״̬������ϵ�ͻ����������˽���ϸ�����'
		RETURN 2
	END	

	-- �ʺŹر�
	IF @StunDown<>0
	BEGIN
		SET @strErrorDescribe=N'�����ʺ�ʹ���˰�ȫ�رչ��ܣ��������¿�ͨ����ܼ���ʹ�ã�'
		RETURN 3
	END

	-- ��������
	IF @InsurePass <> @strInsurePass 
	BEGIN
		SET @strErrorDescribe=N'�����������������������֤���ٴγ��ԣ�'	
		RETURN 4
	END	

	-- ��������
	IF EXISTS (SELECT UserID FROM GameScoreLocker(NOLOCK) WHERE UserID=@dwUserID)
	BEGIN
		SET @strErrorDescribe='���Ѿ��ڽ����Ϸ�����ˣ���Ҫ����ȡ������������˳������Ϸ���䣡'	
		RETURN 5
	END	
	
	-- ��Сȡ����	
	IF @dwSwapScore < @dwMinSwapScore
	BEGIN
		SET @strErrorDescribe=N'�ǳ���Ǹ,��ÿ��ȡ������Ŀ�������' + Convert(NVARCHAR(30), @dwMinSwapScore) + '��ң�'
		RETURN 6
	END

	-- ��Ҳ�ѯ
	SELECT @Score= Score, @InsureScore=InsureScore
	FROM GameScoreInfo WHERE UserID=@dwUserID

	-- ���ӽ�Ҹ����ж�
	IF @InsureScore IS NULL OR @InsureScore<0 OR @InsureScore<@dwSwapScore
	BEGIN
		SET @strErrorDescribe=N'�ǳ���Ǹ,�����еı�������!'	
		RETURN 7
	END

	-- ����˰��
	SELECT @RevenueRate=StatusValue FROM QPAccountsDBLink.QPAccountsDB.dbo.SystemStatusInfo WHERE StatusName=N'RevenueRateTake'
	-- ˰�յ���
	IF @RevenueRate>300 SET @RevenueRate=300
	IF @RevenueRate IS NULL SET @RevenueRate=0

	-- ������
	SET @InsureRevenue=@dwSwapScore*@RevenueRate/1000
	SET @ScoreBalance = @Score - @InsureRevenue + @dwSwapScore
	SET @InsureBalance = @InsureScore - @dwSwapScore

	-- ����¼
	INSERT INTO RecordInsure(
		SourceUserID,SourceGold,SourceBank,SwapScore,Revenue,IsGamePlaza,TradeType,ClientIP,CollectNote)
	VALUES(@UserID,@Score,@InsureScore,@dwSwapScore,@InsureRevenue,1,2,@strClientIP,@strCollectNote)

	-- ������
	UPDATE GameScoreInfo SET Score=@ScoreBalance, InsureScore=@InsureBalance
	WHERE UserID=@dwUserID

	SET @strErrorDescribe=N'ȡ��ɹ�!'
	SELECT @ScoreBalance AS Score,@InsureBalance AS InsureScore
	
END

SET NOCOUNT OFF

RETURN 0
GO



