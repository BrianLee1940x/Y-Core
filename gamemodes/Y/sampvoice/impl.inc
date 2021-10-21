#if defined _inc_impl
	#undef _inc_impl
#endif

#include <YSI_Coding\y_hooks>

YCMD:spawn(playerid, params[], help)
{
	CallLocalFunction("OnPlayerLogin", "i", playerid);
}

YCMD:createroom(playerid, params[], help)
{
	new roomName[32];

	if (sscanf(params, "s[32]", roomName)) 
		return SendClientMessage(playerid, X11_LIGHTBLUE, "การใช้"WHITE" /createroom <ชื่อห้อง>");
	
	new ret = CallRemoteFunction("Voice_CreatePlayerPrivateChat", "ids", playerid, 0x00FF00FF, roomName);
	if (ret)
	{
		SendClientMessage(playerid, -1, "สร้างสำเร็จ!!");
	}
	return 1;
}

YCMD:destroyroom(playerid, params[], help)
{
	new ret = CallRemoteFunction("Voice_DestroyPlayerPrivateChat", "i", playerid);
	if (ret)
	{
		SendClientMessage(playerid, -1, "ทำลายสำเร็จ!!");
	}
	return 1;
}

YCMD:joinroom(playerid, params[], help)
{
	new targetid = INVALID_PLAYER_ID;

	if (sscanf(params, "r", targetid)) 
		return SendClientMessage(playerid, X11_LIGHTBLUE, "การใช้"WHITE" /joinroom <ไอดีผู้เล่น>");

	if (targetid == INVALID_PLAYER_ID)
		return SendClientMessage(playerid, X11_LIGHTBLUE, "การใช้"WHITE" /joinroom <ไอดีผู้เล่น>");

	new ret = CallRemoteFunction("Voice_JoinPlayerPrivateChat", "ii", playerid, targetid);
	if (ret)
	{
		SendClientMessage(playerid, -1, "เข้าห้องสำเร็จ!!");
	}

	return 1;
}