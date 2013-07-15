----------------------------------------------------------------------------------------------------
-- ��Ȩ��2011
-- ʱ�䣺2011-08-31
-- ��;����������
----------------------------------------------------------------------------------------------------

USE QPAccountsDB
GO

IF EXISTS (SELECT * FROM DBO.SYSOBJECTS WHERE ID = OBJECT_ID(N'[dbo].NET_PW_ResetLogonPasswd') and OBJECTPROPERTY(ID, N'IsProcedure') = 1)
DROP PROCEDURE [dbo].NET_PW_ResetLogonPasswd
GO

IF EXISTS (SELECT * FROM DBO.SYSOBJECTS WHERE ID = OBJECT_ID(N'[dbo].NET_PW_ResetInsurePasswd') and OBJECTPROPERTY(ID, N'IsProcedure') = 1)
DROP PROCEDURE [dbo].NET_PW_ResetInsurePasswd
GO

SET QUOTED_IDENTIFIER ON 
GO

SET ANSI_NULLS ON 
GO

----------------------------------------------------------------------------------------------------
-- �һص�¼����
CREATE PROCEDURE NET_PW_ResetLogonPasswd
	@dwUserID			INT,						-- �û���ʶ
	
	@strPassword		NCHAR(32),					-- �û�����
	@strResponse1		NVARCHAR(32),				-- ������1
	@strResponse2		NVARCHAR(32),				-- ������2
	@strResponse3		NVARCHAR(32),				-- ������3
	
	@strClientIP		NVARCHAR(15),				-- ���ӵ�ַ
	@strErrorDescribe	NVARCHAR(127) OUTPUT		-- �����Ϣ
WITH ENCRYPTION AS

-- ��������
SET NOCOUNT ON

-- ������Ϣ
DECLARE @UserID			INT
DECLARE @Nullity		TINYINT
DECLARE @StunDown		TINYINT
DECLARE @ProtectID		INT
DECLARE @Response1		NVARCHAR(32)
DECLARE @Response2		NVARCHAR(32)
DECLARE @Response3		NVARCHAR(32)

-- ִ���߼�
BEGIN
	-- ��ѯ�û�	
	SELECT @UserID=UserID, @ProtectID=ProtectID, @Nullity=Nullity, @StunDown=StunDown
	FROM AccountsInfo(NOLOCK) WHERE UserID=@dwUserID

	-- �û�����
	IF @UserID IS NULL
	BEGIN
		SET @strErrorDescribe=N'�����ʺŲ����ڻ������������������֤���ٴγ��Ե�¼��'
		RETURN 1
	END	

	-- �ʺŽ�ֹ
	IF @Nullity<>0
	BEGIN
		SET @strErrorDescribe=N'�����ʺ���ʱ���ڶ���״̬������ϵ�ͷ������˽���ϸ�����'
		RETURN 2
	END	
	
	-- �ܱ�Ч��
	IF @ProtectID=0
	BEGIN
		SET @strErrorDescribe=N'�����ʺŻ�û�����롰�ʺű��������޷����С��������á���'
		RETURN 4
	END

	-- �ܱ���ѯ
	DECLARE @TmpProtectID INT
	SELECT @TmpProtectID=ProtectID, @Response1=Response1, @Response2=Response2,@Response3=Response3
	FROM AccountsProtect(NOLOCK) WHERE ProtectID=@ProtectID AND UserID=@UserID

	-- �ܱ�Ч��
	IF @TmpProtectID IS NULL
	BEGIN
		SET @strErrorDescribe=N'�����ʺŻ�û�����롰�ʺű��������޷����С��������á���'
		RETURN 5		
	END
	
	-- ����Ч
	IF ((@strResponse1 IS NULL OR @strResponse1=N'') OR
		(@strResponse2 IS NULL OR @strResponse2=N'') OR
		(@strResponse3 IS NULL OR @strResponse3=N''))
	BEGIN
		SET @strErrorDescribe=N'�������뱣���������������֤���ٴγ��ԡ��������á���'
		RETURN 6	
	END

	-- ��Ч��һ
	IF @strResponse1 IS NOT NULL AND @strResponse1<>N''
	BEGIN
		IF @strResponse1<>@Response1
		BEGIN
			SET @strErrorDescribe=N'�������뱣���������������֤���ٴγ��ԡ��������á���'
			RETURN 7	
		END
	END

	-- ��Ч���
	IF @strResponse2 IS NOT NULL AND @strResponse2<>N''
	BEGIN
		IF @strResponse2<>@Response2
		BEGIN
			SET @strErrorDescribe=N'�������뱣���������������֤���ٴγ��ԡ��������á���'
			RETURN 8	
		END
	END

	-- ��Ч����
	IF @strResponse3 IS NOT NULL AND @strResponse3<>N''
	BEGIN
		IF @strResponse3<>@Response3
		BEGIN
			SET @strErrorDescribe=N'�������뱣���������������֤���ٴγ��ԡ��������á���'
			RETURN 9	
		END
	END	

	-- ��������
	UPDATE AccountsInfo 
	SET LogonPass=@strPassword,LastLogonIP=@strClientIP
	WHERE UserID=@UserID
	
	-- ������Ϣ
	BEGIN		
		SET @strErrorDescribe=N'��ϲ���������ʺ��������óɹ��ˣ���������ʹ�������������Ϸ��¼��'
		RETURN 0
	END
END

SET NOCOUNT OFF

RETURN 0

GO

----------------------------------------------------------------------------------------------------
-- �һ���������
CREATE PROCEDURE NET_PW_ResetInsurePasswd
	@dwUserID			INT,						-- �û���ʶ

	@strInsurePass		NCHAR(32),					-- �û�����
	@strResponse1		NVARCHAR(32),				-- ������1
	@strResponse2		NVARCHAR(32),				-- ������2
	@strResponse3		NVARCHAR(32),				-- ������3

	@strClientIP		NVARCHAR(15),				-- ���ӵ�ַ
	@strErrorDescribe	NVARCHAR(127) OUTPUT		-- �����Ϣ
WITH ENCRYPTION AS

-- ��������
SET NOCOUNT ON

-- ������Ϣ
DECLARE @UserID			INT
DECLARE @Nullity		TINYINT
DECLARE @StunDown		TINYINT
DECLARE @ProtectID		INT
DECLARE @Response1		NVARCHAR(32)
DECLARE @Response2		NVARCHAR(32)
DECLARE @Response3		NVARCHAR(32)

-- ִ���߼�
BEGIN
	-- ��ѯ�û�	
	SELECT @UserID=UserID, @ProtectID=ProtectID, @Nullity=Nullity, @StunDown=StunDown
	FROM AccountsInfo(NOLOCK) WHERE UserID=@dwUserID

	-- �û�����
	IF @UserID IS NULL
	BEGIN
		SET @strErrorDescribe=N'�����ʺŲ����ڻ������������������֤���ٴγ��Ե�¼��'
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
		SET @strErrorDescribe=N'�����ʺŻ�û�����롰�ʺű��������޷����С��������á���'
		RETURN 4
	END

	-- �ܱ���ѯ
	DECLARE @TmpProtectID INT
	SELECT @TmpProtectID=ProtectID, @Response1=Response1, @Response2=Response2,@Response3=Response3
	FROM AccountsProtect(NOLOCK) WHERE ProtectID=@ProtectID AND UserID=@UserID

	-- �ܱ�Ч��
	IF @TmpProtectID IS NULL
	BEGIN
		SET @strErrorDescribe=N'�����ʺŻ�û�����롰�ʺű��������޷����С��������á���'
		RETURN 5		
	END
	
	-- ����Ч
	IF ((@strResponse1 IS NULL OR @strResponse1=N'') OR
		(@strResponse2 IS NULL OR @strResponse2=N'') OR
		(@strResponse3 IS NULL OR @strResponse3=N''))
	BEGIN
		SET @strErrorDescribe=N'�������뱣���������������֤���ٴγ��ԡ��������á���'
		RETURN 6	
	END

	-- ��Ч��һ
	IF @strResponse1 IS NOT NULL AND @strResponse1<>N''
	BEGIN
		IF @strResponse1<>@Response1
		BEGIN
			SET @strErrorDescribe=N'�������뱣���������������֤���ٴγ��ԡ��������á���'
			RETURN 7	
		END
	END

	-- ��Ч���
	IF @strResponse2 IS NOT NULL AND @strResponse2<>N''
	BEGIN
		IF @strResponse2<>@Response2
		BEGIN
			SET @strErrorDescribe=N'�������뱣���������������֤���ٴγ��ԡ��������á���'
			RETURN 8	
		END
	END

	-- ��Ч����
	IF @strResponse3 IS NOT NULL AND @strResponse3<>N''
	BEGIN
		IF @strResponse3<>@Response3
		BEGIN
			SET @strErrorDescribe=N'�������뱣���������������֤���ٴγ��ԡ��������á���'
			RETURN 9	
		END
	END	

	-- ��������
	UPDATE AccountsInfo 
	SET InsurePass=@strInsurePass,LastLogonIP=@strClientIP
	WHERE UserID=@UserID
	
	-- ������Ϣ
	BEGIN		
		SET @strErrorDescribe=N'��ϲ�������������������óɹ��ˣ���������ʹ����������вƸ�����'
		RETURN 0
	END
END

SET NOCOUNT OFF

RETURN 0

GO