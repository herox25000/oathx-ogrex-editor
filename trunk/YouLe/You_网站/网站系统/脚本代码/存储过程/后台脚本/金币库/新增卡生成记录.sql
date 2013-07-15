----------------------------------------------------------------------
-- ʱ�䣺2010-03-16
-- ��;�����������ɼ�¼
----------------------------------------------------------------------

USE QPTreasureDB
GO

IF EXISTS (SELECT * FROM DBO.SYSOBJECTS WHERE ID = OBJECT_ID(N'[dbo].[WSP_PM_BuildStreamAdd]') and OBJECTPROPERTY(ID, N'IsProcedure') = 1)
DROP PROCEDURE [dbo].[WSP_PM_BuildStreamAdd]
GO

SET QUOTED_IDENTIFIER ON 
GO

SET ANSI_NULLS ON 
GO

----------------------------------------------------------------------

CREATE PROCEDURE WSP_PM_BuildStreamAdd
	@AdminName nvarchar(31),	-- ����Ա�û���
	@CardTypeID int,			-- ʵ�����
	@CardPrice decimal(18,2),	-- ʵ���۸�
	@CardGold bigint,			-- ʵ�����
	@BuildCount int,			-- ��������
	@BuildAddr nvarchar(15),	-- ���ɵ�ַ
	@NoteInfo nvarchar(128),	-- ��ע��Ϣ
	@BuildCardPacket image		-- ʵ����Ϣ
WITH ENCRYPTION AS

-- ��������
SET NOCOUNT ON

-- ִ���߼�
BEGIN
	INSERT INTO LivcardBuildStream(
		AdminName,CardTypeID,CardPrice,CardGold,BuildCount,BuildAddr,NoteInfo,BuildCardPacket)
	VALUES(
		@AdminName,@CardTypeID,@CardPrice,@CardGold,@BuildCount,@BuildAddr,@NoteInfo,@BuildCardPacket)

	SELECT SCOPE_IDENTITY()
END
RETURN 0