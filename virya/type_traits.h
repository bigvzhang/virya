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
#ifdef _WIN32
template <class _Tp, _Tp __v> struct integral_constant {
    static const _Tp value = __v;
    typedef _Tp           value_type;
    typedef integral_constant type;
    constexpr operator value_type() const {return value;}
};
#else
template <class _Tp, _Tp __v> struct integral_constant {
    static const _Tp value;
    typedef _Tp           value_type;
    typedef integral_constant type;
    constexpr operator value_type() const {return value;}
};
template <class _Tp, _Tp __v> 
constexpr const _Tp integral_constant<_Tp, __v>::value = __v;
#endif

template<class T, class U> struct is_same       : false_type {};
template<class T>          struct is_same<T, T> : true_type {};

template<class T>          struct remove_const{ typedef T type; };
template<class T>          struct remove_const<const T>{ typedef T type; };
template<class T>          struct remove_volatile{ typedef T type; };
template<class T>          struct remove_volatile<volatile T>{ typedef T type; };
template<class T>          using  remove_cv = remove_const<typename remove_volatile<T>::type>; 	
template<class T>          struct remove_cvA:public remove_const<typename remove_volatile<T>::type>{};
template<class T>          struct remove_cvB{typedef typename remove_const<typename remove_volatile<T>::type>::type type;};
 
template<class T>          struct remove_reference     {typedef T type;};
template<class T>          struct remove_reference<T&> {typedef T type;};
template<class T>          struct remove_reference<T&&>{typedef T type;};
 

template <class T>         struct __is_void       : public false_type {};
template <>                struct __is_void<void> : public true_type {};
template <class T>         struct is_void         : public __is_void<typename remove_cv<T>::type> {};

} // namespace virya

#endif //_CXX_VIRYA__TYPE_TRAITS_
