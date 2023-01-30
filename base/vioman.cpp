#include <string.h>
#include <fstream>
#include <regex>
#include <map>
#include "vioman.h"
#include "vstring.h"
#include "vsys.h"
#include "vfile.h"
#include "vmacro_compliance.h"


namespace virya{

std::string center(const char* content, const size_t width, char fillchar) {
    
	auto l = strlen(content);
	if(width <=  l)
		return std::string(content);
	else{
		size_t pad = width - l;
		std::string rtn(width, fillchar);
		memcpy(&rtn[0] + pad/2, content, l);
		return rtn;
	}
 
}

inline void trim_quote(string & s){
	if(s.length() > 1){
		if(s[0] == '\"' && s[s.length()-1]=='\"'){
			s = s.substr(1, s.length()-2);
		}
	}
}
std::string trim_quote(const char* s_){
	string s = s_;
	trim_quote(s);
	return s;
}


void center_output(FILE* stream, const char* content_, const size_t width, const char fillchar, bool newline){
	string content = content_; trim_quote(content);
	auto l = content.length();
	if(width <=  l)
		fprintf(stream, "%s", content.c_str());
	else{
		fprintf(stream, "%s", center(content.c_str(), width, fillchar).c_str()); // depends on center
	}
	
	if(newline){
		fprintf(stream,"\n");
	}
}

void left_output(FILE* stream, const char* content_, const size_t left, const size_t width, const char fillchar, bool newline){
	string content = content_; trim_quote(content);
	auto l = content.length();
	if(width <=  left+l)
		fprintf(stream, "%s%s",   std::string(left, fillchar).c_str(), content.c_str());
	else{
		fprintf(stream, "%s%s%s", std::string(left, fillchar).c_str(), content.c_str(), std::string(width-left-l, fillchar).c_str());
	}
	
	if(newline){
		fprintf(stream,"\n");
	}
}

void right_output(FILE* stream, const char* content_, const size_t right, const size_t width, const char fillchar, bool newline){
	string content = content_; trim_quote(content);
	auto l = content.length();
	if(width <=  right+l)
		fprintf(stream, "%s%s",   content.c_str(), std::string(right, fillchar).c_str());
	else{
		fprintf(stream, "%s%s%s", std::string(width-right-l, fillchar).c_str(), content.c_str(), std::string(right, fillchar).c_str());
	}
	
	if(newline){
		fprintf(stream,"\n");
	}
}

using namespace std;
static regex rgx("^([\\+-]?\\d+)(\\s+([\\+-]?\\d+)){0,1}$");
//
//file_section::file_section(const char* s){
//	cmatch mr;
//	if(regex_search(s, mr, rgx)){
//		pos1 = std::stoi(mr[1].str());
//		if(mr[3].matched){
//			pos1 = std::stoi(mr[2].str());
//		}else{
//			pos2 = pos1;
//		}
//	}else{
//		pos1 = 0;
//		pos2 = 0;
//	}
//}
//
//file_section::file_section(i64 n, const char* s):file_section(s){
//	pos1+=n;
//	pos2+=n;
//}
//
//file_section::file_section(i64 n):pos1(n), pos2(n){
//
//}

file_section::file_section(i64 n, i64 first, i64 second) : pos1(n+first), pos2(n+second){}
file_oneline::file_oneline(size_t pos1, const char* fmt, char flag):pos1(pos1), fmt(fmt), trailing_flag(flag){}
file_trailing_comment::file_trailing_comment(size_t pos1, const char* fmt):pos1(pos1), fmt(fmt){}
file_oneexpression::file_oneexpression(size_t pos1,const char* d, const char* fmt, char flag):pos1(pos1),delimiter(d),fmt(fmt), trailing_flag(flag){}
file_expressions::file_expressions(size_t pos1,const char* d, const char* fmt, char flag)             :pos1(pos1),pos2(SIZE_MAX), delimiter(d),fmt(fmt), trailing_flag(flag){}
file_expressions::file_expressions(size_t pos1,size_t pos2, const char* d, const char* fmt, char flag):pos1(pos1),pos2(pos2),delimiter(d),fmt(fmt), trailing_flag(flag){}
file_section_nxt::file_section_nxt(i64 n, i64 lines, const char* prefix) : pos1(n + 1),    pos2(n +  lines), prefix(prefix){}
file_section_nxt::file_section_nxt(i64 n, const char* prefix, int lines) : file_section_nxt(n, lines, prefix){}
file_section_prv::file_section_prv(i64 n, i64 lines, const char* prefix) : pos1(n - lines), pos2(n - 1), prefix(prefix){}
file_section_prv::file_section_prv(i64 n, const char* prefix, int lines) : file_section_prv(n, lines, prefix){}
file_manual::file_manual(i64 n, const char* name, const char* sec, const char* prefix):	pos(n), name(name),section(sec), prefix(prefix){}

static std::ifstream get_ifstream_(const char* srcfile){
	std::ifstream is(srcfile);
	if(!is.is_open()){// try to search the file
		string dir = dirname2(getCurrentProcessLongName().c_str());
		int cnt = 0;
		while(!dir.empty()){
			is.open(muran_path_join(dir.c_str(), srcfile));
			if(is.is_open())
				break;
			if(++cnt > 5)
				return is;
			dir = dirname2(dir.c_str());
		}
	}
	return is;
}
static std::vector<std::string>& get_source(const char* srcfile){
	static map<const char*, vector<string>> cache;
	auto it = cache.find(srcfile);
	if(it == cache.end()){
		ifstream is = get_ifstream_(srcfile);
		auto x = cache.insert(make_pair(srcfile, vector<string>()));
		if(!x.second){
			throw 1; // memory issue
		}
		for(std::string str; std::getline(is, str);) {
			x.first->second.push_back(str);
		}
		return x.first->second;
	}else{
		return it->second;
	}
}

void  print_srcfile(FILE* stream, const char* srcfile, const i64 pos1, const i64 pos2, const char* line_prefix){
	vector<string>& is = get_source(srcfile);
	// The function getline returns false if there are no more lines.
	i64 l = 0;
	//regex rgx(R"(^(.*?)((TRACE|HEAD|NOTICE|PRINT|HORIZONTAL_LINE|REFERENCE|ANNOTATE|MANUAL|EXPLAIN)\w*))");
	regex rgx(R"(^(.*?)((TRACE|HEAD|NOTICE|PRINT|HORIZONTAL|REFERENCE|ANNOTATE|MANUAL|EXPLAIN)\w*)((.*\)\s*);(.*)){0,1})"); // mr[6]=>some useful after the tag
	cmatch mr;
	for(std::string str : is) {
		l++;
		if(l >= pos1 && l <= pos2){
			if(regex_search(str.c_str(), mr, rgx)){
				//printf("=========TAG:%s\n", mr[2].str().c_str()); tag
				//printf("=========OPT:%s\n", mr[5].str().c_str()); option till `);`
				//printf("=========OTH:%s\n", mr[6].str().c_str()); some useful
				if(!regex_match(mr[1].str(), regex("\\s*"))){ // contains none-space char
					if(line_prefix){
						//TODO, move the first tab
						fprintf(stream, "%s%s%s\n", line_prefix, mr[1].str().c_str(),  mr[6].str().c_str());
					}else
						fprintf(stream, "%s%s\n", mr[1].str().c_str(),  mr[6].str().c_str());
				}
			}else{
				if(line_prefix)
					fprintf(stream, "%s%s\n", line_prefix, str.c_str());
				else
					fprintf(stream, "%s\n", str.c_str());
			}
		}
	}
}

inline void replace_codeblock(string& s){
	smatch mr;
	regex rgx(R"(\bCODE_(NOT|FOR|ERR)(\w+)\((.*)\))");
	while(regex_search(s, mr, rgx)){
		string tmp = s.substr(0, mr.position()) + '{' + mr[3].str() + '}' + s.substr(mr.position() + mr.length());
		if(mr[1].str().compare("FOR") == 0){
			if(mr[2].str().compare("m") == 0){
				s = tmp + "/*for msvc*/";
			}else if(mr[2].str().compare("g") == 0){
				s = tmp + "/*for gcc*/";
			} else if(mr[2].str().compare("k") == 0){
				s = tmp + "/*for clang*/";
			}else {
				s = tmp + "/*for " + mr[1].str() + "*/";
			}
		}else if(mr[1].str().compare("NOT") == 0){
			if(mr[2].str().compare("m") == 0){
				s = tmp + "/*not for msvc*/";
			}else if(mr[2].str().compare("g") == 0){
				s = tmp + "/*not for gcc*/";
			} else if(mr[2].str().compare("k") == 0){
				s = tmp + "/*not for clang*/";
			}else {
				s = tmp + "/*not for " + mr[1].str() + "*/";
			}
		} else {
			if(mr[2].str().compare("c") == 0){
				s = tmp + "/*compile error*/";
			} else {
				s = tmp + "/*error for " + mr[1].str() + "*/";
			}
		}
	}
}
void print_srcfile(FILE* stream, const char* srcfile, file_oneline sec){
	vector<string>& is = get_source(srcfile);
	// The function getline returns false if there are no more lines.
	i64 l = 0;
	regex rgx(R"(^(.*?)((TRACE|HEAD|NOTICE|PRINT|HORIZONTAL|REFERENCE|ANNOTATE|MANUAL|EXPLAIN)\w*)((.*\)\s*)(;|\/\/)\s*(.*)){0,1})"); // mr[6]=>some useful after the tag
	cmatch mr;
	for(std::string str : is) {
		l++;
		if(l == sec.pos1){
			if(regex_search(str.c_str(), mr, rgx)){
				auto s = mr[1].str(); virya::trim(s); replace_codeblock(s);
				fprintf(stream, sec.fmt, s.c_str());
				//  "TRACE(xxx): // test" => mr[5]: xxx, mr[6]: //, mr[7]: test
				if(sec.trailing_flag == 'c'){
					auto s = mr[7].str(); virya::trim(s, " ");
					if(s.length()){
						fprintf(stream, "// %s", s.c_str());
					}
				}
			}else{
			}
			break;
		}
	}
}
void print_srcfile(FILE* stream, const char* srcfile, file_trailing_comment sec){
	vector<string>& is = get_source(srcfile);
	i64 l = 0;
	regex rgx(R"(\/\/\s*(.*)$)"); 
	regex rgx2(R"(`0\{(\d+)(t{0,1})\}`)");      
	cmatch mr;
	for(std::string str : is) {
		l++;
		if(l == sec.pos1){
			if(regex_search(str.c_str(), mr, rgx)){
				auto s = mr[1].str(); virya::trim(s, " ");
				if(regex_search(s.c_str(), mr, rgx2)){
					if(mr[2].matched){
						int len = atoi(mr[1].str().c_str());
						for(int n = 0; n < len; n++){
							fprintf(stream, "%c", '\t'); 
						}
					}else{
						fprintf(stream, (string("%") + mr[1].str() + string("s")).c_str(), " ");
					}
					s = regex_replace(s, rgx2, string("")); virya::trim(s, " ");
				}
				if(s.length()){
					fprintf(stream, "// %s\n", s.c_str());
				}else{
					fprintf(stream, "\n");
				}
			}else{
				fprintf(stream, "\n");
			}
			break;
		}
	}
}
void print_srcfile(FILE* stream, const char* srcfile, file_oneexpression sec){
	vector<string>& is = get_source(srcfile);
	i64 l = 0;
	regex rgx(R"((\/\/)\s*(.+))");
	regex rgx2(R"(\?(\w+))");
	cmatch mr;
	for(std::string str : is) {
		l++;
		if(l == sec.pos1){
			string txt1; // leading content to print   //CODECOPY:prepare_expression_txt1 BEGIN
			if(regex_match(sec.delimiter, mr, rgx2)){
				auto rslt = str.find(mr[1].str());
				if(rslt == string::npos){
					txt1 = str;
				}else{
					txt1 = str.substr(0, rslt).c_str();
					// convert "...>>" to "...  "
					bool found = false;
					for(auto it = txt1.rbegin(); it != txt1.rend(); it++){
						if(*it == ' ' || *it == '\t'){
							if(found)
								break;
						}else if(isalnum(*it) || *it == '_'){
							break;
						}else if( *it == ';'){
							*it = ' ';
							break;
						}else{
							*it = ' ';
							found = true;
						}
					}
				}
			}else{
				auto rslt = str.find(sec.delimiter);
				if(rslt == string::npos){
					txt1 = str;
				}else{
					txt1 = str.substr(0, rslt).c_str();
				}
			}
			auto len1 = txt1.length();
			virya::ltrim(txt1);                         //CODECOPY:prepare_expression_txt1 END
			fprintf(stream, sec.fmt, txt1.c_str());
			if(sec.trailing_flag=='c'){
				string txt2 = str.substr(len1); // second part of the line
				if(regex_search(txt2.c_str(), mr, rgx)){
					fprintf(stream, "// %s", mr[2].str().c_str());
				}
			}
			break;
		}
	}
}
/**
NAME
    TRAILING_FLAG_ES - control how to print expression
CATEGORY
	0 - apppend nothing after the expression
    c - append comment  after the expression
    l - if there's comment, append comment; else append compilor requirements(such as gcc not support)
    L - if it is NOT for the current compiler, behave as l; else skip the line
REFERENCE
   COMPILER_COMPATIBLE
*/
void print_srcfile(FILE* stream, const char* srcfile, file_expressions sec){
	enum class compliance {
		NONE = 0,
		FORm,
		FORk,
		FORg,
		FORa,
		NOTm,
		NOTk,
		NOTg,
		NOTa,
	};
	auto to_string = [](compliance c)->string{
		switch(c){
		case compliance::FORm: return "only for msvc";
		case compliance::FORk: return "only for clang";
		case compliance::FORg: return "only for gcc";
		case compliance::FORa: return "for all compilers";
		case compliance::NOTm: return "not for msvc";
		case compliance::NOTk: return "not for clang";
		case compliance::NOTg: return "not for gcc";
		case compliance::NOTa: return "not for any complier";
		default: return "";
		}
	};
	auto match_block = [](string &str, const char*pattern)->compliance{ // match block
		smatch mr;
		if(regex_search(str, mr, regex(pattern))){
			if     (mr[1].str().compare("FORm") == 0){ return compliance::FORm; }
			else if(mr[1].str().compare("FORk") == 0){ return compliance::FORk; }
			else if(mr[1].str().compare("FORg") == 0){ return compliance::FORg; }
			else if(mr[1].str().compare("FORa") == 0){ return compliance::FORa; }
			else if(mr[1].str().compare("NOTm") == 0){ return compliance::NOTm; }
			else if(mr[1].str().compare("NOTk") == 0){ return compliance::NOTk; }
			else if(mr[1].str().compare("NOTg") == 0){ return compliance::NOTg; }
			else if(mr[1].str().compare("NOTa") == 0){ return compliance::NOTa; }
			else return compliance::NONE;
		}else{
			return compliance::NONE;
		}
	};
	auto is_compatible =[](compliance c)-> bool{
		switch(c){
		case compliance::FORm: return COMPILE_FORm ? true : false;
		case compliance::FORk: return COMPILE_FORk ? true : false;
		case compliance::FORg: return COMPILE_FORg ? true : false;
		case compliance::FORa: return true;
		case compliance::NOTm: return COMPILE_FORm ? false : true;
		case compliance::NOTk: return COMPILE_FORk ? false : true;
		case compliance::NOTg: return COMPILE_FORg ? false : true;
		case compliance::NOTa: return false;
		default: return false;
		}
	};
	
#define PATTERN_CODE ".*\\CODE_(\\w+)\\s*\\(\\s*$"
	vector<string>& is = get_source(srcfile);
	i64 l = 0;
	regex rgx(R"((\/\/)\s*(.+))");
	regex rgx2(R"(\?(\w+))");
	cmatch mr;
	if(sec.pos1 < 1 || sec.pos1 > is.size())
		return;
	auto print_ = [&rgx, &rgx2, &mr, &stream, &sec, &to_string](string & str, compliance c){// TODO, add flag to indicate for compiler
		string txt1; // leading content to print   //CODEPAST:prepare_expression_txt1 BEGIN tab-1
		if(regex_match(sec.delimiter, mr, rgx2)){
			auto rslt = str.find(mr[1].str());
			if(rslt == string::npos){
				txt1 = str;
			}else{
				txt1 = str.substr(0, rslt).c_str();
				// convert "...>>" to "...  "
				bool found = false;
				for(auto it = txt1.rbegin(); it != txt1.rend(); it++){
					if(*it == ' ' || *it == '\t'){
						if(found)
							break;
					}else if(isalnum(*it) || *it == '_'){
						break;
					}else if( *it == ';'){
						*it = ' ';
						break;
					}else{
						*it = ' ';
						found = true;
					}
				}
			}
		}else{
			auto rslt = str.find(sec.delimiter);
			if(rslt == string::npos){
				txt1 = str;
			}else{
				txt1 = str.substr(0, rslt).c_str();
			}
		}
		auto len1 = txt1.length();
		virya::ltrim(txt1);                          //CODEPAST:prepare_expression_txt1 END
		string append;
		if(sec.trailing_flag=='c' || sec.trailing_flag=='l' || sec.trailing_flag=='L' ){
			string txt2 = str.substr(len1); // second part of the line
			if(regex_search(txt2.c_str(), mr, rgx)){
				append = format("// %s", mr[2].str().c_str());
			}
		}
		if(                         sec.trailing_flag=='l' || sec.trailing_flag=='L' ){
			auto&& compliance = to_string(c); // compiler compliance annotation
			if(compliance.size() > 0){
				if(append.empty()){
					append = format("// %s", compliance.c_str());
				}
			}
		}
		if(strlen(sec.fmt) > 0){
			if(sec.fmt[strlen(sec.fmt) -1] == '\n'){
				if(append.empty())
					fprintf(stream, sec.fmt, txt1.c_str());
				else{
					string fmt = sec.fmt;
					fmt = fmt.substr(0, fmt.length() - 1);
					fmt += "%s\n";
					fprintf(stream, fmt.c_str(), txt1.c_str(), append.c_str());
				}
			}else{
				if(append.empty())
					fprintf(stream, sec.fmt, txt1.c_str());
				else{
					string fmt = sec.fmt;
					fmt += "%s";
					fprintf(stream, fmt.c_str(), txt1.c_str(), append.c_str());
				}
			}
		}else{
			if(append.empty())
				fprintf(stream, "%s\n", txt1.c_str());
			else
				fprintf(stream, "%s%s\n", txt1.c_str(), append.c_str());
		}
	};
	auto print_sec_ =[&is, &sec, &print_, &is_compatible](size_t from, size_t till, compliance c){
		if(sec.trailing_flag == 'L' && is_compatible(c)){
			return;
		}
		for(auto i = from; i <= till; i++){ print_(is[i], c); }
	};
	if(sec.pos2 != SIZE_MAX){
		for(size_t l = sec.pos1; l <= sec.pos2; l++){
			if(l>is.size()) { break; }
			auto&str = is[l-1];
			print_(str, compliance::NONE);
		}
	}else {// match CODE_FORx(...) or { #if COMPILE_FORx ... #endif }
		auto search_pre=[&is, &sec, &print_sec_, &match_block](){
			size_t till = sec.pos1 - 1;
			if(till == 0){return;}
			if(--till == 0){return;} // exclude boudary
			size_t from = SIZE_MAX;
			compliance c = compliance::NONE;
			for(size_t i = till; i > 0; i--){ // extremely, a bug
				auto&str=is[i];
				c = match_block(str, PATTERN_CODE);
				if(int(c)){
					from = i + 1;
					break;
				}
			}
			if(from == SIZE_MAX){return;}
			print_sec_(from, till, c);
		};
		auto search_nxt=[&is, &sec, &print_sec_](compliance c){
			size_t from = sec.pos1; // valid already
			size_t till = SIZE_MAX;
			for(size_t i = from; i < is.size(); i++){
				auto&str=is[i];
				if(regex_match(str, regex("\\s+\\).*"))){
					till = i - 1;
					break;
				}
			}
			if(till == SIZE_MAX){return;}
			print_sec_(from, till, c);
		};
		auto search_compile_if=[&is, &sec, &print_sec_, &match_block](){ // the block begin with #ifdef COMPILE*
			size_t till = sec.pos1 - 1;
			if(till == 0){return;}   // to array index
			if(--till == 0){return;} // exclude boudary
			if(!regex_match(is[till], regex("\\s*#endif\\b.*"))){
				return;
			}
			if(--till == 0){return;} // exclude boudary
			size_t from = SIZE_MAX;
			compliance c = compliance::NONE;
			for(size_t i = till; i > 0; i--){ // extremely, a bug
				c = match_block(is[i], "^\\s*#if\\s+COMPILE_(\\w+).*");
				if(int(c)){
					from = i + 1;
					break;
				}
			}
			if(from == SIZE_MAX){return;}
			print_sec_(from, till, c);
		};
		auto&str = is[sec.pos1 - 1];
		auto rslt1 = match_block(str, PATTERN_CODE);
		bool rslt2 = regex_match(str, regex("\\s*\\).*"));
		if(int(rslt1)){
			search_nxt(rslt1);
		}else if(rslt2){
			search_pre();
		}else{
			search_compile_if();
		}
	}
}
void print_manual( FILE* stream, const char* srcfile, const i64 pos, const char* funcsig, const char* section, const char* prefix){
	cmatch mr;
	if(regex_search(funcsig, mr, regex(R"((\w+)::main\()"))){
		print_manual_nm(stream, srcfile, pos, mr[1].str().c_str(), section, prefix);
	}else{
		print_manual_nm(stream, srcfile, pos, funcsig, section, prefix);
	}
}
void print_manual_nm( FILE* stream, const char* srcfile, const i64 pos, const char* entry_name, const char* section, const char* prefix){
	vector<string>& is = get_source(srcfile);
	regex rgx(R"(^\s*BEGIN_UNIT([_]?)\(\s*(\w+))");
	regex rgx_d1(R"(^\s*\/[\*]{2,}\s*(.*))"); // begin
	regex rgx_d2(R"(^(.*?)\s*[\*]{1,}/)");       // end
	smatch mr; i64 l = 0; bool start_unit=false; bool start_doc = false; bool start_sec = false; string tourgroup;
	for(std::string str : is) {
		if(++l >= pos){
			break;
		}
		if(tourgroup.empty() && regex_search(str, mr, regex(R"(^\s*#\s*define\s+TOUR_GROUP\s(\w+))"))){
			tourgroup = mr[1].str();
			continue;
		}
		if(regex_search(str, mr, rgx)){// match test unit
			auto name = mr[2].str();
			if(mr[1].length()){
				name = tourgroup + name;
			}
			if(name.compare(entry_name) == 0){
				start_unit=true;
				//printf("MatchedUnit:%s lineno:%zd\n", name.c_str(), l);
			}
		}
		if(!start_unit)
			continue;

		if(regex_search(str, mr, rgx_d1)){
			start_doc = true;
			//printf("MatchedDoc:%zd\n", l);
			str = mr[1].str();
			if(str.empty())
				continue;
		}

		if(!start_doc)
			continue;

		auto print_ =[&str, &section, &start_sec, &mr](){
			if(section != nullptr && strlen(section) > 0){
				if(!start_sec){
					if(regex_search(str, mr, regex(R"(^(\w+))"))){
						if(mr[1].str().compare(section) == 0){
							start_sec = true;
						}else{
							return;
						}
					} else{
						return;
					}
				}else{
					if(regex_search(str, mr, regex(R"(^(\w+))"))){
						start_sec = false;
						return;
					}
				}
			}
			printf("%s\n", str.c_str());
		};
		if(regex_search(str, mr, rgx_d2)){
			start_doc = false;
			str = mr[1].str();
			if(str.empty())
				continue;
			print_();
		}
		if(start_doc){
			print_();
		}
	}
}



}//namespace virya
