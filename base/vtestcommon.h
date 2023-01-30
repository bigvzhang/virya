#pragma once
#include <iostream>
#include <vioman.h>
#include <varg.h>   // virya/varg.h
#include <vmacro_compliance.h>
#include "vfuncentry_macro.h"
#include "vioman.h"
#include "vmacro_va.h"


#ifdef _WIN32 // let __FUNCSIG__ == __PRETTY_FUNCTION__ 
#define __PRETTY_FUNCTION__ __FUNCSIG__
#else
#define __FUNCSIG__ __PRETTY_FUNCTION__ 
#endif

#define DEF_FUNC(X) X(int argc, char* argv[])

#define PRINT_CONTENT(X) {printf("[%4d] %s => %s\n",__LINE__, #X, X.toString().c_str()); running_line = __LINE__ + 1;}
#define EXECUTE_LINE(...) printf("%s ==> \n",#__VA_ARGS__); __VA_ARGS__

inline int HORIZONTAL_LINE_func (char c = '=', int n = 140){ virya::stdout_horizontal_line(n, c); return 0; }
inline int HORIZONTAL_LINEs_func(char c = '-', int n = 110){ virya::stdout_horizontal_line(n, c); return 0; }
#define HORIZONTAL_LINE(...)  HORIZONTAL_LINE_func( __VA_ARGS__);
#define HORIZONTAL_LINEs(...) HORIZONTAL_LINEs_func(__VA_ARGS__); // == HORIZONTAL_LINE(110)
#define HORIZONTAL_FRAME(...) HORIZONTAL_LINE(); __VA_ARGS__; HORIZONTAL_LINE();
#define HORIZONTAL1(...) HORIZONTAL_LINE_func('=', ##__VA_ARGS__);
#define HORIZONTAL2(...) HORIZONTAL_LINE_func('-', ##__VA_ARGS__);
#define HORIZONTAL3(...) HORIZONTAL_LINE_func('~', ##__VA_ARGS__);
#define HORIZONTAL4(...) HORIZONTAL_LINE_func('.', ##__VA_ARGS__);
#define HORIZONTAL5(...) HORIZONTAL_LINE_func('_', ##__VA_ARGS__);
#define HORIZONTAL1s() HORIZONTAL1(110)
#define HORIZONTAL2s() HORIZONTAL2(110)
#define HORIZONTAL3s() HORIZONTAL3(110)
#define HORIZONTAL4s() HORIZONTAL4(110)
#define HORIZONTAL5s() HORIZONTAL5(110)


//   static const char*                CODE_FORMAT {"++ %-70s"}; // default, must be static
//   static const char*                CODE_FORMAT_{"++ %-70s -> "};   // default, must be static
//   static const char*                CODE_FORMATv{"@@ %-70s == "};   // default, must be static
//,, static const char*                CODE_FORMATw{"!! %-70s\n"}; // default, must be static
//-- dftarg.use.staticvar
extern const char*                CODE_FORMAT ;//{"++ %-70s"}; // default, must be static
extern const char*                CODE_FORMAT_;//{"++ %-70s -> "};   // default, must be static
extern const char*                CODE_FORMATv;//{"@@ %-70s == "};   // default, must be static
extern const char*                CODE_FORMATw;//{"!! %-70s\n"}; // default, must be static

#define TRACE_CODE(...)     printf(CODE_FORMAT, #__VA_ARGS__); __VA_ARGS__ ; printf("\n");       // append '\n'
#define TRACE_CODE_(...)    printf(CODE_FORMAT_, #__VA_ARGS__); __VA_ARGS__;                     // no '\n'
#define TRACE_CODEn(...)    printf(CODE_FORMAT,  #__VA_ARGS__); printf("\n"); __VA_ARGS__;       // 
#define TRACE_CODEv(...)    printf(CODE_FORMATv, #__VA_ARGS__); std::cout << (__VA_ARGS__) << "\n";
#define TRACE_CODEs(...)    printf(CODE_FORMATv, #__VA_ARGS__); std::cout << to_string(__VA_ARGS__) << "\n";
#define TRACE_CODEw(...)    printf(CODE_FORMATw, #__VA_ARGS__); printf("\n"); // for  error
#define TRACE_TYPE(...)     printf("TypeExpression: {{%s}} ==> %s\n", #__VA_ARGS__, typeid(__VA_ARGS__).name());
#define TRACE_NONE()        // do nothing, generally it's used as delimiter
#define TRACE_NON()         // == TRACE_NONE

#define TRACE_LINE(...)     print_srcfile(stdout, __FILE__, virya::file_oneline(__LINE__, CODE_FORMAT));  __VA_ARGS__; printf("\n");       // append '\n'
#define TRACE_LINE_(...)    print_srcfile(stdout, __FILE__, virya::file_oneline(__LINE__, CODE_FORMAT_)); __VA_ARGS__;        
#define TRACE_LINEv(...)    print_srcfile(stdout, __FILE__, virya::file_oneline(__LINE__, CODE_FORMATv)); std::cout << #__VA_ARGS__ << " : " << (__VA_ARGS__) << "\n";// append '\n'
#define TRACE_LINEs1(x)     print_srcfile(stdout, __FILE__, virya::file_oneline(__LINE__, CODE_FORMATv)); std::cout << #x << " : " << to_string(x) << "\n";// append '\n'
#define TRACE_LINEs2(x,f)   print_srcfile(stdout, __FILE__, virya::file_oneline(__LINE__, CODE_FORMATv)); std::cout << #x << " : " << f(x)         << "\n";// append '\n'
#define TRACE_LINEs(...)    __MR_CONCAT(TRACE_LINEs, __MR_VACOUNT(__VA_ARGS__))(__VA_ARGS__)
#define TRACE_LINEm1(x)     print_srcfile(stdout, __FILE__, virya::file_oneline(__LINE__, CODE_FORMATv)); std::cout << #x << " : " << x.toString() << "\n";// append '\n'
#define TRACE_LINEm2(x,f)   print_srcfile(stdout, __FILE__, virya::file_oneline(__LINE__, CODE_FORMATv)); std::cout << #x << " : " << x.f() << "\n";// append '\n'
#define TRACE_LINEm(...)    __MR_CONCAT(TRACE_LINEm, __MR_VACOUNT(__VA_ARGS__))(__VA_ARGS__)
#define TRACE_LINEw(...)    print_srcfile(stdout, __FILE__, virya::file_oneline(__LINE__, CODE_FORMATw)); __VA_ARGS__; printf("\n");
//   TRACE_L <- TRACE_LINE + comment
#define TRACE_L(...)       print_srcfile(stdout, __FILE__, virya::file_oneline(__LINE__, CODE_FORMAT, 'c'));  __VA_ARGS__; printf("\n"); // 
#define TRACE_L_(...)   print_srcfile(stdout, __FILE__, virya::file_oneline(__LINE__, CODE_FORMAT_, 'c')); __VA_ARGS__;        
//   TRACE_LV <- TRACE_LINEv, but don't print var's name
//^^ TRACE_LVm(v, f) == TRACE_LV(v.f())
#define TRACE_LV(...)       print_srcfile(stdout, __FILE__, virya::file_oneline(__LINE__, CODE_FORMATv)); std::cout << (__VA_ARGS__) << "\n";// append '\n'
#define TRACE_LVm1(x)       print_srcfile(stdout, __FILE__, virya::file_oneline(__LINE__, CODE_FORMATv)); std::cout << x.toString() << "\n";// append '\n'
#define TRACE_LVm2(x,f)     print_srcfile(stdout, __FILE__, virya::file_oneline(__LINE__, CODE_FORMATv)); std::cout << x.f() << "\n";// append '\n'
#define TRACE_LVm(...)      __MR_CONCAT(TRACE_LVm, __MR_VACOUNT(__VA_ARGS__))(__VA_ARGS__) 

// TRACE_QUE = TRACE_LINE; ioq.clear
#define TRACE_QUE(...)     print_srcfile(stdout, __FILE__, virya::file_oneline(__LINE__, CODE_FORMAT));  __VA_ARGS__; printf("\n"); ioq.clear();        // append '\n'
#define TRACE_QUE_(...)    print_srcfile(stdout, __FILE__, virya::file_oneline(__LINE__, CODE_FORMAT_)); __VA_ARGS__; ioq.clear();         
#define TRACE_QUEv(...)    print_srcfile(stdout, __FILE__, virya::file_oneline(__LINE__, CODE_FORMATv)); std::cout << #__VA_ARGS__ << " : " << (__VA_ARGS__) << "\n"; ioq.clear(); // append '\n'
#define TRACE_QUEs1(x)     print_srcfile(stdout, __FILE__, virya::file_oneline(__LINE__, CODE_FORMATv)); std::cout << #x << " : " << to_string(x) << "\n"; ioq.clear(); // append '\n'
#define TRACE_QUEs2(x,f)   print_srcfile(stdout, __FILE__, virya::file_oneline(__LINE__, CODE_FORMATv)); std::cout << #x << " : " << f(x)         << "\n"; ioq.clear(); // append '\n'
#define TRACE_QUEs(...)    __MR_CONCAT(TRACE_QUEs, __MR_VACOUNT(__VA_ARGS__))(__VA_ARGS__)
#define TRACE_QUEm1(x)     print_srcfile(stdout, __FILE__, virya::file_oneline(__LINE__, CODE_FORMATv)); std::cout << #x << " : " << x.toString() << "\n"; ioq.clear(); // append '\n'
#define TRACE_QUEm2(x,f)   print_srcfile(stdout, __FILE__, virya::file_oneline(__LINE__, CODE_FORMATv)); std::cout << #x << " : " << x.f() << "\n"; ioq.clear(); // append '\n'
#define TRACE_QUEm(...)    __MR_CONCAT(TRACE_QUEm, __MR_VACOUNT(__VA_ARGS__))(__VA_ARGS__)
#define TRACE_QUEw(...)    print_srcfile(stdout, __FILE__, virya::file_oneline(__LINE__, CODE_FORMATw)); __VA_ARGS__; printf("\n"); ioq.clear(); 


#define ANNOTATE(...)          printf("// %s\n",#__VA_ARGS__);
#define ANNOTATEs(x)           printf("// %s\n",x);                    // x is const char*
#define ANNOTATEe(...)         printf("// %s\n", #__VA_ARGS__);printf(" <== compile error\n");
#define ANNOTATEw(...)         printf("// %s\n", #__VA_ARGS__);printf(" <== warn although compile OK\n");
#define ANNOTATEh(x)           HORIZONTAL_LINEs('.',79);printf("// %s\n",x); // ^^ print one more horizontal
#define EXPLAIN(...)           printf("%s\n",  #__VA_ARGS__);
#define EXPLAIN_(...)          printf("%s",  #__VA_ARGS__);
#define EXPLAINs(x)            printf("%s\n",x);                    //
#define EXPLAINh(x)            HORIZONTAL_LINEs('.',79);printf("%s\n",x); // ^^print one more horizontal
#define NOTICE(...)            std::cout << "NOTICE: " << virya::trim_quote(#__VA_ARGS__) << std::endl;
#define NOTICEf(f, ...)        printf("NOTICE: " f  "\n", ##__VA_ARGS__); // like printf
#define NOTICEf_(f, ...)       printf("        " f  "\n", ##__VA_ARGS__); 
#define SEEALSO(...)           printf("SEEALSO: %s\n", #__VA_ARGS__);
#define MANUAL(...)            __MR_CONCAT(MANUAL, __MR_VACOUNT(__VA_ARGS__))(__VA_ARGS__)               // WHOLE OR PART
#define MANUALs(X)             virya::print_manual(stdout, __FILE__, __LINE__,__FUNCSIG__, X);       // `X` PART of MANUAL
#define MANUAL0()              virya::print_manual(stdout, __FILE__, __LINE__,__FUNCSIG__, nullptr); //  WHOLE MANUAL
#define MANUAL1(X)             virya::print_manual(stdout, __FILE__, __LINE__,__FUNCSIG__, #X);      // `X` PART of MANUAL
#define MANUALb(...)           HORIZONTAL_LINE();MANUAL(__VA_ARGS__);HORIZONTAL_LINE();  //like banner or box;
#define MANUALh(...)		   HORIZONTAL_LINE();MANUAL(__VA_ARGS__);                    //drawline;content;
#define MANUALt(...)		                     MANUAL(__VA_ARGS__);HORIZONTAL_LINE();  //content;drawline;

#define REFERENCE(x)           printf("// %s\n",x);

#define HEAD(...)         virya::left_stdout(#__VA_ARGS__, 40, 140,'=');
#define HEAD1(...)        virya::left_stdout(#__VA_ARGS__, 4, 140, '=');  // as html tag <h1>
#define HEAD2(...)        virya::left_stdout(#__VA_ARGS__, 4, 140, '-');  // as html tag <h2>
#define HEAD3(...)        virya::left_stdout(#__VA_ARGS__, 4, 140, '~');  // as html tag <h3>
#define HEAD4(...)        virya::left_stdout(#__VA_ARGS__, 4, 140, '.');  // as html tag <h4>
#define HEAD5(...)        virya::left_stdout(#__VA_ARGS__, 4, 140, '_');  // as html tag <h5>
#define HEAD1s(...)       virya::left_stdout(#__VA_ARGS__, 4, 120, '=');  // as html tag <h1>
#define HEAD2s(...)       virya::left_stdout(#__VA_ARGS__, 4, 120, '-');  // as html tag <h2>
#define HEAD3s(...)       virya::left_stdout(#__VA_ARGS__, 4, 120, '~');  // as html tag <h3>
#define HEAD4s(...)       virya::left_stdout(#__VA_ARGS__, 4, 120, '.');  // as html tag <h4>
#define HEAD5s(...)       virya::left_stdout(#__VA_ARGS__, 4, 120, '_');  // as html tag <h5>
#define TITLE(...)        virya::left_stdout(#__VA_ARGS__, 60, 140, '*');  // reference `tour_nm_1`
#define TITLE1(...)       virya::left_stdout(#__VA_ARGS__, 50, 120, '~');  // ^^>
#define TITLE2(...)       virya::left_stdout(#__VA_ARGS__, 50, 120, '-');  // ^^>
#define TITLE3(...)       virya::left_stdout(#__VA_ARGS__, 50, 120, '.');  // ^^>
#define TITLE4(...)       virya::left_stdout(#__VA_ARGS__, 50, 120, '_');  // ^^>
#define BANNER(...)       virya::left_stdout(#__VA_ARGS__, 4, 79, '-');;


#define TRACE_TODO(...)        printf("TODO\n");

// TRACE_SRC group
#define TRACE_SRC(n1,n2,...)   print_srcfile(stdout, __FILE__, virya::file_section(__LINE__,n1,n2), ##__VA_ARGS__);// section of file
#define TRACE_NXT(...)         print_srcfile(stdout, __FILE__, virya::file_section_nxt(__LINE__,##__VA_ARGS__));// section of file 
#define TRACE_PRV(...)         print_srcfile(stdout, __FILE__, virya::file_section_prv(__LINE__,##__VA_ARGS__));// section of file 
#define TRACE_SRCb(n1,n2,...)  HORIZONTAL_LINE();TRACE_SRC(n1,n2,##__VA_ARGS__);HORIZONTAL_LINE();  //like banner or box;
#define TRACE_SRCh(n1,n2,...)  HORIZONTAL_LINE();TRACE_SRC(n1,n2,##__VA_ARGS__);                    //drawline;content;
#define TRACE_SRCt(n1,n2,...)		             TRACE_SRC(n1,n2,##__VA_ARGS__);HORIZONTAL_LINE();  //content;drawline;

// try to print manual
#define TRY_MANUAL() if(virya::help_option(argc, argv)){ MANUAL();	return 0; }

// TRACE_E <- TRACE expression + comment
#define TRACE_E(...)     print_srcfile(stdout, __FILE__, virya::file_oneexpression(__LINE__, "TRACE", "++ %s", 'c'));  __VA_ARGS__; printf("\n");
#define TRACE_E_(...)    print_srcfile(stdout, __FILE__, virya::file_oneexpression(__LINE__, "TRACE", "++ %s => ", 'c'));  __VA_ARGS__;
#define TRACE_Ew(...)    print_srcfile(stdout, __FILE__, virya::file_oneexpression(__LINE__, "TRACE", "!! %s", 'c'));  __VA_ARGS__; printf("\n");
#define TRACE_Ev(...)    print_srcfile(stdout, __FILE__, virya::file_oneexpression(__LINE__, "TRACE", "++ %s => ", 'c')); std::cout <<  __VA_ARGS__; printf("\n");
#define TRACE_Eb(...)    print_srcfile(stdout, __FILE__, virya::file_oneexpression(__LINE__, "TRACE", "++ %s => ", 'c')); std::cout << std::boolalpha <<  __VA_ARGS__; printf("\n");
#define TRACE_NE(...)    print_srcfile(stdout, __FILE__, virya::file_oneexpression(__LINE__+1, "TRACE", "++ %s", 'c'));  __VA_ARGS__; printf("\n"); // trace next-line expression
#define TRACE_NE_(...)   print_srcfile(stdout, __FILE__, virya::file_oneexpression(__LINE__+1, "TRACE", "++ %s => ", 'c'));  __VA_ARGS__; 
#define TRACE_PE(...)    print_srcfile(stdout, __FILE__, virya::file_oneexpression(__LINE__-1, "TRACE", "++ %s", 'c'));  __VA_ARGS__; printf("\n"); // trace previous-line expression
#define TRACE_PE_(...)   print_srcfile(stdout, __FILE__, virya::file_oneexpression(__LINE__-1, "TRACE", "++ %s => ", 'c'));  __VA_ARGS__; 

#define TRACE_ES()       print_srcfile(stdout, __FILE__, virya::file_expressions(__LINE__, "&", "++ %s\n", 'L')); // trace expressions
#define TRACE_ES__(...) TRACE_ES() __VA_ARGS__ // TRACE_ES__(CODE_FORg) combines two macros

// The following for TRACE_EXP
struct  BoolWhistle {
	std::string s;
	bool  b;
	BoolWhistle(const std::string& s):s(s), b(false){}	
	BoolWhistle(const char* s):s(s),        b(false){}	
	BoolWhistle() : b(false){}
	BoolWhistle(const char* file, int line, const char* s):s(s),b(false){// print one expression
		print_srcfile(stdout, file, virya::file_oneexpression(line, "&", "!! %s => "));
	}
	BoolWhistle& operator()(const char* file, int line, const char* s){// print one expression
		this->s = s;
	    this->b = false;
	    print_srcfile(stdout, file, virya::file_oneexpression(line, "&", "!! %s => "));
		return *this;
	}
	static BoolWhistle INSTANCE;
};
inline BoolWhistle& operator | (bool b, BoolWhistle &w)                 {	if(!b){ std::cout << w.s; }	w.b = b; return w;} 
inline BoolWhistle& operator & (bool b, BoolWhistle &w)                 {	if(b) { std::cout << w.s; }	w.b = b; return w;}
inline void         operator | (BoolWhistle &w, const char* s){ if(!w.b){ std::cout << s;}  }
inline void         operator & (BoolWhistle &w, const char* s){ if(w.b) { std::cout << s;}  }
#define ECHO_K(s1,s2) BoolWhistle::INSTANCE(__FILE__, __LINE__, s1) | s2 // K<ASK; like condition operator ?:

struct  Whistle {
	Whistle(){}
	Whistle& operator()(const char* file, int line, const char* delimiter = "&",  const char* fmt = "++ %s => "){// print one expression
	    print_srcfile(stdout, file, virya::file_oneexpression(line, delimiter, fmt));
		return *this;
	}
	static Whistle INSTANCE;
};
//example: inline Whistle& operator & (string s, Whistle &w){	std::cout << s;  return w;}
#define ECHO(...)   Whistle::INSTANCE(__FILE__, __LINE__, "?ECHO",  ##__VA_ARGS__)
#define ECHOn(...)  Whistle::INSTANCE(__FILE__, __LINE__, "?ECHO",  ##__VA_ARGS__); printf("\n");
#define ECHOc(...)  Whistle::INSTANCE(__FILE__, __LINE__, "?ECHO",  ##__VA_ARGS__); print_srcfile(stdout, __FILE__, virya::file_trailing_comment(__LINE__));


class CODE_FORMAT_Help {
private:
	const char* oldCODE_FORMAT;
	const char* oldCODE_FORMAT_;
	const char* oldCODE_FORMATv;
	const char* oldCODE_FORMATw;
	std::string newCODE_FORMAT;
	std::string newCODE_FORMAT_;
	std::string newCODE_FORMATv;
	std::string newCODE_FORMATw;

public:
	template<typename... T>
	inline CODE_FORMAT_Help(T... args) :
		oldCODE_FORMAT(nullptr),
		oldCODE_FORMAT_(nullptr),
		oldCODE_FORMATv(nullptr),
		oldCODE_FORMATw(nullptr)
	{
		static_assert(sizeof...(T) >= 2,     "sizeof...(args) >= 2");
		static_assert((sizeof...(T))%2 == 0, "sizeof...(args) must be event");
		std::vector<const char*> vct = {args...};
		for(size_t i = 0; i+1 < vct.size(); i+=2){ // first, accknowlege and backup
			if(vct[i] == CODE_FORMAT && oldCODE_FORMAT == nullptr){
				oldCODE_FORMAT = CODE_FORMAT;
				//CODE_FORMAT = vct[i+1];
			}	else if(vct[i] == CODE_FORMAT_ && oldCODE_FORMAT_ == nullptr){
				oldCODE_FORMAT_ = CODE_FORMAT_;
				//CODE_FORMAT_ = vct[i + 1];
			}	else if(vct[i] == CODE_FORMATv && oldCODE_FORMATv == nullptr){
				oldCODE_FORMATv = CODE_FORMATv;
				//CODE_FORMATv = vct[i + 1];
			}	else if(vct[i] == CODE_FORMATw && oldCODE_FORMATw == nullptr){
				oldCODE_FORMATw = CODE_FORMATw;
				//CODE_FORMATw = vct[i + 1];
			}else {
				throw 1;
			}
		}
		for(size_t i = 0; i+1 < vct.size(); i += 2){ // second, set
			if(vct[i] == CODE_FORMAT){
				//oldCODE_FORMAT = CODE_FORMAT;
				CODE_FORMAT = vct[i + 1];
			} else if(vct[i] == CODE_FORMAT_){
				//oldCODE_FORMAT_ = CODE_FORMAT_;
				CODE_FORMAT_ = vct[i + 1];
			} else if(vct[i] == CODE_FORMATv){
				//oldCODE_FORMATv = CODE_FORMATv;
				CODE_FORMATv = vct[i + 1];
			} else if(vct[i] == CODE_FORMATw){
				//oldCODE_FORMATw = CODE_FORMATw;
				CODE_FORMATw = vct[i + 1];
			} else {
				throw 1;// should never be reached
			}
		}
	}
	
	//TAG:memberfunctiontemplate.instantialize; OK for msvc: template<>, not for gnuc
	inline CODE_FORMAT_Help(int n): 
		oldCODE_FORMAT(CODE_FORMAT),
		oldCODE_FORMAT_(CODE_FORMAT_),
		oldCODE_FORMATv(CODE_FORMATv),
		oldCODE_FORMATw(CODE_FORMATw)
	{
		newCODE_FORMAT  = std::string("++ %") + std::to_string(n) + "s";
		newCODE_FORMAT_ = std::string("++ %") + std::to_string(n) + "s -> ";
		newCODE_FORMATv = std::string("@@ %") + std::to_string(n) + "s == ";
		newCODE_FORMATw = std::string("!! %") + std::to_string(n) + "s";
		CODE_FORMAT  = newCODE_FORMAT.c_str();
		CODE_FORMAT_ = newCODE_FORMAT_.c_str();
		CODE_FORMATv = newCODE_FORMATv.c_str();
		CODE_FORMATw = newCODE_FORMATw.c_str();
	}

	CODE_FORMAT_Help(const CODE_FORMAT_Help& o) = delete;

	~CODE_FORMAT_Help(){
		if(oldCODE_FORMAT)	CODE_FORMAT = oldCODE_FORMAT;
		if(oldCODE_FORMAT_)	CODE_FORMAT_ = oldCODE_FORMAT_;
		if(oldCODE_FORMATv)	CODE_FORMATv = oldCODE_FORMATv;
		if(oldCODE_FORMATw)	CODE_FORMATw = oldCODE_FORMATw;
	}

};

//TAG:memberfunctiontemplate.instantialize; OK for linux => template<> inline CODE_FORMAT_Help<>::CODE_FORMAT_Help<int>(int n) 
