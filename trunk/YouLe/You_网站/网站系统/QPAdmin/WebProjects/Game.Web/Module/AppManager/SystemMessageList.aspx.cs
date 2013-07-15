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
using Game.Entity.Platform;

namespace Game.Web.Module.AppManager
{
    public partial class SystemMessageList : AdminPage
    {
        #region 窗口事件

        protected void Page_Load(object sender, EventArgs e)
        {
            if (!IsPostBack)
            {
                SystemMessageDataBind();
            }
        }

        protected void anpNews_PageChanged(object sender, EventArgs e)
        {
            SystemMessageDataBind();
        }

        /// <summary>
        /// 批量删除
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        protected void btnDelete_Click(object sender, EventArgs e)
        {
            string Checkbox_Value = GameRequest.GetFormString("cid");
            string strQuery = "WHERE ID in (" + Checkbox_Value + ")";
            try
            {
                aidePlatformFacade.DeleteSystemMessage( strQuery );
                ShowInfo("删除成功");
            }
            catch
            {
                ShowError("删除失败");
            }
            SystemMessageDataBind();
        }

        /// <summary>
        /// 批量冻结
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        protected void btnNoEnable_Click( object sender , EventArgs e )
        {
            string Checkbox_Value = GameRequest.GetFormString( "cid" );
            string strQuery = "Update " + SystemMessage.Tablename + " Set Nullity = 1 WHERE ID in (" + Checkbox_Value + ") and Nullity=0";
            int result = aidePlatformFacade.ExecuteSql( strQuery );
            if ( result > 0 )
            {
                ShowInfo( "冻结成功" );
            }
            else
            {
                ShowError( "冻结失败，没有需要冻结的消息！" );
            }
           
            SystemMessageDataBind( );
        }

        /// <summary>
        /// 批量解冻
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        protected void btnEnable_Click( object sender , EventArgs e )
        {
            string Checkbox_Value = GameRequest.GetFormString( "cid" );
            string strQuery = "Update " + SystemMessage.Tablename + " Set Nullity = 0 WHERE ID in (" + Checkbox_Value + ") and Nullity = 1";
            int result = aidePlatformFacade.ExecuteSql( strQuery );
            if ( result > 0 )
            {
                ShowInfo( "解冻成功" );
            }
            else
            {
                ShowError( "解冻失败，没有需要解冻的消息！" );
            }

            SystemMessageDataBind( );
        }



        #endregion

        #region 数据绑定

        //绑定数据
        private void SystemMessageDataBind()
        {
            PagerSet pagerSet = aidePlatformFacade.GetSystemMessageList(anpNews.CurrentPageIndex, anpNews.PageSize, SearchItems, Orderby);
            if (pagerSet.PageSet.Tables[0].Rows.Count > 0)
            {
                litNoData.Visible = false;
            }
            else
            {
                litNoData.Visible = true;
            }

            rptSystemMessage.DataSource = pagerSet.PageSet;
            rptSystemMessage.DataBind();
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
                    ViewState["Orderby"] = "ORDER BY StartTime DESC";
                }

                return (string)ViewState["Orderby"];
            }

            set { ViewState["Orderby"] = value; }
        }

        /// <summary>
        /// 获取消息类型名称
        /// </summary>
        /// <param name="messageType"></param>
        /// <returns></returns>
        protected string GetMessageTypeName(int messageType)
        {
            string rValue = "";
            switch (messageType)
            {
                case 1:
                    rValue = "游戏";
                    break;
                case 2:
                    rValue = "房间";
                    break;
                case 3:
                    rValue = "全部";
                    break;
                default:
                    break;
            }
            return rValue;
        }

        #endregion                       
    }
}
