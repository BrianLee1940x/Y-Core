#if defined _inc_BLESS
	#undef _inc_BLESS
#endif

#if !defined Y_BLESS_HEADER

	#include "core\header"
	//#include "inventory\header"
	//#include "jobs\header"

	#define Y_BLESS_HEADER
#elseif !defined Y_BLESS_END

	#include "core\impl"
	//#include "inventory\impl"
	//#include "jobs\impl"

	#define Y_BLESS_END
#else
	#error Y bless already set up
#endif