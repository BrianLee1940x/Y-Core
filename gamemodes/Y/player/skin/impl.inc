#if defined _inc_impl
	#undef _inc_impl
#endif

#include <YSI_Coding\y_hooks>

static
    gsPlayerSkin[MAX_PLAYERS] = 0;

hook OnPlayerConnect(playerid) 
{
    gsPlayerSkin[playerid] = 0;
    return 1;
}

stock Player_SetSkin(playerid, skinid, bool:save = false) 
{
	gsPlayerSkin[playerid] = skinid;
    SetPlayerSkin(playerid, gsPlayerSkin[playerid]);
    CallLocalFunction("OnPlayerChangeSkin", "iib", playerid, skinid, save);
}

stock Player_UpdateSkin(playerid, skinid) 
{
	gsPlayerSkin[playerid] = skinid;
}

stock Player_GetSkin(playerid) 
{
	return gsPlayerSkin[playerid];
}