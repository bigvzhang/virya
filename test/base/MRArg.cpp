#include <stdio.h>
#include <vector>
#include <string>
#include "MuRanCommonFuncs.h"
#include "MRArg.h"
#include "MRException.h"

#define MR_MALLOC(TAG, ...)          malloc(__VA_ARGS__)
#define free_ptr(TAG,p)              {if(p != nullptr) { free(p); p = nullptr;}}

namespace muranbase{
	
	using namespace std;
	using namespace muranexception;

	MRArg::MRArg(int argc, char* argv[], bool cloneArgvs){
		ptr = (_MRArg*) MR_MALLOC(_MRArg, sizeof(char**)*argc + sizeof(int)*2);
		AssertObj(ptr);
		for(int i = 0; i< argc; i++){
			if(cloneArgvs)
				ptr->argv[i] = muran_clone_str(argv[i]);
			else
				ptr->argv[i] = argv[i];
		}
		ptr->argc = argc;
        bDeleteArgv = cloneArgvs;
	}
    
    MRArg::MRArg(vector<string>& vct,  bool append_nullptr){
        if(append_nullptr){
            ptr = (_MRArg*) MR_MALLOC(_MRArg, sizeof(char**)*(vct.size() + 1)  + sizeof(int)*2);
            AssertObj(ptr);
            for(size_t i = 0; i< vct.size(); i++){
                ptr->argv[i] = muran_clone_str(vct[i].c_str());
            }
            ptr->argv[vct.size()] = nullptr;
            ptr->argc = vct.size();
        }else{
            ptr = (_MRArg*) MR_MALLOC(_MRArg, sizeof(char**)*(vct.size())  + sizeof(int)*2);
            AssertObj(ptr);
            for(size_t i = 0; i< vct.size(); i++){
                ptr->argv[i] = muran_clone_str(vct[i].c_str());
            }
            ptr->argc = vct.size();
        }
        bDeleteArgv = true;    
    }
    
    MRArg::MRArg(const char* command_line, bool append_nullptr){
        vector<string> vct = muranbase::split(command_line, " ");
        if(append_nullptr){
            ptr = (_MRArg*) MR_MALLOC(_MRArg, sizeof(char**)*(vct.size() + 1)  + sizeof(int)*2);
            AssertObj(ptr);
            for(size_t i = 0; i< vct.size(); i++){
                ptr->argv[i] = muran_clone_str(vct[i].c_str());
            }
            ptr->argv[vct.size()] = nullptr;
            ptr->argc = vct.size();
        }else{
            ptr = (_MRArg*) MR_MALLOC(_MRArg, sizeof(char**)*(vct.size())  + sizeof(int)*2);
            AssertObj(ptr);
            for(size_t i = 0; i< vct.size(); i++){
                ptr->argv[i] = muran_clone_str(vct[i].c_str());
            }
            ptr->argc = vct.size();
        }
       bDeleteArgv = true;
    }
    
 


	MRArg::MRArg(const MRArg& o){
		ptr = (_MRArg*) MR_MALLOC(_MRArg, sizeof(char**)*(o.ptr->argc) + sizeof(int)*2);
		AssertObj(ptr);
		for(int i = 0; i< o.ptr->argc; i++){
			ptr->argv[i] = muran_clone_str(o.ptr->argv[i]); // Anyway to clone it
		}
		ptr->argc = o.ptr->argc;
		bDeleteArgv = true;
	}

	MRArg::~MRArg(){
        if(bDeleteArgv){
            for(int i = 0; i < ptr->argc; i++){
                if(ptr->argv[i] != nullptr){
                    free(ptr->argv[i]);
                }
            }
        }
		free_ptr(_MRArg, ptr);
	}

	void MRArg::erase(int idx){
		if(idx >= ptr->argc){
			return;
		}
		for(int i = idx; i < ptr->argc - 1; i++){
			ptr->argv[i] = ptr->argv[i+1];
		}
		ptr->argc--;
	}

}
