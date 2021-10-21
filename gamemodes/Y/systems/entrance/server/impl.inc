#if defined _inc_impl
	#undef _inc_impl
#endif

#include <YSI_Coding\y_hooks>

enum E_ENTRANCE_DATA {
    E_STORE_NAME[MAX_STORE_NAME],
    Float:E_ENTRANCE_POS_X,
    Float:E_ENTRANCE_POS_Y,
    Float:E_ENTRANCE_POS_Z,
    Float:E_ENTRANCE_POS_A,
    E_WORLD_ID,
    E_INTERIOR_ID,
    Float:E_EXIT_POS_X,
    Float:E_EXIT_POS_Y,
    Float:E_EXIT_POS_Z,
    Float:E_EXIT_POS_A,
    E_EXIT_WORLD_ID,
    E_EXIT_INTERIOR_ID,
    E_MAP_ICON,
    bool:E_FREEZE_PLAYER
}

static
    const entranceData[][E_ENTRANCE_DATA] =
{
    // ชื่อทางเข้า, ทางเข้า X, Y, Z, A, WORLD, INT, ทางออก X, Y, Z, A, WORLD, INT, MAP ICON, แช่แข็งเมื่อเข้า-ออก
	{"Test", 0.0, 0.0, 0.0, 0.0, 0, 0, 0.0, 0.0, 0.0, 0.0, 0, 0, 30, true}
};

hook OnGameModeInit() {

    // Init Entrances
    new
        entID,
        Float:enX,
        Float:enY,
        Float:enZ,
        Float:enA,
        enIntID,
        enWorldID,
        Float:exX,
        Float:exY,
        Float:exZ,
        Float:exA,
        exIntID,
        exWorldID,
        labelMessage[40 + MAX_STORE_NAME];

    for(new i = 0; i < sizeof(entranceData); i++) {

        enX = entranceData[i][E_ENTRANCE_POS_X];
        enY = entranceData[i][E_ENTRANCE_POS_Y];
        enZ = entranceData[i][E_ENTRANCE_POS_Z];
        enA = entranceData[i][E_ENTRANCE_POS_A];
        enIntID = entranceData[i][E_INTERIOR_ID];
        enWorldID = entranceData[i][E_WORLD_ID];
        exX = entranceData[i][E_EXIT_POS_X];
        exY = entranceData[i][E_EXIT_POS_Y];
        exZ = entranceData[i][E_EXIT_POS_Z];
        exA = entranceData[i][E_EXIT_POS_A];
        exIntID = entranceData[i][E_EXIT_INTERIOR_ID];
        exWorldID = entranceData[i][E_EXIT_WORLD_ID];

        // create entrance
        entID = Entrance_Create(enX, enY, enZ, enA, enWorldID, enIntID, exX, exY, exZ, exA, exWorldID, exIntID);

        if (entranceData[i][E_MAP_ICON] != 0 && enWorldID == 0 && enIntID == 0)
        {
            Entrance_SetIcon(entID, entranceData[i][E_MAP_ICON]);
        }

        if (!isnull(entranceData[i][E_STORE_NAME]))
        {
            Entrance_SetName(entID, entranceData[i][E_STORE_NAME]);
        }

        Entrance_EnableFreeze(entID, entranceData[i][E_FREEZE_PLAYER]);

        format(labelMessage, sizeof(labelMessage), "%s\n\n"WHITE"เดินชนลูกศรเพื่อเข้า/ออก", entranceData[i][E_STORE_NAME]);
        Entrance_SetLabel(entID, labelMessage);

        // create exit
        entID = Entrance_Create(exX, exY, exZ, exA, exWorldID, exIntID, enX, enY, enZ, enA, enWorldID, enIntID);
        Entrance_EnableFreeze(entID, entranceData[i][E_FREEZE_PLAYER]);

        if (enWorldID == 0 && enIntID == 0)
        {
            if (strfind(entranceData[i][E_STORE_NAME], "ชั้น", true) == -1)
            {
                Entrance_SetLabel(entID, "ออกไปข้างนอก");
            }
        }
    }
    return 1;
}