#pragma once
#define delete_ptr(p)   {if(p != nullptr) { delete p; p=nullptr;}}
#define try_delete(p)   \
	try{                \
		delete_ptr(p)   \
	}catch(...){		\
						\
	}	

#define mr_free_memory(ptr){if(ptr){free(ptr); ptr = nullptr;}} 

#define sizeof_array(a) (sizeof(a)/sizeof(a[0]))
#define ptr_array(a)    &a[0]



#include <string>

#if defined(_WIN32) || defined(_WIN64)
	#pragma warning(disable : 4996)
	#include <regex>
	#define CpyCToBuf(d, s) strcpy_s(d, sizeof(d), s)
	#define CpySToBuf(d, s) strcpy_s(d, sizeof(d), s.c_str())
	typedef __int64 i64;

	#define REGEX_POS_ZERO 0
#else
	#include <vector>

	#include <boost/regex.hpp>
	#include <float.h>
	using namespace boost;
	#ifndef strcpy_s
	#define strcpy_s(d,n,s) strncpy(d,s,n)
	#endif
	#define CpyCToBuf(d, s) strcpy_s(d, sizeof(d), s)
	#define CpySToBuf(d, s) strcpy_s(d, sizeof(d), s.c_str())

	//#ifndef nullptr
	//#define nullptr NULL
	//#endif

	typedef long long i64;
    #define __FUNCDNAME__  __FUNCTION__ // to Support Linux
	#define REGEX_POS_ZERO (unsigned long int)(0)
    #define LONGLONG_ZERO  0L
#endif
//
//#define MR_MALLOC(TAG, ...)          malloc(__VA_ARGS__)
//#define MR_CALLOC(TAG, ...)          calloc(__VA_ARGS__)
//#define MR_FREE(TAG, ...)            free  (__VA_ARGS__)
//#define free_ptr(TAG,p)              {if(p != nullptr) { free(p); p = nullptr;}}

#if defined(_WIN32) || defined(_WIN64)
#define REGEX_POSITION_FIRST 0
#define strcasecmp stricmp
#define strncasecmp strnicmp
#else
#define REGEX_POSITION_FIRST (unsigned long int)0L
#define stricmp  strcasecmp
#define strnicmp strncasecmp
#endif



#ifndef _SIZE_TT_DEFINED
typedef unsigned short int      uint16_t;
typedef unsigned char	        uint8_t;

#ifdef  _WIN64
typedef signed __int64    ssize_t;
#else
#ifdef _WIN32
typedef signed int        ssize_t;
#endif
#endif
#define _SIZE_T_DEFINED
#endif

typedef unsigned int mrsize_t;



#define	SAFE_MEMBER_OBJ_ASSIGN(TYPE_NAME, MEMBER_OBJ_NAME)        \
	if(param_##MEMBER_OBJ_NAME == nullptr){                        \
	delete_ptr(MEMBER_OBJ_NAME);                            \
	}else if(MEMBER_OBJ_NAME != nullptr){                        \
	*MEMBER_OBJ_NAME = *param_##MEMBER_OBJ_NAME;              \
	}else{                                                        \
	MEMBER_OBJ_NAME = new TYPE_NAME(*param_##MEMBER_OBJ_NAME); \
	}


#define mrmap_copy(a,b)                                \
	for(auto it = a.getIterator(); it != a.endElement();it++){    \
		b.insert(it->first, it->second, false)  ;          \
	}

#define mrmap_obj_clone(TYPE_NAME, a,b)                                \
	for(auto it = a.getIterator(); it != a.endElement();it++){    \
	b.insert(it->first, new TYPE_NAME(*(it->second)), false)  ;          \
	}

#define vector_obj_copy(TYPE_NAME, a, b){          \
	for(auto it = a.begin(); it != a.end(); it++){   \
	TYPE_NAME *to_copy = new TYPE_NAME(*(*it));        \
	AssertObj(to_copy);                            \
	b.push_back(to_copy);                          \
	}                                              \
}


#define vector_delete_it(a, it)              \
	delete *it;                              \
	it = a.erase(it);   
#define vector_erase_it(a, it)              \
	it = a.erase(it);   

#define vector_free(a)                                   \
	for(auto it = a.begin(); it != a.end();it++){    \
	delete *it;                              \
	}\
	a.clear();

#define map_free(a)                                      \
	for(auto it = a.begin(); it != a.end(); it++){    \
	delete it->second;                       \
	}\
	a.clear();


#define mrmap_free(a)                                                 \
	for(auto it = a.getIterator(); it != a.endElement(); it++){    \
	delete it->second;                                 \
	}\
    a.clear();

#define vector_clear(a)  a.clear()

#define map_clear(a)   a.clear()

#define mrmap_clear(a)   a.clear()
#define sorted_vector_free(a)                                   \
	for(auto it = a.begin(); it != a.end(); it++){    \
	delete it->second;                              \
	}\
    a.clear();
#define sorted_vector_clear(a)   a.clear()


