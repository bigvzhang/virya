
#ifdef _WIN32
#	include <windows.h>
#	include <tlhelp32.h>
#	include <tchar.h>
#   include <Psapi.h>
#   pragma warning(disable:4200)
#   undef max
#   undef min
#   pragma comment(lib,"Psapi.lib")
#else
#   include <sys/file.h>
#   include <sys/types.h>
#   include <signal.h>
#   include <pthread.h>
#   include <semaphore.h>
#   include <thread>       // C++11 supported
#   include <sys/time.h>
#   include <unistd.h>
#endif



#if defined(_WIN32) || defined(_WIN64)
typedef HANDLE    MR_PROCESS_HANDLE;
typedef DWORD     MR_PROCESS_ID;
typedef HANDLE    MR_THREAD_HANDLE;
typedef DWORD     MR_THREAD_ID;
#define MR_INVALID_HANDLE_VALUE   NULL                 // compatible for linux and windows
#define INVALID_FILE_HANDLE       INVALID_HANDLE_VALUE // only defined for windows
#define NULL_HANDLE               NULL                 // only defined for windows
#else
typedef std::int64_t       MR_PROCESS_HANDLE;
typedef std::int64_t       MR_PROCESS_ID;
typedef pthread_t MR_THREAD_HANDLE;
typedef pid_t     MR_THREAD_ID;
#define MR_INVALID_HANDLE_VALUE  0                     // compatible for linux and windows
#endif

#ifndef _WIN32
#   define MAX_PATH    PATH_MAX
#endif


#include <string>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <iostream>
#include <cstring>
#include <regex>

#include "vstring.h"


using namespace std;
namespace virya{

#ifdef _WIN32

void printError( LPCTSTR msg )
{
	DWORD eNum;
	TCHAR sysMsg[256];
	TCHAR* p;

	eNum = GetLastError( );
	FormatMessage( FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
		NULL, eNum,
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // Default language
		sysMsg, 256, NULL );

	// Trim the end of the line and terminate it with a null
	p = sysMsg;
	while( ( *p > 31 ) || ( *p == 9 ) )
		++p;
	do { *p-- = 0; } while( ( p >= sysMsg ) &&
		( ( *p == '.' ) || ( *p < 33 ) ) );

	// Display the message
	fprintf(stderr, TEXT("\n  WARNING: %s failed with error %d (%s)"), msg, eNum, sysMsg );
}

static
string __getProcessName(DWORD processID){
	string rtn;
	HANDLE hProcessSnap;
	PROCESSENTRY32 pe32;

	// Take a snapshot of all processes in the system.
	hProcessSnap = CreateToolhelp32Snapshot( TH32CS_SNAPPROCESS, processID );
	if( hProcessSnap == INVALID_FILE_HANDLE ){ // AS FILEHANDLE
		printError( TEXT("CreateToolhelp32Snapshot (of processes)") );
		return rtn;
	}

	pe32.dwSize = sizeof( PROCESSENTRY32 );

	if( !Process32First( hProcessSnap, &pe32 ) ){
		printError( TEXT("Process32First") ); // show cause of failure
		CloseHandle( hProcessSnap );          // clean the snapshot object
		return rtn;
	}

	do{
		if(pe32.th32ProcessID == processID){
			rtn = pe32.szExeFile;
			break;
		}
		
		//break;
	}while( Process32Next( hProcessSnap, &pe32 ) );
	CloseHandle( hProcessSnap );

	return rtn;
}

static
DWORD __getParentProcessId(DWORD processID){
		DWORD rtn = 0;
		HANDLE hProcessSnap;
		//HANDLE hProcess;
		PROCESSENTRY32 pe32;
		//DWORD dwPriorityClass;

		// Take a snapshot of all processes in the system.
		hProcessSnap = CreateToolhelp32Snapshot( TH32CS_SNAPPROCESS, processID );
		if( hProcessSnap == INVALID_FILE_HANDLE ){ // AS FILEHANDLE
			printError( TEXT("CreateToolhelp32Snapshot (of processes)") );
			return rtn;
		}

		pe32.dwSize = sizeof( PROCESSENTRY32 );

		if( !Process32First( hProcessSnap, &pe32 ) ){
			printError( TEXT("Process32First") ); // show cause of failure
			CloseHandle( hProcessSnap );          // clean the snapshot object
			return rtn;
		}

		do{
			if(pe32.th32ProcessID == processID){
				rtn = pe32.th32ParentProcessID;
				break;
			}

		}while( Process32Next( hProcessSnap, &pe32 ) );
		CloseHandle( hProcessSnap );

		return rtn;
}


string getCurrentProcessName(){
	return __getProcessName(GetCurrentProcessId());
}

string getCurrentProcessLongName(){
	TCHAR szPath[MAX_PATH];
	if( GetModuleFileName( NULL, szPath, MAX_PATH ) ){
		return string(szPath);
	}else{
		throw 1;
	}
}

string getCurrentProcessRunName() {
	return getCurrentProcessName();
}

string getParentProcessName(){
	return __getProcessName(__getParentProcessId(GetCurrentProcessId()));
}

string get_class_name_from_macro(const char* _func_name){
#ifdef _DEBUG
	if(_func_name == nullptr){
		throw 1;
	}
#endif
	// TODO, make performance better
	string func_name = regex_replace(_func_name, regex("<.*>"), std::string(""), regex_constants::match_any);// delete template internal
	//size_t pos = func_name.find_last_of(":");
	//if(pos != string::npos){
	//	string try_2 = func_name.substr(0, pos);
	//	size_t pos2 = try_2.find_last_not_of(":");
	//	if(pos2 != string::npos){
	//		return try_2.substr(0, pos2+1);
	//	}else{
	//		return try_2;
	//	}
	//	return func_name.substr(0, pos);
	//}else{
	//	return func_name;
	//}
	vector<string> vct = split(func_name, ":", true);
	if(vct.size() == 0){
		throw 1;
	}else if(vct.size() == 1){
		return vct[0];
	}else{
		return vct[vct.size() - 2];
	}
}
#else

string get_cmdline_by_pid(const int pid){
    char name[MAX_PATH]; name[0] = '\0';
    
	FILE* f = fopen(format("/proc/%d/cmdline", pid).c_str(), "r");
	 if(f){
		 size_t size;
		 size = fread(name, sizeof(char), MAX_PATH, f);
		 if(size>0){
			 if(name[size-1] == '\n')
				 name[size-1]='\0';
		 }
		 fclose(f);
	 }

    return string(name);
}

string get_process_name_by_pid(const int pid){
    char szBuf[MAX_PATH];

	memset(szBuf, 0, sizeof(szBuf));
    auto nCount=readlink(format("/proc/%d/exe",pid).c_str(), szBuf,MAX_PATH);
	if(nCount > 0){
		for(int i = strlen(szBuf) - 2; i >= 0 ; i--){// basename
			if(szBuf[i] == '/'){
				return string(&szBuf[i+1]);
			}
		}
	}

    return string(szBuf);
}


string getCurrentProcessName(){
	return program_invocation_short_name;
}

string getParentProcessName(){
	return get_process_name_by_pid(getppid());
}

string getCurrentProcessLongName(){
	char szBuf[MAX_PATH];
	memset(szBuf, 0, sizeof(szBuf));
	auto nCount=readlink("/proc/self/exe", szBuf,MAX_PATH);

	return string(szBuf);
}

string getCurrentProcessRunName() {
	return getCurrentProcessLongName();
}


string get_class_name_from_macro(const char* _func_name){
#ifdef _DEBUG
	if(_func_name == nullptr){
		throw MuRanExceptionCStrNull();
	}
#endif
#ifdef ENABLE_CPP17
	string_view func_name(_func_name);
	size_t pos_9 = func_name.find_last_of("(");
	if(pos_9 != string::npos){
		
		size_t y = func_name.find_last_of(":", pos_9); //for template class, like: int ns1::ns2::name<BASE1,BASE2> [with ...]
		y--;
		size_t x = 0;
		
		if(func_name[y-1] == '>'){
			for(size_t pos = y; pos > 0; pos --){
				if(func_name[pos - 1] == ':'){
					x = pos;
					break;
				}else if(func_name[pos - 1] == '<'){
					y = pos-1;
				}
			}
		}else{
			for(size_t pos = y; pos > 0; pos --){
				if(func_name[pos - 1] == ' '){
					x = pos;
					break;
				}
			}
		}
		
		if(y <= x){
			throw 1;
		}else{
			return string(func_name.substr(x,y-x));
		}
	}else{
		throw 1;
	}
#else
	string func_name(_func_name);
	size_t pos_9 = func_name.find_last_of("(");
	if(pos_9 != string::npos){
		
		size_t y = func_name.find_last_of(":", pos_9); //for template class, like: int ns1::ns2::name<BASE1,BASE2> [with ...]
		y--;
		size_t x = 0;
		
		if(func_name[y-1] == '>'){
			for(size_t pos = y; pos > 0; pos --){
				if(func_name[pos - 1] == ':'){
					x = pos;
					break;
				}else if(func_name[pos - 1] == '<'){
					y = pos-1;
				}
			}
		}else{
			for(size_t pos = y; pos > 0; pos --){
				if(func_name[pos - 1] == ' '){
					x = pos;
					break;
				}
			}
		}
		
		if(y <= x){
			throw 1;
		}else{
			return func_name.substr(x,y-x);
		}

	}else{
		throw 1;
	}
#endif
}

#endif

}// end namespace virya


#ifndef _WIN32

	#ifdef __CYGWIN__
		extern "C"{
			unsigned int GetCurrentThreadId();
		}
	#endif

#endif

namespace virya {

#ifdef _WIN32
	int GetCurrentThreadId(){
		return ::GetCurrentThreadId();
	}
#elif defined(__CYGWIN__)
	int GetCurrentThreadId(){
		return ::GetCurrentThreadId();
	}
#else
    int GetCurrentThreadId(){
        return syscall(SYS_gettid);
    }
#endif

}
