using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;

using Game.Utils;
using Game.Web.UI;
using Game.Kernel;
using Game.Entity.NativeWeb;
using Game.Entity.Enum;
using System.Collections;
using System.Text;

namespace Game.Web.Module.WebManager
{
    public partial class NoticeInfo : AdminPage
    {

        #region 窗口事件

        protected void Page_Load( object sender, EventArgs e )
        {
            if ( !Page.IsPostBack )
            {
                BindLocation( );
                GameNoticeDataBind( );
            }
        }

        protected void btnSave_Click( object sender, EventArgs e )
        {
            ProcessData( );
        }
        #endregion

        #region 数据加载
        private void BindLocation( )
        {
            IList<EnumDescription> arrMemberOrder = NoticeLocationHelper.GetNoticeLocationList( typeof( NoticeLocation ) );
            ckbLocation.DataSource = arrMemberOrder;
            ckbLocation.DataValueField = "EnumValue";
            ckbLocation.DataTextField = "Description";
            ckbLocation.DataBind( );
        }
        private void GameNoticeDataBind( )
        {
            if ( StrCmd == "add" )
            {
                litInfo.Text = "新增";
            }
            else
            {
                litInfo.Text = "更新";
            }

            if ( IntParam <= 0 )
            {
                return;
            }

            //获取公告信息
            Notice notice = aideNativeWebFacade.GetNoticeInfo( IntParam );
            if ( notice == null )
            {
                ShowError( "公告信息不存在" );
                Redirect( "NoticeList.aspx" );
                return;
            }

            CtrlHelper.SetText( txtSubject, notice.Subject );
            CtrlHelper.SetText( txtLinkUrl, notice.LinkUrl == "" ? "http://" : notice.LinkUrl );
            chkIsLinks.Checked = notice.IsLink == 1;
            CtrlHelper.SetText( txtBody, notice.Body );
            CtrlHelper.SetText( txtWidth, notice.Width.ToString( ) );
            CtrlHelper.SetText( txtHeight, notice.Height.ToString( ) );
            CtrlHelper.SetText( txtStartDate, notice.StartDate.ToString( ) );
            CtrlHelper.SetText( txtOverDate, notice.OverDate.ToString( ) );
            rbtnNullity.SelectedValue = notice.Nullity.ToString( );
            string[ ] locationList = notice.Location.Split( new char[ ] { ',' }, StringSplitOptions.RemoveEmptyEntries );
            ;
            if ( ckbLocation.Items.Count > 0 )
            {
                ArrayList list = new ArrayList( locationList );
                foreach ( ListItem item in ckbLocation.Items )
                {
                    item.Selected = list.Contains( item.Value );
                }
            }
        }
        #endregion

        #region 处理方法

        private void ProcessData( )
        {
            Notice notice = new Notice( );
            notice.Subject = CtrlHelper.GetText( txtSubject );
            notice.IsLink = Convert.ToByte( chkIsLinks.Checked );
            notice.LinkUrl = CtrlHelper.GetText( txtLinkUrl );
            notice.Body = CtrlHelper.GetText( txtBody );
            notice.Width = CtrlHelper.GetInt( txtWidth, 0 );
            notice.Height = CtrlHelper.GetInt( txtHeight, 0 );
            notice.StartDate = Convert.ToDateTime( CtrlHelper.GetText( txtStartDate ) );
            notice.OverDate = Convert.ToDateTime( CtrlHelper.GetText( txtOverDate ) );
            notice.Nullity = Convert.ToByte( rbtnNullity.SelectedValue.Trim( ) );

            //使用范围
            StringBuilder sb = new StringBuilder( );
            if ( ckbLocation.Items.Count > 0 )
            {
                foreach ( ListItem item in ckbLocation.Items )
                {
                    if ( item.Selected )
                        sb.AppendFormat( "{0},", item.Value );// |= int.Parse( item.Value );
                }
            }

            notice.Location = sb.ToString( ).TrimEnd( new char[ ] { ',' } );

            Message msg = new Message( );
            if ( StrCmd == "add" )
            {
                //判断权限
                AuthUserOperationPermission( Permission.Add );
                msg = aideNativeWebFacade.InsertNotice( notice );
            }
            else
            {
                //判断权限
                AuthUserOperationPermission( Permission.Edit );
                notice.NoticeID = IntParam;
                msg = aideNativeWebFacade.UpdateNotice( notice );
            }

            if ( msg.Success )
            {
                if ( StrCmd == "add" )
                {
                    ShowInfo( "公告信息增加成功", "NoticeList.aspx", 1200 );
                }
                else
                {
                    ShowInfo( "公告信息修改成功", "NoticeList.aspx", 1200 );
                }
            }
            else
            {
                ShowError( msg.Content );
            }
        }
        #endregion
    }
}
