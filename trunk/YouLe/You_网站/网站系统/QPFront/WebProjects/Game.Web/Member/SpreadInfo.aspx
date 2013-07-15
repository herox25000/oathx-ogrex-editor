﻿<%@ Page Language="C#" AutoEventWireup="true" CodeBehind="SpreadInfo.aspx.cs" Inherits="Game.Web.Member.SpreadInfo" %>
<%@ Import Namespace="Game.Facade" %>

<%@ Register TagPrefix="qp" TagName="Header" Src="~/Themes/Standard/Common_Header.ascx" %>
<%@ Register TagPrefix="qp" TagName="Footer" Src="~/Themes/Standard/Common_Footer.ascx" %>
<%@ Register TagPrefix="qp" TagName="Info" Src="~/Themes/Standard/User_Info.ascx" %>
<%@ Register TagPrefix="qp" TagName="Logon" Src="~/Themes/Standard/User_Logon.ascx" %>
<%@ Register TagPrefix="qp" TagName="UserSidebar" Src="~/Themes/Standard/User_Sidebar.ascx" %>

<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">

<html xmlns="http://www.w3.org/1999/xhtml" >
<head runat="server">
    <meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
    <meta http-equiv="X-UA-Compatible" content="IE=EmulateIE7" />

    <link rel="stylesheet" type="text/css" href="/style/layout.css" />
    <link rel="stylesheet" type="text/css" href="/style/global.css" />
    <link rel="stylesheet" type="text/css" href="/style/user_layout.css" />
    <link rel="stylesheet" type="text/css" href="/style/game_layout.css" />
    <link rel="stylesheet" type="text/css" href="/style/news_layout.css" />    

    <script src="../js/jquery-1.5.2.min.js" type="text/javascript"></script>
      
</head>
<body>

<qp:Header ID="sHeader" runat="server" />

<!--页面主体开始-->
<div class="userBody" style="margin-top:8px;">
	<div class="userTop"></div>
	<div class="userBg">
	    <!--左边页面开始-->
	    <div class="LeftSide">
			<% if (Fetch.GetUserCookie() == null)
           { %>
        <qp:Logon ID="sLogon" runat="server" />
        <%}
           else
           { %>
        <qp:Info ID="sInfo" runat="server" />
        <% } %>
        
<div class="LeftSide mtop10">

<qp:UserSidebar ID="sUserSidebar" runat="server" />

</div>		
<div class="clear"></div>					
		</div>
		<!--左边页面结束-->
		
		<!--右边页面开始-->		
		<div class="mainRight2">
			<div class="userRigthBody">
				<div class="userRigthTitle">会员中心 - 推广服务 - 推广明细查询</div>
				<div class="userRigthBg">
                <!--推广明细开始-->
                
                <form id="form1" runat="server">
                
                <div id="divSpread" runat="server">
                
                <table width="100%" border="0" cellpadding="0" cellspacing="1" bgcolor="#BAD7E5" class="leftTop">
                <tr align="center" class="bold">
                    <td class="leftTop trBg">昵称</td>
                    <td class="leftTop trBg">游戏ＩＤ</td>   
                    <td class="leftTop trBg">单用户贡献金币</td> 
                    <td class="leftTop trBg">最早推荐时间</td>     
                    <td class="leftTop trBg">&nbsp;</td>                                                                  
                </tr>
                   
                    <asp:Repeater ID="rptSpreaderList" runat="server" 
                                    onitemcommand="rptSpreaderList_ItemCommand">
                        <ItemTemplate>
                            <tr align="center" class="trBg1">
                                <td><%# GetNickNameByUserID( Convert.ToInt32( Eval( "ChildrenID" ) ) )%></td>
                                <td><%# GetGameIDByUserID(Convert.ToInt32(Eval("ChildrenID")))%></td>
                                <td><%# Eval("Score","{0:N}")%></td>
                                <td><%# Eval("CollectDate")%></td>
                                <td><asp:LinkButton ID="lbtnContribution" runat="server" CommandArgument='<%# Eval("ChildrenID")+"$"+Eval("Score","{0:N}") %>' CommandName="sel" CssClass="ll" Text="贡献明细"></asp:LinkButton></td>
                            </tr>
                        </ItemTemplate>
                    </asp:Repeater>
                
                <tr id="trNoData" runat="server"><td bgcolor='#FFFFFF' colspan='5' align='center'><br>没有任何信息!息!<br><br></td></tr>    
                
                </table>
                <table width="100%" border="0" align="center" cellpadding="0" cellspacing="0">
                    <tr>
                        <td class="page2" align="right">
                            <webdiyer:AspNetPager ID="anpPage"  runat="server" AlwaysShow="true" FirstPageText="首页"
                                    LastPageText="末页" PageSize="20" NextPageText="下页" PrevPageText="上页" ShowBoxThreshold="0" ShowCustomInfoSection="Left"
                                    LayoutType="Table" NumericButtonCount="5" CustomInfoHTML="总记录：%RecordCount%　页码：%CurrentPageIndex%/%PageCount%　每页：%PageSize%"
                                    UrlPaging="false" onpagechanging="anpPage_PageChanging">
                                </webdiyer:AspNetPager>
                        </td>
                    </tr>
                </table>  
                
                </div>
                
                <!-- 贡献明细查询 -->
                <div id="divContribution" runat="server">
                
                <div class="viewTop">被推荐人：<span class="hong"><asp:Label ID="lblAccounts" runat="server"></asp:Label></span></div>
                <div class="page"><asp:LinkButton ID="lbtnBack" runat="server" ToolTip="返回推广明细" 
                        Text="返回推广明细" onclick="lbtnBack_Click"></asp:LinkButton></div>
		  	    <table width="100%" border="0" cellpadding="0" cellspacing="1" bgcolor="#BAD7E5" class="leftTop box">
                  <tr align="center" class="bold">
                    <td class="leftTop trBg">日期</td>
                    <td class="leftTop trBg">贡献金币</td>                        
                    <td class="leftTop trBg">类别</td>
                    <td class="leftTop trBg">备注</td>                                            
                  </tr>   
                  
                      <asp:Repeater ID="rptContributionList" runat="server">
                        <ItemTemplate>
                            <tr align="center" class="trBg1">
                                <td><%# Eval("CollectDate") %></td>
                                <td><%# Eval("Score","{0:N}") %></td>
                                <td><%# (Convert.ToInt32(Eval("TypeID")) == 1 ? "注册" : Convert.ToInt32(Eval("TypeID")) == 2 ? "游戏时长30小时" : "结算")%></td>
                                <td align="left"><%# Eval("CollectNote")%></td>
                            </tr>
                        </ItemTemplate>
                      </asp:Repeater>
                    
                <tr class="trBg1" align="center">
                    <td>合计：</td>
                    <td class="leftTop trBg"><%= ViewState["total"].ToString() %></td>
                    <td colspan="100"></td>
                </tr>
                
                </table>
                <table width="100%" border="0" align="center" cellpadding="0" cellspacing="0">
                    <tr>
                        <td class="page2" align="right">
                            <webdiyer:AspNetPager ID="anpPage2"  runat="server" AlwaysShow="true" FirstPageText="首页"
                                    LastPageText="末页" PageSize="20" NextPageText="下页" PrevPageText="上页" ShowBoxThreshold="0" ShowCustomInfoSection="Left"
                                    LayoutType="Table" NumericButtonCount="5" CustomInfoHTML="总记录：%RecordCount%　页码：%CurrentPageIndex%/%PageCount%　每页：%PageSize%"
                                    UrlPaging="false" onpagechanging="anpPage2_PageChanging">
                                </webdiyer:AspNetPager>
                        </td>
                    </tr>
                </table>  
                
                </div>
                <!-- 贡献明细查询结束 -->
                
                </form>
                <!--推广明细结束-->
                <div class="clear"></div>
		 	    </div>
				<div class="userRightBottom"><div class="clear"></div></div>
				<div class="clear"></div>
			</div>
			<div class="clear"></div>
		</div>
		<!--右边页面结束-->
		<div class="clear"></div>
	</div>
	<div class="userBottom"><div class="clear"></div></div>
<div class="clear"></div>
</div>
<!--页面主体结束-->

<qp:Footer ID="sFooter" runat="server" />

</body>
</html>
