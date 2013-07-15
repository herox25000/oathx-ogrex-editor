using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

using Game.Kernel;
using Game.IData;
using Game.Entity.Accounts;
using System.Data;
using System.Data.Common;

namespace Game.Data
{
    /// <summary>
    /// 帐号库数据层
    /// </summary>
    public class AccountsDataProvider : BaseDataProvider, IAccountsDataProvider
    {
        #region Fields

        private ITableProvider aideAccountsProvider;
        private ITableProvider aideIndividualDatumProvider;
        private ITableProvider aideAccountsProtectProvider;
        private ITableProvider aideConfineContentProvider;
        private ITableProvider aideConfineAddressProvider;
        private ITableProvider aideConfineMachineProvider;
        private ITableProvider aideSystemStatusInfoProvider;

        #endregion

        #region 构造方法

        /// <summary>
        /// 构造函数
        /// </summary>
        public AccountsDataProvider( string connString )
            : base( connString )
        {
            aideAccountsProvider = GetTableProvider( AccountsInfo.Tablename );
            aideIndividualDatumProvider = GetTableProvider( IndividualDatum.Tablename );
            aideAccountsProtectProvider = GetTableProvider( AccountsProtect.Tablename );
            aideConfineContentProvider = GetTableProvider( ConfineContent.Tablename );
            aideConfineAddressProvider = GetTableProvider( ConfineAddress.Tablename );
            aideConfineMachineProvider = GetTableProvider( ConfineMachine.Tablename );
            aideSystemStatusInfoProvider = GetTableProvider( SystemStatusInfo.Tablename );
        }
        #endregion

        #region 用户基本信息管理

        /// <summary>
        /// 分页获取玩家列表
        /// </summary>
        /// <param name="pageIndex">当前页码</param>
        /// <param name="pageSize">每页条数</param>
        /// <param name="condition">条件</param>
        /// <param name="orderby">排序</param>
        /// <returns></returns>
        public PagerSet GetAccountsList( int pageIndex, int pageSize, string condition, string orderby )
        {
            PagerParameters pagerPrams = new PagerParameters( AccountsInfo.Tablename, orderby, condition, pageIndex, pageSize );
            return GetPagerSet2( pagerPrams );
        }

        /// <summary>
        /// 获得用户名
        /// </summary>
        /// <param name="userID">用户UserID</param>
        /// <returns></returns>
        public string GetAccountByUserID( int userID )
        {
            AccountsInfo model = GetAccountInfoByUserID( userID );
            if ( model != null )
                return model.Accounts;
            else
                return "";
        }
       
        /// <summary>
        /// 获得用户经验值
        /// </summary>
        /// <param name="userID">用户UserID</param>
        /// <returns></returns>
        public int GetExperienceByUserID( int userID )
        {
            AccountsInfo model = GetAccountInfoByUserID( userID );
            if ( model != null )
                return model.Experience;
            else
                return 0;
        }

        /// <summary>
        /// 获取用户基本信息
        /// </summary>
        /// <param name="userID">用户UserID</param>
        /// <returns></returns>
        public AccountsInfo GetAccountInfoByUserID( int userID )
        {
            string sqlQuery = string.Format( "(NOLOCK) WHERE UserID= N'{0}'", userID );
            AccountsInfo model = aideAccountsProvider.GetObject<AccountsInfo>( sqlQuery );
            if ( model != null )
                return model;
            else
                return new AccountsInfo( );
        }
        /// <summary>
        /// 获取用户基本信息
        /// </summary>
        /// <param name="account">用户帐号</param>
        /// <returns></returns>
        public AccountsInfo GetAccountInfoByAccount( string account )
        {
            string sqlQuery = string.Format( "(NOLOCK) WHERE Accounts= N'{0}'", account );
            AccountsInfo model = aideAccountsProvider.GetObject<AccountsInfo>( sqlQuery );
            if ( model != null )
                return model;
            else
                return new AccountsInfo( );
        }
        /// <summary>
        /// 冻结玩家
        /// </summary>
        /// <param name="sqlQuery">条件</param>
        public void DongjieAccount( string sqlQuery )
        {
            string sqlQueryAll = string.Format( "UPDATE AccountsInfo SET Nullity=1 {0}", sqlQuery );
            Database.ExecuteNonQuery( sqlQueryAll );
        }
        /// <summary>
        /// 解冻玩家
        /// </summary>
        /// <param name="sqlQuery">条件</param>
        public void JieDongAccount( string sqlQuery )
        {
            string sqlQueryAll = string.Format( "UPDATE AccountsInfo SET Nullity=0 {0}", sqlQuery );
            Database.ExecuteNonQuery( sqlQueryAll );
        }
        /// <summary>
        /// 设为机器人
        /// </summary>
        /// <param name="sqlQuery">条件</param>
        public void SettingAndroid( string sqlQuery )
        {
            string sqlQueryAll = string.Format( "UPDATE AccountsInfo SET IsAndroid=1 {0}", sqlQuery );
            Database.ExecuteNonQuery( sqlQueryAll );
        }
        /// <summary>
        /// 取消机器人
        /// </summary>
        /// <param name="sqlQuery">条件</param>
        public void CancleAndroid( string sqlQuery )
        {
            string sqlQueryAll = string.Format( "UPDATE AccountsInfo SET IsAndroid=0 {0}", sqlQuery );
            Database.ExecuteNonQuery( sqlQueryAll );
        }


        /// <summary>
        /// 添加玩家信息
        /// </summary>
        /// <param name="account">AccountsInfo实体</param>
        /// <param name="datum">IndividualDatum实体</param>
        /// <returns></returns>
        public Message AddAccount( AccountsInfo account, IndividualDatum datum )
        {
            var prams = new List<DbParameter>( );

            prams.Add( Database.MakeInParam( "strAccounts", account.Accounts ) );
            prams.Add( Database.MakeInParam( "strNickName", account.NickName ) );
            prams.Add( Database.MakeInParam( "strLogonPass", account.LogonPass ) );
            prams.Add( Database.MakeInParam( "strInsurePass", account.InsurePass ) );
            prams.Add( Database.MakeInParam( "dwFaceID", account.FaceID ) );
            prams.Add( Database.MakeInParam( "strUnderWrite", account.UnderWrite ) );
            prams.Add( Database.MakeInParam( "strPassPortID", account.PassPortID ) );
            prams.Add( Database.MakeInParam( "strCompellation", account.Compellation ) );

            prams.Add( Database.MakeInParam( "dwExperience", account.Experience ) );
            prams.Add( Database.MakeInParam( "dwPresent", account.Present ) );
            prams.Add( Database.MakeInParam( "dwLoveLiness", account.LoveLiness ) );
            prams.Add( Database.MakeInParam( "dwUserRight", account.UserRight ) );
            prams.Add( Database.MakeInParam( "dwMasterRight", account.MasterRight ) );
            prams.Add( Database.MakeInParam( "dwServiceRight", account.ServiceRight ) );
            prams.Add( Database.MakeInParam( "dwMasterOrder", account.MasterOrder ) );

            prams.Add( Database.MakeInParam( "dwMemberOrder", account.MemberOrder ) );
            prams.Add( Database.MakeInParam( "dtMemberOverDate", account.MemberOverDate ) );
            prams.Add( Database.MakeInParam( "dtMemberSwitchDate", account.MemberSwitchDate ) );
            prams.Add( Database.MakeInParam( "dwGender", account.Gender ) );
            prams.Add( Database.MakeInParam( "dwNullity", account.Nullity ) );

            prams.Add( Database.MakeInParam( "dwStunDown", account.StunDown ) );
            prams.Add( Database.MakeInParam( "dwMoorMachine", account.MoorMachine ) );
            prams.Add( Database.MakeInParam( "strRegisterIP", account.RegisterIP ) );
            prams.Add( Database.MakeInParam( "strRegisterMachine", account.RegisterMachine ) );
            prams.Add( Database.MakeInParam( "IsAndroid", account.IsAndroid ) );


            prams.Add( Database.MakeInParam( "strQQ", datum.QQ ) );
            prams.Add( Database.MakeInParam( "strEMail", datum.EMail ) );
            prams.Add( Database.MakeInParam( "strSeatPhone", datum.SeatPhone ) );
            prams.Add( Database.MakeInParam( "strMobilePhone", datum.MobilePhone ) );

            prams.Add( Database.MakeInParam( "strDwellingPlace", datum.DwellingPlace ) );
            prams.Add( Database.MakeInParam( "strPostalCode", datum.PostalCode ) );
            prams.Add( Database.MakeInParam( "strUserNote", datum.UserNote ) );

            Message msg = MessageHelper.GetMessage( Database, "NET_PM_AddAccount", prams );
            return msg;
        }

        /// <summary>
        ///  更新用户基本信息
        /// </summary>
        /// <param name="account">AccountsInfo实体</param>
        public void UpdateAccount( AccountsInfo account )
        {
            StringBuilder sqlQuery = new StringBuilder( );
            sqlQuery.Append( "UPDATE AccountsInfo SET " )
                    .Append( "Accounts=@Accounts, " )
                    .Append( "NickName=@NickName, " )
                    .Append( "UnderWrite=@UnderWrite, " )
                    .Append( "LogonPass=@LogonPass, " )
                    .Append( "InsurePass=@InsurePass, " )
                    .Append( "Experience=@Experience, " )
                    .Append( "Present=@Present, " )
                    .Append( "LoveLiness=@LoveLiness, " )
                    .Append( "Gender=@Gender, " )
                    .Append( "FaceID=@FaceID, " )
                    .Append( "StunDown=@StunDown, " )
                    .Append( "Nullity=@Nullity, " )
                    .Append( "MoorMachine=@MoorMachine," )
                    .Append( "IsAndroid=@IsAndroid," )
                    .Append( "UserRight=@UserRight," )
                    .Append( "MasterOrder=@MasterOrder," )
                    .Append( "MasterRight=@MasterRight  " )
                    .Append( "WHERE UserID=@UserID" );

            var prams = new List<DbParameter>( );
            prams.Add( Database.MakeInParam( "Accounts", account.Accounts ) );
            prams.Add( Database.MakeInParam( "NickName", account.NickName ) );
            prams.Add( Database.MakeInParam( "UnderWrite", account.UnderWrite ) );

            prams.Add( Database.MakeInParam( "LogonPass", account.LogonPass ) );
            prams.Add( Database.MakeInParam( "InsurePass", account.InsurePass ) );

            prams.Add( Database.MakeInParam( "Experience", account.Experience ) );
            prams.Add( Database.MakeInParam( "Present", account.Present ) );
            prams.Add( Database.MakeInParam( "LoveLiness", account.LoveLiness ) );

            prams.Add( Database.MakeInParam( "Gender", account.Gender ) );
            prams.Add( Database.MakeInParam( "FaceID", account.FaceID ) );
            prams.Add( Database.MakeInParam( "StunDown", account.StunDown ) );
            prams.Add( Database.MakeInParam( "Nullity", account.Nullity ) );
            prams.Add( Database.MakeInParam( "MoorMachine", account.MoorMachine ) );
            prams.Add( Database.MakeInParam( "IsAndroid", account.IsAndroid ) );


            prams.Add( Database.MakeInParam( "UserRight", account.UserRight ) );
            prams.Add( Database.MakeInParam( "MasterOrder", account.MasterOrder ) );
            prams.Add( Database.MakeInParam( "MasterRight", account.MasterRight ) );
            prams.Add( Database.MakeInParam( "UserID", account.UserID ) );

            Database.ExecuteNonQuery( CommandType.Text, sqlQuery.ToString( ), prams.ToArray( ) );
        }
        #endregion

        #region 用户详细信息管理
        /// <summary>
        /// 获取用户详细信息
        /// </summary>
        /// <param name="userID">用户UserID</param>
        /// <returns></returns>
        public IndividualDatum GetAccountDetailByUserID( int userID )
        {
            string sqlQuery = string.Format( "(NOLOCK) WHERE UserID= N'{0}'", userID );
            IndividualDatum model = aideIndividualDatumProvider.GetObject<IndividualDatum>( sqlQuery );
            return model;
        }

        /// <summary>
        /// 新增详细信息
        /// </summary>
        /// <param name="accountDetail"></param>
        /// <returns></returns>
        public void InsertAccountDetail( IndividualDatum accountDetail )
        {
            DataRow dr = aideIndividualDatumProvider.NewRow( );

            dr[IndividualDatum._UserID] = accountDetail.UserID;
            dr[IndividualDatum._Compellation] = accountDetail.Compellation;
            dr[IndividualDatum._QQ] = accountDetail.QQ;
            dr[IndividualDatum._EMail] = accountDetail.EMail;
            dr[IndividualDatum._SeatPhone] = accountDetail.SeatPhone;
            dr[IndividualDatum._MobilePhone] = accountDetail.MobilePhone;
            dr[IndividualDatum._DwellingPlace] = accountDetail.DwellingPlace;
            dr[IndividualDatum._PostalCode] = accountDetail.PostalCode;
            dr[IndividualDatum._CollectDate] = accountDetail.CollectDate;
            dr[IndividualDatum._UserNote] = accountDetail.UserNote;

            aideIndividualDatumProvider.Insert( dr );
        }

        /// <summary>
        ///  更新用户详细信息
        /// </summary>
        /// <param name="account">IndividualDatum实体</param>
        public void UpdateAccountDetail( IndividualDatum accountDetail )
        {
            StringBuilder sqlQuery = new StringBuilder( );
            sqlQuery.Append( "UPDATE IndividualDatum SET " )
                    .Append( "Compellation=@Compellation, " )
                    .Append( "QQ=@QQ, " )
                    .Append( "EMail=@EMail, " )
                    .Append( "MobilePhone=@MobilePhone, " )
                    .Append( "PostalCode=@PostalCode, " )
                    .Append( "DwellingPlace=@DwellingPlace, " )
                    .Append( "UserNote=@UserNote " )
                    .Append( "WHERE UserID=@UserID" );

            var prams = new List<DbParameter>( );
            prams.Add( Database.MakeInParam( "Compellation", accountDetail.Compellation ) );
            prams.Add( Database.MakeInParam( "QQ", accountDetail.QQ ) );
            prams.Add( Database.MakeInParam( "EMail", accountDetail.EMail ) );
            prams.Add( Database.MakeInParam( "SeatPhone", accountDetail.SeatPhone ) );
            prams.Add( Database.MakeInParam( "MobilePhone", accountDetail.MobilePhone ) );
            prams.Add( Database.MakeInParam( "PostalCode", accountDetail.PostalCode ) );
            prams.Add( Database.MakeInParam( "DwellingPlace", accountDetail.DwellingPlace ) );
            prams.Add( Database.MakeInParam( "UserNote", accountDetail.UserNote ) );
            prams.Add( Database.MakeInParam( "UserID", accountDetail.UserID ) );

            Database.ExecuteNonQuery( CommandType.Text, sqlQuery.ToString( ), prams.ToArray( ) );
        }
        #endregion

        #region 用户密保信息管理
        /// <summary>
        /// 获取用户密保信息
        /// </summary>
        /// <param name="pid">密保ProtectID</param>
        /// <returns></returns>
        public AccountsProtect GetAccountsProtectByPID( int pid )
        {
            string sqlQuery = string.Format( "(NOLOCK) WHERE ProtectID= N'{0}'", pid );
            AccountsProtect model = aideAccountsProtectProvider.GetObject<AccountsProtect>( sqlQuery );
            return model;
        }
        /// <summary>
        /// 获取用户密保信息
        /// </summary>
        /// <param name="uid">用户标识</param>
        /// <returns></returns>
        public AccountsProtect GetAccountsProtectByUserID( int uid )
        {
            string sqlQuery = string.Format( "(NOLOCK) WHERE UserID= N'{0}'", uid );
            AccountsProtect model = aideAccountsProtectProvider.GetObject<AccountsProtect>( sqlQuery );
            if ( model != null )
                return model;
            else
                return new AccountsProtect( );
        }
        /// <summary>
        /// 更新用户密保信息
        /// </summary>
        /// <param name="accountProtect"></param>
        public void UpdateAccountsProtect( AccountsProtect accountProtect )
        {
            StringBuilder sqlQuery = new StringBuilder( );
            sqlQuery.Append( "UPDATE AccountsProtect SET " )
                    .Append( "Question1=@Question1, " )
                    .Append( "Response1=@Response1, " )
                    .Append( "Question2=@Question2, " )
                    .Append( "Response2=@Response2, " )
                    .Append( "Question3=@Question3, " )
                    .Append( "Response3=@Response3, " )
                    .Append( "SafeEmail=@SafeEmail, " )
                    .Append( "ModifyDate=getdate()  " )
                    .Append( "WHERE ProtectID=@ProtectID" );

            var prams = new List<DbParameter>( );
            prams.Add( Database.MakeInParam( "Question1", accountProtect.Question1 ) );
            prams.Add( Database.MakeInParam( "Response1", accountProtect.Response1 ) );
            prams.Add( Database.MakeInParam( "Question2", accountProtect.Question2 ) );
            prams.Add( Database.MakeInParam( "Response2", accountProtect.Response2 ) );
            prams.Add( Database.MakeInParam( "Question3", accountProtect.Question3 ) );
            prams.Add( Database.MakeInParam( "Response3", accountProtect.Response3 ) );
            prams.Add( Database.MakeInParam( "SafeEmail", accountProtect.SafeEmail ) );
            prams.Add( Database.MakeInParam( "ProtectID", accountProtect.ProtectID ) );

            Database.ExecuteNonQuery( CommandType.Text, sqlQuery.ToString( ), prams.ToArray( ) );
        }


        /// <summary>
        /// 删除用户密保信息
        /// </summary>
        /// <param name="pid">密保ProtectID</param>
        public void DeleteAccountsProtect( int pid )
        {
            string sqlQuery = string.Format( "WHERE ProtectID={0}", pid );
            aideAccountsProtectProvider.Delete( sqlQuery );
        }

        /// <summary>
        /// 删除限制字符信息
        /// </summary>
        /// <param name="sqlQuery"></param>
        public void DeleteAccountsProtect( string sqlQuery )
        {
            aideAccountsProtectProvider.Delete( sqlQuery );
        }

        #endregion

        #region 靓号信息
        /// <summary>
        /// 随机取出10个靓号
        /// </summary>
        /// <returns></returns>
        public DataSet GetReserveIdentifierList( )
        {
            string sqlCommandText = @"  SELECT TOP 10 GameID FROM QPAccountsDBLink.QPAccountsDB.dbo.ReserveIdentifier
                                        WHERE Distribute=0 ORDER BY NEWID()";
            DataSet ds = Database.ExecuteDataset( CommandType.Text, sqlCommandText );
            return ds;

        }
        #endregion

        #region 限制字符管理

        /// <summary>
        /// 分页获取限制字符列表
        /// </summary>
        /// <param name="pageIndex">当前页码</param>
        /// <param name="pageSize">每页条数</param>
        /// <param name="condition">条件</param>
        /// <param name="orderby">排序</param>
        /// <returns></returns>
        public PagerSet GetConfineContentList( int pageIndex, int pageSize, string condition, string orderby )
        {
            PagerParameters pagerPrams = new PagerParameters( ConfineContent.Tablename, orderby, condition, pageIndex, pageSize );
            return GetPagerSet2( pagerPrams );
        }

        /// <summary>
        /// 获取限制字符
        /// </summary>
        /// <param name="strString">限制字符表主健</param>
        /// <returns></returns>
        public ConfineContent GetConfineContentByString( string strString )
        {
            string sqlQuery = string.Format( "(NOLOCK) WHERE String= N'{0}'", strString );
            ConfineContent model = aideConfineContentProvider.GetObject<ConfineContent>( sqlQuery );
            if (model != null)
                return model;
            else
                return null;
        }
        /// <summary>
        /// 新增一条限制字符信息
        /// </summary>
        /// <param name="content"></param>
        public void InsertConfineContent( ConfineContent content )
        {
            DataRow dr = aideConfineContentProvider.NewRow( );

            dr[ConfineContent._String] = content.String;
            if ( !content.EnjoinOverDate.Equals( Convert.ToDateTime( "1900-01-01" ) ) )
                dr[ConfineContent._EnjoinOverDate] = content.EnjoinOverDate;
            dr[ConfineContent._CollectDate] = DateTime.Now;
            aideConfineContentProvider.Insert( dr );
        }
        /// <summary>
        ///  更新限制字符信息
        /// </summary>
        /// <param name="content"></param>
        public void UpdateConfineContent( ConfineContent content )
        {
            StringBuilder sqlQuery = new StringBuilder( );
            sqlQuery.Append( "UPDATE ConfineContent SET " )
                    .Append( "EnjoinOverDate=@EnjoinOverDate " )
                    .Append( "WHERE String=@String" );

            var prams = new List<DbParameter>( );
            prams.Add( Database.MakeInParam( "EnjoinOverDate" , content.EnjoinOverDate.Equals( Convert.ToDateTime( "1900-01-01" ) ) ? null : content.EnjoinOverDate.ToString() ) );
            prams.Add( Database.MakeInParam( "String", content.String ) );

            Database.ExecuteNonQuery( CommandType.Text, sqlQuery.ToString( ), prams.ToArray( ) );
        }
        /// <summary>
        /// 删除限制字符信息
        /// </summary>
        /// <param name="strString"></param>
        public void DeleteConfineContentByString( string strString )
        {
            string sqlQuery = string.Format( "WHERE String='{0}'", strString );
            aideConfineContentProvider.Delete( sqlQuery );
        }

        /// <summary>
        /// 删除限制字符信息
        /// </summary>
        /// <param name="sqlQuery"></param>
        public void DeleteConfineContent( string sqlQuery )
        {
            aideConfineContentProvider.Delete( sqlQuery );
        }
        #endregion

        #region 限制地址管理

        /// <summary>
        /// 分页获取限制地址列表
        /// </summary>
        /// <param name="pageIndex">当前页码</param>
        /// <param name="pageSize">每页条数</param>
        /// <param name="condition">条件</param>
        /// <param name="orderby">排序</param>
        /// <returns></returns>
        public PagerSet GetConfineAddressList( int pageIndex, int pageSize, string condition, string orderby )
        {
            PagerParameters pagerPrams = new PagerParameters( ConfineAddress.Tablename, orderby, condition, pageIndex, pageSize );
            return GetPagerSet2( pagerPrams );
        }

        /// <summary>
        /// 获取限制地址
        /// </summary>
        /// <param name="strAddress">限制地址表主健</param>
        /// <returns></returns>
        public ConfineAddress GetConfineAddressByAddress( string strAddress )
        {
            string sqlQuery = string.Format( "(NOLOCK) WHERE AddrString= N'{0}'", strAddress );
            ConfineAddress model = aideConfineAddressProvider.GetObject<ConfineAddress>( sqlQuery );
            return model;
        }
        /// <summary>
        /// 新增一条限制地址信息
        /// </summary>
        /// <param name="address"></param>
        public void InsertConfineAddress( ConfineAddress address )
        {
            DataRow dr = aideConfineAddressProvider.NewRow( );

            dr[ConfineAddress._AddrString] = address.AddrString;
            dr[ConfineAddress._EnjoinLogon] = address.EnjoinLogon;
            dr[ConfineAddress._EnjoinRegister] = address.EnjoinRegister;
            if ( !address.EnjoinOverDate.Equals( Convert.ToDateTime( "1900-01-01" ) ) )
                dr[ConfineContent._EnjoinOverDate] = address.EnjoinOverDate;
            dr[ConfineAddress._CollectNote] = address.CollectNote;
            dr[ConfineAddress._CollectDate] = DateTime.Now;
            aideConfineAddressProvider.Insert( dr );
        }
        /// <summary>
        ///  更新限制地址信息
        /// </summary>
        /// <param name="address"></param>
        public void UpdateConfineAddress( ConfineAddress address )
        {
            StringBuilder sqlQuery = new StringBuilder( );
            sqlQuery.Append( "UPDATE ConfineAddress SET " )
                .Append( "EnjoinLogon=@EnjoinLogon, " )
                .Append( "EnjoinRegister=@EnjoinRegister, " )
                .Append( "EnjoinOverDate=@EnjoinOverDate, " )
                .Append( "CollectNote=@CollectNote " )
                .Append( "WHERE AddrString=@AddrString" );

            var prams = new List<DbParameter>( );
            prams.Add( Database.MakeInParam( "EnjoinLogon", address.EnjoinLogon ) );
            prams.Add( Database.MakeInParam( "EnjoinRegister", address.EnjoinRegister ) );
            prams.Add( Database.MakeInParam( "EnjoinOverDate" , address.EnjoinOverDate.Equals( Convert.ToDateTime( "1900-01-01" ) ) ? null : address.EnjoinOverDate.ToString( ) ) );
            prams.Add( Database.MakeInParam( "CollectNote", address.CollectNote ) );
            prams.Add( Database.MakeInParam( "AddrString", address.AddrString ) );

            Database.ExecuteNonQuery( CommandType.Text, sqlQuery.ToString( ), prams.ToArray( ) );
        }
        /// <summary>
        /// 删除限制地址信息
        /// </summary>
        /// <param name="strAddress"></param>
        public void DeleteConfineAddressByAddress( string strAddress )
        {
            string sqlQuery = string.Format( "WHERE AddrString='{0}'", strAddress );
            aideConfineAddressProvider.Delete( sqlQuery );
        }

        /// <summary>
        /// 删除限制地址信息
        /// </summary>
        /// <param name="sqlQuery"></param>
        public void DeleteConfineAddress( string sqlQuery )
        {
            aideConfineAddressProvider.Delete( sqlQuery );
        }
        #endregion

        #region 限制机器码管理

        /// <summary>
        /// 分页获取限制机器码列表
        /// </summary>
        /// <param name="pageIndex">当前页码</param>
        /// <param name="pageSize">每页条数</param>
        /// <param name="condition">条件</param>
        /// <param name="orderby">排序</param>
        /// <returns></returns>
        public PagerSet GetConfineMachineList( int pageIndex, int pageSize, string condition, string orderby )
        {
            PagerParameters pagerPrams = new PagerParameters( ConfineMachine.Tablename, orderby, condition, pageIndex, pageSize );
            return GetPagerSet2( pagerPrams );
        }

        /// <summary>
        /// 获取限制机器码
        /// </summary>
        /// <param name="strSerial">限制机器码表主健</param>
        /// <returns></returns>
        public ConfineMachine GetConfineMachineBySerial( string strSerial )
        {
            string sqlQuery = string.Format( "(NOLOCK) WHERE MachineSerial= N'{0}'", strSerial );
            ConfineMachine model = aideConfineMachineProvider.GetObject<ConfineMachine>( sqlQuery );
            return model;
        }
        /// <summary>
        /// 新增一条限制机器码信息
        /// </summary>
        /// <param name="machine"></param>
        public void InsertConfineMachine( ConfineMachine machine )
        {
            DataRow dr = aideConfineMachineProvider.NewRow( );

            dr[ConfineMachine._MachineSerial] = machine.MachineSerial;
            dr[ConfineMachine._EnjoinLogon] = machine.EnjoinLogon;
            dr[ConfineMachine._EnjoinRegister] = machine.EnjoinRegister;
            if ( !machine.EnjoinOverDate.Equals( Convert.ToDateTime( "1900-01-01" ) ) )
                dr[ConfineContent._EnjoinOverDate] = machine.EnjoinOverDate;
            dr[ConfineMachine._CollectNote] = machine.CollectNote;
            dr[ConfineMachine._CollectDate] = DateTime.Now;
            aideConfineMachineProvider.Insert( dr );
        }
        /// <summary>
        ///  更新限制机器码信息
        /// </summary>
        /// <param name="machine"></param>
        public void UpdateConfineMachine( ConfineMachine machine )
        {
            StringBuilder sqlQuery = new StringBuilder( );
            sqlQuery.Append( "UPDATE ConfineMachine SET " )
                .Append( "EnjoinLogon=@EnjoinLogon, " )
                .Append( "EnjoinRegister=@EnjoinRegister, " )
                .Append( "EnjoinOverDate=@EnjoinOverDate, " )
                .Append( "CollectNote=@CollectNote " )
                .Append( "WHERE MachineSerial=@MachineSerial" );

            var prams = new List<DbParameter>( );
            prams.Add( Database.MakeInParam( "EnjoinLogon", machine.EnjoinLogon ) );
            prams.Add( Database.MakeInParam( "EnjoinRegister", machine.EnjoinRegister ) );
            prams.Add( Database.MakeInParam( "EnjoinOverDate" , machine.EnjoinOverDate.Equals( Convert.ToDateTime( "1900-01-01" ) ) ? null : machine.EnjoinOverDate.ToString( ) ) );
            prams.Add( Database.MakeInParam( "CollectNote", machine.CollectNote ) );
            prams.Add( Database.MakeInParam( "MachineSerial", machine.MachineSerial ) );

            Database.ExecuteNonQuery( CommandType.Text, sqlQuery.ToString( ), prams.ToArray( ) );
        }
        /// <summary>
        /// 删除限制机器码信息
        /// </summary>
        /// <param name="strSerial"></param>
        public void DeleteConfineMachineBySerial( string strSerial )
        {
            string sqlQuery = string.Format( "WHERE MachineSerial='{0}'", strSerial );
            aideConfineMachineProvider.Delete( sqlQuery );
        }

        /// <summary>
        /// 删除限制机器码信息
        /// </summary>
        /// <param name="sqlQuery"></param>
        public void DeleteConfineMachine( string sqlQuery )
        {
            aideConfineMachineProvider.Delete( sqlQuery );
        }
        #endregion

        #region 系统参数配置
        /// <summary>
        /// 获取配置列表
        /// </summary>
        /// <param name="pageIndex"></param>
        /// <param name="pageSize"></param>
        /// <param name="condition"></param>
        /// <param name="orderby"></param>
        /// <returns></returns>
        public PagerSet GetSystemStatusInfoList( int pageIndex, int pageSize, string condition, string orderby )
        {
            PagerParameters pagerPrams = new PagerParameters( SystemStatusInfo.Tablename, orderby, condition, pageIndex, pageSize );

            return GetPagerSet2( pagerPrams );
        }

        /// <summary>
        /// 获取配置信息实体
        /// </summary>
        /// <param name="statusName"></param>
        /// <returns></returns>
        public SystemStatusInfo GetSystemStatusInfo( string statusName )
        {
            string sqlQuery = string.Format( "(NOLOCK) WHERE StatusName= '{0}'", statusName );
            SystemStatusInfo systemStatusInfo = aideSystemStatusInfoProvider.GetObject<SystemStatusInfo>( sqlQuery );
            return systemStatusInfo;
        }
        /// <summary>
        /// 更新配置信息
        /// </summary>
        /// <param name="systemStatusInfo"></param>
        public void UpdateSystemStatusInfo( SystemStatusInfo systemStatusInfo )
        {
            StringBuilder sqlQuery = new StringBuilder( );
            sqlQuery.Append( "UPDATE SystemStatusInfo SET " )
                    .Append( "StatusValue=@StatusValue, " )
                    .Append( "StatusString=@StatusString, " )
                    .Append( "StatusTip=@StatusTip, " )
                    .Append( "StatusDescription=@StatusDescription " )
                    .Append( "WHERE StatusName=@StatusName" );

            var prams = new List<DbParameter>( );
            prams.Add( Database.MakeInParam( "StatusValue", systemStatusInfo.StatusValue ) );
            prams.Add( Database.MakeInParam( "StatusString", systemStatusInfo.StatusString ) );
            prams.Add( Database.MakeInParam( "StatusTip", systemStatusInfo.StatusTip ) );
            prams.Add( Database.MakeInParam( "StatusDescription", systemStatusInfo.StatusDescription ) );
            prams.Add( Database.MakeInParam( "StatusName", systemStatusInfo.StatusName ) );

            Database.ExecuteNonQuery( CommandType.Text, sqlQuery.ToString( ), prams.ToArray( ) );
        }
        #endregion

        #region 公共

        /// <summary>
        /// 分页获取数据列表
        /// </summary>
        /// <param name="tableName"></param>
        /// <param name="pageIndex"></param>
        /// <param name="pageSize"></param>
        /// <param name="condition"></param>
        /// <param name="orderby"></param>
        /// <returns></returns>
        public PagerSet GetList( string tableName , int pageIndex , int pageSize , string condition , string orderby )
        {
            PagerParameters pagerPrams = new PagerParameters( tableName , orderby , condition , pageIndex , pageSize );
            return GetPagerSet2( pagerPrams );
        }

        /// <summary>
        /// 执行SQL语句返回受影响的行数
        /// </summary>
        /// <param name="sql"></param>
        public int ExecuteSql( string sql )
        {
            return Database.ExecuteNonQuery( sql );
        }

        /// <summary>
        ///  执行SQL语句返回DataSet
        /// </summary>
        /// <param name="where"></param>
        /// <returns></returns>
        public DataSet GetDataSetBySql( string sql )
        {
            DataSet ds = Database.ExecuteDataset( sql );
            return ds;
        }

        /// <summary>
        /// 执行SQL语句返回一个值
        /// </summary>
        /// <param name="sql"></param>
        /// <returns></returns>
        public string GetScalarBySql( string sql )
        {
            return Database.ExecuteScalarToStr( CommandType.Text , sql );
        }

        #endregion
    }
}
