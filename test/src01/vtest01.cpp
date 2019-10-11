
/** Introduction:
 The functions included are mainly to test items defined in type_info.
 */



#include <stdio.h>
#include <iostream>
#include <type_traits.h>

#include "MRFuncEntryMacro.h"
#include "MuRanCommonFuncs.h"


#define DEF_FUNC(X) X(int argc, char* argv[])



#define TRACE_CODE(...)     printf("%s\n",#__VA_ARGS__);         __VA_ARGS__
static  const char*                CODE_FORMAT{"%-60s==>"}; // default, must be static
#define TRACE_CODE0(...)    printf(CODE_FORMAT,  #__VA_ARGS__); __VA_ARGS__
#define TRACE_CODEn(...)    printf(CODE_FORMAT,  #__VA_ARGS__); __VA_ARGS__;printf("\n")
#define TRACE_CODEv(...)    printf(CODE_FORMAT,  #__VA_ARGS__); std::cout << (__VA_ARGS__) << "\n";

#define ANNOTATE(...)       printf("//%s\n", #__VA_ARGS__);
#define ANNOTATE0(...)      printf("//%s",   #__VA_ARGS__);
#define ANNOTATEn(...)      printf("//%s\n", #__VA_ARGS__); // equal ANNOTATE
#define TRACE_CODEok(...)   printf(CODE_FORMAT,  #__VA_ARGS__);__VA_ARGS__;printf(" <== compile OK\n");
#define ANNOTATEok(...)     printf(CODE_FORMAT,  #__VA_ARGS__);printf(" <== compile OK\n");
#define ANNOTATEe(...)      printf(CODE_FORMAT,  #__VA_ARGS__);printf(" <== compile error\n");
#define ANNOTATEw(...)      printf(CODE_FORMAT,  #__VA_ARGS__);printf(" <== warn although compile OK\n");

static const int                                      LEN_LINE = 120; // default, must be static
#define DRAW_LINE(...)      muranbase::stdout_putline(LEN_LINE, ##__VA_ARGS__);             // ONLY one parameter(fillchar) acceptable 
#define DRAW_LINEnn(...)    muranbase::stdout_putline(LEN_LINE, ##__VA_ARGS__);printf("\n");// ONLY one parameter(fillchar) acceptable
#define TITLEH1(...)        muranbase::center_stdout(#__VA_ARGS__, 4, LEN_LINE,    '=', true);
#define TITLEH2(...)        muranbase::center_stdout(#__VA_ARGS__, 4, LEN_LINE-20, '-', true);
#define TITLEH3(...)        muranbase::center_stdout(#__VA_ARGS__, 4, LEN_LINE-40, '.', true);



BEGIN_SECTION(vtest01_integral_constant)
namespace vya=virya;

int DEF_FUNC(vtest01_integral_constant){
 
	std::cout << std::boolalpha;
	
	TITLEH1(test integral_constant)
	typedef vya::integral_constant<int, 2> two_t;
    typedef vya::integral_constant<int, 4> four_t;

	
	TRACE_CODEv(vya::is_same<two_t, four_t>::value); 
    TRACE_CODEv(two_t::value*2 == four_t::value);

	
	TRACE_CODE0(printf("2_t:%d\n", two_t::value););
	TRACE_CODE0(printf("4_t:%d\n", four_t::value););
	TRACE_CODEv(two_t::value);
 
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
	
	TITLEH1(NOTICE, the type of a template non-type parameter must be integral)
    TRACE_CODEok(typedef vya::integral_constant<int, 5>   test_int_5;)
    TRACE_CODEok(typedef vya::integral_constant<short, 5>   test_short_5;)
	TRACE_CODEok(typedef vya::integral_constant<bool, true>   test_bool_true;)
	TITLEH2(if we use float, double as template non-type parameter, we will get compile error)
	ANNOTATEe(typedef vya::integral_constant<float, 5.005> test_float_5;)
	ANNOTATEe(typedef vya::integral_constant<double,5.0>  test_double_5;)
	TITLEH1(we can use interal_constant<>() instead of integral_constant<>::value to make the code clear)
    TRACE_CODEv(test_int_5() == test_int_5::value );
	ANNOTATEe(test_int_5() == test_int_5.value )

	DRAW_LINE();//FINISHED
	return 0;
}
END_SECTION(vtest01_integral_constant)

BEGIN_SECTION(vtest01_is_onetype)
namespace vya=virya;

template<class T,class X> struct wrap_type{typedef T type1; typedef X type2;};

int DEF_FUNC(vtest01_is_onetype){
	std::cout << std::boolalpha;
	static const char* CODE_FORMAT{"%-80s ==>"};
	TITLEH1(define type_is/type_eq to make code clear)
	#define type_is(T, t) (virya::is_##t<T>::value)
	#define type_eq(T, ...) (virya::is_##T<__VA_ARGS__>::value)
	ANNOTATE("#define type_is(T, t) (virya::is_##t<T>::value)");
	ANNOTATE("#define type_eq(T, ...) (virya::is_##T<__VA_ARGS__>::value)");
	TITLEH1(some typedefs)
	TRACE_CODE(typedef const int CONST_INT);
	TRACE_CODE(typedef volatile short VOLATILE_SHORT);
	TRACE_CODE(typedef const void CONST_VOID);

	TITLEH1(test remove_cv);
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
	
	TITLEH1(test is_void);
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

	DRAW_LINE();
	return 0;
}
END_SECTION(vtest01_is_onetype)

	
BEGIN_SECTION(vtest01_remove_reference)
namespace vya=virya;
static  const char*  CODE_FORMAT{"%-80s==>"};


int DEF_FUNC(vtest01_remove_reference){
	std::cout << std::boolalpha;
	TITLEH1(Test remove_reference);
	TRACE_CODEv(vya::is_same<double, double>::value);
	TRACE_CODEv(vya::is_same<double, double&>::value);
	TRACE_CODEv(vya::is_same<double, double&&>::value);
	TRACE_CODEv(vya::is_same<double, vya::remove_reference<double>::type>::value);
	TRACE_CODEv(vya::is_same<double, vya::remove_reference<double&>::type>::value);
	TRACE_CODEv(vya::is_same<double, vya::remove_reference<double&&>::type>());
	
	DRAW_LINE()
	return 0;
}

END_SECTION(vtest01_remove_reference)
