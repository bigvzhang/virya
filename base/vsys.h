#ifndef VIRYA_SYS_H
#define VIRYA_SYS_H
#include <string>
namespace virya{
std::string getCurrentProcessName();
std::string getCurrentProcessLongName();

int GetCurrentThreadId();

std::string get_class_name_from_macro(const char* _func_name);
}


#ifdef _WIN32
#define __CLASS_NAME__ virya::get_class_name_from_macro(__FUNCTION__).c_str()
#else
#define __CLASS_NAME__ virya::get_class_name_from_macro(__PRETTY_FUNCTION__).c_str()
#endif

#endif
