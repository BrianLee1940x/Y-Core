#if defined _inc_header
	#undef _inc_header
#endif

#include <YSI_Players\y_groups>

#define Y_PLAYER_ADMIN_MAX_LEVEL		5
#define Y_PLAYER_ADMIN_MANAGE_LEVEL     4
#define Y_PLAYER_ADMIN_LEAD_LEVEL       3
#define Y_PLAYER_ADMIN_STAFF_LEVEL      2
#define Y_PLAYER_ADMIN_STOCK_LEVEL      1

#define MAX_BAN_REASON                  32
#define PLAYER_ADMIN_TABLE				"admins"

new
	Group:DeveloperGroup,
	Group:AdminGroup[Y_PLAYER_ADMIN_MAX_LEVEL];

#define Admin_IsPlayerDev(%0) Group_GetPlayer(DeveloperGroup, %0)
