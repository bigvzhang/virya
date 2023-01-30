#include <string>
#include <cstring>

#ifdef __GNUC__

#define ENABLE_FILESYSTEM_XP (__GNUC__ == 7 && __GNUC_MINOR__ == 3) // __GNUC_PATCHLEVEL__ == 0;
#define ENABLE_FILESYSTEM    (__GNUC__ > 7)
#define ENABLE_CPP17         (__GNUC__ > 7)

#endif

#if defined(_WIN32) || defined(_WIN64)
#   include <windows.h>
#   include <io.h>
#   include <direct.h>
#else
#   include <dirent.h> // for getcwd
#   include <sys/stat.h>
#if ENABLE_FILESYSTEM_XP
#   include <experimental/filesystem>
namespace filesystem = std::experimental::filesystem;
#elif ENABLE_FILESYSTEM
#   include <filesystem>
namespace filesystem = std::filesystem;
#endif
#endif

#include "vstring.h"


namespace virya{

using namespace std;
string basename2(const char* filePath){
#if defined(_WIN32) || defined (_WIN64)
	if(filePath==NULL){
		return "";
	}
	if(strlen(filePath) == 0 || filePath[strlen(filePath) - 1] == '\\'){
		return "";
	}

	for(int i = strlen(filePath) - 2; i >=0; i--){
		if(filePath[i] == '\\'){
			return string(&filePath[i+1]);
		}
	}
	return string(filePath);
#else
	if(filePath==NULL){
		return "";
	}
	if(strlen(filePath) == 0 || filePath[strlen(filePath) - 1] == '/'){
		return "";
	}

	for(int i = strlen(filePath) - 2; i >=0; i--){
		if(filePath[i] == '/'){
			return string(&filePath[i+1]);
		}
	}
	return string(filePath);
#endif
}

string dirname2(const char* filePath){
#if defined(_WIN32) || defined(_WIN64)
	if(filePath==NULL){
		return "";
	}
	if(strlen(filePath) == 0){
		return "";
	}

	for(int i = strlen(filePath) - 1; i >= 0; i--){
		if(filePath[i] == '\\'){
			string rtn;
			rtn.resize(i+1);
			rtn[i] = '\0';
			memcpy(&rtn[0], filePath, i);
			return rtn;
		}
	}
	return "";
#else
	if(filePath==NULL){
		return "";
	}
	if(strlen(filePath) == 0){
		return "";
	}

	for(int i = strlen(filePath) - 1; i >= 0; i--){
		if(filePath[i] == '/'){
			string rtn;
			rtn.resize(i+1);
			rtn[i] = '\0';
			memcpy(&rtn[0], filePath, i);
			return rtn;
		}
	}
	return "";
#endif
}

string muran_path_join(const char* p, const char* s){
	if(strlen(p) == 0)
		return s;
#       if defined(_WIN32) || defined(_WIN64)
	return format("%s\\%s", p, s);
#       else
	return format("%s/%s", p, s);
#       endif
}

int file_exists(const char* filepath){ // 0 => None, 1=> dir, 2=> fle
#if defined(_WIN32) || defined(_WIN64)
	DWORD  attributes = GetFileAttributes(filepath) ;
	if (attributes == INVALID_FILE_ATTRIBUTES) {
		return 0;
	}else if((attributes & FILE_ATTRIBUTE_DIRECTORY) == FILE_ATTRIBUTE_DIRECTORY ){
		return 1;
	}else{
		return 2;
	}
#else
	filesystem::path         path(filepath);
	std::error_code          ec;
	filesystem::file_status  s = filesystem::status(path, ec);
	switch(s.type()){
	case filesystem::file_type::directory:
		return 1;
	case filesystem::file_type::regular:
		return 2;
	case  filesystem::file_type::not_found:
		return 0;
	//case filesystem::file_type::none:        // ec = 40 under linux
	//case filesystem::file_type::unknown:
	default:
		return 9;
	}
#endif
}

}// namespace virya

