using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;
using Game.Utils;
using Game.Web.UI;
using Game.Entity.Accounts;
using Game.Kernel;
using Game.Entity.Record;
using System.Text;
using Game.Entity.Treasure;
using Game.Entity.Platform;
using Game.Entity.Enum;


namespace Game.Web.Module.AccountManager
{
    public partial class GrantTreasure : AdminPage
    {
        #region Fields

        /// <summary>
        /// 页面标题
        /// </summary>
        public string StrTitle
        {
            get
            {
                return "玩家-赠送金币";
            }
        }
        #endregion

        #region 窗口事件
        protected void Page_Load(object sender, EventArgs e)
        {
            //判断权限
            AuthUserOperationPermission( Permission.GrantTreasure );
            if ( Header != null )
                Title = StrTitle;           
        }
        protected void btnSave_Click(object sender, EventArgs e)
        {
            string strReason = TextFilter.FilterAll(CtrlHelper.GetText(txtReason));
            int intAddGold = CtrlHelper.GetInt(txtAddGold, 0);
            if ( intAddGold == 0 )
            {
                MessageBox( "赠送金币数不能为零！" );
                return;
            }

            if ( string.IsNullOrEmpty(strReason) )
            {
                MessageBox("赠送原因不能为空");
                return;
            }
            Message msg = aideTreasureFacade.GrantTreasure( StrParamsList, intAddGold, userExt.UserID, strReason, GameRequest.GetUserIP());
            if ( msg.Success )
            {
                MessageBox("确认成功");
            }
            else
            {
                string strMessage = "";
                int intMsgID = msg.MessageID;
                switch ( intMsgID )
                {                   
                    case -3:
                        strMessage = "未选中赠送对象！";
                        break;
                    case -2:
                        strMessage = "赠送金额不能为零！";
                        break;
                    case -1:
                        strMessage = "抱歉，未知服务器错误！";
                        break;
                    default:
                        strMessage = "抱歉，未知服务器错误！";
                        break;
                }

                MessageBox(strMessage);
            }
            /* RecordGrantTreasure grantTreasure = new RecordGrantTreasure( );
             GameScoreInfo gameScoreInfo = new GameScoreInfo( );
             grantTreasure.ClientIP = GameRequest.GetUserIP( );
             grantTreasure.MasterID = userExt.UserID;
             grantTreasure.AddGold = intAddGold;
             grantTreasure.Reason = strReason;

             string[ ] arrUserIDList = StrParamsList.Split( new char[ ] { ',' } );
             foreach ( string strid in arrUserIDList )
             {
                 if ( Utils.Validate.IsPositiveInt( strid ) )
                 {
                     gameScoreInfo = aideTreasureFacade.GetGameScoreInfoByUserID( int.Parse( strid ) );
                     if ( gameScoreInfo == null )
                         continue;
                     grantTreasure.UserID = int.Parse( strid );
                     grantTreasure.CurGold = Convert.ToInt64( aideTreasureFacade.GetGameScoreByUserID( int.Parse( strid ) ) );

                     gameScoreInfo.InsureScore = grantTreasure.CurGold + intAddGold;

                     aideTreasureFacade.UpdateInsureScore( gameScoreInfo );          //更新银行金币
                     aideRecordFacade.InsertRecordGrantTreasure( grantTreasure );    //插入赠送金币日志
                 }
             }
             MessageBox( "确认成功" );*/
        }
        #endregion
        
    }
}
