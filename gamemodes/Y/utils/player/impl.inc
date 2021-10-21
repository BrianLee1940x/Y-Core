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
    @forceCheck ค่าเริ่มต้น (true)

    ถ้าเป็น false จะตรวจสอบ vw และ int อีกรอ
    แต่การดึงลูปจาก StreamedPlayer นั้นหมายความว่าผู้เล่นมองเห็นกันแล้ว ไม่จำเป็นต้องตรวจสอบซ้ำ
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