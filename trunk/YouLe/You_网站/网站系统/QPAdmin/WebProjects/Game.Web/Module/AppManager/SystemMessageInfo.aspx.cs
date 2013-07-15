using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;
using System.Data;
using System.Text;

using Game.Web.UI;
using Game.Utils;
using Game.Entity.Platform;
using Game.Kernel;

namespace Game.Web.Module.AppManager
{
    public partial class SystemMessageInfo : AdminPage
    {
        #region Fields

        string cmd = GameRequest.GetQueryString("cmd");
        int id = GameRequest.GetQueryInt("id", 0);
        #endregion

        #region 窗口事件

        protected void Page_Load(object sender, EventArgs e)
        {
            if (!Page.IsPostBack)
            {                
                SystemMessageDataBind();
                KindsDataBind();
            }
        }

        protected void btnSave_Click(object sender, EventArgs e)
        {
            ProcessData();
        }
        #endregion

        #region 数据加载

        //游戏绑定
        private void KindsDataBind()
        {
            tvKinds.Nodes.Clear();

            TreeNode rootNode = new TreeNode();
            rootNode.Text = "游戏列表";
            rootNode.Value = "-1";
            rootNode.SelectAction = TreeNodeSelectAction.None;
            rootNode.Expand();
            rootNode.ShowCheckBox = true;
            tvKinds.Nodes.Add(rootNode);

            if (Servers != "0")
            {
                string[] servers = Servers.Split(',');

                DataSet ds = aidePlatformFacade.GetGameKindItemList(1, Int32.MaxValue, "WHERE Nullity=0", "ORDER BY KindID ASC").PageSet;
                if (ds.Tables[0].Rows.Count > 0)
                {
                    foreach (DataRow dr in ds.Tables[0].Rows)
                    {
                        TreeNode nodeGame = new TreeNode();
                        nodeGame.Text = dr["KindName"].ToString();
                        nodeGame.Value = "";
                        nodeGame.ShowCheckBox = true;
                        nodeGame.SelectAction = TreeNodeSelectAction.None;
                        rootNode.ChildNodes.Add(nodeGame);

                        int GameID = Convert.ToInt32(dr["GameID"]);
                        DataSet dsServer = aidePlatformFacade.GetGameRoomInfoList( 1 , Int32.MaxValue , string.Format( "WHERE GameID={0} AND Nullity=0" , GameID ) , "ORDER BY ServerID ASC" ).PageSet;
                        if (dsServer.Tables[0].Rows.Count == 0)
                            continue;

                        int j = 0;
                        foreach (DataRow drServer in dsServer.Tables[0].Rows)
                        {
                            TreeNode nodeServer = new TreeNode();
                            nodeServer.Text = drServer["ServerName"].ToString();
                            nodeServer.Value = drServer["ServerID"].ToString().Trim();
                            nodeServer.ShowCheckBox = true;
                            nodeServer.SelectAction = TreeNodeSelectAction.None;

                            for (int i = 0; i < servers.Length; i++)
                            {
                                if (servers[i].Trim() == "") continue;
                                if (servers[i].Trim() == drServer["ServerID"].ToString().Trim())
                                {
                                    nodeServer.Checked = true;
                                    j++;
                                    break;
                                }
                            }
                            nodeGame.ChildNodes.Add(nodeServer);
                        }
                        if (j == dsServer.Tables[0].Rows.Count && j != 0) nodeGame.Checked = true;
                    }
                }
            }
            else
            {
                BindKindAndServer(rootNode);
                tvKinds.Nodes[0].Checked = true;
            }
        }

        /// <summary>
        /// 绑定游戏和房间数据
        /// </summary>
        private void BindKindAndServer(TreeNode rootNode)
        {
            DataSet ds = aidePlatformFacade.GetGameKindItemList(1, Int32.MaxValue, "WHERE Nullity=0", "ORDER BY KindID ASC").PageSet;
            if (ds.Tables[0].Rows.Count > 0)
            {
                foreach (DataRow dr in ds.Tables[0].Rows)
                {
                    TreeNode nodeGame = new TreeNode();
                    nodeGame.Text = dr["KindName"].ToString();
                    nodeGame.Value = "";
                    nodeGame.ShowCheckBox = true;
                    nodeGame.SelectAction = TreeNodeSelectAction.None;
                    nodeGame.Checked = true;
                    rootNode.ChildNodes.Add(nodeGame);

                    int kindID = Convert.ToInt32(dr["KindID"]);
                    DataSet dsServer = aidePlatformFacade.GetGameRoomInfoList(1, Int32.MaxValue, string.Format("WHERE KindID={0} AND Nullity=0", kindID), "ORDER BY ServerID ASC").PageSet;
                    if (dsServer.Tables[0].Rows.Count == 0)
                        continue;

                    foreach (DataRow drServer in dsServer.Tables[0].Rows)
                    {
                        TreeNode nodeServer = new TreeNode();
                        nodeServer.Text = drServer["ServerName"].ToString();
                        nodeServer.Value = drServer["ServerID"].ToString().Trim();
                        nodeServer.ShowCheckBox = true;
                        nodeServer.SelectAction = TreeNodeSelectAction.None;
                        nodeServer.Checked = true;

                        nodeGame.ChildNodes.Add(nodeServer);
                    }
                }
            }

        }

        private void SystemMessageDataBind()
        {
            if (cmd == "add")
            {
                litInfo.Text = "新增";
            }
            else
            {
                litInfo.Text = "更新";
            }

            if (id <= 0)
            {
                return;
            }

            //获取站点信息
            SystemMessage systemMessage = aidePlatformFacade.GetSystemMessageInfo(id);
            if (systemMessage == null)
            {
                ShowError("系统消息不存在");
                Redirect("SystemMessageInfo.aspx");
                return;
            }

            CtrlHelper.SetText(txtMessageString, systemMessage.MessageString.Trim());
            ddlMessageType.SelectedValue = systemMessage.MessageType.ToString().Trim();
            rbtnNullity.SelectedValue = systemMessage.Nullity.ToString().Trim();
            CtrlHelper.SetText(txtStartTime, systemMessage.StartTime.ToString().Trim());
            CtrlHelper.SetText(txtConcludeTime, systemMessage.ConcludeTime.ToString().Trim());
            CtrlHelper.SetText(txtTimeRate, systemMessage.TimeRate.ToString().Trim());
            CtrlHelper.SetText(txtCollectNote, systemMessage.CollectNote.Trim());
            CtrlHelper.SetText(lblCreateMasterID, GetMasterName(systemMessage.CreateMasterID));
            CtrlHelper.SetText(lblCreateDate, systemMessage.CreateDate.ToString());
            CtrlHelper.SetText(lblUpdateMasterID, GetMasterName(systemMessage.UpdateMasterID));
            CtrlHelper.SetText(lblUpdateDate, systemMessage.UpdateDate.ToString());
            CtrlHelper.SetText(lblUpdateCount, systemMessage.UpdateCount.ToString());

            Servers = systemMessage.ServerRange;
        }
        #endregion

        #region 处理方法

        private void ProcessData()
        {
            SystemMessage systemMessage = new SystemMessage();
            systemMessage.MessageString = CtrlHelper.GetText(txtMessageString);
            systemMessage.MessageType = Convert.ToInt32(ddlMessageType.SelectedValue.Trim());
            systemMessage.StartTime = Convert.ToDateTime(CtrlHelper.GetText(txtStartTime));
            systemMessage.ConcludeTime = Convert.ToDateTime(CtrlHelper.GetText(txtConcludeTime));
            systemMessage.TimeRate = CtrlHelper.GetInt(txtTimeRate, 0);
            systemMessage.Nullity = Convert.ToByte(rbtnNullity.SelectedValue.Trim());
            systemMessage.CollectNote = CtrlHelper.GetText(txtCollectNote);

            #region 获取房间节点值

            StringBuilder sb = new StringBuilder();
            if (!tvKinds.Nodes[0].Checked)
            {
                foreach (TreeNode node in tvKinds.CheckedNodes)
                {
                    if (node.Value != "")
                    {
                        sb.Append(node.Value.ToString() + ",");
                    }
                }
            }
            else
            {
                sb.Length = 0;
                sb.Append("0");
            }

            if (sb.ToString() == "" || sb.ToString() == null)
            {
                ShowError("请选择要控制的房间！");
                return;
            }
            systemMessage.ServerRange = sb.ToString();
            #endregion

            Message msg = new Message();
            if (cmd == "add")
            {
                systemMessage.CreateMasterID = userExt.UserID;
                systemMessage.CreateDate = DateTime.Now;
                msg = aidePlatformFacade.InsertSystemMessage(systemMessage);
            }
            else
            {
                systemMessage.ID = id;
                systemMessage.UpdateMasterID = userExt.UserID;
                systemMessage.UpdateDate = DateTime.Now;
                systemMessage.UpdateCount = CtrlHelper.GetInt(lblUpdateCount, 0) + 1;
                msg = aidePlatformFacade.UpdateSystemMessage(systemMessage);
            }

            if (msg.Success)
            {
                if (cmd == "add")
                {
                    ShowInfo("系统消息增加成功", "SystemMessageList.aspx", 1200);
                }
                else
                {
                    ShowInfo("系统消息修改成功", "SystemMessageList.aspx", 1200);
                }
            }
            else
            {
                ShowError(msg.Content);
            }
        }
        #endregion      
  
        #region 属性

        /// <summary>
        /// 房间范围记录
        /// </summary>
        public string Servers
        {
            get
            {
                if (ViewState["Server"] == null)
                    ViewState["Server"] = "";
                return ViewState["Server"].ToString();
            }
            set
            {
                ViewState["Server"] = value;
            }
        }
        #endregion
    }
}
