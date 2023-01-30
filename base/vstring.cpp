//
// Copyright (c) 2019-2020 Vic Zhang(VicBig at qq dot com)
//
// Distributed under the GNU General Public License, Version 3.(Please see
// more information at https://www.gnu.org/licenses/)
//
// Official repository: https://github.com/bigvzhang/vhttp
//
#include <cstdarg>
#include <cstring>
#include <iostream>
#include "vstring.h"
#include "vmacro.h"
using std::strlen;
using std::vector;
using std::basic_string;

#if defined(_WIN32) || defined(_WIN64)
#define REGEX_POSITION_FIRST 0
//#define strcasecmp stricmp
//#define strncasecmp strnicmp
#else
#define REGEX_POSITION_FIRST (unsigned long int)0L
#define stricmp  strcasecmp
#define strnicmp strncasecmp
#endif

namespace virya{


#if defined(_WIN32)
void inline vformat(string& s, const char* fmt, va_list  args){
	size_t len = _vscprintf( fmt, args ) // _vscprintf doesn't count
		+1								// terminating '\0'
		;
	s.resize(len);
	vsprintf_s((char*)s.c_str(), s.size(), fmt, args);
	if(s[s.size() - 1] == '\0'){
		s.resize(len -1);
	}
}

string inline vformat(const char* fmt, va_list  args){
	string s;
	size_t len = _vscprintf( fmt, args ) // _vscprintf doesn't count
		+ 1                              // terminating '\0'
		;
	s.resize(len);
	vsprintf_s((char*)s.c_str(), s.size(), fmt, args);
	if(s[s.size() - 1] == '\0'){
		s.resize(len -1);
	}
	return s;
}

char* vbuffer_format(const char* fmt, va_list  args);


#else
#if defined(__CYGWIN__) && ! __GNU_VISIBLE
inline void vasprintf(char** buffer, const char* fmt, va_list  arg_ptr){
	#define  VASPRINTF_BUFFER 16
	*buffer = (char*) malloc(VASPRINTF_BUFFER);
	if(!(*buffer)){
		return;
	}
	int len = vsnprintf(*buffer, VASPRINTF_BUFFER, fmt, arg_ptr);
	if(len >=  VASPRINTF_BUFFER){                  // must be ge(greator or equal)
		len += 1;                                  // must plus 1
		*buffer = (char*)realloc(*buffer, len);
		if(!(*buffer)){
			return;
		}
		vsnprintf(*buffer, len, fmt, arg_ptr);
	}
	#undef  VASPRINTF_BUFFER
}
#endif

#define xfree_ptr(TAG,p)              {if(p != nullptr) { free(p); p = nullptr;}}
void inline vformat(string& s, const char* fmt, va_list  args){
	char* ptr = nullptr;
	vasprintf (&ptr, fmt, args);
	if(ptr !=nullptr){
		s = ptr;
		xfree_ptr(CHAR_STR, ptr);
	}else{
		s.resize(0);
	}
}

inline string vformat(const char* fmt, va_list  args){
	char* ptr = nullptr;
	vasprintf (&ptr, fmt, args);
	if(ptr !=nullptr){
		string s = ptr;
		xfree_ptr(CHAR_STR, ptr);
		return s;
	}else{
		return string();
	}
}

inline char* vbuffer_format(const char* fmt, va_list  args){
	char* ptr = nullptr;
	vasprintf (&ptr, fmt, args);
	if(ptr !=nullptr){
	}
	return ptr;
}
#undef xfree_ptr
#endif


inline char* buffer_format(const char* fmt, ...){
	va_list args;
	va_start (args, fmt);
	char* s = vbuffer_format(fmt, args);
	va_end (args);
	return s;
}

// Return a std::string with formatted data
string format(const char* fmt, ...){
	string s;
	va_list args;
	va_start (args, fmt);
	vformat(s, fmt, args);
	va_end (args);
	return s;
}


// Write formatted data to std::string
void format(string& s, const char* fmt, ...){
	va_list args;
	va_start (args, fmt);
	vformat(s, fmt, args);
	va_end (args);
}

// Check if all the characters in the string is decimal digit
bool isdigit(const char* str){
	size_t len = strlen(str);
	if(len == 0){
		return false;
	}
	for(size_t i = 0; i < len; i++){
		if(str[i] < '0' || str[i] > '9' ){//!std::isdigit(str[i])){
			return false;
		}
	}
	return true;
}

#pragma warning( push )
#pragma warning( disable: 4996)  // skip warning of strcpy
char* clone_str(const char* source){
	char * pStr = new char[strlen(source) + 1];
	if(!pStr)
		return nullptr;
	strcpy(pStr, source);
	return pStr;
}
#pragma warning( pop )


vector<string> split(const string &src, const string& delimit, bool drop_null, const string null_as_string){
	if( src.empty() || delimit.empty() )
		throw EMPTY_STRING_ERROR;
	vector<string> rtnVctString;
	basic_string<char>::size_type deli_len = delimit.size();
	string::size_type index = string::npos, last_search_position = 0;
	while( (index=src.find(delimit, last_search_position)) != string::npos ){
		if( index == last_search_position){
			if(!drop_null)
				rtnVctString.push_back( null_as_string );
		} else {
			rtnVctString.push_back( src.substr(last_search_position, index - last_search_position) );
		}
		last_search_position = index + deli_len;

	}
	{
		string last_one = src.substr(last_search_position);
		if(last_one.empty()){
			if(!drop_null){
				rtnVctString.push_back(null_as_string);
			}
		}else{
			rtnVctString.push_back(last_one);
		}
	}
	return rtnVctString;
}

bool str_lead_with(const char*s1, const char* s2){
	int n1 = strlen(s1);
	int n2 = strlen(s2);
	if(n1 < n2){
		return false;
	}
	for(int i = 0; i < n2 ; i++){
		if(s1[i] != s2[i]){
			return false;
		}
	}
	return true;
}

bool str_i_lead_with(const char*s1, const char* s2){
	int n1 = strlen(s1);
	int n2 = strlen(s2);
	if(n1 < n2){
		return false;
	}
	return strnicmp(s1, s2, n2) == 0;
}

bool str_end_with(const char*s1, const char* s2){
	int n1 = strlen(s1);
	int n2 = strlen(s2);
	if(n1 < n2){
		return false;
	}
	for(int i = 0; i < n2 ; i++){
		if(s1[n1 - n2 + i] != s2[i]){
			return false;
		}
	}
	return true;
}

bool str_i_end_with(const char*s1, const char* s2){
	int n1 = strlen(s1);
	int n2 = strlen(s2);
	if(n1 < n2){
		return false;
	}
	return strnicmp(s1 + n1 -n2, s2, n2) == 0;
}

string LTrim(const string& str, const char* x){
	auto pos1 = str.find_first_not_of(x);
	if(pos1 == string::npos){
		return "";
	}
	return str.substr(pos1);
}

string RTrim(const string& str, const char* x){
	auto pos1 = str.find_last_not_of(x);
	if(pos1 == string::npos){
		return "";
	}
	return str.substr(0, pos1+1);
}

string Trim(const string& str, const char* x){
	auto pos1 = str.find_first_not_of(x);
	if(pos1 == string::npos){
		return "";
	}
	auto pos2 = str.find_last_not_of(x);
	if(pos2 == string::npos){
		return "";
	}
	return str.substr(pos1, pos2 - pos1 + 1);
}


void SlfLTrim(string& str, const char* x){
	auto pos1 = str.find_first_not_of(x);
	if(pos1 == string::npos){
		return ;
	}
	str = str.substr(pos1);
}

void SlfRTrim(string& str, const char* x){
	auto pos1 = str.find_last_not_of(x);
	if(pos1 == string::npos){
		return ;
	}
	str = str.substr(0, pos1+1);
}

void SlfTrim(string& str, const char* x){
	auto pos1 = str.find_first_not_of(x);
	if(pos1 == string::npos){
		str = "";
		return;
	}else{
		str.replace(0, pos1, "");
	}
	auto pos2 = str.find_last_not_of(x);
	if(pos2 == string::npos){
		
	}else{
		str = str.substr(0,pos2+1);
	}
}

string TrimCStr(const char * content, const char* x) {
	string s = content;
	SlfTrim(s, x);
	return s;
}

string LTrimCStr(const char * content, const char* x) {
	string s = content;
	SlfLTrim(s, x);
	return s;
}

string RTrimCStr(const char * content, const char* x) {
	string s = content;
	SlfRTrim(s, x);
	return s;
}

} // end namespace virya



#include "vioman.h" // defined here
namespace virya{

void ioq_base::printf(const char* fmt, ...){
	string s;
	va_list args;
	va_start(args, fmt);
	vformat(s, fmt, args);
	va_end(args);
	if(this->data.size() == 0){
		data.push_back(s);
	}else{
		auto last = this->data.size() - 1;
		if(data[last].length() == 0 || data[last].length() > 0 && data[last][data[last].length() - 1] != '\n'  ){ // append to the last content
			data[last]+=s;
		}else{
			data.push_back(s);
		}
	}
}

void ioq_base::print(const char* fmt, ...){
	string s;
	va_list args;
	va_start(args, fmt);
	vformat(s, fmt, args);
	va_end(args);
	s+='\n'; // only have this line comparing with ioq_base::printf
	if(this->data.size() == 0){
		data.push_back(s);
	}else{
		auto last = this->data.size() - 1;
		if(data[last].length() == 0 || data[last].length() > 0 && data[last][data[last].length() - 1] != '\n'  ){ // append to the last content
			data[last]+=s;
		}else{
			data.push_back(s);
		}
	}
}

void ioq_base::clear(){
	for(auto s : data){
		std::cout << prompt << s;
	}
	data.clear();
}
} // end namespace virya



