#include "StdAfx.h"
#include "WinMySql.h"

CWinMySql::CWinMySql(void)
{
	//��ʼ��
	MySql = mysql_init((MYSQL*)0);
}

CWinMySql::~CWinMySql(void)
{
	//�ͷ�
	if( MySql!=NULL )
	{
		mysql_close( MySql );
	}
}

int CWinMySql::Connect( const char *host, const char *user, const char *passwd, const char *db, unsigned int port )
{
	//δ��ʼ��
	if( MySql==NULL )
		return MYSQL_ERROR_NO_INIT;
	//����
	if( mysql_real_connect( MySql, host, user, passwd, db, port, NULL, 0 ) == NULL )
		return MYSQL_ERROR_CONNECT;
	return 0;
}

int CWinMySql::SelectDB( const char *db )
{
	//δ��ʼ��
	if( MySql==NULL )
		return MYSQL_ERROR_NO_INIT;
	//ѡ������
	if( mysql_select_db( MySql, db ) < 0 )
		return MYSQL_ERROR_SELECT_DB;
	return 0;
}

MYSQL_RES* CWinMySql::Query( const char *query, unsigned long length )
{
	//δ��ʼ��
	if( MySql==NULL )
		return NULL;

	if( !length )
	{
		length = (unsigned long)strlen( query );
	}

	if( mysql_real_query( MySql, query, length ) )
		return NULL;

	return mysql_store_result( MySql );
}

int CWinMySql::GetResNum( MYSQL_RES* MySqlRes )
{
	return (int)mysql_num_rows( MySqlRes );
}

int CWinMySql::FreeQuery( MYSQL_RES* MySqlRes )
{
	if( MySqlRes!=NULL )
	{
		mysql_free_result( MySqlRes ) ;
		MySqlRes = NULL;
	}
	return 0;
}