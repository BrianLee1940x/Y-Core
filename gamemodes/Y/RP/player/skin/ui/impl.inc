#if defined _inc_impl
	#undef _inc_impl
#endif

hook OnGameModeInit()
{
	SkinSelection_Menu0 = TextDrawCreate(439.000000, 383.000000, "box1");
	TextDrawBackgroundColor(SkinSelection_Menu0, 255);
	TextDrawFont(SkinSelection_Menu0, 1);
	TextDrawLetterSize(SkinSelection_Menu0, 0.000000, 3.400001);
	TextDrawUseBox(SkinSelection_Menu0, 1);
	TextDrawBoxColor(SkinSelection_Menu0, 80);
	TextDrawTextSize(SkinSelection_Menu0, 206.000000, 10.000000);
	TextDrawSetSelectable(SkinSelection_Menu0, 0);

	SkinSelection_Menu1 = TextDrawCreate(387.000000, 358.000000, "box2");
	TextDrawBackgroundColor(SkinSelection_Menu1, 255);
	TextDrawFont(SkinSelection_Menu1, 1);
	TextDrawLetterSize(SkinSelection_Menu1, 0.000000, 2.000000);
	TextDrawUseBox(SkinSelection_Menu1, 1);
	TextDrawBoxColor(SkinSelection_Menu1, 2132351487);
	TextDrawTextSize(SkinSelection_Menu1, 258.000000, 10.000000);
	TextDrawSetSelectable(SkinSelection_Menu1, 0);

	SkinSelection_Menu2 = TextDrawCreate(385.000000, 360.000000, "box3");
	TextDrawBackgroundColor(SkinSelection_Menu2, 255);
	TextDrawFont(SkinSelection_Menu2, 1);
	TextDrawLetterSize(SkinSelection_Menu2, 0.000000, 1.600000);
	TextDrawUseBox(SkinSelection_Menu2, 1);
	TextDrawBoxColor(SkinSelection_Menu2, 128);
	TextDrawTextSize(SkinSelection_Menu2, 260.000000, 10.000000);
	TextDrawSetSelectable(SkinSelection_Menu2, 0);

	SkinSelection_Menu3 = TextDrawCreate(268.000000, 361.000000, "Select Action");
	TextDrawBackgroundColor(SkinSelection_Menu3, 255);
	TextDrawFont(SkinSelection_Menu3, 2);
	TextDrawLetterSize(SkinSelection_Menu3, 0.349999, 1.200000);
	TextDrawColor(SkinSelection_Menu3, -1);
	TextDrawSetOutline(SkinSelection_Menu3, 0);
	TextDrawSetProportional(SkinSelection_Menu3, 1);
	TextDrawSetShadow(SkinSelection_Menu3, 1);
	TextDrawSetSelectable(SkinSelection_Menu3, 0);

	SkinSelection_BtnLeft = TextDrawCreate(176.000000, 345.000000, "selecticon1");
	TextDrawBackgroundColor(SkinSelection_BtnLeft, 0);
	TextDrawFont(SkinSelection_BtnLeft, 5);
	TextDrawLetterSize(SkinSelection_BtnLeft, 0.500000, 1.000000);
	TextDrawColor(SkinSelection_BtnLeft, 0xFF6347FF);
	TextDrawTextSize(SkinSelection_BtnLeft, 73.000000, 65.000000);
	TextDrawSetPreviewModel(SkinSelection_BtnLeft, 19132);
	TextDrawSetPreviewRot(SkinSelection_BtnLeft, -40.000000, -90.000000, 90.000000, 1.000000);
	TextDrawSetSelectable(SkinSelection_BtnLeft, 1);
	
	SkinSelection_BtnRight = TextDrawCreate(396.000000, 345.000000, "selecticon2");
	TextDrawBackgroundColor(SkinSelection_BtnRight, 0);
	TextDrawFont(SkinSelection_BtnRight, 5);
	TextDrawLetterSize(SkinSelection_BtnRight, 0.500000, 1.000000);
	TextDrawColor(SkinSelection_BtnRight, -1876547841);
	TextDrawTextSize(SkinSelection_BtnRight, 73.000000, 65.000000);
	TextDrawSetPreviewModel(SkinSelection_BtnRight, 19132);
	TextDrawSetPreviewRot(SkinSelection_BtnRight, -40.000000, 90.000000, 90.000000, 1.000000);
	TextDrawSetSelectable(SkinSelection_BtnRight, 1);

	SkinSelection_BoxCancel = TextDrawCreate(327.000000, 367.000000, "selecticon3");
	TextDrawBackgroundColor(SkinSelection_BoxCancel, 0);
	TextDrawFont(SkinSelection_BoxCancel, 5);
	TextDrawLetterSize(SkinSelection_BoxCancel, 0.500000, 1.000000);
	TextDrawColor(SkinSelection_BoxCancel, -1876547841);
	TextDrawSetProportional(SkinSelection_BoxCancel, 1);
	TextDrawTextSize(SkinSelection_BoxCancel, 84.000000, 63.000000);
	TextDrawSetPreviewModel(SkinSelection_BoxCancel, 19447);
	TextDrawSetPreviewRot(SkinSelection_BoxCancel, -20.000000, 0.000000, 90.000000, 1.000000);
	TextDrawSetSelectable(SkinSelection_BoxCancel, 1);

	SkinSelection_BtnCancel = TextDrawCreate(342.000000, 392.000000, "Cancel");
	TextDrawBackgroundColor(SkinSelection_BtnCancel, 255);
	TextDrawFont(SkinSelection_BtnCancel, 2);
	TextDrawLetterSize(SkinSelection_BtnCancel, 0.350000, 1.200000);
	TextDrawColor(SkinSelection_BtnCancel, -1);
	TextDrawSetProportional(SkinSelection_BtnCancel, 1);
	TextDrawSetSelectable(SkinSelection_BtnCancel, 0);


	SkinSelection_BoxAccept = TextDrawCreate(233.000000, 367.000000, "selecticon3");
	TextDrawBackgroundColor(SkinSelection_BoxAccept, 0);
	TextDrawFont(SkinSelection_BoxAccept, 5);
	TextDrawLetterSize(SkinSelection_BoxAccept, 0.500000, 1.000000);
	TextDrawColor(SkinSelection_BoxAccept, -1876547841);
	TextDrawTextSize(SkinSelection_BoxAccept, 84.000000, 63.000000);
	TextDrawSetPreviewModel(SkinSelection_BoxAccept, 19447);
	TextDrawSetPreviewRot(SkinSelection_BoxAccept, -20.000000, 0.000000, 90.000000, 1.000000);
	TextDrawSetSelectable(SkinSelection_BoxAccept, 1);
	
	SkinSelection_BtnSelect = TextDrawCreate(247.000000, 392.000000, "Accept");
	TextDrawBackgroundColor(SkinSelection_BtnSelect, 255);
	TextDrawFont(SkinSelection_BtnSelect, 2);
	TextDrawLetterSize(SkinSelection_BtnSelect, 0.350000, 1.200000);
	TextDrawColor(SkinSelection_BtnSelect, -1);
	TextDrawSetProportional(SkinSelection_BtnSelect, 1);
	TextDrawSetSelectable(SkinSelection_BtnSelect, 0);

}