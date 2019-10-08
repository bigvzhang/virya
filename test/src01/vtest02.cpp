
/** Introduction:
 The functions included are mainly to test items defined in type_traits.
 */



#include <stdio.h>
#include <iostream>
#include <typeinfo>
//#include <type_info.h>

#include "MRFuncEntryMacro.h"
#include "MuRanCommonFuncs.h"


#define DEF_FUNC(X) X(int argc, char* argv[])



#define TRACE_CODE(...)     printf("%s\n",#__VA_ARGS__);         __VA_ARGS__
static  const char*                CODE_FORMAT{"%-60s==>"}; // default, must be static
#define TRACE_CODE0(...)    printf(CODE_FORMAT,  #__VA_ARGS__); __VA_ARGS__
#define TRACE_CODEn(...)    printf(CODE_FORMAT,  #__VA_ARGS__); __VA_ARGS__;printf("\n")
#define TRACE_CODEv(...)    printf(CODE_FORMAT,  #__VA_ARGS__); std::cout << (__VA_ARGS__) << "\n";

#define ANNOTATE(...)       printf("//%s\n", #__VA_ARGS__);
#define ANNOTATE0(...)      printf("//%s",   #__VA_ARGS__);
#define ANNOTATEn(...)      printf("//%s\n", #__VA_ARGS__); // equal ANNOTATE

static const int                                      LEN_LINE = 120; // default, must be static
#define DRAW_LINE(...)      muranbase::stdout_putline(LEN_LINE, ##__VA_ARGS__);             // ONLY one parameter(fillchar) acceptable 
#define DRAW_LINEnn(...)    muranbase::stdout_putline(LEN_LINE, ##__VA_ARGS__);printf("\n");// ONLY one parameter(fillchar) acceptable
#define TITLEH1(...)        muranbase::center_stdout(#__VA_ARGS__, 4, LEN_LINE,    '=', true);
#define TITLEH2(...)        muranbase::center_stdout(#__VA_ARGS__, 4, LEN_LINE-20, '-', true);
#define TITLEH3(...)        muranbase::center_stdout(#__VA_ARGS__, 4, LEN_LINE-40, '.', true);



BEGIN_SECTION(vtest02_typeinfo)
//namespace vya=virya;

int DEF_FUNC(vtest02_typeinfo){
 
	std::cout << std::boolalpha;
	
	
	TRACE_CODE(int i = 5;);
	TRACE_CODE(int *j = &i);
	TRACE_CODEv(typeid(i).name()); 
	TRACE_CODEv(typeid(j).name()); 
	TRACE_CODEv(typeid(5).name()); 
	TRACE_CODEv(typeid("5").name()); 
	TRACE_CODEv(typeid(5).name()); 
	TRACE_CODEv(typeid(0.5).name()); 
 

	return 0;
}
END_SECTION(vtest02_typeinfo)
