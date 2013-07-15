----------------------------------------------------------------------------------------------------
-- ��Ȩ��2011
-- ʱ�䣺2011-08-31
-- ��;���޸�����
----------------------------------------------------------------------------------------------------

USE QPAccountsDB
GO

IF EXISTS (SELECT * FROM DBO.SYSOBJECTS WHERE ID = OBJECT_ID(N'[dbo].NET_PW_ModifyLogonPass') and OBJECTPROPERTY(ID, N'IsProcedure') = 1)
DROP PROCEDURE [dbo].NET_PW_ModifyLogonPass
GO

IF EXISTS (SELECT * FROM DBO.SYSOBJECTS WHERE ID = OBJECT_ID(N'[dbo].NET_PW_ModifyInsurePass') and OBJECTPROPERTY(ID, N'IsProcedure') = 1)
DROP PROCEDURE [dbo].NET_PW_ModifyInsurePass
GO

SET QUOTED_IDENTIFIER ON 
GO

SET ANSI_NULLS ON 
GO

----------------------------------------------------------------------------------------------------

-- �޸ĵ�¼����
CREATE PROCEDURE NET_PW_ModifyLogonPass
	@dwUserID INT,								-- �û� I D

	@strSrcPassword NCHAR(32),					-- �û�����
	@strDesPassword NCHAR(32),					-- �û�����

	@strClientIP NVARCHAR(15),					-- ���ӵ�ַ
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
	DECLARE @LogonPass AS NCHAR(32)
	SELECT @UserID=UserID, @LogonPass=LogonPass, @Nullity=Nullity, @StunDown=StunDown
	FROM AccountsInfo(NOLOCK) WHERE UserID=@dwUserID

	-- ��ѯ�û������ж�����
	IF @UserID IS NULL OR @LogonPass<>@strSrcPassword
	BEGIN
		SET @strErrorDescribe=N'ԭ��¼�����������,���������룡'
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

	-- �޸�����
	UPDATE AccountsInfo SET LogonPass=@strDesPassword WHERE UserID=@UserID
	
	-- ��Ӽ�¼
	INSERT INTO QPRecordDB.dbo.RecordPasswdExpend(OperMasterID,UserID,ReLogonPasswd,ReInsurePasswd,ClientIP,CollectDate)
	VALUES(0,@dwUserID,@strDesPassword,'',@strClientIP,GETDATE())

	-- ������Ϣ	
	SET @strErrorDescribe= N'��ϲ�������ĵ�¼�����޸ĳɹ��ˣ�'

END

RETURN 0

GO

----------------------------------------------------------------------------------------------------

-- �޸���������
CREATE PROCEDURE NET_PW_ModifyInsurePass
	@dwUserID INT,								-- �û� I D

	@strSrcPassword NCHAR(32),					-- �û�����
	@strDesPassword NCHAR(32),					-- �û�����

	@strClientIP NVARCHAR(15),					-- ���ӵ�ַ
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
	DECLARE @InsurePass AS NCHAR(32)
	SELECT @UserID=UserID, @InsurePass=InsurePass, @Nullity=Nullity, @StunDown=StunDown
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
	
	-- �����ж�
	IF @InsurePass<>@strSrcPassword
	BEGIN
		SET @strErrorDescribe=N'�����������������������֤���ٴγ��ԣ�'
		RETURN 4
	END

	-- �޸�����
	UPDATE AccountsInfo SET InsurePass=@strDesPassword WHERE UserID=@UserID
	
	-- ��Ӽ�¼
	INSERT INTO QPRecordDB.dbo.RecordPasswdExpend(OperMasterID,UserID,ReLogonPasswd,ReInsurePasswd,ClientIP,CollectDate)
	VALUES(0,@dwUserID,'',@strDesPassword,@strClientIP,GETDATE())

	-- ������Ϣ	
	SET @strErrorDescribe= N'��ϲ�����������������޸ĳɹ��ˣ�'

END

RETURN 0

GO