/** 
NOTICE:
 */


#include <stdio.h>
#include <iostream>
#include <typeinfo>

#include "vtestcommon.h"
#define TOUR_GROUP tour20003_

#ifdef _WIN32
#define vcTRACE_CODE  TRACE_CODE
#define vcTRACE_CODE_ TRACE_CODE_
#define vcTRACE_CODEn TRACE_CODEn
#define vcTRACE_CODEv TRACE_CODEv
#else
#define vcTRACE_CODE  ANNOTATEe
#define vcTRACE_CODE_ ANNOTATE0
#define vcTRACE_CODEn ANNOTATEe
#define vcTRACE_CODEv ANNOTATEe
#endif


BEGIN_UNIT_(constructor)
int main(int argc, char* argv[]){
	HEAD1(define some varialbes)
	TRACE_CODE(int i = 1;)

	{
		HEAD1(Notice, without "copy cotr" and "operator=")

		TRACE_CODE(struct C{
			C(int x)                { std::cout << "!!!contructor!!!"; };
			//(const C& o)           { std::cout << "!!!copy  ctor!!!"; };
			//C& operator=(const C& o){ std::cout << "!!!operator= !!!"; return * this; };
		} 
		);
		TRACE_CODE_(C m (5);)  ANNOTATE(constructor called for both compilers)
		TRACE_CODE_(C n = 10;) ANNOTATE(constructor called for both compilers)
		TRACE_CODE_(C x = m;)  ANNOTATE(copy   ctor called for both compilers)
		TRACE_CODE_(  x = 15;) ANNOTATE(ctor & then op=    for both compilers)
		TRACE_CODE_(  x = i;)  ANNOTATE(ctor & then op = for both compilers)
		TRACE_CODE_(  x = n;)  ANNOTATE(op=                for both compilers)
	}
	{
		HEAD1(Notice, without "operator=")

		TRACE_CODE(struct C{
			C(int x)                { std::cout << "!!!contructor!!!"; };
			C(const C& o)           { std::cout << "!!!copy  ctor!!!"; };
			//C& operator=(const C& o){ std::cout << "!!!operator= !!!"; return * this; };
		} 
		);
		TRACE_CODE_(C m (5);)  ANNOTATE(constructor called for both compilers)
		TRACE_CODE_(C n = 10;) ANNOTATE(constructor called for both compilers)
		TRACE_CODE_(C x = m;)  ANNOTATE(copy   ctor called for both compilers)
		TRACE_CODE_(  x = 15;) ANNOTATE(ctor & then op=    for both compilers)
		TRACE_CODE_(  x = i;)  ANNOTATE(ctor & then op = for both compilers)
		TRACE_CODE_(  x = n;)  ANNOTATE(op=                for both compilers)
	}
	{
		HEAD1(Notice, with only "operator=")

		TRACE_CODE(struct C{
			C(int x)                { std::cout << "!!!contructor!!!"; };
			C(const C& o)           { std::cout << "!!!copy  ctor!!!"; };
			C& operator=(const C& o){ std::cout << "!!!op=(T&)   !!!"; return * this; };
		} 
		);
		TRACE_CODE_(C m (5);)  ANNOTATE(constructor called for both compilers)
		TRACE_CODE_(C n = 10;) ANNOTATE(constructor called for both compilers)
		TRACE_CODE_(C x = m;)  ANNOTATE(copy   ctor called for both compilers)
		TRACE_CODE_(  x = 15;) ANNOTATE(ctor & then op=    for both compilers)
		TRACE_CODE_(  x = i;)  ANNOTATE(ctor & then op = for both compilers)
		TRACE_CODE_(  x = n;)  ANNOTATE(op=                for both compilers)
	}
	{
		HEAD1(Notice, with both "operator=(const int)" and "operator(cont T&)")

		TRACE_CODE(struct C{
			C(int x)                  { std::cout << "!!!contructor!!!"; };
			C(const C& o)             { std::cout << "!!!copy  ctor!!!"; };
			C& operator=(const C& o)  { std::cout << "!!!op=(T&)   !!!"; return * this; };
			C& operator=(const int& o){ std::cout << "!!!op=(int&) !!!"; return * this; };
		} 
		);
		TRACE_CODE_(C m (5);)  ANNOTATE(constructor called for both compilers)
		TRACE_CODE_(C n = 10;) ANNOTATE(constructor called for both compilers)
		TRACE_CODE_(C x = m;)  ANNOTATE(copy   ctor called for both compilers)
		TRACE_CODE_(  x = 15;) ANNOTATE(op=                for both compilers)
		TRACE_CODE_(  x = i;)  ANNOTATE(ctor & then op = for both compilers)
		TRACE_CODE_(  x = n;)  ANNOTATE(op=                for both compilers)
	}

	{
		HEAD1(Notice, with both "operator=(const int)" and "operator(cont T&)")

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
		TRACE_CODE_(C m (5);)  ANNOTATE(constructor called for both compilers)
		TRACE_CODE_(C n = 10;) ANNOTATE(constructor called for both compilers)
		TRACE_CODE_(C x = m;)  ANNOTATE(copy   ctor called for both compilers)
		TRACE_CODE_(  x = 15;) ANNOTATE(op=                for both compilers)
		TRACE_CODE_(  x = i;)  ANNOTATE(ctor & then op = for both compilers)
		TRACE_CODE_(  x = n;)  ANNOTATE(op=                for both compilers)
		TRACE_CODE_(C y = C{20};)ANNOTATE(ctor       called for both compilers)
		TRACE_CODE_(C z = C(20);)ANNOTATE(ctor       called for both compilers)
		TRACE_CODE_(  z = C(30);)ANNOTATE(ctor & op= called for both compilers)
		HEAD3(return funcs)
		TRACE_CODE_(auto func1=[]()->C{return C(1000);};)   ANNOTATE(fine for both compilers)
      vcTRACE_CODE_(auto func2=[]()->C&{return C(2000);};)  ANNOTATE(fine for vc)
	  vcTRACE_CODE_(auto func3=[]()->C&&{return C(3000);};) ANNOTATE(fine for vc)
		TRACE_CODEn(auto  c1 = func1();)
	  vcTRACE_CODEn(auto  c2 = func2();)
	  vcTRACE_CODEn(auto  c3 = func3();)
		TRACE_CODEn(      c1 = func1();)
	  vcTRACE_CODEn(      c2 = func2();)
	  vcTRACE_CODEn(      c3 = func3();)
	}

	HORIZONTAL_LINE()
	return 0;
}
END_UNIT // ctor


