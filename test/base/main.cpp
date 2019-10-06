#include <iostream>
#include <string>
#include "MRFuncEntry.h"
#include "MuRanCommonFuncs.h"
#include "MRArg.h"



using namespace std;
using namespace muranbase;

#define PROG_FLAG "vtest"
int main(int _argc, char**_argv) {
	std::map<std::string, TestFuncEntry>& func_entries = get_func_entries();

	auto getSubArgument =[&](const char* s){
		string a;
		for(int i = 1; i < _argc; i++){
			if(i == 1)
				a = s;
			else if(i > 1)
				a = format("%s %s", a.c_str(), _argv[i]);
		}
		return MRArg(a.c_str());
	};

	static regex rgx1("^(\\d+)\\.(\\d+)$");
	static regex rgx2("^" PROG_FLAG "(\\d+)_(\\w+)$");

	auto printMatchedProg =[&](int reqID){
		cmatch mr;
		int  cntFound = 0;
		for(auto it = func_entries.begin(); it != func_entries.end(); it++){
			if(regex_search(it->first.c_str(), mr, rgx2)){
				int no = my_atoi(mr[1].str().c_str());
				if(no == reqID){
					cntFound++;
					printf("%s.%d %s\n",  mr[1].str().c_str(), cntFound, mr[2].str().c_str());
				}
			}
		}
	};

	auto printMatchedProg2 = [&](const char* prog_name){
		cmatch mr;
		int  cntFound = 0;
		for(auto it = func_entries.begin(); it != func_entries.end(); it++){
			if(regex_search(it->first.c_str(), mr, rgx2)){
				if(mr[2].str().compare(prog_name) == 0){
					cntFound++;
					printf("%s.%d %s\n", mr[2].str().c_str(), cntFound, it->first.c_str());
				}
			}
		}
	};
    if(_argc > 1){

		if(_argv[1][0] >='0' && _argv[1][0] <='9'){
			if(is_str_number(_argv[1])){
				// Search prog idenfified by input id
				auto itFound = func_entries.end();
				int  cntFound = 0;
				int  reqID = my_atoi(_argv[1]);
				cmatch mr;
				for(auto it = func_entries.begin(); it != func_entries.end(); it++){
					if(regex_search(it->first.c_str(), mr, rgx2)){
						int id = my_atoi(mr[1].str().c_str());
						if(id == reqID ){
							if(itFound == func_entries.end())
								itFound = it;
							cntFound++;
						}
					}
				}
				if(cntFound == 0){
					return -1;
				}
				else if(cntFound == 1){
					MRArg convertedArg = getSubArgument(itFound->first.c_str());
					return (*itFound->second.f)(convertedArg->argc, convertedArg->argv);
				}else{
					printMatchedProg(reqID);
					return -1;
				}
			}else{
				cmatch mrx;
				if(regex_search(_argv[1], mrx, rgx1)){// input string like 1.1
				   // Search prog idenfified by input id and seq
					auto itFound = func_entries.end();
					int  cntFound = 0;
					int  reqID = my_atoi(mrx[1].str().c_str());
					int  reqNO = my_atoi(mrx[2].str().c_str());
					cmatch mr;
					for(auto it = func_entries.begin(); it != func_entries.end(); it++){
						if(regex_search(it->first.c_str(), mr, rgx2)){
							int id = my_atoi(mr[1].str().c_str());
							if(id == reqID){
								cntFound++;
								if(cntFound == reqNO){
									itFound = it;
								}
							}
						}
					}
					if(cntFound == 0){
						return -1;
					} else if(itFound != func_entries.end()){
						MRArg convertedArg = getSubArgument(itFound->first.c_str());
						return (*itFound->second.f)(convertedArg->argc, convertedArg->argv);
					} else{
						printMatchedProg(reqID);
						return -1;
					}

				}else{
					string prog_name = PROG_FLAG;
					prog_name += _argv[1];

					auto it = func_entries.find(prog_name);
					if(it != func_entries.end()){
						MRArg convertedArg = getSubArgument(prog_name.c_str());
						return (*it->second.f)(convertedArg->argc, convertedArg->argv);
					}
					return -1;
				}
			}
		}else{

			if(strcmp(_argv[1], "--help") == 0 || strcmp(_argv[1], "help") == 0){
				printf("Existing Functions:\n");
				for(auto x : func_entries){
					printf("   %s \n", x.second.name.c_str());
				}
				return 0;
			} else{
				string prog_name = _argv[1];
				auto it = func_entries.find(prog_name);
				if(it != func_entries.end()){
					MRArg convertedArg = getSubArgument(prog_name.c_str());
					return (*it->second.f)(convertedArg->argc, convertedArg->argv);
				}

				auto itFound = func_entries.end();
				int  cntFound = 0;
				cmatch mr;
				for(auto it = func_entries.begin(); it != func_entries.end(); it++){
					if(regex_search(it->first.c_str(), mr, rgx2)){
						if(mr[2].str().compare(prog_name) == 0){
							if(itFound == func_entries.end())
								itFound = it;
							cntFound++;
						}
					}
				}
				if(cntFound == 0){
					return -1;
				} else if(cntFound == 1){
					MRArg convertedArg = getSubArgument(itFound->first.c_str());
					return (*itFound->second.f)(convertedArg->argc, convertedArg->argv);
				} else{
					printMatchedProg2(prog_name.c_str());
					return -1;
				}

				fprintf(stderr, "Couldn't find function(%s)\n", prog_name.c_str());
				return -1;
			}
		}
	}else{
		printf("Existing Functions:\n");
		for(auto x : func_entries){
			printf("   %s \n", x.second.name.c_str());
		}
		return 0;
	}

}

