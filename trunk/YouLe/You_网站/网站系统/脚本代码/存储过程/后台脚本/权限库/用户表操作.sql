----------------------------------------------------------------------
-- ʱ�䣺2010-04-21
-- ��;�������û�����(����/����/ɾ��)
----------------------------------------------------------------------

USE QPPlatformManagerDB
GO

IF EXISTS (SELECT * FROM DBO.SYSOBJECTS WHERE ID = OBJECT_ID(N'[dbo].[BaseUser_OP]') and OBJECTPROPERTY(ID, N'IsProcedure') = 1)
DROP PROCEDURE [dbo].[BaseUser_OP]
GO

SET QUOTED_IDENTIFIER ON 
GO

SET ANSI_NULLS ON 
GO

----------------------------------------------------------------------

CREATE PROCEDURE [dbo].[BaseUser_OP]
	
	@Username NVARCHAR(40),					-- �û�����
	@Password NVARCHAR(40),					-- �û�����
	@RoleID		int,					        -- Ȩ�����
	@DataTable_Action_  varchar(10) = ''	-- �������� Insert:���� Update:�޸� Delete:ɾ��
AS

SET NOCOUNT ON

DECLARE @ReturnValue varchar(18) -- ���ز������

BEGIN
	-- ����
	IF(@DataTable_Action_='Insert')
	BEGIN
		
		INSERT INTO Base_Users(
			Username,Password,RoleID)
		VALUES(
			@Username,@Password,@RoleID)
		SET @ReturnValue = SCOPE_IDENTITY()
		SELECT @ReturnValue
	END

SELECT @ReturnValue
END








