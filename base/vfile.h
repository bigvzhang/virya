#ifndef VIRYA_FILE_H
#define VIRYA_FILE_H
#include <string>
namespace virya{
std::string basename2(const char* filePath);
std::string dirname2(const char* filePath);
std::string muran_path_join(const char* p, const char* s);

int file_exists(const char* filepath);         // 0<= None, 1: directory 2:regular, 9 other

}
#endif
