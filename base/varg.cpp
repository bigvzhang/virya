#include <vector>
#include "varg.h"
#include "vstring.h"
#include "vmacro.h"
#include "vstdlib.h"

namespace virya{

using std::vector;
using std::cmatch;
using std::regex;

Arg::Arg(int argc, char* argv[], bool cloneArgvs){
	ptr = (_Arg*) MR_MALLOC(_Arg, sizeof(char**)*argc + sizeof(int)*2);
	AssertObj(ptr);
	for(int i = 0; i< argc; i++){
		if(cloneArgvs)
			ptr->argv[i] = clone_str(argv[i]);
		else
			ptr->argv[i] = argv[i];
	}
	ptr->argc = argc;
	bDeleteArgv = cloneArgvs;
}

Arg::Arg(vector<string>& vct,  bool append_nullptr){
	if(append_nullptr){
		ptr = (_Arg*) MR_MALLOC(_Arg, sizeof(char**)*(vct.size() + 1)  + sizeof(int)*2);
		AssertObj(ptr);
		for(size_t i = 0; i< vct.size(); i++){
			ptr->argv[i] = clone_str(vct[i].c_str());
		}
		ptr->argv[vct.size()] = nullptr;
		ptr->argc = (int)vct.size();
	}else{
		ptr = (_Arg*) MR_MALLOC(_Arg, sizeof(char**)*(vct.size())  + sizeof(int)*2);
		AssertObj(ptr);
		for(size_t i = 0; i< vct.size(); i++){
			ptr->argv[i] = clone_str(vct[i].c_str());
		}
		ptr->argc = (int) vct.size();
	}
	bDeleteArgv = true;    
}

Arg::Arg(const char* command_line, bool append_nullptr){
	vector<string> vct = split(command_line, " ");
	if(append_nullptr){
		ptr = (_Arg*) MR_MALLOC(_Arg, sizeof(char**)*(vct.size() + 1)  + sizeof(int)*2);
		AssertObj(ptr);
		for(size_t i = 0; i< vct.size(); i++){
			ptr->argv[i] = clone_str(vct[i].c_str());
		}
		ptr->argv[vct.size()] = nullptr;
		ptr->argc = vct.size();
	}else{
		ptr = (_Arg*) MR_MALLOC(_Arg, sizeof(char**)*(vct.size())  + sizeof(int)*2);
		AssertObj(ptr);
		for(size_t i = 0; i< vct.size(); i++){
			ptr->argv[i] = clone_str(vct[i].c_str());
		}
		ptr->argc = vct.size();
	}
   bDeleteArgv = true;
}




Arg::Arg(const Arg& o){
	ptr = (_Arg*) MR_MALLOC(_Arg, sizeof(char**)*(o.ptr->argc) + sizeof(int)*2);
	AssertObj(ptr);
	for(int i = 0; i< o.ptr->argc; i++){
		ptr->argv[i] = clone_str(o.ptr->argv[i]); // Anyway to clone it
	}
	ptr->argc = o.ptr->argc;
	bDeleteArgv = true;
}

Arg::~Arg(){
	if(bDeleteArgv){
		for(int i = 0; i < ptr->argc; i++){
			if(ptr->argv[i] != nullptr){
				free(ptr->argv[i]);
			}
		}
	}
	free_ptr(_Arg, ptr);
}

void Arg::erase(int idx){
	if(idx >= ptr->argc){
		return;
	}
	for(int i = idx; i < ptr->argc - 1; i++){
		ptr->argv[i] = ptr->argv[i+1];
	}
	ptr->argc--;
}

string Arg::to_string(int from, const char* delimiter) const{
	string rtn;
	for(int i = from; i < ptr->argc; i++ ){
		if(i == from){
			rtn = ptr->argv[i];
		}else{
			rtn += delimiter;
			rtn += ptr->argv[i];
		}
	}
	return rtn;
}



bool isParameterSet(Arg& arg, const char *strParamterName, bool deleteParameter){
	cmatch mr;
	regex  rgx(format("^%s$", strParamterName).c_str());

	for(int i = 0; i < arg->argc;i++){
		if(regex_search(arg->argv[i], mr, rgx)){
			if(deleteParameter)
				arg.erase(i);
			return true;
		}
	}
	return false;
}

int getIntParameter(Arg& arg, const char *strParamterName, int dft, bool exitOnError, bool deleteParameter){
	auto my_exit=[&](int i){
		if(arg->argc >= 2)
			fprintf(stderr, "%s: missing argument to '%s'\n", arg->argv[0], strParamterName);
		else
			fprintf(stderr, "%s: missing argument to '%s'\n", getCurrentProcessName().c_str(), strParamterName);

		exit(i);
	};
	cmatch mr;
	regex  rgx(format("^%s$", strParamterName).c_str());

	for(int i = 0; i < arg->argc; i++){
		string s = arg->argv[i];
		if(regex_search(s.c_str(), mr, rgx)){
			if(i < arg->argc - 1){
				if(isdigit(arg->argv[i+1])){
					int rtn = atoi32(arg->argv[i+1]);
					arg.erase(i+1);
					arg.erase(i);
					return rtn;
				}else{
					if(exitOnError)
						my_exit(1);
					else{
						arg.erase(i); // only erase one
						return dft;
					}
				}
			}else{
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

bool help_option(int param_argc, char* param_argv[]){
	if(param_argc >= 2){
		if(strcmp(param_argv[1], "help") == 0) // the first param could be help, --help or -h
			return true;                       //    <cmd> help|--help|-h
		for(int i = 1; i < param_argc; i++){
			if(strcmp(param_argv[i], "--help")  == 0 || strcmp(param_argv[i], "-h")  == 0)
				return true;
		}
	}
	return false;
}

bool help_option(Arg& arg){
	return help_option(arg->argc, arg->argv);
}

}
