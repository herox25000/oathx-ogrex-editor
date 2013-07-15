using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;

using Game.Web.UI;
using Game.Utils;
using Game.Entity.Treasure;
using Game.Kernel;
using Game.Entity.Enum;

namespace Game.Web.Module.AccountManager
{
    public partial class AndroidInfo : AdminPage
    {
        #region 窗口事件

        protected void Page_Load(object sender, EventArgs e)
        {
            //判断权限
            AuthUserOperationPermission( Permission.Read );
            if (!Page.IsPostBack)
            {
                BindServerList();
                AndroidDataBind();
            }
        }

        protected void btnSave_Click(object sender, EventArgs e)
        {
            //判断权限
            AuthUserOperationPermission( Permission.Edit );
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

        private void AndroidDataBind()
        {
            if (IntParam <= 0)
            {
                return;
            }

            //获取类型信息
            AndroidManager android = aideTreasureFacade.GetAndroidInfo(IntParam);
            if (android == null)
            {
                ShowError("机器人信息不存在");
                Redirect("AndroidList.aspx");
                return;
            }
            ddlServerID.SelectedValue = android.ServerID.ToString().Trim();
            CtrlHelper.SetText(txtMinPlayDraw, android.MinPlayDraw.ToString());
            CtrlHelper.SetText(txtMaxPlayDraw, android.MaxPlayDraw.ToString());
            CtrlHelper.SetText(txtMinTakeScore, android.MinTakeScore.ToString());
            CtrlHelper.SetText(txtMaxTakeScore, android.MaxTakeScore.ToString());
            CtrlHelper.SetText(txtMinReposeTime, android.MinReposeTime.ToString());
            CtrlHelper.SetText(txtMaxReposeTime, android.MaxReposeTime.ToString());
            //服务类型
            int serviceGender = android.ServiceGender;
            if (chkServiceGender.Items.Count > 0)
            {
                foreach (ListItem item in chkServiceGender.Items)
                {
                    item.Selected = int.Parse(item.Value) == (serviceGender & int.Parse(item.Value));
                }
            }
            //服务时间
            int serverTime = android.ServiceTime;
            if (chkServiceTime.Items.Count > 0)
            {
                foreach (ListItem item in chkServiceTime.Items)
                {
                    item.Selected = int.Parse(item.Value) == (serverTime & int.Parse(item.Value));
                }
            }
            CtrlHelper.SetText(txtAndroidNote, android.AndroidNote);
            rbtnNullity.SelectedValue = android.Nullity.ToString().Trim();
            CtrlHelper.SetText(lblCreateDate, android.CreateDate.ToString());
        }
        #endregion

        #region 处理方法

        private void ProcessData()
        {
            AndroidManager android = new AndroidManager();
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
            android.UserID = IntParam;

            Message msg = new Message();
            msg = aideTreasureFacade.UpdateAndroid(android);

            if (msg.Success)
            {
                //ShowInfo("机器人配置成功", "AndroidList.aspx", 1200);
                MessageBoxClose( "操作成功" );
            }
            else
            {
                MessageBox( "操作失败" );
            }
        }
        #endregion        
    }
}
