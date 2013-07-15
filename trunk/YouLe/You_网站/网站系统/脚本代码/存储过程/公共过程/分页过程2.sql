/*********************************************************************************
*      Function:  WEB_PageView2													 *
*      Description:                                                              *
*             Sql2005��ҳ�洢����												 *
*      Finish DateTime:                                                          *
*             2009/1/3															 *
*	   Example:																	 *
*	          WEB_PageView @Tablename = 'Table1', @Returnfields = '*',           *
*			  @PageSize = 2, @PageIndex = 1, @Where = '',					     *
*			  @OrderBy=N'ORDER BY id desc'										 *           
*********************************************************************************/

IF EXISTS (SELECT * FROM DBO.SYSOBJECTS WHERE ID = OBJECT_ID(N'[dbo].[WEB_PageView2]') and OBJECTPROPERTY(ID, N'IsProcedure') = 1)
DROP PROCEDURE [dbo].[WEB_PageView2]
GO

SET QUOTED_IDENTIFIER ON
GO

SET ANSI_NULLS ON 
GO


CREATE PROCEDURE dbo.WEB_PageView2
	@TableName		NVARCHAR(200),			-- ����
	@ReturnFields	NVARCHAR(1000) = '*',	-- ��Ҫ���ص��� 
	@PageSize		INT = 10,				-- ÿҳ��¼��
	@PageIndex		INT = 1,				-- ��ǰҳ��
	@Where			NVARCHAR(1000) = '',	-- ��ѯ����
	@OrderBy		NVARCHAR(1000),			-- �����ֶ��� ���ΪΨһ����	
	@PageCount		INT OUTPUT,				-- ҳ������
	@RecordCount	INT OUTPUT	        	-- ��¼����

WITH ENCRYPTION AS

--��������
SET NOCOUNT ON

-- ��������
DECLARE @TotalRecord INT
DECLARE @TotalPage INT
DECLARE @CurrentPageSize INT
DECLARE @TotalRecordForPageIndex INT

BEGIN
	IF @Where IS NULL SET @Where=N''
	
	-- ��¼����
	DECLARE @countSql NVARCHAR(4000)  
	
	IF @RecordCount IS NULL
	BEGIN
		SET @countSql='SELECT @TotalRecord=Count(*) From '+@TableName+' '+@Where
		EXECUTE sp_executesql @countSql,N'@TotalRecord int out',@TotalRecord OUT
	END
	ELSE
	BEGIN
		SET @TotalRecord=@RecordCount
	END		
	
	SET @RecordCount=@TotalRecord
	SET @TotalPage=(@TotalRecord-1)/@PageSize+1	
	SET @CurrentPageSize=(@PageIndex-1)*@PageSize

	-- ������ҳ�����ܼ�¼��
	SET @PageCount=@TotalPage
	SET @RecordCount=@TotalRecord
		
	-- ���ؼ�¼
	SET @TotalRecordForPageIndex=@PageIndex*@PageSize
	
	EXEC	('SELECT *
			FROM (SELECT TOP '+@TotalRecordForPageIndex+' '+@ReturnFields+', ROW_NUMBER() OVER ('+@OrderBy+') AS PageView_RowNo
			FROM '+@TableName+ ' ' + @Where +' ) AS TempPageViewTable
			WHERE TempPageViewTable.PageView_RowNo > 
			'+@CurrentPageSize)
	
END
RETURN 0
GO
			

