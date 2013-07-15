----------------------------------------------------------------------
-- ʱ�䣺2010-03-16
-- ��;�����;���
----------------------------------------------------------------------

USE QPRecordDB
GO

IF EXISTS (SELECT * FROM DBO.SYSOBJECTS WHERE ID = OBJECT_ID(N'[dbo].[WSP_PM_GrantExperience]') and OBJECTPROPERTY(ID, N'IsProcedure') = 1)
DROP PROCEDURE [dbo].[WSP_PM_GrantExperience]
GO

SET QUOTED_IDENTIFIER ON 
GO

SET ANSI_NULLS ON 
GO
----------------------------------------------------------------------
CREATE PROCEDURE WSP_PM_GrantExperience
	@MasterID INT,				-- ����Ա��ʶ
	@ClientIP VARCHAR(15),		-- ���͵�ַ
	@UserID INT,				-- �û���ʶ
	@AddExperience INT,			-- ���;���
	@Reason NVARCHAR(32)		-- ����ԭ��
WITH ENCRYPTION AS

-- ��������
SET NOCOUNT ON

-- �û�����
DECLARE @CurExperience INT

-- ִ���߼�
BEGIN
	
	-- ��ȡ�û�����
	SELECT @CurExperience = Experience FROM QPAccountsDBLink.QPAccountsDB.dbo.AccountsInfo
	WHERE UserID = @UserID

	-- ������¼��Ϣ
	INSERT INTO RecordGrantExperience(MasterID,ClientIP,UserID,CurExperience,AddExperience,Reason)
	VALUES(@MasterID,@ClientIP,@UserID,@CurExperience,@AddExperience,@Reason)

	-- ���;���
	UPDATE QPAccountsDBLink.QPAccountsDB.dbo.AccountsInfo SET Experience = Experience + @AddExperience
	WHERE UserID = @UserID
END
RETURN 0
