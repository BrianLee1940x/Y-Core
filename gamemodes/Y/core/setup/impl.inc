#if defined _inc_impl
	#undef _inc_impl
#endif

public OnGameModeInit()
{
	SendRconCommand("hostname "#SERVER_NAME " v" #SCRIPT_VERSION_MAJOR "." #SCRIPT_VERSION_MINOR "." #SCRIPT_VERSION_PATCH);
	SendRconCommand("gamemodetext "SERVER_MODE"");
	SendRconCommand("language "SERVER_LANGUAGE"");
	SendRconCommand("weburl "SERVER_WEBSITE"");

   	SetWeather(0);
	ManualVehicleEngineAndLights();
	DisableInteriorEnterExits();
	EnableStuntBonusForAll(0);
    return 1;
}