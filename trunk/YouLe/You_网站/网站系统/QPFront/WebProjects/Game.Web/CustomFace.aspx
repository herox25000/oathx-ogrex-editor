<%@ Page Language="C#" AutoEventWireup="true" %>

<%@ Import Namespace=" Game.Utils" %>
<%@ Import Namespace="Game.Facade" %>
<%@ Import Namespace="Game.Entity.Accounts" %>

<script type="text/C#" runat="server">
    protected override void OnInit ( EventArgs e )
    {
        base.OnInit( e );
        int CustomID = GameRequest.GetQueryInt( "CustomID" , -1 );
        int UserID = GameRequest.GetQueryInt( "UserID" , -1 );
        if( UserID < 0 || CustomID < 0 )
        {
            return;
        }
        StringBuilder sqlQuery = new StringBuilder( );
        sqlQuery.AppendFormat( "SELECT {0} FROM {1} WHERE ID={2} AND UserID={3}" , AccountsFace._CustomFace.ToString( ) , AccountsFace.Tablename , CustomID , UserID );
        AccountsFacade accountsFacade = new AccountsFacade( );
        object o = accountsFacade.GetObjectBySql( sqlQuery.ToString( ) );
        byte[ ] faceByte = ( byte[ ] )o;
        Response.AddHeader( "Content-Disposition" , "attachment;filename=face.txt" );
        Response.BinaryWrite( faceByte );
        Response.End( );

        //base.OnInit( e );
        //int CustomID = GameRequest.GetQueryInt( "CustomID" , -1 );
        //int OnlyID = GameRequest.GetQueryInt( "OnlyID" , -1 );
        //if( UserID < 0 || CustomID < 0 )
        //{
        //    return;
        //}
        //StringBuilder sqlQuery = new StringBuilder( );
        //sqlQuery.AppendFormat( "SELECT {0} FROM ValidateTable WHERE OnlyID={0}" ,UserID );
        //AccountsFacade accountsFacade = new AccountsFacade( );
        //object o = accountsFacade.GetObjectBySql( sqlQuery.ToString( ) );
        //byte[ ] faceByte = ( byte[ ] )o;
        //Response.AddHeader( "Content-Disposition" , "attachment;filename=face.txt" );
        //Response.BinaryWrite( faceByte );
        //Response.End( );
    }
</script>