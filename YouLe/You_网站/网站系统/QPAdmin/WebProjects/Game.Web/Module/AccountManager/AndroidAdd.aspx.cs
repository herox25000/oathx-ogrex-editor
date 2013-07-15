using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;
using System.Data;

using Game.Web.UI;
using Game.Utils;
using Game.Entity.Treasure;
using Game.Kernel;
using Game.Entity.Accounts;
using Game.Entity.Enum;

namespace Game.Web.Module.AccountManager
{
    public partial class AndroidAdd : AdminPage
    {
        #region 窗口事件

        protected void Page_Load(object sender, EventArgs e)
        {
            //判断权限
            AuthUserOperationPermission( Permission.Read );
            if (!Page.IsPostBack)
            {
                BindServerList();
            }
        }

        protected void rbtnType_SelectedIndexChanged(object sender, EventArgs e)
        {
            if (rbtnType.SelectedValue.Trim() == "0")
            {
                lblAndroidName.Text = "机器人帐号：";
            }
            else
            {
                lblAndroidName.Text = "机器人个数：";
            }
        }

        protected void btnSave_Click(object sender, EventArgs e)
        {
            //判断权限
            AuthUserOperationPermission( Permission.Add );
            ProcessData();
        }
        #endregion

        #region 数据加载

        //绑定房间
        private void BindServerList()
        {
           PagerSet pagerSet = aidePlatformFacade.GetGameRoomInfoList(1, Int32.MaxValue, "WHERE Nullity=0", "ORDER BY ServerID ASC");
            if (pagerSet.PageSet.Tables[0].Rows.Count > 0)
            {
                ddlServerID.DataSource = pagerSet.PageSet;
                ddlServerID.DataTextField = "ServerName";
                ddlServerID.DataValueField = "ServerID";
                ddlServerID.DataBind();
            }
        }        
        #endregion

        #region 处理方法

        private void ProcessData()
        {
            AndroidManager android = new AndroidManager();
            Message msg = new Message();

            if (rbtnType.SelectedValue.Trim() == "0")
            {
                AccountsInfo accounts = aideAccountsFacade.GetAccountInfoByAccount(CtrlHelper.GetText(txtAndroidName));
                if (accounts == null || accounts.IsAndroid == 0)
                {
                    ShowError("该机器人不存在");
                    return;
                }
                else
                {
                    AndroidManager androidExsits = aideTreasureFacade.GetAndroidInfo(accounts.UserID);
                    if (androidExsits != null)
                    {
                        ShowError("该机器人已经被添加");
                        return;
                    }
                    
                    //添加机器人
                    android.UserID = accounts.UserID;
                    android.ServerID = Convert.ToInt32(ddlServerID.SelectedValue.Trim());
                    android.MinPlayDraw = CtrlHelper.GetInt(txtMinPlayDraw, 0);
                    android.MaxPlayDraw = CtrlHelper.GetInt(txtMaxPlayDraw, 0);
                    android.MinTakeScore = CtrlHelper.GetInt(txtMinTakeScore, 0);
                    android.MaxTakeScore = CtrlHelper.GetInt(txtMaxTakeScore, 0);
                    android.MinReposeTime = CtrlHelper.GetInt(txtMinReposeTime, 0);
                    android.MaxReposeTime = CtrlHelper.GetInt(txtMaxReposeTime, 0);
                    //机器人类型
                    int serviceGender = 0;
                    foreach (ListItem item in chkServiceGender.Items)
                    {
                        if (item.Selected)
                        {
                            serviceGender |= int.Parse(item.Value);
                        }
                    }
                    android.ServiceGender = serviceGender;
                    //机器人服务时间
                    int serviceTime = 0;
                    foreach (ListItem item in chkServiceTime.Items)
                    {
                        if (item.Selected)
                        {
                            serviceTime |= int.Parse(item.Value);
                        }
                    }
                    android.ServiceTime = serviceTime;

                    android.AndroidNote = CtrlHelper.GetText(txtAndroidNote);
                    android.Nullity = Convert.ToByte(rbtnNullity.SelectedValue.Trim());
                    msg = aideTreasureFacade.InsertAndroid(android);
                    if (msg.Success)
                    {
                        ShowInfo("成功添加了机器人 "+accounts.Accounts, "AndroidList.aspx", 1200);
                    }
                    else
                    {
                        ShowError(msg.Content);
                    }
                }
            }
            else
            {
                #region 检查

                try
                {
                    Convert.ToUInt32(txtAndroidName.Text);
                }
                catch
                {
                    ShowError("机器人个人填写非法");
                    return;
                }
                #endregion

                PagerSet pagerSet = aideAccountsFacade.GetAccountsList( 1 , Convert.ToInt32( txtAndroidName.Text ) , "WHERE IsAndroid=1 AND UserID NOT IN (SELECT UserID FROM QPTreasureDB.dbo.AndroidManager)" , "ORDER BY NEWID()" );
                if (pagerSet.PageSet.Tables[0].Rows.Count == 0)
                {
                    ShowError("没有可用的机器人帐号");
                    return;
                }

                foreach (DataRow dr in pagerSet.PageSet.Tables[0].Rows)
                {
                    android.UserID = Convert.ToInt32(dr["UserID"]);
                    android.ServerID = Convert.ToInt32(ddlServerID.SelectedValue.Trim());
                    android.MinPlayDraw = CtrlHelper.GetInt(txtMinPlayDraw, 0);
                    android.MaxPlayDraw = CtrlHelper.GetInt(txtMaxPlayDraw, 0);
                    android.MinTakeScore = CtrlHelper.GetInt(txtMinTakeScore, 0);
                    android.MaxTakeScore = CtrlHelper.GetInt(txtMaxTakeScore, 0);
                    android.MinReposeTime = CtrlHelper.GetInt(txtMinReposeTime, 0);
                    android.MaxReposeTime = CtrlHelper.GetInt(txtMaxReposeTime, 0);
                    //机器人类型
                    int serviceGender = 0;
                    foreach (ListItem item in chkServiceGender.Items)
                    {
                        if (item.Selected)
                        {
                            serviceGender |= int.Parse(item.Value);
                        }
                    }
                    android.ServiceGender = serviceGender;
                    //机器人服务时间
                    int serviceTime = 0;
                    foreach (ListItem item in chkServiceTime.Items)
                    {
                        if (item.Selected)
                        {
                            serviceTime |= int.Parse(item.Value);
                        }
                    }
                    android.ServiceTime = serviceTime;
                    android.AndroidNote = CtrlHelper.GetText(txtAndroidNote);
                    android.Nullity = Convert.ToByte(rbtnNullity.SelectedValue.Trim());
                    aideTreasureFacade.InsertAndroid(android);
                }
                ShowInfo( "成功添加了" + pagerSet.PageSet.Tables[0].Rows.Count+ "个机器人" , "AndroidList.aspx" , 1200 );
            }         
        }
        #endregion              
    }
}
