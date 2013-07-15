----------------------------------------------------------------------------------------------------
-- ��Ȩ��2011
-- ʱ�䣺2011-09-02
-- ��;����������
----------------------------------------------------------------------------------------------------
USE QPGameScoreDB
GO

IF EXISTS (SELECT * FROM DBO.SYSOBJECTS WHERE ID = OBJECT_ID(N'[dbo].NET_PW_ResetGameScore') and OBJECTPROPERTY(ID, N'IsProcedure') = 1)
DROP PROCEDURE [dbo].NET_PW_ResetGameScore
GO

SET QUOTED_IDENTIFIER ON
GO

SET ANSI_NULLS ON
GO

---------------------------------------------------------------------------------------
--	��������
CREATE  PROCEDURE dbo.NET_PW_ResetGameScore
	@dwUserID INT,		-- �û���ʶ

	@strClientIP VARCHAR(15),				-- ��ַ
	@strErrorDescribe	NVARCHAR(127) OUTPUT		-- �����Ϣ
WITH ENCRYPTION AS

-- ��������
SET NOCOUNT ON

-- �û���Ϣ
DECLARE @UserID INT
DECLARE @Nullity BIT
DECLARE @StunDown BIT
DECLARE @MemberOrder TINYINT

-- �û�����
DECLARE @Score BIGINT

BEGIN
	-- ��ѯ�û�
	SELECT @UserID=UserID, @Nullity=Nullity, @StunDown=StunDown,@MemberOrder=MemberOrder
	FROM QPAccountsDBLink.QPAccountsDB.dbo.AccountsInfo WHERE UserID=@dwUserID

	-- ��ѯ�û�
	IF @UserID IS NULL
	BEGIN
		SET @strErrorDescribe=N'�����ʺŲ����ڻ������������������֤���ٴγ��Ե�¼��'
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

	-- �ǻ�Ա
	IF @MemberOrder=0
	BEGIN
		SET @strErrorDescribe=N'�����ʺŲ��ǻ�Ա�����뿪ͨ��Ա�����ʹ�øù��ܣ�'
		RETURN 4
	END

	-- ��ѯ����
	SELECT @Score=Score FROM GameScoreInfo(NOLOCK) WHERE UserID=@dwUserID

	-- �����ж�
	IF @Score IS NULL OR @Score>=0
	BEGIN
		SET @strErrorDescribe=N'��ϲ��������Ϸ�ɼ����ֵķǳ��ã�û�и�����Ҫ���㡣'
		RETURN 5
	END
	
	UPDATE GameScoreInfo SET Score=0 WHERE UserID=@dwUserID

	SET @strErrorDescribe=N'��������ɹ���' 
END

SET NOCOUNT OFF

RETURN 0
GO