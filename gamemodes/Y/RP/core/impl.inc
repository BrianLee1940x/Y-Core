#if defined _inc_impl
	#undef _inc_impl
#endif

#include <YSI_Coding\y_hooks>

/*
	วนซ้ำเวลาเซิร์ฟเวอร์ทุกวินาที

	วิธีใช้:
	hook OnServerSecondUpdate()
	{
		printf("server timer is running");
	}
*/
static task _ServerSecondTimer[1000]() 
{
    CallRemoteFunction("OnServerSecondUpdate", "");
}