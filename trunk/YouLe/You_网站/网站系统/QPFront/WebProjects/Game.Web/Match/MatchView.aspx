﻿<%@ Page Language="C#" AutoEventWireup="true" CodeBehind="MatchView.aspx.cs" Inherits="Game.Web.Match.MatchView" %>

<%@ Import Namespace="Game.Facade" %>
<%@ Register TagPrefix="qp" TagName="Header" Src="~/Themes/Standard/Common_Header.ascx" %>
<%@ Register TagPrefix="qp" TagName="Footer" Src="~/Themes/Standard/Common_Footer.ascx" %>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head runat="server">
    <meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
    <meta http-equiv="X-UA-Compatible" content="IE=EmulateIE7" />
    <link rel="stylesheet" type="text/css" href="/style/layout.css" />
    <link rel="stylesheet" type="text/css" href="/style/global.css" />
    <link rel="stylesheet" type="text/css" href="/style/contest_layout.css" />
</head>
<body>
    <qp:Header ID="sHeader" runat="server" />
    <!--页面主体开始-->
    <div class="main" style="margin-top: 8px;">
        <div class="contTop">
            <div class="nav">
                <div class="left">
                </div>
                <div class="center">
                    <ul>
                        <li class="current">
                            <a href="/Match/MatchView.aspx?XID=<%= matchID %>">赛事公告</a></li>
                        <li>
                            <a href="/Match/MatchOrder.aspx?XID=<%= matchID %>">比赛排名</a></li>
                        <li>
                            <a href="/Match/MatchQuery.aspx?XID=<%= matchID %>">个人成绩</a></li>
                    </ul>
                </div>
                <div class="right">
                </div>
            </div>
        </div>
        <div class="contMain">
            <div class="top">
            </div>
            <div class="mainBox">
                <div class="mainBox1 f12 lineHeight25" style="word-break: break-all; width: 850px;">
                    <%= content %>
                    <div id="divBtn" runat="server" align="center" class="mtop25" visible="false">
                        <a href="/Match/MatchApply.aspx?XID=<%= matchID %>" hidefocus="true">
                            <img src="/images/bm.gif" border="0" /></a></div>
                </div>
            </div>
            <div class="bottom">
            </div>
        </div>
        <div class="clear">
        </div>
    </div>
    <!--页面主体结束-->
    <qp:Footer ID="sFooter" runat="server" />
</body>
</html>
