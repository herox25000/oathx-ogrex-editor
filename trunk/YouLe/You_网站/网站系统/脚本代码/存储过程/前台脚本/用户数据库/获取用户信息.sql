----------------------------------------------------------------------------------------------------
-- ��Ȩ��2011
-- ʱ�䣺2011-08-31
-- ��;����ȡ�û���Ϣ
----------------------------------------------------------------------------------------------------

USE QPAccountsDB
GO

IF EXISTS (SELECT * FROM DBO.SYSOBJECTS WHERE ID = OBJECT_ID(N'[dbo].NET_PW_GetUserBaseInfo') and OBJECTPROPERTY(ID, N'IsProcedure') = 1)
DROP PROCEDURE [dbo].NET_PW_GetUserBaseInfo

IF EXISTS (SELECT * FROM DBO.SYSOBJECTS WHERE ID = OBJECT_ID(N'[dbo].NET_PW_GetUserContactInfo') and OBJECTPROPERTY(ID, N'IsProcedure') = 1)
DROP PROCEDURE [dbo].NET_PW_GetUserContactInfo
GO

SET QUOTED_IDENTIFIER ON
GO

SET ANSI_NULLS ON
GO

----------------------------------------------------------------------------------------------------

-- ��ȡ�û���������
CREATE  PROCEDURE NET_PW_GetUserBaseInfo
	@dwUserID INT,                            		-- �û�ID	
	@strErrorDescribe NVARCHAR(127) OUTPUT			-- �����Ϣ
WITH ENCRYPTION AS

-- ��������
SET NOCOUNT ON

-- �ʺ���Ϣ
DECLARE @UserID INT
DECLARE @Account NVARCHAR(31)
DECLARE @NikeName NVARCHAR(31)	
DECLARE @GameID	INT

-- �û�����
DECLARE @Gender TINYINT
DECLARE @UnderWrite NVARCHAR(63)

-- �ʺ�״̬
DECLARE @Nullity BIT
DECLARE @StunDown BIT

-- ִ���߼�
BEGIN
	-- �û�����
	SELECT	@UserID=UserID,
		@Account=Accounts,
		@NikeName = Nickname,
		@GameID=GameID,
		@Gender=Gender,
		@UnderWrite=UnderWrite,		
		@Nullity=Nullity,
		@StunDown=StunDown
	FROM AccountsInfo (NOLOCK) WHERE UserID=@dwUserID
	
	-- ��ѯ�û�
	IF @UserID IS NULL
	BEGIN
		SET @strErrorDescribe= N'�����ʺŲ����ڻ������������������֤���ٴγ��Ե�¼��'
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
	
	-- �������
	SELECT	@UserID AS UserID, 
			@Account AS Accounts,
			@NikeName as Nickname,
			@GameID AS GameID,
			@Gender AS Gender,
			@UnderWrite as UnderWrite
END

RETURN 0

GO


--------------------------------------------------------------------------------
-- ��ȡ�û���չ����
CREATE  PROCEDURE NET_PW_GetUserContactInfo
	@dwUserID INT,                            		-- �û�ID	
	@strErrorDescribe NVARCHAR(127) OUTPUT			-- �����Ϣ
WITH ENCRYPTION AS

-- ��������
SET NOCOUNT ON

-- �ʺ���Ϣ
DECLARE @UserID INT
DECLARE @Account NVARCHAR(31)
DECLARE @NikeName NVARCHAR(31)	
DECLARE @GameID	INT

-- �û�����
DECLARE @Gender TINYINT
DECLARE @UnderWrite NVARCHAR(63)

-- ��ϸ����
DECLARE @Compellation NVARCHAR(16)
DECLARE @QQ NVARCHAR(16)
DECLARE @Email NVARCHAR(32)
DECLARE @SeatPhone NVARCHAR(32)
DECLARE @MobilePhone NVARCHAR(16)
DECLARE @DwellingPlace NVARCHAR(128)
DECLARE @UserNote NVARCHAR(256)

-- �ʺ�״̬
DECLARE @Nullity BIT
DECLARE @StunDown BIT

-- ִ���߼�
BEGIN
	-- �û�����
	SELECT	@UserID=UserID,
		@Account=Accounts,
		@NikeName = Nickname,
		@GameID=GameID,
		@Gender=Gender,
		@UnderWrite=UnderWrite,		
		@Nullity=Nullity,
		@StunDown=StunDown
	FROM AccountsInfo (NOLOCK) WHERE UserID=@dwUserID
	
	-- ��ѯ�û�
	IF @UserID IS NULL
	BEGIN
		SET @strErrorDescribe= N'�����ʺŲ����ڻ������������������֤���ٴγ��Ե�¼��'
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
	
	-- ��ϸ����
	SELECT  @Compellation=Compellation,
			@QQ=QQ,
			@Email=EMail,
			@MobilePhone=MobilePhone,
			@SeatPhone=SeatPhone,
			@DwellingPlace=DwellingPlace,				
			@UserNote=UserNote
	FROM IndividualDatum (NOLOCK) WHERE UserID = @dwUserID
	
	-- �������
	SELECT	@Compellation AS Compellation,
			@QQ AS QQ,
			@Email AS Email,
			@MobilePhone AS MobilePhone,
			@SeatPhone AS SeatPhone,
			@DwellingPlace AS DwellingPlace,				
			@UserNote As UserNote	

END

RETURN 0

GO