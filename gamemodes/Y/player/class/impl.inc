#if defined _inc_impl
	#undef _inc_impl
#endif

#include <YSI_Coding\y_hooks>

static
	bool:gsPlayerClassState[MAX_PLAYERS] = true;

timer Player_ForceSpawn[50](playerid) 
{
	SetSpawnInfo(playerid, 0, Player_GetSkin(playerid), 0.0, 0.0, 0.0, 0.0, 0, 0, 0, 0, 0, 0);
	TogglePlayerSpectating(playerid, false);
}

hook OnPlayerLogin(playerid) 
{
	Logger_Dbg(PLAYER_DEBUG_HANDLER, "[Y/player/class : OnPlayerLogin] skipping class selection after login");

	gsPlayerClassState[playerid] = false;
	SetSpawnInfo(playerid, 0, Player_GetSkin(playerid), 0.0, 0.0, 0.0, 0.0, 0, 0, 0, 0, 0, 0);
	TogglePlayerSpectating(playerid, false);
	return 1;
}

hook OnPlayerRequestClass(playerid, classid) 
{
	// เมื่อกดปุ่ม F4
	if(!Class_SelectionStatus(playerid)) 
	{
		TogglePlayerSpectating(playerid, true);
		defer Player_ForceSpawn(playerid);

		Logger_Dbg(PLAYER_DEBUG_HANDLER, "[Y/player/class : OnPlayerRequestClass] skipping class selection",
			Logger_P(playerid)
    	);
	}
	return 1;
}

hook OnPlayerConnect(playerid) 
{
	gsPlayerClassState[playerid] = true;
	TogglePlayerSpectating(playerid, true);
	return 1;
}

stock Class_SelectionStatus(playerid) 
{
	return gsPlayerClassState[playerid];
}

stock void:Class_SelectionState(playerid, bool:status) 
{
	gsPlayerClassState[playerid] = status;
}