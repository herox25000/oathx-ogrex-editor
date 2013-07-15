USE QPPlatformManagerDB

-- 模块表
TRUNCATE TABLE [dbo].[Base_Module]

INSERT [dbo].[Base_Module] ([ModuleID], [ParentID], [Title], [Link], [OrderNo], [Nullity], [IsMenu], [Description], [ManagerPopedom]) VALUES (1, 0, N'游戏用户', N'', 0, 0, 1, N'', 0)
INSERT [dbo].[Base_Module] ([ModuleID], [ParentID], [Title], [Link], [OrderNo], [Nullity], [IsMenu], [Description], [ManagerPopedom]) VALUES (2, 0, N'冲值系统', N'', 5, 0, 1, N'', 0)
INSERT [dbo].[Base_Module] ([ModuleID], [ParentID], [Title], [Link], [OrderNo], [Nullity], [IsMenu], [Description], [ManagerPopedom]) VALUES (3, 0, N'系统维护', N'', 10, 0, 1, N'', 0)
INSERT [dbo].[Base_Module] ([ModuleID], [ParentID], [Title], [Link], [OrderNo], [Nullity], [IsMenu], [Description], [ManagerPopedom]) VALUES (4, 0, N'网站系统', N'', 15, 0, 1, N'', 0)
INSERT [dbo].[Base_Module] ([ModuleID], [ParentID], [Title], [Link], [OrderNo], [Nullity], [IsMenu], [Description], [ManagerPopedom]) VALUES (5, 0, N'后台系统', N'', 20, 0, 1, N'', 0)
INSERT [dbo].[Base_Module] ([ModuleID], [ParentID], [Title], [Link], [OrderNo], [Nullity], [IsMenu], [Description], [ManagerPopedom]) VALUES (6, 0, N'操作日志', N'', 25, 0, 1, N'', 0)
INSERT [dbo].[Base_Module] ([ModuleID], [ParentID], [Title], [Link], [OrderNo], [Nullity], [IsMenu], [Description], [ManagerPopedom]) VALUES (100, 1, N'用户管理', N'Module/AccountManager/AccountsList.aspx', 0, 0, 1, N'', 0)
INSERT [dbo].[Base_Module] ([ModuleID], [ParentID], [Title], [Link], [OrderNo], [Nullity], [IsMenu], [Description], [ManagerPopedom]) VALUES (101, 1, N'金币管理', N'Module/AccountManager/AccountsGoldList.aspx', 5, 0, 1, N'', 0)
INSERT [dbo].[Base_Module] ([ModuleID], [ParentID], [Title], [Link], [OrderNo], [Nullity], [IsMenu], [Description], [ManagerPopedom]) VALUES (102, 1, N'积分管理', N'Module/AccountManager/AccountsScoreList.aspx', 10, 0, 1, N'', 0)
INSERT [dbo].[Base_Module] ([ModuleID], [ParentID], [Title], [Link], [OrderNo], [Nullity], [IsMenu], [Description], [ManagerPopedom]) VALUES (103, 1, N'银行记录', N'Module/AccountManager/AccountsInsureList.aspx', 20, 0, 1, N'', 0)
INSERT [dbo].[Base_Module] ([ModuleID], [ParentID], [Title], [Link], [OrderNo], [Nullity], [IsMenu], [Description], [ManagerPopedom]) VALUES (104, 1, N'限制用户名', N'Module/AccountManager/ConfineContentList.aspx', 25, 0, 1, N'', 0)
INSERT [dbo].[Base_Module] ([ModuleID], [ParentID], [Title], [Link], [OrderNo], [Nullity], [IsMenu], [Description], [ManagerPopedom]) VALUES (105, 1, N'限制IP地址', N'Module/AccountManager/ConfineAddressList.aspx', 35, 0, 1, N'', 0)
INSERT [dbo].[Base_Module] ([ModuleID], [ParentID], [Title], [Link], [OrderNo], [Nullity], [IsMenu], [Description], [ManagerPopedom]) VALUES (106, 1, N'限制机器码', N'Module/AccountManager/ConfineMachineList.aspx', 40, 0, 1, N'', 0)
INSERT [dbo].[Base_Module] ([ModuleID], [ParentID], [Title], [Link], [OrderNo], [Nullity], [IsMenu], [Description], [ManagerPopedom]) VALUES (107, 1, N'机器人管理', N'Module/AccountManager/AndroidList.aspx', 40, 0, 1, N'', 0)
INSERT [dbo].[Base_Module] ([ModuleID], [ParentID], [Title], [Link], [OrderNo], [Nullity], [IsMenu], [Description], [ManagerPopedom]) VALUES (108, 1, N'魅力管理', N'Module/AccountManager/AccountsConvertPresentList.aspx', 15, 0, 1, N'', 0)
INSERT [dbo].[Base_Module] ([ModuleID], [ParentID], [Title], [Link], [OrderNo], [Nullity], [IsMenu], [Description], [ManagerPopedom]) VALUES (110, 1, N'奖牌管理', N'Module/AccountManager/RecordConvertMedalList.aspx', 16, 0, 1, N'', 0)
INSERT [dbo].[Base_Module] ([ModuleID], [ParentID], [Title], [Link], [OrderNo], [Nullity], [IsMenu], [Description], [ManagerPopedom]) VALUES (200, 2, N'实卡管理', N'Module/FilledManager/LivcardBuildStreamList.aspx', 0, 0, 1, N'', 0)
INSERT [dbo].[Base_Module] ([ModuleID], [ParentID], [Title], [Link], [OrderNo], [Nullity], [IsMenu], [Description], [ManagerPopedom]) VALUES (202, 2, N'订单管理', N'Module/FilledManager/OnLineOrderList.aspx', 10, 0, 1, N'', 0)
INSERT [dbo].[Base_Module] ([ModuleID], [ParentID], [Title], [Link], [OrderNo], [Nullity], [IsMenu], [Description], [ManagerPopedom]) VALUES (203, 2, N'充值记录', N'Module/FilledManager/ShareInfoList.aspx', 8, 0, 1, N'', 0)
INSERT [dbo].[Base_Module] ([ModuleID], [ParentID], [Title], [Link], [OrderNo], [Nullity], [IsMenu], [Description], [ManagerPopedom]) VALUES (205, 2, N'快钱管理', N'Module/FilledManager/OrderKQList.aspx', 25, 0, 1, N'', 0)
INSERT [dbo].[Base_Module] ([ModuleID], [ParentID], [Title], [Link], [OrderNo], [Nullity], [IsMenu], [Description], [ManagerPopedom]) VALUES (206, 2, N'易宝管理', N'Module/FilledManager/OrderYPList.aspx', 30, 0, 1, N'', 0)
INSERT [dbo].[Base_Module] ([ModuleID], [ParentID], [Title], [Link], [OrderNo], [Nullity], [IsMenu], [Description], [ManagerPopedom]) VALUES (208, 2, N'声讯记录', N'Module/FilledManager/OrderVBList.aspx', 31, 0, 1, N'', 0)
INSERT [dbo].[Base_Module] ([ModuleID], [ParentID], [Title], [Link], [OrderNo], [Nullity], [IsMenu], [Description], [ManagerPopedom]) VALUES (300, 3, N'机器管理', N'Module/AppManager/DataBaseInfoList.aspx', 0, 0, 1, N'', 0)
INSERT [dbo].[Base_Module] ([ModuleID], [ParentID], [Title], [Link], [OrderNo], [Nullity], [IsMenu], [Description], [ManagerPopedom]) VALUES (301, 3, N'游戏管理', N'Module/AppManager/GameGameItemList.aspx', 5, 0, 1, N'', 0)
INSERT [dbo].[Base_Module] ([ModuleID], [ParentID], [Title], [Link], [OrderNo], [Nullity], [IsMenu], [Description], [ManagerPopedom]) VALUES (302, 3, N'房间管理', N'Module/AppManager/GameRoomInfoList.aspx', 10, 0, 1, N'', 0)
INSERT [dbo].[Base_Module] ([ModuleID], [ParentID], [Title], [Link], [OrderNo], [Nullity], [IsMenu], [Description], [ManagerPopedom]) VALUES (303, 3, N'系统消息', N'Module/AppManager/SystemMessageList.aspx', 20, 0, 1, N'', 0)
INSERT [dbo].[Base_Module] ([ModuleID], [ParentID], [Title], [Link], [OrderNo], [Nullity], [IsMenu], [Description], [ManagerPopedom]) VALUES (304, 3, N'系统设置', N'Module/AppManager/SystemSet.aspx', 20, 0, 1, N'', 0)
INSERT [dbo].[Base_Module] ([ModuleID], [ParentID], [Title], [Link], [OrderNo], [Nullity], [IsMenu], [Description], [ManagerPopedom]) VALUES (305, 3, N'道具管理', N'Module/AppManager/GamePropertyManager.aspx', 35, 0, 1, N'', 0)
INSERT [dbo].[Base_Module] ([ModuleID], [ParentID], [Title], [Link], [OrderNo], [Nullity], [IsMenu], [Description], [ManagerPopedom]) VALUES (307, 3, N'在线统计', N'Module/AppManager/StatOnline.aspx', 45, 0, 1, N'', 0)
INSERT [dbo].[Base_Module] ([ModuleID], [ParentID], [Title], [Link], [OrderNo], [Nullity], [IsMenu], [Description], [ManagerPopedom]) VALUES (308, 3, N'泡点设置', N'Module/AppManager/GlobalPlayPresentList.aspx', 25, 0, 1, N'', 0)
INSERT [dbo].[Base_Module] ([ModuleID], [ParentID], [Title], [Link], [OrderNo], [Nullity], [IsMenu], [Description], [ManagerPopedom]) VALUES (309, 3, N'推广管理', N'Module/AppManager/SpreadSet.aspx', 30, 0, 1, N'', 0)
INSERT [dbo].[Base_Module] ([ModuleID], [ParentID], [Title], [Link], [OrderNo], [Nullity], [IsMenu], [Description], [ManagerPopedom]) VALUES (400, 4, N'新闻管理', N'Module/WebManager/NewsList.aspx', 0, 0, 1, N'', 0)
--INSERT [dbo].[Base_Module] ([ModuleID], [ParentID], [Title], [Link], [OrderNo], [Nullity], [IsMenu], [Description], [ManagerPopedom]) VALUES (402, 4, N'弹出页面', N'Module/WebManager/NoticeList.aspx', 30, 0, 1, N'', 0)
INSERT [dbo].[Base_Module] ([ModuleID], [ParentID], [Title], [Link], [OrderNo], [Nullity], [IsMenu], [Description], [ManagerPopedom]) VALUES (404, 4, N'规则管理', N'Module/WebManager/RulesList.aspx', 5, 0, 1, N'', 0)
INSERT [dbo].[Base_Module] ([ModuleID], [ParentID], [Title], [Link], [OrderNo], [Nullity], [IsMenu], [Description], [ManagerPopedom]) VALUES (405, 4, N'问题管理', N'Module/WebManager/IssueList.aspx', 10, 0, 1, N'', 0)
INSERT [dbo].[Base_Module] ([ModuleID], [ParentID], [Title], [Link], [OrderNo], [Nullity], [IsMenu], [Description], [ManagerPopedom]) VALUES (406, 4, N'比赛管理', N'Module/WebManager/MatchList.aspx', 15, 0, 1, N'', 0)
INSERT [dbo].[Base_Module] ([ModuleID], [ParentID], [Title], [Link], [OrderNo], [Nullity], [IsMenu], [Description], [ManagerPopedom]) VALUES (407, 4, N'回馈管理', N'Module/WebManager/FeedbackList.aspx', 20, 0, 1, N'', 0)
INSERT [dbo].[Base_Module] ([ModuleID], [ParentID], [Title], [Link], [OrderNo], [Nullity], [IsMenu], [Description], [ManagerPopedom]) VALUES (500, 5, N'管理员管理', N'Module/BackManager/BaseRoleList.aspx', 0, 0, 1, N'', 0)
INSERT [dbo].[Base_Module] ([ModuleID], [ParentID], [Title], [Link], [OrderNo], [Nullity], [IsMenu], [Description], [ManagerPopedom]) VALUES (501, 5, N'系统设置', N'Module/BackManager/SystemSet.aspx', 10, 0, 1, N'', 0)
INSERT [dbo].[Base_Module] ([ModuleID], [ParentID], [Title], [Link], [OrderNo], [Nullity], [IsMenu], [Description], [ManagerPopedom]) VALUES (502, 5, N'系统统计', N'Module/BackManager/SystemStat.aspx', 20, 0, 1, N'', 0)
INSERT [dbo].[Base_Module] ([ModuleID], [ParentID], [Title], [Link], [OrderNo], [Nullity], [IsMenu], [Description], [ManagerPopedom]) VALUES (600, 6, N'安全日志', N'Module/OperationLog/SystemSecurityList.aspx', 20, 0, 1, N'', 0)


-- 模板权限表
TRUNCATE TABLE Base_ModulePermission

INSERT [dbo].[Base_ModulePermission] ([ModuleID], [PermissionTitle], [PermissionValue], [Nullity], [StateFlag], [ParentID]) VALUES (100, N'查看', 1, 0, 0, 1)
INSERT [dbo].[Base_ModulePermission] ([ModuleID], [PermissionTitle], [PermissionValue], [Nullity], [StateFlag], [ParentID]) VALUES (100, N'添加', 2, 0, 0, 1)
INSERT [dbo].[Base_ModulePermission] ([ModuleID], [PermissionTitle], [PermissionValue], [Nullity], [StateFlag], [ParentID]) VALUES (100, N'编辑', 4, 0, 0, 1)
INSERT [dbo].[Base_ModulePermission] ([ModuleID], [PermissionTitle], [PermissionValue], [Nullity], [StateFlag], [ParentID]) VALUES (100, N'赠送会员', 16, 0, 0, 1)
INSERT [dbo].[Base_ModulePermission] ([ModuleID], [PermissionTitle], [PermissionValue], [Nullity], [StateFlag], [ParentID]) VALUES (100, N'赠送金币', 32, 0, 0, 1)
INSERT [dbo].[Base_ModulePermission] ([ModuleID], [PermissionTitle], [PermissionValue], [Nullity], [StateFlag], [ParentID]) VALUES (100, N'赠送经验', 64, 0, 0, 1)
INSERT [dbo].[Base_ModulePermission] ([ModuleID], [PermissionTitle], [PermissionValue], [Nullity], [StateFlag], [ParentID]) VALUES (100, N'赠送积分', 128, 0, 0, 1)
INSERT [dbo].[Base_ModulePermission] ([ModuleID], [PermissionTitle], [PermissionValue], [Nullity], [StateFlag], [ParentID]) VALUES (100, N'赠送靓号', 256, 0, 0, 1)
INSERT [dbo].[Base_ModulePermission] ([ModuleID], [PermissionTitle], [PermissionValue], [Nullity], [StateFlag], [ParentID]) VALUES (100, N'清零积分', 512, 0, 0, 1)
INSERT [dbo].[Base_ModulePermission] ([ModuleID], [PermissionTitle], [PermissionValue], [Nullity], [StateFlag], [ParentID]) VALUES (100, N'清零逃率', 1024, 0, 0, 1)
INSERT [dbo].[Base_ModulePermission] ([ModuleID], [PermissionTitle], [PermissionValue], [Nullity], [StateFlag], [ParentID]) VALUES (100, N'冻/解帐号', 8192, 0, 0, 1)
INSERT [dbo].[Base_ModulePermission] ([ModuleID], [PermissionTitle], [PermissionValue], [Nullity], [StateFlag], [ParentID]) VALUES (100, N'设置/取消机器人', 16384, 0, 0, 1)
INSERT [dbo].[Base_ModulePermission] ([ModuleID], [PermissionTitle], [PermissionValue], [Nullity], [StateFlag], [ParentID]) VALUES (101, N'查看', 1, 0, 0, 1)
INSERT [dbo].[Base_ModulePermission] ([ModuleID], [PermissionTitle], [PermissionValue], [Nullity], [StateFlag], [ParentID]) VALUES (102, N'查看', 1, 0, 0, 1)
INSERT [dbo].[Base_ModulePermission] ([ModuleID], [PermissionTitle], [PermissionValue], [Nullity], [StateFlag], [ParentID]) VALUES (103, N'查看', 1, 0, 0, 1)
INSERT [dbo].[Base_ModulePermission] ([ModuleID], [PermissionTitle], [PermissionValue], [Nullity], [StateFlag], [ParentID]) VALUES (104, N'查看', 1, 0, 0, 1)
INSERT [dbo].[Base_ModulePermission] ([ModuleID], [PermissionTitle], [PermissionValue], [Nullity], [StateFlag], [ParentID]) VALUES (104, N'添加', 2, 0, 0, 1)
INSERT [dbo].[Base_ModulePermission] ([ModuleID], [PermissionTitle], [PermissionValue], [Nullity], [StateFlag], [ParentID]) VALUES (104, N'编辑', 4, 0, 0, 1)
INSERT [dbo].[Base_ModulePermission] ([ModuleID], [PermissionTitle], [PermissionValue], [Nullity], [StateFlag], [ParentID]) VALUES (104, N'删除', 8, 0, 0, 1)
INSERT [dbo].[Base_ModulePermission] ([ModuleID], [PermissionTitle], [PermissionValue], [Nullity], [StateFlag], [ParentID]) VALUES (105, N'查看', 1, 0, 0, 1)
INSERT [dbo].[Base_ModulePermission] ([ModuleID], [PermissionTitle], [PermissionValue], [Nullity], [StateFlag], [ParentID]) VALUES (105, N'添加', 2, 0, 0, 1)
INSERT [dbo].[Base_ModulePermission] ([ModuleID], [PermissionTitle], [PermissionValue], [Nullity], [StateFlag], [ParentID]) VALUES (105, N'编辑', 4, 0, 0, 1)
INSERT [dbo].[Base_ModulePermission] ([ModuleID], [PermissionTitle], [PermissionValue], [Nullity], [StateFlag], [ParentID]) VALUES (105, N'删除', 8, 0, 0, 1)
INSERT [dbo].[Base_ModulePermission] ([ModuleID], [PermissionTitle], [PermissionValue], [Nullity], [StateFlag], [ParentID]) VALUES (106, N'查看', 1, 0, 0, 1)
INSERT [dbo].[Base_ModulePermission] ([ModuleID], [PermissionTitle], [PermissionValue], [Nullity], [StateFlag], [ParentID]) VALUES (106, N'添加', 2, 0, 0, 1)
INSERT [dbo].[Base_ModulePermission] ([ModuleID], [PermissionTitle], [PermissionValue], [Nullity], [StateFlag], [ParentID]) VALUES (106, N'编辑', 4, 0, 0, 1)
INSERT [dbo].[Base_ModulePermission] ([ModuleID], [PermissionTitle], [PermissionValue], [Nullity], [StateFlag], [ParentID]) VALUES (106, N'删除', 8, 0, 0, 1)
INSERT [dbo].[Base_ModulePermission] ([ModuleID], [PermissionTitle], [PermissionValue], [Nullity], [StateFlag], [ParentID]) VALUES (107, N'查看', 1, 0, 0, 1)
INSERT [dbo].[Base_ModulePermission] ([ModuleID], [PermissionTitle], [PermissionValue], [Nullity], [StateFlag], [ParentID]) VALUES (107, N'添加', 2, 0, 0, 1)
INSERT [dbo].[Base_ModulePermission] ([ModuleID], [PermissionTitle], [PermissionValue], [Nullity], [StateFlag], [ParentID]) VALUES (107, N'编辑', 4, 0, 0, 1)
INSERT [dbo].[Base_ModulePermission] ([ModuleID], [PermissionTitle], [PermissionValue], [Nullity], [StateFlag], [ParentID]) VALUES (107, N'删除', 8, 0, 0, 1)
INSERT [dbo].[Base_ModulePermission] ([ModuleID], [PermissionTitle], [PermissionValue], [Nullity], [StateFlag], [ParentID]) VALUES (108, N'查看', 1, 0, 0, 1)
INSERT [dbo].[Base_ModulePermission] ([ModuleID], [PermissionTitle], [PermissionValue], [Nullity], [StateFlag], [ParentID]) VALUES (110, N'查看', 1, 0, 0, 1)
--INSERT [dbo].[Base_ModulePermission] ([ModuleID], [PermissionTitle], [PermissionValue], [Nullity], [StateFlag], [ParentID]) VALUES (109, N'卡线清理', 8, 0, 0, 1)
INSERT [dbo].[Base_ModulePermission] ([ModuleID], [PermissionTitle], [PermissionValue], [Nullity], [StateFlag], [ParentID]) VALUES (200, N'查看', 1, 0, 0, 2)
INSERT [dbo].[Base_ModulePermission] ([ModuleID], [PermissionTitle], [PermissionValue], [Nullity], [StateFlag], [ParentID]) VALUES (200, N'添加', 2, 0, 0, 2)
INSERT [dbo].[Base_ModulePermission] ([ModuleID], [PermissionTitle], [PermissionValue], [Nullity], [StateFlag], [ParentID]) VALUES (200, N'编辑', 4, 0, 0, 2)
INSERT [dbo].[Base_ModulePermission] ([ModuleID], [PermissionTitle], [PermissionValue], [Nullity], [StateFlag], [ParentID]) VALUES (200, N'生成实卡', 2048, 0, 0, 2)
INSERT [dbo].[Base_ModulePermission] ([ModuleID], [PermissionTitle], [PermissionValue], [Nullity], [StateFlag], [ParentID]) VALUES (200, N'导出实卡', 4096, 0, 0, 2)
INSERT [dbo].[Base_ModulePermission] ([ModuleID], [PermissionTitle], [PermissionValue], [Nullity], [StateFlag], [ParentID]) VALUES (202, N'查看', 1, 0, 0, 2)
INSERT [dbo].[Base_ModulePermission] ([ModuleID], [PermissionTitle], [PermissionValue], [Nullity], [StateFlag], [ParentID]) VALUES (202, N'删除', 8, 0, 0, 2)
INSERT [dbo].[Base_ModulePermission] ([ModuleID], [PermissionTitle], [PermissionValue], [Nullity], [StateFlag], [ParentID]) VALUES (203, N'查看', 1, 0, 0, 2)
INSERT [dbo].[Base_ModulePermission] ([ModuleID], [PermissionTitle], [PermissionValue], [Nullity], [StateFlag], [ParentID]) VALUES (205, N'查看', 1, 0, 0, 2)
INSERT [dbo].[Base_ModulePermission] ([ModuleID], [PermissionTitle], [PermissionValue], [Nullity], [StateFlag], [ParentID]) VALUES (205, N'删除', 8, 0, 0, 2)
INSERT [dbo].[Base_ModulePermission] ([ModuleID], [PermissionTitle], [PermissionValue], [Nullity], [StateFlag], [ParentID]) VALUES (206, N'查看', 1, 0, 0, 2)
INSERT [dbo].[Base_ModulePermission] ([ModuleID], [PermissionTitle], [PermissionValue], [Nullity], [StateFlag], [ParentID]) VALUES (206, N'删除', 8, 0, 0, 2)
INSERT [dbo].[Base_ModulePermission] ([ModuleID], [PermissionTitle], [PermissionValue], [Nullity], [StateFlag], [ParentID]) VALUES (208, N'查看', 1, 0, 0, 2)
INSERT [dbo].[Base_ModulePermission] ([ModuleID], [PermissionTitle], [PermissionValue], [Nullity], [StateFlag], [ParentID]) VALUES (300, N'查看', 1, 0, 0, 3)
INSERT [dbo].[Base_ModulePermission] ([ModuleID], [PermissionTitle], [PermissionValue], [Nullity], [StateFlag], [ParentID]) VALUES (300, N'添加', 2, 0, 0, 3)
INSERT [dbo].[Base_ModulePermission] ([ModuleID], [PermissionTitle], [PermissionValue], [Nullity], [StateFlag], [ParentID]) VALUES (300, N'编辑', 4, 0, 0, 3)
INSERT [dbo].[Base_ModulePermission] ([ModuleID], [PermissionTitle], [PermissionValue], [Nullity], [StateFlag], [ParentID]) VALUES (300, N'删除', 8, 0, 0, 3)
INSERT [dbo].[Base_ModulePermission] ([ModuleID], [PermissionTitle], [PermissionValue], [Nullity], [StateFlag], [ParentID]) VALUES (301, N'查看', 1, 0, 0, 3)
INSERT [dbo].[Base_ModulePermission] ([ModuleID], [PermissionTitle], [PermissionValue], [Nullity], [StateFlag], [ParentID]) VALUES (301, N'添加', 2, 0, 0, 3)
INSERT [dbo].[Base_ModulePermission] ([ModuleID], [PermissionTitle], [PermissionValue], [Nullity], [StateFlag], [ParentID]) VALUES (301, N'编辑', 4, 0, 0, 3)
INSERT [dbo].[Base_ModulePermission] ([ModuleID], [PermissionTitle], [PermissionValue], [Nullity], [StateFlag], [ParentID]) VALUES (301, N'删除', 8, 0, 0, 3)
INSERT [dbo].[Base_ModulePermission] ([ModuleID], [PermissionTitle], [PermissionValue], [Nullity], [StateFlag], [ParentID]) VALUES (302, N'查看', 1, 0, 0, 3)
INSERT [dbo].[Base_ModulePermission] ([ModuleID], [PermissionTitle], [PermissionValue], [Nullity], [StateFlag], [ParentID]) VALUES (302, N'添加', 2, 0, 0, 3)
INSERT [dbo].[Base_ModulePermission] ([ModuleID], [PermissionTitle], [PermissionValue], [Nullity], [StateFlag], [ParentID]) VALUES (302, N'编辑', 4, 0, 0, 3)
INSERT [dbo].[Base_ModulePermission] ([ModuleID], [PermissionTitle], [PermissionValue], [Nullity], [StateFlag], [ParentID]) VALUES (302, N'删除', 8, 0, 0, 3)
INSERT [dbo].[Base_ModulePermission] ([ModuleID], [PermissionTitle], [PermissionValue], [Nullity], [StateFlag], [ParentID]) VALUES (303, N'查看', 1, 0, 0, 3)
INSERT [dbo].[Base_ModulePermission] ([ModuleID], [PermissionTitle], [PermissionValue], [Nullity], [StateFlag], [ParentID]) VALUES (303, N'添加', 2, 0, 0, 3)
INSERT [dbo].[Base_ModulePermission] ([ModuleID], [PermissionTitle], [PermissionValue], [Nullity], [StateFlag], [ParentID]) VALUES (303, N'编辑', 4, 0, 0, 3)
INSERT [dbo].[Base_ModulePermission] ([ModuleID], [PermissionTitle], [PermissionValue], [Nullity], [StateFlag], [ParentID]) VALUES (303, N'删除', 8, 0, 0, 3)
INSERT [dbo].[Base_ModulePermission] ([ModuleID], [PermissionTitle], [PermissionValue], [Nullity], [StateFlag], [ParentID]) VALUES (304, N'查看', 1, 0, 0, 3)
INSERT [dbo].[Base_ModulePermission] ([ModuleID], [PermissionTitle], [PermissionValue], [Nullity], [StateFlag], [ParentID]) VALUES (304, N'编辑', 4, 0, 0, 3)
INSERT [dbo].[Base_ModulePermission] ([ModuleID], [PermissionTitle], [PermissionValue], [Nullity], [StateFlag], [ParentID]) VALUES (305, N'查看', 1, 0, 0, 3)
INSERT [dbo].[Base_ModulePermission] ([ModuleID], [PermissionTitle], [PermissionValue], [Nullity], [StateFlag], [ParentID]) VALUES (305, N'编辑', 4, 0, 0, 3)
INSERT [dbo].[Base_ModulePermission] ([ModuleID], [PermissionTitle], [PermissionValue], [Nullity], [StateFlag], [ParentID]) VALUES (305, N'删除', 8, 0, 0, 3)
INSERT [dbo].[Base_ModulePermission] ([ModuleID], [PermissionTitle], [PermissionValue], [Nullity], [StateFlag], [ParentID]) VALUES (306, N'查看', 1, 0, 0, 3)
INSERT [dbo].[Base_ModulePermission] ([ModuleID], [PermissionTitle], [PermissionValue], [Nullity], [StateFlag], [ParentID]) VALUES (307, N'查看', 1, 0, 0, 3)
INSERT [dbo].[Base_ModulePermission] ([ModuleID], [PermissionTitle], [PermissionValue], [Nullity], [StateFlag], [ParentID]) VALUES (308, N'查看', 1, 0, 0, 3)
INSERT [dbo].[Base_ModulePermission] ([ModuleID], [PermissionTitle], [PermissionValue], [Nullity], [StateFlag], [ParentID]) VALUES (308, N'添加', 2, 0, 0, 3)
INSERT [dbo].[Base_ModulePermission] ([ModuleID], [PermissionTitle], [PermissionValue], [Nullity], [StateFlag], [ParentID]) VALUES (308, N'编辑', 4, 0, 0, 3)
INSERT [dbo].[Base_ModulePermission] ([ModuleID], [PermissionTitle], [PermissionValue], [Nullity], [StateFlag], [ParentID]) VALUES (308, N'删除', 8, 0, 0, 3)
INSERT [dbo].[Base_ModulePermission] ([ModuleID], [PermissionTitle], [PermissionValue], [Nullity], [StateFlag], [ParentID]) VALUES (309, N'查看', 1, 0, 0, 3)
INSERT [dbo].[Base_ModulePermission] ([ModuleID], [PermissionTitle], [PermissionValue], [Nullity], [StateFlag], [ParentID]) VALUES (309, N'编辑', 4, 0, 0, 3)
INSERT [dbo].[Base_ModulePermission] ([ModuleID], [PermissionTitle], [PermissionValue], [Nullity], [StateFlag], [ParentID]) VALUES (400, N'查看', 1, 0, 0, 4)
INSERT [dbo].[Base_ModulePermission] ([ModuleID], [PermissionTitle], [PermissionValue], [Nullity], [StateFlag], [ParentID]) VALUES (400, N'添加', 2, 0, 0, 4)
INSERT [dbo].[Base_ModulePermission] ([ModuleID], [PermissionTitle], [PermissionValue], [Nullity], [StateFlag], [ParentID]) VALUES (400, N'编辑', 4, 0, 0, 4)
INSERT [dbo].[Base_ModulePermission] ([ModuleID], [PermissionTitle], [PermissionValue], [Nullity], [StateFlag], [ParentID]) VALUES (400, N'删除', 8, 0, 0, 4)
INSERT [dbo].[Base_ModulePermission] ([ModuleID], [PermissionTitle], [PermissionValue], [Nullity], [StateFlag], [ParentID]) VALUES (404, N'查看', 1, 0, 0, 4)
INSERT [dbo].[Base_ModulePermission] ([ModuleID], [PermissionTitle], [PermissionValue], [Nullity], [StateFlag], [ParentID]) VALUES (404, N'添加', 2, 0, 0, 4)
INSERT [dbo].[Base_ModulePermission] ([ModuleID], [PermissionTitle], [PermissionValue], [Nullity], [StateFlag], [ParentID]) VALUES (404, N'编辑', 4, 0, 0, 4)
INSERT [dbo].[Base_ModulePermission] ([ModuleID], [PermissionTitle], [PermissionValue], [Nullity], [StateFlag], [ParentID]) VALUES (404, N'删除', 8, 0, 0, 4)
INSERT [dbo].[Base_ModulePermission] ([ModuleID], [PermissionTitle], [PermissionValue], [Nullity], [StateFlag], [ParentID]) VALUES (405, N'查看', 1, 0, 0, 4)
INSERT [dbo].[Base_ModulePermission] ([ModuleID], [PermissionTitle], [PermissionValue], [Nullity], [StateFlag], [ParentID]) VALUES (405, N'添加', 2, 0, 0, 4)
INSERT [dbo].[Base_ModulePermission] ([ModuleID], [PermissionTitle], [PermissionValue], [Nullity], [StateFlag], [ParentID]) VALUES (405, N'编辑', 4, 0, 0, 4)
INSERT [dbo].[Base_ModulePermission] ([ModuleID], [PermissionTitle], [PermissionValue], [Nullity], [StateFlag], [ParentID]) VALUES (405, N'删除', 8, 0, 0, 4)
INSERT [dbo].[Base_ModulePermission] ([ModuleID], [PermissionTitle], [PermissionValue], [Nullity], [StateFlag], [ParentID]) VALUES (406, N'查看', 1, 0, 0, 4)
INSERT [dbo].[Base_ModulePermission] ([ModuleID], [PermissionTitle], [PermissionValue], [Nullity], [StateFlag], [ParentID]) VALUES (406, N'添加', 2, 0, 0, 4)
INSERT [dbo].[Base_ModulePermission] ([ModuleID], [PermissionTitle], [PermissionValue], [Nullity], [StateFlag], [ParentID]) VALUES (406, N'编辑', 4, 0, 0, 4)
INSERT [dbo].[Base_ModulePermission] ([ModuleID], [PermissionTitle], [PermissionValue], [Nullity], [StateFlag], [ParentID]) VALUES (406, N'删除', 8, 0, 0, 4)
INSERT [dbo].[Base_ModulePermission] ([ModuleID], [PermissionTitle], [PermissionValue], [Nullity], [StateFlag], [ParentID]) VALUES (407, N'查看', 1, 0, 0, 4)
INSERT [dbo].[Base_ModulePermission] ([ModuleID], [PermissionTitle], [PermissionValue], [Nullity], [StateFlag], [ParentID]) VALUES (407, N'编辑', 4, 0, 0, 4)
INSERT [dbo].[Base_ModulePermission] ([ModuleID], [PermissionTitle], [PermissionValue], [Nullity], [StateFlag], [ParentID]) VALUES (407, N'删除', 8, 0, 0, 4)
INSERT [dbo].[Base_ModulePermission] ([ModuleID], [PermissionTitle], [PermissionValue], [Nullity], [StateFlag], [ParentID]) VALUES (500, N'查看', 1, 0, 0, 5)
INSERT [dbo].[Base_ModulePermission] ([ModuleID], [PermissionTitle], [PermissionValue], [Nullity], [StateFlag], [ParentID]) VALUES (500, N'添加', 2, 0, 0, 5)
INSERT [dbo].[Base_ModulePermission] ([ModuleID], [PermissionTitle], [PermissionValue], [Nullity], [StateFlag], [ParentID]) VALUES (500, N'编辑', 4, 0, 0, 5)
INSERT [dbo].[Base_ModulePermission] ([ModuleID], [PermissionTitle], [PermissionValue], [Nullity], [StateFlag], [ParentID]) VALUES (500, N'删除', 8, 0, 0, 5)
INSERT [dbo].[Base_ModulePermission] ([ModuleID], [PermissionTitle], [PermissionValue], [Nullity], [StateFlag], [ParentID]) VALUES (501, N'查看', 1, 0, 0, 5)
INSERT [dbo].[Base_ModulePermission] ([ModuleID], [PermissionTitle], [PermissionValue], [Nullity], [StateFlag], [ParentID]) VALUES (501, N'编辑', 4, 0, 0, 5)
INSERT [dbo].[Base_ModulePermission] ([ModuleID], [PermissionTitle], [PermissionValue], [Nullity], [StateFlag], [ParentID]) VALUES (502, N'查看', 1, 0, 0, 5)
INSERT [dbo].[Base_ModulePermission] ([ModuleID], [PermissionTitle], [PermissionValue], [Nullity], [StateFlag], [ParentID]) VALUES (600, N'查看', 1, 0, 0, 6)

-- 用户表
TRUNCATE TABLE Base_Users

INSERT INTO Base_Users(Username,Password,RoleID) VALUES('admin','E10ADC3949BA59ABBE56E057F20F883E',1)

-- 角色表
TRUNCATE TABLE Base_Roles

INSERT INTO Base_Roles(RoleName,Description) VALUES('超级管理员','超级管理员')

-- 平台信息
TRUNCATE TABLE [dbo].[QPAdminSiteInfo]

INSERT [dbo].[QPAdminSiteInfo] ([SiteName], [PageSize], [CopyRight]) VALUES (N'平台管理后台', 30, N'深圳市有限公司')


