#if defined _inc_impl
	#undef _inc_impl
#endif

stock ShiftCoords(style, &Float:x, &Float:y, Float:a, Float:distance)
{
	switch(style)
	{
		case 0:
		{
			x += (distance * floatsin(-a, degrees));
			y += (distance * floatcos(-a, degrees));
		}
		case 1:
		{
			x -= (distance * floatsin(-a, degrees));
			y -= (distance * floatcos(-a, degrees));
		}
		default: return false;
	}
	return true;
}