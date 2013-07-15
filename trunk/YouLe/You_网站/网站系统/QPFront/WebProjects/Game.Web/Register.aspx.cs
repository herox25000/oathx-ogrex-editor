using System;
using System.Collections;
using System.Configuration;
using System.Data;
using System.Linq;
using System.Web;
using System.Web.Security;
using System.Web.UI;
using System.Web.UI.HtmlControls;
using System.Web.UI.WebControls;
using System.Web.UI.WebControls.WebParts;
using System.Xml.Linq;

using Game.Entity.NativeWeb;
using Game.Entity.Platform;
using Game.Entity.Accounts;
using Game.Facade;
using Game.Kernel;
using Game.Utils;

namespace Game.Web
{
    public partial class Register : UCPageBase
    {
        private AccountsFacade accountsFacade = new AccountsFacade();

        /// <summary>
        /// 页面加载
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        protected void Page_Load(object sender, EventArgs e)
        {
            Themes.Standard.Common_Header sHeader = (Themes.Standard.Common_Header)this.FindControl("sHeader");
            sHeader.title = "会员中心";
        }

        /// <summary>
        /// 增加页面标题
        /// </summary>
        protected override void AddHeaderTitle()
        {
            AddMetaTitle("用户注册 - " + ApplicationSettings.Get("title"));
            AddMetaKeywords(ApplicationSettings.Get("keywords"));
            AddMetaDescription(ApplicationSettings.Get("description"));
        }

        /// <summary>
        /// 注册按钮事件
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        protected void btnRegister_Click(object sender, EventArgs e)
        {
            if (TextUtility.EmptyTrimOrNull(txtAccounts.Text.Trim()) || TextUtility.EmptyTrimOrNull(txtLogonPass.Text.Trim()))
            {
                Show("抱歉！您输入的用户名或密码错误了。");
                this.txtAccounts.Focus();
                return;
            }

            //验证码错误
            if (!txtCode.Text.Trim().Equals(Fetch.GetVerifyCode(), StringComparison.InvariantCultureIgnoreCase))
            {
                Show("抱歉！您输入的验证码错误了。");
                this.txtAccounts.Focus();
                return;
            }

            Message umsg = accountsFacade.IsAccountsExist(CtrlHelper.GetText(txtAccounts));
            if (!umsg.Success)
            {
                Show(umsg.Content);
                this.txtAccounts.Focus();
                return;
            }

            UserInfo user = new UserInfo();
            user.Accounts = CtrlHelper.GetText(txtAccounts);
            user.Compellation = CtrlHelper.GetText(txtCompellation);
            user.FaceID = Convert.ToInt16(hfFaceID.Value.Trim());
            user.Gender = Convert.ToByte(ddlGender.SelectedValue);
            user.InsurePass = TextEncrypt.EncryptPassword(CtrlHelper.GetText(txtInsurePass1));
            user.LastLogonDate = DateTime.Now;
            user.LastLogonIP = GameRequest.GetUserIP();
            user.LogonPass = TextEncrypt.EncryptPassword(CtrlHelper.GetText(txtLogonPass));
            user.NickName = CtrlHelper.GetText(txtNickname);
            user.PassPortID = CtrlHelper.GetText(txtPassPortID);
            user.RegisterDate = DateTime.Now;
            user.RegisterIP = GameRequest.GetUserIP();

            Message msg = accountsFacade.Register(user, CtrlHelper.GetText(txtSpreader));
            if (msg.Success)
            {
                UserInfo ui = msg.EntityList[0] as UserInfo;
                ui.LogonPass = TextEncrypt.EncryptPassword(CtrlHelper.GetText(txtLogonPass));
                Fetch.SetUserCookie( ui.ToUserTicketInfo( ) );

                ShowAndRedirect("注册成功！","/Member/MIndex.aspx");
            }
            else
            {
                Show(msg.Content);
                this.txtAccounts.Focus();
            }
        }
    }
}
