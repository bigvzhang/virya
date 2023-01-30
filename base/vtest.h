#ifndef VIRYA_TEST_H
#define VIRYA_TEST_H
#include <vector>
#include <map>
#include <string>

namespace virya{
namespace test{

typedef int (*PROG_ENTRY)(int, char**);

class prog_entry{
public:
	static std::map<std::string, prog_entry> prog_entries;
public:
	std::string name;
	std::string title;
	PROG_ENTRY f;
public:
	prog_entry(PROG_ENTRY func, const char* name, const char* title = "");
	prog_entry();
}; // class prog_entry


typedef void (*SUB_ENTRY)();
class SubEntry{
public:
	std::string name;
	SUB_ENTRY f;
public:
	SubEntry(const char* name, SUB_ENTRY f):name(name), f(f){}
	SubEntry() :name(name), f(nullptr){}
};
int submain(std::vector<SubEntry>& subEntries, int argc, char* argv[]);

}// namespace test
}// namesapce virya


#ifndef BEGIN_UNIT// TOREMOVE
#define STARTUP_RUN(X,...) class RUN##X{public: class TheRun{public: TheRun(){__VA_ARGS__}}; static TheRun entry;}; RUN##X::TheRun RUN##X::entry;

#define CLS_ENTRY(X, ...) class __msg{public: static virya::test::prog_entry entry;}; virya::test::prog_entry __msg::entry(main, #X, ##__VA_ARGS__);
#define BEGIN_UNIT(X,...) namespace X{int main(int, char* []); CLS_ENTRY(X, ##__VA_ARGS__) 
#define END_UNIT   }
#endif

#endif
