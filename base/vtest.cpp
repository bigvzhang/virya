#include "vtest.h"
#include <cstring>

namespace virya{
namespace test{

std::map<std::string, prog_entry> prog_entry::prog_entries;

prog_entry::prog_entry(PROG_ENTRY f, const char* name, const char* title):name(name), f(f), title(title){
	// Will Add This Entry to the Book
	auto it = prog_entries.find(this->name);
	if(it == prog_entries.end()){
		prog_entries.insert(std::pair<std::string, prog_entry>(this->name, *this));
	}else{
		it->second = *this;
	}	
}

prog_entry::prog_entry():f(nullptr){}

int submain(std::vector<SubEntry>& subEntries, int argc, char* argv[]){
	if(argc == 1){
		subEntries[0].f();
	}else{
		for(auto&e : subEntries){
			std::string name = std::string("--nm-") + e.name;
			for(int i = 0; i < argc; i++){
				if(name.compare(argv[i]) == 0){
					e.f();
					return 0;
				}else if(strcmp(argv[i], "--nm") == 0 || strcmp(argv[i], "--names") == 0 || strcmp(argv[i], "--entries") == 0){
					printf("Available names(sub-entries)\n");
					for(auto&e : subEntries){
						printf(" - %s\n", e.name.c_str());
					}
					return 0;
				}
			}
		}
	}
	return 0;
}


}// namespace test
}// namespace virya
