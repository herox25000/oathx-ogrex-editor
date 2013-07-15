----------------------------------------------------------------------------------------------------
-- ��Ȩ��2011
-- ʱ�䣺2011-09-06
-- ��;�����������
----------------------------------------------------------------------------------------------------
USE QPNativeWebDB
GO

IF EXISTS (SELECT * FROM DBO.SYSOBJECTS WHERE ID = OBJECT_ID(N'[dbo].NET_PW_UpdateViewCount') and OBJECTPROPERTY(ID, N'IsProcedure') = 1)
DROP PROCEDURE [dbo].NET_PW_UpdateViewCount
GO

SET QUOTED_IDENTIFIER ON 
GO

SET ANSI_NULLS ON 
GO

----------------------------------------------------------------------------------------------------
-- ���������
CREATE PROCEDURE NET_PW_UpdateViewCount

	-- ��֤��Ϣ
	@dwFeedbackID		NCHAR(32)					-- ������ʶ

WITH ENCRYPTION AS

-- ��������
SET NOCOUNT ON

-- ִ���߼�
BEGIN	
	
	UPDATE GameFeedbackInfo SET ViewCount = ViewCount+1 WHERE FeedbackID=@dwFeedbackID
	
END

SET NOCOUNT OFF

RETURN 0

GO