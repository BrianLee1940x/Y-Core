#if defined _inc_impl
	#undef _inc_impl
#endif

// ���¡����Ẻ OnServerSecondUpdate ���� parameter ��������������� (playerid)
// CTRL + P: y/rp/core/impl.inc

static ptask _PlayerPerSecondTimer[1000](playerid) 
{
    if(Player_IsSpawned(playerid)) 
	{
        CallLocalFunction("OnPlayerSecondUpdate", "i", playerid);
    }
}