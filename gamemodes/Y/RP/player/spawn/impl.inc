#if defined _inc_impl
	#undef _inc_impl
#endif

#include <YSI_Coding\y_hooks>

static
    Statement:stmt_loadPlayerSpawn,
    Statement:stmt_savePlayerSpawnType;

static
    PlayerSpawnType[MAX_PLAYERS],
    Float:PlayerLastSpawnX[MAX_PLAYERS],
    Float:PlayerLastSpawnY[MAX_PLAYERS],
    Float:PlayerLastSpawnZ[MAX_PLAYERS],
    Float:PlayerLastSpawnAng[MAX_PLAYERS],
    PlayerLastSpawnVWorld[MAX_PLAYERS],
    PlayerLastSpawnInt[MAX_PLAYERS],
    bool:PlayerFirstSpawn[MAX_PLAYERS] = true
;

hook OnGroupInit()
{
	GROUP_ADD<LoggedGroup>
	{
		@YCMD:setspawn;
	}
}

hook OnMySQLConnected()
{
    static const PlayerSpawnQuery[] ="\
    SELECT \
        spawnType, \
        lastPosX, \
        lastPosY, \
        lastPosZ, \
        lastAng, \
        lastWorld, \
        lastInt \
    FROM \
        player_stats \
    WHERE \
        p_id = ?";

    stmt_loadPlayerSpawn = MySQL_PrepareStatement(Database_GetHandle(), PlayerSpawnQuery);

    static const savePlayerSpawnTypeQuery[] = "\
    UPDATE \
        player_stats \
    SET \
        spawnType = ? \
    WHERE \
        p_id = ? \
    ";
    stmt_savePlayerSpawnType = MySQL_PrepareStatement(Database_GetHandle(), savePlayerSpawnTypeQuery);
}

hook OnPlayerConnect(playerid) 
{
    PlayerLastSpawnX[playerid] = 
    PlayerLastSpawnY[playerid] = 
    PlayerLastSpawnZ[playerid] = 
    PlayerLastSpawnAng[playerid] = 0.0;

    PlayerLastSpawnVWorld[playerid] = 0;
    PlayerLastSpawnInt[playerid] = 0;

    PlayerSpawnType[playerid] = PLAYER_SPAWN_TYPE_DEFAULT;
    PlayerFirstSpawn[playerid] = true;
    return 1;
}

hook OnPlayerLogin(playerid) {
    Player_LoadSpawn(playerid);
    return 1;
}

static Player_LoadSpawn(playerid) 
{
    inline OnDataLoad() 
    {
        MySQL_BindResultInt(stmt_loadPlayerSpawn, 0, PlayerSpawnType[playerid]);
        MySQL_BindResultFloat(stmt_loadPlayerSpawn, 1, PlayerLastSpawnX[playerid]);
        MySQL_BindResultFloat(stmt_loadPlayerSpawn, 2, PlayerLastSpawnY[playerid]);
        MySQL_BindResultFloat(stmt_loadPlayerSpawn, 3, PlayerLastSpawnZ[playerid]);
        MySQL_BindResultFloat(stmt_loadPlayerSpawn, 4, PlayerLastSpawnAng[playerid]);
        MySQL_BindResultInt(stmt_loadPlayerSpawn, 5, PlayerLastSpawnVWorld[playerid]);
        MySQL_BindResultInt(stmt_loadPlayerSpawn, 6, PlayerLastSpawnInt[playerid]);

        if(MySQL_Statement_FetchRow(stmt_loadPlayerSpawn)) 
        {
            Logger_Dbg(PLAYER_DEBUG_HANDLER, "[rp/player/spawn : Player_LoadSpawn]",
                Logger_P(playerid)
            );
        }
    }

    MySQL_BindInt(stmt_loadPlayerSpawn, 0, Player_GetUserID(playerid));
    MySQL_ExecuteParallel_Inline(stmt_loadPlayerSpawn, using inline OnDataLoad);
}

hook OnPlayerSpawn(playerid) 
{

    if(PlayerFirstSpawn[playerid]) 
    {
        Logger_Dbg(PLAYER_DEBUG_HANDLER, "[rp/player/spawn : OnPlayerSpawn] calling OnPlayerFirstSpawn");
        CallLocalFunction("OnPlayerFirstSpawn", "i", playerid);
        PlayerFirstSpawn[playerid] = false;
    }

    new
        Float: x,
        Float: y,
        Float: z,
        Float: ang,
        virworld = 0,
        interior = 0;

    if (PlayerSpawnType[playerid] == PLAYER_SPAWN_TYPE_HOUSE)
    {
        // �Դ��ҹ
    }
    else if (PlayerSpawnType[playerid] == PLAYER_SPAWN_TYPE_FACTION)
    {
        // �Դῤ���
    }
    else if (PlayerSpawnType[playerid] == PLAYER_SPAWN_TYPE_POINT)
    {
        // �Դ�ش���ѹ�֡���
        x = PlayerLastSpawnX[playerid];
        y = PlayerLastSpawnY[playerid];
        z = PlayerLastSpawnZ[playerid];
        ang = PlayerLastSpawnAng[playerid];
        virworld = PlayerLastSpawnVWorld[playerid];
        interior = PlayerLastSpawnInt[playerid];
    }
    else
    {
        // �ش�Դ������
        x = 1756.60;
        y = -1895.25;
        z = 13.56;
        ang = 199.2585;

        if (PlayerSpawnType[playerid] != PLAYER_SPAWN_TYPE_DEFAULT)
        {
            Player_SetSpawn(playerid, PLAYER_SPAWN_TYPE_DEFAULT);
        }
    }
    
    SetPlayerPos(playerid, x, y, z);
    SetPlayerFacingAngle(playerid, ang);
    SetPlayerInterior(playerid, interior);
    SetPlayerVirtualWorld(playerid, virworld);

    Logger_Dbg(PLAYER_DEBUG_HANDLER, "[rp/player/spawn : OnPlayerSpawn] player spawned",
        Logger_P(playerid),
        Logger_I("id", playerid),
        Logger_F("x", x),
        Logger_F("y", y),
        Logger_F("z", z)
    );

    return 1;
}

Player_SetSpawn(playerid, type, save = true)
{
    PlayerSpawnType[playerid] = type;

    if(save) {
        MySQL_BindInt(stmt_savePlayerSpawnType, 0, type);
        MySQL_BindInt(stmt_savePlayerSpawnType, 1, Player_GetUserID(playerid));
        MySQL_ExecuteThreaded(stmt_savePlayerSpawnType);
    }
}

SetPlayerSpawnDialog(playerid)
{
    new string[500], str[124];
	new szSpawn[124];
	format(str,sizeof(str),""INDIANRED"%.2f %.2f %.2f"WHITE"", PlayerLastSpawnX[playerid], PlayerLastSpawnY[playerid], PlayerLastSpawnZ[playerid]);
	switch(PlayerSpawnType[playerid])
	{
        case PLAYER_SPAWN_TYPE_DEFAULT: szSpawn = ""TOMATO"ʶҹ�ö�"WHITE"";
        case PLAYER_SPAWN_TYPE_HOUSE: szSpawn = ""FORESTGREEN"��ҹ"WHITE"";
        case PLAYER_SPAWN_TYPE_FACTION: szSpawn = ""FORESTGREEN"ͧ���"WHITE"";
        case PLAYER_SPAWN_TYPE_POINT: szSpawn = str;
	}
	format(string, sizeof(string),"�ش�Դ㹻Ѩ�غѹ: %s\n��駺�ҹ�繨ش�Դ\n���ͧ����繨ش�Դ\n���ʶҹ�ö��繨ش�Դ\n��駵ç����繨ش�Դ", szSpawn);

    inline const Response(response, listitem, string:inputtext[]) 
    {
    	#pragma unused inputtext
    	
    	if (!response)
    	{
    		@return 1;
    	}

        switch(listitem)
        {
            case 1: // house
            {
                SendErrorMsg(playerid, "�к�����㹪�ǧ�Ѳ�� ..");
                SetPlayerSpawnDialog(playerid);
            }
            case 2: // organization
            {
                SendErrorMsg(playerid, "�к�����㹪�ǧ�Ѳ�� ..");
                SetPlayerSpawnDialog(playerid);
            }
            case 3: // newbie spawn
            {
                SendClientMessage(playerid, X11_WHITE, ">> "TOMATO" �س�����繨ش�Դ�������!");
                Player_SetSpawn(playerid, PLAYER_SPAWN_TYPE_DEFAULT);
                SetPlayerSpawnDialog(playerid);
            }
            case 4: // current position
            {
                new 
                    Float:X, 
                    Float:Y, 
                    Float:Z, 
                    Float:A;
			    
                if(VIP_GetPlayerLevel(playerid) < 6)  
                    return SendErrorMsg(playerid, "�س�����ʶҹ� VIP �дѺ��������!");
            
			    GetPlayerPos(playerid, X, Y, Z);
			    GetPlayerFacingAngle(playerid, A);

                PlayerLastSpawnX[playerid] = X;
                PlayerLastSpawnY[playerid] = Y;
                PlayerLastSpawnZ[playerid] = Z;
                PlayerLastSpawnAng[playerid] = A;

                PlayerLastSpawnVWorld[playerid] = GetPlayerVirtualWorld(playerid);
                PlayerLastSpawnInt[playerid] = GetPlayerInterior(playerid);
            
			    SendClientMessage(playerid,X11_WHITE,">> "TOMATO" �س���駨ش�Դ����!");
                Player_SetSpawn(playerid, PLAYER_SPAWN_TYPE_POINT);
			    SetPlayerSpawnDialog(playerid);
            }
            default:
            {
                @return SetPlayerSpawnDialog(playerid);
            }
        }
    }
	return Dialog_ShowCallback(playerid, using inline Response, DIALOG_STYLE_LIST, "���͡�ش�Դ���˹觵�ҧ �", string, "��駤��", "�Դ");
}

YCMD:setspawn(playerid, params[], help)
{
	SetPlayerSpawnDialog(playerid);
	return 1;
}