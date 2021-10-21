#if defined _inc_impl
	#undef _inc_impl
#endif

static ptask _PlayerPerSecondTimer[1000](playerid) 
{
    if(Player_IsSpawned(playerid)) 
	{
        CallLocalFunction("OnPlayerSecondUpdate", "i", playerid);
    }
}