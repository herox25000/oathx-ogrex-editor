----------------------------------------------------------------------------------------------------
-- ��Ȩ��2011
-- ʱ�䣺2012-02-23
-- ��;�����ƶһ�
----------------------------------------------------------------------------------------------------

USE QPAccountsDB
GO

IF EXISTS (SELECT * FROM DBO.SYSOBJECTS WHERE ID = OBJECT_ID(N'[dbo].NET_PW_ConvertMedal') and OBJECTPROPERTY(ID, N'IsProcedure') = 1)
DROP PROCEDURE [dbo].NET_PW_ConvertMedal
GO

SET QUOTED_IDENTIFIER ON
GO

SET ANSI_NULLS ON
GO

----------------------------------------------------------------------------------------------------
-- ���ƶһ�
CREATE PROCEDURE NET_PW_ConvertMedal
	@dwUserID	INT,						-- �û� I D
	@dwMedals	INT,						-- �һ�����
	@dwConvertRate	INT,					-- �һ�����
	@strClientIP VARCHAR(15),				-- �һ���ַ
	@strErrorDescribe NVARCHAR(127) OUTPUT	-- �����Ϣ
WITH ENCRYPTION AS

-- ��������
SET NOCOUNT ON

-- �û���Ϣ
DECLARE @UserID INT
DECLARE @Nullity BIT
DECLARE @StunDown BIT
DECLARE @CurrentMedals INT

-- �����Ϣ
DECLARE @InsureScore BIGINT

-- �һ����
DECLARE @ConvertGold BIGINT

-- ִ���߼�
BEGIN
	-- ��ѯ�û�
	SELECT @UserID=UserID, @Nullity=Nullity, @StunDown=StunDown,@CurrentMedals=UserMedal
	FROM AccountsInfo(NOLOCK) WHERE UserID=@dwUserID

	-- ��ѯ�û�
	IF @UserID IS NULL
	BEGIN
		SET @strErrorDescribe=N'�����ʺŲ����ڻ������������������֤���ٴγ��Ե�¼��'
		RETURN 1
	END	
	
	-- �ʺŽ�ֹ
	IF @Nullity<>0
	BEGIN
		SET @strErrorDescribe=N'�����ʺ���ʱ���ڶ���״̬������ϵ�ͻ����������˽���ϸ�����'
		RETURN 2
	END	

	-- �ʺŹر�
	IF @StunDown<>0
	BEGIN
		SET @strErrorDescribe=N'�����ʺ�ʹ���˰�ȫ�رչ��ܣ��������¿�ͨ����ܼ���ʹ�ã�'
		RETURN 3
	END		

	-- �����ж�
	IF @dwMedals > @CurrentMedals 
	BEGIN
		SET @strErrorDescribe=N'�ǳ���Ǹ,���Ľ��������㣡'
		RETURN 4
	END
	
	-- ��ѯ���
	SELECT @InsureScore = InsureScore FROM QPTreasureDBLink.QPTreasureDB.dbo.GameScoreInfo 
	WHERE UserID = @dwUserID
	IF @InsureScore IS NULL
	BEGIN
		SET @InsureScore = 0
	END

	-- �һ���¼
	INSERT INTO QPRecordDBLink.QPRecordDB.dbo.RecordConvertUserMedal(
		UserID,CurInsureScore,CurUserMedal,ConvertUserMedal,ConvertRate,IsGamePlaza,ClientIP)
	VALUES(@UserID,@InsureScore,@CurrentMedals,@dwMedals,@dwConvertRate,1,@strClientIP)

	-- �һ�
	SET @ConvertGold = @dwMedals*@dwConvertRate
	UPDATE QPTreasureDBLink.QPTreasureDB.dbo.GameScoreInfo SET
		InsureScore = InsureScore+@ConvertGold
	WHERE UserID = @dwUserID

	IF @@ROWCOUNT = 0 
	BEGIN
		INSERT INTO QPTreasureDBLink.QPTreasureDB.dbo.GameScoreInfo(UserID,InsureScore,RegisterIP,LastLogonIP)
		VALUES(@UserID,@ConvertGold,@strClientIP,@strClientIP)
	END

	-- ���½�����
	UPDATE AccountsInfo SET UserMedal = @CurrentMedals-@dwMedals
	WHERE UserID = @dwUserID
	SET @strErrorDescribe=N'���ƶһ��ɹ���' 
END

RETURN 0

GO