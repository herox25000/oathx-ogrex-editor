----------------------------------------------------------------------
-- ��Ȩ��2011
-- ʱ�䣺2011-09-22
-- ��;����ȡ��һ������һ������
----------------------------------------------------------------------
USE QPNativeWebDB
GO

SET QUOTED_IDENTIFIER ON 
GO

SET ANSI_NULLS ON 
GO

IF EXISTS (SELECT * FROM DBO.SYSOBJECTS WHERE ID = OBJECT_ID(N'[dbo].NET_PW_GetNewsInfoByID') and OBJECTPROPERTY(ID, N'IsProcedure') = 1)
DROP PROCEDURE [dbo].NET_PW_GetNewsInfoByID
GO

----------------------------------------------------------------------
CREATE PROC NET_PW_GetNewsInfoByID
	@dwNewsID		INT,				--	���ű�ʶ
	@dwMode		INT=1 			-- ���µı�ʶ
WITH ENCRYPTION AS

BEGIN
	-- ��������
	SET NOCOUNT ON;
	
	--�������
	DECLARE @TempID INT

	SELECT @TempID = TempID FROM (
		SELECT ROW_NUMBER() OVER(ORDER By OnTopAll DESC,OnTop DESC,IssueDate DESC ,NewsID DESC) AS TempID, * 
		FROM News
		WHERE IsLock=1 AND IsDelete=0) AS TC
	WHERE NewsID = @dwNewsID
	
	IF @dwMode=1
	BEGIN
		SELECT NewsID, PopID, Subject, Subject1, OnTop, OnTopAll, IsElite, IsHot, IsLock, IsDelete, IsLinks, LinkUrl, Body, FormattedBody, HighLight, ClassID, UserID, IssueIP, LastModifyIP, IssueDate, LastModifyDate FROM (
			SELECT ROW_NUMBER() OVER(ORDER By OnTopAll DESC,OnTop DESC,IssueDate DESC ,NewsID DESC) AS TempID, * 
			FROM News
			WHERE IsLock=1 AND IsDelete=0) AS TC
		WHERE TC.TempID = @TempID - 1
	END
	ELSE IF @dwMode=2
	BEGIN
		SELECT NewsID, PopID, Subject, Subject1, OnTop, OnTopAll, IsElite, IsHot, IsLock, IsDelete, IsLinks, LinkUrl, Body, FormattedBody, HighLight, ClassID, UserID, IssueIP, LastModifyIP, IssueDate, LastModifyDate FROM (
			SELECT ROW_NUMBER() OVER(ORDER By OnTopAll DESC,OnTop DESC,IssueDate DESC ,NewsID DESC) AS TempID, * 
			FROM News
			WHERE IsLock=1 AND IsDelete=0) AS TC
		WHERE TC.TempID = @TempID + 1
	END
END

