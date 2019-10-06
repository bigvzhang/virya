#include "MuRanCommonFuncs.h"


namespace muranbase{
static const 	basic_string<char>::size_type INVALID_POS = -1;




bool is_char_number(char c){
	if(c >='0' && c <= '9')
		return true;
	else
		return false;
}

bool is_char_float(char c){
	if(c >='0' && c <= '9')
		return true;
	else
		return false;
	switch(c){
	case '+':
	case '-':
	case '.':
		return true;
	default:
		return false;
	}
}

bool is_str_number(const char* info){
	size_t len = strlen(info);
	if(len == 0){
		return false;
	}
	for(size_t i = 0; i < len; i++){
		if(!is_char_number(info[i])){
			return false;
		}
	}
	return true;
}

bool is_str_integer(const char* info){
	size_t len = strlen(info);
	if(len == 0){
		return false;
	}
	for(size_t i = 0; i < len; i++){
		if(i == 0){
			if(info[0] == '-' || info[i] == '+'){
				if( len == 1){
					return false;
				}else{
					continue;
				}
			}else{
				if(!is_char_number(info[i])){
					return false;
				}
			}
		}else{
			if(!is_char_number(info[i])){
				return false;
			}
		}
	}
	return true;
}

bool is_str_float(const char* info){
	size_t len = strlen(info);
	if(len == 0){
		return false;
	}
	for(size_t i = 0; i < len; i++){
		if(!is_char_float(info[i])){
			return false;
		}
	}
	return true;
}

int my_atoi(const char* info){
	return atoi(info);
}
int my_atoi(const char* info, bool throwable){
	if(throwable){
		if(is_str_integer(info)){
			return atoi(info);
		}else{
			throw MuRanExceptionBadData();
		}
	}else{
		return atoi(info);
	}
}

size_t my_atoui(const char* info){
	return (size_t)atoi(info);
}
size_t my_atoui(const char* info, bool throwable){
	if(throwable){
		if(is_str_integer(info)){
			return (size_t)atoi(info);
		}else{
			throw MuRanExceptionBadData();
		}
	}else{
		return (size_t)atoi(info);
	}
}
double my_atof(const char* info){
	return atof(info);
}
#if defined(_WIN32) || defined(_WIN64)
i64 my_atoint64(const char* info){
	return _atoi64(info);
}
string  my_int64toa(__int64 i){
	return format("%lld", i);
}
#else
i64 my_atoint64(const char* info){
	return  strtol (info,     NULL, 10);
}
string  my_int64toa(i64 i){
	return format("%lld", i);
}
#endif

bool my_atobool_throwable(const char* info, bool throwable){
	if(stricmp(info, "true") == 0){
		return true;
	}
	if(stricmp(info, "false") == 0){
		return false;
	}
	if(throwable){
		throw MuRanExceptionBadData();
	}else{
		return false;
	}
}

vector<string> tokenize(const string& src, const string & tok, bool trim, string null_subst){
	vector<string> rtnVctString;
	if( src.empty() || tok.empty() ){
		return rtnVctString;
	}
	basic_string<char>::size_type pre_index = 0, index = 0, len = 0;
	while( (index = src.find_first_of(tok, pre_index)) != INVALID_POS ){
		if( (len = index-pre_index)!=0 )
			rtnVctString.push_back(src.substr(pre_index, len));
		else if(trim==false)
			rtnVctString.push_back(null_subst);
		pre_index = index+1;
	}
	string endstr = src.substr(pre_index);
	if( trim==false )
		rtnVctString.push_back( endstr.empty()?null_subst:endstr );
	else if( !endstr.empty() )
		rtnVctString.push_back(endstr);
	return rtnVctString;
}


vector<string> split(const string &src, const string& delimit, bool drop_null, const string null_as_string){
	if( src.empty() || delimit.empty() )
		throw EMPTY_STRING_ERROR;
	vector<string> rtnVctString;
	basic_string<char>::size_type deli_len = delimit.size();
	string::size_type index = INVALID_POS, last_search_position = 0;
	while( (index=src.find(delimit, last_search_position)) != INVALID_POS ){
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

bool contains_word(const string & s1, const string& s2){
	vector<string> words = tokenize(s1, " ");
	for(size_t i = 0; i < words.size();i++){
		if(s2.compare(words[i]) == 0){
			return true;
		}
	}
	return false;
}

bool contains_char(const string & s1,char c){
	vector<string> words = tokenize(s1, " ");
	for(size_t i = 0; i < s1.size();i++){
		if(s1[i] == c){
			return true;
		}
	}
	return false;
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

bool str_case_lead_with(const char*s1, const char* s2){
	int n1 = strlen(s1);
	int n2 = strlen(s2);
	if(n1 < n2){
		return false;
	}
	return strncasecmp(s1, s2, n2) == 0;
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

bool str_case_end_with(const char*s1, const char* s2){
	int n1 = strlen(s1);
	int n2 = strlen(s2);
	if(n1 < n2){
		return false;
	}
	return strncasecmp(s1 + n1 -n2, s2, n2) == 0;
}

bool isParameterSet(string & s, const char *strParameterName1, bool deleteParameter){
	//string strParameterName = format("\\b(%s)\\b", strParameterName1);
	string strParameterName = format("(^|\\s+)%s($|\\s+)", strParameterName1);
	

	if(deleteParameter){
		regex  rgx(strParameterName.c_str());
		string fmt=" ";
		string r = regex_replace(s, rgx, fmt);
		//my_prompt("Comp<%s:%s>", s.c_str(), r.c_str());
		if(r.compare(s) == 0){
			return false;
		}else{
			s = r;
			SlfTrim(s);
			return true;
		}
	}else{
		cmatch mr; 
		regex  rgx(strParameterName.c_str()); 
		for(int pos = 0; regex_search(s.c_str() + pos, mr, rgx); pos+=mr.position(REGEX_POSITION_FIRST) + mr.length()){
			//my_prompt("%s\n", mr.str().c_str());
			return true;
		}
		return false;
	}
}



bool isIntParameterSet(string & s, bool deleteParameter, int& v){
	//string strParameterName = format("\\b(%s)\\b", strParameterName1);
	string strParameterName = "(^|\\s+)-(\\d+)\\s*";


	bool rtnVal = false;
	cmatch mr; 
	regex  rgx(strParameterName.c_str()); 
	for(int pos = 0; regex_search(s.c_str() + pos, mr, rgx); pos+=mr.position(REGEX_POSITION_FIRST) + mr.length()){
		v = my_atoi(mr[2].str().c_str());
		rtnVal = true;
		break;
	}

	if(deleteParameter){
		regex  rgx(strParameterName.c_str());
		string fmt=" ";
		string r = regex_replace(s, rgx, fmt);
		//my_prompt("Comp<%s:%s>", s.c_str(), r.c_str());
		if(r.compare(s) == 0){
			// do nothing
		}else{
			s = r;
			SlfTrim(s);
		}
	}

	return rtnVal;
}

string popRegexParameter(string & s, const char *regParameter, size_t _Sub){ // return submatch _Sub
	cmatch mr; 
	regex  rgx(regParameter); 
	string r;
	if(regex_search(s.c_str(), mr, rgx)){
		r = mr[_Sub];
		s.replace(mr.position(), mr.length(), " ");
		SlfTrim(s);
	}
	return r;
}

vector<string> popRegexMatchs(string & s, const char *regParameter){ // return submatch _Sub
	cmatch mr; 
	regex  rgx(regParameter); 
	vector<string> r;
	if(regex_search(s.c_str(), mr, rgx)){
		r.reserve(mr.size() + 1);
		for(size_t i = 0; i <= mr.size(); i++){
			r.push_back(mr[i].str());
		}
		s.replace(mr.position(), mr.length(), " ");
		SlfTrim(s);
	}
	return r;
}

pair<bool, int> popRegexParameterAsInt(string & s, const char *regParameter, size_t _Sub){ // return submatch _Sub
	cmatch mr;
	regex  rgx(regParameter);
	string r;
	if(regex_search(s.c_str(), mr, rgx)){
		r = mr[_Sub];
		s.replace(mr.position(), mr.length(), " ");
		SlfTrim(s);
	}
	if(is_str_integer(r.c_str())){
		return pair<bool, int>(true, my_atoi(r.c_str()));
	} else{
		return pair<bool, int>(false, 0);
	}
}

pair<bool, i64> popRegexParameterAsInt64(string & s, const char *regParameter, size_t _Sub){ // return submatch _Sub
	cmatch mr;
	regex  rgx(regParameter);
	string r;
	if(regex_search(s.c_str(), mr, rgx)){
		r = mr[_Sub];
		s.replace(mr.position(), mr.length(), " ");
		SlfTrim(s);
	}
	if(is_str_integer(r.c_str())){
		return pair<bool, i64>(true, my_atoint64(r.c_str()));
	} else{
		return pair<bool, i64>(false, 0);
	}
}

pair<bool, double> popRegexParameterAsDouble(string & s, const char *regParameter, size_t _Sub){ // return submatch _Sub
	cmatch mr;
	regex  rgx(regParameter);
	string r;
	if(regex_search(s.c_str(), mr, rgx)){
		r = mr[_Sub];
		s.replace(mr.position(), mr.length(), " ");
		SlfTrim(s);
	}
	if(is_str_float(r.c_str())){
		return pair<bool, double>(true, my_atof(r.c_str()));
	} else{
		return pair<bool, double>(false, 0);
	}
}

pair<bool, string> popRegexParameterAsOptionStr(string & s, const char *regParameter, size_t _Sub){ // return submatch _Sub
	cmatch mr;
	regex  rgx(regParameter);
	string r;
	if(regex_search(s.c_str(), mr, rgx)){
		r = mr[_Sub];
		s.replace(mr.position(), mr.length(), " ");
		SlfTrim(s);
		return pair<bool,string>(true, r);
	}else{
		return pair<bool,string>(false, "");
	}
}
int  popRegexParameterOptionalInt(string & s, const char *regParameter, size_t _Sub, int matched_d, int nonmatched_d){
	// [--trace-step=>1][--trace-step 2=>2][None=>0]
	cmatch mr;
	regex  rgx(regParameter);
	if(regex_search(s.c_str(), mr, rgx)){ //General Matched
		int rtn;
		if(mr[_Sub].matched){ // SubMatched
			if(is_str_integer(mr[_Sub].str().c_str())){
				rtn = my_atoi(mr[_Sub].str().c_str());
			} else{
				throw MuRanExceptionBadDataIntegrity();
			}
		} else{
			rtn = matched_d; // Return Default
		}
		s.replace(mr.position(), mr.length(), " ");
		SlfTrim(s);
		return rtn;
	} else { // Matched 
		return nonmatched_d;
	}
}

bool verify_single_choice(vector<bool> list){
	int cnt = 0;
	for(auto it = list.begin(); it != list.end(); it++){
		if(*it){
			cnt++;
			if(cnt>1)
				return false;
		}
	}
	return true;
}

bool isSpaceChar(char c){
	switch(c){
	case ' ':
	case '\t':
	case '\r':
	case '\n':
		return true;
	default:
		return false;

	}

}
void setPrimitiveValue(const char* s, PARAMETER_PRIMITIVE_TYP parameter_typ, void* output_content){
	switch(parameter_typ){
	case PARAMETER_PRIMITIVE_TYP_INT:
		*((int*) output_content) = my_atoi(s);
		break;
	case PARAMETER_PRIMITIVE_TYP_INT64:
		*((i64*) output_content) = my_atoint64(s);
		break;
	case PARAMETER_PRIMITIVE_TYP_DOUBLE:
		*((double*) output_content) = my_atof(s);
		break;
	case PARAMETER_PRIMITIVE_TYP_STRING:
		*((string*) output_content) = s;
		break;
	case PARAMETER_PRIMITIVE_TYP_CHARBUF:
		strcpy((char*)output_content, s);
		break;
	case PARAMETER_PRIMITIVE_TYP_CHAR_PtrPtr:
		if(strlen(s) == 0){
			*((char**)output_content) = nullptr;
		}else{
			*((char**)output_content) = (char*) malloc(strlen(s) + 1);
			strcpy(*((char**)output_content), s);
		}
		break;
	default:
		throw MuRanExceptionBadEnum();
	}
}
bool  popParameter(string & s, const char *strParameterName1, PARAMETER_PRIMITIVE_TYP parameter_typ, void* output_content, bool mandatory, bool deleteParameter){
	string strParameterName = format("((^|\\s+)%s\\b\\s*)", strParameterName1);
	cmatch mr; 
	regex  rgx(strParameterName.c_str()); 
	string r;
	for(string::size_type pos = 0; regex_search(s.c_str() + pos, mr, rgx); pos+=mr.position(REGEX_POSITION_FIRST) + mr.length()){
		// we got parameter name
		int value_content_begin = -1;
		int value_content_end   = -1;
		// pop parameter value
		for(size_t pos = mr.position() + mr.length(); pos < s.length() ; pos++){
			if(isSpaceChar(s[pos])){
				if(value_content_begin == -1){
					continue;
				}else{
					break; // we have got all the content
				}
			}else{
				if(value_content_begin == -1){
					value_content_begin = pos;
					value_content_end   = pos;
				}else{
					value_content_end = pos;
				}
			}
		}
		bool rtn = false;
		if(value_content_begin != -1){
			string value_str = s.substr(value_content_begin, value_content_end - value_content_begin + 1);
			setPrimitiveValue(value_str.c_str(), parameter_typ, output_content);
			rtn = true;
			if(deleteParameter){
				r = mr[1];
				s.replace(mr.position(), value_content_end - mr.position() + 1, "");
				SlfTrim(s);
			}
		}else{
			if(deleteParameter){
				r = mr[1];
				s.replace(mr.position(), mr.length(), "");
				SlfTrim(s);
			}
			if(mandatory){
				throw MuRanExceptionShortData();
			}
		}
		return rtn;
	}
	if(mandatory){
		throw MuRanExceptionShortData();
	}
	return false;
}


int execute_prog(const char* input_command, const char* name,  int (*f)(int, char**)){
	string s = input_command;
	vector<string> sv = tokenize(input_command, " ");
	//bool bFound = false;

	int input_argc = 0;
	char**p = nullptr;

	if(sv.size() > 0){
		if(name != nullptr ){
			input_argc = (int) sv.size() + 1;
			p = new char*[input_argc ];
			if(p == nullptr){
				cerr << "Cannot Allocate Memory!" << endl;
				return -1;
			}else{
				p[0] = (char*)name;                    // will be safe to convert form const char * to char *
				for(int n = 0; n < sv.size(); n++){
					p[n + 1] = (char*) sv[n].c_str();  // will be safe to convert form const char * to char *
				}
			}
		}else{
			input_argc = (int) sv.size();
			p = new char*[input_argc ];
			if(p == nullptr){
				cerr << "Cannot Allocate Memory!" << endl;
				return -1;
			}else{
				for(int n = 0; n < input_argc; n++){
					p[n] = (char*) sv[n].c_str();  // will be safe to convert form const char * to char *
				}
			}
		}
	}else{
		if(name != nullptr ){
			input_argc = 1;
			p = new char*[input_argc ];
			p[0] = (char*) name;                          // will be safe to convert form const char * to char *
		}else{
			input_argc = 0;
			p = nullptr;
		}
	}

	int rtnVal;
	try {
		rtnVal = (*f)(input_argc, p);
	}catch(...){
		cerr << "Unhandled Execption Catched!!!" << endl;
		rtnVal = -1;
	}

	if(!p) delete p;
	return rtnVal;
}

#if defined(_WIN32) || defined(_WIN64)
char* vbuffer_format(const char* fmt, va_list  args){
	size_t len = _vscprintf( fmt, args )+ 1;
	char* b =(char*)  malloc(len);
	b[len-1] = '\0';
	vsprintf_s(b, len, fmt, args);
	return b;
}
#endif


int numberInTailOfString(const char* s){
	if(strlen(s) == 0){
		throw MuRanExceptionBadDataIntegrity();
	}
	cmatch mr;
	regex rgx("(\\d+)$");
	if(regex_search(s, mr, rgx)){
		return my_atoi(mr[1].str().c_str());
	}else{
		throw MuRanExceptionBadDataIntegrity();
	}
}

char* clone_str(const char* source){
	char * pStr = new char[strlen(source) + 1];
	AssertObj(pStr);
	strcpy(pStr, source);
	return pStr;
}

// center_output("abc"  ,7,'-') == print "--abc--"
// center_output("abc",1,7,'-') == print "-abc---"
inline string center(const char* content, const size_t width, char fillchar) {
	auto l = strlen(content);
	if(width <=  l)
		return string(content);
	else{
		size_t pad = width - l;
		string rtn(width, fillchar);
		memcpy(&rtn[0] + pad/2, content, l);
		return rtn;
	}
}

inline string center(const char* content, const size_t left, const size_t width, char fillchar) {
	auto l = strlen(content);
	if(width <=  l)
		return string(content);
	else{
		size_t pad = width - l;
		std::string rtn(width, fillchar);
		memcpy(&rtn[0] + left, content, l);
		return rtn;
	}
}

void center_output(FILE* stream, const char* content, const size_t width, const char fillchar, bool newline){
	auto l = strlen(content);
	if(width <=  l)
		fprintf(stream, "%s", content);
	else{
		fprintf(stream, "%s", center(content, width, fillchar).c_str()); // depends on center
	}
	
	if(newline){
		fprintf(stream,"\n");
	}
}

void center_output(FILE* stream, const char* content, const size_t left, const size_t width, const char fillchar, bool newline){
	auto l = strlen(content);
	if(width <=  l)
		fprintf(stream, "%s", content);
	else{
		fprintf(stream, "%s", center(content, left, width, fillchar).c_str()); // depends on center
	}
	
	if(newline){
		fprintf(stream,"\n");
	}
}


}
