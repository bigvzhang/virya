#ifndef VIRYA_MACRO_COMPLIANCE_H
#define VIRYA_MACRO_COMPLIANCE_H
// TAG:COMPILER_COMPATIBLE
#if defined(_MSC_VER) && ! defined(__clang__)
#define CODE_FORm(...) {__VA_ARGS__}
#define CODE_NOTm(...) {}
#define COMPILE_FORm 1
#define COMPILE_NOTm 0
#else
#define CODE_FORm(...) {}
#define CODE_NOTm(...) {__VA_ARGS__}
#define COMPILE_FORm 0
#define COMPILE_NOTm 1
#endif

#if  defined(__clang__)
#define CODE_FORk(...) {__VA_ARGS__}
#define CODE_NOTk(...) {}
#define COMPILE_FORk 1
#define COMPILE_NOTk 0
#else
#define CODE_FORk(...) {}
#define CODE_NOTk(...) {__VA_ARGS__}
#define COMPILE_FORk 0
#define COMPILE_NOTk 1
#endif

#if  defined(__GNUC__)
#define CODE_FORg(...) {__VA_ARGS__}
#define CODE_NOTg(...) {}
#define COMPILE_FORg      1
#define COMPILE_NOTg      0
#else
#define CODE_FORg(...) {}
#define CODE_NOTg(...) {__VA_ARGS__}
#define COMPILE_FORg      0
#define COMPILE_NOTg      1
#endif

#define CODE_ERRc(...) {} // compile error for all

#define COMPILE_FORa 1
#define COMPILE_NOTa 0

#endif //  VIRYA_MACRO_COMPLIANCE_H
