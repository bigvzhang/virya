#pragma once

#include <vector>
#include <regex>
#include "vstring.h"


namespace virya{
string getCurrentProcessName(); 

#pragma warning( push )            // suppress warning generated `char* argv[]`
#pragma warning( disable : 4200 )
class Arg{
public:
	struct _Arg{
		int   argc;
		char* argv[];
	};
private:
	_Arg *ptr;
	bool    bDeleteArgv;
public:
	Arg(int argc, char* argv[],   bool cloneArgvs     = false);
	Arg(const char* command_line, bool append_nullptr = false);
	Arg(std::vector<std::string>& vct,      bool append_nullptr = false);
	Arg(const Arg& o);
	~Arg();
public:
	void erase(int idx);
	_Arg* operator->(){return ptr;}

	std::string to_string(int from, const char* delimiter = " ") const;
};
#pragma warning( pop )


bool isParameterSet(Arg& arg, const char *strParameteName, bool deleteParameter = true);

int getIntParameter(Arg& arg, const char *strParamterName, int dft, bool exitOnError = true, bool deleteParameter = true);

bool help_option(int param_argc, char* param_argv[]);
bool help_option(Arg& arg);

template<class Typ, class VLD, class CVT> Typ getParameter(Arg& arg, const char *strParamterName, Typ dft, VLD func_vld, CVT func_cvt, bool exitOnError = true, bool deleteParameter = true){ 
	auto my_exit = [&](int i){
		if(arg->argc >= 2)
			fprintf(stderr, "%s: missing argument to '%s'\n", arg->argv[0], strParamterName);
		else
			fprintf(stderr, "%s: missing argument to '%s'\n", getCurrentProcessName().c_str(), strParamterName);

		exit(i);
	};
	std::cmatch mr;
	std::regex  rgx(format("^%s$", strParamterName).c_str());

	for(int i = 0; i < arg->argc; i++){
		if(std::regex_search(arg->argv[i], mr, rgx)){
			if(i < arg->argc - 1){
				if(func_vld(arg->argv[i + 1])){
					auto rtn = func_cvt(arg->argv[i + 1]);
					arg.erase(i + 1);
					arg.erase(i);
					return rtn;
				} else{
					if(exitOnError)
						my_exit(1);
					else{
						arg.erase(i); // only erase one
						return dft;
					}
				}
			} else{
				if(exitOnError)
					my_exit(1);
				else{
					arg.erase(i); // only erase one
					return dft;
				}
			}
		}
	}
	return dft;
}

}// end namespace

