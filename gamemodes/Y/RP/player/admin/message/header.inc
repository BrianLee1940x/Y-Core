#if defined _inc_header
	#undef _inc_header
#endif

#include <YSI_Coding\y_va>
#include <YSI_Players\y_groups>
#include <YSI_Data\y_iterate>
#include <YSI_Core\y_utils>

#define	Y_PLAYER_ADMIN_DUTY_COLOR Y_ORANGE

enum e_ADMIN_MSGS 
{
	e_ADMIN_MSG_NONE,
	e_ADMIN_MSG_INFO,
	e_ADMIN_MSG_WARNING
}