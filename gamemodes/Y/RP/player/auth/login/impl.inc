#if defined _inc_impl
	#undef _inc_impl
#endif

#include <YSI_Coding\y_hooks>

static
    gsLoginAttempts[MAX_PLAYERS];

hook OnPlayerConnect(playerid)
{
    gsLoginAttempts[playerid] = 0;
}

void:Auth_PromptLogin(playerid, const password[], len = sizeof(password), err = false) 
{
    new
        playerHash[62],
        errorMsg[64];

    if (err)
    {
        format(errorMsg, sizeof(errorMsg), "\n"WHITE"ความพยายามป้อนรหัสผ่านคงเหลือ "LIMEGREEN"%d"WHITE" ครั้ง", MAX_PASSWORD_ATTEMPT - gsLoginAttempts[playerid]);
    }

    strcpy(playerHash, password, len);

    inline const PromptLoginResponse(response, listitem, string:inputtext[]) 
    {
        #pragma unused listitem

        if(!response) 
        {
            Kick(playerid);
            return;
        }

        inline const OnPasswordVerify(bool: success) 
        {
            if(!success) 
            {
                gsLoginAttempts[playerid] ++;
                if(gsLoginAttempts[playerid] >= MAX_PASSWORD_ATTEMPT) 
                {
                    SendErrorMsg(playerid, "คุณถูกเตะออกจากเซิร์ฟเวอร์เนื่องจากพยายามเข้าสู่ระบบหลายครั้ง");
                    Kick(playerid);

                    Logger_Dbg(PLAYER_DEBUG_HANDLER, "[rp/player/auth/login : Auth_PromptLogin] player has been kicked for too many login attempts",
                        Logger_P(playerid),
                        Logger_I("uid", Player_GetUserID(playerid))
                    );
                    return;
                }
                PlayerPlaySound(playerid, 1136, 0.0, 0.0, 0.0);
                Auth_PromptLogin(playerid, playerHash, .err = true);
                
                Logger_Dbg(PLAYER_DEBUG_HANDLER, "[rp/player/auth/login : Auth_PromptLogin] player failed to login",
                    Logger_I("attemps", gsLoginAttempts[playerid]),
                    Logger_P(playerid),
                    Logger_I("uid", Player_GetUserID(playerid))
                );
                return;
            }

            Logger_Dbg(PLAYER_DEBUG_HANDLER, "[rp:player:auth:login / Auth_PromptLogin] player successfully logged in",
                Logger_P(playerid),
                Logger_I("uid", Player_GetUserID(playerid))
            );

            gsLoginAttempts[playerid] = 0;
            Account_StampLastLogin(playerid);
        }
        BCrypt_CheckInline(inputtext, playerHash, using inline OnPasswordVerify);
    }

    new
        string[58 + 64 + 24];

    static const LoginMessage[] = "\
        "WHITE"ยินดีต้อนรับสู่ "ORANGE"%s \
        \n\n\
        "WHITE"โปรดป้อนรหัสผ่านของคุณ \
        %s \
    ";

    format(
        string,
        sizeof(string),
        LoginMessage,
        SERVER_NAME,
        errorMsg
    );

    Dialog_ShowCallback(
        playerid,
        using inline PromptLoginResponse,
        DIALOG_STYLE_PASSWORD,
        "การยืนยันตัวตน",
        string,
        "ถัดไป",
        ""
    );
}

 // API

stock void:Player_SetLoginStatus(playerid, bool:status) 
{
    Group_SetPlayer(LoggedGroup, playerid, status);
}
