call "D:\Program Files\MacrsoftVisualStudio.Net2003\Common7\Tools\vsvars32.bat"

@echo off

title 只编译Release版本

cls

set begintime=%TIME%

color 0A

echo "VC++2003 编译环境设置完毕.........."

echo "开始编译: 服务器以及公用组件"

devenv.com Platform.sln /rebuild "release"

echo "开始编译: 百家乐"
devenv.com 小游戏\百家乐\GameProject.sln /rebuild "release"

echo "开始编译: 德州扑克"
devenv.com 小游戏\德州扑克\GameProject.sln /rebuild "release"

echo "开始编译: 港式五张"
devenv.com 小游戏\港式五张\GameProject.sln /rebuild "release"

echo "开始编译: 牛牛"
devenv.com 小游戏\牛牛\GameProject.sln /rebuild "release"

echo "开始编译: 牌九"
devenv.com 小游戏\牌九\GameProject.sln /rebuild "release"

echo "开始编译: 港式五张"
devenv.com 小游戏\港式五张\GameProject.sln /rebuild "release"

echo "开始编译: 斗地主"
devenv.com 小游戏\斗地主\GameProject.sln /rebuild "release"

echo "开始编译: 梭哈"
devenv.com 小游戏\梭哈\GameProject.sln /rebuild "release"

echo "开始编译: 小九"
devenv.com 小游戏\小九\GameProject.sln /rebuild "release"

echo "开始编译: 诈金花"
devenv.com 小游戏\诈金花\GameProject.sln /rebuild "release"


@echo "正在清理编译垃圾..........."

del /F 开发库\Lib\*.exp
del /F 运行\*.ilk

@echo "正在复制服务器文件..........."


@echo off

set endtime=%TIME%

@echo 编译开始时间:  %begintime%
@echo 编译开始时间:  %endtime%

@echo ------------------------------------------------------------------------------
@echo ------------------------------------------------------------------------------
@echo 编译完成.........................

pause

