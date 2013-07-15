using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;
using System.Collections;

using Game.Web.UI;
using Game.Utils;
using Game.Entity.Platform;
using Game.Kernel;
using Game.Entity.Accounts;
using Game.Facade.Aide;
using Game.Entity.Enum;

namespace Game.Web.Module.AppManager
{
    public partial class GameGameItemInfo : AdminPage
    {
        #region 窗口事件

        protected void Page_Load(object sender, EventArgs e)
        {
            if (!Page.IsPostBack)
            {
                if ( IntParam <= 0 && StrCmd.Equals( "add" ) )
                    txtGameID.Text = ( aidePlatformFacade.GetMaxGameKindID( ) + 1 ).ToString( );
                BindDataBaseAddr();
                BindSupporType();
                GameGameItemDataBind();
            }
        }

        protected void btnSave_Click(object sender, EventArgs e)
        {
            ProcessData();
        }
        #endregion

        #region 数据加载

        /// <summary>
        /// 绑定支持类型
        /// </summary>
        private void BindSupporType()
        {
            IList<EnumDescription> list = SupporTypeHelper.GetSupporTypeList(typeof(SupporTypeStatus));
            chklSupporType.DataSource = list;
            chklSupporType.DataTextField = "Description";
            chklSupporType.DataValueField = "EnumValue";
            chklSupporType.DataBind();
        }

        /// <summary>
        /// 绑定数据库地址
        /// </summary>
        private void BindDataBaseAddr()
        {
            PagerSet pagerSet = aidePlatformFacade.GetDataBaseList(1, Int32.MaxValue, "", "ORDER BY DBInfoID ASC");
            if (pagerSet.PageSet.Tables[0].Rows.Count > 0)
            {
                ddlDataBaseAddr.DataSource = pagerSet.PageSet;
                ddlDataBaseAddr.DataTextField = "Information";
                ddlDataBaseAddr.DataValueField = "DBAddr";
                ddlDataBaseAddr.DataBind();
            }
        }

        private void GameGameItemDataBind()
        {
            if (StrCmd == "add")
            {
                litInfo.Text = "新增";
                txtGameID.Enabled = true;
            }
            else
            {
                litInfo.Text = "更新";
                txtGameID.Enabled = false;
            }

            if (IntParam <= 0)
            {
                return;
            }

            //获取模块信息
            GameGameItem gameGameItem = aidePlatformFacade.GetGameGameItemInfo(IntParam);
            if (gameGameItem == null)
            {
                ShowError("模块信息不存在");
                Redirect("GameGameItemList.aspx");
                return;
            }

            CtrlHelper.SetText(txtGameID, gameGameItem.GameID.ToString().Trim());
            CtrlHelper.SetText(txtGameName, gameGameItem.GameName.Trim());
            CtrlHelper.SetText(txtDataBaseName, gameGameItem.DataBaseName.Trim());
            ddlDataBaseAddr.SelectedValue = gameGameItem.DataBaseAddr.Trim();
            CtrlHelper.SetText(txtServerVersion, CalVersion(gameGameItem.ServerVersion));
            CtrlHelper.SetText(txtClientVersion, CalVersion(gameGameItem.ClientVersion));
            CtrlHelper.SetText(txtServerDLLName, gameGameItem.ServerDLLName.Trim());
            CtrlHelper.SetText(txtClientExeName, gameGameItem.ClientExeName.Trim());
            //支持类型
            if (chklSupporType.Items.Count > 0)
            {
                foreach (ListItem item in chklSupporType.Items)
                {
                    item.Selected = (gameGameItem.SuporType & Convert.ToInt32(item.Value)) != 0;
                }
            }
        }
        #endregion

        #region 处理方法

        private void ProcessData()
        {
            GameGameItem gameGameItem = new GameGameItem();
            string gameID = CtrlHelper.GetText( txtGameID );
            if ( !Utils.Validate.IsPositiveInt( gameID ) )
            {
                ShowError( "游戏标识不合法，游戏标识只能为正整数" );
                return;
            }
            gameGameItem.GameID = Convert.ToInt32( gameID );
            gameGameItem.GameName = CtrlHelper.GetText(txtGameName);
            //支持类型
            int supporType = 0;
            foreach (ListItem item in chklSupporType.Items)
            {
                if (item.Selected)
                {
                    supporType |= Convert.ToInt32(item.Value);
                }
            }
            gameGameItem.SuporType = supporType;
            gameGameItem.DataBaseAddr = ddlDataBaseAddr.SelectedValue.Trim();
            gameGameItem.DataBaseName = CtrlHelper.GetText(txtDataBaseName);
            gameGameItem.ServerVersion = CalVersion2(CtrlHelper.GetText(txtServerVersion));
            gameGameItem.ClientVersion = CalVersion2(CtrlHelper.GetText(txtClientVersion));
            gameGameItem.ServerDLLName = CtrlHelper.GetText(txtServerDLLName);
            gameGameItem.ClientExeName = CtrlHelper.GetText(txtClientExeName);
            
            Message msg = new Message();
            if (StrCmd == "add")
            {
                //判断权限
                AuthUserOperationPermission( Permission.Add );
                if ( aidePlatformFacade.IsExistsGameID( gameGameItem.GameID ) )
                {
                    ShowError( "模块标识已经存在");
                    return;
                }
                msg = aidePlatformFacade.InsertGameGameItem(gameGameItem);
            }
            else
            {
                //判断权限
                AuthUserOperationPermission( Permission.Edit );
                msg = aidePlatformFacade.UpdateGameGameItem(gameGameItem);
            }

            if (msg.Success)
            {
                if (StrCmd == "add")
                {
                    ShowInfo("模块信息增加成功", "GameGameItemList.aspx", 1200);
                }
                else
                {
                    ShowInfo("模块信息修改成功", "GameGameItemList.aspx", 1200);
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
