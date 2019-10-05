#pragma once
#include <string>

#define FORMAT_PIPE "\\\\.\\pipe\\muran_%s_%lld"

#if defined(_WIN32) || defined(_WIN64)
#define __MR_UNDERLYING_OS WINDOWS
#else
#define __FUNCTION__ __func__
#endif

namespace muranexception{
	using namespace std;
	enum MR_EXECPTION_TYPE{
		__EXCEPTION_GENERAL          =   0,
		__EXCEPTION_ERR_CSTR_NULL    =   101,
		__EXCEPTION_ERR_PTR_NULL     =   102,
		__EXCEPTION_NEW_OBJ_FAILED   =   103,
		__EXCEPTION_SHORT_RESOURCE   =   104,
		__EXCEPTION_ERR_SERIALIZE    =   105,
		__EXCEPTION_ERR_CONFIG       =   106,
		__EXCEPTION_PTR_MUST_NULL    =   107,
		__EXCEPTION_BAD_PATH         =   108,
		__EXCEPTION_IO               =   109,
		__EXCEPTION_SHORT_DATA       =   110,
		__EXCEPTION_VALUE_MUST_EQUAL =   111,
		__EXCEPTION_BAD_SET          =   200,
		__EXCEPTION_BAD_ENUM              = 201,
		__EXCEPTION_MORE_THAN_ONCE        = 202,
		__EXCEPTION_NOT_INITIALIZED       = 203,
		__EXCEPTION_BAD_CONSTRUCTOR       = 205,
		__EXCEPTION_BAD_DESTRUCTOR        = 290,
		__EXCEPTION_BAD_COPY_CONSTRUCTOR  = 206,
		__EXCEPTION_BAD_EQUAL_CONSTRUCTOR = 207,
		__EXCEPTION_BAD_DCHAR             = 208,
		__EXCEPTION_TODO                  = 209,
		__EXCEPTION_UNKNOWN               = 210,
		__EXCEPTION_OPEN_R_FILE           = 211,
		__EXCEPTION_OPEN_W_FILE           = 212,
		__EXCEPTION_BAD_DATA              = 213,
		__EXCEPTION_BAD_DATA_INTEGRITY    = 214,
		__EXCEPTION_BOUNDARY              = 215,
		__EXCEPTION_SYS_CALL              = 216,
	};
#define _TRACE_MREXCEPTION
#ifdef  _TRACE_MREXCEPTION
#if defined(_WIN32) || defined(_WIN64)
#	define MuRanException(...)         MRException(__EXCEPTION_GENERAL,       __FILE__, __LINE__,__FUNCTION__, __VA_ARGS__)
#	define MuRanExceptionBadConstructor(...)         MRException(__EXCEPTION_BAD_CONSTRUCTOR,       __FILE__, __LINE__,__FUNCTION__, __VA_ARGS__)
#	define MuRanExceptionBadDestructor(...)         MRException(__EXCEPTION_BAD_DESTRUCTOR,       __FILE__, __LINE__,__FUNCTION__, __VA_ARGS__)
#	define MuRanExceptionBadCopyConstructor(...)     MRException(__EXCEPTION_BAD_COPY_CONSTRUCTOR,       __FILE__, __LINE__,__FUNCTION__, __VA_ARGS__)
#	define MuRanExceptionBadEqualConstructor(...)    MRException(__EXCEPTION_BAD_EQUAL_CONSTRUCTOR,       __FILE__, __LINE__,__FUNCTION__, __VA_ARGS__)
#	define MuRanExceptionBadPath(...)  MRException(__EXCEPTION_BAD_PATH,      __FILE__, __LINE__,__FUNCTION__, __VA_ARGS__)
#	define MuRanExceptionBadEnum(...)  MRException(__EXCEPTION_BAD_ENUM,      __FILE__, __LINE__,__FUNCTION__, __VA_ARGS__)
#	define MuRanExceptionBadData(...)  MRException(__EXCEPTION_BAD_DATA,      __FILE__, __LINE__,__FUNCTION__, __VA_ARGS__)

#	define MuRanExceptionBadDataIntegrity(...)  MRException(__EXCEPTION_BAD_DATA_INTEGRITY,      __FILE__, __LINE__,__FUNCTION__, __VA_ARGS__)
#	define MuRanExceptionMoreThanOnce(...)  MRException(__EXCEPTION_MORE_THAN_ONCE,      __FILE__, __LINE__,__FUNCTION__, __VA_ARGS__)
#	define MuRanExceptionNotInitialized(...)  MRException(__EXCEPTION_NOT_INITIALIZED,      __FILE__, __LINE__,__FUNCTION__, __VA_ARGS__)
#	define MuRanExceptionBadSet(...)   MRException(__EXCEPTION_BAD_SET,       __FILE__, __LINE__,__FUNCTION__, __VA_ARGS__)
#	define MuRanExceptionTODO(...)     MRException(__EXCEPTION_TODO,          __FILE__, __LINE__,__FUNCTION__, __VA_ARGS__)
#	define MuRanExceptionCStrNull(...) MRException(__EXCEPTION_ERR_CSTR_NULL,       __FILE__, __LINE__,__FUNCTION__, __VA_ARGS__)
#	define MuRanExceptionPtrNull(...)  MRException(__EXCEPTION_ERR_PTR_NULL,  __FILE__, __LINE__,__FUNCTION__, __VA_ARGS__)
#	define MuRanExceptionNewFailed(...) MRException(__EXCEPTION_NEW_OBJ_FAILED,  __FILE__, __LINE__,__FUNCTION__, __VA_ARGS__)
#	define MuRanExceptionShortRes(...) MRException(__EXCEPTION_SHORT_RESOURCE,__FILE__, __LINE__,__FUNCTION__, __VA_ARGS__)
#	define MuRanExceptionShortData(...)MRException(__EXCEPTION_SHORT_DATA,__FILE__, __LINE__,__FUNCTION__, __VA_ARGS__)
#	define MuRanExceptionIO(...)       MRException(__EXCEPTION_IO,            __FILE__, __LINE__,__FUNCTION__, __VA_ARGS__)
#	define MuRanExceptionCfg(...)      MRExceptionCfg(__FILE__, __LINE__,__FUNCTION__, __VA_ARGS__)
#	define MuRanExceptionBadDChar(...) MRException(__EXCEPTION_BAD_DCHAR,  __FILE__, __LINE__,__FUNCTION__, __VA_ARGS__)
#	define MuRanExceptionUnknown(...)  MRException(__EXCEPTION_UNKNOWN,  __FILE__, __LINE__,__FUNCTION__, __VA_ARGS__)
#	define MuRanExceptionOpenReadFile(...) MRException(__EXCEPTION_OPEN_R_FILE,  __FILE__, __LINE__,__FUNCTION__, __VA_ARGS__)
#	define MuRanExceptionOpenWriteFile(...) MRException(__EXCEPTION_OPEN_W_FILE,  __FILE__, __LINE__,__FUNCTION__, __VA_ARGS__)
#	define MuRanExceptionBoundary(...) MRException(__EXCEPTION_BOUNDARY,  __FILE__, __LINE__,__FUNCTION__, __VA_ARGS__)
#	define MuRanExceptionSysCall(...)  MRException(__EXCEPTION_SYS_CALL,  __FILE__, __LINE__,__FUNCTION__, __VA_ARGS__)

#   define AssertObj(p)                if(p==nullptr) {throw MRException(__EXCEPTION_NEW_OBJ_FAILED,  __FILE__, __LINE__,__FUNCTION__);}
#   define AssertNotNull(p)            if(p==nullptr) {throw MRException(__EXCEPTION_ERR_PTR_NULL,    __FILE__, __LINE__,__FUNCTION__);}
#   define AssureNull(p)               if(p!=nullptr) {throw MRException(__EXCEPTION_PTR_MUST_NULL,   __FILE__, __LINE__,__FUNCTION__);}
#   define AssureEqual(t1,t2)          if(t1!=t2)     {throw MRException(__EXCEPTION_VALUE_MUST_EQUAL,  __FILE__, __LINE__,__FUNCTION__);}
#   define AssureTrue(v)               if(!(v))       {throw MRException(__EXCEPTION_VALUE_MUST_EQUAL,  __FILE__, __LINE__,__FUNCTION__);}
#   define new_s(obj,expr, ...)        obj = new expr;if(obj==nullptr){throw MRException(__EXCEPTION_NEW_OBJ_FAILED,  __FILE__, __LINE__,__FUNCTION__, __VA_ARGS__);}
#else
#	define MuRanException(__VA_ARGS__1...)         MRException(__EXCEPTION_GENERAL,       __FILE__, __LINE__,__FUNCTION__, ##__VA_ARGS__1)
#	define MuRanExceptionBadConstructor(__VA_ARGS__1...)         MRException(__EXCEPTION_BAD_CONSTRUCTOR,       __FILE__, __LINE__,__FUNCTION__, ##__VA_ARGS__1)
#	define MuRanExceptionBadDestructor(__VA_ARGS__1...)         MRException(__EXCEPTION_BAD_DESTRUCTOR,       __FILE__, __LINE__,__FUNCTION__, ##__VA_ARGS__1)
#	define MuRanExceptionBadCopyConstructor(__VA_ARGS__1...)     MRException(__EXCEPTION_BAD_COPY_CONSTRUCTOR,       __FILE__, __LINE__,__FUNCTION__, ##__VA_ARGS__1)
#	define MuRanExceptionBadEqualConstructor(__VA_ARGS__1...)    MRException(__EXCEPTION_BAD_EQUAL_CONSTRUCTOR,       __FILE__, __LINE__,__FUNCTION__, ##__VA_ARGS__1)
#	define MuRanExceptionBadPath(__VA_ARGS__1...)  MRException(__EXCEPTION_BAD_PATH,      __FILE__, __LINE__,__FUNCTION__, ##__VA_ARGS__1)
#	define MuRanExceptionBadEnum(__VA_ARGS__1...)  MRException(__EXCEPTION_BAD_ENUM,      __FILE__, __LINE__,__FUNCTION__, ##__VA_ARGS__1)
#	define MuRanExceptionBadData(...)  MRException(__EXCEPTION_BAD_DATA,      __FILE__, __LINE__,__FUNCTION__, ##__VA_ARGS__)

#	define MuRanExceptionBadDataIntegrity(__VA_ARGS__1...)  MRException(__EXCEPTION_BAD_DATA_INTEGRITY,      __FILE__, __LINE__,__FUNCTION__, ##__VA_ARGS__1)
#	define MuRanExceptionMoreThanOnce(__VA_ARGS__1...)  MRException(__EXCEPTION_MORE_THAN_ONCE,      __FILE__, __LINE__,__FUNCTION__, ##__VA_ARGS__1)
#	define MuRanExceptionNotInitialized(__VA_ARGS__1...)  MRException(__EXCEPTION_NOT_INITIALIZED,      __FILE__, __LINE__,__FUNCTION__, ##__VA_ARGS__1)
#	define MuRanExceptionBadSet(__VA_ARGS__1...)   MRException(__EXCEPTION_BAD_SET,       __FILE__, __LINE__,__FUNCTION__, ##__VA_ARGS__1)
#	define MuRanExceptionTODO(__VA_ARGS__1...)     MRException(__EXCEPTION_TODO,          __FILE__, __LINE__,__FUNCTION__, ##__VA_ARGS__1)
#	define MuRanExceptionCStrNull(__VA_ARGS__1...) MRException(__EXCEPTION_ERR_CSTR_NULL,       __FILE__, __LINE__,__FUNCTION__, ##__VA_ARGS__1)
#	define MuRanExceptionPtrNull(__VA_ARGS__1...)  MRException(__EXCEPTION_ERR_PTR_NULL,  __FILE__, __LINE__,__FUNCTION__, ##__VA_ARGS__1)
#	define MuRanExceptionNewFailed(__VA_ARGS__1...) MRException(__EXCEPTION_NEW_OBJ_FAILED,  __FILE__, __LINE__,__FUNCTION__, ##__VA_ARGS__1)
#	define MuRanExceptionShortRes(__VA_ARGS__1...) MRException(__EXCEPTION_SHORT_RESOURCE,__FILE__, __LINE__,__FUNCTION__, ##__VA_ARGS__1)
#	define MuRanExceptionShortData(__VA_ARGS__1...)MRException(__EXCEPTION_SHORT_DATA,__FILE__, __LINE__,__FUNCTION__, ##__VA_ARGS__1)
#	define MuRanExceptionIO(__VA_ARGS__1...)       MRException(__EXCEPTION_IO,            __FILE__, __LINE__,__FUNCTION__, ##__VA_ARGS__1)
#	define MuRanExceptionCfg(__VA_ARGS__1...)      MRExceptionCfg(__FILE__, __LINE__,__FUNCTION__, ##__VA_ARGS__1)
#	define MuRanExceptionBadDChar(__VA_ARGS__1...) MRException(__EXCEPTION_BAD_DCHAR,  __FILE__, __LINE__,__FUNCTION__, ##__VA_ARGS__1)
#	define MuRanExceptionUnknown(__VA_ARGS__1...)  MRException(__EXCEPTION_UNKNOWN,  __FILE__, __LINE__,__FUNCTION__, ##__VA_ARGS__1)
#	define MuRanExceptionOpenReadFile(__VA_ARGS__1...) MRException(__EXCEPTION_OPEN_R_FILE,  __FILE__, __LINE__,__FUNCTION__, ##__VA_ARGS__1)
#	define MuRanExceptionOpenWriteFile(__VA_ARGS__1...) MRException(__EXCEPTION_OPEN_W_FILE,  __FILE__, __LINE__,__FUNCTION__, ##__VA_ARGS__1)
#	define MuRanExceptionBoundary(__VA_ARGS__1...) MRException(__EXCEPTION_BOUNDARY,  __FILE__, __LINE__,__FUNCTION__, ##__VA_ARGS__1)
#	define MuRanExceptionSysCall(__VA_ARGS__1...)  MRException(__EXCEPTION_SYS_CALL,  __FILE__, __LINE__,__FUNCTION__, ##__VA_ARGS__1)

#   define AssertObj(p)                if(p==nullptr) {throw MRException(__EXCEPTION_NEW_OBJ_FAILED,  __FILE__, __LINE__,__FUNCTION__);}
#   define AssertNotNull(p)            if(p==nullptr) {throw MRException(__EXCEPTION_ERR_PTR_NULL,    __FILE__, __LINE__,__FUNCTION__);}
#   define AssureNull(p)               if(p!=nullptr) {throw MRException(__EXCEPTION_PTR_MUST_NULL,   __FILE__, __LINE__,__FUNCTION__);}
#   define AssureEqual(t1,t2)          if(t1!=t2)     {throw MRException(__EXCEPTION_VALUE_MUST_EQUAL,  __FILE__, __LINE__,__FUNCTION__);}
#   define AssureTrue(v)               if(!(v))       {throw MRException(__EXCEPTION_VALUE_MUST_EQUAL,  __FILE__, __LINE__,__FUNCTION__);}
#   define new_s(obj,expr, __VA_ARGS__1...)        obj = new expr;if(obj==nullptr){throw MRException(__EXCEPTION_NEW_OBJ_FAILED,  __FILE__, __LINE__,__FUNCTION__, ##__VA_ARGS__1);}
#endif
	
	class MRException{
	private:
		MR_EXECPTION_TYPE exceptionType;
	public:
		const char *  file;
		const int     lineno;
	private:
		const char * func;
		int    errorCode;
		char * errorMsg;
	public:
		MRException(MR_EXECPTION_TYPE typ, const char *  file, const int fileno, const char *func);
		MRException(MR_EXECPTION_TYPE typ, const char *  file, const int fileno, const char *func, int errorCode);
		MRException(MR_EXECPTION_TYPE typ, const char *  file, const int fileno, const char *func, int errorCode, const char* errorMsg);
		MRException(const MRException & o);
		virtual ~MRException();
	public:
		virtual string getErrorMsg();
		const char*    getExeFunc(){return func;}
		int getErrorCode(){return errorCode;}
		MR_EXECPTION_TYPE getExceptionTyp();
	};
	class MRExceptionCfg: public MRException{
	private:
		char *key;
	public:
		MRExceptionCfg(const char *  file, const int fileno, const char *func);
		MRExceptionCfg(const char *  file, const int fileno, const char *func, const char* key);
		virtual ~MRExceptionCfg();
		virtual string getErrorMsg();
	};
#else
#if defined(_WIN32) || defined(_WIN64)
#	define MuRanException, ##__VA_ARGS__         MRException(__EXCEPTION_GENERAL,       __FUNCTION__, __VA_ARGS__)
#	define MuRanExceptionBadConstructor(...)         MRException(__EXCEPTION_BAD_CONSTRUCTOR,__FUNCTION__, __VA_ARGS__)
#	define MuRanExceptionBadDestructor(...)          MRException(__EXCEPTION_BAD_DESTRUCTOR,__FUNCTION__, __VA_ARGS__)
#	define MuRanExceptionBadCopyConstructor(...)     MRException(__EXCEPTION_BAD_COPY_CONSTRUCTOR,__FUNCTION__, __VA_ARGS__)
#	define MuRanExceptionBadEqualConstructor(...)    MRException(__EXCEPTION_BAD_EQUAL_CONSTRUCTOR,__FUNCTION__, __VA_ARGS__)
#	define MuRanExceptionBadPath(...)                MRException(__EXCEPTION_BAD_PATH,      __FUNCTION__, __VA_ARGS__)
#	define MuRanExceptionBadData(...)                MRException(__EXCEPTION_BAD_DATA,      __FUNCTION__, __VA_ARGS__)
#	define MuRanExceptionBadDataIntegrity(...)  MRException(__EXCEPTION_BAD_DATA_INTEGRITY,      __FUNCTION__, __VA_ARGS__)
#	define MuRanExceptionBadEnum(...)  MRException(__EXCEPTION_BAD_ENUM,      __FUNCTION__, __VA_ARGS__)
#	define MuRanExceptionMoreThanOnce(...)  MRException(__EXCEPTION_MORE_THAN_ONCE,      __FUNCTION__, __VA_ARGS__)
#	define MuRanExceptionNotInitialized(...)  MRException(__EXCEPTION_NOT_INITIALIZED,      __FUNCTION__, __VA_ARGS__)
#	define MuRanExceptionBadSet(...)   MRException(__EXCEPTION_BAD_SET,      __FUNCTION__, __VA_ARGS__)
#	define MuRanExceptionTODO(...)     MRException(__EXCEPTION_TODO,      __FUNCTION__, __VA_ARGS__)
#	define MuRanExceptionCStrNull(...) MRException(__EXCEPTION_ERR_CSTR_NULL, __FUNCTION__, __VA_ARGS__)
#	define MuRanExceptionPtrNull(...)  MRException(__EXCEPTION_ERR_PTR_NULL,  __FUNCTION__, __VA_ARGS__)
#	define MuRanExceptionNewFailed(...) MRException(__EXCEPTION_NEW_OBJ_FAILED, __FUNCTION__, __VA_ARGS__)
#	define MuRanExceptionShortRes(...) MRException(__EXCEPTION_SHORT_RESOURCE,__FUNCTION__, __VA_ARGS__)
#	define MuRanExceptionShortData(...)MRException(__EXCEPTION_SHORT_DATA    ,__FUNCTION__, __VA_ARGS__)
#	define MuRanExceptionIO(...)       MRException(__EXCEPTION_IO,      __FUNCTION__, __VA_ARGS__)
#	define MuRanExceptionCfg(...)      MRExceptionCfg(__FUNCTION__, __VA_ARGS__)
#	define MuRanExceptionBadDChar(...) MRException(__EXCEPTION_BAD_DCHAR,    __FUNCTION__, __VA_ARGS__)
#	define MuRanExceptionUnknown(...)  MRException(__EXCEPTION_UNKNOWN,      __FUNCTION__, __VA_ARGS__)
#	define MuRanExceptionOpenReadFile(...)   MRException(__EXCEPTION_OPEN_R_FILE,      __FUNCTION__, __VA_ARGS__)
#	define MuRanExceptionOpenWriteFile(...)  MRException(__EXCEPTION_OPEN_W_FILE,      __FUNCTION__, __VA_ARGS__)
#	define MuRanExceptionBoundary(...) MRException(__EXCEPTION_BOUNDARY,  __FUNCTION__, __VA_ARGS__)
#	define MuRanExceptionSysCall(...)  MRException(__EXCEPTION_SYS_CALL,  __FUNCTION__, __VA_ARGS__)
#   define AssertObj(p)                if(p==nullptr) {throw MRException(__EXCEPTION_NEW_OBJ_FAILED,__FUNCTION__);}
#   define AssertNotNull(p)            if(p==nullptr) {throw MRException(__EXCEPTION_ERR_PTR_NULL,  __FUNCTION__);}
#   define AssureNull(p)               if(p!=nullptr) {throw MRException(__EXCEPTION_PTR_MUST_NULL, __FUNCTION__);}
#   define AssureEqual(t1,t2)          if(t1!=t2) {throw MRException(__EXCEPTION_VALUE_MUST_EQUAL, __FUNCTION__);}
#   define AssureTrue(v)               if(!(v))   {throw MRException(__EXCEPTION_VALUE_MUST_EQUAL, __FUNCTION__);}
#   define new_s(obj,expr, ...)        obj = new expr;if(obj==nullptr){throw MRException(__EXCEPTION_NEW_OBJ_FAILED, __FUNCTION__, __VA_ARGS__);}
#else
#	define MuRanException(__VA_ARGS_1_...)                       MRException(__EXCEPTION_GENERAL,       __FUNCTION__, ##__VA_ARGS__1)
#	define MuRanExceptionBadConstructor(__VA_ARGS__1...)         MRException(__EXCEPTION_BAD_CONSTRUCTOR,__FUNCTION__, ##__VA_ARGS__1)
#	define MuRanExceptionBadDestructor(__VA_ARGS__1...)          MRException(__EXCEPTION_BAD_DESTRUCTOR,__FUNCTION__, ##__VA_ARGS__1)
#	define MuRanExceptionBadCopyConstructor(__VA_ARGS__11...)     MRException(__EXCEPTION_BAD_COPY_CONSTRUCTOR,__FUNCTION__, ##__VA_ARGS__1)
#	define MuRanExceptionBadEqualConstructor(__VA_ARGS__1...)    MRException(__EXCEPTION_BAD_EQUAL_CONSTRUCTOR,__FUNCTION__, ##__VA_ARGS__1)
#	define MuRanExceptionBadPath(__VA_ARGS__1...)                MRException(__EXCEPTION_BAD_PATH,      __FUNCTION__, ##__VA_ARGS__1)
#	define MuRanExceptionBadData(__VA_ARGS__1...)                MRException(__EXCEPTION_BAD_DATA,      __FUNCTION__, ##__VA_ARGS__1)
#	define MuRanExceptionBadDataIntegrity(__VA_ARGS__1...)        MRException(__EXCEPTION_BAD_DATA_INTEGRITY,      __FUNCTION__, ##__VA_ARGS__1)
#	define MuRanExceptionBadEnum(__VA_ARGS__1...)                MRException(__EXCEPTION_BAD_ENUM,      __FUNCTION__, ##__VA_ARGS__1)
#	define MuRanExceptionMoreThanOnce(__VA_ARGS__1...)           MRException(__EXCEPTION_MORE_THAN_ONCE,      __FUNCTION__, ##__VA_ARGS__1)
#	define MuRanExceptionNotInitialized(__VA_ARGS__1...)         MRException(__EXCEPTION_NOT_INITIALIZED,      __FUNCTION__, ##__VA_ARGS__1)
#	define MuRanExceptionBadSet(__VA_ARGS__1...)                 MRException(__EXCEPTION_BAD_SET,      __FUNCTION__, ##__VA_ARGS__1)
#	define MuRanExceptionTODO(__VA_ARGS__1...)                   MRException(__EXCEPTION_TODO,      __FUNCTION__, ##__VA_ARGS__1)
#	define MuRanExceptionCStrNull(__VA_ARGS__1...)               MRException(__EXCEPTION_ERR_CSTR_NULL, __FUNCTION__, ##__VA_ARGS__1)
#	define MuRanExceptionPtrNull(__VA_ARGS__1...)                MRException(__EXCEPTION_ERR_PTR_NULL,  __FUNCTION__, ##__VA_ARGS__1)
#	define MuRanExceptionNewFailed(__VA_ARGS__1...)              MRException(__EXCEPTION_NEW_OBJ_FAILED, __FUNCTION__, ##__VA_ARGS__1)
#	define MuRanExceptionShortRes(__VA_ARGS__1...)               MRException(__EXCEPTION_SHORT_RESOURCE,__FUNCTION__, ##__VA_ARGS__1)
#	define MuRanExceptionShortData(__VA_ARGS__1...)              MRException(__EXCEPTION_SHORT_DATA    ,__FUNCTION__, ##__VA_ARGS__1)
#	define MuRanExceptionIO(__VA_ARGS__1...)                     MRException(__EXCEPTION_IO,      __FUNCTION__, ##__VA_ARGS__1)
#	define MuRanExceptionCfg(__VA_ARGS__1...)                    MRExceptionCfg(__FUNCTION__, ##__VA_ARGS__1)
#	define MuRanExceptionBadDChar(__VA_ARGS__1...)               MRException(__EXCEPTION_BAD_DCHAR,    __FUNCTION__, ##__VA_ARGS__1)
#	define MuRanExceptionUnknown(__VA_ARGS__1...)                MRException(__EXCEPTION_UNKNOWN,      __FUNCTION__, ##__VA_ARGS__1)
#	define MuRanExceptionOpenReadFile(__VA_ARGS__1...)           MRException(__EXCEPTION_OPEN_R_FILE,      __FUNCTION__, ##__VA_ARGS__1)
#	define MuRanExceptionOpenWriteFile(__VA_ARGS__1...)          MRException(__EXCEPTION_OPEN_W_FILE,      __FUNCTION__, ##__VA_ARGS__1)
#	define MuRanExceptionBoundary(__VA_ARGS__1...)               MRException(__EXCEPTION_BOUNDARY,  __FUNCTION__, ##__VA_ARGS__1)
#	define MuRanExceptionSysCall(__VA_ARGS__1...)                MRException(__EXCEPTION_SYS_CALL,  __FUNCTION__, ##__VA_ARGS__1)
#   define AssertObj(p)                if(p==nullptr) {throw MRException(__EXCEPTION_NEW_OBJ_FAILED,__FUNCTION__);}
#   define AssertNotNull(p)            if(p==nullptr) {throw MRException(__EXCEPTION_ERR_PTR_NULL,  __FUNCTION__);}
#   define AssureNull(p)               if(p!=nullptr) {throw MRException(__EXCEPTION_PTR_MUST_NULL, __FUNCTION__);}
#   define AssureEqual(t1,t2)          if(t1!=t2) {throw MRException(__EXCEPTION_VALUE_MUST_EQUAL, __FUNCTION__);}
#   define AssureTrue(v)               if(!(v))   {throw MRException(__EXCEPTION_VALUE_MUST_EQUAL, __FUNCTION__);}
#   define new_s(obj,expr, __VA_ARGS__1...)        obj = new expr;if(obj==nullptr){throw MRException(__EXCEPTION_NEW_OBJ_FAILED, __FUNCTION__, ##__VA_ARGS__1);}
#endif

	class MRException{
	private:
		MR_EXECPTION_TYPE exceptionType;
		const char * func;
		int    errorCode;
		char * errorMsg;
	public:
		MRException(MR_EXECPTION_TYPE typ, const char *func);
		MRException(MR_EXECPTION_TYPE typ, const char *func, int errorCode);
		MRException(MR_EXECPTION_TYPE typ, const char *func, int errorCode, char* errorMsg);
		MRException(const MRException & o);
		virtual ~MRException();
	public:
		virtual string getErrorMsg();
		const char*    getExeFunc(){return func;}
		MR_EXECPTION_TYPE getExceptionTyp();

		
	};
	class MRExceptionCfg: MRException{
	private:
		char *key;
	public:
		MRExceptionCfg(const char *func);
		MRExceptionCfg(const char *func, const char* key);
		virtual ~MRExceptionCfg();
		virtual string getErrorMsg();
	};
#endif

	//class MRExpnCStrNull: MuRanException{
	//public:
	//	MRExpnCStrNull();
	//	MRExpnCStrNull(char* errorMsg);
	//	virtual ~MRExpnCStrNull();
	//};

	//class MuRanExceptionPtrNull: MuRanException{
	//public:
	//	MuRanExceptionPtrNull();
	//	MuRanExceptionPtrNull(char* errorMsg);
	//	virtual ~MuRanExceptionPtrNull();
	//};

	//class MuRanExceptionPtrInvalid: MuRanException{
	//public:
	//	MuRanExceptionPtrInvalid();
	//	MuRanExceptionPtrInvalid(char* errorMsg);
	//	virtual ~MuRanExceptionPtrInvalid();
	//};

	//class MuRanExceptionEmptyString: MuRanException{
	//public:
	//	MuRanExceptionEmptyString();
	//	MuRanExceptionEmptyString(char* errorMsg);
	//	virtual ~MuRanExceptionEmptyString();
	//};

	//class MuRanExceptionSerialize: MuRanException{
	//public:
	//	MuRanExceptionSerialize();
	//	MuRanExceptionSerialize(char* errorMsg);
	//	virtual ~MuRanExceptionSerialize();
	//};


}

#define TOUCH_THROW(...){try{__VA_ARGS__}catch(...){}}



