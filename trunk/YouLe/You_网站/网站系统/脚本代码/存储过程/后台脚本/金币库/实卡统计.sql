----------------------------------------------------------------------
-- ʱ�䣺2010-03-16
-- ��;�������ͳ��
----------------------------------------------------------------------

USE QPTreasureDB
GO

IF EXISTS (SELECT * FROM DBO.SYSOBJECTS WHERE ID = OBJECT_ID(N'[dbo].[WSP_PM_LivcardStat]') and OBJECTPROPERTY(ID, N'IsProcedure') = 1)
DROP PROCEDURE [dbo].[WSP_PM_LivcardStat]

IF EXISTS (SELECT * FROM DBO.SYSOBJECTS WHERE ID = OBJECT_ID(N'[dbo].[NET_PM_LivcardStatByBuildID]') and OBJECTPROPERTY(ID, N'IsProcedure') = 1)
DROP PROCEDURE [dbo].[NET_PM_LivcardStatByBuildID]
GO

SET QUOTED_IDENTIFIER ON 
GO

SET ANSI_NULLS ON 
GO

----------------------------------------------------------------------

CREATE PROCEDURE WSP_PM_LivcardStat

WITH ENCRYPTION AS

-- ��������
SET NOCOUNT ON
-- ִ���߼�
BEGIN
	SELECT	CardTypeID,
		COUNT (CardID) AS TotalCount,
		SUM(CASE WHEN ApplyDate IS NOT NULL THEN 1 ELSE 0 END) AS TotalUsed,
		SUM(CASE WHEN ApplyDate IS NOT NULL THEN 0 ELSE 1 END) AS TotalNoUsed,
		SUM(CASE WHEN ValidDate<getdate() AND ApplyDate IS NULL THEN 1 ELSE 0 END) AS TotalOut,
		SUM(CASE WHEN Nullity=1 AND ApplyDate IS NULL THEN 1 ELSE 0 END) AS TotalNullity,
		SUM(CardPrice) AS TotalPrice,
		SUM(CardGold) AS TotalGold
	FROM LivcardAssociator(NOLOCK)
	GROUP BY CardTypeID 
	WITH CUBE
END
RETURN 0
GO
----------------------------------------------------------------------

CREATE PROCEDURE [NET_PM_LivcardStatByBuildID]
		@BuildID int --����
WITH ENCRYPTION AS

-- ��������
SET NOCOUNT ON
-- ִ���߼�
BEGIN
	IF @BuildID = 0
	BEGIN
		SELECT
			COUNT (CardID) AS TotalCount,
			SUM(CASE WHEN ApplyDate IS NOT NULL THEN 1 ELSE 0 END) AS TotalUsed,
			SUM(CASE WHEN ApplyDate IS NOT NULL THEN 0 ELSE 1 END) AS TotalNoUsed,
			SUM(CASE WHEN ValidDate<getdate() AND ApplyDate IS NULL THEN 1 ELSE 0 END) AS TotalOut,
			SUM(CASE WHEN Nullity=1 AND ApplyDate IS NULL THEN 1 ELSE 0 END) AS TotalNullity,
			SUM(CardPrice) AS TotalPrice,
			SUM(CardGold) AS TotalGold
		FROM LivcardAssociator(NOLOCK)
	END
	ELSE
	BEGIN
		SELECT
			COUNT (CardID) AS TotalCount,
			SUM(CASE WHEN ApplyDate IS NOT NULL THEN 1 ELSE 0 END) AS TotalUsed,
			SUM(CASE WHEN ApplyDate IS NOT NULL THEN 0 ELSE 1 END) AS TotalNoUsed,
			SUM(CASE WHEN ValidDate<getdate() AND ApplyDate IS NULL THEN 1 ELSE 0 END) AS TotalOut,
			SUM(CASE WHEN Nullity=1 AND ApplyDate IS NULL THEN 1 ELSE 0 END) AS TotalNullity,
			SUM(CardPrice) AS TotalPrice,
			SUM(CardGold) AS TotalGold
		FROM LivcardAssociator(NOLOCK)
		WHERE BuildID=@BuildID
	END
END
RETURN 0