#if defined _inc_impl
	#undef _inc_impl
#endif

#include <YSI_Coding\y_hooks>

static
    Statement:stmt_insertPlayerAccount;

hook OnMySQLConnected() 
{
    stmt_insertPlayerAccount = MySQL_PrepareStatement(Database_GetHandle(), "INSERT INTO accounts (username, password) VALUES (?, ?)");
}

static bool:_isContainNumber(const string[])
{
    for(new i = 0; string[i] != EOS; ++i )
	{
        switch(string[i]) 
        {
            case '0'..'9':
            {
                return true;
            }
        }
    }
    return false;
}

stock Auth_PromptRegister(playerid) 
{
    inline const _response(response, listitem, string:inputtext[]) 
    {
        #pragma unused listitem
        if (!response) 
        {
            Kick(playerid);
            return;
        }
        Account_Create(playerid, inputtext);
    }

    new
        string[309 + 48 + MAX_PLAYER_NAME + 1];

    static
        const RegisterMessage[] = "\
        "WHITE"ยินดีต้อนรับ "ROYALBLUE"%s \
        \n\n \
        "WHITE"บัญชีนี้ "SKYBLUE"ยังไม่ได้ลงทะเบียน "WHITE"บนเซิร์ฟเวอร์ของเรา \
        \n \
        สำหรับการลงทะเบียน ให้ป้อนรหัสผ่านด้านล่างนี้ \
        \n \
        มันจะถูกใช้เพื่อการยืนยันตัวตน \
        \n\n \
        "INDIANRED"หมายเหตุ: \
        \n \
        \t- ความยาวของรหัสผ่านควรมีตั้งแต่ 6 ถึง 30 ตัวอักษร \
        \n \
        \t- รหัสผ่านควรมีทั้งตัวเลขและตัวหนังสือ \
        \n \
        \t- รหัสผ่านที่ลงทะเบียนมีการแยกแยะตัวพิมพ์ใหญ่-เล็ก \
        \n \
    ";

    format(string, sizeof(string), RegisterMessage, Player_GetUsername(playerid), SERVER_NAME);

    Dialog_ShowCallback(playerid,
        using inline _response,
        DIALOG_STYLE_PASSWORD,
        ""ORANGE"[1/3] รหัสผ่าน",
        string,
        "ถัดไป",
        "ออกเกม");
}

static Account_Create(playerid, const password[]) 
{
    if (!(6 <= strlen(password) <= 30)) 
    {
        SendErrorMsg(playerid, "ความยาวของรหัสผ่านไม่ถูกต้อง มันควรอยู่ระหว่าง 6-30 ตัวอักษร");
        Auth_PromptRegister(playerid);
        return;
    }

    if (isnumeric(password) || !_isContainNumber(password)) 
    {
        SendErrorMsg(playerid, "รหัสผ่านไม่ถูกต้อง ควรมีตัวอักษรและตัวเลขรวมอยู่ด้วย");
        Auth_PromptRegister(playerid);
        return;
    }

    inline const OnPasswordHash(string:hash[]) 
    {
        Account_InsertToDatabase(playerid, hash);
    }

    BCrypt_HashInline(password, BCRYPT_COST, using inline OnPasswordHash);
}

static Account_InsertToDatabase(playerid, const hash[]) 
{
    inline const OnRegister() 
    {
        Player_SetUserID(playerid, cache_insert_id());
        CreatePlayerStats(playerid);

        Logger_Dbg(PLAYER_DEBUG_HANDLER, "[rp/player/auth/register : Account_InsertToDatabase] player registered successfully",
            Logger_P(playerid),
            Logger_I("uid", Player_GetUserID(playerid))
        );
    }

    MySQL_Bind(stmt_insertPlayerAccount, 0, Player_GetUsername(playerid));
    MySQL_Bind(stmt_insertPlayerAccount, 1, hash);
    MySQL_ExecuteThreaded_Inline(stmt_insertPlayerAccount, using inline OnRegister);
}