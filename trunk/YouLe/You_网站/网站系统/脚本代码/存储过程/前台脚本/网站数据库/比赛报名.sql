----------------------------------------------------------------------------------------------------
-- ��Ȩ��2011
-- ʱ�䣺2011-09-02
-- ��;����������
----------------------------------------------------------------------------------------------------
USE QPNativeWebDB
GO

IF EXISTS (SELECT * FROM DBO.SYSOBJECTS WHERE ID = OBJECT_ID(N'[dbo].NET_PW_AddGameMatchUser') and OBJECTPROPERTY(ID, N'IsProcedure') = 1)
DROP PROCEDURE [dbo].NET_PW_AddGameMatchUser
GO

SET QUOTED_IDENTIFIER ON 
GO

SET ANSI_NULLS ON 
GO

----------------------------------------------------------------------------------------------------
-- ��������
CREATE PROCEDURE NET_PW_AddGameMatchUser
	@dwMatchID			INT,				-- ������ʶ 
	@strAccounts		NVARCHAR(31),		-- �û��ʺ�
	@strPassword		NCHAR(32),			-- �û�����

	@strCompellation	NVARCHAR(16),		-- �û�����
	@dwGender			TINYINT,			-- �Ա�
	@strPassportID		NVARCHAR(32),		-- ���֤
	@strMobilePhone		NVARCHAR(16),		-- ��ϵ�绰
	@strEMail			NVARCHAR(32),		-- ��������
	@strQQ				NVARCHAR(16),		-- QQ
	@strDwellingPlace	NVARCHAR(128),		-- ��ϸ��ַ
	@strPostalCode		NVARCHAR(8),		-- �ʱ�

	@strClientIP		NVARCHAR(15),		-- ������ַ
	@strErrorDescribe	NVARCHAR(127) OUTPUT	-- �����Ϣ
WITH ENCRYPTION AS

-- ��������
SET NOCOUNT ON

-- ������Ϣ
DECLARE @UserID INT
DECLARE @Accounts NVARCHAR(31)
DECLARE @GameID	INT
DECLARE @LogonPass	NCHAR(32)
DECLARE @Nullity BIT
DECLARE @StunDown BIT

-- ������Ϣ
DECLARE @MatchID INT
DECLARE @ApplyBeginDate DATETIME
DECLARE @ApplyEndDate DATETIME

-- ִ���߼�
BEGIN
	-- ��ѯ�û�
	SELECT @UserID=UserID,@Accounts=Accounts,@GameID=GameID,@LogonPass=LogonPass,@Nullity=Nullity, @StunDown=StunDown
	FROM QPAccountsDBLink.QPAccountsDB.dbo.AccountsInfo WHERE Accounts=@strAccounts

	IF @UserID IS NULL
	BEGIN
		SET @strErrorDescribe=N'�����ʺŲ����ڻ������������������֤���ٴγ��Ե�¼��'
		RETURN 100
	END	

	-- �ʺŽ�ֹ
	IF @Nullity<>0
	BEGIN
		SET @strErrorDescribe=N'�����ʺ���ʱ���ڶ���״̬������ϵ�ͻ����������˽���ϸ�����'
		RETURN 101
	END	

	-- �ʺŹر�
	IF @StunDown<>0
	BEGIN
		SET @strErrorDescribe=N'�����ʺ�ʹ���˰�ȫ�رչ��ܣ��������¿�ͨ����ܼ���ʹ�ã�'
		RETURN 102
	END	

	-- �����ж�
	IF @LogonPass<>@strPassword
	BEGIN
		SET @strErrorDescribe=N'�����ʺŲ����ڻ������������������֤���ٴγ��Ե�¼��'
		RETURN 103
	END

	-- ��ѯ����
	SELECT @MatchID=MatchID,@ApplyBeginDate=ApplyBeginDate,@ApplyEndDate=ApplyEndDate
	FROM GameMatchInfo WHERE Nullity=0 AND MatchID=@dwMatchID

	IF @MatchID IS NULL
	BEGIN
		SET @strErrorDescribe=N'���������ڻ򱻽�ֹ������ϵ�ͻ����������˽���ϸ�����'
		RETURN 200
	END

	IF @ApplyBeginDate > GETDATE()
	BEGIN
		SET @strErrorDescribe=N'��������δ��ʼ����鿴���¹����˽���ϸ�����'
		RETURN 201
	END

	IF @ApplyEndDate < GETDATE()
	BEGIN
		SET @strErrorDescribe=N'���������ѽ�ֹ��'
		RETURN 202
	END

	-- �Ƿ��ѱ���
	IF EXISTS (SELECT UserID FROM GameMatchUserInfo WHERE MatchID=@MatchID AND UserID=@UserID)
	BEGIN
		SET @strErrorDescribe=N'���ѱ���,�����ظ�������'
		RETURN 300
	END

	-- ����������Ϣ
	INSERT INTO GameMatchUserInfo(
		MatchID,UserID,Accounts,GameID,Compellation,Gender,PassportID,MobilePhone,EMail,QQ,DwellingPlace,PostalCode,ClientIP)
	VALUES(
		@MatchID,@UserID,@Accounts,@GameID,@strCompellation,@dwGender,@strPassportID,@strMobilePhone,
		@strEMail,@strQQ,@strDwellingPlace,@strPostalCode,@strClientIP)

	SET @strErrorDescribe=N'�����ɹ���'
END
RETURN 0
GO