call "D:\Program Files\MacrsoftVisualStudio.Net2003\Common7\Tools\vsvars32.bat"

@echo off

title ֻ����Release�汾

cls

set begintime=%TIME%

color 0A

echo "VC++2003 ���뻷���������.........."

echo "��ʼ����: �������Լ��������"

devenv.com Platform.sln /rebuild "release"

echo "��ʼ����: �ټ���"
devenv.com С��Ϸ\�ټ���\GameProject.sln /rebuild "release"

echo "��ʼ����: �����˿�"
devenv.com С��Ϸ\�����˿�\GameProject.sln /rebuild "release"

echo "��ʼ����: ��ʽ����"
devenv.com С��Ϸ\��ʽ����\GameProject.sln /rebuild "release"

echo "��ʼ����: ţţ"
devenv.com С��Ϸ\ţţ\GameProject.sln /rebuild "release"

echo "��ʼ����: �ƾ�"
devenv.com С��Ϸ\�ƾ�\GameProject.sln /rebuild "release"

echo "��ʼ����: ��ʽ����"
devenv.com С��Ϸ\��ʽ����\GameProject.sln /rebuild "release"

echo "��ʼ����: ������"
devenv.com С��Ϸ\������\GameProject.sln /rebuild "release"

echo "��ʼ����: ���"
devenv.com С��Ϸ\���\GameProject.sln /rebuild "release"

echo "��ʼ����: С��"
devenv.com С��Ϸ\С��\GameProject.sln /rebuild "release"

echo "��ʼ����: թ��"
devenv.com С��Ϸ\թ��\GameProject.sln /rebuild "release"


@echo "���������������..........."

del /F ������\Lib\*.exp
del /F ����\*.ilk

@echo "���ڸ��Ʒ������ļ�..........."


@echo off

set endtime=%TIME%

@echo ���뿪ʼʱ��:  %begintime%
@echo ���뿪ʼʱ��:  %endtime%

@echo ------------------------------------------------------------------------------
@echo ------------------------------------------------------------------------------
@echo �������.........................

pause

