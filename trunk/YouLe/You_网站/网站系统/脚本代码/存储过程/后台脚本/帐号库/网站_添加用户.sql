----------------------------------------------------------------------
-- ʱ�䣺2011-09-29
-- ��;����̨����Ա����û���Ϣ
----------------------------------------------------------------------
USE QPAccountsDB
GO

SET QUOTED_IDENTIFIER ON 
GO

SET ANSI_NULLS ON 
GO

IF EXISTS (SELECT * FROM DBO.SYSOBJECTS WHERE ID = OBJECT_ID(N'[dbo].[NET_PM_AddAccount]') and OBJECTPROPERTY(ID, N'IsProcedure') = 1)
DROP PROCEDURE [dbo].[NET_PM_AddAccount]
GO

----------------------------------------------------------------------
CREATE PROC [NET_PM_AddAccount]
(
	@strAccounts		NVARCHAR(31),			--�û��ʺ�
	@strNickName		NVARCHAR(31)=N'',		--�û��ǳ�
	@strLogonPass		NCHAR(32),				--��¼����
	@strInsurePass		NCHAR(32),				--��ȫ����
	@dwFaceID			SMALLINT ,				--ͷ��
	@strUnderWrite			NVARCHAR(18)=N'',	--����ǩ��
	@strPassPortID		NVARCHAR(18)=N'',		--���֤��
	@strCompellation	NVARCHAR(16)=N'',		--��ʵ����	
	
	@dwExperience		INT	= 0,				--������ֵ
	@dwPresent			INT	= 0,				--������ֵ
	@dwLoveLiness		INT	= 0,				--����ֵ��	
	@dwUserRight		INT	= 0,				--�û�Ȩ��
	@dwMasterRight		INT	= 0,				--����Ȩ��
	@dwServiceRight		INT	= 0,				--����Ȩ��
	@dwMasterOrder		TINYINT	= 0,			--����ȼ�
	
	@dwMemberOrder		TINYINT	= 0,			--��Ա�ȼ�
	@dtMemberOverDate	DATETIME='1980-01-01',	--��������
	@dtMemberSwitchDate DATETIME='1980-01-01',	--�л�ʱ��
	@dwGender			TINYINT = 1,			--�û��Ա�
	@dwNullity			TINYINT = 0,			--��ֹ����
	@dwStunDown			TINYINT = 0,			--�رձ�־
	@dwMoorMachine		TINYINT = 0,			--�̶�����	
	@strRegisterIP		NVARCHAR(15),			--ע���ַ
	@strRegisterMachine NVARCHAR(32)=N'',		--ע�����        
	@IsAndroid			TINYINT,
	                
	@strQQ				NVARCHAR(16)=N'',		--QQ ����
	@strEMail			NVARCHAR(32)=N'',		--�����ʼ�
	@strSeatPhone		NVARCHAR(32)=N'',		--�̶��绰
	@strMobilePhone		NVARCHAR(16)=N'',		--�ֻ�����
	@strDwellingPlace	NVARCHAR(128)=N'',		--��ϸסַ
	@strPostalCode		NVARCHAR(8)=N'',		--��������               
	@strUserNote		NVARCHAR(256)=N''		--�û���ע
	
)
			
--WITH ENCRYPTION AS
AS
BEGIN
	-- ��������
	SET NOCOUNT ON

	DECLARE @dwUserID			INT,			-- �û���ʶ
			@GameID				INT,			-- ��ϷID
			@dtCurrentDate		DATETIME,
			@dwDefSpreaderScale DECIMAL(18,2)	--Ĭ�ϵĳ�ˮ����ֵ0.10
	SET @dwDefSpreaderScale = 0.10
	SET @dtCurrentDate =  GETDATE()

	-- ִ���߼�
	BEGIN TRY
	--��֤
	IF @strAccounts IS NULL OR @strAccounts = ''
		RETURN -2;	--��������
	IF @strNickName IS NULL OR @strNickName = ''
		SET @strNickName = @strAccounts
	IF EXISTS (SELECT * FROM AccountsInfo WHERE Accounts=@strAccounts OR RegAccounts=@strAccounts)
		RETURN -3;	--	�ʺ��Ѵ���
	IF EXISTS (SELECT * FROM AccountsInfo WHERE NickName=@strNickName)
		RETURN -4;	--	�ǳ��Ѵ���
	-- Ч���ʺ�
	IF EXISTS (SELECT [String] FROM ConfineContent(NOLOCK) WHERE (EnjoinOverDate IS NULL  OR EnjoinOverDate>=GETDATE()) AND CHARINDEX(String,@strAccounts)>0)
	BEGIN		
		RETURN -5;	-- ����������ʺ������������ַ���
	END
		
	-- ע�����ͽ��	
	DECLARE @GrantScoreCount AS INT
	DECLARE @DateID INT
	SET @DateID=CAST(CAST(GETDATE() AS FLOAT) AS INT)
	SELECT @GrantScoreCount=StatusValue FROM SystemStatusInfo(NOLOCK) WHERE StatusName=N'GrantScoreCount'
	
	IF @GrantScoreCount IS NULL OR @GrantScoreCount = '' OR @GrantScoreCount <= 0
		SET @GrantScoreCount = 0;
	
	IF @strNickName IS NULL OR 	@strNickName = ''
		SET @strNickName = @strAccounts
	IF @strInsurePass IS NULL OR @strInsurePass = ''
		SET @strInsurePass = @strLogonPass
	BEGIN TRAN
		--�û���Ϣ
		INSERT AccountsInfo
				( Accounts,NickName,RegAccounts,UnderWrite,PassPortID,
				  Compellation ,LogonPass ,InsurePass ,FaceID,Experience ,
				  Present,LoveLiness,UserRight ,MasterRight ,ServiceRight ,
				  MasterOrder ,MemberOrder ,MemberOverDate ,MemberSwitchDate ,Gender ,
				  Nullity ,StunDown ,MoorMachine ,LastLogonIP,RegisterIP ,
				  RegisterDate ,RegisterMobile ,RegisterMachine ,IsAndroid
				)
		VALUES  (				  			  
				  @strAccounts , -- Accounts - nvarchar(31)
				  @strNickName , -- NickName - nvarchar(31)
				  @strAccounts , -- RegAccounts - nvarchar(31)	
				  @strUnderWrite,			  
				  @strPassPortID , -- PassPortID - nvarchar(18)
				  
				  @strCompellation , -- Compellation - nvarchar(16)
				  @strLogonPass , -- LogonPass - nchar(32)
				  @strInsurePass , -- InsurePass - nchar(32)
				  @dwFaceID,
				  @dwExperience , -- Experience - int
				  
				  @dwPresent,							
				  @dwLoveLiness,
				  @dwUserRight , -- UserRight - int
				  @dwMasterRight , -- MasterRight - int
				  @dwServiceRight , -- ServiceRight - int
				  
				  @dwMasterOrder , -- MasterOrder - tinyint
				  @dwMemberOrder , -- MemberOrder - tinyint
				  @dtMemberOverDate , -- MemberOverDate - datetime
				  @dtMemberSwitchDate , -- MemberSwitchDate - datetime
				  @dwGender , -- Gender - tinyint
				  
				  @dwNullity, -- Nullity - tinyint
				  @dwStunDown , -- StunDown - tinyint
				  @dwMoorMachine , -- MoorMachine - tinyint	  
				  @strRegisterIP,      
				  @strRegisterIP , -- RegisterIP - nvarchar(15)
				  
				  @dtCurrentDate , -- RegisterDate - datetime
				  @strMobilePhone , -- RegisterMobile - nvarchar(11)
				  @strRegisterMachine , -- RegisterMachine - nvarchar(32)
				  @IsAndroid  -- IsAndroid - tinyint				 
				)
				--�û���ʶ
		        SET @dwUserID  = @@IDENTITY
		       
				--�û���ϸ��Ϣ
				INSERT IndividualDatum
						( UserID ,Compellation ,QQ ,EMail ,SeatPhone ,
						  MobilePhone ,DwellingPlace ,PostalCode ,CollectDate ,UserNote
						)
				VALUES  ( @dwUserID , -- UserID - int
						  @strCompellation , -- Compellation - nvarchar(16)
						  @strQQ , -- QQ - nvarchar(16)
						  @strEMail , -- EMail - nvarchar(32)
						  @strSeatPhone , -- SeatPhone - nvarchar(32)
						  @strMobilePhone , -- MobilePhone - nvarchar(16)
						  @strDwellingPlace , -- DwellingPlace - nvarchar(128)
						  @strPostalCode , -- PostalCode - nvarchar(8)
						  @dtCurrentDate , -- CollectDate - datetime
						  @strUserNote  -- UserNote - nvarchar(256)
						)
				-- �û��Ƹ���Ϣ
				INSERT QPTreasureDB.dbo.GameScoreInfo
				        ( UserID ,	
				          Score,
				          Revenue,
				          InsureScore,		          
				          UserRight ,
				          MasterRight ,
				          MasterOrder ,
				          LastLogonMachine,				         
				          LastLogonIP ,				         
				          RegisterIP ,
				          RegisterDate,
				          RegisterMachine
				           
				        )
				VALUES  ( @dwUserID , -- UserID - int
				          @GrantScoreCount , -- Score - bigint
				          0 , -- Revenue - bigint
				          0 , -- InsureScore - bigint				        
				          @dwUserRight , -- UserRight - int
				          @dwMasterRight , -- MasterRight - int
				          @dwMasterOrder , -- MasterOrder - tinyint	
				          '',			          
				          @strRegisterIP , -- LastLogonIP - nvarchar(15)
				          @strRegisterIP , -- RegisterIP - nvarchar(15)
				          @dtCurrentDate,  -- RegisterDate - datetime
				          ''				          				         
				        )    
			
			-- ��¼��־			
			UPDATE SystemStreamInfo SET WebRegisterSuccess=WebRegisterSuccess+1 WHERE DateID=@DateID
			IF @@ROWCOUNT=0 INSERT SystemStreamInfo (DateID, WebRegisterSuccess) VALUES (@DateID, 1)
			
			IF @GrantScoreCount > 0
			BEGIN 
				-- �������ͽ�Ҽ�¼
				UPDATE SystemGrantCount SET GrantScore=GrantScore+@GrantScoreCount, GrantCount=GrantCount+1 WHERE DateID=@DateID AND RegisterIP=@strRegisterIP

				-- �����¼
				IF @@ROWCOUNT=0		
					INSERT SystemGrantCount (DateID, RegisterIP, RegisterMachine, GrantScore, GrantCount) VALUES (@DateID, @strRegisterIP, '', @GrantScoreCount, 1)		
			END 
			
			-- ������ϷID
			SELECT @GameID=GameID FROM GameIdentifier(NOLOCK) WHERE UserID=@dwUserID
			IF @GameID IS NULL 
			BEGIN
				COMMIT TRAN			
				RETURN 1;--�û���ӳɹ�����δ�ɹ���ȡ��Ϸ ID ���룬ϵͳ�Ժ󽫸������䣡				
			END
			ELSE UPDATE AccountsInfo SET GameID=@GameID WHERE UserID=@dwUserID  
			     
			COMMIT TRAN			
			RETURN 0;--�ɹ�
		END TRY
		BEGIN CATCH
			IF @@TRANCOUNT > 0
			BEGIN
				ROLLBACK TRAN
			END
			RETURN -1;    --δ֪����������
		END CATCH
END
GO