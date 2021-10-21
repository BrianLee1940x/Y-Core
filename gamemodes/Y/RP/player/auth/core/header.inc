#if defined _inc_header
	#undef _inc_header
#endif

#include <YSI_Players\y_groups>
#include <YSI_Coding\y_timers>

new
	Group:LoggedGroup;

#define Player_IsLoggedIn(%0) Group_GetPlayer(LoggedGroup, %0)