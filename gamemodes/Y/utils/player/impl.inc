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


/*
    params:
    @forceCheck ���������� (true)

    ����� false �е�Ǩ�ͺ vw ��� int �ա�ͺ
    ���ô֧�ٻ�ҡ StreamedPlayer ������¤�����Ҽ������ͧ��繡ѹ���� �����繵�ͧ��Ǩ�ͺ���
 */
stock Player_IsNearPlayer(playerid, targetid, Float:radius, forceCheck = true)
{
	new
        Float:x,
        Float:y,
        Float:z;

	GetPlayerPos(playerid, x, y, z);
    new bool:inRange = IsPlayerInRangeOfPoint(targetid, radius, x, y, z) == true;

    if (forceCheck == false)
    {
        return GetPlayerVirtualWorld(playerid) == GetPlayerVirtualWorld(targetid) &&
            GetPlayerInterior(playerid) == GetPlayerInterior(targetid) &&
            inRange;
    }

    return inRange;
}