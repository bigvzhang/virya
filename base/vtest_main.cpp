#include <iostream>
#include <vsys.h>
#include <varg.h>
#include <vstring.h>
#include "vfuncentry.h"
#include "vioman.h"
using namespace virya;
using namespace std;

#define PROG_FLAG "tour"

int main(int _argc, char**_argv) {
	auto getSubArgument =[&](const char* s){
		string a;
		for(int i = 1; i < _argc; i++){
			if(i == 1)
				a = s;
			else if(i > 1)
				a = format("%s %s", a.c_str(), _argv[i]);
		}
		return Arg(a.c_str());
	};

	static regex rgx1("^(\\d+)\\.(\\d+)$");
	static regex rgx_progfullname("^" PROG_FLAG "(\\d+)_(\\w+)$");

	auto printMatchedProg =[&](int reqID){
		cmatch mr;
		int  cntFound = 0;
		auto& func_entries = get_func_entries();
		for(auto it = func_entries.begin(); it != func_entries.end(); it++){
			if(regex_search(it->first.c_str(), mr, rgx_progfullname)){
				int no = stoi(mr[1].str());
				if(no == reqID){
					cntFound++;
					printf("%s.%d %-30s %s\n",  mr[1].str().c_str(), cntFound, mr[2].str().c_str(), it->second.title.c_str());
				}
			}
		}
	};

	auto printMatchedProg2 = [&](const char* prog_name){
		cmatch mr;
		int  cntFound = 0;
		auto& func_entries = get_func_entries();
		for(auto it = func_entries.begin(); it != func_entries.end(); it++){
			if(regex_search(it->first.c_str(), mr, rgx_progfullname)){
				if(mr[2].str().compare(prog_name) == 0){
					cntFound++;
					printf("%s.%d %-40s %s\n", mr[2].str().c_str(), cntFound, it->first.c_str(), it->second.title.c_str());
				}
			}
		}
	};

	auto notfound =[&]()->TestFuncEntry*{
		if(_argc > 1)
			fprintf(stderr, "Couldn't find program(%s), please get help with option --help!\n", _argv[1]);
		return nullptr;
	};

	auto& func_entries = get_func_entries();
    auto get_entry =[&func_entries, &notfound, &printMatchedProg, &printMatchedProg2](const char* name) ->TestFuncEntry*{
		if(name[0] >='0' && name[0] <='9'){
			if(isdigit(name)){
				// Search prog idenfified by input id
				auto itFound = func_entries.end();
				int  cntFound = 0;
				int  reqID = atoi(name);
				cmatch mr;
				for(auto it = func_entries.begin(); it != func_entries.end(); it++){
					if(regex_search(it->first.c_str(), mr, rgx_progfullname)){
						int id = stoi(mr[1].str());
						if(id == reqID ){
							if(itFound == func_entries.end())
								itFound = it;
							cntFound++;
						}
					}
				}
				if(cntFound == 0){
					return notfound();
				}
				else if(cntFound == 1){
					//Arg convertedArg = getSubArgument(itFound->first.c_str());
					return &itFound->second;//return (*itFound->second.f)(convertedArg->argc, convertedArg->argv);
				}else{
					printMatchedProg(reqID);
					return nullptr;
				}
			}else{
				cmatch mrx;
				if(regex_search(name, mrx, rgx1)){// input string like 1.1
				   // Search prog idenfified by input id and seq
					auto itFound = func_entries.end();
					int  cntFound = 0;
					int  reqID = atoi(mrx[1].str().c_str());
					int  reqNO = atoi(mrx[2].str().c_str());
					cmatch mr;
					for(auto it = func_entries.begin(); it != func_entries.end(); it++){
						if(regex_search(it->first.c_str(), mr, rgx_progfullname)){
							int id = atoi(mr[1].str().c_str());
							if(id == reqID){
								cntFound++;
								if(cntFound == reqNO){
									itFound = it;
								}
							}
						}
					}
					if(cntFound == 0){
						return notfound();
					} else if(itFound != func_entries.end()){
						//Arg convertedArg = getSubArgument(itFound->first.c_str());
						return &itFound->second;//return (*itFound->second.f)(convertedArg->argc, convertedArg->argv);
					} else{
						printMatchedProg(reqID);
						return nullptr;
					}

				}else{
					string prog_name = PROG_FLAG;
					prog_name += name;

					auto it = func_entries.find(prog_name);
					if(it != func_entries.end()){
						//Arg convertedArg = getSubArgument(prog_name.c_str());
						return &it->second;//return (*it->second.f)(convertedArg->argc, convertedArg->argv);
					}
					return notfound();
				}
			}
		}else{
			{
				string prog_name = name;
				auto it = func_entries.find(prog_name);
				if(it != func_entries.end()){
					//Arg convertedArg = getSubArgument(prog_name.c_str());
					return &it->second;//return (*it->second.f)(convertedArg->argc, convertedArg->argv);
				}

				auto itFound = func_entries.end();
				int  cntFound = 0;
				cmatch mr;
				for(auto it = func_entries.begin(); it != func_entries.end(); it++){
					if(regex_search(it->first.c_str(), mr, rgx_progfullname)){
						if(mr[2].str().compare(prog_name) == 0){
							if(itFound == func_entries.end())
								itFound = it;
							cntFound++;
						}
					}
				}
				if(cntFound == 0){
					return notfound();
				} else if(cntFound == 1){
					//Arg convertedArg = getSubArgument(itFound->first.c_str());
					return &itFound->second;//return (*itFound->second.f)(convertedArg->argc, convertedArg->argv);
				} else{
					printMatchedProg2(prog_name.c_str());
					return nullptr;
				}
			}
		}
	};
	if(_argc > 1){
			if(strcmp(_argv[1], "--help") == 0 || strcmp(_argv[1], "help") == 0){
				vector<string> names;
				for(auto x : func_entries){
					names.push_back(x.second.name);
				}
				sort(names.begin(), names.end(), [](string& a1, string& a2){
					cmatch mr1;
					if(regex_search(a1.c_str(), mr1, rgx_progfullname)){
						cmatch mr2;
						if(regex_search(a2.c_str(), mr2, rgx_progfullname)){
							int no1 = atoi(mr1[1].str().c_str());
							int no2 = atoi(mr2[1].str().c_str());
							if(no1 < no2){
								return true;
							}else if(no1 == no2){
								if(mr1[2].str().compare(mr2[2].str()) < 0){
									return true;
								}
							}
							return false;
						}
					}
					if(a1.compare(a2) < 0)
						return true;
					else
						return false;
				});
				printf("Existing Functions:\n");
				for(auto name : names){
					auto e = func_entries.find(name);
					if(e == func_entries.end())
						continue; // let it pass
					printf("   %-40s %s \n", name.c_str(), e->second.title.c_str());
				}
				return 0;
			}else if(strcmp(_argv[1], "man") == 0 || strcmp(_argv[1], "--man") == 0){
				if(_argc == 2){
					printf("Missing argument!\n");
					return 1;
				}
				auto entry = get_entry(_argv[2]);
				if(!entry){
					return 1; // error message already printed
				}
				//printf("%s %s [%d~%d]\n", entry->name.c_str(), entry->src_file, entry->src_line_begin, entry->src_line_end);
				if(_argc == 3)
					virya::print_manual_nm(stdout, entry->src_file, entry->src_line_end, entry->name.c_str(), nullptr);
				else{for(int i = 3; i < _argc; i++){
					virya::print_manual_nm(stdout, entry->src_file, entry->src_line_end, entry->name.c_str(), _argv[i]);
				}}
			}else{
				auto entry = get_entry(_argv[1]);
				if(entry){
					Arg convertedArg = getSubArgument(entry->name.c_str());
					return (entry->f)(convertedArg->argc, convertedArg->argv);
				}else{
					return 1;// have alreay print error message;
				}
			}
	}else{
		printf("There're %zu programs, please see them using --help option!\n", func_entries.size());
		return 0;
	}

}

