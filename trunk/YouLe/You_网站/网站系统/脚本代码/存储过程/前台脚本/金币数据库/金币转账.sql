----------------------------------------------------------------------
-- ��Ȩ��2011
-- ʱ�䣺2011-09-1
-- ��;�����ת��
----------------------------------------------------------------------

USE [QPTreasureDB]
GO

IF EXISTS (SELECT * FROM DBO.SYSOBJECTS WHERE ID = OBJECT_ID(N'[dbo].NET_PW_InsureTransfer') AND OBJECTPROPERTY(ID, N'IsProcedure') = 1)
DROP PROCEDURE [dbo].NET_PW_InsureTransfer
GO

SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO

--------------------------------------------------------------------------------
-- ���
CREATE PROCEDURE NET_PW_InsureTransfer
	@dwSrcUserID		INT,						-- Դ�û���ʶ

	@dwDstUserID		INT,						-- Ŀ���û���ʶ
	@strInsurePass		NVARCHAR(32),				-- ��������
	@dwSwapScore		BIGINT,						-- ת�˽��
	@dwMinSwapScore		BIGINT,						-- ��Сת����Ŀ

	@strClientIP		NVARCHAR(15),				-- ������ַ
	@strCollectNote		NVARCHAR(63),				-- ��ע
	@strErrorDescribe	NVARCHAR(127) OUTPUT		-- �����Ϣ
WITH ENCRYPTION AS

-- ��������
SET NOCOUNT ON

-- ����û�
DECLARE @SrcUserID			INT
DECLARE @SrcInsurePass		NCHAR(32)
DECLARE @SrcNullity			TINYINT
DECLARE @SrcStunDown		TINYINT

-- �տ��û�
DECLARE @DstUserID			INT
DECLARE @DstNullity			TINYINT
DECLARE @DstStunDown		TINYINT

-- ����û������Ϣ
DECLARE @SrcScore			BIGINT		-- ������ֽ�		
DECLARE @SrcInsureScore		BIGINT		-- ���������
DECLARE @SrcInsureBalance	BIGINT		-- ��������	

-- �տ��û������Ϣ
DECLARE @DstScore			BIGINT		-- �տ����ֽ�			
DECLARE @DstInsureScore		BIGINT		-- �տ�������
DECLARE @DstInsureBalance	BIGINT		-- �տ������

-- ˰��
DECLARE @Revenue BIGINT
DECLARE @InsureRevenue BIGINT
DECLARE @MaxTax BIGINT

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

	-- �ж��Ƿ��Լ�ת���Լ�
	IF @dwSrcUserID = @dwDstUserID
	BEGIN
		SET @strErrorDescribe=N'��Ǹ��֪ͨ����ͬһ�ʺŲ�����������ͽ�ҡ�'
		RETURN 1
	END
	
	--------------------------------------------------------------------------------
	/* ����˲��� */

	-- ��ѯ�û�	
	SELECT @SrcUserID=UserID,@SrcNullity=Nullity, @SrcStunDown=StunDown,@SrcInsurePass=InsurePass	
	FROM QPAccountsDBLink.QPAccountsDB.dbo.AccountsInfo WHERE UserID=@dwSrcUserID

	-- ��֤�û�
	IF @SrcUserID IS NULL
	BEGIN
		SET @strErrorDescribe=N'�����ʺŲ����ڻ������������������֤���ٴγ��Ե�¼��'
		RETURN 101
	END

	-- �ʺŷ�ͣ
	IF @SrcNullity<>0
	BEGIN
		SET @strErrorDescribe=N'�����ʺ���ʱ���ڶ���״̬������ϵ�ͻ����������˽���ϸ�����'
		RETURN 102
	END	

	-- �ʺŹر�
	IF @SrcStunDown<>0
	BEGIN
		SET @strErrorDescribe=N'�����ʺ�ʹ���˰�ȫ�رչ��ܣ��������¿�ͨ����ܼ���ʹ�ã�'
		RETURN 103
	END

	-- ��������
	IF @SrcInsurePass <> @strInsurePass 
	BEGIN
		SET @strErrorDescribe=N'�����������������������֤���ٴγ��ԣ�'	
		RETURN 104
	END	
	--------------------------------------------------------------------------------
	
	--------------------------------------------------------------------------------
	/* �տ��˲��� */

	-- ��ѯ�û�	
	SELECT @DstUserID=UserID,@DstNullity=Nullity,@DstStunDown=StunDown
	FROM QPAccountsDBLink.QPAccountsDB.dbo.AccountsInfo WHERE UserID=@dwDstUserID

	-- ��֤�û�
	IF @DstUserID IS NULL
	BEGIN
		SET @strErrorDescribe=N'��Ǹ����Ҫ���͵�Ŀ���ʺŲ����ڣ�'
		RETURN 201
	END

	-- �ʺŷ�ͣ
	IF @DstNullity<>0
	BEGIN
		SET @strErrorDescribe=N'��Ǹ�������͵�Ŀ���ʺ���ʱ���ڶ���״̬���޷����н�����ͣ�'
		RETURN 202
	END	

	-- �ʺŹر�
	IF @DstStunDown<>0
	BEGIN
		SET @strErrorDescribe=N'��Ǹ�������͵�Ŀ���ʺ�ʹ���˰�ȫ�رչ��ܣ��޷����н�����ͣ�'
		RETURN 203
	END
	--------------------------------------------------------------------------------

	-- ��������
	IF EXISTS (SELECT UserID FROM GameScoreLocker(NOLOCK) WHERE UserID=@dwSrcUserID)
	BEGIN
		SET @strErrorDescribe='���Ѿ��ڽ����Ϸ�����ˣ���Ҫ����ת�˲����������˳������Ϸ���䣡'		
		RETURN 2
	END	
	
	-- ��Сת�˽��	
	IF @dwSwapScore < @dwMinSwapScore
	BEGIN
		SET @strErrorDescribe=N'�ǳ���Ǹ,��ÿ�ʱ��ܵ���Ŀ�������' + Convert(NVARCHAR(30), @dwMinSwapScore) + '��ң�'
		RETURN 3
	END
	
	--------------------------------------------------------------------------------
	/* ����˲��� */

	-- ��Ҳ�ѯ
	SELECT @SrcScore= Score, @SrcInsureScore=InsureScore
	FROM GameScoreInfo WHERE UserID=@dwSrcUserID
	
	-- ����ж�
	IF @SrcInsureScore IS NULL OR @SrcInsureScore<0
	BEGIN
		SET @strErrorDescribe=N'�ǳ���Ǹ,�����еı�������!'
		RETURN 4
	END
	
	-- ת������
	DECLARE @TransferPrerequisite INT; SET @TransferPrerequisite = 0
	SELECT @TransferPrerequisite=ISNULL(StatusValue,0) FROM QPAccountsDBLink.QPAccountsDB.dbo.SystemStatusInfo WHERE StatusName=N'TransferPrerequisite'
	IF @SrcInsureScore <= @TransferPrerequisite
	BEGIN
		SET @strErrorDescribe=N'�ǳ���Ǹ,�������н�����������'+LTRIM(@TransferPrerequisite)+'�ſ�ת��'
		RETURN 5
	END
	
	-- ���б���
	DECLARE @TransferRetention INT	-- ���ٱ���
	DECLARE @SurplusScore BIGINT	-- ת������
	SELECT @TransferRetention=ISNULL(StatusValue,0) FROM QPAccountsDBLink.QPAccountsDB.dbo.SystemStatusInfo WHERE StatusName=N'TransferRetention'
	IF @TransferRetention<>0
	BEGIN
		SET @SurplusScore=@SrcInsureScore-@dwSwapScore
		IF @SurplusScore<@TransferRetention
		BEGIN
			SET @strErrorDescribe=N'�ǳ���Ǹ,ת�˺������е���������'+LTRIM(@TransferRetention)+'���'
			RETURN 7
		END
	END
	
	-- ת��˰��
	DECLARE @RevenueRate INT
	SELECT @RevenueRate=StatusValue FROM QPAccountsDBLink.QPAccountsDB.dbo.SystemStatusInfo WHERE StatusName=N'RevenueRateTransfer'

	-- ˰�յ���
	IF @RevenueRate>300 SET @RevenueRate=300
	IF @RevenueRate IS NULL SET @RevenueRate=1	

	-- ����ж�
	IF @dwSwapScore > @SrcInsureScore
	BEGIN
		SET @strErrorDescribe=N'�ǳ���Ǹ,�����еı�������!'
		RETURN 6
	END
	
	-- ������
	SET @Revenue=@dwSwapScore*@RevenueRate/1000

	-- ˰�շⶥ
	SELECT @MaxTax=StatusValue FROM QPAccountsDBLink.QPAccountsDB.dbo.SystemStatusInfo WHERE StatusName=N'TransferMaxTax'
	IF @MaxTax<>0
	BEGIN
		IF @Revenue > @MaxTax
			SET @Revenue=@MaxTax
	END

	SET @SrcInsureBalance = @SrcInsureScore - @dwSwapScore
	--------------------------------------------------------------------------------
	
	--------------------------------------------------------------------------------
	/* �տ��˲��� */
	
	-- ��Ҳ�ѯ
	SELECT @DstScore= Score, @DstInsureScore=InsureScore
	FROM GameScoreInfo WHERE UserID=@dwDstUserID

	-- ��֤�û�
	IF @DstScore IS NULL OR @DstInsureScore IS NULL
	BEGIN
		-- ��ʼ�û�
		SET @DstScore = 0
		SET @DstInsureScore = 0

		INSERT INTO GameScoreInfo(UserID,LastLogonIP,RegisterIP)
		VALUES(@dwDstUserID,@strClientIP,@strClientIP)
	END

	-- ������
	SET @DstInsureBalance = @DstInsureScore + @dwSwapScore - @Revenue
	--------------------------------------------------------------------------------

	-- ת�˼�¼
	INSERT INTO RecordInsure(
		SourceUserID,SourceGold,SourceBank,TargetUserID,TargetGold,TargetBank,SwapScore,Revenue,IsGamePlaza,TradeType,ClientIP,CollectNote)
	VALUES(@SrcUserID,@SrcScore,@SrcInsureScore,@DstUserID,@DstScore,@DstInsureScore,@dwSwapScore,@Revenue,1,3,@strClientIP,@strCollectNote)

	-- ת�˲���
	-- �տ��û�
	UPDATE GameScoreInfo SET InsureScore=@DstInsureBalance
	WHERE UserID=@dwDstUserID

	-- ����û�	
	UPDATE GameScoreInfo SET InsureScore=@SrcInsureBalance,Revenue=Revenue+@Revenue
	WHERE UserID=@dwSrcUserID

	SET @strErrorDescribe=N'ת�˳ɹ�!'
	
END

SET NOCOUNT OFF

RETURN 0
GO



