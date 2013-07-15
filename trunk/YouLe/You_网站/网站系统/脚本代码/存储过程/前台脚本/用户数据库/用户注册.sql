----------------------------------------------------------------------------------------------------
-- ��Ȩ��2011
-- ʱ�䣺2011-08-31
-- ��;���ʺ�ע��
----------------------------------------------------------------------------------------------------

USE QPAccountsDB
GO

IF EXISTS (SELECT * FROM DBO.SYSOBJECTS WHERE ID = OBJECT_ID(N'[dbo].NET_PW_RegisterAccounts') and OBJECTPROPERTY(ID, N'IsProcedure') = 1)
DROP PROCEDURE [dbo].NET_PW_RegisterAccounts
GO

SET QUOTED_IDENTIFIER ON 
GO

SET ANSI_NULLS ON 
GO

----------------------------------------------------------------------------------------------------

-- �ʺ�ע��
CREATE PROCEDURE NET_PW_RegisterAccounts
	@strAccounts NVARCHAR(31),					-- �û��ʺ�
	@strNickname NVARCHAR(31),					-- �û��ǳ�
	@strLogonPass NCHAR(32),					-- �û�����
	@strInsurePass NCHAR(32),					-- �û�����
	@dwFaceID INT,								-- ͷ���ʶ
	@dwGender TINYINT,							-- �û��Ա�
	@strSpreader NVARCHAR(31),					-- �ƹ�Ա��
	@strCompellation NVARCHAR(16),				-- ��ʵ����
	@strPassPortID NVARCHAR(18),				-- ���֤��
	@strClientIP NVARCHAR(15),					-- ���ӵ�ַ
	@strErrorDescribe	NVARCHAR(127) OUTPUT	-- �����Ϣ
WITH ENCRYPTION AS

-- ��������
SET NOCOUNT ON

-- ������Ϣ
DECLARE @UserID INT
DECLARE @FaceID INT
DECLARE @Accounts NVARCHAR(31)
DECLARE @Nickname NVARCHAR(31)
DECLARE @UnderWrite NVARCHAR(63)

-- ��չ��Ϣ
DECLARE @GameID INT
DECLARE @SpreaderID INT
DECLARE @Gender TINYINT
DECLARE @Experience INT
DECLARE @Loveliness INT
DECLARE @MemberOrder INT
DECLARE @MemberOverDate DATETIME
DECLARE @CustomFaceVer TINYINT
DECLARE @Compellation NVARCHAR(16)
DECLARE @PassPortID NVARCHAR(18)

-- ��������
DECLARE @EnjoinLogon AS INT
DECLARE @EnjoinRegister AS INT

-- ִ���߼�
BEGIN
	-- ע����ͣ
	SELECT @EnjoinRegister=StatusValue FROM SystemStatusInfo(NOLOCK) WHERE StatusName=N'EnjoinRegister'
	IF @EnjoinRegister IS NOT NULL AND @EnjoinRegister<>0
	BEGIN
		SELECT @strErrorDescribe=StatusString FROM SystemStatusInfo(NOLOCK) WHERE StatusName=N'EnjoinRegister'
		RETURN 1
	END

	-- ��¼��ͣ
	SELECT @EnjoinLogon=StatusValue FROM SystemStatusInfo(NOLOCK) WHERE StatusName=N'EnjoinLogon'
	IF @EnjoinLogon IS NOT NULL AND @EnjoinLogon<>0
	BEGIN
		SELECT @strErrorDescribe=StatusString FROM SystemStatusInfo(NOLOCK) WHERE StatusName=N'EnjoinLogon'
		RETURN 2
	END

	-- Ч������
	IF EXISTS (SELECT [String] FROM ConfineContent(NOLOCK) WHERE CHARINDEX(String,@strAccounts)>0 AND (EnjoinOverDate>GETDATE() OR EnjoinOverDate IS NULL))
	BEGIN
		SET @strErrorDescribe=N'��Ǹ��֪ͨ��������������ʺ������������ַ�����������ʺ������ٴ������ʺţ�'
		RETURN 1
	END

	-- Ч���ǳ�
	IF EXISTS (SELECT [String] FROM ConfineContent(NOLOCK) WHERE CHARINDEX(String,@strNickname)>0 AND (EnjoinOverDate>GETDATE() OR EnjoinOverDate IS NULL))
	BEGIN
		SET @strErrorDescribe=N'��Ǹ��֪ͨ��������������ǳƺ��������ַ�����������ǳƺ��ٴ������ʺţ�'
		RETURN 1
	END
	
	-- Ч���ַ
	SELECT @EnjoinRegister=EnjoinRegister FROM ConfineAddress(NOLOCK) WHERE AddrString=@strClientIP AND (EnjoinOverDate>GETDATE() OR EnjoinOverDate IS NULL)
	IF @EnjoinRegister IS NOT NULL AND @EnjoinRegister<>0
	BEGIN
		SET @strErrorDescribe=N'��Ǹ��֪ͨ����ϵͳ��ֹ�������ڵ� IP ��ַ��ע�Ṧ�ܣ�����ϵ�ͻ����������˽���ϸ�����'
		RETURN 2
	END
	
	-- ��ѯ�û�
	IF EXISTS (SELECT UserID FROM AccountsInfo(NOLOCK) WHERE Accounts=@strAccounts)
	BEGIN
		SET @strErrorDescribe=N'���ʺ����ѱ�ע�ᣬ�뻻��һ�ʺ����ֳ����ٴ�ע�ᣡ'
		RETURN 3
	END

	IF EXISTS (SELECT UserID FROM AccountsInfo(NOLOCK) WHERE NickName=@strNickname)
	BEGIN
		SET @strErrorDescribe=N'���ǳ��ѱ�ע�ᣬ�뻻��һ�ǳƳ����ٴ�ע�ᣡ'
		RETURN 3
	END

	-- ���ƹ�Ա
	IF @strSpreader<>''
	BEGIN
		-- ���ƹ�Ա
		SELECT @SpreaderID=UserID FROM AccountsInfo(NOLOCK) WHERE Accounts=@strSpreader

		-- �������
		IF @SpreaderID IS NULL
		BEGIN
			SET @strErrorDescribe=N'������д���Ƽ��˲����ڻ�����д����������ٴ�ע�ᣡ'
			RETURN 4
		END
	END
	ELSE SET @SpreaderID=0

	-- ע���û�
	INSERT AccountsInfo (Accounts,Nickname,RegAccounts,LogonPass,InsurePass,SpreaderID,Gender,FaceID,WebLogonTimes,RegisterIP,LastLogonIP,Compellation,PassPortID)
	VALUES (@strAccounts,@strNickname,@strAccounts,@strLogonPass,@strInsurePass,@SpreaderID,@dwGender,@dwFaceID,1,@strClientIP,@strClientIP,@strCompellation,@strPassPortID)

	-- �����ж�
	IF @@ERROR<>0
	BEGIN
		SET @strErrorDescribe=N'�ʺ��Ѵ��ڣ��뻻��һ�ʺ����ֳ����ٴ�ע�ᣡ'
		RETURN 5
	END
	
	-- ��ѯ�û�
	SELECT @UserID=UserID, @Accounts=Accounts, @Nickname=Nickname,@UnderWrite=UnderWrite, @Gender=Gender, @FaceID=FaceID, @Experience=Experience,
		@MemberOrder=MemberOrder, @MemberOverDate=MemberOverDate, @Loveliness=Loveliness,@CustomFaceVer=CustomFaceVer,
		@Compellation=Compellation,@PassPortID=PassPortID
	FROM AccountsInfo(NOLOCK) WHERE Accounts=@strAccounts

	-- �����ʶ
	SELECT @GameID=GameID FROM GameIdentifier(NOLOCK) WHERE UserID=@UserID
	IF @GameID IS NULL 
	BEGIN
		SET @GameID=0
		SET @strErrorDescribe=N'�û�ע��ɹ�����δ�ɹ���ȡ��Ϸ ID ���룬ϵͳ�Ժ󽫸������䣡'
	END
	ELSE UPDATE AccountsInfo SET GameID=@GameID WHERE UserID=@UserID

	-- �ƹ����
	IF @SpreaderID<>0
	BEGIN
		DECLARE @Score BIGINT
		DECLARE @Note NVARCHAR(512)
		SET @Note = N'ע��'
		SELECT @Score = RegisterGrantScore FROM QPTreasureDBLink.QPTreasureDB.dbo.GlobalSpreadInfo
		IF @Score IS NULL
		BEGIN
			SET @Score=5000
		END
		INSERT INTO QPTreasureDBLink.QPTreasureDB.dbo.RecordSpreadInfo(
			UserID,Score,TypeID,ChildrenID,CollectNote)
		VALUES(@SpreaderID,@Score,1,@UserID,@Note)		
	END

	-- ��¼��־
	DECLARE @DateID INT
	SET @DateID=CAST(CAST(GETDATE() AS FLOAT) AS INT)
	UPDATE SystemStreamInfo SET WebRegisterSuccess=WebRegisterSuccess+1 WHERE DateID=@DateID
	IF @@ROWCOUNT=0 INSERT SystemStreamInfo (DateID, WebRegisterSuccess) VALUES (@DateID, 1)

	----------------------------------------------------------------------------------------------------
	----------------------------------------------------------------------------------------------------
	-- ע������

	-- ��ȡ����
	DECLARE @GrantScoreCount AS BIGINT
	DECLARE @GrantIPCount AS BIGINT
	SELECT @GrantScoreCount=StatusValue FROM SystemStatusInfo(NOLOCK) WHERE StatusName=N'GrantScoreCount'
	SELECT @GrantIPCount=StatusValue FROM SystemStatusInfo(NOLOCK) WHERE StatusName=N'GrantIPCount'

	-- ��������
	IF @GrantScoreCount IS NOT NULL AND @GrantScoreCount>0 AND @GrantIPCount IS NOT NULL AND @GrantIPCount>0
	BEGIN
		-- ���ʹ���
		DECLARE @GrantCount AS BIGINT
		SELECT @GrantCount=GrantCount FROM SystemGrantCount(NOLOCK) WHERE DateID=@DateID AND RegisterIP=@strClientIP
	
		-- �����ж�
		IF @GrantCount IS NOT NULL AND @GrantCount>=@GrantIPCount
		BEGIN
			SET @GrantScoreCount=0
		END
	END

	-- ���ͽ��
	IF @GrantScoreCount IS NOT NULL AND @GrantScoreCount>0
	BEGIN
		-- ���¼�¼
		UPDATE SystemGrantCount SET GrantScore=GrantScore+@GrantScoreCount, GrantCount=GrantCount+1 WHERE DateID=@DateID AND RegisterIP=@strClientIP

		-- �����¼
		IF @@ROWCOUNT=0
		BEGIN
			INSERT SystemGrantCount (DateID, RegisterIP, RegisterMachine, GrantScore, GrantCount) VALUES (@DateID, @strClientIP, '', @GrantScoreCount, 1)
		END

		-- ���ͽ��
		INSERT QPTreasureDBLink.QPTreasureDB.dbo.GameScoreInfo (UserID, Score, RegisterIP, LastLogonIP) VALUES (@UserID, @GrantScoreCount, @strClientIP, @strClientIP) 
	END

	----------------------------------------------------------------------------------------------------
	----------------------------------------------------------------------------------------------------

	-- �������
	SELECT @UserID AS UserID, @GameID AS GameID, @Accounts AS Accounts, @Nickname AS Nickname,@UnderWrite AS UnderWrite, @FaceID AS FaceID, 
		@Gender AS Gender, @Experience AS Experience, @MemberOrder AS MemberOrder, @MemberOverDate AS MemberOverDate,
		@Loveliness AS Loveliness,@CustomFaceVer AS CustomFaceVer,
		@Compellation AS Compellation,@PassPortID AS PassPortID
End 

RETURN 0

GO