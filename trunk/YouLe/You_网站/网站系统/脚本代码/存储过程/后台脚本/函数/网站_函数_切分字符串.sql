----------------------------------------------------------------------
-- ��Ȩ��2011
-- ʱ�䣺2011-06-17
-- ��;���з��ַ����������������ָ����ͷָ���֮��Ŀ��ַ�
-- �÷���SELECT * FROM [dbo].[WF_Split]('a,b,c,d',',');
--		���ر�ṹ:
--		id		��������
--		rs		�ָ����зֵ�ÿ������
----------------------------------------------------------------------
USE QPTreasureDB
GO
IF EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[WF_Split]') AND type in (N'FN', N'IF', N'TF', N'FS', N'FT'))
DROP FUNCTION dbo.[WF_Split]
GO
----------------------------------------------------------------
CREATE FUNCTION [dbo].[WF_Split]
(
	@strSource NVARCHAR(4000),	--Ҫ�������ַ���
	@strSeparator CHAR(1)			--�ָ��������ֽ�
)
RETURNS @tbResult TABLE(id INT IDENTITY(1,1),rs NVARCHAR(1000))
WITH ENCRYPTION AS  
BEGIN 
   DECLARE @dwIndex INT ,@strResult NVARCHAR(1000);
   SET @strSource = RTRIM(LTRIM(@strSource)); -- ���ո�
   SET @dwIndex = CHARINDEX(@strSeparator,@strSource);	-- ȡ�õ�һ���ָ�����λ��

   WHILE @dwIndex>0
   BEGIN 
      SET @strResult = LTRIM(RTRIM(LEFT(@strSource,@dwIndex-1)));
      IF @strResult IS NULL OR @strResult = '' OR @strResult = @strSeparator
      BEGIN 
        SET @strSeparator = SUBSTRING(@strSource,@dwIndex+1,LEN(@strSource)-@dwIndex); --��Ҫ�������ַ���ȥ�����зֲ���
        SET @dwIndex = CHARINDEX(@strSeparator,@strSource); --ѭ��������
		CONTINUE;
      END 

      INSERT @tbResult VALUES(@strResult);
      SET @strSource = SUBSTRING(@strSource,@dwIndex+1,LEN(@strSource)-@dwIndex); --��Ҫ�������ַ���ȥ�����зֲ���
      SET @dwIndex=CHARINDEX(@strSeparator,@strSource); --ѭ��������
   END 
   --�������һ��
   IF  @strSource IS NOT NULL AND LTRIM(RTRIM(@strSource)) <> '' AND @strSource <> @strSeparator 
   BEGIN 
      INSERT @tbResult VALUES(@strSource)
   END 

   RETURN;
END 



