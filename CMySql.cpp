#include "stdafx.h"
#include "CMySql.h"





CMySql::~CMySql(void)
{
    if(sock)
    {
        delete sock;
        sock = NULL;
    }
    
}

void CMySql::DisConnect()
{
    mysql_close(sock);
}

bool CMySql::ConnectMySql(char *host,char *user,char *pass,char *db)
{
   
	if (!mysql_real_connect(sock, host, user, pass, db, 0, NULL, CLIENT_MULTI_STATEMENTS))
	{
        //连接错误
		return false;
	}
	
    return true;
}

bool CMySql::SelectMySql(char* szSql,int nColumn,list<string>& lstStr)
{
    //mysql_query() 函数用于向 MySQL 发送并执行 SQL 语句
     if(mysql_query(sock,szSql))return false;

     /*·mysql_store_result 对于成功检索了数据的每个查询(SELECT、SHOW、DESCRIBE、EXPLAIN、CHECK TABLE等)
     返回值:
     . CR_COMMANDS_OUT_OF_SYNC 　　以不恰当的顺序执行了命令。
 　　· CR_OUT_OF_MEMORY 　　内存溢出。
 　　· CR_SERVER_GONE_ERROR 　　MySQL服务器不可用。
 　　· CR_SERVER_LOST 　　在查询过程中，与服务器的连接丢失。
 　　· CR_UNKNOWN_ERROR 　　出现未知错误。*/
	results=mysql_store_result(sock);
    if(NULL == results)return false;
	while (record = mysql_fetch_row(results))
	{
        
		 for(int i = 0;i < nColumn;i++)
         {
			if(!record[i])
				record[i] = "";

             lstStr.push_back(record[i]);
         }
    

	}

    return true;
}

void CMySql::init()
{
	sock = new MYSQL;
	mysql_init(sock );  
	mysql_set_character_set(sock,"gb2312");
}

bool  CMySql::UpdateMySql(char* szSql)
 {
    if(!szSql)return false;

    if(mysql_query(sock,szSql))return false;

    return true;
 }


