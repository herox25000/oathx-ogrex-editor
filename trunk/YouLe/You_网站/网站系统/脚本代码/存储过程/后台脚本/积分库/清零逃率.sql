----------------------------------------------------------------------
-- ��Ȩ��2009
-- ʱ�䣺2010-03-16
-- ��;����������
----------------------------------------------------------------------
USE QPGameScoreDB
GO

IF EXISTS (SELECT * FROM DBO.SYSOBJECTS WHERE ID = OBJECT_ID(N'[dbo].[WSP_PM_GrantClearFlee]') and OBJECTPROPERTY(ID, N'IsProcedure') = 1)
DROP PROCEDURE [dbo].[WSP_PM_GrantClearFlee]
GO

SET QUOTED_IDENTIFIER ON 
GO

SET ANSI_NULLS ON 
GO
----------------------------------------------------------------------

CREATE PROCEDURE WSP_PM_GrantClearFlee
	@MasterID INT,				-- ����Ա��ʶ
	@ClientIP VARCHAR(15),		-- �����ַ
	@UserID INT,				-- �û���ʶ
	@KindID INT,				-- ��Ϸ��ʶ
	@Reason NVARCHAR(32)		-- ����ԭ��
WITH ENCRYPTION AS

-- ��������
SET NOCOUNT ON

-- �û����ܴ���
DECLARE @CurFlee INT

-- ������Ϣ
DECLARE @ReturnValue NVARCHAR(127)

-- ִ���߼�
BEGIN
	
	-- ��ȡ�û����ʴ���
	SELECT @CurFlee = FleeCount FROM GameScoreInfo WHERE UserID=@UserID
	IF @CurFlee = 0 OR @CurFlee IS NULL
	BEGIN
		SET @ReturnValue = N'û�����ܼ�¼������Ҫ���㣡'
		SELECT @ReturnValue
		RETURN 1
	END

	-- ������¼��Ϣ
	INSERT INTO QPRecordDBLink.QPRecordDB.dbo.RecordGrantClearFlee(MasterID,ClientIP,UserID,KindID,CurFlee,Reason)
	VALUES(@MasterID,@ClientIP,@UserID,@KindID,@CurFlee,@Reason)

	-- ��������
	UPDATE GameScoreInfo SET FleeCount = 0 WHERE UserID=@UserID	

	SELECT ''
END
RETURN 0
