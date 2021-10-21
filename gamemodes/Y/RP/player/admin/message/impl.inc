#if defined _inc_impl
	#undef _inc_impl
#endif

stock SendAdminMsg(e_ADMIN_MSGS:type, level, const msg[]) 
{
	if (level < 1 || level > Y_PLAYER_ADMIN_MAX_LEVEL) 
	{
		Logger_Err("invalid admin level", 
            Logger_I("level", level)
        );
		return;
	}

	new
		out[144],
        color = X11_YELLOW1;

    switch (type) 
	{
		case e_ADMIN_MSG_INFO: 
		{
			color = X11_YELLOW2;
			format(out, sizeof out, "AdmLog: %s", msg);
		}
		case e_ADMIN_MSG_WARNING: 
		{
			color = X11_GOLDENROD;
			format(out, sizeof out, "AdmWarning: %s", msg);
		}
		default:
		{
			strcpy(out, msg);
		}
	}

    foreach(new i:GroupMember(AdminGroup[level - 1]))
	{
        SendClientMessage(i, color, out);
	}
    return;
}

stock SendAdminMsgF(e_ADMIN_MSGS:type, level, const fmat[],  va_args<>)
{
	if (level < 1 || level > Y_PLAYER_ADMIN_MAX_LEVEL) 
	{
		Logger_Err("invalid admin level", 
            Logger_I("level", level)
        );
		return;
	}

	new
		out[144];

	va_format(out, sizeof (out), fmat, va_start<3>);

    SendAdminMsg(type, level, out);
	return;
}