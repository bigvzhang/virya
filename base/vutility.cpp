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

#include "vutility.h"

namespace virya{
namespace utility{

TimeRecord::~TimeRecord(){
	vtime t2;
	if(msg.size() > 0){
		printf("TaskCompleted: %s ~ %s (%lld MilliSeconds) => %s\n", 
				t1.to_std_milli().c_str(),
				t2.to_hhmiss_milli(false).c_str(),
				t2.get_int64() - t1.get_int64(),
				msg.c_str()
		);
	}else{
		printf("TaskCompleted: %s ~ %s (%lld MilliSeconds)\n", 
				t1.to_std_milli().c_str(),
				t2.to_hhmiss_milli(false).c_str(),
				t2.get_int64() - t1.get_int64()
		);	
	}
}

ConsoleProtector::ConsoleProtector(){
#ifdef _WIN32
	HWND hwndConsole = GetConsoleWindow();
	HMENU hMenu = GetSystemMenu(hwndConsole, FALSE);
	EnableMenuItem(hMenu, SC_CLOSE, MF_BYCOMMAND | MF_GRAYED);	// Grayed => Disable
#endif
}

ConsoleProtector::~ConsoleProtector(){
#ifdef _WIN32
	HWND hwndConsole = GetConsoleWindow();
	HMENU hMenu = GetSystemMenu(hwndConsole, FALSE);
	EnableMenuItem(hMenu, SC_CLOSE, MF_BYCOMMAND | MF_ENABLED);	// Grayed => Disable
#endif
}



std::mutex PrintThread::_mutexPrint;

} // namespace utility
} // namespace virya
