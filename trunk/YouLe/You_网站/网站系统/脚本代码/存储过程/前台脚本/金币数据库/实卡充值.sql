----------------------------------------------------------------------
-- ��Ȩ��2011
-- ʱ�䣺2011-09-1
-- ��;��ʵ����ֵ
----------------------------------------------------------------------

USE [QPTreasureDB]
GO

IF EXISTS (SELECT * FROM DBO.SYSOBJECTS WHERE ID = OBJECT_ID(N'[dbo].NET_PW_FilledLivcard') AND OBJECTPROPERTY(ID, N'IsProcedure') = 1)
DROP PROCEDURE [dbo].NET_PW_FilledLivcard
GO

SET QUOTED_IDENTIFIER ON 
GO
SET ANSI_NULLS ON 
GO

----------------------------------------------------------------------------------
-- ʵ����ֵ
CREATE PROC NET_PW_FilledLivcard
	@dwOperUserID		INT,						--	�����û�

	@strSerialID		NVARCHAR(32),				--	��Ա����
	@strPassword		NCHAR(32),					--	��Ա����	
	@strAccounts		NVARCHAR(31),				--	��ֵ����ʺ�

	@strClientIP		NVARCHAR(15),				--	��ֵ��ַ
	@strErrorDescribe	NVARCHAR(127) OUTPUT		--	�����Ϣ
WITH ENCRYPTION AS

-- ��������
SET NOCOUNT ON

-- ʵ����Ϣ
DECLARE @CardID INT
DECLARE @SerialID NVARCHAR(15)
DECLARE @Password NCHAR(32)
DECLARE @CardTypeID INT
DECLARE @CardPrice DECIMAL(18,2)
DECLARE @CardGold INT
DECLARE @MemberOrder TINYINT
DECLARE @MemberDays INT
DECLARE @UserRight INT
DECLARE @ValidDate DATETIME
DECLARE @ApplyDate DATETIME
DECLARE @UseRange INT

-- �ʺ�����
DECLARE @Accounts NVARCHAR(31)
DECLARE @GameID INT
DECLARE @UserID INT
DECLARE @SpreaderID INT
DECLARE @Nullity TINYINT
DECLARE @StunDown TINYINT
DECLARE @WebLogonTimes INT
DECLARE @GameLogonTimes INT

-- ��Ա����
DECLARE @MaxMemberOrder INT
DECLARE @MaxUserRight INT
DECLARE @MemberOverDate DATETIME
DECLARE @MemberSwitchDate DATETIME

-- ִ���߼�
BEGIN
	DECLARE @ShareID INT
	SET @ShareID=1		-- 1 ʵ��
	
	-- ���Ų�ѯ
	SELECT	@CardID=CardID,@SerialID=SerialID,@Password=[Password],@CardTypeID=CardTypeID,
			@CardPrice=CardPrice,@CardGold=CardGold,@MemberOrder=MemberOrder,@MemberDays=MemberDays,
			@UserRight=UserRight,@ValidDate=ValidDate,@ApplyDate=ApplyDate,@UseRange=UseRange,@Nullity=Nullity
	FROM LivcardAssociator WHERE SerialID = @strSerialID

	-- ��֤����Ϣ
	IF @CardID IS NULL
	BEGIN
		SET @strErrorDescribe=N'��Ǹ����Ҫ��ֵ�Ŀ��Ų����ڡ�������������ϵ�ͷ����ġ�'
		RETURN 101
	END	

	IF @strPassword=N'' OR @strPassword IS NULL OR @Password<>@strPassword
	BEGIN
		SET @strErrorDescribe=N'��Ǹ����ֵʧ�ܣ����鿨�Ż������Ƿ���д��ȷ��������������ϵ�ͷ����ġ�'
		RETURN 102
	END

	IF @ApplyDate IS NOT NULL
	BEGIN
		SET @strErrorDescribe=N'��Ǹ���ó�ֵ���ѱ�ʹ�ã��뻻һ�����ԡ�������������ϵ�ͷ����ġ�'
		RETURN 103
	END

	IF @Nullity=1
	BEGIN
		SET @strErrorDescribe=N'��Ǹ���û�Ա���ѱ����á�'
		RETURN 104
	END

	IF @ValidDate < GETDATE()
	BEGIN
		SET @strErrorDescribe=N'��Ǹ���û�Ա���Ѿ����ڡ�'
		RETURN 105
	END
	
	-- ��֤�û�
	SELECT @UserID=UserID,@GameID=GameID,@Accounts=Accounts,@Nullity=Nullity,@StunDown=StunDown,@SpreaderID=SpreaderID,
		   @WebLogonTimes=WebLogonTimes,@GameLogonTimes=GameLogonTimes
	FROM QPAccountsDBLink.QPAccountsDB.dbo.AccountsInfo
	WHERE Accounts=@strAccounts

	IF @UserID IS NULL
	BEGIN
		SET @strErrorDescribe=N'��Ǹ����Ҫ��ֵ���û��˺Ų����ڡ�'
		RETURN 201
	END

	IF @Nullity=1
	BEGIN
		SET @strErrorDescribe=N'��Ǹ����Ҫ��ֵ���û��˺���ʱ���ڶ���״̬������ϵ�ͻ����������˽���ϸ�����'
		RETURN 202
	END

	IF @StunDown<>0
	BEGIN
		SET @strErrorDescribe=N'��Ǹ����Ҫ��ֵ���û��˺�ʹ���˰�ȫ�رչ��ܣ��������¿�ͨ����ܼ���ʹ�á�'
		RETURN 203
	END

	-- ʵ��ʹ�÷�Χ
	-- ��ע���û�
	IF @UseRange = 1
	BEGIN
		IF @WebLogonTimes+@GameLogonTimes>1
		BEGIN
			SET @strErrorDescribe=N'��Ǹ���û�Ա��ֻ�ʺ���ע����û�ʹ�á�'
			RETURN 301
		END 
	END
	-- ��һ�γ�ֵ�û�
	IF @UseRange = 2
	BEGIN
		DECLARE @FILLCOUNT INT
		SELECT @FillCount=COUNT(USERID) FROM ShareDetailInfo WHERE UserID=@UserID
		IF @FillCount>0
		BEGIN
			SET @strErrorDescribe=N'��Ǹ���û�Ա��ֻ�ʺϵ�һ�γ�ֵ���û�ʹ�á�'
			RETURN 302
		END
	END

	-- ��������
	IF EXISTS (SELECT UserID FROM GameScoreLocker(NOLOCK) WHERE UserID=@UserID)
	BEGIN
		SET @strErrorDescribe='��Ǹ�����Ѿ��ڽ����Ϸ�����ˣ����ܽ��г�ֵ�����������˳������Ϸ���䣡'	
		RETURN 401
	END	

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
	DECLARE @CurScore BIGINT
	SELECT @CurScore=Score FROM GameScoreInfo WHERE UserID=@UserID
	IF @CurScore IS NULL
	BEGIN
		SET @CurScore=0
		INSERT GameScoreInfo(UserID,Score,RegisterIP,LastLogonIP)
		VALUES (@UserID,@CardGold,@strClientIP,@strClientIP)
	END
	ELSE
	BEGIN
		UPDATE GameScoreInfo SET Score=Score+@CardGold WHERE UserID=@UserID
	END
	--------------------------------------------------------------------------------

	-- �ƹ�ϵͳ
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

	-- ���ÿ���ʹ��
	UPDATE LivcardAssociator SET ApplyDate=GETDATE() WHERE CardID=@CardID

	-- д����ֵ��¼
	INSERT INTO ShareDetailInfo(
		OperUserID,ShareID,UserID,GameID,Accounts,SerialID,CardTypeID,CardPrice,CardGold,BeforeGold,CardTotal,PayAmount,IPAddress,ApplyDate)
	VALUES(@dwOperUserID,@ShareID,@UserID,@GameID,@Accounts,@SerialID,@CardTypeID,@CardPrice,@CardGold,@CurScore,1,@CardPrice,@strClientIP,GETDATE())

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

	SET @strErrorDescribe=N'ʵ����ֵ�ɹ���'
END 

RETURN 0
GO



