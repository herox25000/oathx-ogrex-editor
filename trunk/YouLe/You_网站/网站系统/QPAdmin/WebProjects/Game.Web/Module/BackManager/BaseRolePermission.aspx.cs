using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;
using System.Data;

using Game.Web.UI;
using Game.Utils;
using Game.Kernel;
using Game.Entity.PlatformManager;
using Game.Entity.Enum;


namespace Game.Web.Module.BackManager
{
    public partial class BaseRolePermission : AdminPage
    {
        #region 窗口事件

        protected void Page_Load(object sender, EventArgs e)
        {
            if (!Page.IsPostBack)
            {
                GameRolePermissionBind();
            }
        }

        protected void btnSave_Click(object sender, EventArgs e)
        {
            //判断权限
            AuthUserOperationPermission( Permission.Edit );
            ProcessData();
        }


        protected void rptRolePermission_ItemDataBound(object sender, RepeaterItemEventArgs e)
        {
            if (e.Item.ItemType == ListItemType.Item || e.Item.ItemType== ListItemType.AlternatingItem)
            {
                ((Label)e.Item.FindControl("lblParentName")).Text = DataBinder.Eval(e.Item.DataItem, "Title").ToString();
                int moduleID = Convert.ToInt32(DataBinder.Eval(e.Item.DataItem, "ModuleID").ToString().Trim());
                DataSet dsCModule = aidePlatformManagerFacade.GetModuleListByModuleID(moduleID);
                GridView gvRolePermission = (GridView)e.Item.FindControl("gvRolePermission");
                CheckBox chkAll = (CheckBox)e.Item.FindControl("chkAll");
                chkAll.Attributes.Add("onclick", "SelectAllTable(this.checked,'" + gvRolePermission.ClientID + "');");

                gvRolePermission.DataSource = dsCModule;
                gvRolePermission.DataBind();

            }
        }

        protected void gvRolePermission_RowDataBound(object sender, GridViewRowEventArgs e)
        {
            if (e.Row.RowType == DataControlRowType.DataRow)
            {
                ((Label)e.Row.FindControl("lblTitle")).Text = DataBinder.Eval(e.Row.DataItem, "Title").ToString();
                int moduleID = Convert.ToInt32(DataBinder.Eval(e.Row.DataItem, "ModuleID").ToString().Trim());
                ((TextBox)e.Row.FindControl("txtModuleID")).Text = moduleID.ToString().Trim();
                DataSet dsModulePer = aidePlatformManagerFacade.GetModulePermissionList( moduleID );

                //角色权限
                CheckBoxList cblModuleRole = (CheckBoxList)e.Row.FindControl("cblModulePermission");
                DataSet dsRolePer = aidePlatformManagerFacade.GetRolePermissionList( IntParam );
                if (dsModulePer.Tables[0].Rows.Count == 0)
                {
                    ListItem li = new ListItem();
                    li.Text = "全部控制";
                    li.Value = "0";
                    DataRow[] row = dsRolePer.Tables[0].Select("ModuleID=" + moduleID);
                    if (row.Length > 0)
                    {
                        li.Selected = true;
                    }
                    cblModuleRole.Items.Add(li);
                }
                else
                {
                    foreach (DataRow dr in dsModulePer.Tables[0].Rows)
                    {
                        ListItem li = new ListItem();
                        li.Text = dr["PermissionTitle"].ToString();
                        li.Value = dr["PermissionValue"].ToString();
                        DataRow[] row = dsRolePer.Tables[0].Select("ModuleID=" + moduleID);
                        if (row.Length > 0)
                        {
                            DataRow row0 = row[0];
                            if ((Convert.ToInt64(row0["OperationPermission"].ToString().Trim()) & Convert.ToInt64(dr["PermissionValue"].ToString().Trim())) > 0)
                            {
                                li.Selected = true;
                            }
                        }
                        cblModuleRole.Items.Add(li);
                    }
                }
            }
        }
        #endregion

        #region 数据加载

        private void GameRolePermissionBind()
        {

            if (IntParam <= 0)
            {
                return;
            }
            litInfo.Text = "【" + GetRoleName(IntParam) + "】";

            //获取角色权限信息
            if (IntParam == 1)
            {
                litSuper.Text = "<超级管理员默认具有全部权限>";
            }
            else
            {
                DataSet dsPModule = aidePlatformManagerFacade.GetModuleParentList( );
                rptRolePermission.DataSource = dsPModule;
                rptRolePermission.DataBind();
            }
        }
        #endregion

        #region 处理方法

        private void ProcessData()
        {
            Base_RolePermission rolePermission = new Base_RolePermission();
            rolePermission.RoleID = IntParam;
            aidePlatformManagerFacade.DeleteRolePermission( IntParam );
            for (int i = 0; i < rptRolePermission.Items.Count; i++)
            {                
                int crtModuleID = 0;//入库模块标记
                Int64 crtPrivValue = 0;//入库权限值
                GridView gvRolePermission = (GridView)rptRolePermission.Items[i].FindControl("gvRolePermission");
                for (int j = 0; j < gvRolePermission.Rows.Count; j++)
                {
                    bool ret = false;
                    crtPrivValue = 0;
                    TextBox txtModuleID = (TextBox)gvRolePermission.Rows[j].FindControl("txtModuleID");
                    crtModuleID = Convert.ToInt32(txtModuleID.Text);
                    CheckBoxList cblModulePermission = (CheckBoxList)gvRolePermission.Rows[j].FindControl("cblModulePermission");
                    for (int k = 0; k < cblModulePermission.Items.Count; k++)
                    {
                        if (cblModulePermission.Items[k].Selected)
                        {
                            crtPrivValue |= Convert.ToInt64(cblModulePermission.Items[k].Value);
                            ret = true;
                        }
                    }

                    if (ret)
                    {
                        rolePermission.ModuleID = crtModuleID;
                        rolePermission.OperationPermission = crtPrivValue;
                        Message msg = aidePlatformManagerFacade.InsertRolePermission( rolePermission );
                        if (!msg.Success)
                        {
                            ShowError(msg.Content);
                        }
                    }
                }
            }

            ShowInfo("角色权限配置成功", "BaseRoleList.aspx", 1200);
        }
        #endregion              
    }
}
