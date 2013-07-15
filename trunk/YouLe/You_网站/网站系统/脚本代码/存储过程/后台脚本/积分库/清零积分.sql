----------------------------------------------------------------------
-- ��Ȩ��2009
-- ʱ�䣺2010-03-16
-- ��;���������
----------------------------------------------------------------------
USE QPGameScoreDB
GO

IF EXISTS (SELECT * FROM DBO.SYSOBJECTS WHERE ID = OBJECT_ID(N'[dbo].[WSP_PM_GrantClearScore]') and OBJECTPROPERTY(ID, N'IsProcedure') = 1)
DROP PROCEDURE [dbo].[WSP_PM_GrantClearScore]
GO

SET QUOTED_IDENTIFIER ON 
GO

SET ANSI_NULLS ON 
GO
----------------------------------------------------------------------

CREATE PROCEDURE WSP_PM_GrantClearScore
	@MasterID INT,				-- ����Ա��ʶ
	@ClientIP VARCHAR(15),		-- ���͵�ַ
	@UserID INT,				-- �û���ʶ
	@KindID INT,				-- ��Ϸ��ʶ
	@Reason NVARCHAR(32)		-- ����ԭ��
WITH ENCRYPTION AS

-- ��������
SET NOCOUNT ON

-- �û�����
DECLARE @CurScore BIGINT

-- ������Ϣ
DECLARE @ReturnValue NVARCHAR(127)

-- ִ���߼�
BEGIN
	
	-- ��ȡ�û�����
	SELECT 	@CurScore = Score FROM GameScoreInfo WHERE UserID=@UserID
	IF @CurScore>=0 OR @CurScore IS NULL
	BEGIN
		SET @ReturnValue = N'û�и�����Ϣ������Ҫ���㣡'
		SELECT @ReturnValue
		RETURN 1
	END

	-- ������¼��Ϣ
	INSERT INTO QPRecordDBLink.QPRecordDB.dbo.RecordGrantClearScore(MasterID,ClientIP,UserID,KindID,CurScore,Reason)
	VALUES(@MasterID,@ClientIP,@UserID,@KindID,@CurScore,@Reason)

	-- �������
	UPDATE GameScoreInfo SET Score = 0 WHERE UserID=@UserID	

	SELECT ''
END
RETURN 0