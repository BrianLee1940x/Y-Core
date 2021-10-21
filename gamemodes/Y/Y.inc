#if defined _inc_Y
	#undef _inc_Y
#endif

#if !defined Y_@@@@_HEADER

	#include "core\header"
	#include "logger\header"
	#include "db\header"
	#include "utils\header"

	#include "chat\header"
	#include "player\header"
	#include "ui\header"

	#include "systems\header"
	#include "RP\RP"
	#include "BLESS\BLESS"
	
	// #include "sampvoice\header"

	#define Y_@@@@_HEADER
#elseif !defined Y_@@@@_END

	#include "core\impl"
	#include "logger\impl"
	#include "db\impl"
	#include "utils\impl"

	#include "chat\impl"
	#include "player\impl"
	#include "ui\impl"

	#include "systems\impl"
	#include "RP\RP"
	#include "BLESS\BLESS"

	// #include "sampvoice\impl"

	#define Y_@@@@_END
#else
	#error y core already set up
#endif