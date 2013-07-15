﻿<%@ Page Language="C#" AutoEventWireup="true" CodeBehind="GameGameItemList.aspx.cs" Inherits="Game.Web.Module.AppManager.GameGameItemList" %>
<%@ Register Src="~/Themes/TabGame.ascx" TagPrefix="Fox" TagName="Tab" %>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">

<html xmlns="http://www.w3.org/1999/xhtml" >
<head runat="server">
    <link href="../../styles/layout.css" rel="stylesheet" type="text/css" />
    <script type="text/javascript" src="../../scripts/common.js"></script>
    <title></title>
</head>
<body>
    <form id="form1" runat="server">
    <!-- 头部菜单 Start -->
    <table width="100%" border="0" cellpadding="0" cellspacing="0" class="title">
        <tr>
            <td width="19" height="25" valign="top"  class="Lpd10"><div class="arr"></div></td>
            <td width="1232" height="25" valign="top" align="left">你当前位置：游戏系统 - 游戏管理</td>
        </tr>
    </table>
    <!-- 头部菜单 End -->
     <Fox:Tab ID="fab1" runat="server" NavActivated="A"></Fox:Tab>
    <table width="100%" border="0" align="center" cellpadding="0" cellspacing="0">
        <tr>
            <td height="39" class="titleOpBg">
                <input type="button" value="新增" class="btn wd1" onclick="Redirect('GameGameItemInfo.aspx?cmd=add')" />
                <input class="btnLine" type="button" /> 
                <asp:Button ID="btnDelete" runat="server" Text="删除" CssClass="btn wd1" 
                    onclick="btnDelete_Click" OnClientClick="return deleteop()" />                
            </td>
        </tr>
    </table>  
    <div id="content">
        <table width="100%" border="0" align="center" cellpadding="0" cellspacing="0" class="box" id="list">
            <tr align="center" class="bold">
                <td style="width:30px;" class="listTitle"><input type="checkbox" name="chkAll" onclick="SelectAll(this.checked);" /></td>
                <td style="width:100px;" class="listTitle2">管理</td>
                <td class="listTitle2">模块标识</td>
                <td class="listTitle2">模块名称</td>
                <td class="listTitle2">服务端版本</td>
                <td class="listTitle2">客户端版本</td>     
                <td class="listTitle2">数据库名</td> 
                <td class="listTitle1">数据库地址</td>            
            </tr>
            <asp:Repeater ID="rptGameGameItem" runat="server">
                <ItemTemplate>
                    <tr align="center" class="list" onmouseover="currentcolor=this.style.backgroundColor;this.style.backgroundColor='#caebfc';this.style.cursor='default';"
                    onmouseout="this.style.backgroundColor=currentcolor">
                        <td><input name='cid' type='checkbox' value='<%# Eval("GameID")%>'/></td>      
                        <td>                             
                            <a class="l" href="GameGameItemInfo.aspx?cmd=edit&param=<%#Eval("GameID") %>">更新</a>              
                        </td>                
                        <td><%# Eval("GameID")%></td>
                        <td><%# Eval("GameName")%></td>
                        <td><%# CalVersion((int)Eval("ServerVersion"))%></td>
                        <td><%# CalVersion((int)Eval("ClientVersion"))%></td>
                        <td><%# Eval("DataBaseName")%></td>
                        <td><%# Eval("DataBaseAddr")%></td>
                    </tr>
                </ItemTemplate>
                <AlternatingItemTemplate>
                    <tr align="center" class="listBg" onmouseover="currentcolor=this.style.backgroundColor;this.style.backgroundColor='#caebfc';this.style.cursor='default';"
                    onmouseout="this.style.backgroundColor=currentcolor">                        
                        <td><input name='cid' type='checkbox' value='<%# Eval("GameID")%>'/></td>      
                        <td>                             
                            <a class="l" href="GameGameItemInfo.aspx?cmd=edit&param=<%#Eval("GameID") %>">更新</a>              
                        </td>                
                        <td><%# Eval("GameID")%></td>
                        <td><%# Eval("GameName")%></td>
                        <td><%# CalVersion((int)Eval("ServerVersion"))%></td>
                        <td><%# CalVersion((int)Eval("ClientVersion"))%></td>
                        <td><%# Eval("DataBaseName")%></td>
                        <td><%# Eval("DataBaseAddr")%></td>
                    </tr>
                </AlternatingItemTemplate>
            </asp:Repeater>
            <asp:Literal runat="server" ID="litNoData" Visible="false" Text="<tr class='tdbg'><td colspan='100' align='center'><br>没有任何信息!<br><br></td></tr>"></asp:Literal>
        </table>
    </div>
    <table width="100%" border="0" align="center" cellpadding="0" cellspacing="0">
        <tr>
            <td class="listTitleBg"><span>选择：</span>&nbsp;<a class="l1" href="javascript:SelectAll(true);">全部</a>&nbsp;-&nbsp;<a class="l1" href="javascript:SelectAll(false);">无</a></td>                
            <td align="right" class="page">                
                <gsp:AspNetPager ID="anpNews" runat="server" onpagechanged="anpNews_PageChanged" AlwaysShow="true" FirstPageText="首页" LastPageText="末页" PageSize="20" 
                    NextPageText="下页" PrevPageText="上页" ShowBoxThreshold="0" ShowCustomInfoSection="Left" LayoutType="Table" NumericButtonCount="5"
                    CustomInfoHTML="总记录：%RecordCount%　页码：%CurrentPageIndex%/%PageCount%　每页：%PageSize%">
                </gsp:AspNetPager>
            </td>
        </tr>
    </table>  
    <table width="100%" border="0" align="center" cellpadding="0" cellspacing="0" id="OpList">
        <tr>
            <td height="39" class="titleOpBg">
                <input type="button" value="新增" class="btn wd1" onclick="Redirect('GameGameItemInfo.aspx?cmd=add')" />
                <input class="btnLine" type="button" /> 
                <asp:Button ID="Button1" runat="server" Text="删除" CssClass="btn wd1" 
                    onclick="btnDelete_Click" OnClientClick="return deleteop()" />                
            </td>
        </tr>
    </table>  
    </form>
</body>
</html>
