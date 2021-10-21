#if defined _inc_impl
	#undef _inc_impl
#endif

#include <YSI_Coding\y_hooks>

static
    Statement:stmt_loadPlayerStats,
    Statement:stmt_insertPlayerStats,
    Statement:stmt_savePlayerXP,
    Statement:stmt_savePlayerMoney,
    Statement:stmt_savePlayerRace,
    Statement:stmt_savePlayerGender;

static
    PlayerXP[MAX_PLAYERS],
    PlayerGender[MAX_PLAYERS],
    PlayerRace[MAX_PLAYERS];

timer DelayGiveMoney[100](playerid, money)
{
    Logger_Dbg(PLAYER_DEBUG_HANDLER, "[rp/player/stats : / Timer:DelayGiveMoney]",
        Logger_P(playerid),
        Logger_I("money", money)
    );

    GivePlayerMoneyEx(playerid, money);
}

hook OnMySQLConnected() 
{
    static const PlayerStatsQuery[] ="\
    SELECT \
        developer, \
        gender, \
        race, \
        money, \
        xp \
    FROM \
        player_stats \
    WHERE \
        p_id = ?";

    stmt_loadPlayerStats = MySQL_PrepareStatement(Database_GetHandle(), PlayerStatsQuery);

    stmt_insertPlayerStats = MySQL_PrepareStatement(Database_GetHandle(), "INSERT INTO player_stats (p_id) VALUES (?)");

    stmt_savePlayerMoney = MySQL_PrepareStatement(Database_GetHandle(), "UPDATE player_stats SET money=? WHERE p_id=?");

    static const savePlayerXPQuery[] = "\
    UPDATE \
        player_stats \
    SET \
        xp = ? \
    WHERE \
        p_id = ? \
    ";
    stmt_savePlayerXP = MySQL_PrepareStatement(Database_GetHandle(), savePlayerXPQuery);

    static const savePlayerGenderQuery[] = "\
    UPDATE \
        player_stats \
    SET \
        gender = ? \
    WHERE \
        p_id = ? \
    ";
    stmt_savePlayerGender = MySQL_PrepareStatement(Database_GetHandle(), savePlayerGenderQuery);


    static const savePlayerRaceQuery[] = "\
    UPDATE \
        player_stats \
    SET \
        race = ? \
    WHERE \
        p_id = ? \
    ";
    stmt_savePlayerRace = MySQL_PrepareStatement(Database_GetHandle(), savePlayerRaceQuery);
}

hook OnPlayerLogin(playerid) {
    Player_LoadStats(playerid);
    return 1;
}

CreatePlayerStats(playerid) 
{
    inline const OnStatsCreated() 
    {
        if(!Player_IsLoggedIn(playerid))
        {
            Character_ChooseGender(playerid);
        }
        else
        {
            Player_LoadStats(playerid);
        }
    }
    MySQL_BindInt(stmt_insertPlayerStats, 0, Player_GetUserID(playerid));
    MySQL_ExecuteThreaded_Inline(stmt_insertPlayerStats, using inline OnStatsCreated);
}

static Player_LoadStats(playerid) 
{
    inline OnDataLoad() 
    {
        new
            isDeveloper,
            playerGender,
            playerRace,
            playerMoney,
            playerXP;

        MySQL_BindResultInt(stmt_loadPlayerStats, 0, isDeveloper);
        MySQL_BindResultInt(stmt_loadPlayerStats, 1, playerGender);
        MySQL_BindResultInt(stmt_loadPlayerStats, 2, playerRace);
        MySQL_BindResultInt(stmt_loadPlayerStats, 3, playerMoney);
        MySQL_BindResultInt(stmt_loadPlayerStats, 4, playerXP);

        if(MySQL_Statement_FetchRow(stmt_loadPlayerStats)) 
        {
        
            Logger_Dbg(PLAYER_DEBUG_HANDLER, "[rp/player/stats : Player_LoadStats]",
                Logger_P(playerid)
            );

            if (isDeveloper == 1)
            {
                Admin_SetPlayerDeveloper(playerid, true);
            }

            defer DelayGiveMoney(playerid, playerMoney);

            Player_SetXP(playerid, playerXP);
            Player_SetGender(playerid, playerGender);
            Player_SetRace(playerid, playerRace);
        }
        else
        {
            CreatePlayerStats(playerid);
        }
    }

    MySQL_BindInt(stmt_loadPlayerStats, 0, Player_GetUserID(playerid));
    MySQL_ExecuteParallel_Inline(stmt_loadPlayerStats, using inline OnDataLoad);
}


stock Player_GiveXP(playerid, xp, bool:save = true) 
{
    new
        currentXP = Player_GetXP(playerid),
        newXP = currentXP + xp;
    
    PlayerXP[playerid] = newXP;

    if(currentXP != newXP) 
    {
        if(save) 
        {
            MySQL_BindInt(stmt_savePlayerXP, 0, newXP);
            MySQL_BindInt(stmt_savePlayerXP, 1, Player_GetUserID(playerid));
            MySQL_ExecuteThreaded(stmt_savePlayerXP);
        }
    }
}


stock Player_SetXP(playerid, xp, bool:save = false)
{
    PlayerXP[playerid] = xp;

    if(save) {
        MySQL_BindInt(stmt_savePlayerXP, 0, xp);
        MySQL_BindInt(stmt_savePlayerXP, 1, Player_GetUserID(playerid));
        MySQL_ExecuteThreaded(stmt_savePlayerXP);
    }
}

stock Player_GetXP(playerid)
    return PlayerXP[playerid];


stock Player_SetGender(playerid, gender, bool:save = false)
{
    PlayerGender[playerid] = gender;

    if(save) {
        MySQL_BindInt(stmt_savePlayerGender, 0, gender);
        MySQL_BindInt(stmt_savePlayerGender, 1, Player_GetUserID(playerid));
        MySQL_ExecuteThreaded(stmt_savePlayerGender);
    }
}

stock Player_GetGender(playerid)
    return PlayerGender[playerid];


stock Player_SetRace(playerid, race, bool:save = false)
{
    PlayerRace[playerid] = race;

    if(save) {
        MySQL_BindInt(stmt_savePlayerRace, 0, race);
        MySQL_BindInt(stmt_savePlayerRace, 1, Player_GetUserID(playerid));
        MySQL_ExecuteThreaded(stmt_savePlayerRace);
    }
}

stock Player_GetRace(playerid)
    return PlayerRace[playerid];

forward OnPlayerMoneyChange(playerid, previous, current);
public OnPlayerMoneyChange(playerid, previous, current) 
{
    // ถ้ายังไม่เลือกตัวละครก็อย่าพึ่งอัพเดตอะไร
    if (!Player_IsLoggedIn(playerid))
        return 0;

    Logger_Dbg(PLAYER_DEBUG_HANDLER, "[rp/player/stats : / OnPlayerMoneyChange]",
        Logger_P(playerid),
        Logger_I("previous", previous),
        Logger_I("current", current)
    );
    
    MySQL_BindInt(stmt_savePlayerMoney, 0, current);
    MySQL_BindInt(stmt_savePlayerMoney, 1, Player_GetUserID(playerid));
    MySQL_ExecuteThreaded(stmt_savePlayerMoney);
    return 1;
}