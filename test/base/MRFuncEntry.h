#pragma once
#include <string.h>
#include <vector>
#include <map>

typedef int (*FUNC_ENTRY)(int, char**);
class TestFuncEntry{
public:
	std::string name;
	FUNC_ENTRY f;
public:
	TestFuncEntry(const char* param_name, FUNC_ENTRY param_f);
	TestFuncEntry();
};
std::map<std::string, TestFuncEntry>& get_func_entries();