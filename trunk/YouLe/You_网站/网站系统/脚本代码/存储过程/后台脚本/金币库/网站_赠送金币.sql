----------------------------------------------------------------------
-- ʱ�䣺2011-09-29
-- ��;���������ͽ��
----------------------------------------------------------------------
USE QPTreasureDB
GO

SET QUOTED_IDENTIFIER ON 
GO

SET ANSI_NULLS ON 
GO

IF EXISTS (SELECT * FROM DBO.SYSOBJECTS WHERE ID = OBJECT_ID(N'[dbo].[NET_PM_GrantTreasure]') and OBJECTPROPERTY(ID, N'IsProcedure') = 1)
DROP PROCEDURE [dbo].[NET_PM_GrantTreasure]
GO

----------------------------------------------------------------------
CREATE PROC [NET_PM_GrantTreasure]
(	
	@strUserIDList	NVARCHAR(1000),	--�û���ʶ���ַ���
	@dwAddGold		DECIMAL(18,2),	--���ͽ��
	@dwMasterID		INT,			--�����߱�ʶ
	@strReason 		NVARCHAR(32),	--����ԭ��
	@strClientIP	VARCHAR(15)		--IP��ַ
)
			
WITH ENCRYPTION AS

BEGIN
	-- ��������
	SET NOCOUNT ON

	DECLARE @dwCounts		INT,			-- ���Ͷ��������	
			@dwTotalGold	DECIMAL(18,2),	-- ���͵��ܽ��
			@dtCurrentDate	DATETIME		-- ��������
	SET @dtCurrentDate =  GETDATE()
	
	
	-- ִ���߼�
	BEGIN TRY
	-- ��֤
	IF @dwAddGold IS NULL OR @dwAddGold = 0
		RETURN -2;		-- ���ͽ���Ϊ��
	SELECT @dwCounts=COUNT(*) FROM dbo.WF_Split(@strUserIDList,',')
	IF @dwCounts<=0 
		RETURN -3;		-- δѡ�����Ͷ���
	SET @dwTotalGold = @dwCounts * @dwAddGold	
	
	BEGIN TRAN
			--�������ͽ�Ҽ�¼		
			INSERT QPRecordDB.dbo.RecordGrantTreasure(MasterID,ClientIP,CollectDate,UserID,CurGold,AddGold,Reason)
				SELECT @dwMasterID,@strClientIP,@dtCurrentDate,
						a.rs,ISNULL(b.InsureScore,0),@dwAddGold,@strReason
				FROM WF_Split(@strUserIDList,',') a LEFT JOIN GameScoreInfo b ON a.rs = b.UserID			 
			
			--����������н��
			UPDATE GameScoreInfo SET InsureScore=(CASE WHEN InsureScore+@dwAddGold<0 THEN 0 WHEN InsureScore+@dwAddGold>=0 THEN InsureScore+@dwAddGold end) 
			WHERE UserID IN (SELECT rs FROM dbo.WF_Split(@strUserIDList,','))
			
			--û�н�Ҽ�¼��������н�Ҹ���
			INSERT INTO GameScoreInfo(UserID,InsureScore) 
			SELECT rs,@dwAddGold FROM dbo.WF_Split(@strUserIDList,',') WHERE rs NOT IN (SELECT UserID FROM dbo.GameScoreInfo)
			
		
	COMMIT TRAN			
		RETURN 0;--�ɹ�
	END TRY
	BEGIN CATCH
		IF @@TRANCOUNT > 0
		BEGIN
			ROLLBACK TRAN
		END
		RETURN -1;    --δ֪����������
	END CATCH
END
GO

