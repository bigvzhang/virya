#include <stdio.h>
#include <string>
#include "MRException.h"
#include "MuRanCommonFuncs.h"
using namespace muranbase;
static FILE*  _p_default_exception_stream = stderr;
FILE**        _pp_actual_exception_stream = &_p_default_exception_stream;

namespace muranexception{
	
	// Notice, function name seems constant and eternal in the program, so we don't need to copy it.

#ifdef  _TRACE_MREXCEPTION
	MRException::MRException(MR_EXECPTION_TYPE typ, const char* file, const int lineno, const char* f):
		exceptionType(typ),
		file(file),
		lineno(lineno),
		func(f),
		errorCode(0),
		errorMsg(nullptr){
			if(*_pp_actual_exception_stream != nullptr)
				fprintf(*_pp_actual_exception_stream,"Exception: File: %40s[%4d], Func:%40s\n", file, lineno , f);
		}

	MRException::MRException(MR_EXECPTION_TYPE typ, const char* file, const int lineno, const char* f, int errorCode):
		exceptionType(typ),
			file(file),
			lineno(lineno),
			func(f),
			errorCode(errorCode),
			errorMsg(nullptr){
			if(*_pp_actual_exception_stream != nullptr)
				fprintf(*_pp_actual_exception_stream,"Exception: File: %40s[%4d], Func:%40s, Code:%d\n", file, lineno, f, errorCode);
		}


	MRException::MRException(MR_EXECPTION_TYPE typ, const char* file, const int lineno, const char* f, int errorCode, const char* errorMsg):		
	exceptionType(typ),
		file(file),
		lineno(lineno),
		func(f),
		errorCode(errorCode),
		errorMsg(nullptr){
			if(errorMsg != nullptr) copy_const_cstr(&this->errorMsg, errorMsg); // in case the memory leak
			if(*_pp_actual_exception_stream != nullptr)
				fprintf(*_pp_actual_exception_stream,"Exception: File: %40s[%4d], Func:%40s, Code:%d, Msg:%s\n", file, lineno, f, errorCode, errorMsg);
	}

	MRException::MRException(const MRException & o):
	exceptionType(o.exceptionType),
		file(o.file),
		lineno(o.lineno),
		func(o.func),
		errorCode(o.errorCode),
		errorMsg(nullptr){
			if(o.errorMsg != nullptr) copy_cstr(&this->errorMsg, o.errorMsg, true);
	}
#else 
	MRException::MRException(MR_EXECPTION_TYPE typ, const char* f):
		exceptionType(typ),
			func(f),
			errorCode(0),
			errorMsg(nullptr){}

	MRException::MRException(MR_EXECPTION_TYPE typ, const char* f, int errorCode):
		exceptionType(typ),
			func(f),
			errorCode(errorCode),
			errorMsg(nullptr){}


	MRException::MRException(MR_EXECPTION_TYPE typ, const char* f, int errorCode, char* errorMsg):		
		exceptionType(typ),
			func(f),
			errorCode(errorCode),
			errorMsg(nullptr){
		if(errorMsg != nullptr) copy_cstr(&this->errorMsg, errorMsg, true); // in case the memory leak
	}

	MRException::MRException(const MRException & o):
		exceptionType(o.exceptionType),
			func(o.func),
			errorCode(o.errorCode),
			errorMsg(nullptr){
		if(o.errorMsg!=nullptr)copy_cstr(&this->errorMsg, o.errorMsg, true);
	}
#endif

	MRException::~MRException(){
		if(errorMsg != nullptr){delete errorMsg;}
	}

	string MRException::getErrorMsg(){
		if(errorMsg != NULL){return errorMsg;}
		else{return "";}
	}

	MR_EXECPTION_TYPE MRException::getExceptionTyp(){
		return this->exceptionType;
	}


	//MRExpnCStrNull::MRExpnCStrNull() : MuRanException(__EXCEPTION_ERR_CSTR_NULL){}
	//MRExpnCStrNull::MRExpnCStrNull(char* errorMsg) : MuRanException(__EXCEPTION_ERR_CSTR_NULL, errorMsg){}
	//MRExpnCStrNull::~MRExpnCStrNull() {}

	//MuRanExceptionPtrNull::MuRanExceptionPtrNull() : MuRanException(__EXCEPTION_ERR_PTR_NULL){}
	//MuRanExceptionPtrNull::MuRanExceptionPtrNull(char* errorMsg) : MuRanException(__EXCEPTION_ERR_PTR_NULL, errorMsg){}
	//MuRanExceptionPtrNull::~MuRanExceptionPtrNull(){}

	//MuRanExceptionPtrInvalid::MuRanExceptionPtrInvalid() : MuRanException(__EXCEPTION_ERR_PTR_INVALID){}
	//MuRanExceptionPtrInvalid::MuRanExceptionPtrInvalid(char* errorMsg) : MuRanException(__EXCEPTION_ERR_PTR_INVALID, errorMsg){}
	//MuRanExceptionPtrInvalid::~MuRanExceptionPtrInvalid(){}

	//MuRanExceptionEmptyString::MuRanExceptionEmptyString(): MuRanException(__EXCEPTION_ERR_SERIALIZE){}
	//MuRanExceptionEmptyString::MuRanExceptionEmptyString(char* errorMsg) : MuRanException(__EXCEPTION_ERR_SERIALIZE, errorMsg){}
	//MuRanExceptionEmptyString::~MuRanExceptionEmptyString(){}


	//MuRanExceptionSerialize::MuRanExceptionSerialize() : MuRanException(__EXCEPTION_ERR_SERIALIZE){}
	//MuRanExceptionSerialize::MuRanExceptionSerialize(char* errorMsg) : MuRanException(__EXCEPTION_ERR_SERIALIZE, errorMsg){}
	//MuRanExceptionSerialize::~MuRanExceptionSerialize(){}

#ifdef _TRACE_MREXCEPTION
	MRExceptionCfg::MRExceptionCfg(const char *  file, const int lineno, const char* func) : MRException(__EXCEPTION_ERR_CONFIG,file, lineno, func, __EXCEPTION_ERR_CONFIG){key = nullptr;}
	MRExceptionCfg::MRExceptionCfg(const char *  file, const int lineno, const char* func, const char* key) : MRException(__EXCEPTION_ERR_CONFIG,file, lineno, func, __EXCEPTION_ERR_CONFIG){
		this->key = nullptr;
		copy_cstr(&this->key, (char*)key, true);
	}
#else
	MRExceptionCfg::MRExceptionCfg(const char* func) : MRException(__EXCEPTION_ERR_CONFIG, func, __EXCEPTION_ERR_CONFIG){key = nullptr;}
	MRExceptionCfg::MRExceptionCfg(const char* func, const char* key) : MRException(__EXCEPTION_ERR_CONFIG, func, __EXCEPTION_ERR_CONFIG){
		this->key = nullptr;
		copy_cstr(&this->key, (char*)key, true);
	}
#endif

	MRExceptionCfg::~MRExceptionCfg(){
		if(key != nullptr){delete key;}
	}
	string MRExceptionCfg::getErrorMsg(){
		if(key != NULL){return format("Key:%s is not found!", key);}
		else{return "";}
	}
}

