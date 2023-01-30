/**
* the macro defined in the file is for test purpose
* Notice, nerver included in a head file
*/

#include <iostream>

#ifndef VIRYA_ANNOTATE_H_
#define VIRYA_ANNOTATE_H_

#define TRACE_CODE(...)     printf("%s\n",#__VA_ARGS__);         __VA_ARGS__
static  const char*                CODE_FORMAT{"%-60s==>"}; // default, must be static
#define TRACE_CODE0(...)    printf(CODE_FORMAT,  #__VA_ARGS__); __VA_ARGS__;
#define TRACE_CODEn(...)    printf(CODE_FORMAT,  #__VA_ARGS__); __VA_ARGS__;printf("\n");
#define TRACE_CODEv(...)    printf(CODE_FORMAT,  #__VA_ARGS__); std::cout << (__VA_ARGS__) << "\n";
#define TRACE_CODEs(...)    printf(CODE_FORMAT,  #__VA_ARGS__); std::cout << to_string(__VA_ARGS__) << "\n";

#define ANNOTATE(...)       printf("//%s\n", #__VA_ARGS__);
#define ANNOTATE0(...)      printf("//%s",   #__VA_ARGS__);
#define ANNOTATEn(...)      printf("//%s\n", #__VA_ARGS__); // equal ANNOTATE
#define ANNOTATEe(...)      printf(CODE_FORMAT,  #__VA_ARGS__);printf(" <== compile error\n");
#define ANNOTATEw(...)      printf(CODE_FORMAT,  #__VA_ARGS__);printf(" <== warn although compile OK\n");

static const int                                      LEN_LINE = 120; // default, must be static
#define DRAW_LINE(...)      virya::stdout_putline(LEN_LINE, ##__VA_ARGS__);             // ONLY one parameter(fillchar) acceptable 
#define DRAW_LINEnn(...)    virya::stdout_putline(LEN_LINE, ##__VA_ARGS__);printf("\n");// ONLY one parameter(fillchar) acceptable
#define TITLEH1(...)        virya::center_stdout(#__VA_ARGS__, 4, LEN_LINE,    '=', true);
#define TITLEH2(...)        virya::center_stdout(#__VA_ARGS__, 4, LEN_LINE-20, '-', true);
#define TITLEH3(...)        virya::center_stdout(#__VA_ARGS__, 4, LEN_LINE-40, '.', true);

#ifdef _WIN32
#define vcTRACE_CODE  TRACE_CODE
#define vcTRACE_CODE0 TRACE_CODE0
#define vcTRACE_CODEn TRACE_CODEn
#define vcTRACE_CODEv TRACE_CODEv
#else
#define vcTRACE_CODE  ANNOTATEe
#define vcTRACE_CODE0 ANNOTATE0
#define vcTRACE_CODEn ANNOTATEe
#define vcTRACE_CODEv ANNOTATEe
#endif

#endif //  VIRYA_ANNOTATE_H_
