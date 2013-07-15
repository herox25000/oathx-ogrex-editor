
----------------------------------------------------------------------
-- ʱ�䣺2011-09-26
-- ��;������Ա��¼
----------------------------------------------------------------------
USE QPPlatformManagerDB
GO

SET QUOTED_IDENTIFIER ON 
GO

SET ANSI_NULLS ON 
GO

IF EXISTS (SELECT * FROM DBO.SYSOBJECTS WHERE ID = OBJECT_ID(N'[dbo].[NET_PM_UserLogon]') and OBJECTPROPERTY(ID, N'IsProcedure') = 1)
DROP PROCEDURE [dbo].[NET_PM_UserLogon]
GO
-----------------------------------------------------------------------
CREATE PROC [NET_PM_UserLogon]
	@strUserName		NVARCHAR(31),					-- ����Ա�ʺ�
	@strPassword		NCHAR(32),						-- ��¼����
	@strClientIP		NVARCHAR(15),					-- ��¼IP
	@strErrorDescribe	NVARCHAR(127) OUTPUT			-- �����Ϣ
WITH ENCRYPTION AS

-- ��������
SET NOCOUNT ON

-- ִ���߼�
BEGIN	

	-- �û�����
	IF @strUserName IS NULL OR @strUserName=N'' OR @strPassword IS NULL OR @strPassword=N''
	BEGIN
		SET @strErrorDescribe = N'��Ǹ�����Ĺ����ʺŲ����ڻ������������������֤���ٴγ��Ե�¼��'
		RETURN 100
	END		
	IF NOT EXISTS (SELECT * FROM Base_Users WHERE UserName=@strUserName AND [Password]=@strPassword)
	BEGIN
		SET @strErrorDescribe = N'��Ǹ�����Ĺ����ʺŲ����ڻ������������������֤���ٴγ��Ե�¼��'
		RETURN 100
	END 
	
	DECLARE @IsBand INT 
	DECLARE @BandIP NVARCHAR(15)
	DECLARE @Nullity INT 
	
	SELECT @IsBand=IsBand,@BandIP=BandIP,@Nullity=Nullity FROM Base_Users WHERE UserName=@strUserName
	
	IF @IsBand = 0 AND @BandIP <> @strClientIP
	BEGIN
		SET @strErrorDescribe = N'��Ǹ�����Ĺ����ʺ��Ѿ���ָ����IP��ַ��¼��'
		RETURN 101
	END
	-- �ʺŽ�ֹ
	IF @Nullity<>0
	BEGIN
		SET @strErrorDescribe = N'��Ǹ�������ʺ��ѱ���ֹʹ�ã�����ϵ����Ա�˽���ϸ�����'
		RETURN 102
	END
	-- ���µ�¼
	UPDATE Base_Users SET LoginTimes=LoginTimes+1,PreLogintime=LastLogintime,PreLoginIP=LastLoginIP, LastLoginTime=GETDATE(),LastLoginIP=@strClientIP
	WHERE UserName=@strUserName
	-- ��¼��־
	INSERT dbo.SystemSecurity
	        ( OperatingTime ,
	          OperatingName ,
	          OperatingIP ,
	          OperatingAccounts
	        )
	VALUES  ( GETDATE() , -- OperatingTime - datetime
	          '��¼' , -- OperatingName - nvarchar(50)
	          @strClientIP , -- OperatingIP - nvarchar(50)
	          @strUserName  -- OperatingAccounts - nvarchar(50)
	        )
	-- ���
	SELECT a.* FROM Base_Users a INNER JOIN dbo.Base_Roles b ON a.RoleID=b.RoleID
	WHERE a.UserName=@strUserName	
	
END
RETURN 0
GO