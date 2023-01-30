//
// Copyright (c) 2019-2020 Vic Zhang(VicBig at qq dot com)
//
// Distributed under the GNU General Public License, Version 3.(Please see
// more information at https://www.gnu.org/licenses/)
//
// Official repository: https://github.com/bigvzhang/vhttp
//

#ifndef VIRYA_STRING_H
#define VIRYA_STRING_H


#include <string>
#include <vector>

namespace virya{

using std::string;

string format(const char* fmt, ...);
void format(string& s, const char* fmt, ...);

bool isdigit(const char* str);

char* clone_str(const char* source);

std::vector<string>  split(const string& src, const string& delimit, bool drop_null  = false, string null_substr = "");

inline std::string& rtrim(std::string& s, const char* t = "\t ") {
    s.erase(s.find_last_not_of(t) + 1);
    return s;
}
inline std::string& ltrim(std::string& s, const char* t = "\t ") {
    s.erase(0, s.find_first_not_of(t));
    return s;
} 
inline std::string& trim(std::string& s, const char* t = "\t "){
    return ltrim(rtrim(s, t), t);
}

bool str_lead_with(const char*s1, const char* s2);
bool str_i_lead_with(const char*s1, const char* s2);
bool str_end_with(const char*s1, const char* s2);
bool str_i_end_with(const char*s1, const char* s2);

string LTrim(const string& str, const char* x = " \t\n\r");
string RTrim(const string& str, const char* x = " \t\n\r");
string Trim(const string& str, const char* x = " \t\n\r");
void SlfLTrim(string& str, const char* x = " \t\n\r");
void SlfRTrim(string& str, const char* x = " \t\n\r");
void SlfTrim(string& str, const char* x = " \t\n\r");
string LTrimCStr(const char* str, const char* x = " \t\n\r");
string RTrimCStr(const char* str, const char* x = " \t\n\r");
string TrimCStr(const char* str, const char* x = " \t\n\r");

} // namespace 


#endif // VIRYA_STRING_H
