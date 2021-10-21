#include <a_mysql>

#include <YSI_Coding\y_hooks>
#include <YSI_Coding\y_inline>
#include <YSI_Extra\y_inline_mysql>

hook OnMySQLSetupTable() 
{
    Logger_Log("TABLE SETUP BEGIN");

    // --------------------------------------------------------------------------------------------
    // PLAYERS
    // --------------------------------------------------------------------------------------------

    // accounts table.
    mysql_tquery_file(Database_GetHandle(), "db/accounts.sql");
    Logger_Log("setting up 'accounts' table...");

    // player stats table.
    mysql_tquery_file(Database_GetHandle(), "db/player_stats.sql");
    Logger_Log("setting up 'player stats' table...");

    // --------------------------------------------------------------------------------------------
    // ADMIN
    // --------------------------------------------------------------------------------------------

    // Admin accounts table.
    mysql_tquery_file(Database_GetHandle(), "db/admins.sql");
    Logger_Log("setting up 'admins' table...");

    // Banned accounts table.
    mysql_tquery_file(Database_GetHandle(), "db/bans.sql");
    Logger_Log("setting up 'bans' table...");

    inline Handler()
    {
        CallLocalFunction("OnMySQLConnected", "");
    }
    MySQL_TQueryInline(Database_GetHandle(), using inline Handler, "SELECT 1=1");

    Logger_Log("TABLE SETUP END");
    return 1;
}