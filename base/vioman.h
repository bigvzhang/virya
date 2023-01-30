#ifndef VIRYA_IOMAN_H
#define VIRYA_IOMAN_H
#include <string>
#include <vector>
#include <vstring.h>
namespace virya{

typedef std::int64_t i64;

struct file_section {
	size_t pos1;
	size_t pos2; 
	file_section(i64 n, i64 first,  i64 second);
};

struct file_oneline {
	size_t pos1;
	const char* fmt;
	char trailing_flag; // 'c': append comment, '0': none
	file_oneline(size_t pos1, const char* fmt, char traing_flag = '0');
};

struct file_trailing_comment { // to control to print trailing comment of a line
	size_t pos1;
	const char* fmt;
	file_trailing_comment(size_t pos1, const char* fmt="%s");
};

struct file_oneexpression { // one expression in oneline
	size_t pos1;
	const char* delimiter; // such as "&" ">>" "ECHO" "?ECHO" -- "?ECHO" is special
	const char* fmt;
	char trailing_flag; // 'c': append comment, '0': none
	file_oneexpression(size_t pos1, const char* delimiter, const char* fmt, char trailing_flag = '0');
};

struct file_expressions { // each expression in one block; examples in tour predefined_macros
	size_t pos1;
	size_t pos2;
	const char* delimiter; // same as member of file_oneexpression 
	const char* fmt;
	char trailing_flag; // 'c': append comment, 'l': append comment or compilor info, '0': none, TAG:TRAILING_FLAG_ES
	file_expressions(size_t pos1, size_t pos2, const char* delimiter, const char* fmt, char trailing_flag = '0');
	file_expressions(size_t pos1, /*automatch*/const char* delimiter, const char* fmt, char trailing_flag = '0');
};

struct file_section_nxt {
	size_t pos1;
	size_t pos2;
	const char* prefix;
	file_section_nxt(i64 n, const char* prefix, int lines=1);
	file_section_nxt(i64 n, i64 lines=1, const char* prefix="++");
};

struct file_section_prv {
	size_t pos1;
	size_t pos2;
	const char* prefix;
	file_section_prv(i64 n, const char* prefix, int lines=1);
	file_section_prv(i64 n, i64 lines=1, const char* prefix="++");
};

struct file_manual{
	size_t pos;
	std::string name;     // __FUNCSIG__=>namespace
	std::string section;  // default to empty
	const char* prefix;
	file_manual(i64 pos, const char* name, const char* section, const char* prefix = nullptr);
};

std::string trim_quote(const char* content);
std::string center(const char* content, const size_t width, const char x); // center("abc",7,'-') => "--abc--"
void center_output(FILE* stream, const char* content,                     const size_t width, const char fillchar, bool newline = true); // center_output("abc",7,'-') print "--abc--\n"
void   left_output(FILE* stream, const char* content, const size_t left,  const size_t width, const char fillchar, bool newline = true); // center_output("abc",7,'-') print "--abc--\n"
void  right_output(FILE* stream, const char* content, const size_t right, const size_t width, const char fillchar, bool newline = true); // center_output("abc",7,'-') print "--abc--\n"
void print_srcfile(FILE* stream, const char* srcfile, const i64 pos1,     const i64 pos2, const char* prefix = nullptr);
void print_manual( FILE* stream, const char* srcfile, const i64 pos, const char* funcsig, const char* section, const char* prefix = nullptr);
void print_manual_nm(FILE* stream, const char* srcfile, const i64 pos, const char* entry_name, const char* section, const char* prefix = nullptr);
inline void print_srcfile(FILE* stream, const char* src, file_section fs, const char* prefix = nullptr){ print_srcfile(stream, src, fs.pos1, fs.pos2, prefix); }
inline void print_srcfile(FILE* stream, const char* src, file_section_nxt fs){ print_srcfile(stream, src, fs.pos1, fs.pos2, fs.prefix); }
inline void print_srcfile(FILE* stream, const char* src, file_section_prv fs){ print_srcfile(stream, src, fs.pos1, fs.pos2, fs.prefix); }
       void print_srcfile(FILE* stream, const char* src, file_oneline one);
       void print_srcfile(FILE* stream, const char* src, file_trailing_comment one);
       void print_srcfile(FILE* stream, const char* src, file_oneexpression);
       void print_srcfile(FILE* stream, const char* src, file_expressions);


inline void center_stdout(const char* content,                     const size_t width, const char fillchar, bool newline = true){center_output(stdout,content,      width,fillchar,newline);}
inline void center_stderr(const char* content,                     const size_t width, const char fillchar, bool newline = true){center_output(stderr,content,      width,fillchar,newline);}
inline void   left_stdout(const char* content, const size_t left,  const size_t width, const char fillchar, bool newline = true){  left_output(stdout,content,left, width,fillchar,newline);}
inline void   left_stderr(const char* content, const size_t left,  const size_t width, const char fillchar, bool newline = true){  left_output(stderr,content,left, width,fillchar,newline);}
inline void  right_stdout(const char* content, const size_t right, const size_t width, const char fillchar, bool newline = true){ right_output(stdout,content,right,width,fillchar,newline);}
inline void  right_stderr(const char* content, const size_t right, const size_t width, const char fillchar, bool newline = true){ right_output(stderr,content,right,width,fillchar,newline);}
inline void stdout_horizontal_line(int n, char c){ center_stdout("", n, c); }
inline void stderr_horizontal_line(int n, char c){ center_stderr("", n, c); }

class ioq_base { // FIFO io cache
private:
	std::vector<std::string> data;
	string prompt;
public:
	ioq_base(const char* prompt = ">> "):prompt(prompt){}
	void printf(const char* fmt, ...);
	void print(const char* fmt, ...);
	void clear();
};
typedef ioq_base ioq;

}

#endif
