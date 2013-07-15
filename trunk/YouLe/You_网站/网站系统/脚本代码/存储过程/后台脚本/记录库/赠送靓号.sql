----------------------------------------------------------------------
-- ʱ�䣺2010-03-16
-- ��;����������
----------------------------------------------------------------------
USE QPRecordDB
GO

IF EXISTS (SELECT * FROM DBO.SYSOBJECTS WHERE ID = OBJECT_ID(N'[dbo].[WSP_PM_GrantGameID]') and OBJECTPROPERTY(ID, N'IsProcedure') = 1)
DROP PROCEDURE [dbo].[WSP_PM_GrantGameID]
GO

SET QUOTED_IDENTIFIER ON 
GO

SET ANSI_NULLS ON 
GO
----------------------------------------------------------------------


CREATE PROCEDURE WSP_PM_GrantGameID
	@MasterID INT,								-- ����Ա��ʶ
	@UserID INT,								-- �û���ʶ
	@ReGameID INT,								-- ����ID
	@ClientIP VARCHAR(15),						-- ���͵�ַ
	@Reason NVARCHAR(32)						-- ����ԭ��
WITH ENCRYPTION AS

-- ��������
SET NOCOUNT ON

-- �û���Ϣ
DECLARE @CurGameID BIGINT
DECLARE @dwUserID INT

-- ����ID��Ϣ
DECLARE @dwGameID INT
DECLARE @IDLevel INT

-- ���ز���
DECLARE @ReturnValue NVARCHAR(127)

-- ִ���߼�
BEGIN
	
	-- ��ȡ�û���ϷID
	SELECT @CurGameID = GameID FROM QPAccountsDBLink.QPAccountsDB.dbo.AccountsInfo
	WHERE UserID = @UserID

	-- �ж�
	SELECT @dwGameID = GameID,@IDLevel = IDLevel FROM QPAccountsDBLink.QPAccountsDB.dbo.ReserveIdentifier
	WHERE GameID = @ReGameID
	IF @dwGameID IS NULL
	BEGIN
		SET @ReturnValue = N'���͵����Ų����ڣ�'
		SELECT @ReturnValue
		RETURN 1
	END

	SELECT @dwUserID = UserID FROM QPAccountsDBLink.QPAccountsDB.dbo.AccountsInfo
	WHERE GameID = @ReGameID
	IF @dwUserID IS NOT NULL
	BEGIN
		SET @ReturnValue = N'���͵������ѱ�ʹ�ã��������'
		SELECT @ReturnValue
		RETURN 2
	END	

	-- ������¼
	INSERT INTO RecordGrantGameID(MasterID,UserID,CurGameID,ReGameID,IDLevel,ClientIP,Reason)
	VALUES(@MasterID,@UserID,@CurGameID,@ReGameID,@IDLevel,@ClientIP,@Reason)

	-- ���±�����
	UPDATE QPAccountsDBLink.QPAccountsDB.dbo.ReserveIdentifier SET Distribute = 1 
	WHERE GameID = @ReGameID

	-- �����û���
	UPDATE QPAccountsDBLink.QPAccountsDB.dbo.AccountsInfo SET GameID = @ReGameID
	WHERE UserID = @UserID

	SELECT @ReturnValue
END
RETURN 0