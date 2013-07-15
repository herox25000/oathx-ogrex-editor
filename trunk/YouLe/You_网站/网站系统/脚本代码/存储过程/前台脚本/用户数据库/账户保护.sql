----------------------------------------------------------------------------------------------------
-- ��Ȩ��2011
-- ʱ�䣺2011-08-31
-- ��;���˻�����
----------------------------------------------------------------------------------------------------

USE QPAccountsDB
GO

IF EXISTS (SELECT * FROM DBO.SYSOBJECTS WHERE ID = OBJECT_ID(N'[dbo].NET_PW_AddAccountProtect') and OBJECTPROPERTY(ID, N'IsProcedure') = 1)
DROP PROCEDURE [dbo].NET_PW_AddAccountProtect
GO

IF EXISTS (SELECT * FROM DBO.SYSOBJECTS WHERE ID = OBJECT_ID(N'[dbo].NET_PW_ModifyAccountProtect') and OBJECTPROPERTY(ID, N'IsProcedure') = 1)
DROP PROCEDURE [dbo].NET_PW_ModifyAccountProtect
GO

IF EXISTS (SELECT * FROM DBO.SYSOBJECTS WHERE ID = OBJECT_ID(N'[dbo].NET_PW_GetAccountProtectByUserID') and OBJECTPROPERTY(ID, N'IsProcedure') = 1)
DROP PROCEDURE [dbo].NET_PW_GetAccountProtectByUserID
GO

IF EXISTS (SELECT * FROM DBO.SYSOBJECTS WHERE ID = OBJECT_ID(N'[dbo].NET_PW_GetAccountProtectByAccounts') and OBJECTPROPERTY(ID, N'IsProcedure') = 1)
DROP PROCEDURE [dbo].NET_PW_GetAccountProtectByAccounts
GO

IF EXISTS (SELECT * FROM DBO.SYSOBJECTS WHERE ID = OBJECT_ID(N'[dbo].NET_PW_GetAccountProtectByGameID') and OBJECTPROPERTY(ID, N'IsProcedure') = 1)
DROP PROCEDURE [dbo].NET_PW_GetAccountProtectByGameID
GO

IF EXISTS (SELECT * FROM DBO.SYSOBJECTS WHERE ID = OBJECT_ID(N'[dbo].NET_PW_ConfirmAccountProtect') and OBJECTPROPERTY(ID, N'IsProcedure') = 1)
DROP PROCEDURE [dbo].NET_PW_ConfirmAccountProtect
GO

SET QUOTED_IDENTIFIER ON 
GO

SET ANSI_NULLS ON
GO

----------------------------------------------------------------------------------------------------

-- �������뱣��
CREATE PROCEDURE NET_PW_AddAccountProtect
	@dwUserID INT,								-- �û� I D

	@strQuestion1 NVARCHAR(32),					-- ����һ
	@strResponse1 NVARCHAR(32),					-- ��һ
	@strQuestion2 NVARCHAR(32),					-- �����
	@strResponse2 NVARCHAR(32),					-- �𰸶�
	@strQuestion3 NVARCHAR(32),					-- ������
	@strResponse3 NVARCHAR(32),					-- ����

	@strPassportID NVARCHAR(32),				-- ֤������
	@dwPassportType TINYINT,					-- ֤������
	@strSafeEmail NVARCHAR(32),					-- �������

	@strClientIP NVARCHAR(15),					-- ���ӵ�ַ
	@strErrorDescribe NVARCHAR(127) OUTPUT		-- �����Ϣ
WITH ENCRYPTION AS

-- ��������
SET NOCOUNT ON

-- ִ���߼�
BEGIN
	-- ��ѯ�û�
	DECLARE @UserID INT
	DECLARE @StunDown BIT
	DECLARE @Nullity BIT
	DECLARE @ProtectID INT
	DECLARE @LogonPass NCHAR(32)
	SELECT @UserID=UserID, @ProtectID=ProtectID, @LogonPass=LogonPass, @Nullity=Nullity, @StunDown=StunDown
	FROM AccountsInfo(NOLOCK) WHERE UserID=@dwUserID

	-- ��ѯ�û�
	IF @UserID IS NULL 
	BEGIN
		SET @strErrorDescribe=N'�����ʺŲ����ڻ������������������֤���ٴγ��ԣ�'
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

	-- �ܱ�Ч��
	IF @ProtectID<>0
	BEGIN
		SET @strErrorDescribe=N'�����ʺ��Ѿ������ˡ��ʺű��������ܣ��޷��ٴ����롰�ʺű�������'
		RETURN 4
	END

	-- ���뱣��
	INSERT INTO AccountsProtect(UserID,Question1,Response1,Question2,Response2,Question3,Response3,
		PassportID,PassportType,SafeEmail,CreateIP,ModifyIP)
	VALUES(@UserID,@strQuestion1,@strResponse1,@strQuestion2,@strResponse2,@strQuestion3,@strResponse3,
		@strPassportID,@dwPassportType,@strSafeEmail,@strClientIP,@strClientIP)

	-- �����û�
	IF @@ERROR=0 
	BEGIN
		UPDATE AccountsInfo SET ProtectID=@@IDENTITY WHERE UserID = @dwUserID
		SET @strErrorDescribe=N'��ϲ�������ʺű�������������ɹ��ˣ���������ġ��ʺű��������ݣ�'
		RETURN 0
	END
	ELSE
	BEGIN
		SET @strErrorDescribe=N'���ʺű�������������ʧ���ˣ�����ϵ�ͻ����������˽���ϸ�����'
		RETURN 5
	END
END

SET NOCOUNT OFF
RETURN 0

GO

----------------------------------------------------------------------------------------------------

-- �������뱣��
CREATE PROCEDURE NET_PW_ModifyAccountProtect
	@dwUserID INT,								-- �û� I D

	@strQuestion1 NVARCHAR(32),					-- ����һ
	@strResponse1 NVARCHAR(32),					-- ��һ
	@strQuestion2 NVARCHAR(32),					-- �����
	@strResponse2 NVARCHAR(32),					-- �𰸶�
	@strQuestion3 NVARCHAR(32),					-- ������
	@strResponse3 NVARCHAR(32),					-- ����

	@strSafeEmail NVARCHAR(32),					-- �������

	@strClientIP NVARCHAR(15),					-- ���ӵ�ַ
	@strErrorDescribe NVARCHAR(127) OUTPUT		-- �����Ϣ
WITH ENCRYPTION AS

-- ��������
SET NOCOUNT ON

-- ִ���߼�
BEGIN
	-- ��ѯ�û�
	DECLARE @UserID INT
	DECLARE @StunDown BIT
	DECLARE @Nullity BIT
	DECLARE @ProtectID INT
	DECLARE @LogonPass NCHAR(32)
	SELECT @UserID=UserID, @ProtectID=ProtectID, @LogonPass=LogonPass, @Nullity=Nullity, @StunDown=StunDown
	FROM AccountsInfo(NOLOCK) WHERE UserID=@dwUserID

	-- ��ѯ�û��������ж�
	IF @UserID IS NULL 
	BEGIN
		SET @strErrorDescribe=N'�����ʺŲ����ڻ������������������֤���ٴγ��ԣ�'
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

	-- �ܱ�Ч��
	IF @ProtectID=0
	BEGIN
		SET @strErrorDescribe=N'�����ʺŻ�û�����롰�ʺű��������ܣ��޷��޸ġ��ʺű��������ϣ�'
		RETURN 4
	END

	-- ���뱣��
	UPDATE AccountsProtect SET Question1 = @strQuestion1,Response1 = @strResponse1,Question2 = @strQuestion2,
		Response2 = @strResponse2,Question3 = @strQuestion3,Response3 = @strResponse3,SafeEmail = @strSafeEmail,		
		ModifyIP = @strClientIP,ModifyDate = getdate()
	WHERE UserID = @dwUserID
	
	-- ������Ϣ
	SET @strErrorDescribe=N'��ϲ�������ʺű����������޸ĳɹ��ˣ���������ġ��ʺű��������ݣ�'
	RETURN 0
END

SET NOCOUNT OFF
RETURN 0

GO

----------------------------------------------------------------------------------------------------

-- ��ȡ�ܱ�����
CREATE PROCEDURE NET_PW_GetAccountProtectByUserID
	@dwUserID			INT,						-- �û���ʶ
	@strErrorDescribe NVARCHAR(127) OUTPUT		-- �����Ϣ
WITH ENCRYPTION AS

-- ��������
SET NOCOUNT ON

-- ������Ϣ
DECLARE @UserID			INT
DECLARE @ProtectID		INT
DECLARE @Nullity		TINYINT
DECLARE @StunDown		TINYINT

-- ������Ϣ
DECLARE @PassportType	TINYINT
DECLARE @Question1		NVARCHAR(32)
DECLARE @Question2		NVARCHAR(32)
DECLARE @Question3		NVARCHAR(32)

-- ִ���߼�
BEGIN	
	-- ��ѯ�û�	
	SELECT @UserID=UserID, @ProtectID=ProtectID, @Nullity=Nullity,@StunDown=StunDown
	FROM AccountsInfo(NOLOCK) WHERE UserID=@dwUserID

	-- �û�����
	IF @UserID IS NULL
	BEGIN
		SET @strErrorDescribe=N'�����ʺŲ����ڻ������������������֤���ٴγ��ԣ�'
		RETURN 1
	END	

	-- �ʺŽ�ֹ
	IF @Nullity<>0
	BEGIN
		SET @strErrorDescribe=N'�����ʺ���ʱ���ڶ���״̬������ϵ�ͷ������˽���ϸ�����'
		RETURN 2
	END	

	-- �ʺŹر�
	IF @StunDown<>0
	BEGIN
		SET @strErrorDescribe=N'�����ʺ�ʹ���˰�ȫ�رչ��ܣ��������¿�ͨ����ܼ���ʹ�ã�'
		RETURN 3
	END	
	
	-- �ܱ�Ч��
	IF @ProtectID=0
	BEGIN
		SET @strErrorDescribe=N'��Ǹ�������ʺŻ�û�����롰�ʺű��������ܣ�'
		RETURN 4
	END	

	-- ���뱣��
	DECLARE @TmpProtectID INT
	SELECT @TmpProtectID=ProtectID, @PassportType=PassportType, @Question1=Question1
		, @Question2=Question2, @Question3=Question3
	FROM AccountsProtect(NOLOCK) WHERE UserID=@dwUserID

	-- �ܱ�Ч��
	IF @TmpProtectID IS NULL
	BEGIN
		SET @strErrorDescribe=N'��Ǹ�������ʺŻ�û�������ˡ��ʺű��������ܣ�'
		RETURN 5
	END

	-- �������
	SELECT @UserID AS UserID, @TmpProtectID AS ProtectID, @PassportType AS PassportType
		, @Question1 AS Question1, @Question2 AS Question2, @Question3 AS Question3
END

SET NOCOUNT OFF

RETURN 0
GO

----------------------------------------------------------------------------------------------------

-- ��ȡ�ܱ�����
CREATE PROCEDURE NET_PW_GetAccountProtectByAccounts
	@strAccounts	NVARCHAR(31),						-- �û��ʺ�
	@strErrorDescribe NVARCHAR(127) OUTPUT		-- �����Ϣ
WITH ENCRYPTION AS

-- ��������
SET NOCOUNT ON

-- ������Ϣ
DECLARE @UserID			INT
DECLARE @ProtectID		INT
DECLARE @Nullity		TINYINT
DECLARE @StunDown		TINYINT

-- ������Ϣ
DECLARE @PassportType	TINYINT
DECLARE @Question1		NVARCHAR(32)
DECLARE @Question2		NVARCHAR(32)
DECLARE @Question3		NVARCHAR(32)

-- ִ���߼�
BEGIN	
	-- ��ѯ�û�	
	SELECT @UserID=UserID, @ProtectID=ProtectID, @Nullity=Nullity,@StunDown=StunDown
	FROM AccountsInfo(NOLOCK) WHERE Accounts=@strAccounts

	-- �û�����
	IF @UserID IS NULL
	BEGIN
		SET @strErrorDescribe=N'�����ʺŲ����ڻ������������������֤���ٴγ��ԣ�'
		RETURN 1
	END	

	-- �ʺŽ�ֹ
	IF @Nullity<>0
	BEGIN
		SET @strErrorDescribe=N'�����ʺ���ʱ���ڶ���״̬������ϵ�ͷ������˽���ϸ�����'
		RETURN 2
	END	

	-- �ʺŹر�
	IF @StunDown<>0
	BEGIN
		SET @strErrorDescribe=N'�����ʺ�ʹ���˰�ȫ�رչ��ܣ��������¿�ͨ����ܼ���ʹ�ã�'
		RETURN 3
	END	
	
	-- �ܱ�Ч��
	IF @ProtectID=0
	BEGIN
		SET @strErrorDescribe=N'��Ǹ�������ʺŻ�û�������ˡ��ʺű��������ܣ�'
		RETURN 4
	END	

	-- ���뱣��
	DECLARE @TmpProtectID INT
	SELECT @TmpProtectID=ProtectID, @PassportType=PassportType, @Question1=Question1
		, @Question2=Question2, @Question3=Question3
	FROM AccountsProtect(NOLOCK) WHERE UserID=@UserID

	-- �ܱ�Ч��
	IF @TmpProtectID IS NULL
	BEGIN
		SET @strErrorDescribe=N'��Ǹ�������ʺŻ�û�������ˡ��ʺű��������ܣ�'
		RETURN 5
	END

	-- �������
	SELECT @UserID AS UserID, @TmpProtectID AS ProtectID, @PassportType AS PassportType
		, @Question1 AS Question1, @Question2 AS Question2, @Question3 AS Question3
END

SET NOCOUNT OFF

RETURN 0
GO

----------------------------------------------------------------------------------------------------

-- ��ȡ�ܱ�����
CREATE PROCEDURE NET_PW_GetAccountProtectByGameID
	@dwGameID			INT,						-- ��Ϸ I D	
	@strErrorDescribe NVARCHAR(127) OUTPUT		-- �����Ϣ
WITH ENCRYPTION AS

-- ��������
SET NOCOUNT ON

-- ������Ϣ
DECLARE @UserID			INT
DECLARE @ProtectID		INT
DECLARE @Nullity		TINYINT
DECLARE @StunDown		TINYINT

-- ������Ϣ
DECLARE @PassportType	TINYINT
DECLARE @Question1		NVARCHAR(32)
DECLARE @Question2		NVARCHAR(32)
DECLARE @Question3		NVARCHAR(32)

-- ִ���߼�
BEGIN	
	-- ��ѯ�û�	
	SELECT @UserID=UserID, @ProtectID=ProtectID, @Nullity=Nullity,@StunDown=StunDown
	FROM AccountsInfo(NOLOCK) WHERE GameID=@dwGameID

	-- �û�����
	IF @UserID IS NULL
	BEGIN
		SET @strErrorDescribe=N'�����ʺŲ����ڻ������������������֤���ٴγ��ԣ�'
		RETURN 1
	END	

	-- �ʺŽ�ֹ
	IF @Nullity<>0
	BEGIN
		SET @strErrorDescribe=N'�����ʺ���ʱ���ڶ���״̬������ϵ�ͷ������˽���ϸ�����'
		RETURN 2
	END	

	-- �ʺŹر�
	IF @StunDown<>0
	BEGIN
		SET @strErrorDescribe=N'�����ʺ�ʹ���˰�ȫ�رչ��ܣ��������¿�ͨ����ܼ���ʹ�ã�'
		RETURN 3
	END	
	
	-- �ܱ�Ч��
	IF @ProtectID=0
	BEGIN
		SET @strErrorDescribe=N'��Ǹ�������ʺŻ�û�������ˡ��ʺű��������ܣ�'
		RETURN 4
	END	

	-- ���뱣��
	DECLARE @TmpProtectID INT
	SELECT @TmpProtectID=ProtectID, @PassportType=PassportType, @Question1=Question1
		, @Question2=Question2, @Question3=Question3
	FROM AccountsProtect(NOLOCK) WHERE UserID=@UserID

	-- �ܱ�Ч��
	IF @TmpProtectID IS NULL
	BEGIN
		SET @strErrorDescribe=N'��Ǹ�������ʺŻ�û�������ˡ��ʺű��������ܣ�'
		RETURN 5
	END

	-- �������
	SELECT @UserID AS UserID, @TmpProtectID AS ProtectID, @PassportType AS PassportType
		, @Question1 AS Question1, @Question2 AS Question2, @Question3 AS Question3
END

SET NOCOUNT OFF

RETURN 0
GO

----------------------------------------------------------------------------------------------------
CREATE PROCEDURE NET_PW_ConfirmAccountProtect
	@dwUserID			INT,                   		-- �û���ʶ	

	@strResponse1		NVARCHAR(32),             	-- ��ʾ��1
	@strResponse2		NVARCHAR(32),             	-- ��ʾ��2
	@strResponse3		NVARCHAR(32),             	-- ��ʾ��3

	@strErrorDescribe NVARCHAR(127) OUTPUT		-- �����Ϣ
WITH ENCRYPTION AS

-- ��������
SET NOCOUNT ON

-- ������Ϣ
DECLARE @UserID			INT
DECLARE @Nullity		TINYINT
DECLARE @StunDown		TINYINT

-- �ܱ���Ϣ
DECLARE @ProtectID		INT
DECLARE @Response1		NVARCHAR(32)
DECLARE @Response2		NVARCHAR(32)
DECLARE @Response3		NVARCHAR(32)

-- ִ���߼�
BEGIN	
	-- ��ѯ�û�	
	SELECT @UserID=UserID, @ProtectID=ProtectID, @Nullity=Nullity,@StunDown=StunDown
	FROM AccountsInfo(NOLOCK) WHERE UserID=@dwUserID

	-- �û�����
	IF @UserID IS NULL
	BEGIN
		SET @strErrorDescribe=N'�����ʺŲ����ڻ������������������֤���ٴγ��ԣ�'
		RETURN 1
	END	

	-- �ʺŽ�ֹ
	IF @Nullity<>0
	BEGIN
		SET @strErrorDescribe=N'�����ʺ���ʱ���ڶ���״̬������ϵ�ͷ������˽���ϸ�����'
		RETURN 2
	END	

	-- �ʺŹر�
	IF @StunDown<>0
	BEGIN
		SET @strErrorDescribe=N'�����ʺ�ʹ���˰�ȫ�رչ��ܣ��������¿�ͨ����ܼ���ʹ�ã�'
		RETURN 3
	END	
	
	-- �ܱ�Ч��
	IF @ProtectID=0
	BEGIN
		SET @strErrorDescribe=N'��Ǹ�������ʺŻ�û�������ˡ��ʺű��������ܣ�'
		RETURN 4
	END	

	-- ��ȡ�ܱ�
	DECLARE @TmpProtectID INT
	SELECT @TmpProtectID=ProtectID, @Response1=Response1,@Response2=Response2,@Response3=Response3
	FROM AccountsProtect(NOLOCK) WHERE ProtectID=@ProtectID AND UserID=@dwUserID

	-- �ܱ�Ч��
	IF @TmpProtectID IS NULL
	BEGIN
		SET @strErrorDescribe=N'��Ǹ�������ʺŻ�û�����롰�ʺű��������ܣ�'
		RETURN 5		
	END
	
	-- ����Ч
	IF ((@strResponse1 IS NULL OR @strResponse1=N'') OR
		(@strResponse2 IS NULL OR @strResponse2=N'') OR
		(@strResponse3 IS NULL OR @strResponse3=N''))
	BEGIN
		SET @strErrorDescribe=N'�������뱣���������������֤���ٴγ��ԣ�'
		RETURN 6	
	END

	-- ��Ч��һ
	IF @strResponse1 IS NOT NULL AND @strResponse1<>N''
	BEGIN
		IF @strResponse1<>@Response1
		BEGIN
			SET @strErrorDescribe=N'�������뱣���������������֤���ٴγ��ԣ�'
			RETURN 7	
		END
	END

	-- ��Ч���
	IF @strResponse2 IS NOT NULL AND @strResponse2<>N''
	BEGIN
		IF @strResponse2<>@Response2
		BEGIN
			SET @strErrorDescribe=N'�������뱣���������������֤���ٴγ��ԣ�'
			RETURN 8	
		END
	END

	-- ��Ч����
	IF @strResponse3 IS NOT NULL AND @strResponse3<>N''
	BEGIN
		IF @strResponse3<>@Response3
		BEGIN
			SET @strErrorDescribe=N'�������뱣���������������֤���ٴγ��ԣ�'
			RETURN 9	
		END
	END	

	SELECT 0
END

SET NOCOUNT OFF

RETURN 0
GO
