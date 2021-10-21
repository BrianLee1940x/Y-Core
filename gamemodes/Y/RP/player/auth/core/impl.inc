#if defined _inc_impl
	#undef _inc_impl
#endif

#include <YSI_Coding\y_hooks>

static
    Statement: stmt_checkAccount;

hook OnMySQLConnected() 
{
    stmt_checkAccount = MySQL_PrepareStatement(Database_GetHandle(), "SELECT u_id, password FROM accounts WHERE username=?");
}

hook OnGameModeInit()
{
	LoggedGroup = Group_Create("Logged in");
	return 1;
}

hook OnPlayerConnect(playerid)
{
    Admin_CheckBanUser(playerid);
	return 1;
}

hook OnPlayerSpawn(playerid) 
{
    if (!Player_IsLoggedIn(playerid))
    {
        Logger_Dbg(PLAYER_DEBUG_HANDLER, "[rp/player/auth/core : OnPlayerSpawn] spawn without login ...");
        Kick(playerid);
    }
    return 1;
}

timer MoveCamera[500](playerid) 
{
	InterpolateCameraPos(playerid, 2173.0742 + 3.0, -1046.8438 - 3.0, 74.5567, 2173.0742, -1046.8438 + 3.0, 74.5567, 1000 * 10, CAMERA_MOVE);
	InterpolateCameraLookAt(playerid, 2172.1289 + 3.0, -1047.1642 - 5.0, 74.4168, 2172.1289, -1047.1642 + 3.0, 74.4168, 1000 * 10, CAMERA_MOVE);	
}

hook OnPlayerPassedBanCheck(playerid)
{
	defer MoveCamera(playerid);
    SetPlayerVirtualWorld(playerid, 111);
    SetPlayerInterior(playerid, 0);

    // ไม่อยากฟังเสียงก็ปิดไว้
	// PlayerPlaySound(playerid, 1187, 0.0, 0.0, 0.0);
	SendClientMessage(playerid, X11_INDIANRED, !"ยินดีต้อนรับเข้าสู่ " SERVER_NAME "!");

	inline const OnDataLoad() 
	{
        new
            accountUID,
            playerHash[62];

        MySQL_BindResultInt(stmt_checkAccount, 0, accountUID);
        MySQL_BindResult(stmt_checkAccount, 1, playerHash, sizeof(playerHash));

        if(MySQL_Statement_FetchRow(stmt_checkAccount)) 
		{
            Player_SetUserID(playerid, accountUID);
            Auth_PromptLogin(playerid, playerHash);
        }
        else 
		{
            Auth_PromptRegister(playerid);
        }
    }

    MySQL_Bind(stmt_checkAccount, 0, Player_GetUsername(playerid));
    MySQL_ExecuteParallel_Inline(stmt_checkAccount, using inline OnDataLoad);
}