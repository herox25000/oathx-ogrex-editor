----------------------------------------------------------------------------------------------------
-- ��Ȩ��2011
-- ʱ�䣺2011-08-31
-- ��;���޸�����
----------------------------------------------------------------------------------------------------

USE QPAccountsDB
GO

IF EXISTS (SELECT * FROM DBO.SYSOBJECTS WHERE ID = OBJECT_ID(N'[dbo].NET_PW_ModifyUserInfo') and OBJECTPROPERTY(ID, N'IsProcedure') = 1)
DROP PROCEDURE [dbo].NET_PW_ModifyUserInfo

IF EXISTS (SELECT * FROM DBO.SYSOBJECTS WHERE ID = OBJECT_ID(N'[dbo].NET_PW_ModifyUserFace') and OBJECTPROPERTY(ID, N'IsProcedure') = 1)
DROP PROCEDURE [dbo].NET_PW_ModifyUserFace

IF EXISTS (SELECT * FROM DBO.SYSOBJECTS WHERE ID = OBJECT_ID(N'[dbo].NET_PW_ModifyUserNickName') and OBJECTPROPERTY(ID, N'IsProcedure') = 1)
DROP PROCEDURE [dbo].NET_PW_ModifyUserNickName

GO

SET QUOTED_IDENTIFIER ON
GO

SET ANSI_NULLS ON
GO

----------------------------------------------------------------------------------------------------

-- �޸��û�����
CREATE PROCEDURE NET_PW_ModifyUserInfo
	-- ��֤��Ϣ
	@dwUserID INT,								-- �û� I D

	-- �û�����
	@dwGender TINYINT,							-- �û��Ա�
	@strUnderWrite NVARCHAR(63),				-- �û�ǩ��

	-- ��ϸ����
	@strCompellation NVARCHAR(16),				-- �û�����
	@strQQ NVARCHAR(16),						-- Q Q ����
	@strEmail NVARCHAR(32),						-- �ʼ���ַ
	@strMobilePhone NVARCHAR(16),				-- �ֻ�����
	@strSeatPhone NVARCHAR(32),					-- �̶��绰
	@strDwellingPlace NVARCHAR(128),			-- ��ϵ��ַ
	@strUserNote NVARCHAR(256),					-- ��������	

	@strErrorDescribe NVARCHAR(127) OUTPUT		-- �����Ϣ
WITH ENCRYPTION AS

-- ��������
SET NOCOUNT ON

-- ִ���߼�
BEGIN

	-- ��ѯ�û�
	DECLARE @UserID INT
	DECLARE @Nullity BIT
	DECLARE @StunDown BIT
	SELECT @UserID=UserID, @Nullity=Nullity, @StunDown=StunDown FROM AccountsInfo(NOLOCK) WHERE UserID=@dwUserID

	-- �ʺŽ�ֹ
	IF @Nullity<>0
	BEGIN
		SET @strErrorDescribe=N'�����ʺ���ʱ���ڶ���״̬������ϵ�ͻ����������˽���ϸ�����'
		RETURN 1
	END	

	-- �ʺŹر�
	IF @StunDown<>0
	BEGIN
		SET @strErrorDescribe=N'�����ʺ�ʹ���˰�ȫ�رչ��ܣ��������¿�ͨ����ܼ���ʹ�ã�'
		RETURN 2
	END		

	-- ������Ϣ
	UPDATE AccountsInfo SET Gender=@dwGender,UnderWrite=@strUnderWrite WHERE UserID=@dwUserID

	-- ��������
	UPDATE IndividualDatum SET Compellation=@strCompellation, QQ=@strQQ, EMail=@strEMail, MobilePhone=@strMobilePhone,SeatPhone=@strSeatPhone,
		DwellingPlace=@strDwellingPlace, UserNote=@strUserNote WHERE UserID=@dwUserID

	-- ���봦��
	IF @@ROWCOUNT=0
	BEGIN
		INSERT IndividualDatum (UserID, Compellation, QQ, EMail, MobilePhone,SeatPhone, DwellingPlace, UserNote)
		VALUES (@dwUserID, @strCompellation, @strQQ, @strEMail, @strMobilePhone, @strSeatPhone,@strDwellingPlace, @strUserNote)
	END

	-- ������Ϣ	
	SET @strErrorDescribe= N'��ϲ�������ĸ��������޸ĳɹ��ˣ�'
END

RETURN 0

GO


----------------------------------------------------------------------------------------------------

-- �޸��û�ͷ��
CREATE PROCEDURE NET_PW_ModifyUserFace
	-- ��֤��Ϣ
	@dwUserID INT,								-- �û� I D

	-- �û�����
	@dwFaceID SMALLINT,							-- �û�ͷ��

	@strErrorDescribe NVARCHAR(127) OUTPUT		-- �����Ϣ
WITH ENCRYPTION AS

-- ��������
SET NOCOUNT ON

-- ִ���߼�
BEGIN

	-- ��ѯ�û�
	DECLARE @UserID INT
	DECLARE @Nullity BIT
	DECLARE @StunDown BIT
	SELECT @UserID=UserID, @Nullity=Nullity, @StunDown=StunDown FROM AccountsInfo(NOLOCK) WHERE UserID=@dwUserID

	-- �ʺŽ�ֹ
	IF @Nullity<>0
	BEGIN
		SET @strErrorDescribe=N'�����ʺ���ʱ���ڶ���״̬������ϵ�ͻ����������˽���ϸ�����'
		RETURN 1
	END	

	-- �ʺŹر�
	IF @StunDown<>0
	BEGIN
		SET @strErrorDescribe=N'�����ʺ�ʹ���˰�ȫ�رչ��ܣ��������¿�ͨ����ܼ���ʹ�ã�'
		RETURN 2
	END		

	-- ����ͷ��
	UPDATE AccountsInfo SET FaceID = @dwFaceID WHERE UserID=@dwUserID

	-- ������Ϣ	
	SET @strErrorDescribe= N'��ϲ��������ͷ���޸ĳɹ��ˣ�'
END

RETURN 0

GO


----------------------------------------------------------------------------------------------------

-- �޸��û��ǳ�
CREATE PROCEDURE NET_PW_ModifyUserNickName
	-- ��֤��Ϣ
	@dwUserID INT,								-- �û� I D
	@ClientIP NVARCHAR(31),	
	-- �û�����
	@strNickName NVARCHAR(31),							-- �û��ǳ�

	@strErrorDescribe NVARCHAR(127) OUTPUT		-- �����Ϣ
WITH ENCRYPTION AS

-- ��������
SET NOCOUNT ON

-- ִ���߼�
BEGIN

	-- ��ѯ�û�
	DECLARE @UserID INT
	DECLARE @Nullity BIT
	DECLARE @StunDown BIT
	SELECT @UserID=UserID, @Nullity=Nullity, @StunDown=StunDown FROM AccountsInfo(NOLOCK) WHERE UserID=@dwUserID

	-- �ʺŽ�ֹ
	IF @Nullity<>0
	BEGIN
		SET @strErrorDescribe=N'�����ʺ���ʱ���ڶ���״̬������ϵ�ͻ����������˽���ϸ�����'
		RETURN 1
	END	

	-- �ʺŹر�
	IF @StunDown<>0
	BEGIN
		SET @strErrorDescribe=N'�����ʺ�ʹ���˰�ȫ�رչ��ܣ��������¿�ͨ����ܼ���ʹ�ã�'
		RETURN 2
	END		

	-- Ч���ǳ�
	IF EXISTS (SELECT [String] FROM ConfineContent(NOLOCK) WHERE CHARINDEX(String,@strNickName)>0 AND (EnjoinOverDate>GETDATE() OR EnjoinOverDate IS NULL))
	BEGIN
		SET @strErrorDescribe=N'��Ǹ��֪ͨ��������������ǳƺ��������ַ�����������ǳƺ��ٴ������ʺţ�'
		RETURN 3
	END

	IF EXISTS (SELECT UserID FROM AccountsInfo(NOLOCK) WHERE NickName=@strNickName)
	BEGIN
		SET @strErrorDescribe=N'���ǳ��ѱ�ע�ᣬ�뻻��һ�ǳƳ����ٴ�ע�ᣡ'
		RETURN 3
	END

	-- �����ǳ�
	UPDATE AccountsInfo SET NickName = @strNickName WHERE UserID=@dwUserID
	
    -- ����޸ļ�¼
    INSERT INTO QPRecordDB.dbo.RecordAccountsExpend(OperMasterID,UserID ,ReAccounts ,ClientIP ,CollectDate)
    VALUES(0,@dwUserID ,@strNickName , @ClientIP, GETDATE())

	-- ������Ϣ	
	SET @strErrorDescribe= N'��ϲ���������ǳ��޸ĳɹ��ˣ�'
END

RETURN 0

GO


