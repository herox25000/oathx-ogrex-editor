@echo off

TITLE �������ݿ⡾Ver6.6_Spreader�� �����ű�������... [�ڼ�����ر�]

md D:\���ݿ�

Rem �������ݿ����
set rootPath=���ݿ�ű�\
osql -E -i "%rootPath%���ݿ�ɾ��.sql"
osql -E -i "%rootPath%1_1_��վ��ű�.sql"
osql -E -i "%rootPath%1_2_��̨��ű�.sql"

osql -E -i "%rootPath%2_1_��վ��ű�.sql"
osql -E -i "%rootPath%2_2_��̨��ű�.sql"

Rem �����ӷ�����������
set rootPath=���ݽű�\
osql -E -i "%rootPath%�Ƹ�����.sql"
osql -E -i "%rootPath%��¼����.sql"
osql -E -i "%rootPath%ƽ̨����.sql"
osql -E -i "%rootPath%�û�����.sql"
osql -E -i "%rootPath%��ֵ����.sql"
osql -E -i "%rootPath%��̨����.sql"
osql -E -i "%rootPath%��Ա������.sql"
osql -E -i "%rootPath%��վ����.sql"
osql -E -i "%rootPath%ϵͳ����.sql"
osql -E -i "%rootPath%�ƹ�����.sql"
osql -E -i "%rootPath%�ݵ�����.sql"

Rem �洢����
set rootPath=�洢����\ǰ̨�ű�\������ݿ�\
osql -E  -i "%rootPath%��Ҵ��.sql"
osql -E  -i "%rootPath%���ȡ��.sql"
osql -E  -i "%rootPath%���ת��.sql"
osql -E  -i "%rootPath%ʵ����ֵ.sql"
osql -E  -i "%rootPath%�ƹ�����.sql"
osql -E  -i "%rootPath%���߳�ֵ.sql"
osql -E  -i "%rootPath%���߶���.sql"
osql -E  -i "%rootPath%�����û������б��Ƽ��˵��ƹ���Ϣ.sql"

Rem �洢����
set rootPath=�洢����\ǰ̨�ű�\��վ���ݿ�\
osql -E  -i "%rootPath%��������.sql"
osql -E  -i "%rootPath%���ⷴ��.sql"
osql -E  -i "%rootPath%���������.sql"
osql -E  -i "%rootPath%��ȡ������Ϣ.sql"

Rem �洢����
set rootPath=�洢����\ǰ̨�ű�\�û����ݿ�\
osql -E  -i "%rootPath%�̶�����.sql"
osql -E  -i "%rootPath%��ȡ�û���Ϣ.sql"
osql -E  -i "%rootPath%���ƶһ�.sql"
osql -E  -i "%rootPath%�����һ�.sql"
osql -E  -i "%rootPath%�޸�����.sql"
osql -E  -i "%rootPath%�޸�����.sql"
osql -E  -i "%rootPath%�û���¼.sql"
osql -E  -i "%rootPath%�û������.sql"
osql -E  -i "%rootPath%�û�ȫ����Ϣ.sql"
osql -E  -i "%rootPath%�û�ע��.sql"
osql -E  -i "%rootPath%�˻�����.sql"
osql -E  -i "%rootPath%��������.sql"

Rem �洢����
set rootPath=�洢����\ǰ̨�ű�\�������ݿ�\
osql -E  -i "%rootPath%��������.sql"
osql -E  -i "%rootPath%��������.sql"

Rem �洢����
set rootPath=�洢����\��̨�ű�\����\
osql -E  -i "%rootPath%��վ_����_�з��ַ���.sql"

Rem �洢����
set rootPath=�洢����\��̨�ű�\��¼��\
osql -E  -i "%rootPath%���ͻ�Ա.sql"
osql -E  -i "%rootPath%���ͽ��.sql"
osql -E  -i "%rootPath%���;���.sql"
osql -E  -i "%rootPath%��������.sql"

Rem �洢����
set rootPath=�洢����\��̨�ű�\ƽ̨��\
osql -E  -i "%rootPath%����ͳ��.sql"

Rem �洢����
set rootPath=�洢����\��̨�ű�\��ҿ�\
osql -E  -i "%rootPath%���ߵ���ɾ��.sql"
osql -E  -i "%rootPath%ʵ�����.sql"
osql -E  -i "%rootPath%ʵ��ͳ��.sql"
osql -E  -i "%rootPath%��վ_���ݻ���ͳ��.sql"
osql -E  -i "%rootPath%��վ_���ͽ��.sql"
osql -E  -i "%rootPath%���������ɼ�¼.sql"

Rem �洢����
set rootPath=�洢����\��̨�ű�\Ȩ�޿�\
osql -E  -i "%rootPath%�û������.sql"
osql -E  -i "%rootPath%��վ_�˵�����.sql"
osql -E  -i "%rootPath%��վ_����Ա��¼.sql"
osql -E  -i "%rootPath%��վ_Ȩ�޼���.sql"

Rem �洢����
set rootPath=�洢����\��̨�ű�\���ֿ�\
osql -E  -i "%rootPath%�������.sql"
osql -E  -i "%rootPath%��������.sql"
osql -E  -i "%rootPath%���ͻ���.sql"

Rem �洢����
set rootPath=�洢����\��̨�ű�\�ʺſ�\
osql -E  -i "%rootPath%��վ_����û�.sql"

Rem �洢����
set rootPath=�洢����\��������\
osql -d QPAccountsDB -E  -n -i "%rootPath%��ҳ����.sql"
osql -d QPGameMatchDB -E  -n -i "%rootPath%��ҳ����.sql"
osql -d QPGameScoreDB -E  -n -i "%rootPath%��ҳ����.sql"
osql -d QPNativeWebDB -E  -n -i "%rootPath%��ҳ����.sql"
osql -d QPPlatformDB -E  -n -i "%rootPath%��ҳ����.sql"
osql -d QPPlatformManagerDB -E  -n -i "%rootPath%��ҳ����.sql"
osql -d QPRecordDB -E  -n -i "%rootPath%��ҳ����.sql"
osql -d QPTreasureDB -E  -n -i "%rootPath%��ҳ����.sql"

pause


COLOR 0A
CLS
@echo off
cls
echo ------------------------------
echo.
echo.		��Ҫ���ݿ⽨����ɣ�������Լ�ƽ̨�Ļ�����Ϸִ�� 
echo.		�洢����\��̨�ű�\���ֿ�  ���ȫ���ű�
echo
echo ------------------------------

pause


