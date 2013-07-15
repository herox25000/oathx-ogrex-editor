using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;
using System.Text;

using Game.Web.UI;
using Game.Kernel;
using Game.Utils;
using Game.Entity.Enum;

namespace Game.Web.Module.BackManager
{
    public partial class BaseUserList : AdminPage
    {
        #region 窗口事件

        protected void Page_Load(object sender, EventArgs e)
        {
            if (!IsPostBack)
            {
                GameUserDataBind();
            }
        }

        protected void anpNews_PageChanged(object sender, EventArgs e)
        {
            GameUserDataBind();
        }

        /// <summary>
        /// 批量删除
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        protected void btnDelete_Click(object sender, EventArgs e)
        {
            //判断权限
            AuthUserOperationPermission( Permission.Delete );
            string Checkbox_Value = GameRequest.GetFormString("cid");
            string strQuery = "WHERE UserID in (" + Checkbox_Value + ")";
            try
            {
                aidePlatformManagerFacade.DeleteUser( Checkbox_Value );
                ShowInfo("删除成功");
            }
            catch
            {
                ShowError("删除失败");
            }
            GameUserDataBind();
        } /// <summary>
        /// 批量冻结玩家
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        protected void btnDongjie_Click( object sender, EventArgs e )
        {
            //判断权限
            AuthUserOperationPermission( Permission.Edit );
            string Checkbox_Value = GameRequest.GetFormString( "cid" );
            try
            {
                aidePlatformManagerFacade.ModifyUserNullity( Checkbox_Value, true );
                ShowInfo( "冻结成功" );
            }
            catch
            {
                ShowError( "冻结失败" );
            }
            GameUserDataBind( );
        }
        /// <summary>
        /// 批量解冻玩家
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        protected void btnJiedong_Click( object sender, EventArgs e )
        {
            //判断权限
            AuthUserOperationPermission( Permission.Edit );
            string Checkbox_Value = GameRequest.GetFormString( "cid" );          
            try
            {
                aidePlatformManagerFacade.ModifyUserNullity( Checkbox_Value, false );
                ShowInfo( "解冻成功" );
            }
            catch
            {
                ShowError( "解冻失败" );
            }
            GameUserDataBind( );
        }

        #endregion

        #region 数据绑定

        //绑定数据
        private void GameUserDataBind()
        {
            PagerSet pagerSet = aidePlatformManagerFacade.GetUserList(anpNews.CurrentPageIndex, anpNews.PageSize, SearchItems, Orderby);
            if (pagerSet.PageSet.Tables[0].Rows.Count > 0)
            {
                litNoData.Visible = false;
            }
            else
            {
                litNoData.Visible = true;
            }

            rptUser.DataSource = pagerSet.PageSet;
            rptUser.DataBind();
            anpNews.RecordCount = pagerSet.RecordCount;
        }

        /// <summary>
        /// 查询条件
        /// </summary>
        public string SearchItems
        {
            get
            {
                if (ViewState["SearchItems"] == null)
                {
                    StringBuilder condition = new StringBuilder();
                    condition.Append(" WHERE 1=1 ");

                    ViewState["SearchItems"] = condition.ToString();
                }

                return (string)ViewState["SearchItems"];
            }

            set { ViewState["SearchItems"] = value; }
        }

        /// <summary>
        /// 排序条件
        /// </summary>
        public string Orderby
        {
            get
            {
                if (ViewState["Orderby"] == null)
                {
                    ViewState["Orderby"] = "ORDER BY UserID ASC";
                }

                return (string)ViewState["Orderby"];
            }

            set { ViewState["Orderby"] = value; }
        }

        #endregion                       
    }
}
