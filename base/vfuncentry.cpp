#include "vfuncentry.h"

#include <regex>

namespace virya {

std::map<std::string, TestFuncEntry>& get_func_entries(){
	static std::map<std::string, TestFuncEntry> func_entries;
	return func_entries; 
}

TestFuncEntry::TestFuncEntry(FUNC_ENTRY f_, const char* name_,const char* src_file, int src_line, const char* title_):	name(name_), f(f_), src_file(src_file), src_line_begin(src_line), src_line_end(0), title(title_){
	// Will Add This Entry to the Book
	std::map<std::string, TestFuncEntry>& func_entries = get_func_entries();
	auto it = func_entries.find(name);
	if(it == func_entries.end()){
		func_entries.insert(std::pair<std::string, TestFuncEntry>(name, *this));
	}else{
		it->second = *this;
	}	
}
TestFuncEntry::TestFuncEntry():f(nullptr),src_file(nullptr), src_line_begin(0), src_line_end(0){}

void TestFuncEntry::add_keywords(const std::vector<const char*> p_keywords){
	this->keywords.insert(this->keywords.end(),p_keywords.begin(), p_keywords.end());
}
void TestFuncEntry::add_keywords(const char* keywords){

	typedef std::regex_token_iterator<const char *> Myiter;

	std::regex rgx("\\s*,\\s*");

	auto next = Myiter(keywords, keywords + strlen(keywords), rgx, -1);
	Myiter end;
	for(; next != end; ++next){
		this->keywords.push_back(next->str());
	}
}

void TestFuncEntry::add_keyword(const char* keyword){
	this->keywords.push_back(keyword);
}

TestFuncEntry::END::END(TestFuncEntry& e, int line){
	e.src_line_end = line;
	std::map<std::string, TestFuncEntry>& func_entries = get_func_entries();

	auto it = func_entries.find(e.name);
	if(it == func_entries.end()){
		func_entries.insert(std::pair<std::string, TestFuncEntry>(e.name, e));
	} else{
		it->second = e;
	}
}

} // namespace virya
