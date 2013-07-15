----------------------------------------------------------------------
-- ʱ�䣺2011-09-26
-- ��;���˵�����
----------------------------------------------------------------------
USE QPPlatformManagerDB
GO

SET QUOTED_IDENTIFIER ON 
GO

SET ANSI_NULLS ON 
GO

IF EXISTS (SELECT * FROM DBO.SYSOBJECTS WHERE ID = OBJECT_ID(N'[dbo].[NET_PM_GetMenuByUserID]') and OBJECTPROPERTY(ID, N'IsProcedure') = 1)
DROP PROCEDURE [dbo].[NET_PM_GetMenuByUserID]
GO

----------------------------------------------------------------------
-- �˵�����
CREATE PROC NET_PM_GetMenuByUserID
	@dwUserID	INT			-- ����Ա��ʶ	
WITH ENCRYPTION AS

-- ��������
SET NOCOUNT ON

-- ��ɫ��ʶ
DECLARE @RoleID	INT

-- ִ���߼�
BEGIN
	-- ��ɫ��ȡ
	IF @dwUserID=1 SET @RoleID=1
	ELSE 
		SELECT @RoleID=RoleID FROM Base_Users(NOLOCK) WHERE UserID=@dwUserID

	-- ��������Ա
	IF @dwUserID=1 OR @RoleID=1
		BEGIN
			-- �������
			SELECT ModuleID,Title,Link,IsMenu
			FROM Base_Module
			WHERE Nullity=0 AND ParentID=0
			ORDER BY OrderNo

			-- �Ӽ��汾
			SELECT  ModuleID,ParentID,Title,Link,IsMenu
			FROM Base_Module
			WHERE Nullity=0 AND ParentID<>0
			ORDER BY ParentID,OrderNo
		END
	ELSE
		BEGIN

			-- �������
			SELECT ModuleID, Title, Link, IsMenu
			FROM Base_Module (NOLOCK) 			
			WHERE ModuleID in 
			(
				SELECT DISTINCT ParentID as ModuleID
						FROM Base_RolePermission (NOLOCK) AS rip, Base_Module (NOLOCK) AS m
						WHERE rip.RoleID=@RoleID AND m.ModuleID=rip.ModuleID AND m.Nullity=0 AND m.ParentID <>0
			)

			-- �Ӽ����
			SELECT rip.ModuleID, ParentID, m.Title, m.Link,m.IsMenu
			FROM Base_RolePermission (NOLOCK) AS rip, Base_Module (NOLOCK) AS m
			WHERE rip.RoleID=@RoleID AND m.ModuleID=rip.ModuleID AND m.Nullity=0 AND m.ParentID <>0 
			ORDER BY m.ParentID, m.OrderNo			

		END

END
RETURN 0
GO