#if defined _inc_impl
	#undef _inc_impl
#endif

#include <YSI_Coding\y_hooks>

enum E_DATA_LIST
{
    E_DATA_LIST_NEXT,
	E_DATA_LIST_LAST,
	bool:E_DATA_LIST_DATA
}

static
	PlayerText:UI_NotifyTextdraw[MAX_PLAYERS][UI_NOTIFY_LIMIT],
	UI_NotifyText[MAX_PLAYERS][UI_NOTIFY_LIMIT][UI_NOTIFY_TEXT_LIMIT],
	UI_NotifyListData[MAX_PLAYERS][UI_NOTIFY_LIMIT][E_DATA_LIST],
	UI_NotifyDelete[MAX_PLAYERS][UI_NOTIFY_LIMIT],
	Float:UI_NotifyAlpha[MAX_PLAYERS][UI_NOTIFY_LIMIT],
	Timer:UI_NotifyTimer[MAX_PLAYERS][UI_NOTIFY_LIMIT],
	UI_NotifyListLast[MAX_PLAYERS],
	UI_NotifyListFirst[MAX_PLAYERS],
	gsFreeSlot = 0;

timer DelayRefresh[100](playerid)
{
	_Notify_Refresh(playerid);
}

hook OnPlayerConnect(playerid)
{
	UI_NotifyListFirst[playerid] = -1;
	UI_NotifyListLast[playerid] = -1;

	for(new i = 0; i != UI_NOTIFY_LIMIT; i++)
	{
		UI_NotifyTextdraw[playerid][i] = PlayerText:INVALID_TEXT_DRAW;
	}
	return 1;
}

stock Notify_PushText(playerid, const text[], time = 8)
{
	new slot = List_Add(playerid, text);
	UI_NotifyDelete[playerid][slot] = time;
	UI_NotifyAlpha[playerid][slot] = 100.0;
	_Notify_Refresh(playerid);
}

static stock void:_Notify_Refresh(playerid)
{
	new 
		pointer = UI_NotifyListLast[playerid],
		i = pointer,
		count = 0;

	for(new x = 0; x != UI_NOTIFY_LIMIT; x++)
	{
		PlayerTextDrawDestroy(playerid, UI_NotifyTextdraw[playerid][x]);
		UI_NotifyTextdraw[playerid][x] = PlayerText:INVALID_TEXT_DRAW;
	}

	while(pointer != -1)
	{

		if (!isnull(UI_NotifyText[playerid][i]) && count < 5)
		{
			UI_NotifyTextdraw[playerid][i] = CreatePlayerTextDraw(playerid, 450.000000, 198.000000 + (count * 16.0), UI_NotifyText[playerid][i]);
			PlayerTextDrawFont(playerid, UI_NotifyTextdraw[playerid][i], 1);
			PlayerTextDrawLetterSize(playerid, UI_NotifyTextdraw[playerid][i], 0.300000, 1.200000);
			PlayerTextDrawTextSize(playerid, UI_NotifyTextdraw[playerid][i], 626.000000, 17.000000);
			PlayerTextDrawSetOutline(playerid, UI_NotifyTextdraw[playerid][i], 1);
			PlayerTextDrawSetShadow(playerid, UI_NotifyTextdraw[playerid][i], 0);
			PlayerTextDrawAlignment(playerid, UI_NotifyTextdraw[playerid][i], 1);
			PlayerTextDrawColor(playerid, UI_NotifyTextdraw[playerid][i], (255<<24 | 255<<16 | 255<<8 | floatround(255.0 * UI_NotifyAlpha[playerid][i] / 100.0)));
			PlayerTextDrawBackgroundColor(playerid, UI_NotifyTextdraw[playerid][i], (0<<24 | 0<<16 | 0<<8 | floatround(255.0 * UI_NotifyAlpha[playerid][i] / 100.0)));
			PlayerTextDrawBoxColor(playerid, UI_NotifyTextdraw[playerid][i], (0<<24 | 0<<16 | 0<<8 | floatround(50.0 * UI_NotifyAlpha[playerid][i] / 100.0)));
			PlayerTextDrawUseBox(playerid, UI_NotifyTextdraw[playerid][i], 1);
			PlayerTextDrawSetProportional(playerid, UI_NotifyTextdraw[playerid][i], 1);
			PlayerTextDrawSetSelectable(playerid, UI_NotifyTextdraw[playerid][i], 0);
			PlayerTextDrawShow(playerid, UI_NotifyTextdraw[playerid][i]);
		}

		count++;

		pointer = UI_NotifyListData[playerid][pointer][E_DATA_LIST_LAST];
		i = pointer;
	}
}

static stock List_Add(playerid, const value[])
{
	if (gsFreeSlot == -1)
	{
		new 
			tempFirst = UI_NotifyListFirst[playerid],
			tempLast = UI_NotifyListLast[playerid];

		UI_NotifyListFirst[playerid] = UI_NotifyListData[playerid][tempFirst][E_DATA_LIST_NEXT];
		UI_NotifyListData[playerid][UI_NotifyListFirst[playerid]][E_DATA_LIST_LAST] = -1;

		UI_NotifyListData[playerid][tempLast][E_DATA_LIST_NEXT] = tempFirst;

		UI_NotifyText[playerid][tempFirst][0] = '\0';
		strcpy(UI_NotifyText[playerid][tempFirst], value);

		UI_NotifyListData[playerid][tempFirst][E_DATA_LIST_LAST] = tempLast; // ต่อหลังสุด
		UI_NotifyListData[playerid][tempFirst][E_DATA_LIST_NEXT] = -1;

		UI_NotifyListLast[playerid] = tempFirst;

		return UI_NotifyListLast[playerid];
	}

	new 
		slot = gsFreeSlot;
	
	if (UI_NotifyListFirst[playerid] == -1) // ไม่มีข้อมูลเลย
	{
		UI_NotifyText[playerid][slot][0] = '\0';
		strcpy(UI_NotifyText[playerid][slot], value);

		UI_NotifyListData[playerid][slot][E_DATA_LIST_NEXT] = -1;
		UI_NotifyListData[playerid][slot][E_DATA_LIST_LAST] = -1;
		UI_NotifyListData[playerid][slot][E_DATA_LIST_DATA] = true;
		
		UI_NotifyListFirst[playerid] = slot;
		UI_NotifyListLast[playerid] = slot;
	}
	else
	{
		// ต่อท้าย
		UI_NotifyListData[playerid][UI_NotifyListLast[playerid]][E_DATA_LIST_NEXT] = slot;

		UI_NotifyText[playerid][slot][0] = '\0';
		strcpy(UI_NotifyText[playerid][slot], value);

		UI_NotifyListData[playerid][slot][E_DATA_LIST_LAST] = UI_NotifyListLast[playerid];
		UI_NotifyListData[playerid][slot][E_DATA_LIST_NEXT] = -1;
		UI_NotifyListData[playerid][slot][E_DATA_LIST_DATA] = true;
      	UI_NotifyListLast[playerid] = slot;
	}

	gsFreeSlot = -1;

	new i = 0;
	while(i < UI_NOTIFY_LIMIT)
	{
		if (UI_NotifyListData[playerid][i][E_DATA_LIST_DATA] == false)
		{
			gsFreeSlot = i;
			break;
		}
		i++;
	}

	return UI_NotifyListLast[playerid];
}

static stock List_Pop(playerid)
{
	if (UI_NotifyListFirst[playerid] == -1)
		return -1;

	new 
		tempFirst = UI_NotifyListFirst[playerid];

	UI_NotifyText[playerid][tempFirst][0] = '\0';

	UI_NotifyListFirst[playerid] = UI_NotifyListData[playerid][tempFirst][E_DATA_LIST_NEXT];
	if (UI_NotifyListFirst[playerid] != -1)
		UI_NotifyListData[playerid][UI_NotifyListFirst[playerid]][E_DATA_LIST_LAST] = -1;

	UI_NotifyListData[playerid][tempFirst][E_DATA_LIST_NEXT] = -1;
	UI_NotifyListData[playerid][tempFirst][E_DATA_LIST_LAST] = -1;
	UI_NotifyListData[playerid][tempFirst][E_DATA_LIST_DATA] = false;

	gsFreeSlot = tempFirst;
	
	return tempFirst;
}


timer _NotifyFade[200](playerid, i)
{
	UI_NotifyAlpha[playerid][i] -= 15.0;

	if (UI_NotifyAlpha[playerid][i] < 0.0)
	{
		UI_NotifyAlpha[playerid][i] = 0.1;
		stop UI_NotifyTimer[playerid][i];
	}

	PlayerTextDrawColor(playerid, UI_NotifyTextdraw[playerid][i], (255<<24 | 255<<16 | 255<<8 | floatround(255.0 * UI_NotifyAlpha[playerid][i] / 100.0)));
	PlayerTextDrawBackgroundColor(playerid, UI_NotifyTextdraw[playerid][i], (0<<24 | 0<<16 | 0<<8 | floatround(255.0 * UI_NotifyAlpha[playerid][i] / 100.0)));
	PlayerTextDrawBoxColor(playerid, UI_NotifyTextdraw[playerid][i], (0<<24 | 0<<16 | 0<<8 | floatround(50.0 * UI_NotifyAlpha[playerid][i] / 100.0)));
	PlayerTextDrawShow(playerid, UI_NotifyTextdraw[playerid][i]);
}

ptask _NotifyHide[1000](playerid)
{
	for(new i = 0; i != UI_NOTIFY_LIMIT; i++)
	{
		if (UI_NotifyDelete[playerid][i] > 0)
		{
			UI_NotifyDelete[playerid][i]--;
			if (UI_NotifyDelete[playerid][i] == 4)
			{
				stop UI_NotifyTimer[playerid][i];
				UI_NotifyAlpha[playerid][i] = 100.0;
				UI_NotifyTimer[playerid][i] = repeat _NotifyFade(playerid, i);
			}
			if (UI_NotifyDelete[playerid][i] == 1)
			{
				new slot = List_Pop(playerid);

				if(slot != -1)
				{
					PlayerTextDrawDestroy(playerid, UI_NotifyTextdraw[playerid][slot]);
					UI_NotifyTextdraw[playerid][slot] = PlayerText:INVALID_TEXT_DRAW;
				}
	
				defer DelayRefresh(playerid);
			}
		}
	}
}

#if defined DEBUG_MODE
	hook OnGameModeInit()
	{
		new playerid = 0;

		UI_NotifyListFirst[playerid] = -1;
		UI_NotifyListLast[playerid] = -1;

		new
			pointer = -1;
		
		List_Add(playerid, "Text1");
		List_Add(playerid, "Text2");
		List_Add(playerid, "Text3");
		List_Add(playerid, "Text4");
		List_Add(playerid, "Text6");
		List_Add(playerid, "Text7");
		List_Add(playerid, "Text8");

		pointer = UI_NotifyListLast[playerid];

		printf("Notify Test: 8 Add");

		while(pointer != -1)
		{
			printf("pointer %d, value %s", pointer, UI_NotifyText[playerid][pointer]);
			pointer = UI_NotifyListData[playerid][pointer][E_DATA_LIST_LAST];
		}

		List_Pop(playerid);
		List_Pop(playerid);

		printf("======================================================");
		pointer = UI_NotifyListLast[playerid];

		printf("Notify Test: 2 Pop");

		while(pointer != -1)
		{
			printf("pointer %d, value %s", pointer, UI_NotifyText[playerid][pointer]);
			pointer = UI_NotifyListData[playerid][pointer][E_DATA_LIST_LAST];
		}

		printf("======================================================");

		List_Add(playerid, "1");
		List_Pop(playerid);
		List_Add(playerid, "2");

		pointer = UI_NotifyListLast[playerid];

		printf("Notify Test: Add, Pop, Add");

		while(pointer != -1)
		{
			printf("pointer %d, value %s", pointer, UI_NotifyText[playerid][pointer]);
			pointer = UI_NotifyListData[playerid][pointer][E_DATA_LIST_LAST];
		}


		printf("======================================================");

		List_Pop(playerid);
		List_Pop(playerid);
		List_Pop(playerid);
		List_Pop(playerid);
		List_Pop(playerid);
		List_Add(playerid, "Text1");
		List_Add(playerid, "Text2");
		List_Add(playerid, "Text3");
		List_Add(playerid, "Text4");
		List_Add(playerid, "Text6");
		List_Add(playerid, "Text7");
		List_Add(playerid, "Text8");

		pointer = UI_NotifyListLast[playerid];

		printf("Notify Test: Mass pop and Add");

		while(pointer != -1)
		{
			printf("pointer %d, value %s", pointer, UI_NotifyText[playerid][pointer]);
			pointer = UI_NotifyListData[playerid][pointer][E_DATA_LIST_LAST];
		}
	}
#endif