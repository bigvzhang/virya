// C++11
// most of the content is copied from the standard library
#ifndef _CXX_VIRYA__TYPE_TRAITS_
#define _CXX_VIRYA__TYPE_TRINTS_ 1
namespace virya {

// helper class:
template <class T, T v>          struct integral_constant;
template<bool B>                 using  bool_constant = integral_constant<bool, B>;
typedef bool_constant<true>             true_type;
typedef bool_constant<false>            false_type;

template<class T, class U>       struct is_same;
template<class T>                struct is_same<T,T>;

// implement
template <class _Tp, _Tp __v> struct integral_constant {
    static const _Tp value;
    typedef _Tp               value_type;
    typedef integral_constant type;
    constexpr operator value_type() const {return value;}
};
template <class _Tp, _Tp __v> 
constexpr const _Tp integral_constant<_Tp, __v>::value = __v;

template<class T, class U> struct is_same       : false_type {};
template<class T>          struct is_same<T, T> : true_type {};
 	
  
} // namespace virya

#endif //_CXX_VIRYA__TYPE_TRAITS_
