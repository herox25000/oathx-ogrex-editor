----------------------------------------------------------------------
-- 版权：2011
-- 时间：2011-09-1
-- 用途：在线充值
----------------------------------------------------------------------

USE [QPTreasureDB]
GO

-- 在线充值
IF EXISTS (SELECT * FROM DBO.SYSOBJECTS WHERE ID = OBJECT_ID(N'[dbo].NET_PW_FilledApp') and OBJECTPROPERTY(ID, N'IsProcedure') = 1)
DROP PROCEDURE [dbo].NET_PW_FilledApp
GO

SET QUOTED_IDENTIFIER ON 
GO
SET ANSI_NULLS ON 
GO

---------------------------------------------------------------------------------------
-- 在线充值
CREATE PROCEDURE NET_PW_FilledApp
	@dwUserID			INT,					-- 用户标识
	@strOrdersID		NVARCHAR(50),			-- 订单编号
	@PayAmount			DECIMAL(18,2),			-- 付款金额
	@dwShareID			INT,					-- 服务标识
	@strErrorDescribe	NVARCHAR(127) OUTPUT	-- 输出信息
WITH ENCRYPTION AS

-- 属性设置
SET NOCOUNT ON

-- 订单信息
DECLARE @UserID INT
DECLARE @Accounts NVARCHAR(31)
DECLARE @GameID INT
DECLARE @Nullity TINYINT

-- 金币信息
DECLARE @Score BIGINT

-- 执行逻辑
BEGIN	
	-- 订单重复
	IF EXISTS(SELECT OrderID FROM ShareDetailInfo(NOLOCK) WHERE OrderID=@strOrdersID) 
	BEGIN
		SET @strErrorDescribe=N'抱歉！充值订单重复。'
		RETURN 1
	END

	-- 验证用户
	SELECT @UserID=UserID,@GameID=GameID,@Accounts=Accounts,@Nullity=Nullity
	FROM QPAccountsDBLink.QPAccountsDB.dbo.AccountsInfo
	WHERE UserID=@dwUserID

	IF @UserID IS NULL
	BEGIN
		SET @strErrorDescribe=N'抱歉！您要充值的用户账号不存在。'
		RETURN 2
	END

	IF @Nullity=1
	BEGIN
		SET @strErrorDescribe=N'抱歉！您要充值的用户账号暂时处于冻结状态，请联系客户服务中心了解详细情况。'
		RETURN 3
	END	

	-- 金币查询
	SELECT @Score=Score FROM GameScoreInfo WHERE UserID=@UserID

	-- 计算金币
	DECLARE @PresentScore BIGINT 
	SET @PresentScore = @PayAmount*10000

	-- 产生记录
	INSERT INTO ShareDetailInfo(
		OperUserID,ShareID,UserID,GameID,Accounts,OrderID,CardTypeID,CardPrice,CardGold,BeforeGold,
		CardTotal,OrderAmount,DiscountScale,PayAmount,IPAddress)
	VALUES(
		@UserID,@dwShareID,@UserID,@GameID,@Accounts,@strOrdersID,0,@PayAmount,@PresentScore,@Score,
		1,@PayAmount,0,@PayAmount,'0.0.0.0')

	-- 充值金币
	UPDATE GameScoreInfo SET Score=Score+@PresentScore WHERE UserID=@UserID
	IF @@ROWCOUNT=0	
	BEGIN
		INSERT GameScoreInfo(UserID,Score,RegisterIP,LastLogonIP)
		VALUES (@UserID,@PresentScore,'0.0.0.0','0.0.0.0')
	END

	-- 记录日志
	DECLARE @DateID INT
	SET @DateID=CAST(CAST(GETDATE() AS FLOAT) AS INT)

	UPDATE StreamShareInfo
	SET ShareTotals=ShareTotals+1
	WHERE DateID=@DateID AND ShareID=@dwShareID

	IF @@ROWCOUNT=0
	BEGIN
		INSERT StreamShareInfo(DateID,ShareID,ShareTotals)
		VALUES (@DateID,@dwShareID,1)
	END	 
	
END 
RETURN 0
GO



