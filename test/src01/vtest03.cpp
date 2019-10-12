
/** Introduction:
 The functions included are mainly to test items defined in type_traits.
 */



#include <stdio.h>
#include <iostream>
#include <typeinfo>
//#include <type_traits.h>
//#include <utility.h>

#include "MRFuncEntryMacro.h"
#include "MuRanCommonFuncs.h"


#define DEF_FUNC(X) X(int argc, char* argv[])



#define TRACE_CODE(...)     printf("%s\n",#__VA_ARGS__);         __VA_ARGS__
static  const char*                CODE_FORMAT{"%-60s==>"}; // default, must be static
#define TRACE_CODE0(...)    printf(CODE_FORMAT,  #__VA_ARGS__); __VA_ARGS__;
#define TRACE_CODEn(...)    printf(CODE_FORMAT,  #__VA_ARGS__); __VA_ARGS__;printf("\n");
#define TRACE_CODEv(...)    printf(CODE_FORMAT,  #__VA_ARGS__); std::cout << (__VA_ARGS__) << "\n";

#define ANNOTATE(...)       printf("//%s\n", #__VA_ARGS__);
#define ANNOTATE0(...)      printf("//%s",   #__VA_ARGS__);
#define ANNOTATEn(...)      printf("//%s\n", #__VA_ARGS__); // equal ANNOTATE
#define ANNOTATEe(...)      printf(CODE_FORMAT,  #__VA_ARGS__);printf(" <== compile error\n");
#define ANNOTATEw(...)      printf(CODE_FORMAT,  #__VA_ARGS__);printf(" <== warn although compile OK\n");

static const int                                      LEN_LINE = 120; // default, must be static
#define DRAW_LINE(...)      muranbase::stdout_putline(LEN_LINE, ##__VA_ARGS__);             // ONLY one parameter(fillchar) acceptable 
#define DRAW_LINEnn(...)    muranbase::stdout_putline(LEN_LINE, ##__VA_ARGS__);printf("\n");// ONLY one parameter(fillchar) acceptable
#define TITLEH1(...)        muranbase::center_stdout(#__VA_ARGS__, 4, LEN_LINE,    '=', true);
#define TITLEH2(...)        muranbase::center_stdout(#__VA_ARGS__, 4, LEN_LINE-20, '-', true);
#define TITLEH3(...)        muranbase::center_stdout(#__VA_ARGS__, 4, LEN_LINE-40, '.', true);

#ifdef _WIN32
#define vcTRACE_CODE  TRACE_CODE
#define vcTRACE_CODE0 TRACE_CODE0
#define vcTRACE_CODEn TRACE_CODEn
#define vcTRACE_CODEv TRACE_CODEv
#else
#define vcTRACE_CODE  ANNOTATEe
#define vcTRACE_CODE0 ANNOTATE0
#define vcTRACE_CODEn ANNOTATEe
#define vcTRACE_CODEv ANNOTATEe
#endif



BEGIN_SECTION(vtest03_ctor)
int DEF_FUNC(vtest03_ctor){
	TITLEH1(define some varialbes)
	TRACE_CODE0(int i = 1;)

	{
		TITLEH1(Notice, without "copy cotr" and "operator=")

		TRACE_CODE(struct C{
			C(int x)                { std::cout << "!!!contructor!!!"; };
			//(const C& o)           { std::cout << "!!!copy  ctor!!!"; };
			//C& operator=(const C& o){ std::cout << "!!!operator= !!!"; return * this; };
		} 
		);
		TRACE_CODE0(C m (5);)  ANNOTATE(constructor called for both compilers)
		TRACE_CODE0(C n = 10;) ANNOTATE(constructor called for both compilers)
		TRACE_CODE0(C x = m;)  ANNOTATE(copy   ctor called for both compilers)
		TRACE_CODE0(  x = 15;) ANNOTATE(ctor & then op=    for both compilers)
		TRACE_CODE0(  x = i;)  ANNOTATE(ctor & then op = for both compilers)
		TRACE_CODE0(  x = n;)  ANNOTATE(op=                for both compilers)
	}
	{
		TITLEH1(Notice, without "operator=")

		TRACE_CODE(struct C{
			C(int x)                { std::cout << "!!!contructor!!!"; };
			C(const C& o)           { std::cout << "!!!copy  ctor!!!"; };
			//C& operator=(const C& o){ std::cout << "!!!operator= !!!"; return * this; };
		} 
		);
		TRACE_CODE0(C m (5);)  ANNOTATE(constructor called for both compilers)
		TRACE_CODE0(C n = 10;) ANNOTATE(constructor called for both compilers)
		TRACE_CODE0(C x = m;)  ANNOTATE(copy   ctor called for both compilers)
		TRACE_CODE0(  x = 15;) ANNOTATE(ctor & then op=    for both compilers)
		TRACE_CODE0(  x = i;)  ANNOTATE(ctor & then op = for both compilers)
		TRACE_CODE0(  x = n;)  ANNOTATE(op=                for both compilers)
	}
	{
		TITLEH1(Notice, with only "operator=")

		TRACE_CODE(struct C{
			C(int x)                { std::cout << "!!!contructor!!!"; };
			C(const C& o)           { std::cout << "!!!copy  ctor!!!"; };
			C& operator=(const C& o){ std::cout << "!!!op=(T&)   !!!"; return * this; };
		} 
		);
		TRACE_CODE0(C m (5);)  ANNOTATE(constructor called for both compilers)
		TRACE_CODE0(C n = 10;) ANNOTATE(constructor called for both compilers)
		TRACE_CODE0(C x = m;)  ANNOTATE(copy   ctor called for both compilers)
		TRACE_CODE0(  x = 15;) ANNOTATE(ctor & then op=    for both compilers)
		TRACE_CODE0(  x = i;)  ANNOTATE(ctor & then op = for both compilers)
		TRACE_CODE0(  x = n;)  ANNOTATE(op=                for both compilers)
	}
	{
		TITLEH1(Notice, with both "operator=(const int)" and "operator(cont T&)")

		TRACE_CODE(struct C{
			C(int x)                  { std::cout << "!!!contructor!!!"; };
			C(const C& o)             { std::cout << "!!!copy  ctor!!!"; };
			C& operator=(const C& o)  { std::cout << "!!!op=(T&)   !!!"; return * this; };
			C& operator=(const int& o){ std::cout << "!!!op=(int&) !!!"; return * this; };
		} 
		);
		TRACE_CODE0(C m (5);)  ANNOTATE(constructor called for both compilers)
		TRACE_CODE0(C n = 10;) ANNOTATE(constructor called for both compilers)
		TRACE_CODE0(C x = m;)  ANNOTATE(copy   ctor called for both compilers)
		TRACE_CODE0(  x = 15;) ANNOTATE(op=                for both compilers)
		TRACE_CODE0(  x = i;)  ANNOTATE(ctor & then op = for both compilers)
		TRACE_CODE0(  x = n;)  ANNOTATE(op=                for both compilers)
	}

	{
		TITLEH1(Notice, with both "operator=(const int)" and "operator(cont T&)")

		TRACE_CODE(struct C{
			C(int x)                   { std::cout << "!!!contructor!!!"; };
			C(const C& o)              { std::cout << "!!!ctor(&)   !!!"; };
			C(C&&o)                    { std::cout << "!!!ctor(&&)  !!!"; };
			C& operator=(const C& o)   { std::cout << "!!!op=(T&)   !!!"; return * this; };
			C& operator=(const C&& o)  { std::cout << "!!!op=(T&&)  !!!"; return * this; };
			C& operator=(const int& o) { std::cout << "!!!op=(int&) !!!"; return * this; };
			C& operator=(const int&&o) { std::cout << "!!!op=(int&&)!!!"; return * this; };
		} 
		);
		TRACE_CODE0(C m (5);)  ANNOTATE(constructor called for both compilers)
		TRACE_CODE0(C n = 10;) ANNOTATE(constructor called for both compilers)
		TRACE_CODE0(C x = m;)  ANNOTATE(copy   ctor called for both compilers)
		TRACE_CODE0(  x = 15;) ANNOTATE(op=                for both compilers)
		TRACE_CODE0(  x = i;)  ANNOTATE(ctor & then op = for both compilers)
		TRACE_CODE0(  x = n;)  ANNOTATE(op=                for both compilers)
		TRACE_CODE0(C y = C{20};)ANNOTATE(ctor       called for both compilers)
		TRACE_CODE0(C z = C(20);)ANNOTATE(ctor       called for both compilers)
		TRACE_CODE0(  z = C(30);)ANNOTATE(ctor & op= called for both compilers)
		TITLEH3(return funcs)
		TRACE_CODE0(auto func1=[]()->C{return C(1000);};)   ANNOTATE(fine for both compilers)
      vcTRACE_CODE0(auto func2=[]()->C&{return C(2000);};)  ANNOTATE(fine for vc)
	  vcTRACE_CODE0(auto func3=[]()->C&&{return C(3000);};) ANNOTATE(fine for vc)
		TRACE_CODEn(auto  c1 = func1();)
	  vcTRACE_CODEn(auto  c2 = func2();)
	  vcTRACE_CODEn(auto  c3 = func3();)
		TRACE_CODEn(      c1 = func1();)
	  vcTRACE_CODEn(      c2 = func2();)
	  vcTRACE_CODEn(      c3 = func3();)
	}

	DRAW_LINE()
	return 0;
}
END_SECTION(vtest03_ctor)


