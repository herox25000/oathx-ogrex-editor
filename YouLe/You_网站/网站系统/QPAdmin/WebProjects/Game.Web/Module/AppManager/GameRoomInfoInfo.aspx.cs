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
using Game.Entity.Enum;

namespace Game.Web.Module.AppManager
{
    public partial class GameRoomInfoInfo : AdminPage
    {
        #region 窗口事件

        protected void Page_Load(object sender, EventArgs e)
        {
            if (!Page.IsPostBack)
            {
                BindNode( );
                BindKindList();
                BindGameList();
                BindDataBaseAddr();
                BindSupporType();
                GameRoomInfoDataBind();
            }
        }

        protected void btnSave_Click(object sender, EventArgs e)
        {
            ProcessData();
        }
        #endregion

        #region 数据加载
        
        //绑定节点
        private void BindNode( )
        {
            PagerSet pagerSet = aidePlatformFacade.GetGameNodeItemList( 1, Int32.MaxValue, "", "ORDER BY NodeID ASC" );
            if ( pagerSet.PageSet.Tables[0].Rows.Count > 0 )
            {
                ddlNode.DataSource = pagerSet.PageSet;
                ddlNode.DataTextField = "NodeName";
                ddlNode.DataValueField = "NodeID";
                ddlNode.DataBind( );
            }
            ddlNode.Items.Insert( 0, new ListItem( "无挂接", "0" ) );
        }

        //绑定游戏
        private void BindKindList()
        {
            PagerSet pagerSet = aidePlatformFacade.GetGameKindItemList(1, Int32.MaxValue, "", "ORDER BY KindID ASC");
            if (pagerSet.PageSet.Tables[0].Rows.Count > 0)
            {
                ddlKindID.DataSource = pagerSet.PageSet;
                ddlKindID.DataTextField = "KindName";
                ddlKindID.DataValueField = "KindID";
                ddlKindID.DataBind();
            }
        }

        //绑定模块
        private void BindGameList()
        {
            PagerSet pagerSet = aidePlatformFacade.GetGameGameItemList(1, Int32.MaxValue, "", "ORDER BY GameID ASC");
            if (pagerSet.PageSet.Tables[0].Rows.Count > 0)
            {
                ddlGameID.DataSource = pagerSet.PageSet;
                ddlGameID.DataTextField = "GameName";
                ddlGameID.DataValueField = "GameID";
                ddlGameID.DataBind();
            }
        }

        //绑定数据库
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

        //绑定支持类型
        private void BindSupporType()
        {
            IList<EnumDescription> list = SupporTypeHelper.GetSupporTypeList(typeof(SupporTypeStatus));
            ddlServerType.DataSource = list;
            ddlServerType.DataTextField = "Description";
            ddlServerType.DataValueField = "EnumValue";
            ddlServerType.DataBind();
        }

        private void GameRoomInfoDataBind()
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

            //获取游戏信息
            GameRoomInfo gameRoomInfo = aidePlatformFacade.GetGameRoomInfoInfo(IntParam);
            if (gameRoomInfo == null)
            {
                ShowError("房间信息不存在");
                Redirect("GameRoomInfoList.aspx");
                return;
            }

            CtrlHelper.SetText(txtServerName, gameRoomInfo.ServerName.Trim());
            ddlKindID.SelectedValue = gameRoomInfo.KindID.ToString().Trim();
            ddlNode.SelectedValue = gameRoomInfo.NodeID.ToString( ).Trim( );
            CtrlHelper.SetText(txtSortID, gameRoomInfo.SortID.ToString().Trim());
            ddlGameID.SelectedValue = gameRoomInfo.GameID.ToString().Trim();
            CtrlHelper.SetText(txtTableCount, gameRoomInfo.TableCount.ToString().Trim());
            ddlServerType.SelectedValue = gameRoomInfo.ServerType.ToString().Trim();
            CtrlHelper.SetText(txtServerPort, gameRoomInfo.ServerPort.ToString().Trim());
            ddlDataBaseAddr.SelectedValue = gameRoomInfo.DataBaseAddr.Trim();
            CtrlHelper.SetText(txtDataBaseName, gameRoomInfo.DataBaseName.Trim());
            CtrlHelper.SetText(txtCellScore, gameRoomInfo.CellScore.ToString().Trim());
            CtrlHelper.SetText(txtRevenueRatio, gameRoomInfo.RevenueRatio.ToString().Trim());
            CtrlHelper.SetText(txtRestrictScore, gameRoomInfo.RestrictScore.ToString().Trim());
            CtrlHelper.SetText(txtMinTableScore, gameRoomInfo.MinTableScore.ToString().Trim());
            CtrlHelper.SetText(txtMinEnterScore, gameRoomInfo.MinEnterScore.ToString().Trim());
            CtrlHelper.SetText(txtMaxEnterScore, gameRoomInfo.MaxEnterScore.ToString().Trim());
            CtrlHelper.SetText(txtMinEnterMember, gameRoomInfo.MinEnterMember.ToString().Trim());
            CtrlHelper.SetText(txtMaxEnterMember, gameRoomInfo.MaxEnterMember.ToString().Trim());
            CtrlHelper.SetText(txtMaxPlayer, gameRoomInfo.MaxPlayer.ToString().Trim());
            CtrlHelper.SetText(txtServerRule, gameRoomInfo.ServerRule.ToString().Trim());
            CtrlHelper.SetText(txtDistributeRule, gameRoomInfo.DistributeRule.ToString().Trim());
            CtrlHelper.SetText(txtMinDistributeUser, gameRoomInfo.MinDistributeUser.ToString().Trim());
            CtrlHelper.SetText(txtMaxDistributeUser, gameRoomInfo.MaxDistributeUser.ToString().Trim());
            CtrlHelper.SetText(txtDistributeTimeSpace, gameRoomInfo.DistributeTimeSpace.ToString().Trim());
            CtrlHelper.SetText(txtDistributeDrawCount, gameRoomInfo.DistributeDrawCount.ToString().Trim());
            CtrlHelper.SetText(txtDistributeStartDelay, gameRoomInfo.DistributeStartDelay.ToString().Trim());
            CtrlHelper.SetText(txtAttachUserRight, gameRoomInfo.AttachUserRight.ToString().Trim());
            CtrlHelper.SetText(txtServiceMachine, gameRoomInfo.ServiceMachine.Trim());
            CtrlHelper.SetText(txtCustomRule, gameRoomInfo.CustomRule.Trim());
            rbtnNullity.SelectedValue = gameRoomInfo.Nullity.ToString().Trim();
            CtrlHelper.SetText(txtServerNote, gameRoomInfo.ServerNote.Trim());
            CtrlHelper.SetText(lblCreateDateTime, gameRoomInfo.CreateDateTime.ToString());
            CtrlHelper.SetText(lblModifyDateTime, gameRoomInfo.ModifyDateTime.ToString());
        }
        #endregion

        #region 处理方法

        private void ProcessData()
        {
            string serverName = CtrlHelper.GetText( txtServerName );        //房间名称
            string sortID = CtrlHelper.GetText( txtSortID );                //排序
            string tableCount = CtrlHelper.GetText( txtTableCount );        //桌子数量
            string serverPort = CtrlHelper.GetText( txtServerPort );        //服务端口
            string cellScore = CtrlHelper.GetText( txtServerPort );         //单位积分 bigint
            string revenueRatio = CtrlHelper.GetText( txtRevenueRatio );    //税收比例 tinyint
            string restrictScore = CtrlHelper.GetText( txtRestrictScore );  //限制积分 bigint
            string minTableScore = CtrlHelper.GetText( txtMinTableScore );  //最低积分 bigint
            string minEnterScore = CtrlHelper.GetText( txtMinEnterScore );  //最小进入积分 bigint
            string maxEnterScore = CtrlHelper.GetText( txtMaxEnterScore );  //最大进入积分 bigint
            string minEnterMember = CtrlHelper.GetText( txtMinEnterMember );//最小进入等级
            string maxEnterMember = CtrlHelper.GetText( txtMaxEnterMember );//最大进入等级
            string maxPlayer = CtrlHelper.GetText( txtMaxPlayer );          //最大玩家数目
            string serverRule = CtrlHelper.GetText( txtServerRule );        //房间规则
            string distributeRule = CtrlHelper.GetText( txtDistributeRule );//分组规则
            string minDistributeUser = CtrlHelper.GetText( txtMinDistributeUser );      //最小人数
            string maxDistributeUser = CtrlHelper.GetText( txtMaxDistributeUser );      //最大人数
            string distributeTimeSpace = CtrlHelper.GetText( txtDistributeTimeSpace );  //分组间隔
            string distributeDrawCount = CtrlHelper.GetText( txtDistributeDrawCount );  //分组局数
            string distributeStartDelay = CtrlHelper.GetText( txtDistributeStartDelay );//开始延时
            string attachUserRight = CtrlHelper.GetText( txtAttachUserRight );          //附加属性

            #region 数据验证

            if ( string.IsNullOrEmpty( serverName ) )
            {
                ShowError( "房间名称必须填写" );
                return;
            }
            if ( !Utils.Validate.IsPositiveInt( sortID ) )
            {
                ShowError( "排序不规范，排序只能为0或正整数，且最大值不能超过2,147,483,647" );
                return;
            }
            if ( !Utils.Validate.IsPositiveInt( tableCount ) )
            {
                ShowError( "桌子数量不规范，桌子只能为0或正整数，且最大值不能超过2,147,483,647" );
                return;
            }
            if ( !Utils.Validate.IsPositiveInt( serverPort ) )
            {
                ShowError( "服务端口不规范，服务端口只能为0或正整数，且最大值不能超过2,147,483,647" );
                return;
            }
            if ( !Utils.Validate.IsPositiveInt64( cellScore ) )
            {
                ShowError( "单位积分不规范，单位积分只能为0或正整数" );
                return;
            }
            if ( !Utils.Validate.IsPositiveInt64( revenueRatio ) || Convert.ToInt32( revenueRatio ) > 255 )
            {
                ShowError( "税收比例不规范，单位积分只能为0或正整数，且最大值不能超过255" );
                return;
            }
            if ( !Utils.Validate.IsPositiveInt64( minTableScore ) )
            {
                ShowError( "最低积分不规范，最低积分只能为0或正整数" );
                return;
            }
            if ( !Utils.Validate.IsPositiveInt64( minEnterScore ) )
            {
                ShowError( "最小进入积分不规范，最小进入积分只能为0或正整数" );
                return;
            }
            if ( !Utils.Validate.IsPositiveInt64( maxEnterScore ) )
            {
                ShowError( "最大进入积分不规范，最大进入积分只能为0或正整数" );
                return;
            }
            if ( !Utils.Validate.IsPositiveInt( minEnterMember ) )
            {
                ShowError( "最小进入等级不规范，最小进入等级只能为0或正整数，且最大值不能超过2,147,483,647" );
                return;
            }
            if ( !Utils.Validate.IsPositiveInt( maxEnterMember ) )
            {
                ShowError( "最大进入等级不规范，最大进入等级只能为0或正整数，且最大值不能超过2,147,483,647" );
                return;
            }
            if ( !Utils.Validate.IsPositiveInt( maxPlayer ) )
            {
                ShowError( "最大玩家数目不规范，最大玩家数目只能为0或正整数，且最大值不能超过2,147,483,647" );
                return;
            }
            if ( !Utils.Validate.IsPositiveInt( serverRule ) )
            {
                ShowError( "房间规则不规范，房间规则只能为0或正整数，且最大值不能超过2,147,483,647" );
                return;
            }
            if ( !Utils.Validate.IsPositiveInt( distributeRule ) )
            {
                ShowError( "分组规则不规范，分组规则只能为0或正整数，且最大值不能超过2,147,483,647" );
                return;
            }
            if ( !Utils.Validate.IsPositiveInt( minDistributeUser ) )
            {
                ShowError( "最小人数不规范，最小人数只能为0或正整数，且最大值不能超过2,147,483,647" );
                return;
            }
            if ( !Utils.Validate.IsPositiveInt( maxDistributeUser ) )
            {
                ShowError( "最大人数不规范，最大人数只能为0或正整数，且最大值不能超过2,147,483,647" );
                return;
            }
            if ( !Utils.Validate.IsPositiveInt( distributeTimeSpace ) )
            {
                ShowError( "分组间隔不规范，分组间隔只能为0或正整数，且最大值不能超过2,147,483,647" );
                return;
            }
            if ( !Utils.Validate.IsPositiveInt( distributeDrawCount ) )
            {
                ShowError( "分组局数不规范，分组局数只能为0或正整数，且最大值不能超过2,147,483,647" );
                return;
            }
            if ( !Utils.Validate.IsPositiveInt( distributeStartDelay ) )
            {
                ShowError( "开始延时不规范，开始延时只能为0或正整数，且最大值不能超过2,147,483,647" );
                return;
            }
            if ( !Utils.Validate.IsPositiveInt( attachUserRight ) )
            {
                ShowError( "附加属性不规范，附加属性只能为0或正整数，且最大值不能超过2,147,483,647" );
                return;
            }
            #endregion

            GameRoomInfo gameRoomInfo = new GameRoomInfo();
            gameRoomInfo.ServerName = CtrlHelper.GetText(txtServerName);
            gameRoomInfo.KindID = Convert.ToInt32(ddlKindID.SelectedValue.Trim());
            gameRoomInfo.NodeID = Convert.ToInt32( ddlNode.SelectedValue.Trim( ) );
            gameRoomInfo.SortID = CtrlHelper.GetInt(txtSortID, 0);
            gameRoomInfo.GameID = Convert.ToInt32(ddlGameID.SelectedValue.Trim());
            gameRoomInfo.TableCount = CtrlHelper.GetInt(txtTableCount, 0);
            gameRoomInfo.ServerType = Convert.ToInt32(ddlServerType.SelectedValue.Trim());
            gameRoomInfo.ServerPort = CtrlHelper.GetInt(txtServerPort, 0);
            gameRoomInfo.DataBaseName = CtrlHelper.GetText(txtDataBaseName);
            gameRoomInfo.DataBaseAddr = ddlDataBaseAddr.SelectedValue.Trim();
            gameRoomInfo.CellScore = Convert.ToInt64(CtrlHelper.GetInt(txtCellScore, 0));
            gameRoomInfo.RevenueRatio = Convert.ToByte(CtrlHelper.GetInt(txtRevenueRatio, 0));
            gameRoomInfo.RestrictScore = Convert.ToInt64(CtrlHelper.GetInt(txtRestrictScore, 0));
            gameRoomInfo.MinTableScore = Convert.ToInt64(CtrlHelper.GetInt(txtMinTableScore, 0));
            gameRoomInfo.MinEnterScore = Convert.ToInt64(CtrlHelper.GetInt(txtMinEnterScore, 0));
            gameRoomInfo.MaxEnterScore = Convert.ToInt64(CtrlHelper.GetInt(txtMaxEnterScore, 0));
            gameRoomInfo.MinEnterMember = CtrlHelper.GetInt(txtMinEnterMember, 0);
            gameRoomInfo.MaxEnterMember = CtrlHelper.GetInt(txtMaxEnterMember, 0);
            gameRoomInfo.MaxPlayer = CtrlHelper.GetInt(txtMaxPlayer, 0);
            gameRoomInfo.ServerRule = CtrlHelper.GetInt(txtServerRule, 0);
            gameRoomInfo.DistributeRule = CtrlHelper.GetInt(txtDistributeRule, 0);
            gameRoomInfo.MinDistributeUser = CtrlHelper.GetInt(txtMinDistributeUser, 0);
            gameRoomInfo.MaxDistributeUser = CtrlHelper.GetInt(txtMaxDistributeUser, 0);
            gameRoomInfo.DistributeTimeSpace = CtrlHelper.GetInt(txtDistributeTimeSpace, 0);
            gameRoomInfo.DistributeDrawCount = CtrlHelper.GetInt(txtDistributeDrawCount, 0);
            gameRoomInfo.DistributeStartDelay = CtrlHelper.GetInt(txtDistributeStartDelay, 0);
            gameRoomInfo.AttachUserRight = CtrlHelper.GetInt(txtAttachUserRight, 0);
            gameRoomInfo.ServiceMachine = CtrlHelper.GetText(txtServiceMachine);
            gameRoomInfo.CustomRule = CtrlHelper.GetText(txtCustomRule);
            gameRoomInfo.Nullity = Convert.ToByte(rbtnNullity.SelectedValue.Trim());
            gameRoomInfo.ServerNote = CtrlHelper.GetText(txtServerNote);
            gameRoomInfo.ServiceScore = 0;
            Message msg = new Message();
            if (StrCmd == "add")
            {
                //判断权限
                AuthUserOperationPermission( Permission.Add );
                msg = aidePlatformFacade.InsertGameRoomInfo(gameRoomInfo);
            }
            else
            {
                //判断权限
                AuthUserOperationPermission( Permission.Edit );
                gameRoomInfo.ServerID = IntParam;
                gameRoomInfo.ModifyDateTime = DateTime.Now;
                msg = aidePlatformFacade.UpdateGameRoomInfo(gameRoomInfo);
            }

            if (msg.Success)
            {
                if (StrCmd == "add")
                {
                    ShowInfo("房间信息增加成功", "GameRoomInfoList.aspx", 1200);
                }
                else
                {
                    ShowInfo("房间信息修改成功", "GameRoomInfoList.aspx", 1200);
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
