﻿<%@ Page Language="C#" AutoEventWireup="true" CodeBehind="ShareDetailList.aspx.cs" Inherits="Game.Web.Module.AccountManager.ShareDetailList" %>

<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">

<html xmlns="http://www.w3.org/1999/xhtml" >
<head runat="server">
    <link href="../../styles/layout.css" rel="stylesheet" type="text/css" />

    <script type="text/javascript" src="../../scripts/common.js"></script>

    <script type="text/javascript" src="../../scripts/comm.js"></script>

    <script type="text/javascript" src="../../scripts/My97DatePicker/WdatePicker.js"></script>

    <title></title>
</head>
<body>
    <form id="form1" runat="server">
    <!-- 头部菜单 Start -->
    <table width="100%" border="0" cellpadding="0" cellspacing="0" class="title">
        <tr>
            <td width="19" height="25" valign="top" class="Lpd10">
                <div class="arr">
                </div>
            </td>
            <td width="1232" height="25" valign="top" align="left">
                你当前位置：用户系统 - 充值记录
            </td>
        </tr>
    </table>
    <!-- 头部菜单 End -->
    <table width="100%" border="0" align="center" cellpadding="0" cellspacing="0" class="titleQueBg">
        <tr>
            <td class="listTdLeft" style="width: 80px">
                日期查询：
            </td>
            <td>
                 <asp:TextBox ID="txtStartDate" runat="server" CssClass="text wd2" onfocus="WdatePicker({dateFmt:'yyyy-MM-dd',maxDate:'#F{$dp.$D(\'txtEndDate\')}'})"></asp:TextBox><img
                    src="../../Images/btn_calendar.gif" onclick="WdatePicker({el:'txtStartDate',dateFmt:'yyyy-MM-dd',maxDate:'#F{$dp.$D(\'txtEndDate\')}'})"
                    style="cursor: pointer; vertical-align: middle" />
                至
                <asp:TextBox ID="txtEndDate" runat="server" CssClass="text wd2" onfocus="WdatePicker({dateFmt:'yyyy-MM-dd',minDate:'#F{$dp.$D(\'txtStartDate\')}'})"></asp:TextBox><img
                    src="../../Images/btn_calendar.gif" onclick="WdatePicker({el:'txtEndDate',dateFmt:'yyyy-MM-dd',minDate:'#F{$dp.$D(\'txtStartDate\')}'})"
                    style="cursor: pointer; vertical-align: middle" />
                <asp:DropDownList ID="ddlShareID" runat="server">
                </asp:DropDownList>
                 <asp:DropDownList ID="ddlCardType" runat="server">                   
                </asp:DropDownList>
                <asp:Button ID="btnQuery" runat="server" Text="查询" CssClass="btn wd1" OnClick="btnQuery_Click" />
                <asp:Button ID="btnQueryTD" runat="server" Text="今天" CssClass="btn wd1" OnClick="btnQueryTD_Click" />
                <asp:Button ID="btnQueryYD" runat="server" Text="昨天" CssClass="btn wd1" OnClick="btnQueryYD_Click" />
                <asp:Button ID="btnQueryTW" runat="server" Text="本周" CssClass="btn wd1" OnClick="btnQueryTW_Click" />
                <asp:Button ID="btnQueryYW" runat="server" Text="上周" CssClass="btn wd1" OnClick="btnQueryYW_Click" />
            </td>
        </tr>
    </table>
    <table width="100%" border="0" align="center" cellpadding="0" cellspacing="0" class="Tmg7">
        <tr>
            <td class="titleOpBg Lpd10">
                <input type="button" value="关闭" class="btn wd1" onclick="window.close();" />                
            </td>
        </tr>
    </table>
    <div id="content">
        <table width="100%" border="0" align="center" cellpadding="0" cellspacing="0" class="box" id="list">
            <tr align="center" class="bold">
                <td class="listTitle">充值时间</td>
                <td class="listTitle2">服务类型</td>     
                <td class="listTitle2">用户名</td>         
                <td class="listTitle2">游戏ID</td>         
                <td class="listTitle2">订单号码</td>         
                <td class="listTitle2">卡名称</td>         
                <td class="listTitle2">卡价格</td>
                         
                <td class="listTitle2">赠送金币</td>        
                <td class="listTitle2">充值前金币</td>       
                <td class="listTitle1">订单数量</td>
                <td class="listTitle2">订单金额</td>        
                <td class="listTitle2">实付金额</td>       
                <td class="listTitle1">充值地址</td>
                <td class="listTitle1">操作用户</td>             
            </tr>
            <asp:Repeater ID="rptShareDetail" runat="server">
                <ItemTemplate>
                    <tr align="center" class="list" onmouseover="currentcolor=this.style.backgroundColor;this.style.backgroundColor='#caebfc';this.style.cursor='default';"
                    onmouseout="this.style.backgroundColor=currentcolor">               
                        <td><%# Eval("ApplyDate")%></td>
                        <td><%# GetShareName((int)Eval("ShareID"))%></td>
                        <td><%# Eval("Accounts")%></td>
                        <td><%# Eval("GameID")%></td>
                        <td><%# Eval("OrderID")%></td>    
                        <td><%# Eval( "CardTypeID" )%></td>
                        <td><%# Eval( "CardPrice" )%></td>
                        <td><%# Eval( "CardGold" )%></td>
                        <td><%# Eval( "BeforeGold" )%></td>
                        <td><%# Eval( "CardTotal" )%></td>
                        <td><%# Eval( "OrderAmount" )%></td>
                        <td><%# Eval( "PayAmount" )%></td>
                        <td title=" <%# Eval( "IPAddress" ).ToString( )%>"><%# GetAddressWithIP( Eval( "IPAddress" ).ToString( ) )%></td> 
                        <td><%# GetAccounts((int)Eval("OperUserID"))%></td>
                    </tr>
                </ItemTemplate>
                <AlternatingItemTemplate>
                    <tr align="center" class="listBg" onmouseover="currentcolor=this.style.backgroundColor;this.style.backgroundColor='#caebfc';this.style.cursor='default';"
                    onmouseout="this.style.backgroundColor=currentcolor">                                       
                        <td><%# Eval("ApplyDate")%></td>
                        <td><%# GetShareName((int)Eval("ShareID"))%></td>
                        <td><%# Eval("Accounts")%></td>
                        <td><%# Eval("GameID")%></td>
                        <td><%# Eval("OrderID")%></td>    
                        <td><%# Eval( "CardTypeID" )%></td>
                        <td><%# Eval( "CardPrice" )%></td>
                        <td><%# Eval( "CardGold" )%></td>
                        <td><%# Eval( "BeforeGold" )%></td>
                        <td><%# Eval( "CardTotal" )%></td>
                        <td><%# Eval( "OrderAmount" )%></td>
                        <td><%# Eval( "PayAmount" )%></td>
                        <td title=" <%# Eval( "IPAddress" ).ToString( )%>"><%# GetAddressWithIP( Eval( "IPAddress" ).ToString( ) )%></td> 
                        <td><%# GetAccounts((int)Eval("OperUserID"))%></td>
                    </tr>
                </AlternatingItemTemplate>
            </asp:Repeater>
            <asp:Literal runat="server" ID="litNoData" Visible="false" Text="<tr class='tdbg'><td colspan='100' align='center'><br>没有任何信息!<br><br></td></tr>"></asp:Literal>
        </table>
    </div>
    <table width="100%" border="0" align="center" cellpadding="0" cellspacing="0">
        <tr>
            <td align="right" class="page">                
                <gsp:AspNetPager ID="anpNews" runat="server" onpagechanged="anpNews_PageChanged" AlwaysShow="true" FirstPageText="首页" LastPageText="末页" PageSize="20" 
                    NextPageText="下页" PrevPageText="上页" ShowBoxThreshold="0" ShowCustomInfoSection="Left" LayoutType="Table" NumericButtonCount="5"
                    CustomInfoHTML="总记录：%RecordCount%　页码：%CurrentPageIndex%/%PageCount%　每页：%PageSize%">
                </gsp:AspNetPager>
            </td>
        </tr>
    </table>  
    </form>
</body>
</html>
