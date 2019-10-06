#include "MRFuncEntry.h"


std::map<std::string, TestFuncEntry>& get_func_entries(){
	static std::map<std::string, TestFuncEntry> func_entries;
	return func_entries; 
}

TestFuncEntry::TestFuncEntry(const char* _param_name, FUNC_ENTRY param_f):	name(_param_name), f(param_f){
	// Will Add This Entry to the Book
	std::map<std::string, TestFuncEntry>& func_entries = get_func_entries();
	auto it = func_entries.find(name);
	if(it == func_entries.end()){
		func_entries.insert(std::pair<std::string, TestFuncEntry>(name, *this));
	}else{
		it->second = *this;
	}	
}
TestFuncEntry::TestFuncEntry():f(nullptr){}
