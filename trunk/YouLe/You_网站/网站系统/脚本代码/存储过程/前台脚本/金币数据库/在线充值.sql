----------------------------------------------------------------------
-- ��Ȩ��2011
-- ʱ�䣺2011-09-1
-- ��;�����߳�ֵ
----------------------------------------------------------------------

USE [QPTreasureDB]
GO

-- ���߳�ֵ
IF EXISTS (SELECT * FROM DBO.SYSOBJECTS WHERE ID = OBJECT_ID(N'[dbo].NET_PW_FilledOnLine') and OBJECTPROPERTY(ID, N'IsProcedure') = 1)
DROP PROCEDURE [dbo].NET_PW_FilledOnLine
GO

SET QUOTED_IDENTIFIER ON 
GO
SET ANSI_NULLS ON 
GO

---------------------------------------------------------------------------------------
-- ���߳�ֵ
CREATE PROCEDURE NET_PW_FilledOnLine
	@strOrdersID		NVARCHAR(50),			--	�������
	@strOrderAmount		decimal,				--  ʵ��֧�����
	@isVB				INT,					--	�Ƿ�绰��ֵ
	@strIPAddress		NVARCHAR(31),			--	�û��ʺ�	
	@strErrorDescribe	NVARCHAR(127) OUTPUT	--	�����Ϣ
WITH ENCRYPTION AS

-- ��������
SET NOCOUNT ON

-- ������Ϣ
DECLARE @OperUserID INT
DECLARE @ShareID INT
DECLARE @UserID INT
DECLARE @GameID INT
DECLARE @Accounts NVARCHAR(31)
DECLARE @OrderID NVARCHAR(32)
DECLARE @CardTypeID INT
DECLARE @CardPrice DECIMAL(18,2)
DECLARE @CardTotal INT
DECLARE @OrderAmount DECIMAL(18,2)
DECLARE @DiscountScale DECIMAL(18,2)
DECLARE @PayAmount DECIMAL(18,2)
DECLARE @IPAddress NVARCHAR(15)

-- ʵ����Ϣ
DECLARE @CardGold BIGINT

-- ��Ա����Ϣ
DECLARE @MemberOrder TINYINT
DECLARE @MemberDays INT
DECLARE @UserRight INT

-- ��Ա����
DECLARE @MaxMemberOrder INT
DECLARE @MaxUserRight INT
DECLARE @MemberOverDate DATETIME
DECLARE @MemberSwitchDate DATETIME

-- �����Ϣ
DECLARE @Score BIGINT

-- ִ���߼�
BEGIN
	-- ������ѯ
	SELECT @OperUserID=OperUserID,@ShareID=ShareID,@UserID=UserID,@GameID=GameID,@Accounts=Accounts,
		@OrderID=OrderID,@CardTypeID=CardTypeID,@CardPrice=CardPrice,@CardTotal=CardTotal,
		@OrderAmount=OrderAmount,@DiscountScale=DiscountScale,@PayAmount=PayAmount
	FROM OnLineOrder WHERE OrderID=@strOrdersID
	
	if @strOrderAmount<>@OrderAmount
	BEGIN
		SET @strErrorDescribe=N'�Ƿ��������ύ��֧�������ʵ��֧������'
		RETURN 1
	END	

	-- ��������
	IF @OrderID IS NULL 
	BEGIN
		SET @strErrorDescribe=N'��Ǹ����ֵ���������ڡ�'
		RETURN 1
	END

	-- �����ظ�
	IF EXISTS(SELECT OrderID FROM ShareDetailInfo(NOLOCK) WHERE OrderID=@strOrdersID) 
	BEGIN
		SET @strErrorDescribe=N'��Ǹ����ֵ�����ظ���'
		RETURN 2
	END
	
	-- ʵ����ѯ
	SELECT @CardGold=CardGold FROM GlobalLivcard WHERE CardTypeID=@CardTypeID

	-- ��Ҳ�ѯ
	SET @Score=0
	SELECT @Score=Score FROM GameScoreInfo WHERE UserID=@UserID

	-- ��Ա����ѯ
	SELECT @MemberOrder=MemberOrder,@MemberDays=MemberDays,@UserRight=UserRight
	FROM GlobalLivcard WHERE CardTypeID=@CardTypeID

	SET @MemberDays = @MemberDays * @OrderAmount / @CardPrice

	--------------------------- Ϊ�û��󶨻�Ա����Ϣ -------------------------------
	-- ɾ������
	DELETE FROM QPAccountsDBLink.QPAccountsDB.dbo.AccountsMember
	WHERE UserID=@UserID AND MemberOrder=@MemberOrder AND MemberOverDate<=GETDATE()

	-- ���»�Ա
	UPDATE QPAccountsDBLink.QPAccountsDB.dbo.AccountsMember SET MemberOverDate=MemberOverDate+@MemberDays
	WHERE UserID=@UserID AND MemberOrder=@MemberOrder

	IF @@ROWCOUNT=0
	BEGIN
		INSERT QPAccountsDBLink.QPAccountsDB.dbo.AccountsMember(UserID,MemberOrder,UserRight,MemberOverDate)
		VALUES (@UserID,@MemberOrder,@UserRight,GETDATE()+@MemberDays)
	END

	-- �󶨻�Ա,(��Ա�������л�ʱ��)
	SELECT @MaxMemberOrder=MAX(MemberOrder),@MemberOverDate=MAX(MemberOverDate),@MemberSwitchDate=MIN(MemberOverDate)
	FROM QPAccountsDBLink.QPAccountsDB.dbo.AccountsMember WHERE UserID=@UserID

	-- ��ԱȨ��
	SELECT @MaxUserRight=UserRight FROM QPAccountsDBLink.QPAccountsDB.dbo.AccountsMember
	WHERE UserID=@UserID AND MemberOrder=@MaxMemberOrder
	
	-- ���ӻ�Ա����Ϣ
	UPDATE QPAccountsDBLink.QPAccountsDB.dbo.AccountsInfo
	SET MemberOrder=@MaxMemberOrder,UserRight=@MaxUserRight,MemberOverDate=@MemberOverDate,MemberSwitchDate=@MemberSwitchDate
	WHERE UserID=@UserID

	-- ��ֵ���	
	SET @CardGold = @CardGold*@OrderAmount/@CardPrice

	IF @isVB = 1
	BEGIN
		SET @CardGold = @CardGold/2
	END

	UPDATE GameScoreInfo SET Score=Score+@CardGold WHERE UserID=@UserID
	IF @@ROWCOUNT=0	
	BEGIN
		INSERT GameScoreInfo(UserID,Score,RegisterIP,LastLogonIP)
		VALUES (@UserID,@CardGold,@strIPAddress,@strIPAddress)
	END

	-- ������¼
	INSERT INTO ShareDetailInfo(
		OperUserID,ShareID,UserID,GameID,Accounts,OrderID,CardTypeID,CardPrice,CardGold,BeforeGold,
		CardTotal,OrderAmount,DiscountScale,PayAmount,IPAddress)
	VALUES(
		@OperUserID,@ShareID,@UserID,@GameID,@Accounts,@OrderID,@CardTypeID,@CardPrice,@CardGold,@Score,
		@CardTotal,@OrderAmount,@DiscountScale,@PayAmount,@strIPAddress)
	--------------------------------------------------------------------------------

	-- �ƹ�ϵͳ
	DECLARE @SpreaderID INT	
	SELECT @UserID=UserID,@Accounts=Accounts,@SpreaderID=SpreaderID FROM QPAccountsDBLink.QPAccountsDB.dbo.AccountsInfo
	WHERE UserID = @UserID
	IF @SpreaderID<>0
	BEGIN
		DECLARE @Rate DECIMAL(18,2)
		DECLARE @GrantScore BIGINT
		DECLARE @Note NVARCHAR(512)
		SELECT @Rate=FillGrantRate FROM GlobalSpreadInfo
		IF @Rate IS NULL
		BEGIN
			SET @Rate=0.1
		END
		SET @GrantScore = @CardGold*@Rate
		SET @Note = N'��ֵ'+LTRIM(STR(@CardPrice))+'Ԫ'
		INSERT INTO RecordSpreadInfo(
			UserID,Score,TypeID,ChildrenID,CollectNote)
		VALUES(@SpreaderID,@GrantScore,3,@UserID,@Note)		
	END

	-- ���¶���״̬
	UPDATE OnLineOrder SET OrderStatus=2 WHERE OrderID=@OrderID

	-- ��¼��־
	DECLARE @DateID INT
	SET @DateID=CAST(CAST(GETDATE() AS FLOAT) AS INT)

	UPDATE StreamShareInfo
	SET ShareTotals=ShareTotals+1
	WHERE DateID=@DateID AND ShareID=@ShareID

	IF @@ROWCOUNT=0
	BEGIN
		INSERT StreamShareInfo(DateID,ShareID,ShareTotals)
		VALUES (@DateID,@ShareID,1)
	END	 
	
END 
RETURN 0
GO



