#include "MRFuncEntry.h"
std::map<std::string, TestFuncEntry> func_entries;
TestFuncEntry::TestFuncEntry(const char* param_name, FUNC_ENTRY param_f):	name(param_name), f(param_f){
	// Will Add This Entry to the Book
	auto it = func_entries.find(param_name);
	if(it == func_entries.end()){
		func_entries.insert(std::pair<std::string, TestFuncEntry>(param_name, *this));
	}else{
		it->second = *this;
	}	
}
TestFuncEntry::TestFuncEntry():f(nullptr){}
