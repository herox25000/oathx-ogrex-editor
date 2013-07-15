----------------------------------------------------------------------------------------------------
-- ��Ȩ��2011
-- ʱ�䣺2011-08-31
-- ��;����ȡ�û�ȫ����Ϣ
----------------------------------------------------------------------------------------------------

USE QPAccountsDB
GO

IF EXISTS (SELECT * FROM DBO.SYSOBJECTS WHERE ID = OBJECT_ID(N'[dbo].NET_PW_GetUserGlobalsInfo') and OBJECTPROPERTY(ID, N'IsProcedure') = 1)
DROP PROCEDURE [dbo].NET_PW_GetUserGlobalsInfo
GO

SET QUOTED_IDENTIFIER ON
GO

SET ANSI_NULLS ON
GO

----------------------------------------------------------------------------------------------------
-- ��ȡ�û�����
CREATE  PROCEDURE NET_PW_GetUserGlobalsInfo
	@dwUserID			INT,					-- �û���ʶ
	@dwGameID			INT,					-- ��Ϸ����
	@strAccounts		NVARCHAR(31),			-- �û��˺�
	@strErrorDescribe	NVARCHAR(127) OUTPUT	-- �����Ϣ
WITH ENCRYPTION AS

-- ��������
SET NOCOUNT ON

-- ������Ϣ
DECLARE @UserID				INT
DECLARE @GameID				INT
DECLARE @Accounts			NVARCHAR(31)
DECLARE @NikeName			NVARCHAR(31)

-- ��չ��Ϣ
DECLARE @FaceID				SMALLINT
DECLARE @Gender				TINYINT
DECLARE @Experience			INT
DECLARE @Present			INT
DECLARE @LoveLiness			INT
DECLARE @UserMedal			INT
DECLARE @UserRight			INT
DECLARE @ServiceRight		INT
DECLARE @MasterOrder		INT
DECLARE @MemberOrder		TINYINT
DECLARE @MemberOverDate		DATETIME
DECLARE @MemberSwitchDate	DATETIME
DECLARE @UnderWrite			NVARCHAR(63)

-- ��ȫ��Ϣ
DECLARE @ProtectID			INT
DECLARE @LogonPass			NVARCHAR(32)
DECLARE @StunDown			TINYINT
DECLARE @MoorMachine		TINYINT
DECLARE @Nullity			TINYINT

-- ��¼��Ϣ
DECLARE @LastLogonIP		NVARCHAR(15)
DECLARE @LastLogonDate		DATETIME

-- ִ���߼�
BEGIN
	-- ��ѯ�û�
	IF @dwUserID <= 0 AND @dwGameID <= 0
	BEGIN
		-- �û��˺�
		SELECT	@UserID=UserID,@GameID=GameID,@Accounts=Accounts,@NikeName=Nickname,
				@FaceID=FaceID,@Gender=Gender,@Experience=Experience,@Present=Present,@LoveLiness=LoveLiness,@UserMedal=UserMedal,
				@UserRight=UserRight,@ServiceRight=ServiceRight,@MasterOrder=MasterOrder,@MemberOrder=MemberOrder,
				@MemberOverDate=MemberOverDate,@MemberSwitchDate=MemberSwitchDate,@UnderWrite=UnderWrite,
				@ProtectID=ProtectID,@LogonPass=LogonPass,@StunDown=StunDown,@MoorMachine=MoorMachine,@Nullity=Nullity,
				@LastLogonIP=LastLogonIP,@LastLogonDate=LastLogonDate
		FROM AccountsInfo(NOLOCK) WHERE Accounts=@strAccounts
	END
	ELSE
	BEGIN
		-- �û���ʶ
		IF  @dwUserID > 0
		BEGIN	
			SELECT	@UserID=UserID,@GameID=GameID,@Accounts=Accounts,@NikeName=Nickname,
					@FaceID=FaceID,@Gender=Gender,@Experience=Experience,@Present=Present,@LoveLiness=LoveLiness,@UserMedal=UserMedal,
					@UserRight=UserRight,@ServiceRight=ServiceRight,@MasterOrder=MasterOrder,@MemberOrder=MemberOrder,
					@MemberOverDate=MemberOverDate,@MemberSwitchDate=MemberSwitchDate,@UnderWrite=UnderWrite,
					@ProtectID=ProtectID,@LogonPass=LogonPass,@StunDown=StunDown,@MoorMachine=MoorMachine,@Nullity=Nullity,
					@LastLogonIP=LastLogonIP,@LastLogonDate=LastLogonDate
			FROM AccountsInfo(NOLOCK) WHERE UserID=@dwUserID
		END
		ELSE
		BEGIN
			-- ��Ϸ��ʶ
			SELECT	@UserID=UserID,@GameID=GameID,@Accounts=Accounts,@NikeName=Nickname,
					@FaceID=FaceID,@Gender=Gender,@Experience=Experience,@Present=Present,@LoveLiness=LoveLiness,@UserMedal=UserMedal,
					@UserRight=UserRight,@ServiceRight=ServiceRight,@MasterOrder=MasterOrder,@MemberOrder=MemberOrder,
					@MemberOverDate=MemberOverDate,@MemberSwitchDate=MemberSwitchDate,@UnderWrite=UnderWrite,
					@ProtectID=ProtectID,@LogonPass=LogonPass,@StunDown=StunDown,@MoorMachine=MoorMachine,@Nullity=Nullity,
					@LastLogonIP=LastLogonIP,@LastLogonDate=LastLogonDate
			FROM AccountsInfo(NOLOCK) WHERE GameID=@dwGameID
		END
	END
	
	-- �û�����
	IF @UserID IS NULL
	BEGIN
		SET @strErrorDescribe = N'�����ʺŲ����ڻ������������������֤���ٴγ��Ե�¼��'
		RETURN 1
	END	

	-- �ʺŽ�ֹ
	IF @Nullity<>0
	BEGIN
		SET @strErrorDescribe=N'�����ʺ���ʱ���ڶ���״̬������ϵ�ͻ����������˽���ϸ�����'
		RETURN 2
	END			

	-- ��Ա�ȼ�
	IF GETDATE()>@MemberOverDate SET @MemberOrder=0
	
	-- �������
	SELECT @UserID AS UserID,@GameID AS GameID,@Accounts AS Accounts,@NikeName AS NickName,
	@FaceID AS FaceID,@Gender AS Gender,@Experience AS Experience,@Present AS Present,@LoveLiness AS LoveLiness, @UserMedal AS UserMedal,
	@UserRight AS UserRight,@ServiceRight AS ServiceRight,@MasterOrder AS MasterOrder,@MemberOrder AS MemberOrder,
	@MemberOverDate AS MemberOverDate,@MemberSwitchDate AS MemberSwitchDate,@UnderWrite AS UnderWrite,
	@ProtectID AS ProtectID,@LogonPass AS LogonPass,@StunDown AS StunDown,@MoorMachine AS MoorMachine,@Nullity AS Nullity,
	@LastLogonIP AS LastLogonIP,@LastLogonDate AS LastLogonDate

END

SET NOCOUNT OFF

RETURN 0

GO
