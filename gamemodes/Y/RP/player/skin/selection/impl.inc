#if defined _inc_impl
	#undef _inc_impl
#endif

#include <YSI_Coding\y_hooks>

static gsMaleSkins[][] = {
	{78, 135, 137, 200, 213, 230},
	{79, 136, 134, 35, 4 , 5}};

static gsFeMaleSkins[][] = {
	{41, 77, 226},
	{13, 245, 214}};

static
	gsPlayerSelector[MAX_PLAYERS],
    gsPlayerLastWorld[MAX_PLAYERS],
	gsPlayerMode[MAX_PLAYERS];

Player_BuySkin(playerid)
{
	new race = Player_GetRace(playerid);

    new 
        Float:X = 1755.7021, 
        Float:Y = -1904.0400,
        Float:Z = 13.5643,
        Float:A = 0.0;

    SetPlayerPos(playerid, X, Y, Z);
    SetPlayerFacingAngle(playerid, A);

    SetPlayerCameraLookAt(playerid, X, Y, Z);

    ShiftCoords(0, X, Y, A, 3.0);
    SetPlayerCameraPos(playerid, X, Y, Z);

    if(Player_GetGender(playerid) == 1)
    {
        Player_SetSkin(playerid, gsMaleSkins[race][0]);
    }
    else
    {
        Player_SetSkin(playerid, gsFeMaleSkins[race][0]);
    }
	gsPlayerMode[playerid] = e_SKIN_MODE_FREE;
	gsPlayerSelector[playerid] = 0;
	gsPlayerLastWorld[playerid] = GetPlayerVirtualWorld(playerid);
	SetPlayerVirtualWorld(playerid, playerid + 5);

	TogglePlayerControllable(playerid, false);

	TextDrawShowForPlayer(playerid, SkinSelection_Menu0);
	TextDrawShowForPlayer(playerid, SkinSelection_Menu1);
	TextDrawShowForPlayer(playerid, SkinSelection_Menu2);
	TextDrawShowForPlayer(playerid, SkinSelection_Menu3);
	TextDrawShowForPlayer(playerid, SkinSelection_BtnRight);
	TextDrawShowForPlayer(playerid, SkinSelection_BtnCancel);
	TextDrawShowForPlayer(playerid, SkinSelection_BtnSelect);
	TextDrawShowForPlayer(playerid, SkinSelection_BoxAccept);
	TextDrawShowForPlayer(playerid, SkinSelection_BoxCancel);

	SelectTextDraw(playerid, 0xFF6347FF);

	return true;
}

hook OnPlayerClickTextDraw(playerid, Text:clickedid)
{
	if (gsPlayerMode[playerid] == e_SKIN_MODE_FREE)
	{
		if (clickedid == SkinSelection_BoxCancel)
		{
			return SendErrorMsg(playerid, "คุณต้องเลือกสกิน");
		}
		else if (clickedid == SkinSelection_BoxAccept)
		{
			gsPlayerMode[playerid] = 0;
			Player_SetSkin(playerid, GetPlayerSkin(playerid), true);

			SetPlayerVirtualWorld(playerid, 0);
			SetPlayerInterior(playerid, 0);

			// จุดเกิดเด็กใหม่
          	SetPlayerPos(playerid, 1756.60, -1895.25, 13.56);
			SetPlayerFacingAngle(playerid, 199.2585);

			StopAudioStreamForPlayer(playerid);
			ClearChatForPlayer(playerid);
			SendClientMessage(playerid, X11_LIMEGREEN, "[ช่วยเหลือ] "WHITE"ขอบคุณสำหรับการลงทะเบียนบนเซิร์ฟเวอร์ของเรา");

			TogglePlayerControllable(playerid, true);
			SetPlayerHealth(playerid,100);
		    SetCameraBehindPlayer(playerid);

			TextDrawHideForPlayer(playerid, SkinSelection_Menu0);
			TextDrawHideForPlayer(playerid, SkinSelection_Menu1);
			TextDrawHideForPlayer(playerid, SkinSelection_Menu2);
			TextDrawHideForPlayer(playerid, SkinSelection_Menu3);
			TextDrawHideForPlayer(playerid, SkinSelection_BtnLeft);
			TextDrawHideForPlayer(playerid, SkinSelection_BtnRight);
			TextDrawHideForPlayer(playerid, SkinSelection_BoxCancel);
			TextDrawHideForPlayer(playerid, SkinSelection_BtnSelect);
			TextDrawHideForPlayer(playerid, SkinSelection_BoxAccept);
			TextDrawHideForPlayer(playerid, SkinSelection_BtnCancel);
			
			CancelSelectTextDraw(playerid);
		}
		else if (clickedid == SkinSelection_BtnLeft)
		{
			new 
				race = Player_GetRace(playerid);

			if(gsPlayerSelector[playerid] == 0 ) return PlayerPlaySound(playerid, 30802, 0.0, 0.0, 0.0);
			else if(gsPlayerSelector[playerid] == 1 ) TextDrawHideForPlayer(playerid, SkinSelection_BtnLeft);
			TextDrawShowForPlayer(playerid, SkinSelection_BtnRight);
			gsPlayerSelector[playerid]--;

			if(Player_GetGender(playerid) == 1)
			{
				SetPlayerSkin(playerid, gsMaleSkins[race][gsPlayerSelector[playerid]]);
			}
			else
			{
				SetPlayerSkin(playerid, gsFeMaleSkins[race][gsPlayerSelector[playerid]]);
			}
		}
		else if (clickedid == SkinSelection_BtnRight)
		{
			new 
				race = Player_GetRace(playerid);

			if(Player_GetGender(playerid) == 1)
			{
				if( (gsPlayerSelector[playerid] + 1) == sizeof(gsMaleSkins[]) ) return PlayerPlaySound(playerid, 30802, 0.0, 0.0, 0.0);
				else if( (gsPlayerSelector[playerid] + 2) == sizeof(gsMaleSkins[]) ) TextDrawHideForPlayer(playerid, SkinSelection_BtnRight);
				else if(!gsMaleSkins[race][gsPlayerSelector[playerid] + 1]) return PlayerPlaySound(playerid, 30802, 0.0, 0.0, 0.0);
				else if(!gsMaleSkins[race][gsPlayerSelector[playerid] + 2]) TextDrawHideForPlayer(playerid, SkinSelection_BtnRight);
				TextDrawShowForPlayer(playerid, SkinSelection_BtnLeft);
				gsPlayerSelector[playerid]++;
				SetPlayerSkin(playerid,gsMaleSkins[race][gsPlayerSelector[playerid]]);
			}
			else
			{
				if( (gsPlayerSelector[playerid] + 1) == sizeof(gsFeMaleSkins[]) ) return PlayerPlaySound(playerid, 30802, 0.0, 0.0, 0.0);
				else if( (gsPlayerSelector[playerid] + 2) == sizeof(gsFeMaleSkins[]) ) TextDrawHideForPlayer(playerid, SkinSelection_BtnRight);
				TextDrawShowForPlayer(playerid, SkinSelection_BtnLeft);
				gsPlayerSelector[playerid]++;
				SetPlayerSkin(playerid,gsFeMaleSkins[race][gsPlayerSelector[playerid]]);
			}
		}
	}
	return 1;
}