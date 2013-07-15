----------------------------------------------------------------------------------------------------
-- ��Ȩ��2011
-- ʱ�䣺2011-09-02
-- ��;�����ⷴ��
----------------------------------------------------------------------------------------------------
USE QPNativeWebDB
GO

IF EXISTS (SELECT * FROM DBO.SYSOBJECTS WHERE ID = OBJECT_ID(N'[dbo].NET_PW_AddGameFeedback') and OBJECTPROPERTY(ID, N'IsProcedure') = 1)
DROP PROCEDURE [dbo].NET_PW_AddGameFeedback
GO

SET QUOTED_IDENTIFIER ON 
GO

SET ANSI_NULLS ON 
GO

----------------------------------------------------------------------------------------------------
-- ���ⷴ��
CREATE PROCEDURE NET_PW_AddGameFeedback
	@strAccounts	NVARCHAR(31),			-- �û��ʺ�

	@strTitle		NVARCHAR(512),			-- ��������
	@strContent		NVARCHAR(4000),			-- ��������

	@strClientIP	NVARCHAR(15),			-- ������ַ
	@strErrorDescribe	NVARCHAR(127) OUTPUT	--�����Ϣ	
WITH ENCRYPTION AS

-- ��������
SET NOCOUNT ON

-- ������Ϣ
DECLARE @UserID INT
DECLARE @Nullity BIT
DECLARE @StunDown BIT

-- ִ���߼�
BEGIN
	IF @strAccounts<>''
	BEGIN
		-- ��ѯ�û�
		SELECT @UserID=UserID,@Nullity=Nullity, @StunDown=StunDown
		FROM QPAccountsDBLink.QPAccountsDB.dbo.AccountsInfo WHERE Accounts=@strAccounts

		-- �û�����
		IF @UserID IS NULL
		BEGIN
			SET @strErrorDescribe=N'�����ʺŲ����ڣ����֤���ٴ����룡'
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
	END	

	-- ��������
	INSERT INTO GameFeedbackInfo(FeedbackTitle,FeedbackContent,Accounts,ClientIP,Nullity)
	VALUES(@strTitle,@strContent,@strAccounts,@strClientIP,1)

	SET @strErrorDescribe=N'���ⷴ�������ɹ���'
END
RETURN 0
GO