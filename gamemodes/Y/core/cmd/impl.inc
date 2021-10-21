#if defined _inc_impl
	#undef _inc_impl
#endif

#include <YSI_Coding\y_hooks>

timer onAllInitiated[100]()
{
	CallLocalFunction("OnGroupInit", "");
}

hook OnGameModeInit() 
{
	Command_SetDeniedReturn(true);
	defer onAllInitiated();
}

public e_COMMAND_ERRORS:OnPlayerCommandReceived(playerid, cmdtext[], e_COMMAND_ERRORS:success) 
{
	#if defined RP_PLAYER_MODULES
    if (!Player_IsLoggedIn(playerid))
    {
		SendSpecialMsg(playerid, X11_INDIANRED, "ACCESS DENIED", "คุณต้องเข้าสู่ระบบก่อนที่จะใช้คำสั่ง");
		return COMMAND_DENIED;
    }
	#endif

    switch(success) 
	{
    	case COMMAND_DENIED: 
		{
			SendSpecialMsg(playerid, X11_INDIANRED, "ACCESS DENIED", "คุณไม่ได้รับอนุญาตให้ใช้คำสั่งนี้");
    		return COMMAND_DENIED;
    	}
    	case COMMAND_UNDEFINED:
    	{
			if (strlen(cmdtext) > 28) // Preventing long bad commands from returning default message;
				SendErrorMsg(playerid, "คำสั่งนี้ไม่มีอยู่ ใช้ /help ถ้าคุณต้องการความช่วยเหลือ"); 	
			else
				SendErrorMsgF(playerid, "คำสั่ง \"%s\" ไม่มีอยู่ ใช้ /help ถ้าคุณต้องการความช่วยเหลือ", cmdtext);

    		return COMMAND_OK;
    	}
    }
    return success;
}