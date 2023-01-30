#pragma once
#include <string>
#include <vector>
#include <map>
namespace virya{

typedef int (*FUNC_ENTRY)(int, char**);
class TestFuncEntry{
public:
	std::string name;
	std::string title;
	std::vector<std::string> keywords;
	FUNC_ENTRY f;
	const char* src_file;
	int         src_line_begin;    
	int         src_line_end;
public:
	TestFuncEntry(FUNC_ENTRY f, const char* name, const char* src_file, int src_line, const char* title = "");
	TestFuncEntry();
	void add_keywords(const std::vector<const char*> keywords);
	void add_keywords(const char* keywords); // ',' is the input field separator
	void add_keywords(const std::string& keywords){add_keywords(keywords.c_str());}
	void add_keyword(const char* keyword);
	void add_keyword(const std::string& keywords){ add_keyword(keywords.c_str());}

class Keywords {
public:
	Keywords(TestFuncEntry& e, const char* s){e.add_keywords(s);}
};

class END {
public:
	END(TestFuncEntry& e, int line);//{ e.src_line_end = line; }
};
};
extern std::map<std::string, TestFuncEntry>& get_func_entries();

} // end namespace virya
