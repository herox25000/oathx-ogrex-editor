----------------------------------------------------------------------
-- ʱ�䣺2010-03-16
-- ��;�����ͽ��
----------------------------------------------------------------------

USE QPRecordDB
GO

IF EXISTS (SELECT * FROM DBO.SYSOBJECTS WHERE ID = OBJECT_ID(N'[dbo].[WSP_PM_GrantTreasure]') and OBJECTPROPERTY(ID, N'IsProcedure') = 1)
DROP PROCEDURE [dbo].[WSP_PM_GrantTreasure]
GO

SET QUOTED_IDENTIFIER ON 
GO

SET ANSI_NULLS ON 
GO
----------------------------------------------------------------------

CREATE PROCEDURE WSP_PM_GrantTreasure
	@MasterID INT,				-- ����Ա��ʶ
	@ClientIP VARCHAR(15),		-- ���͵�ַ
	@UserID INT,				-- �û���ʶ
	@AddGold BIGINT,			-- ���ͽ��
	@Reason NVARCHAR(32)		-- ����ԭ��	
WITH ENCRYPTION AS

-- ��������
SET NOCOUNT ON

-- �û������Ϣ
DECLARE @CurGold BIGINT

-- ִ���߼�
BEGIN
	
	-- ��ȡ�û������Ϣ
	SELECT @CurGold = InsureScore FROM QPTreasureDBLink.QPTreasureDB.dbo.GameScoreInfo
	WHERE UserID = @UserID
	If @CurGold IS NULL
	BEGIN
		SET @CurGold = 0
	END

	IF @CurGold+@AddGold<0
	BEGIN
		RETURN -1
	END 

	-- ������¼��Ϣ
	INSERT INTO RecordGrantTreasure(MasterID,ClientIP,UserID,CurGold,AddGold,Reason)
	VALUES(@MasterID,@ClientIP,@UserID,@CurGold,@AddGold,@Reason)

	-- ���ͽ��
	UPDATE QPTreasureDBLink.QPTreasureDB.dbo.GameScoreInfo SET InsureScore = InsureScore + @AddGold
	WHERE UserID = @UserID
	
	IF @@ROWCOUNT = 0
	BEGIN
		INSERT INTO QPTreasureDBLink.QPTreasureDB.dbo.GameScoreInfo(UserID,InsureScore,RegisterIP,LastLogonIP)
		VALUES(@UserID,@AddGold,@ClientIP,@ClientIP)
	END
END
RETURN 0

