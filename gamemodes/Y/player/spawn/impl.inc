#if defined _inc_impl
	#undef _inc_impl
#endif

#include <YSI_Coding\y_hooks>

hook OnPlayerConnect(playerid) 
{
    SetPlayerColor(playerid, Y_GRAY25);
    Bit_Set(Player_gSpawnState, playerid, false);
}

hook OnPlayerSpawn(playerid) 
{
    Logger_Dbg(PLAYER_DEBUG_HANDLER, "[Y/player/spawn : OnPlayerSpawn]");
    Bit_Set(Player_gSpawnState, playerid, true);
    Player_UpdateColour(playerid);
    return 1;
}

hook OnPlayerDeath(playerid, killerid, reason) 
{
    Logger_Dbg(PLAYER_DEBUG_HANDLER, "[Y/player/spawn : OnPlayerDeath]");
    Bit_Set(Player_gSpawnState, playerid, false);
    return 1;
}

stock Player_IsSpawned(playerid) 
{
    return Bit_Get(Player_gSpawnState, playerid);
}

stock Player_UpdateColour(playerid) 
{
	SetPlayerColor(playerid, Y_WHITE);
    return 1;
}