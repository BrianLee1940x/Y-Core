#if defined _inc_impl
	#undef _inc_impl
#endif

#include <YSI_Coding\y_hooks>

/*
	ǹ����������������ء�Թҷ�

	�Ը���:
	hook OnServerSecondUpdate()
	{
		printf("server timer is running");
	}
*/
static task _ServerSecondTimer[1000]() 
{
    CallRemoteFunction("OnServerSecondUpdate", "");
}