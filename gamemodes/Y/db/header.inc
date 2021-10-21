#if defined _inc_header
	#undef _inc_header
#endif

#include <a_mysql>

#include <YSI_Coding\y_inline>
#include <YSI_Extra\y_inline_mysql>
#include <mysql_prepared>

#define INVALID_DB_ID DBID:0

static 
    stock DBID:__DBID__;

new
    MySQL:gMySQLHandle;

stock MySQL:Database_GetHandle() {
    return gMySQLHandle;
}