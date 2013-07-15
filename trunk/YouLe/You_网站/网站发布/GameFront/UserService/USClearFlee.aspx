﻿<%@ Page Language="C#" AutoEventWireup="true" CodeBehind="USClearFlee.aspx.cs" Inherits="Game.Web.UserService.USClearFlee" %>

<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">

<html xmlns="http://www.w3.org/1999/xhtml" >
<head id="Head1" runat="server">
    <meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
    <meta http-equiv="X-UA-Compatible" content="IE=EmulateIE7" />
    
    <link rel="stylesheet" type="text/css" href="/style/client.css" /> 

    <script src="../js/jquery-1.5.2.min.js" type="text/javascript"></script>
</head>
<body>
<br />
 <div class="userRigthBg2">
				    <!--逃跑清零开始-->
				    <form id="form1" runat="server" runat="server">
				    <div class="userRigthBg2">
                      <!--<span><asp:Label ID="lblAccounts" runat="server" Visible="false"></asp:Label>你有以下<asp:Label ID="lblNumber" runat="server"></asp:Label>款游戏需要进行逃跑清零：</span>-->
                      <table width="100%" border="0" cellpadding="0" cellspacing="1" bgcolor="#BAD7E5" class="leftTop">
                        <tr align="center" class="bold">
                          <td class="leftTop trBg" style="width:40%;">游戏名称</td>
                          <td class="leftTop trBg" style="width:40%;">逃跑数</td>
                          <td class="leftTop trBg" style="width:20%;">清零</td>
                        </tr>
                          <asp:Repeater ID="rptFleeList" runat="server" 
                                    onitemcommand="rptFleeList_ItemCommand">
                            <ItemTemplate>
                                <tr align="center" class="trBg1">
                                  <td><%# Eval("KindName") %></td>
                                  <td><%# Eval("FleeCount") %></td>
                                  <td>
                                    <asp:LinkButton ID="btnClear" runat="server" CommandName="Clear" CommandArgument='<%# Eval("KindID") %>' OnClientClick="return confirm('确定要清零吗?')" Text="清零" CssClass="lan"></asp:LinkButton>
                                  </td>
                                </tr>
                            </ItemTemplate>
                          </asp:Repeater>
                      </table>
                    </div>
	                <!--逃跑清零结束-->
	                </form>
	                
	                <div class="loginHint" id="divRight" runat="server">   
	                </div>
		 	    </div>
</body>
</html>