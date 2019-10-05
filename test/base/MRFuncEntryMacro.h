#pragma once
/****
* Only used in cpp files
****/
#include "MRFuncEntry.h" 

#define STARTUP_RUN(X,...) class RUN##X{public: class TheRun{public: TheRun(){__VA_ARGS__}}; static TheRun entry;}; RUN##X::TheRun RUN##X::entry;
#define MEMORY_FUNC(X) class M##X{public: static TestFuncEntry entry;}; TestFuncEntry M##X::entry(#X, X::X);
#define TOUR_FUNC(X) namespace X{int X(int argc, char* argv[]);}  MEMORY_FUNC(X)


#define BEGIN_SECTION(X)  namespace X{
#define END_SECTION(X)    } MEMORY_FUNC(X)

