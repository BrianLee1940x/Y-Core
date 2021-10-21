#if defined _inc_impl
	#undef _inc_impl
#endif

#include <YSI_Coding\y_hooks>

static
    gsCharacterGender[MAX_PLAYERS];

timer RegistrationFinished[100](playerid)
{
    Account_StampLastLogin(playerid);

    ClearChatForPlayer(playerid);

    SendAdminMsgF(e_ADMIN_MSG_NONE, 1, "มีผู้เล่นใหม่บนเซิร์ฟเวอร์ของเรา: "ORANGE"%s "WHITE"(ID:%i)", Player_GetUsername(playerid), playerid);
    SetPlayerHealth(playerid,100);
}

hook OnPlayerSpawn(playerid) 
{
    if (Player_GetGender(playerid) == 0)
    {
        TogglePlayerSpectating(playerid, true);
        defer MoveCamera(playerid);

        Character_ChooseGender(playerid);
        return Y_HOOKS_BREAK_RETURN_1;
    }

    if(Player_GetSkin(playerid) == 0)
    {
        Player_BuySkin(playerid);
        return Y_HOOKS_BREAK_RETURN_1;
    }

    return 1;
}

void:Character_ChooseGender(playerid)
{
    inline const _response(response, listitem, string:inputtext[]) 
    {
        #pragma unused inputtext
        if (!response) 
        {
            Kick(playerid);
            return;
        }
        gsCharacterGender[playerid] = listitem + 1;
        Character_ChooseRace(playerid);
    }

    Dialog_ShowCallback(playerid,
        using inline _response,
        DIALOG_STYLE_LIST,
        ""ORANGE"[2/3] เลือกเพศสภาพ",
        "เพศชาย\nเพศหญิง",
        "ถัดไป",
        "ออกเกม");
}

void:Character_ChooseRace(playerid)
{
    inline const _response(response, listitem, string:inputtext[]) 
    {
        #pragma unused inputtext
        if (!response) 
        {
            Kick(playerid);
            return;
        }
        Player_SetRace(playerid, listitem, true);
        Player_SetGender(playerid, gsCharacterGender[playerid], true);
    
        defer RegistrationFinished(playerid);
    }
    
    Dialog_ShowCallback(playerid,
        using inline _response,
        DIALOG_STYLE_LIST,
        ""ORANGE"[3/3] เลือกสีผิว",
        "ผิวขาว\nผิวดำ",
        "ถัดไป",
        "ออกเกม");
}