#if defined _inc_header
	#undef _inc_header
#endif

stock bool:IsFlagged(flags, flagValue) 
{
    if ((flags & flagValue) == flagValue) 
	{
        return true;
    }
    return false;
}