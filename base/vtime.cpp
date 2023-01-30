#include <cstring>
#include "vtime.h"

namespace virya{


std::string fmtgtime(const char * fmt, std::time_t t) { // use
	struct tm the_tm;
	if(!gmtime2tm(&t, &the_tm)){
		printf("Fatal error: fail to call gmtime2tm: time_t:%lld\n", t);
		exit(1);// abort program
	}
	std::string buf(31, '\0');
	while(std::strftime((char*)buf.data(), buf.size()+1, fmt, &the_tm) == 0){
		buf.resize(buf.size() + 32);
	}
	buf.resize(strlen(buf.c_str()));
	return buf;
}


std::string fmtltime(const char* fmt, std::time_t t) { // use
	struct tm the_tm;
	if(!localtime2tm(&t, &the_tm)){
		printf("Fatal error: fail to call localtime2tm: time_t:%lld\n", t);
		exit(1);// abort program
	}
	std::string buf(31, '\0');
	while(std::strftime((char*)buf.data(), buf.size() + 1, fmt, &the_tm) == 0){
		buf.resize(buf.size() + 32);
	}
	buf.resize(strlen(buf.c_str()));
	return buf;
}

}

// The following is only for test
#ifdef _MSC_VER
	#define TIME_FMT_VERSION 1
#elif __GNUC__ > 7
	#define TIME_FMT_VERSION 1
#elif __GNUC__ == 7
	#define TIME_FMT_VERSION 2
	#ifdef TIME_FMT_USING_BOOST_DATETIME
	#include <boost/date_time/local_time/local_time.hpp>
	#else
	#define BOOST_CHRONO_VERSION 3
	#include <boost/chrono/config.hpp>
	#include <boost/chrono/chrono_io.hpp>
	#include <boost/chrono/system_clocks.hpp>
	#include <boost/chrono/thread_clock.hpp>
	#include <boost/chrono/process_cpu_clocks.hpp>
	#endif
#else
#error "Unspecifed compiler"
#endif

namespace virya_experimental {
/** converts time_t to string
 *     Notice
 *       1. For windows, implement by using gmtime_s
 *       2. For others, gmtime_s is not available in CentOS6 and gmtime is not thread safe.
 *          So try to use boost library as following:
 *            (1) If using boost::chrono::time_fmt, we need to set BOOST_CHRONO_VERSION to 2
 *                and it will generate warnings like "header is deprecated" when compiling.
 *            (2) If using boost::date_time, it won't generate warnings when compiling.
 */
std::string time_fmt(std::time_t  t) {
#if  TIME_FMT_VERSION == 1 
	struct tm the_tm;
	if(!gmtime2tm(&t, &the_tm)){
		printf("Fatal error: fail to call gmtime2tm: time_t:%lld\n", t);
		exit(1);// abort program
	}
	//std::cout << std::put_time(&the_tm, "%D, %d %m %Y %T %Z") << std::endl;
	#define BUFSIZE1 48
	char buf[BUFSIZE1];
	auto len = std::strftime(buf, BUFSIZE1, "%a, %d %b %Y %T GMT", &the_tm);
	//std::cout << "len:" << len << "Time ==>" << buf << std::endl;
	return buf;
	#undef BUFSIZE1
#elif TIME_FMT_VERSION == 2 //defined(TIME_FMT_USING_BOOST_DATETIME)
	using namespace boost::gregorian;
	using namespace boost::posix_time;
	using namespace boost::local_time;
	using std::locale;
	std::ostringstream oss;
	time_facet* output_facet = new time_facet("%a, %d %b %Y %T GMT"); //TODO: verify whether to free it
	oss.imbue(locale(locale::classic(), output_facet));
	oss << from_time_t(t);
	return oss.str();
#elif TIME_FMT_VERSION == 3 //BOOST
	auto tp = boost::chrono::system_clock::from_time_t(t); // tp => time point
	std::ostringstream oss;
	oss << boost::chrono::time_fmt(boost::chrono::timezone::utc, "%a, %d %b %Y %T GMT") << tp;
	return oss.str();
#else
#error "Unknown method"
#endif
}

} // end namespace virya
