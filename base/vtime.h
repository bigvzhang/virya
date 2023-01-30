#pragma once
#include <chrono>
#include <iostream>
#include <sstream>
#include <iomanip>
#include "vstring.h"

#ifdef _WIN32
#define localtime2tm(b,a) (localtime_s(a,b)==0)
#define gmtime2tm(b,a)    (gmtime_s(a,b)==0)
#else // linux or cygwin ...
#define localtime2tm(a,b) (localtime_r(a,b)!=nullptr)
#define gmtime2tm(a,b)    (gmtime_r(a,b)!=nullptr)
#endif

namespace virya {


template <class Clock, class Duration = typename Clock::duration>  
class time_point : public std::chrono::time_point<Clock, Duration> {
private:
	using PARENT =  std::chrono::time_point<Clock, Duration>;
	using THISTYP = time_point<Clock, Duration>;
public:
	time_point():PARENT(Clock::now()){}

	//std::ostream& operator>>(std::ostream& os){
	//	auto t_c = this->time_since_epoch().count() * Clock::period::num / Clock::period::den;
	//	struct tm t_m;
	//	if(!localtime_s(&t_m, &t_c) == 0){
	//		exit(1);
	//	}
	//	os << std::put_time(&t_m, "%Y-%m-%d %H:%M:%S");
	//	return os;
	//}


friend//template <class Clock, class Duration = typename Clock::duration>
std::ostream& operator<<(std::ostream& os, THISTYP&&tp){//time_point<Clock, Duration>& tp){
	//const std::time_t t_c = Clock::to_time_t(tp);
	auto t_c = tp.time_since_epoch().count() * Clock::period::num / Clock::period::den;
	struct tm t_m;
	if(!localtime2tm(&t_c, &t_m)){
		printf("Fatal error: fail to call localtime2tm: time_t:%lld\n", t_c);
		exit(1);
	}
	os << std::put_time(&t_m, "%Y-%m-%d %H:%M:%S");
	return os;
}

friend//template <class Clock, class Duration = typename Clock::duration>
std::ostream& operator<<(std::ostream& os, THISTYP&tp){//time_point<Clock, Duration>& tp){
	//const std::time_t t_c = Clock::to_time_t(tp);
	auto t_c = tp.time_since_epoch().count() * Clock::period::num / Clock::period::den;
	struct tm t_m;
	if(!localtime2tm(&t_c, &t_m)){
		printf("Fatal error: fail to call localtime2tm: time_t:%lld\n", t_c);
		exit(1);
	}
	os << std::put_time(&t_m, "%Y-%m-%d %H:%M:%S");
	return os;
}


std::string to_std_milli(){
	auto t_c     = this->time_since_epoch().count() * Clock::period::num / Clock::period::den;
	auto t_milli = this->time_since_epoch().count() * Clock::period::num % Clock::period::den * 1000 / Clock::period::den ; 
	struct tm m;
	if(!localtime2tm(&t_c, &m)){
		printf("Fatal error: fail to call localtime2tm: time_t:%lld\n", t_c);
		exit(1);
	}
	return format("%04d-%02d-%02d %02d:%02d:%02d.%03lld", 
		m.tm_year+1900, m.tm_mon+1, m.tm_mday, m.tm_hour, m.tm_min, m.tm_sec,t_milli);
}

std::string to_hhmiss_milli(bool compact){
	auto t_c = this->time_since_epoch().count() * Clock::period::num / Clock::period::den;
	auto t_milli = this->time_since_epoch().count() * Clock::period::num % Clock::period::den * 1000 / Clock::period::den;
	struct tm m;
	if(!localtime2tm(&t_c, &m)){
		printf("Fatal error: fail to call localtime2tm: time_t:%lld\n", t_c);
		exit(1);
	}
	if(compact)
		return format("%02d%02d%02d.%03lld", m.tm_hour, m.tm_min, m.tm_sec, t_milli);
	else
		return format("%02d:%02d:%02d.%03lld", m.tm_hour, m.tm_min, m.tm_sec, t_milli);
}

std::int64_t get_int64(){
	return this->time_since_epoch().count() * Clock::period::num /(Clock::period::den/1000);
}

};

using htime = time_point<std::chrono::high_resolution_clock>;
using vtime = time_point<std::chrono::system_clock>; // system clock
using ytime = time_point<std::chrono::steady_clock>; // steady clock

std::string fmtgtime(const char * fmt, std::time_t t); // format gmtime
std::string fmtltime(const char * fmt, std::time_t t); // format localtime
}// 
