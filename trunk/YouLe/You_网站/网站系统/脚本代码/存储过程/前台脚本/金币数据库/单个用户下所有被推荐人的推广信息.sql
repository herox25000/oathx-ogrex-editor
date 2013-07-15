----------------------------------------------------------------------
-- ��Ȩ��2011
-- ʱ�䣺2011-09-20
-- ��;����ҳ��ʾ�����û������б��Ƽ��˵��ƹ���Ϣ
----------------------------------------------------------------------
USE QPTreasureDB
GO

SET QUOTED_IDENTIFIER ON 
GO

SET ANSI_NULLS ON 
GO

IF EXISTS (SELECT * FROM DBO.SYSOBJECTS WHERE ID = OBJECT_ID(N'[dbo].NET_PW_GetAllChildrenInfoByUserID') and OBJECTPROPERTY(ID, N'IsProcedure') = 1)
DROP PROCEDURE [dbo].NET_PW_GetAllChildrenInfoByUserID
GO

----------------------------------------------------------------------
CREATE PROC NET_PW_GetAllChildrenInfoByUserID
	@dwUserID		INT,				--	�û���ʶ
	@dwPageSize		INT=10 ,			--ÿҳ��¼����
	@dwPageIndex	INT=1 				--��ǰҳ��		
WITH ENCRYPTION AS

BEGIN
	-- ��������
	SET NOCOUNT ON;
	
	--�������
	DECLARE @dwStart INT,@dwEnd INT		
	DECLARE @Record INT;
	
	--����ҳ��	
	SET  @dwStart = (@dwPageIndex - 1)*@dwPageSize + 1;
	SET  @dwEnd = @dwPageSize * @dwPageIndex;
	
	SELECT @Record=COUNT(*) FROM RecordSpreadInfo WHERE UserID = @dwUserID AND ChildrenID <> 0 GROUP BY ChildrenID
	SELECT @Record AS Records
	SELECT Score,ChildrenID,CollectDate FROM (
		SELECT ROW_NUMBER() OVER(ORDER BY ChildrenID DESC) AS TempID,SUM(Score) AS Score, ChildrenID, min(CollectDate) AS CollectDate
		FROM RecordSpreadInfo 
		WHERE UserID = @dwUserID AND ChildrenID <> 0 GROUP BY ChildrenID) AS TC
	WHERE TC.TempID BETWEEN @dwStart AND @dwEnd
	
END

