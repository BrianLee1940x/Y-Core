#if defined _inc_impl
	#undef _inc_impl
#endif

// เรียกใช้ได้แบบ OnServerSecondUpdate แต่มี parameter ผู้เล่นเพิ่มเข้ามา (playerid)
// CTRL + P: y/rp/core/impl.inc

static ptask _PlayerPerSecondTimer[1000](playerid) 
{
    if(Player_IsSpawned(playerid)) 
	{
        CallLocalFunction("OnPlayerSecondUpdate", "i", playerid);
    }
}