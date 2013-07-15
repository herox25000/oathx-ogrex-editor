USE QPTreasureDB
GO

IF EXISTS (SELECT * FROM DBO.SYSOBJECTS WHERE ID = OBJECT_ID(N'[dbo].[WSP_PM_LivcardAdd]') and OBJECTPROPERTY(ID, N'IsProcedure') = 1)
DROP PROCEDURE [dbo].[WSP_PM_LivcardAdd]
GO

SET QUOTED_IDENTIFIER ON 
GO

SET ANSI_NULLS ON 
GO

----------------------------------------------------------------------
-- ʱ�䣺2010-03-16
-- ��;��ʵ�����
----------------------------------------------------------------------
CREATE PROCEDURE WSP_PM_LivcardAdd
	@SerialID nvarchar(31),		-- ʵ������
	@Password nchar(32),		-- ʵ������
	@BuildID int,				-- ���ɱ�ʶ
	@CardTypeID int,			-- ʵ������
	@CardPrice decimal(18,2),	-- ʵ���۸�	
	@CardGold bigint,			-- ʵ�����
	@MemberOrder tinyint,		-- ��Ա�ȼ�
	@MemberDays int,			-- ��Ա����
	@UserRight int,				-- �û�Ȩ��
	@ServiceRight int,			-- ����Ȩ��
	@UseRange int,				-- ʹ�÷�Χ
	@SalesPerson nvarchar(31),	-- ������
	@ValidDate datetime			-- ��Ч����	
WITH ENCRYPTION AS

-- ��������
SET NOCOUNT ON

-- ִ���߼�
BEGIN
	INSERT INTO LivcardAssociator(
		SerialID,Password,BuildID,CardTypeID,CardPrice,CardGold,MemberOrder,
		MemberDays,UserRight,ServiceRight,UseRange,SalesPerson,ValidDate)
	VALUES(
		@SerialID,@Password,@BuildID,@CardTypeID,@CardPrice,@CardGold,@MemberOrder,
		@MemberDays,@UserRight,@ServiceRight,@UseRange,@SalesPerson,@ValidDate)
END
RETURN 0

