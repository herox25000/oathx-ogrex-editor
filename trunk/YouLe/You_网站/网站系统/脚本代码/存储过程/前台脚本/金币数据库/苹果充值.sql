----------------------------------------------------------------------
-- ��Ȩ��2011
-- ʱ�䣺2011-09-1
-- ��;�����߳�ֵ
----------------------------------------------------------------------

USE [QPTreasureDB]
GO

-- ���߳�ֵ
IF EXISTS (SELECT * FROM DBO.SYSOBJECTS WHERE ID = OBJECT_ID(N'[dbo].NET_PW_FilledApp') and OBJECTPROPERTY(ID, N'IsProcedure') = 1)
DROP PROCEDURE [dbo].NET_PW_FilledApp
GO

SET QUOTED_IDENTIFIER ON 
GO
SET ANSI_NULLS ON 
GO

---------------------------------------------------------------------------------------
-- ���߳�ֵ
CREATE PROCEDURE NET_PW_FilledApp
	@dwUserID			INT,					-- �û���ʶ
	@strOrdersID		NVARCHAR(50),			-- �������
	@PayAmount			DECIMAL(18,2),			-- ������
	@dwShareID			INT,					-- �����ʶ
	@strErrorDescribe	NVARCHAR(127) OUTPUT	-- �����Ϣ
WITH ENCRYPTION AS

-- ��������
SET NOCOUNT ON

-- ������Ϣ
DECLARE @UserID INT
DECLARE @Accounts NVARCHAR(31)
DECLARE @GameID INT
DECLARE @Nullity TINYINT

-- �����Ϣ
DECLARE @Score BIGINT

-- ִ���߼�
BEGIN	
	-- �����ظ�
	IF EXISTS(SELECT OrderID FROM ShareDetailInfo(NOLOCK) WHERE OrderID=@strOrdersID) 
	BEGIN
		SET @strErrorDescribe=N'��Ǹ����ֵ�����ظ���'
		RETURN 1
	END

	-- ��֤�û�
	SELECT @UserID=UserID,@GameID=GameID,@Accounts=Accounts,@Nullity=Nullity
	FROM QPAccountsDBLink.QPAccountsDB.dbo.AccountsInfo
	WHERE UserID=@dwUserID

	IF @UserID IS NULL
	BEGIN
		SET @strErrorDescribe=N'��Ǹ����Ҫ��ֵ���û��˺Ų����ڡ�'
		RETURN 2
	END

	IF @Nullity=1
	BEGIN
		SET @strErrorDescribe=N'��Ǹ����Ҫ��ֵ���û��˺���ʱ���ڶ���״̬������ϵ�ͻ����������˽���ϸ�����'
		RETURN 3
	END	

	-- ��Ҳ�ѯ
	SELECT @Score=Score FROM GameScoreInfo WHERE UserID=@UserID

	-- ������
	DECLARE @PresentScore BIGINT 
	SET @PresentScore = @PayAmount*10000

	-- ������¼
	INSERT INTO ShareDetailInfo(
		OperUserID,ShareID,UserID,GameID,Accounts,OrderID,CardTypeID,CardPrice,CardGold,BeforeGold,
		CardTotal,OrderAmount,DiscountScale,PayAmount,IPAddress)
	VALUES(
		@UserID,@dwShareID,@UserID,@GameID,@Accounts,@strOrdersID,0,@PayAmount,@PresentScore,@Score,
		1,@PayAmount,0,@PayAmount,'0.0.0.0')

	-- ��ֵ���
	UPDATE GameScoreInfo SET Score=Score+@PresentScore WHERE UserID=@UserID
	IF @@ROWCOUNT=0	
	BEGIN
		INSERT GameScoreInfo(UserID,Score,RegisterIP,LastLogonIP)
		VALUES (@UserID,@PresentScore,'0.0.0.0','0.0.0.0')
	END

	-- ��¼��־
	DECLARE @DateID INT
	SET @DateID=CAST(CAST(GETDATE() AS FLOAT) AS INT)

	UPDATE StreamShareInfo
	SET ShareTotals=ShareTotals+1
	WHERE DateID=@DateID AND ShareID=@dwShareID

	IF @@ROWCOUNT=0
	BEGIN
		INSERT StreamShareInfo(DateID,ShareID,ShareTotals)
		VALUES (@DateID,@dwShareID,1)
	END	 
	
END 
RETURN 0
GO



