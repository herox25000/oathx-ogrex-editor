----------------------------------------------------------------------
-- ��Ȩ��2011
-- ʱ�䣺2011-09-1
-- ��;���ƹ�����
----------------------------------------------------------------------

USE [QPTreasureDB]
GO

-- ��ȡ�ƹ���Ϣ
IF EXISTS (SELECT * FROM DBO.SYSOBJECTS WHERE ID = OBJECT_ID(N'[dbo].NET_PW_GetUserSpreadInfo') and OBJECTPROPERTY(ID, N'IsProcedure') = 1)
DROP PROCEDURE [dbo].NET_PW_GetUserSpreadInfo
GO

-- �ƹ����
IF EXISTS (SELECT * FROM DBO.SYSOBJECTS WHERE ID = OBJECT_ID(N'[dbo].NET_PW_SpreadBalance') and OBJECTPROPERTY(ID, N'IsProcedure') = 1)
DROP PROCEDURE [dbo].NET_PW_SpreadBalance
GO

SET QUOTED_IDENTIFIER ON
GO

SET ANSI_NULLS ON
GO

----------------------------------------------------------------------------------------------------
-- ��ȡ�û��ƹ���Ϣ
CREATE PROCEDURE NET_PW_GetUserSpreadInfo
	@dwUserID			INT,					-- �û���ʶ
	@strErrorDescribe	NVARCHAR(127) OUTPUT	--�����Ϣ
WITH ENCRYPTION AS

-- ��������
SET NOCOUNT ON

-- ������Ϣ
DECLARE @UserID				INT
DECLARE @GameID				INT
DECLARE @Accounts			NVARCHAR(31)

-- �ʺ�״̬
DECLARE @Nullity BIT
DECLARE @StunDown BIT

-- �Ƹ���Ϣ
DECLARE @Score			BIGINT
DECLARE @InsureScore	BIGINT

-- �ƹ���Ϣ
DECLARE @SpreadIn  BIGINT
DECLARE @SpreadOut BIGINT
DECLARE @SpreadBalance BIGINT

-- ִ���߼�
BEGIN
	-- �û�����
	SELECT	@UserID=UserID,@GameID=GameID,@Accounts=Accounts,@Nullity=Nullity,@StunDown=StunDown
	FROM QPAccountsDBLink.QPAccountsDB.dbo.AccountsInfo
	WHERE UserID=@dwUserID

	-- ��ѯ�û�
	IF @UserID IS NULL
	BEGIN
		SET @strErrorDescribe= N'�����ʺŲ����ڻ������������������֤���ٴγ��Ե�¼��'
		RETURN 1
	END

	-- �ʺŽ�ֹ
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

	-- ������Ϣ
	SELECT @Score=Score,@InsureScore=InsureScore FROM GameScoreInfo(NOLOCK) WHERE UserID = @dwUserID
	IF @Score IS NULL
	BEGIN
		SET @Score=0
		SET @InsureScore=0
	END

	-- �ƹ���Ϣ
	SELECT @SpreadIn = SUM(Score) FROM RecordSpreadInfo WHERE UserID=@dwUserID AND Score>0
	IF @SpreadIn IS NULL
	BEGIN
		SET @SpreadIn=0
	END
	
	SELECT @SpreadOut = -SUM(Score) FROM RecordSpreadInfo WHERE UserID=@dwUserID AND Score<0
	IF @SpreadOut IS NULL
	BEGIN
		SET @SpreadOut=0
	END
	SET @SpreadBalance = @SpreadIn-@SpreadOut
	
	-- �����Ϣ
	SELECT @UserID AS UserID,@SpreadIn AS Score, @SpreadOut AS InsureScore,@SpreadBalance AS RecordID
END
RETURN 0 
GO


----------------------------------------------------------------------------------------------------------------
-- �ƹ����
CREATE PROCEDURE NET_PW_SpreadBalance
	@dwUserID			INT,					-- �û���ʶ

	@dwBalance			INT,					-- ������

	@strClientIP		NVARCHAR(15),			-- ������ַ
	@strErrorDescribe	NVARCHAR(127) OUTPUT	-- �����Ϣ
WITH ENCRYPTION AS

-- ��������
SET NOCOUNT ON

-- ������Ϣ
DECLARE @UserID				INT
DECLARE @GameID				INT
DECLARE @Accounts			NVARCHAR(31)
DECLARE @SpreaderID			INT

-- �ʺ�״̬
DECLARE @Nullity BIT
DECLARE @StunDown BIT

-- �ƹ���Ϣ
DECLARE @SpreadBalance BIGINT     -- �ƹ����
DECLARE @MinBalanceScore BIGINT   -- ��ͽ�����

-- ִ���߼�
BEGIN
	-- �û�����
	SELECT	@UserID=UserID,@GameID=GameID,@Accounts=Accounts,@Nullity=Nullity,@StunDown=StunDown,@SpreaderID=SpreaderID
	FROM QPAccountsDBLink.QPAccountsDB.dbo.AccountsInfo
	WHERE UserID=@dwUserID

	-- ��ѯ�û�
	IF @UserID IS NULL
	BEGIN
		SET @strErrorDescribe= N'�����ʺŲ����ڻ������������������֤���ٴγ��Ե�¼��'
		RETURN 1
	END

	-- �ʺŽ�ֹ
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

	-- ��С������
	SELECT @MinBalanceScore=MinBalanceScore FROM GlobalSpreadInfo
	IF @MinBalanceScore IS NULL
	BEGIN
		SET @MinBalanceScore=200000
	END
	IF @dwBalance < @MinBalanceScore
	BEGIN
		SET @strErrorDescribe=N'�ǳ���Ǹ,��ÿ�ʽ������Ŀ�������' + Convert(NVARCHAR(30), @MinBalanceScore) + '��ң�'
		RETURN 4
	END

	-- ��ѯ�ƹ����
	SELECT @SpreadBalance = SUM(Score) FROM RecordSpreadInfo WHERE UserID = @dwUserID
	IF @SpreadBalance IS NULL OR @SpreadBalance<0 OR @dwBalance>@SpreadBalance
	BEGIN
		SET @strErrorDescribe=N'�ǳ���Ǹ,����ǰ�ƹ�����!'
		RETURN 5
	END

	-- ��ѯ���н��
	DECLARE @InsureScore BIGINT
	SELECT @InsureScore=InsureScore FROM GameScoreInfo(NOLOCK) WHERE UserID = @UserID
	IF @InsureScore IS NULL
	BEGIN
		SET @InsureScore=0
	END

	-- �����¼
	INSERT INTO RecordSpreadInfo(
		UserID,Score,TypeID,ChildrenID,InsureScore,CollectNote)
	VALUES(
		@UserID,-@dwBalance,4,0,@InsureScore,N'����֧���������ַ��'+@strClientIP)

	-- �������н��
	UPDATE GameScoreInfo SET InsureScore = InsureScore+@dwBalance
	WHERE UserID = @UserID
	IF @@ROWCOUNT = 0 
	BEGIN
		INSERT INTO GameScoreInfo(UserID,InsureScore,RegisterIP,LastLogonIP)
		VALUES(@UserID,@dwBalance,@strClientIP,@strClientIP)
	END

	-- �ϼ����
	IF @SpreaderID<>0 
	BEGIN
		DECLARE @Rate DECIMAL(18,2)		 -- �ϼ���ɱ���
		DECLARE @ParentBanlance  BIGINT  -- �ϼ���ɽ��
		DECLARE @Note NVARCHAR(512)		 -- ��ע
		SELECT @Rate=BalanceRate FROM GlobalSpreadInfo
		IF @Rate IS NULL
		BEGIN
			SET @Rate=0.1
		END
		SET @ParentBanlance = @dwBalance*@Rate
		SET @Note = N'����'+LTRIM(STR(@dwBalance))

		INSERT INTO RecordSpreadInfo(
			UserID,Score,TypeID,ChildrenID,CollectNote)
		VALUES(
			@SpreaderID,@ParentBanlance,4,@UserID,@Note)
	END

	SET @strErrorDescribe=N'����ɹ�!'
END
RETURN 0
GO



