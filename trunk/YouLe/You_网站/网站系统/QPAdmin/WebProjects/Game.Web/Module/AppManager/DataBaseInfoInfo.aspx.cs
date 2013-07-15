using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;

using Game.Web.UI;
using Game.Utils;
using Game.Entity.Platform;
using Game.Kernel;
using Game.Entity.Accounts;
using Game.Facade.Aide;
using Game.Entity.Enum;

namespace Game.Web.Module.AppManager
{
    public partial class DataBaseInfoInfo : AdminPage
    {  
        #region 窗口事件

        protected void Page_Load(object sender, EventArgs e)
        {
            if (!Page.IsPostBack)
            {
                DataBaseDataBind();
            }
        }

        protected void btnSave_Click(object sender, EventArgs e)
        {
            ProcessData();
        }
        #endregion

        #region 数据加载

        private void DataBaseDataBind()
        {
            if (StrCmd == "add")
            {
                litInfo.Text = "新增";
            }
            else
            {
                litInfo.Text = "更新";
            }

            if (IntParam <= 0)
            {
                return;
            }

            //获取站点信息
            DataBaseInfo dataBaseInfo = aidePlatformFacade.GetDataBaseInfo( IntParam );
            if (dataBaseInfo == null)
            {
                ShowError("机器信息不存在");
                Redirect("DataBaseInfoList.aspx");
                return;
            }

            CtrlHelper.SetText(txtInformation, dataBaseInfo.Information.Trim());
            CtrlHelper.SetText(txtDBAddr, dataBaseInfo.DBAddr.Trim());
            CtrlHelper.SetText(txtDBPort, dataBaseInfo.DBPort.ToString().Trim());
            CtrlHelper.SetText(txtDBUser, CWHEncryptNet.XorCrevasse(dataBaseInfo.DBUser.Trim()));
            if (dataBaseInfo.DBPassword != "")
            {
                txtDBPassword.Attributes.Add("value", "********");
                CtrlHelper.SetText(hdfDBPassword, dataBaseInfo.DBPassword.Trim());
            }
            CtrlHelper.SetText(txtMachineID, dataBaseInfo.MachineID.Trim());
        }
        #endregion

        #region 处理方法

        private void ProcessData()
        {
            if ( !Utils.Validate.IsPositiveInt( txtDBPort.Text ) )
            {
                ShowError( "端口不规范，端口只能为正整数" );
                return;
            }
            DataBaseInfo dataBaseInfo = new DataBaseInfo();
            dataBaseInfo.DBAddr = CtrlHelper.GetText(txtDBAddr);
            dataBaseInfo.DBPort = CtrlHelper.GetInt(txtDBPort, 0);
            dataBaseInfo.DBUser = CWHEncryptNet.XorEncrypt(CtrlHelper.GetText(txtDBUser));
            if (CtrlHelper.GetText(hdfDBPassword) == "********")
            {
                dataBaseInfo.DBPassword = CWHEncryptNet.XorEncrypt(CtrlHelper.GetText(txtDBPassword));
            }
            else
            {
                dataBaseInfo.DBPassword = CtrlHelper.GetText(hdfDBPassword);
            }
            
            dataBaseInfo.MachineID = CtrlHelper.GetText(txtMachineID);
            dataBaseInfo.Information = CtrlHelper.GetText(txtInformation);

            Message msg = new Message();
            if (StrCmd == "add")
            {
                //判断权限
                AuthUserOperationPermission( Permission.Add );
                if ( aidePlatformFacade.IsExistsDBAddr( dataBaseInfo.DBAddr ) )
                {
                    ShowError( "地址已经存在" );
                    return;
                }
                msg = aidePlatformFacade.InsertDataBase(dataBaseInfo);
            }
            else
            {
                //判断权限
                AuthUserOperationPermission( Permission.Edit );
                dataBaseInfo.DBInfoID = IntParam;
                msg = aidePlatformFacade.UpdateDataBase(dataBaseInfo);
            }

            if (msg.Success)
            {
                if (StrCmd == "add")
                {
                    ShowInfo("机器信息增加成功", "DataBaseInfoList.aspx", 1200);
                }
                else
                {
                    ShowInfo("机器信息修改成功", "DataBaseInfoList.aspx", 1200);
                }
            }
            else
            {
                ShowError(msg.Content);
            }
        }
        #endregion        
    }
}
