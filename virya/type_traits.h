// C++11
// most of the content is copied from the standard library
#ifndef _CXX_VIRYA__TYPE_TRAITS_
#define _CXX_VIRYA__TYPE_TRINTS_ 1
namespace virya {

// helper class:
template<class T, T v>           struct integral_constant;
template<bool B>                 using  bool_constant = integral_constant<bool, B>;
typedef bool_constant<true>             true_type;
typedef bool_constant<false>            false_type;

template<class T, class U>       struct is_same;
template<class T>                struct is_same<T,T>;

// implement
#ifdef _WIN32
template<class _Tp, _Tp __v> struct integral_constant {
    static const _Tp value = __v;
    typedef _Tp           value_type;
    typedef integral_constant type;
    constexpr operator value_type() const {return value;}
};
#else
template<class _Tp, _Tp __v> struct integral_constant {
    static const _Tp value;
    typedef _Tp           value_type;
    typedef integral_constant type;
    constexpr operator value_type() const {return value;}
};
template<class _Tp, _Tp __v> 
constexpr const _Tp integral_constant<_Tp, __v>::value = __v;
#endif

template<class T>           struct is_array      : false_type {};
template<class T>           struct is_array<T[]> : true_type {};
template<class T, size_t N> struct is_array<T[N]> : true_type {};
template<class T>           struct is_bounded_array         : false_type {};
//template<class T>           struct is_bounded_array<T[]>    : false_type {}; no necessary
template<class T, size_t N> struct is_bounded_array<T[N]>   : true_type {};
template<class T>           struct is_unbounded_array       : false_type {};
template<class T>           struct is_unbounded_array<T[]>  : true_type {};
//template<class T, size_t N> struct is_unbounded_array<T[N]> : false_type {}; no necessary

template<class T>           struct is_enum       : integral_constant<bool, __is_enum(T)> {};

template<class T, class U> struct is_same       : false_type {};
template<class T>          struct is_same<T, T> : true_type {};

template<class _Tp> struct is_const            : public false_type {};
template<class _Tp> struct is_const<_Tp const> : public true_type {};
template<class _Tp> struct is_volatile               : public false_type {};
template<class _Tp> struct is_volatile<_Tp volatile> : public true_type {};

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
template <class T>         struct _is_void        : public __is_void<typename remove_cv<T>::type> {};
template <class T>         struct is_void         : public is_same<void, typename remove_cv<T>::type>{};

// __is_nullptr_t
template <class _Tp> struct __is_nullptr_t_impl            : public false_type {};
template <>          struct __is_nullptr_t_impl<nullptr_t> : public true_type {};
template <class _Tp> struct __is_nullptr_t                 : public __is_nullptr_t_impl<typename remove_cv<_Tp>::type> {};

// is_reference is_lvalue_referenc is_rvalue_reference
template <class _Tp> struct is_lvalue_reference       : public false_type {};
template <class _Tp> struct is_lvalue_reference<_Tp&> : public true_type {};
template <class _Tp> struct is_rvalue_reference        : public false_type {};
template <class _Tp> struct is_rvalue_reference<_Tp&&> : public true_type {};
template <class _Tp> struct is_reference        : public false_type {};
template <class _Tp> struct is_reference<_Tp&>  : public true_type {};
template <class _Tp> struct is_reference<_Tp&&> : public true_type {};


// the helper class
struct __two {char __lx[2];};

// is_union
template <class _Ty> struct is_union : bool_constant<__is_union(_Ty)> {}; // determine whether _Ty is a union
template <class _Ty> constexpr bool is_union_v = __is_union(_Ty);


// is_class
namespace __is_class_imp
{
template <class _Tp> char  __test(int _Tp::*);
template <class _Tp> __two __test(...);
}
template <class _Tp> struct is_class : public integral_constant<bool, sizeof(__is_class_imp::__test<_Tp>(0)) == 1 && !is_union<_Tp>::value> {};


// is_function
//   copy from llvm
namespace __is_function_imp
{
struct __dummy_type {};
template <class _Tp> char  __test(_Tp*);
template <class _Tp> char __test(__dummy_type);
template <class _Tp> __two __test(...);
template <class _Tp> _Tp&  __source(int);
template <class _Tp> __dummy_type __source(...);

template <class _Tp, bool = is_class<_Tp>::value ||
                            is_union<_Tp>::value ||
                            is_void<_Tp>::value  ||
                            is_reference<_Tp>::value ||
                            __is_nullptr_t<_Tp>::value >
struct _is_function
    : public integral_constant<bool, sizeof(__test<_Tp>(__source<_Tp>(0))) == 1>
    {};
template <class _Tp> struct _is_function<_Tp, true> : public false_type {};
}
template <class _Tp> struct is_function : public __is_function_imp::_is_function<_Tp> {};
template <class _Tp> constexpr bool is_function_v = is_function<_Tp>::value;


template <class _Bp, class _Dp> struct is_base_of: public integral_constant<bool, __is_base_of(_Bp, _Dp)> {};

namespace __is_convertible_imp1{ // copy from cppreference
/*template<class T>
auto is_returnable(int) -> decltype(
    void(static_cast<T(*)()>(nullptr)), true_type{}
);
namespace detail{
template<class T>
auto test_returnable(int) -> decltype(
    void(static_cast<T(*)()>(nullptr)), true_type{}
);
template<class>
auto test_returnable(...) ->false_type;
 
template<class From, class To>
auto test_implicitly_convertible(int) -> decltype(
    void(declval<void(&)(To)>()(declval<From>())), true_type{}
);
template<class, class>
auto test_implicitly_convertible(...) -> false_type;
}// namespace detail
template<class From, class To> struct is_convertible : integral_constant<bool,
    (decltype(detail::test_returnable<To>(0))::value &&
     decltype(detail::test_implicitly_convertible<From, To>(0))::value) ||
    (is_void<From>::value && is_void<To>::value)
> {};
*/
}// namespace __is_convertible_imp1

namespace __is_convertible_imp2{ // is_convertible - copy from llvm
namespace helper
{
template <class _Tp> void  __test_convert(_Tp);

template <class _From, class _To, class = void>
struct __is_convertible_test : public false_type {};

template <class _From, class _To>
struct __is_convertible_test<_From, _To,
    decltype(_VSTD::helper::__test_convert<_To>(_VSTD::declval<_From>()))> : public true_type
{};

template <class _Tp, bool _IsArray =    is_array<_Tp>::value,
                     bool _IsFunction = is_function<_Tp>::value,
                     bool _IsVoid =     is_void<_Tp>::value>
                     struct __is_array_function_or_void                          {enum {value = 0};};
template <class _Tp> struct __is_array_function_or_void<_Tp, true, false, false> {enum {value = 1};};
template <class _Tp> struct __is_array_function_or_void<_Tp, false, true, false> {enum {value = 2};};
template <class _Tp> struct __is_array_function_or_void<_Tp, false, false, true> {enum {value = 3};};
}

template <class _Tp,
    unsigned = helper::__is_array_function_or_void<typename remove_reference<_Tp>::type>::value>
struct __is_convertible_check
{
    static const size_t __v = 0;
};

template <class _Tp>
struct __is_convertible_check<_Tp, 0>
{
    static const size_t __v = sizeof(_Tp);
};

template <class _T1, class _T2,
    unsigned _T1_is_array_function_or_void = helper::__is_array_function_or_void<_T1>::value,
    unsigned _T2_is_array_function_or_void = helper::__is_array_function_or_void<_T2>::value>
struct __is_convertible
    : public integral_constant<bool,
       helper::__is_convertible_test<_T1, _T2>::value
         && !(!is_function<_T1>::value && !is_reference<_T1>::value && is_reference<_T2>::value
              && (!is_const<typename remove_reference<_T2>::type>::value
                  || is_volatile<typename remove_reference<_T2>::type>::value)
                  && (is_same<typename remove_cv<_T1>::type,
                              typename remove_cv<typename remove_reference<_T2>::type>::type>::value
                      || is_base_of<typename remove_reference<_T2>::type, _T1>::value))
    >
{};

template <class _T1, class _T2> struct __is_convertible<_T1, _T2, 0, 1> : public false_type {};
template <class _T1, class _T2> struct __is_convertible<_T1, _T2, 1, 1> : public false_type {};
template <class _T1, class _T2> struct __is_convertible<_T1, _T2, 2, 1> : public false_type {};
template <class _T1, class _T2> struct __is_convertible<_T1, _T2, 3, 1> : public false_type {};

template <class _T1, class _T2> struct __is_convertible<_T1, _T2, 0, 2> : public false_type {};
template <class _T1, class _T2> struct __is_convertible<_T1, _T2, 1, 2> : public false_type {};
template <class _T1, class _T2> struct __is_convertible<_T1, _T2, 2, 2> : public false_type {};
template <class _T1, class _T2> struct __is_convertible<_T1, _T2, 3, 2> : public false_type {};

template <class _T1, class _T2> struct __is_convertible<_T1, _T2, 0, 3> : public false_type {};
template <class _T1, class _T2> struct __is_convertible<_T1, _T2, 1, 3> : public false_type {};
template <class _T1, class _T2> struct __is_convertible<_T1, _T2, 2, 3> : public false_type {};
template <class _T1, class _T2> struct __is_convertible<_T1, _T2, 3, 3> : public true_type {};

template <class _T1, class _T2> struct  is_convertible
    : public __is_convertible<_T1, _T2>
{
    static const size_t __complete_check1 = __is_convertible_check<_T1>::__v;
    static const size_t __complete_check2 = __is_convertible_check<_T2>::__v;
};

template <class _From, class _To> bool is_convertible_v = is_convertible<_From, _To>::value;
}// namespace __is_convertible_imp2

inline namespace __is_convertible_imp3 {
template <class _From, class _To> struct is_convertible : bool_constant<__is_convertible_to(_From, _To)> {};
}

} // namespace virya

#endif //_CXX_VIRYA__TYPE_TRAITS_
