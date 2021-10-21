#if defined _inc_impl
	#undef _inc_impl
#endif

stock ClearChatForPlayer(playerid)
{
    for(new i = 0; i < 100; i++) 
	{
        SendClientMessage(playerid, -1, " ");
    }
}


stock Player_IsNearPlayer(playerid, targetid, Float:radius)
{
	new
        Float:x,
        Float:y,
        Float:z;

	GetPlayerPos(playerid, x, y, z);

    new
        matchingVW = GetPlayerVirtualWorld(playerid) == GetPlayerVirtualWorld(targetid),
        matchingInt = GetPlayerInterior(playerid) == GetPlayerInterior(targetid),
        inRange = IsPlayerInRangeOfPoint(targetid, radius, x, y, z);

	return matchingVW && matchingInt && inRange;
}