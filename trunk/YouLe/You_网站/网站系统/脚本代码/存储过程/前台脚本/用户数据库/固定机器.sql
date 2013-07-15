----------------------------------------------------------------------------------------------------
-- ��Ȩ��2011
-- ʱ�䣺2011-08-31
-- ��;���̶�����
----------------------------------------------------------------------------------------------------

USE QPAccountsDB
GO

IF EXISTS (SELECT * FROM DBO.SYSOBJECTS WHERE ID = OBJECT_ID(N'[dbo].NET_PW_ApplyMoorMachine') and OBJECTPROPERTY(ID, N'IsProcedure') = 1)
DROP PROCEDURE [dbo].NET_PW_ApplyMoorMachine
GO

IF EXISTS (SELECT * FROM DBO.SYSOBJECTS WHERE ID = OBJECT_ID(N'[dbo].NET_PW_CancelMoorMachine') and OBJECTPROPERTY(ID, N'IsProcedure') = 1)
DROP PROCEDURE [dbo].NET_PW_CancelMoorMachine
GO

SET QUOTED_IDENTIFIER ON 
GO

SET ANSI_NULLS ON 
GO

----------------------------------------------------------------------------------------------------

-- �����
CREATE PROCEDURE NET_PW_ApplyMoorMachine
	@dwUserID			INT,					-- �û���ʶ

	@strResponse1		NVARCHAR(32),			-- �ܱ���1
	@strResponse2		NVARCHAR(32),			-- �ܱ���2
	@strResponse3		NVARCHAR(32),			-- �ܱ���3

	@strClientIP		NVARCHAR(15),			-- ���ӵ�ַ
	@strErrorDescribe	NVARCHAR(127) OUTPUT	-- �����Ϣ
WITH ENCRYPTION AS

-- ��������
SET NOCOUNT ON

-- ������Ϣ
DECLARE @UserID			INT
DECLARE @Nullity		TINYINT
DECLARE @StunDown		TINYINT
DECLARE @MoorMachine	TINYINT

-- �ܱ���Ϣ
DECLARE @ProtectID		INT
DECLARE @Response1		NVARCHAR(32)
DECLARE @Response2		NVARCHAR(32)
DECLARE @Response3		NVARCHAR(32)

-- ִ���߼�
BEGIN	
	-- ��ѯ�û�	
	SELECT @UserID=UserID, @ProtectID=ProtectID,@Nullity=Nullity, @StunDown=StunDown, @MoorMachine=MoorMachine
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

	-- ���÷���
	UPDATE AccountsInfo 
	SET MoorMachine=2,LastLogonIP=@strClientIP,LastLogonDate=GETDATE()
	WHERE UserID=@UserID

	-- ������Ϣ
	SET @strErrorDescribe= N'��ϲ�������̶���������������ɹ��ˣ�����������ʹ�ÿͻ��˵�¼��Ϸ�����ǽ���Ϊ����ɻ����İ󶨹�����'
END
RETURN 0

GO

----------------------------------------------------------------------------------------------------
-- �����
CREATE PROCEDURE NET_PW_CancelMoorMachine
	@dwUserID			INT,					-- �û���ʶ

	@strResponse1		NVARCHAR(32),			-- �ܱ���1
	@strResponse2		NVARCHAR(32),			-- �ܱ���2
	@strResponse3		NVARCHAR(32),			-- �ܱ���3

	@strClientIP		NVARCHAR(15),			-- ���ӵ�ַ
	@strErrorDescribe	NVARCHAR(127) OUTPUT	-- �����Ϣ
WITH ENCRYPTION AS

-- ��������
SET NOCOUNT ON

-- ������Ϣ
DECLARE @UserID			INT
DECLARE @Nullity		TINYINT
DECLARE @StunDown		TINYINT
DECLARE @MoorMachine	TINYINT

-- �ܱ���Ϣ
DECLARE @ProtectID		INT
DECLARE @Response1		NVARCHAR(32)
DECLARE @Response2		NVARCHAR(32)
DECLARE @Response3		NVARCHAR(32)

-- ��������
DECLARE @ErrorDescribe AS NVARCHAR(128)

-- ִ���߼�
BEGIN	
	-- ��ѯ�û�	
	SELECT @UserID=UserID, @ProtectID=ProtectID,@Nullity=Nullity, @StunDown=StunDown, @MoorMachine=MoorMachine
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

	-- �������
	UPDATE AccountsInfo 
	SET MoorMachine=0,LastLogonIP=@strClientIP,LastLogonDate=GETDATE()
	WHERE UserID=@UserID

	-- ������Ϣ
	SET @strErrorDescribe= N'��ϲ�������̶�����������ɹ��ˣ�'
END
RETURN 0

GO
