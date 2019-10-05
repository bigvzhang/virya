#pragma once

#if defined(_WIN32) || defined(_WIN64)
	#define MR_COMMON_FUNCS "MR_COMMON_FUNCS_WINDOWS"
#else
	#define MR_COMMON_FUNCS "MR_COMMON_FUNCS_LINUX"

#endif
#include "MRCommon.h"
#include "MRBaseEnm.h"

#include <iostream>
#include <sstream>
#include <string>
#include <stdio.h>
#include <stdarg.h>

#include <algorithm>
#include "MRException.h"



namespace muranbase{
	using namespace muranexception;
	using namespace std;

	//const char* format_double_p(double *pDouble);
	//const char* format_double(double pDouble);
	#define EMPTY_STRING_ERROR 0
	vector<string>  tokenize(const string& src, const string& tok,     bool   trim     = false, string null_subst = "" );
	vector<string>     split(const string& src, const string& delimit, bool drop_null  = false, string null_substr = "");
	bool       contains_word(const string & s1, const string& s2);
	bool       contains_char(const string &s1, char c);
	bool      isParameterSet(string & s, const char *strParamterName,  bool deleteParameter = true);
	bool   isIntParameterSet(string & s, bool deleteParameter, int& v);
	string popRegexParameter(string & s, const char *regParameter, size_t _Sub = 1); // return submatch _Sub
	pair<bool, int>    popRegexParameterAsInt(string & s, const char *regParameter, size_t _Sub);
	pair<bool, i64>    popRegexParameterAsInt64(string & s, const char *regParameter, size_t _Sub);
	pair<bool, double> popRegexParameterAsDouble(string & s, const char *regParameter, size_t _Sub);
	pair<bool, string> popRegexParameterAsOptionStr(string & s, const char *regParameter, size_t _Sub); // The Whole String matched, it return ture, sub possibly be empty
	vector<string>  popRegexMatchs(string & s, const char *regParameter); // return submatch _Sub
	int        popRegexParameterOptionalInt(string & s, const char *regParameter, size_t _Sub, int matched_d, int nonmatched_d); // [--trace-step=>1][--trace-step 2=>2][None=>0]
	bool       popParameter(string & s, const char *strParameterName, PARAMETER_PRIMITIVE_TYP parmater_typ, void*, bool mandatory = false, bool deleteParameter = true);
	bool       verify_single_choice(vector<bool> list);

	bool       str_lead_with(const char* s1, const char* s2);
	bool       str_end_with(const char* s1, const char* s2);
	bool       str_case_lead_with(const char* s1, const char* s2);
	bool       str_case_end_with(const char* s1, const char* s2);

	void setPrimitiveValue(const char* s, PARAMETER_PRIMITIVE_TYP parameter_typ, void* output_content);


	bool is_char_number(char c);
	bool is_char_float(char c);
	bool is_str_number(const char*);
	bool is_str_integer(const char*);
	bool is_str_float(const char*);
	int my_atoi(const char* info);
	int my_atoi(const char* info, bool throwable);
	size_t my_atoui(const char* info);
	size_t my_atoui(const char* info, bool throwable);
	double my_atof(const char* info);
	i64 my_atoint64(const char* info);
	string  my_int64toa(i64);
	bool my_atobool_throwable(const char* info, bool throwable);

	inline void string_erase(string & input, const string what, bool erase_all=true){
		for(size_t found = input.find(what); found != string::npos; found = input.find(what)){
			input.erase(found, what.length());
			if(!erase_all){
				break; // break here
			}
		}
	}

	inline int is_whitespace(const int ch){
		return strchr(" \t\r\n", ch) != NULL;
	}

	inline int is_alpha(const int ch){
		return (ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z');
	}

	inline int is_digit(const int ch){
		return (ch >= '0' && ch <= '9');
	}

	inline static	int is_wordchar(const int ch){
		return (ch == '_') || is_alpha(ch) || is_digit(ch);
	}

	inline int is_empty_str(const char *str){
		const char *p = str;
		while(*p && is_whitespace(*p)){
			p++;
		}
		return *p == '\0';
	}

	inline static char * ltrim_cstr(char *str){
		char *p = str;
		while(*p && is_whitespace(*p)){
			p++;
		}
		return p;
	}

	inline char * rtrim_cstr(char *str){
		char *p;
		p = str + strlen(str) - 1;
		while(p >= str && is_whitespace(*p)){
			p--;
		}
		*(p + 1) = '\0';
		return str;
	}

	inline char * trim_cstr(char *str){
		char *p;
		p = ltrim_cstr(str);
		rtrim_cstr(p);
		return p;
	}


	inline string& replace_all(string& str, const string& old_value, const string& new_value){
		string::size_type  new_len = new_value.length();
		string::size_type old_len = old_value.length();
		string::size_type pos(0);

		while(true){
			if((pos = str.find(old_value, pos)) != string::npos){
				str.replace(pos, old_len, new_value);
				pos += new_len;
			} else
				break;
		}
		return str;
	}


	inline string to_lowercase(const string & sourceString ){
		std::string destinationString;
		destinationString.resize(sourceString.size());
		std::transform(sourceString.begin(),
			sourceString.end(),
			destinationString.begin(),
			::tolower);
		return destinationString;
	}



	inline string& cstr_date_add_dash(string& str){
		if(str.length() != 8){
			return str;
		}else{
			string s1 = str.substr(0,4);
			string s2 = str.substr(4,2);
			string s3 = str.substr(6,2);
			str = s1 + "-" + s2 + "-" + s3;
		}   
		return str;   
	}  


	inline string&  operator %= (string& src, char c){
		//string::size_type len = src.length();
		string::size_type pos = string::npos;
		for(string::size_type i=0; src[i] == c; i++ ){
			pos++;
		}
		if(pos != string::npos){
			src = src.substr(pos+1);
		}
		return src;
	}

	inline string&  operator /= (string& src, char c){
		string::size_type len = src.length();
		string::size_type pos = string::npos;
		for(string::size_type i=len-1; src[i] == c; i-- ){
			pos=i;
		}
		if(pos != string::npos){
			src = src.substr(pos+1);
		}
		return src;
	}

	inline string&  operator -= (string& src, char c){
		src /= c %= c;
		return src;
	}

	//inline string&  operator -= (string& str, const string& old_value, const string& new_value){   
	//	while (true ){   
	//		string::size_type   pos(0 );   
	//		if ((pos= str.find(old_value)) != string::npos   )   
	//			str.replace(pos,old_value.length(),new_value);   
	//		else
	//			break ;   
	//	}   
	//	return str;   
	//}





	inline string& operator ^ (string& src, char c){
		return src;
	}

	int execute_prog(const char* input_command, const char* name,  int (*f)(int, char**));



	void inline copy_cstr(char ** pStr,  char * source, bool clone = false){
		if(source == NULL){
			throw MuRanExceptionCStrNull();
		}

		if(clone){
			if(*pStr != nullptr){ // delee the old value first
				delete *pStr;
				*pStr = nullptr;
			}
			*pStr = new char[strlen(source) + 1];
			strcpy(*pStr, source);
		}else{
			*pStr = source;
		}
	}

	void inline copy_const_cstr(char ** pStr, const char * source){
		if(source == NULL){
			throw MuRanExceptionCStrNull();
		}

		if(*pStr != nullptr){ // delee the old value first
			delete *pStr;
			*pStr = nullptr;
		}
		*pStr = new char[strlen(source) + 1];
		strcpy(*pStr, source);

	}

	void inline str_pack(char* str, unsigned char * source, size_t size){
		//stringstream ss;  
		for(size_t i =0 ;i < size; i++){
			unsigned int c = source[i];
			sprintf(&str[i*2], "%02x", c);
			//ss << hex << c;  
		}
		//ss >> str;
	}

	void inline str_unpack(unsigned char* str, char * source, size_t size){
		// output it as a signed type  
		//std::cout << static_cast<int>(x) << std::endl;  
		   unsigned int x;     
		for(size_t i =0 ;i < size; i++){
			stringstream ss;  
			ss << hex << source[2*i] << source[2*i+1];  
			ss>> x;
			str[i] = x;
		}
	}


	inline void string_set_to_N_char(string& empty_line, size_t N, char v){
		empty_line.resize(N+1);
		for(size_t t = 0; t<N; t++){
			empty_line[t] = v;
		}
		empty_line[N] = '\0';
	}

#if defined(_WIN32) || defined(_WIN64)
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
			+ 1 // terminating '\0'
			;
		s.resize(len);
		vsprintf_s((char*)s.c_str(), s.size(), fmt, args);
		if(s[s.size() - 1] == '\0'){
			s.resize(len -1);
		}
		return s;
	}

	char* vbuffer_format(const char* fmt, va_list  args);


#elif defined(__CYGWIN__)
#define xfree_ptr(TAG,p)            {delete[]p;}
#define vasprintf(buffer, fmt, args) {             \
    auto nsize = vsnprintf(nullptr, 0, fmt, args);\
    if(nsize>0){                                     \
        buffer = new char[nsize+1];                \
        nsize = vsnprintf(buffer, nsize, fmt, args);  \
    }}
	
	void inline vformat(string& s, const char* fmt, va_list  args){
		char* ptr = nullptr;
		vasprintf (ptr, fmt, args);
		if(ptr !=nullptr){
			s = ptr;
			xfree_ptr(CHAR_STR, ptr);
		}else{
			s.resize(0);
		}
	}

	string inline vformat(const char* fmt, va_list  args){
		char* ptr = nullptr;
		vasprintf (ptr, fmt, args);
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
		vasprintf (ptr, fmt, args);
		if(ptr !=nullptr){
		}
		return ptr;
	}
#undef xfree_ptr
#else
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

	string inline vformat(const char* fmt, va_list  args){
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

	inline const string trim_all(const char * instrumentID){
		string s = instrumentID;
		remove(s.begin(), s.end(), ' ');
		return s;
	}

	inline const string LTrim(const string& str){
		auto pos1 = str.find_first_not_of(" \n\r\t");
		if(pos1 == string::npos){
			return "";
		}
		return str.substr(pos1);
	}

	inline const string RTrim(const string& str){
		auto pos1 = str.find_last_not_of(" \n\r\t"); 
		if(pos1 == string::npos){
			return "";
		}
		return str.substr(0, pos1+1);
	}

	inline const string Trim(const string& str){
		auto pos1 = str.find_first_not_of(" \n\r\t");
		if(pos1 == string::npos){
			return "";
		}
		auto pos2 = str.find_last_not_of(" \n\r\t");
		if(pos2 == string::npos){
			return "";
		}
		return str.substr(pos1, pos2 - pos1 + 1);
	} 


	inline void SlfLTrim(string& str){
		auto pos1 = str.find_first_not_of(" \n\r\t");
		if(pos1 == string::npos){
			return ;
		}
		str = str.substr(pos1);
	}

	inline void SlfRTrim(string& str){
		auto pos1 = str.find_last_not_of(" \n\r\t"); 
		if(pos1 == string::npos){
			return ;
		}
		str = str.substr(0, pos1+1);
	}

	inline void SlfTrim(string& str){
		auto pos1 = str.find_first_not_of(" \n\r\t");
		if(pos1 == string::npos){
			str = "";
			return;
		}else{
			str.replace(0, pos1, "");
		}
		auto pos2 = str.find_last_not_of(" \n\r\t");
		if(pos2 == string::npos){
			
		}else{
			str = str.substr(0,pos2+1);
		}
	}


	//void inline delete_ptr(void **p){
	//	if(*p == NULL){
	//		throw MuRanExceptionPtrNull();
	//	}

	//	if(*p == NULL){
	//		throw MuRanExceptionPtrNull();
	//	}
	//	try{
	//		delete *p;
	//	}catch(...){
	//		throw MuRanExceptionPtrNull();
	//	}

	//	*p = NULL;
	//}



	inline char* buffer_format(const char* fmt, ...){
		va_list args;
		va_start (args, fmt);
		char* s = vbuffer_format(fmt, args);
		va_end (args);
		return s;
	}

	inline string format(const char* fmt, ...){
		string s;
		va_list args;
		va_start (args, fmt);
		vformat(s, fmt, args);
		va_end (args);
		return s;
	}

	string info_format(const char* fmt, ...);

	void inline format(string& s, const char* fmt, ...){
		va_list args;
		va_start (args, fmt);
		vformat(s, fmt, args);
		va_end (args);
	}

	
	inline string merge_vct_string(vector<string>& columns){
		string option_str;
		for(auto it = columns.begin(); it != columns.end(); it++){
			if(option_str.length() == 0){
				option_str = *it;
			} else{
				option_str = format("%s %s", option_str.c_str(), it->c_str());
			}
		}
		return option_str;
	}

	union chr_dbl{
		char c[8];
		double d;
		chr_dbl(char*p){
			strcpy_s(c,8,p);
		}
	};


	#define BUFSIZE 512
	inline bool read_line(FILE * fp, string & s){
		int length = 0;
		char  ch = getc(fp);
		for(; ch != '\n' && ch != EOF;){
			char buf[BUFSIZE + 1];
			int i = 0;
			for (; ch != '\n' && ch != EOF && i < BUFSIZE; length++, ch=getc(fp) ) {
				buf[i++] = ch;
			}
			buf[i] = '\0';
			s += buf;
		}
		return ch != EOF;
	}
#undef BUFSIZE


	//inline bool ifset(int val, int tag){
	//	return (val & tag) != 0; 
	//}

	inline string toStringDouble(const double d, const char * fmt = "%9.2f"){
		if(d == DBL_MAX){
			return "DMax";
		}else if(d==DBL_MIN){
			return "DMin";

		}else{
			return format(fmt, d);
		}
	}




	inline bool is_the_str_uint(const char* s){
		cmatch mr;
		regex rgx("^\\d+$");
		for(unsigned int npos = 0; regex_search(s + npos, mr, rgx);){
			return true;
		}
		return false;
	}

	inline bool is_the_str_int(const char* s){
		cmatch mr;
		regex rgx("[\\-]{0,1}\\d+$");
		for(unsigned int npos = 0; regex_search(s + npos, mr, rgx);){
			return true;
		}
		return false;
	}

	inline bool is_the_str_float(const char* s){
		cmatch mr;
		regex rgx("^[\\-]{0,1}\\d*\\.\\d+$");
		for(unsigned int npos = 0; regex_search(s + npos, mr, rgx);){
			return true;
		}
		return false;
	}

	inline bool is_the_str_real_number(const char* s){
		if(strlen(s) == 0){
			return false;
		}
		cmatch mr;
		regex rgx("^[\\-]{0,1}\\d*(\\.){0,1}\\d*$");
		for(unsigned int npos = 0; regex_search(s + npos, mr, rgx);){
			return true;
		}
		return false;
	}
	
	inline bool is_regex_standard_word_char(char x){
		if((x >= 'a' && x <='z') || x=='_' || (x >= 'A' && x <='Z') || (x >= '0' && x <= '9') ){
			return true;
		}else{
			return false;
		}
	}

	inline string cvt_std_args_to_string(int param__argc, char* param__argv[]){
		string s ;
		for(int i = 0; i < param__argc; i++){
			if(i == 0){
				s = param__argv[0];
			}else{
				s +=  ' ';
				s += param__argv[i];
			}
		}
		return s;
	}



	inline void  intToBytes(int i,char *bytes,int size = 4)
	{
		//byte[] bytes = new byte[4];
		memset(bytes,0,sizeof(char) *  size);
		bytes[0] = (char) (0xff & i);
		bytes[1] = (char) ((0xff00 & i) >> 8);
		bytes[2] = (char) ((0xff0000 & i) >> 16);
		bytes[3] = (char) ((0xff000000 & i) >> 24);
		return ;
	}

	//byteתint
	inline int bytesToInt(char* bytes,int size = 4) 
	{
		int addr = bytes[0] & 0xFF;
		addr |= ((bytes[1] << 8) & 0xFF00);
		addr |= ((bytes[2] << 16) & 0xFF0000);
		addr |= ((bytes[3] << 24) & 0xFF000000);
		return addr;
	}


	template <class A> 	bool vector_erase(vector<A> & v, A& m){
		for(auto it = v.begin(); it != v.end(); it++){
			if(*it == m){
				v.erase(it);
				return true;
			}
		}
		return false;
	}


	template <class A> 	bool vector_erase_idx(vector<A> & v, size_t idx){
		auto it = v.begin();
		it += idx;
		if(it != v.end()){
			v.erase(it);
			return true;
		}else{
			return false;
		}
	}

	template <class A> 	bool vector_exist(vector<A> & v, A& m){
		for(auto it = v.begin(); it != v.end(); it++){
			if(*it == m){
				return true;
			}
		}
		return false;
	}

	template <class A> 	bool vector_uniq_exist(vector<A> & v, A& m){
		int cnt = 0;
		for(auto it = v.begin(); it != v.end(); it++){
			if(*it == m){
				cnt++;
			}
		}
		if(cnt == 1)
			return true;
		else
			return false;
	}



	template <class A> 	bool vector_insert_uniq(vector<A> & v, A& m){
		for(auto it = v.begin(); it != v.end(); it++){
			if(*it == m){
				return true;
			}
		}
		v.push_back(m);
		return false;
	}

	template<class X> 
	char get_greator_less(X x1, X x2){
		if(x1 > x2){
			return '>';
		}else if( x1 < x2 ) {
			return '<';
		}else{
			return '=';
		}
	}

	inline const char* toCStr(bool x){
		if(x){
			return "True";
		}else{
			return "False";
		}
	}

	int numberInTailOfString(const char* s);


	inline bool leading_str_equal(const char *s1, const char* s2, size_t len){
		if(strlen(s1) < len || strlen(s2) < len){
			return false;
		}
		for(size_t pos = 0; pos < len; pos++){
			if(s1[pos] != s2[pos]){
				return false;
			}
		}
		return true;
	}

	inline bool are_bytes_equal(const void*x1, const void* x2, size_t len){
		for(size_t i = 0; i < len; i++){
			if(((const char*)x1)[i] != ((const char*)x2)[i]){
				return false;
			}
		}
		return true;
	}

	const char* toStringIsNull(const void * p);
	const char* toStringIsNull2(const void * p);

	char* muran_clone_str(const char* source);

}
