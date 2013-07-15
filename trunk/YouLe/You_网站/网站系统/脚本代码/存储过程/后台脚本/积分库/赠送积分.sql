----------------------------------------------------------------------
-- ��Ȩ��2009
-- ʱ�䣺2010-03-16
-- ��;�����ͻ���
----------------------------------------------------------------------

USE QPGameScoreDB
GO

IF EXISTS (SELECT * FROM DBO.SYSOBJECTS WHERE ID = OBJECT_ID(N'[dbo].[WSP_PM_GrantGameScore]') and OBJECTPROPERTY(ID, N'IsProcedure') = 1)
DROP PROCEDURE [dbo].[WSP_PM_GrantGameScore]
GO

SET QUOTED_IDENTIFIER ON 
GO

SET ANSI_NULLS ON 
GO
----------------------------------------------------------------------

CREATE PROCEDURE WSP_PM_GrantGameScore
	@MasterID INT,				-- ����Ա��ʶ
	@ClientIP VARCHAR(15),		-- ���͵�ַ	
	@UserID INT,				-- �û���ʶ
	@KindID INT,				-- ��Ϸ��ʶ
	@AddScore BIGINT,			-- ���ͻ���
	@Reason NVARCHAR(32)		-- ����ԭ��
	
WITH ENCRYPTION AS

-- ��������
SET NOCOUNT ON

-- �û�����
DECLARE @CurScore BIGINT

-- ִ���߼�
BEGIN
	
	-- ��ȡ�û�����
	SELECT 	@CurScore = Score FROM GameScoreInfo WHERE UserID=@UserID
	IF @CurScore IS NULL
	BEGIN
		SET @CurScore = 0
	END

	-- ������¼��Ϣ
	INSERT INTO QPRecordDBLink.QPRecordDB.dbo.RecordGrantGameScore(MasterID,ClientIP,UserID,KindID,CurScore,AddScore,Reason)
	VALUES(@MasterID,@ClientIP,@UserID,@KindID,@CurScore,@AddScore,@Reason)

	-- ���ͻ���
	UPDATE GameScoreInfo SET Score = Score + @AddScore
	WHERE UserID=@UserID
	
	IF @@ROWCOUNT = 0 
	BEGIN
		INSERT INTO GameScoreInfo(UserID,Score,RegisterIP,LastLogonIP)
		VALUES(@UserID,@AddScore,@ClientIP,@ClientIP)
	END
END
RETURN 0