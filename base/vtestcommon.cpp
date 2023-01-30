/**
RESEARCH - {dftarg.use.staticvar}{[default argument][use][static variable]}
	1. Default argument use static variable
	2. Default argument use global variable
CONCLUSION
	if use static varialbe, there will be problem whatever the function is:
	  - normal function
	  - inline function
	  - template function
	  - template inline function
*/
const char*                CODE_FORMAT {"++ %-70s"};       // default, must be static
const char*                CODE_FORMAT_{"++ %-70s -> "};   // default, must be static
const char*                CODE_FORMATv{"@@ %-70s == "};   // default, must be static
const char*                CODE_FORMATw{"!! %-70s"};       // default, must be static

#include "vtestcommon.h"
BoolWhistle BoolWhistle::INSTANCE;
Whistle Whistle::INSTANCE;
