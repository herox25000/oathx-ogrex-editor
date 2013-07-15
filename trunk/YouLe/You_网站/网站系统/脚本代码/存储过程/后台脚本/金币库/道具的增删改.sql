

----------------------------------------------------------------------
-- ʱ�䣺2009-11-4 10:06:57
-- ���̣�������ɾ��
----------------------------------------------------------------------

USE QPTreasureDB
GO

IF EXISTS (SELECT * FROM DBO.SYSOBJECTS WHERE ID = OBJECT_ID(N'[dbo].[WSP_PM_GameProperty_OP]') and OBJECTPROPERTY(ID, N'IsProcedure') = 1)
DROP PROCEDURE [dbo].[WSP_PM_GameProperty_OP]
GO

SET QUOTED_IDENTIFIER ON 
GO

SET ANSI_NULLS ON 
GO

----------------------------------------------------------------------------------------------------
CREATE PROCEDURE [dbo].[WSP_PM_GameProperty_OP]
(

    @ID  int = 0,	-- ���ݿ�����
    @Name  nvarchar(32) = '',	-- �ṩվ��
	@Cash decimal(18,2) = 0, --������
    @Gold  bigint = 0,	-- ���ݿ��ַ
    @Discount  smallint = 0,	-- ��ͨ��ַ
    @IssueArea  smallint = 0,	-- ��ͨ��ַ
    @ServiceArea  smallint = 0,	-- ���ݿ�˿�
    @SendLoveLiness  bigint = 0,	-- ���ݿ��û�
    @RecvLoveLiness  bigint = 0,	-- ���ݿ�����
    @RegulationsInfo  nvarchar(255) = '',	-- ������ʶ
    @Nullity  tinyint  = 0,	-- ��ע��Ϣ
    @DataTable_Action_  varchar(10) = ''		-- �������� Insert:���� Update:�޸� Delete:ɾ��
)
WITH ENCRYPTION AS
    -- ������Ϣ
	DECLARE @ReturnValue NVARCHAR(127)
    SET @ReturnValue = -1
    -- ����
    IF (@DataTable_Action_='Insert')
    BEGIN
    
        --��������Ƿ���ͬ
        IF exists (select 1
            FROM  GameProperty
            WHERE ID=@ID )
        BEGIN
            SET @ReturnValue = N'ID�ظ�������ʧ�ܣ�'
			SELECT @ReturnValue
			RETURN 1
        END
    
        INSERT INTO GameProperty(
            ID , 
			[Name],
            Cash , 
            Gold , 
            Discount , 
            IssueArea , 
            ServiceArea , 
            SendLoveLiness , 
            RecvLoveLiness , 
            RegulationsInfo
        ) VALUES (
            @ID , 
			@Name,
            @Cash , 
            @Gold , 
            @Discount , 
            @IssueArea , 
            @ServiceArea , 
            @SendLoveLiness , 
            @RecvLoveLiness , 
            @RegulationsInfo
        )
    END

    -- ����
    IF (@DataTable_Action_='Update')
    BEGIN
    
        --��������Ƿ���ͬ
        IF exists (select 1
            FROM  GameProperty
            WHERE  ID<>@ID)
        BEGIN
            SET @ReturnValue = N'����ID�����ڣ�'
			SELECT @ReturnValue
			RETURN 1
        END
    
        UPDATE DataBaseInfo SET 
            ID=@ID ,
			[Name]=@Name, 
            Cash=@Cash , 
            Gold=@Gold , 
            Discount=@Discount , 
            IssueArea=@IssueArea , 
            ServiceArea=@ServiceArea , 
            SendLoveLiness=@SendLoveLiness , 
            RecvLoveLiness=@RecvLoveLiness , 
            RegulationsInfo=@RegulationsInfo
        WHERE (ID=@ID)

        IF @@ROWCOUNT =0
		BEGIN
			RETURN -3
		END
		ELSE
		BEGIN
			RETURN 1
		END
    END
    -- ɾ��
    IF (@DataTable_Action_='Delete')
    BEGIN
        DELETE DataBaseInfo	WHERE (ID=@ID)

        IF @@ROWCOUNT =0
		BEGIN
			RETURN -3
		END
		ELSE
		BEGIN
			RETURN 1
		END
    END

    SELECT @ReturnValue
