﻿<%@ Page Language="C#" AutoEventWireup="true" CodeBehind="ConfineMachineInfo.aspx.cs" Inherits="Game.Web.Module.AccountManager.ConfineMachineInfo" %>

<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">
<head runat="server">
    <title></title>
    <link href="../../styles/layout.css" rel="stylesheet" type="text/css" />

    <script type="text/javascript" src="../../scripts/common.js"></script>

    <script type="text/javascript" src="../../scripts/My97DatePicker/WdatePicker.js"></script>

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
                你当前位置：用户系统 - 限制机器码管理
            </td>
        </tr>
    </table>
    <table width="100%" border="0" align="center" cellpadding="0" cellspacing="0">
        <tr>
            <td class="titleOpBg Lpd10">
                <input type="button" value="返回" class="btn wd1" onclick="Redirect('ConfineMachineList.aspx')" />
                <input class="btnLine" type="button" />
                <asp:Button ID="btnSave" runat="server" Text="保存" CssClass="btn wd1" OnClick="btnSave_Click" />
            </td>
        </tr>
    </table>
    <table width="100%" border="0" align="center" cellpadding="0" cellspacing="0" class="listBg2">
        <tr>
            <td height="35" colspan="2" class="f14 bold Lpd10 Rpd10">
                <div class="hg3  pd7">
                    限制机器码信息</div>
            </td>
        </tr>
        <tr>
            <td class="listTdLeft">
                限制机器码：
            </td>
            <td>
                <asp:Literal ID="ltString" runat="server"></asp:Literal>
                <asp:TextBox ID="txtString" runat="server" CssClass="text" MaxLength="32"></asp:TextBox>
            </td>
        </tr>
        <tr>
            <td class="listTdLeft">
                选项：
            </td>
            <td>
                <asp:CheckBox ID="ckbEnjoinLogon" runat="server" Text="限制登录" />&nbsp;&nbsp;&nbsp;&nbsp;
                <asp:CheckBox ID="ckbEnjoinRegister" runat="server" Text="限制注册" />
            </td>
        </tr>
        <tr>
            <td class="listTdLeft">
                失效时间：
            </td>
            <td>
                <asp:TextBox ID="txtEnjoinOverDate" runat="server" CssClass="text wd2"></asp:TextBox><img src="../../Images/btn_calendar.gif"
                    onclick="WdatePicker({el:'txtEnjoinOverDate',skin:'whyGreen',dateFmt:'yyyy-MM-dd'})" style="cursor: pointer; vertical-align: middle" />
            </td>
        </tr>
        <tr>
            <td class="listTdLeft">
                警告：
            </td>
            <td>
                <span class="hong"> 失效时间不填写，则默认为永久限制</span>
            </td>
        </tr>
         <tr>
            <td class="listTdLeft">
                备注：
            </td>
            <td>             
                <asp:TextBox ID="txtCollectNote" runat="server" CssClass="text" maxlength="32" style="width:500px;" ></asp:TextBox>
            </td>
        </tr>
    </table>
    <table width="100%" border="0" align="center" cellpadding="0" cellspacing="0">
        <tr>
            <td class="titleOpBg Lpd10">
                <input type="button" value="返回" class="btn wd1" onclick="Redirect('ConfineMachineList.aspx')" />
                <input class="btnLine" type="button" />
                <asp:Button ID="btnSave1" runat="server" Text="保存" CssClass="btn wd1" OnClick="btnSave_Click" />
            </td>
        </tr>
    </table>
    </form>
</body>
</html>
