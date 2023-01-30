#pragma once
#include <chrono>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <tuple>
#include <mutex>

#include "vtime.h"

namespace virya_tuple {

template<typename F, typename Tuple, size_t ...S >
decltype(auto) apply_impl(F&& fn, Tuple&& t, std::index_sequence<S...>)
{
  return std::forward<F>(fn)(std::get<S>(std::forward<Tuple>(t))...);
}

template<typename F, typename Tuple>
decltype(auto) apply(F&& fn, Tuple&& t)
{
  std::size_t constexpr tSize
    = std::tuple_size<typename std::remove_reference<Tuple>::type>::value;
  return apply_impl(std::forward<F>(fn),
                          std::forward<Tuple>(t),
                          std::make_index_sequence<tSize>());
}

}// namespace virya_tuple


namespace virya_tuple2 {

template<typename F, typename Tuple, size_t ...S>
decltype(auto) apply_impl(F&& fn, Tuple&& t, std::index_sequence<S...>)
{
  return std::forward<F>(fn)(std::get<S>(std::forward<Tuple>(t))...);
}

template<typename F, typename Tuple, typename...Parameters>
decltype(auto) apply(F&& fn, Tuple&& t, Parameters&&...parameters)
{
  auto t2 = std::forward_as_tuple(parameters...); // TAG:forward_as_tuple

  auto t3 = std::tuple_cat(t2, t);
  std::size_t constexpr tSize = std::tuple_size<typename std::remove_reference<decltype(t3)>::type>::value;

  return apply_impl(std::forward<F>(fn),
                          std::forward<decltype(t3)>(t3),
                          std::make_index_sequence<tSize>());
}

}// namespace virya_tuple

namespace virya {
namespace utility{

struct TimeRecord{
	vtime       t1;
	std::string msg;
	~TimeRecord();
};

struct ConsoleProtector{// will disable console close button
	ConsoleProtector();
	~ConsoleProtector();
};

class PrintThread: public std::ostringstream
{
public:
    PrintThread() = default;
protected:
    static std::mutex _mutexPrint;
};

class coutThread: public PrintThread {
public:
	 ~coutThread()
    {
        std::lock_guard<std::mutex> guard(_mutexPrint);
        std::cout << this->str();
    }
};

class cerrThread: public PrintThread {
public:
	 ~cerrThread()
    {
        std::lock_guard<std::mutex> guard(_mutexPrint);
        std::cerr << this->str();
    }
};


}// namespace utility
}// namespace virya

