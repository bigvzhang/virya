#pragma once
#define __MR_11TH(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, ...) a11
#define __MR_LEFT (  
#define __MR_RIGHT )  
#define __MA_PASS(...) __VA_ARGS__ 
#define __MR_CONCAT(a, b)  __MR_CONCAT5(a, b)
#define __MR_CONCAT1(a, b) a ## b
#define __MR_CONCAT2(a, b) __MR_CONCAT1(a, b)
#define __MR_CONCAT3(a, b) __MR_CONCAT2(a, b)
#define __MR_CONCAT4(a, b) __MR_CONCAT3(a, b)
#define __MR_CONCAT5(a, b) __MR_CONCAT4(a, b)
#if  defined(_WIN32) && ! defined(__clang__)
//#define __MR_12TH(a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, ...) a12
#define __MR_11TH_re(x, ...) __MA_PASS(__VA_ARGS__,9,8,7,6,5,4,3,2,1,0)                         //  1. if x is there, the last comma(,) in(__VA_ARGS__) will be deleted
#define __MR_VACOUNT(...)    __MR_11TH __MR_LEFT __MR_11TH_re(dummy1,dummy2, __VA_ARGS__) __MR_RIGHT// ^2. two dummies to esure the previous(__VA_ARGS__) is not empty
#define __MR_11TH_ZERO_re(x, ...) __MA_PASS(__VA_ARGS__,1,1,1,1,1,1,1,1,1,0)                         //  1. if x is there, the last comma(,) in(__VA_ARGS__) will be deleted
#define __MR_VAZERO(...)          __MR_11TH __MR_LEFT __MR_11TH_ZERO_re(dummy1,dummy2, __VA_ARGS__) __MR_RIGHT// ^2. two dummies to esure the previous(__VA_ARGS__) is not empty
#else
#define __MR_VACOUNT(...) __MR_11TH(dummy, ##__VA_ARGS__, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0)
#define __MR_VAZERO(...)  __MR_11TH(dummy, ##__VA_ARGS__, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0)
#endif 
/*
#define str_in(s, ...)                  __MR_CONCAT1(str_in, __MR_VACOUNT(__VA_ARGS__))(s, ##__VA_ARGS__)
#define str_in0(s)                      false
#define str_in1(s,s1)                   strcmp(s,s1) == 0
#define str_in2(s,s1,s2)                strcmp(s,s2) == 0 || str_in1(s,s1)
#define str_in3(s,s1,s2,s3)             strcmp(s,s3) == 0 || str_in2(s,s1,s2)   
#define str_in4(s,s1,s2,s3,s4)          strcmp(s,s4) == 0 || str_in3(s,s1,s2,s3)
#define str_in5(s,s1,s2,s3,s4,s5)          strcmp(s,s5) == 0 || str_in4(s,s1,s2,s3,s4)
#define str_in6(s,s1,s2,s3,s4,s5,s6)          strcmp(s,s6) == 0 || str_in5(s,s1,s2,s3,s4,s5)
#define str_in7(s,s1,s2,s3,s4,s5,s6,s7)          strcmp(s,s7) == 0 || str_in6(s,s1,s2,s3,s4,s5,s6)
#define str_in8(s,s1,s2,s3,s4,s5,s6,s7,s8)          strcmp(s,s8) == 0 || str_in7(s,s1,s2,s3,s4,s5,s6,s7)
#define str_in9(s,s1,s2,s3,s4,s5,s6,s7,s8,s9)          strcmp(s,s9) == 0 || str_in8(s,s1,s2,s3,s4,s5,s6,s7,s8)
#define str_in10(s,s1,s2,s3,s4,s5,s6,s7,s8,s9,s10)          strcmp(s,s10) == 0 || str_in9(s,s1,s2,s3,s4,s5,s6,s7,s8,s9)
#define str_in11(s,s1,s2,s3,s4,s5,s6,s7,s8,s9,s10,s11)          strcmp(s,s11) == 0 || str_in10(s,s1,s2,s3,s4,s5,s6,s7,s8,s9,s10))
*/

