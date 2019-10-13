
/** Introduction:
 The functions included are mainly to test items defined in type_traits.
 */



#include <stdio.h>
#include <iostream>
#include <typeinfo>

#include "MRFuncEntryMacro.h"
#include "MuRanCommonFuncs.h"


#define DEF_FUNC(X) X(int argc, char* argv[])



#define TRACE_CODE(...)     printf("%s\n",#__VA_ARGS__);         __VA_ARGS__
static  const char*                CODE_FORMAT{"%-60s==>"}; // default, must be static
#define TRACE_CODE0(...)    printf(CODE_FORMAT,  #__VA_ARGS__); __VA_ARGS__;
#define TRACE_CODEn(...)    printf(CODE_FORMAT,  #__VA_ARGS__); __VA_ARGS__;printf("\n");
#define TRACE_CODEv(...)    printf(CODE_FORMAT,  #__VA_ARGS__); std::cout << (__VA_ARGS__) << "\n";
#define TRACE_CODEs(...)    printf(CODE_FORMAT,  #__VA_ARGS__); std::cout << to_string(__VA_ARGS__) << "\n";

#define TRACE_v(...)        std::cout << (__VA_ARGS__);          printf("<==%s\n",  #__VA_ARGS__); 
#define TRACE_s(...)         std::cout << to_string(__VA_ARGS__);printf("<==%s\n",  #__VA_ARGS__);

#define ANNOTATE(...)       printf("//%s\n", #__VA_ARGS__);
#define ANNOTATE0(...)      printf("//%s",   #__VA_ARGS__);
#define ANNOTATEn(...)      printf("//%s\n", #__VA_ARGS__); // equal ANNOTATE
#define ANNOTATEe(...)      printf(CODE_FORMAT,  #__VA_ARGS__);printf(" <== compile error\n");
#define ANNOTATEw(...)      printf(CODE_FORMAT,  #__VA_ARGS__);printf(" <== warn although compile OK\n");

static const int                                      LEN_LINE = 120; // default, must be static
#define DRAW_LINE(...)      muranbase::stdout_putline(LEN_LINE, ##__VA_ARGS__);             // ONLY one parameter(fillchar) acceptable 
#define DRAW_LINEnn(...)    muranbase::stdout_putline(LEN_LINE, ##__VA_ARGS__);printf("\n");// ONLY one parameter(fillchar) acceptable
#define TITLEH1(...)        muranbase::center_stdout(#__VA_ARGS__, 4, LEN_LINE,    '=', true);
#define TITLEH2(...)        muranbase::center_stdout(#__VA_ARGS__, 4, LEN_LINE-20, '-', true);
#define TITLEH3(...)        muranbase::center_stdout(#__VA_ARGS__, 4, LEN_LINE-40, '.', true);

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

template<class T> std::string to_string(const std::vector<T>&vct){
	std::string rtn="{";
	auto it = vct.begin();
	if(it!=vct.end()){
		rtn += std::to_string(*it);
		while(++it != vct.end()){
			rtn += ","+ std::to_string(*it);
		}
		rtn+="}";
	}else{
		rtn+="}";
	}
	return rtn;
}

BEGIN_SECTION(vtest05_sort)
int DEF_FUNC(vtest05_sort){
	std::cout << std::boolalpha;

	TITLEH1(test std::sort)
	TRACE_CODE(std::vector<int> A = {8,9,3,7,105,101,103,102,104,2,1,4,6,5};)
	TRACE_CODEs(A);
	TRACE_CODE(std::sort (A.begin(),   A.begin()+4));
	TRACE_CODEs(A);
	TRACE_CODE(std::sort (A.begin()+9, A.end()));
	TRACE_CODEs(A);
	TRACE_CODE(std::sort (A.begin(),   A.end()));
	TRACE_CODEs(A);
	DRAW_LINE()
	return 0;
}
END_SECTION(vtest05_sort)

BEGIN_CODE(vtest05_sort_by)
template<class T>void rank_idx(const T& a, std::vector<size_t> &r){// a: source list; r: rank idx of the source(based on index)
	r.resize(a.size());
	if(a.size() == 0)
		return;
	r[0] = 0;
	for(size_t i = 1; i < a.size(); i++){// forward
		bool modified = false; 
		for(size_t j = 0; j < i; j++){
			if(a[i] < a[r[j]]){// the forward is smaller, move the left one position
				for(size_t k = i; k > j; k--){
					r[k] = r[k-1];
				}
				r[j]     = i; // refresh it
				modified = true;
				//std::cout<<".^."<<"{i:"<<i<<"("<<a[i]<<"),j("<<j<<"," << a[j]<<")}"; 
				//TRACE_CODEs(r);

				break;
			}
		}
		if(!modified){
			r[i] = i;
			//std::cout<<"..+"; TRACE_CODEs(r);
		}
	}
}

template<class T>void rank(const T& a, std::vector<size_t> &r){// a: source list; r: rank of the source(based on index)
	r.resize(a.size());
	if(a.size() == 0)
		return;
	for(size_t i = 0; i < a.size(); i++){// forward
		for(size_t j = 0; j < a.size(); j++){
			if(i != j){
				if(a[i] < a[j]){
				}else{
					r[i]++;
				}
			}
		}
	}
}

template<class T> bool sort_by(const std::vector<T>& m, std::vector<T>& o){//T:(vector,list,set); m: model; n: object to sort
	if(m.size() != o.size()){
		return false;
	}
	if(m.size() == 0){
		return true;
	}
	
	std::vector<size_t> rank_m, rank_pos;
	rank_idx(m, rank_pos);
	//TRACE_CODEs(rank_pos);


	std::vector<size_t> rank_o;
	rank(o, rank_o);
	//TRACE_CODEs(rank_o);

	std::vector<T> tmp; tmp.resize(o.size());
	for(size_t i = 0; i < rank_o.size(); i++){
		tmp[rank_pos[rank_o[i]]] = o[i];
	}
	std::copy(tmp.begin(), tmp.end(), o.begin());
	//TRACE_CODEs(tmp);

	return true;
}

END_CODE(vtest05_sort_by)

BEGIN_SECTION(vtest05_sort_by)
int DEF_FUNC(vtest05_sort_by){
	std::cout << std::boolalpha;

	TITLEH1(This is test to order one list according to one the other)
	TRACE_CODE(std::vector<int> A = {8,9,3,7,2,1,4,6,5};);
	TRACE_CODE(std::vector<int> B = {19,18,17,16,15,14,13,12,11};);
	TRACE_CODE(std::vector<int> C = {28,29,26,27,24,25,21,22,23};);
	TRACE_CODE(std::vector<int> X = {11,12};);

	TRACE_CODEs(X);
	TRACE_CODEv(sort_by(A,X));
	TRACE_CODEs(A);
	TRACE_CODEs(B);
	TRACE_CODEs(C);
	TRACE_CODE0(sort_by(A,B));TRACE_s(B);
	TRACE_CODE0(sort_by(A,C));TRACE_s(C);
	
	
	DRAW_LINE()
	return 0;
}
END_SECTION(vtest05_sort_by)


