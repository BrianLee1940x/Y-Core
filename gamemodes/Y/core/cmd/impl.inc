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
		SendSpecialMsg(playerid, X11_INDIANRED, "ACCESS DENIED", "�س��ͧ�������к���͹����������");
		return COMMAND_DENIED;
    }
	#endif

    switch(success) 
	{
    	case COMMAND_DENIED: 
		{
			SendSpecialMsg(playerid, X11_INDIANRED, "ACCESS DENIED", "�س������Ѻ͹حҵ��������觹��");
    		return COMMAND_DENIED;
    	}
    	case COMMAND_UNDEFINED:
    	{
			if (strlen(cmdtext) > 28) // Preventing long bad commands from returning default message;
				SendErrorMsg(playerid, "����觹����������� �� /help ��Ҥس��ͧ��ä������������"); 	
			else
				SendErrorMsgF(playerid, "����� \"%s\" ��������� �� /help ��Ҥس��ͧ��ä������������", cmdtext);

    		return COMMAND_OK;
    	}
    }
    return success;
}