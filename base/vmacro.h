#ifndef VIRYA_MACRO_H
#define VIRYA_MACRO_H
#define free_ptr(TAG,p)              {if(p != nullptr) { free(p); p = nullptr;}}
#define MR_MALLOC(TAG, ...)          malloc(__VA_ARGS__)
#define AssertObj(p)                 if(p==nullptr) {throw 1;}
#define EMPTY_STRING_ERROR  1
#endif
