#if defined _inc_impl
	#undef _inc_impl
#endif

#include <YSI_Coding\y_hooks>

static
    Player_VIPLevel[MAX_PLAYERS],
    Statement: stmt_deleteVIP,
    Statement: stmt_insertVIP,
    Statement: stmt_selectVIP;

hook OnMySQLConnected()
{
    static const delete_Query[] = "\
    DELETE FROM \
        vips \
    WHERE \
        p_id = ?";
    stmt_deleteVIP = MySQL_PrepareStatement(Database_GetHandle(), delete_Query);

    static const insert_Query[] = "\
    INSERT INTO \
        vips (p_id, vip_level, vip_expire_date) \
    VALUES \
        (?, ?, DATE_ADD(CURRENT_TIMESTAMP(), INTERVAL ? MONTH)) \
    ON DUPLICATE KEY UPDATE \
	    vip_level = ?, \
	    vip_expire_date = DATE_ADD(CURRENT_TIMESTAMP(), INTERVAL ? MONTH) \
    ";
    stmt_insertVIP = MySQL_PrepareStatement(Database_GetHandle(), insert_Query);

    static const select_Query[] = "\
    SELECT \
        vip_level, \
        DATE_FORMAT(vip_expire_date, '%d %M %Y เวลา %r') as expiry, \
        TIMESTAMPDIFF(SECOND, CURRENT_TIMESTAMP(), vip_expire_date) as expire \
    FROM vips \
    WHERE \
        p_id = ? LIMIT 1";
    stmt_selectVIP = MySQL_PrepareStatement(Database_GetHandle(), select_Query);
}

hook OnPlayerConnect(playerid)
{
    Player_VIPLevel[playerid] = 0;
}

hook OnPlayerLogin(playerid)
{
    inline OnPlayerVIPLoad()
    {
        new
            expire, 
            expiry_date[30];

        MySQL_BindResultInt(stmt_selectVIP, 0, Player_VIPLevel[playerid]);
        MySQL_BindResult(stmt_selectVIP, 1, expiry_date, sizeof(expiry_date));
        MySQL_BindResultInt(stmt_selectVIP, 2, expire);

        
        if(MySQL_Statement_FetchRow(stmt_selectVIP)) {

            if (VIP_GetPlayerLevel(playerid) == 0)
            {
                VIP_RemovePlayer(playerid);
                return;
            }

            if (expire <= 0) {
                VIP_RemovePlayer(playerid);
                SendServerMsgF(playerid, "ระดับ VIP ของคุณได้หมดอายุลงแล้วเมื่อ "GREY"%s", expiry_date);
                Player_VIPLevel[playerid] = 0;
                return;
            }
        
            SendServerMsgF(playerid, "คุณได้เข้าสู่ระบบด้วย VIP ระดับ %i ("GREY"วันหมดอายุ %s"WHITE")", VIP_GetPlayerLevel(playerid), expiry_date);
        }
    }

    MySQL_BindInt(stmt_selectVIP, 0, Player_GetUserID(playerid));
    MySQL_ExecuteThreaded_Inline(stmt_selectVIP, using inline OnPlayerVIPLoad);
}

stock VIP_GivePlayer(playerid, level, duration) {
   
    MySQL_BindInt(stmt_insertVIP, 0, Player_GetUserID(playerid));
    MySQL_BindInt(stmt_insertVIP, 1, level);
    MySQL_BindInt(stmt_insertVIP, 2, duration);
    MySQL_BindInt(stmt_insertVIP, 3, level);
    MySQL_BindInt(stmt_insertVIP, 4, duration);

    MySQL_ExecuteThreaded(stmt_insertVIP);
    Player_VIPLevel[playerid] = level;
}

stock VIP_RemovePlayer(playerid) {
    MySQL_BindInt(stmt_deleteVIP, 0, Player_GetUserID(playerid));
    MySQL_ExecuteThreaded(stmt_deleteVIP);
}

stock VIP_GetPlayerLevel(playerid) {
    return Player_VIPLevel[playerid];
}