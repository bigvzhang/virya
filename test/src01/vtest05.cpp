
/** Introduction:
 The functions included are mainly to test items defined in type_traits.
 */



#include <stdio.h>
#include <iostream>
#include <typeinfo>

#include "vtestcommon.h"
#define TOUR_GROUP tour20005_


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

	HEAD1(test std::sort)
	TRACE_CODE(std::vector<int> A = {8,9,3,7,105,101,103,102,104,2,1,4,6,5};)
	TRACE_CODEs(A);
	TRACE_CODE(std::sort (A.begin(),   A.begin()+4));
	TRACE_CODEs(A);
	TRACE_CODE(std::sort (A.begin()+9, A.end()));
	TRACE_CODEs(A);
	TRACE_CODE(std::sort (A.begin(),   A.end()));
	TRACE_CODEs(A);
	HORIZONTAL_LINE()
	return 0;
}
END_SECTION(vtest05_sort)

BEGIN_UNIT_(sort_by)
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


int main(int argc, char* argv[]){
	std::cout << std::boolalpha;

	HEAD1(This is test to order one list according to one the other)
	TRACE_CODE(std::vector<int> A = {8,9,3,7,2,1,4,6,5};);
	TRACE_CODE(std::vector<int> B = {19,18,17,16,15,14,13,12,11};);
	TRACE_CODE(std::vector<int> C = {28,29,26,27,24,25,21,22,23};);
	TRACE_CODE(std::vector<int> X = {11,12};);

	TRACE_CODEs(X);
	TRACE_CODEv(sort_by(A,X));
	TRACE_CODEs(A);
	TRACE_CODEs(B);
	TRACE_CODEs(C);
	TRACE_CODE_(sort_by(A,B));TRACE_CODEs(B);
	TRACE_CODE_(sort_by(A,C));TRACE_CODEs(C);
	
	
	HORIZONTAL_LINE()
	return 0;
}
END_UNIT // sort_by


