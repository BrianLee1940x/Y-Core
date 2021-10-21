#if defined _inc_impl
	#undef _inc_impl
#endif

#include <YSI_Coding\y_hooks>

static
	gsUID[MAX_PLAYERS],
	gsUsername[MAX_PLAYERS][MAX_PLAYER_NAME + 1];

static
    Statement:stmt_updatePlayerLastLogin;

hook OnMySQLConnected() 
{
    stmt_updatePlayerLastLogin = MySQL_PrepareStatement(Database_GetHandle(), "UPDATE accounts SET last_login = CURRENT_TIMESTAMP() WHERE u_id = ?");
}

hook OnPlayerConnect(playerid)
{
	new
        playerName[MAX_PLAYER_NAME + 1];

    GetPlayerName(playerid, playerName, sizeof(playerName));
	Player_SetUsername(playerid, playerName);
	return 1;
}

stock Account_StampLastLogin(playerid)
{
    MySQL_BindInt(stmt_updatePlayerLastLogin, 0, Player_GetUserID(playerid));
    MySQL_ExecuteThreaded(stmt_updatePlayerLastLogin);
    
    Player_SetLoginStatus(playerid, true);
	CallLocalFunction("OnPlayerLogin", "i", playerid);
}

stock Player_SetUsername(playerid, const name[], len = sizeof(name)) 
{
    memset(gsUsername[playerid], 0);
    strcpy(gsUsername[playerid], name, len);
}

stock Player_GetUsername(playerid) 
{
    return gsUsername[playerid];
}

stock Player_SetUserID(playerid, value) 
{
    return gsUID[playerid] = value;
}

stock Player_GetUserID(playerid) 
{
    return gsUID[playerid];
}