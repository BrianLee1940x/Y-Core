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
		return SendClientMessage(playerid, X11_LIGHTBLUE, "�����"WHITE" /createroom <������ͧ>");
	
	new ret = CallRemoteFunction("Voice_CreatePlayerPrivateChat", "ids", playerid, 0x00FF00FF, roomName);
	if (ret)
	{
		SendClientMessage(playerid, -1, "���ҧ�����!!");
	}
	return 1;
}

YCMD:destroyroom(playerid, params[], help)
{
	new ret = CallRemoteFunction("Voice_DestroyPlayerPrivateChat", "i", playerid);
	if (ret)
	{
		SendClientMessage(playerid, -1, "����������!!");
	}
	return 1;
}

YCMD:joinroom(playerid, params[], help)
{
	new targetid = INVALID_PLAYER_ID;

	if (sscanf(params, "r", targetid)) 
		return SendClientMessage(playerid, X11_LIGHTBLUE, "�����"WHITE" /joinroom <�ʹռ�����>");

	if (targetid == INVALID_PLAYER_ID)
		return SendClientMessage(playerid, X11_LIGHTBLUE, "�����"WHITE" /joinroom <�ʹռ�����>");

	new ret = CallRemoteFunction("Voice_JoinPlayerPrivateChat", "ii", playerid, targetid);
	if (ret)
	{
		SendClientMessage(playerid, -1, "�����ͧ�����!!");
	}

	return 1;
}