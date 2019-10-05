#include <stdio.h>
#include <iostream>
#include <type_traits.h>


#include "MRFuncEntryMacro.h"

#define DEF_FUNC(X) X(int argc, char* argv[])


#define TRACE_CODE0(...)    printf("%-60s ==> ",  #__VA_ARGS__); __VA_ARGS__
#define TRACE_CODEn(...)    printf("%-60s ==> ",  #__VA_ARGS__); __VA_ARGS__;printf("\n")
#define TRACE_CODEv(...)    printf("%-60s ==> ",  #__VA_ARGS__); std::cout << (__VA_ARGS__) << "\n";
#define TRACE_CODE(...)     printf("%s\n",#__VA_ARGS__); __VA_ARGS__

#define EXPLAIN(x)          muranbase::center_stdout(x, 140, '=');
#define HORIZONTAL_LINE()   muranbase::center_stdout("=", 140, '=');
#define HORIZONTAL_LINE2()  muranbase::center_stdout("=", 140, '=');printf("\n");
#define PRINT_NEWLINE()     printf("\n");


#define TITLEH1(...)   muranbase::center_stdout(#__VA_ARGS__, 140, '=');
#define TITLEH2(...)   muranbase::center_stdout(#__VA_ARGS__, 120, '-');
#define TITLEH3(...)   muranbase::center_stdout(#__VA_ARGS__, 100, '.');



BEGIN_SECTION(vtest01_integral_constant)
namespace vya=virya;

int DEF_FUNC(vtest01_integral_constant){
    typedef vya::integral_constant<int, 2> two_t;
    typedef vya::integral_constant<int, 4> four_t;
 
	std::cout << std::boolalpha;
	
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
	
    typedef vya::integral_constant<int, 5> f_5;

	return 0;
}
END_SECTION(vtest01_integral_constant)

