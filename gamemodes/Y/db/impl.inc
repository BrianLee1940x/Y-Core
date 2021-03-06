#if defined _inc_impl
	#undef _inc_impl
#endif

#include <YSI_Coding\y_hooks>

public OnQueryError(errorid, const error[], const callback[], const query[], MySQL:handle)
{
	switch(errorid) {
		case 1136: printf("[MySQL] Error 1136 | Column count does not match value count => \"%s\"", query);
		case 1054: printf("[MySQL] Error 1054 | Invalid field name => \"%s\"", query);
		case 1065: printf("[MySQL] Error 1065 | Query was empty (variable's size too small?) => \"%s\" from \"%s\"", query, callback);
		case 1058: printf("[MySQL] Error 1058 | Column count doesn't match value count => \"%s\" from \"%s\"", query, callback);
		case 1203: printf("[MySQL] Error 1203 | User already has more than 'max_user_connections' active connections => \"%s\" from \"%s\"", query, callback);
		case 1045: printf("[MySQL] Error 1045 | Access denied");
		case ER_SYNTAX_ERROR: printf("[MySQL] Syntax Error => \"%s\"",query);

		default : printf("[MySQL] Error %d | Callback: %s | \"%s\"", errorid, callback, query);
	}
	return 1;
}

hook OnGameModeInit() 
{
    Logger_Log("[Y/db / OnGameModeInit] setting up...");

    new
        MySQLOpt: option_id = mysql_init_options();
	mysql_set_option(option_id, AUTO_RECONNECT, true);

	gMySQLHandle = mysql_connect_file("mysql.ini");
	if (gMySQLHandle == MYSQL_INVALID_HANDLE || mysql_errno(gMySQLHandle) != 0)
	{
		Logger_Fatal("MySQL failed to connect. Server shutting down...");
		return 1;
	}

	mysql_log(ERROR | WARNING);

    mysql_set_charset(MYSQL_CHARSET, gMySQLHandle);

    #if SETUP_TABLE
        CallLocalFunction("OnMySQLSetupTable", "");
	#else
		CallLocalFunction("OnMySQLConnected", "");
    #endif

    printf("MySQL connection is successful.");
    return 1;
}

hook OnGameModeExit() {
    CallLocalFunction("OnMySQLPreClose", "");
    printf("MySQL connection has been closed.");
    mysql_close(gMySQLHandle);
}