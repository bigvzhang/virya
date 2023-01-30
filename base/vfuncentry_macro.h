#pragma once
/**
  *NOTICE!  Only used in cpp files; including in the header file is forbidden 
  */
#include "vfuncentry.h" 

#define STARTUP_RUN(X,...) class RUN##X{public: class TheRun{public: TheRun(){__VA_ARGS__}}; static TheRun entry;}; RUN##X::TheRun RUN##X::entry;
#define MEMORY_FUNC(X) class M##X{public: static virya::TestFuncEntry entry;}; virya::TestFuncEntry M##X::entry(X::X, #X, __FILE__, __LINE__);
#define TOUR_FUNC(X) namespace X{int X(int argc, char* argv[]);}  MEMORY_FUNC(X)


#define BEGIN_SECTION(X)  namespace X{
#define END_SECTION(X)    } MEMORY_FUNC(X)



#define BEGIN_UNIT(X,...) namespace X{using namespace virya; int main(int, char* []); TestFuncEntry __test_entry(&main, #X,__FILE__,__LINE__, #__VA_ARGS__ ""); 
#define END_UNIT      TestFuncEntry::END __test_entry_end(__test_entry, __LINE__);}
#define KEYWORDS(...) TestFuncEntry::Keywords _test_entry_keywords(__test_entry, #__VA_ARGS__ );

// if defined TOUR_GROUP, BEGIN_UNIT_ can be used
#define BEGIN_UNIT_1(Y,X,...) namespace Y##X{using namespace virya; int main(int, char* []); TestFuncEntry __test_entry(&main, #Y#X,__FILE__,__LINE__, #__VA_ARGS__ ""); 
#define BEGIN_UNIT_2(Y,X,...) BEGIN_UNIT_1(Y,X, ##__VA_ARGS__)
#define BEGIN_UNIT_(X,...) BEGIN_UNIT_2(TOUR_GROUP, X, ##__VA_ARGS__)
