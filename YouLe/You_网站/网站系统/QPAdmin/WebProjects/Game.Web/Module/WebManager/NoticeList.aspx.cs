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
using System.Collections;

namespace Game.Web.Module.WebManager
{
    public partial class NoticeList : AdminPage
    {
        #region 窗口事件

        protected void Page_Load( object sender, EventArgs e )
        {
            if ( !IsPostBack )
            {
                NoticeDataBind( );
            }
        }

        protected void anpNews_PageChanged( object sender, EventArgs e )
        {
            NoticeDataBind( );
        }

        /// <summary>
        /// 批量删除
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        protected void btnDelete_Click( object sender, EventArgs e )
        {
            //判断权限
            AuthUserOperationPermission( Permission.Delete );
            string Checkbox_Value = GameRequest.GetFormString( "cid" );
            string strQuery = "WHERE NoticeID in (" + Checkbox_Value + ")";
            try
            {
                aideNativeWebFacade.DeleteNotice( strQuery );
                ShowInfo( "删除成功" );
            }
            catch
            {
                ShowError( "删除失败" );
            }
            NoticeDataBind( );
        }
        //冻结
        protected void btnDisable_Click( object sender, EventArgs e )
        {
            //判断权限
            AuthUserOperationPermission( Permission.Edit );
            string Checkbox_Value = GameRequest.GetFormString( "cid" );
            string strQuery = "WHERE NoticeID in (" + Checkbox_Value + ")";
            try
            {
                aideNativeWebFacade.SetNoticeDisbale( strQuery );
                ShowInfo( "冻结成功" );
            }
            catch
            {
                ShowError( "冻结失败" );
            }
            NoticeDataBind( );
        }
        //解冻
        protected void btnEnable_Click( object sender, EventArgs e )
        {
            //判断权限
            AuthUserOperationPermission( Permission.Edit );
            string Checkbox_Value = GameRequest.GetFormString( "cid" );
            string strQuery = "WHERE NoticeID in (" + Checkbox_Value + ")";
            try
            {
                aideNativeWebFacade.SetNoticeEnbale( strQuery );
                ShowInfo( "解冻成功" );
            }
            catch
            {
                ShowError( "解冻失败" );
            }
            NoticeDataBind( );
        }
        #endregion

        #region 数据绑定

        //绑定数据
        private void NoticeDataBind( )
        {
            PagerSet pagerSet = aideNativeWebFacade.GetNoticeList( anpNews.CurrentPageIndex, anpNews.PageSize, SearchItems, Orderby );
            if ( pagerSet.PageSet.Tables[0].Rows.Count > 0 )
            {
                litNoData.Visible = false;
            }
            else
            {
                litNoData.Visible = true;
            }

            rptNotice.DataSource = pagerSet.PageSet;
            rptNotice.DataBind( );
            anpNews.RecordCount = pagerSet.RecordCount;
        }

        /// <summary>
        /// 查询条件
        /// </summary>
        public string SearchItems
        {
            get
            {
                if ( ViewState["SearchItems"] == null )
                {
                    StringBuilder condition = new StringBuilder( );
                    condition.Append( " WHERE 1=1 " );

                    ViewState["SearchItems"] = condition.ToString( );
                }

                return ( string ) ViewState["SearchItems"];
            }

            set
            {
                ViewState["SearchItems"] = value;
            }
        }

        /// <summary>
        /// 排序条件
        /// </summary>
        public string Orderby
        {
            get
            {
                if ( ViewState["Orderby"] == null )
                {
                    ViewState["Orderby"] = "ORDER BY NoticeID DESC";
                }

                return ( string ) ViewState["Orderby"];
            }

            set
            {
                ViewState["Orderby"] = value;
            }
        }

        //公告范围
        protected string GetNoticeLocation( string locationList )
        {
            StringBuilder sb = new StringBuilder( );
            IList<EnumDescription> arrNoticeLocation = NoticeLocationHelper.GetNoticeLocationList( typeof( NoticeLocation ) );
            string[ ] arrList = locationList.Split( new char[ ] { ',' }, StringSplitOptions.RemoveEmptyEntries );
            ArrayList list = new ArrayList( arrList );
            foreach ( EnumDescription v in arrNoticeLocation )
            {
                if ( list.Contains( v.EnumValue.ToString() ) )
                    sb.AppendFormat( "{0},", NoticeLocationHelper.GetNoticeLocationDes( ( NoticeLocation ) v.EnumValue ) );
            }

            return sb.ToString( ).TrimEnd( new char[ ] { ',' } );
        }

        #endregion

    }
}
