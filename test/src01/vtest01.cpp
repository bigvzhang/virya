
/** Introduction:
 The functions included are mainly to test items defined in type_info.
 */



#include <stdio.h>
#include <iostream>
#include <type_traits.h>

#include "MRTestCommon.h"
#include "vtest.h"
#define TOUR_GROUP tour801_

#define TRACE_CODE0(...)    printf(CODE_FORMAT,  #__VA_ARGS__); __VA_ARGS__
#define TRACE_CODEok(...)   printf(CODE_FORMAT,  #__VA_ARGS__);__VA_ARGS__;printf(" <== compile OK\n");
#define ANNOTATEe(...)      printf(CODE_FORMAT,  #__VA_ARGS__);printf(" <== compile error\n");

inline Whistle& operator >> (bool b, Whistle &w)         { std::cout << std::boolalpha << b;  return w; }
inline Whistle& operator >> (virya::true_type b, Whistle &w)         { std::cout << std::boolalpha << b.value;  return w; }
inline Whistle& operator << (Whistle &w, const char* s)  { std::cout << std::boolalpha << s;  return w; }

BEGIN_UNIT_(integral_constant)
namespace vya=virya;

int main(int argc, char* argv[]){
 
	std::cout << std::boolalpha;
	
	HEAD1(integral_constant - int); TRACE_SRC(1,2);
	typedef vya::integral_constant<int, 2> two_t;
	typedef vya::integral_constant<int, 4> four_t;

	
	TRACE_CODEv(vya::is_same<two_t, four_t>::value); 
    TRACE_CODEv(two_t::value*2 == four_t::value);

	
	TRACE_CODE0(printf("2_t:%d\n", two_t::value););
	TRACE_CODE0(printf("4_t:%d\n", four_t::value););
	TRACE_CODEv(two_t::value);
 
	HEAD1(integral_constant - enum); TRACE_SRC(1,6)
    enum class my_e {
       e1=1000,
       e2=1001
    };
    typedef vya::integral_constant<my_e, my_e::e1> my_e_e1;
    typedef vya::integral_constant<my_e, my_e::e2> my_e_e2;
 
	TRACE_CODE0(printf("%d\n",my_e_e1::value));
	TRACE_CODE0(printf("%d\n",my_e_e2::value));
	TRACE_CODEv(my_e_e1::value == my_e::e1);
	TRACE_CODEv(my_e_e1::value == my_e::e2);
	TRACE_CODEv(my_e_e1::value != my_e::e2);
	
    TRACE_CODEv(vya::is_same<my_e_e1, my_e_e2>::value);
    TRACE_CODEv(vya::is_same<my_e_e2, my_e_e2>::value);
	
	HEAD1(NOTICE, the type of a template non-type parameter must be integral)
    TRACE_CODEok(typedef vya::integral_constant<int, 5>   test_int_5;)
    TRACE_CODEok(typedef vya::integral_constant<short, 5>   test_short_5;)
	TRACE_CODEok(typedef vya::integral_constant<bool, true>   test_bool_true;)
	HEAD2s(if we use float, double as template non-type parameter, we will get compile error)
	ANNOTATEe(typedef vya::integral_constant<float, 5.005> test_float_5;)
	ANNOTATEe(typedef vya::integral_constant<double,5.0>  test_double_5;)
	HEAD1(we can use interal_constant<>() instead of integral_constant<>::value to make the code clear)
    TRACE_CODEv(test_int_5() == test_int_5::value );
	ANNOTATEe(test_int_5() == test_int_5.value )

	HORIZONTAL_LINE();//FINISHED
	return 0;
}
END_UNIT//integral_constant

BEGIN_UNIT_(is_convertible)
template <template<class, class> class CVT, class From, class To> constexpr bool export_v = CVT<From, To>::value;

class E { public: template<class T> E(T&&) { } };
class A {};
class B : public A {};
class C {};
class D { public: operator C(){return c;} C c;};
template<template<class A ,class B> class is_convertible>
void unit_func(){HEAD1(defintions); TRACE_SRC(-6,-2); 
	HEAD1("for primitive");
	is_convertible<int, short>::value              >> ECHOn();
	is_convertible<char, int>::value               >> ECHOn();
	HEAD1("for classes ");
	is_convertible<A*, B*>::value                  >> ECHOn();
	is_convertible<B*, A*>::value                  >> ECHOn();
	is_convertible<B,  A>::value                   >> ECHOn();
	is_convertible<D*, C*>::value                  >> ECHOn();
	is_convertible<D,  C>::value                   >> ECHOn();
	is_convertible<B*, C*>::value                  >> ECHOn();
	is_convertible<A,  E>::value                   >> ECHOn();
	HORIZONTAL_LINE();
}

template<template<class A ,class B> class is_convertible_v>
void unit_func_2(){HEAD1(defintions); TRACE_SRC(-6,-2); 
	HEAD1("for primitive");
	is_convertible_v<int, short>              >> ECHOn();
	is_convertible_v<char, int>               >> ECHOn();
	HEAD1("for classes ");
	is_convertible_v<A*, B*>                  >> ECHOn();
	is_convertible_v<B*, A*>                  >> ECHOn();
	is_convertible_v<B,  A>                   >> ECHOn();
	is_convertible_v<D*, C*>                  >> ECHOn();
	is_convertible_v<D,  C>                   >> ECHOn();
	is_convertible_v<B*, C*>                  >> ECHOn();
	is_convertible_v<A,  E>                   >> ECHOn();
	HORIZONTAL_LINE();
}

template<template<class,class> class is_convertible>
void TORESEARCH(){
	is_convertible<int, short>::value        >> ECHOn();
	/// 1 using is_convertible_v<A,B> = is_convertible<A,B>::value 
	///   is_convertible_v<int, short>         >> ECHOn();
    
    /// 2 why cannot pass is_converible_v
}



std::vector<virya::test::SubEntry> subEntries = {
	{"std",     unit_func<std::is_convertible>  },
	{"virya",   unit_func<virya::is_convertible>},
};

int main(int argc, char* argv[]){
	return virya::test::submain(subEntries, argc, argv);
}
END_UNIT // is_convertible

BEGIN_UNIT_(is_enum) namespace vya = virya;
struct A { enum E { }; };
enum E {};
enum class Ec : int {};
int main(int argc, char* argv[]){HEAD1(defintions); TRACE_SRC(-3,-1); HEAD1("");
	vya::is_enum<A>{}                        >> ECHOn();	
	vya::is_enum<E>{}                        >> ECHOn();	
	vya::is_enum<Ec>{}                       >> ECHOn();	
	vya::is_enum<int>{}                      >> ECHOn();	
	vya::is_enum<float>{}                    >> ECHOn();	
	return HORIZONTAL_LINE();
}
END_UNIT // is_enum

BEGIN_UNIT_(is_array) namespace vya = virya;

struct A {};
int main(int argc, char* argv[]){HEAD1(defintion); TRACE_SRC(-1,-1); HEAD1("");
    vya::is_array<A>{}                        >> ECHOn();
    vya::is_array<A[]>::value                 >> ECHOn();
    vya::is_array<A[3]>::value                >> ECHOn();
    vya::is_array<float>::value               >> ECHOn();
    vya::is_array<int>::value                 >> ECHOn();
    vya::is_array<int[]>::value               >> ECHOn();
    vya::is_array<int[3]>::value              >> ECHOn();
    vya::is_array<std::array<int, 3> >::value >> ECHOn();
	HORIZONTAL3();
    vya::is_array<char*[]>::value                           >> ECHOn();
    vya::is_array<decltype(argv)>::value                    >> ECHOn();
	char* x[]={nullptr}; vya::is_array<decltype(x)>::value  >> ECHOn();
	HORIZONTAL4s();
	int i[]={0}; vya::is_array<decltype(i)>::value          >> ECHOn();
	HORIZONTAL_LINE()
	SEEALSO(is_bounded_array, is_unbounded_array, extent, rank)
	return HORIZONTAL_LINE();
}
/*
TORESEARCH: tour on is_bounded_array and is_unbounded_array
     - methods
       - using macro 
       - using template function
       - using different functions, which are cloned by cc-copy  
*/

END_UNIT// is_array



BEGIN_UNIT_(is_union)

struct A {};
 
typedef union {
    int a;
    float b;
} B;
 
class C {
    B d;
};

enum E1{
};

enum class E2{
};

template <template<class> class is_union> 
void test_func(){HEAD1(Defition); TRACE_SRC(-18,-3); HEAD1("");
    is_union<A>::value    >> ECHOn(); 
    is_union<B>::value    >> ECHOn();
    is_union<C>::value    >> ECHOn();
    is_union<int>::value  >> ECHOn(); 

	is_union<E1>::value   >> ECHOn();
	is_union<E2>::value   >> ECHOn();

	HORIZONTAL_LINE();
}

std::vector<virya::test::SubEntry> subEntries = {
	virya::test::SubEntry("std",     test_func<std::is_union>),
	virya::test::SubEntry("virya",   test_func<virya::is_union>)
};

int main(int argc, char* argv[]){
	return virya::test::submain(subEntries, argc, argv);
}

END_UNIT// is_union


BEGIN_UNIT_(is_class)

using namespace __MR_CONCAT(TOUR_GROUP, is_union);

template <template<class> class is_class> 
void test_func(){HEAD1(Defition); TRACE_SRC(-47,-32); HEAD1("");
    is_class<A>::value    >> ECHOn(); 
    is_class<B>::value    >> ECHOn();
    is_class<C>::value    >> ECHOn();
    is_class<int>::value  >> ECHOn(); 

	is_class<E1>::value   >> ECHOn();
	is_class<E2>::value   >> ECHOn();
	HORIZONTAL_LINE();
}

std::vector<virya::test::SubEntry> subEntries = {
	virya::test::SubEntry("std",     test_func<std::is_class>),
	virya::test::SubEntry("virya",   test_func<virya::is_class>)
};

int main(int argc, char* argv[]){
	return virya::test::submain(subEntries, argc, argv);
}
END_UNIT//is_class

BEGIN_UNIT_(is_function)
int f();
 
struct A {
    int fun() const&;
};

template<typename>
struct PM_traits {};
 
template<class T, class U>
struct PM_traits<U T::*> {
    using member_type = U;
};

using PMf = PM_traits<decltype(&A::fun)>::member_type; // T is int() const&
 
template<template<class> class is_function> 
void test_func() { HEAD1(Defintions); TRACE_SRC(-17, -3);HORIZONTAL1();
    is_function<decltype(f)>::value >> ECHOn();
    is_function<A>::value           >> ECHOn();
    is_function<PMf>::value         >> ECHOn();
    is_function<int(int)>::value    >> ECHOn(); 
    is_function<int>::value         >> ECHOn();
}

std::vector<virya::test::SubEntry> subEntries = {
	virya::test::SubEntry("std",     test_func<std::is_function>),
	virya::test::SubEntry("virya",   test_func<virya::is_function>)
};

int main(int argc, char* argv[]){
	return virya::test::submain(subEntries, argc, argv);
}
END_UNIT//is_function

BEGIN_UNIT_(is_onetype)
namespace vya=virya;

template<class T,class X> struct wrap_type{typedef T type1; typedef X type2;};

int main(int argc, char* argv[]){
	std::cout << std::boolalpha;
	static const char* CODE_FORMAT{"%-80s ==>"};
	HEAD1(define type_is/type_eq to make code clear)
	#define type_is(T, t) (virya::is_##t<T>::value)
	#define type_eq(T, ...) (virya::is_##T<__VA_ARGS__>::value)
	ANNOTATE("#define type_is(T, t) (virya::is_##t<T>::value)");
	ANNOTATE("#define type_eq(T, ...) (virya::is_##T<__VA_ARGS__>::value)");
	HEAD1(some typedefs)
	TRACE_CODE(typedef const int CONST_INT);
	TRACE_CODE(typedef volatile short VOLATILE_SHORT);
	TRACE_CODE(typedef const void CONST_VOID);

	HEAD1(test remove_cv);
	TRACE_CODEv(vya::is_same<int, vya::remove_cv<const int>::type>::value);
    TRACE_CODEv(vya::is_same<int, vya::remove_cv<CONST_INT>::type>::value);
	TRACE_CODEv(vya::is_same<int, vya::remove_cvA<const int>::type>::value);
    TRACE_CODEv(vya::is_same<int, vya::remove_cvA<CONST_INT>::type>::value);
	TRACE_CODEv(vya::is_same<int, vya::remove_cvB<const int>::type>::value);
    TRACE_CODEv(vya::is_same<int, vya::remove_cvB<CONST_INT>::type>::value);
    TRACE_CODEv(vya::is_same<short, vya::remove_volatile<VOLATILE_SHORT>::type>::value);
    TRACE_CODEv(vya::is_same<short, vya::remove_cv<VOLATILE_SHORT>::type>::value);
    TRACE_CODEv(vya::is_same<int,   vya::remove_cv<VOLATILE_SHORT>::type>::value);
    TRACE_CODEv(vya::is_same<short, vya::remove_const<CONST_INT>::type>::value);
    TRACE_CODEv(vya::is_same<short, vya::remove_cv<CONST_INT>::type>::value);
	
	HEAD1(test is_void);
    TRACE_CODEv(vya::is_void<int>::value);
    TRACE_CODEv(vya::is_void<void>::value);
    TRACE_CODEv(type_is(void,          void));
    TRACE_CODEv(type_is(const void,    void));
    TRACE_CODEv(type_is(CONST_VOID,    void));
	TRACE_CODEv(type_is(volatile void, void));
	TRACE_CODEv(type_eq(void,          typename wrap_type<int, void>::type1));
	TRACE_CODEv(type_eq(void,          typename wrap_type<int, void>::type2));
	TRACE_CODEv(type_eq(void,          wrap_type<int, void>::type1));
	TRACE_CODEv(type_eq(void,          wrap_type<int, void>::type2));
	TRACE_CODEv(type_eq(void,          const void));
	std::cout << vya::integral_constant<int, 5>::value << "\n";

	HORIZONTAL_LINE();
	return 0;
}
END_UNIT//_is_onetype

	
BEGIN_UNIT_(remove_reference)
namespace vya=virya;
static  const char*  CODE_FORMAT{"%-80s==>"};


int main(int argc, char* argv[]){
	std::cout << std::boolalpha;
	HEAD1(Test remove_reference);
	TRACE_CODEv(vya::is_same<double, double>::value);
	TRACE_CODEv(vya::is_same<double, double&>::value);
	TRACE_CODEv(vya::is_same<double, double&&>::value);
	TRACE_CODEv(vya::is_same<double, vya::remove_reference<double>::type>::value);
	TRACE_CODEv(vya::is_same<double, vya::remove_reference<double&>::type>::value);
	TRACE_CODEv(vya::is_same<double, vya::remove_reference<double&&>::type>());
	
	HORIZONTAL_LINE()
	return 0;
}

END_UNIT//remove_reference
	
BEGIN_UNIT_(is_void)
namespace vya=virya;
//static  const char*  CODE_FORMAT{"%-80s==>"};


int main(int argc, char* argv[]){
	std::cout << std::boolalpha;
	HEAD1(Test is_void);
	TRACE_CODEv(vya::is_void<void>::value);
	TRACE_CODEv(vya::is_void<int>::value);
	TRACE_CODEv(vya::is_void<const void>::value);
	TRACE_CODEv(vya::is_void<const int>::value);
	TRACE_CODEv(vya::is_void<volatile void>::value);
	TRACE_CODEv(vya::is_void<volatile int>::value);
	
	HORIZONTAL_LINE()
	return 0;
}

END_UNIT// is_THE

