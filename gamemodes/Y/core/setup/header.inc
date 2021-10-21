#if defined _inc_header
	#undef _inc_header
#endif

#include <YSI_Core\y_master>

// OO-STYLE
#define OO_TYPE(%6,%7)%0[%1] (_:@vb:@va:%6:%7@%0[%1]
#define @va:%6:%7@%0[%1][@%2] %7%0[%1])[E_%6_%0_%2]
#define @vb:@va:%6:%7@%0[%1][%2][@%3] %7%0[%1])[%2][E_%6_%0_%3]


#if !defined PRESSED
	#define PRESSED(%0) \
		(((newkeys & (%0)) == (%0)) && ((oldkeys & (%0)) != (%0)))
#endif

#if !defined PRESSING
	#define PRESSING(%0,%1) \
		(%0 & (%1))
#endif

#if !defined RELEASED
	#define RELEASED(%0) \
		(((newkeys & (%0)) != (%0)) && ((oldkeys & (%0)) == (%0)))
#endif

enum
{
	BOT_STREAMER_IDENTIFIER = 100,
	ENEX_STREAMER_IDENTIFIER
}