#if defined _inc_impl
	#undef _inc_impl
#endif

#include <YSI_Coding\y_hooks>

static
    PlayerAdminLevel[MAX_PLAYERS],
    Statement:stmt_retrieveAdmin;

timer RetrieveRconPlayer[1000](ip)
{
    new
        playerIP[16 + 1];

	foreach(new i : Player) 
	{
        GetPlayerIp(i, playerIP, sizeof(playerIP));
		if (IPToInt(playerIP) == ip && IsPlayerAdmin(i)) 
		{
			CallRemoteFunction("OnPlayerRconLogin", "i", i);
			return 1;
		}
	}

	return 1;
}

hook OnMySQLConnected()
{
	static const query_retrieveAdmin[] = "\
        SELECT \
            admin_level \
        FROM  \
            admins \
        WHERE \
            u_id = ? \
        "
    ;
    stmt_retrieveAdmin = MySQL_PrepareStatement(Database_GetHandle(), query_retrieveAdmin);
}

hook OnPlayerConnect(playerid) 
{
    PlayerAdminLevel[playerid] = 0;
    return 1;
}

hook OnPlayerRconLogin(playerid)
{
	Admin_SetPlayerLevel(playerid, Y_PLAYER_ADMIN_MAX_LEVEL, true);
	return 1;
}

hook OnRconLoginAttempt(ip[], password[], success)
{
	new ip2 = IPToInt(ip);

	if (success) {
		defer RetrieveRconPlayer(ip2);
	}

	return 1;
}

hook OnPlayerLogin(playerid) 
{
    inline OnPlayerAdminLoad() 
	{
        new
            adminLevel;

        MySQL_BindResultInt(stmt_retrieveAdmin, 0, adminLevel);

        if(MySQL_Statement_FetchRow(stmt_retrieveAdmin)) 
		{
            Admin_SetPlayerLevel(playerid, adminLevel);
        }

    }
    MySQL_BindInt(stmt_retrieveAdmin, 0, Player_GetUserID(playerid));
    MySQL_ExecuteThreaded_Inline(stmt_retrieveAdmin, using inline OnPlayerAdminLoad);
}

hook OnGameModeInit()
{
	for (new i = 0; i != Y_PLAYER_ADMIN_MAX_LEVEL; ++i) 
	{
		new name[32];
		format(name, sizeof name, "Admin level %d", i + 1);
		AdminGroup[i] = Group_Create(name);

		if (i > 0) 
		{
			Group_AddChild(AdminGroup[i], AdminGroup[i - 1]);
		}
	}

	DeveloperGroup = Group_Create("Developer");
}

hook OnGroupInit()
{
	Group_AddChild(AdminGroup[0], DeveloperGroup);
	return 1;
}

stock Admin_SetPlayerDeveloper(playerid, bool:status)
{
    Logger_Dbg(PLAYER_DEBUG_HANDLER, "[rp/player/admin/core : Admin_SetPlayerDeveloper] Developer privileges", 
        Logger_P(playerid), 
        Logger_I("status", status)
    );

    Group_SetPlayer(DeveloperGroup, playerid, status);
}

Admin_ClearPlayerLevel(playerid)
{
	if (PlayerAdminLevel[playerid] > 0) 
	{
		Group_SetPlayer(AdminGroup[PlayerAdminLevel[playerid] - 1], playerid, false);	
	}
}

stock Admin_SetPlayerLevel(playerid, level, bool:force = false) {

	if (!force && IsPlayerAdmin(playerid)) 
	{
		return 2;
	}

    Admin_ClearPlayerLevel(playerid);

	if (!(1 <= level <= Y_PLAYER_ADMIN_MAX_LEVEL)) 
	{
		Logger_Err("invalid player admin level", 
            Logger_P(playerid), 
            Logger_I("level", level)
        );
        Kick(playerid);
		return 1;
	}

	Group_SetPlayer(AdminGroup[level - 1], playerid, true);
	PlayerAdminLevel[playerid] = level;

    Logger_Dbg(PLAYER_DEBUG_HANDLER, "[rp/player/admin/core : Admin_SetPlayerLevel] Administrative privileges", 
        Logger_P(playerid), 
        Logger_I("level", level)
    );

    new string[256];

    static const query[] = "\
    INSERT INTO \
        admins(u_id, admin_level) \
    VALUES \
        (%i, %i) \
    ON DUPLICATE KEY UPDATE \
        admin_level = %i \
    ";

    mysql_format(Database_GetHandle(), string, sizeof(string), query, Player_GetUserID(playerid), level, level);
    mysql_tquery(Database_GetHandle(), string);

	return 0;
}

stock Admin_GetPlayerLevel(playerid)
    return PlayerAdminLevel[playerid];
