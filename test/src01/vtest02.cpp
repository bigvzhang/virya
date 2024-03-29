
/** Introduction:
 The functions included are mainly to test items defined in type_traits.
 */



#include <stdio.h>
#include <iostream>
#include <typeinfo>

#include "vtestcommon.h"
#define TOUR_GROUP tour20002_



#define DEF_FUNC(X) X(int argc, char* argv[])




BEGIN_UNIT_(typeinfo)
//namespace vya=virya; typeid is c++ intenal operator

int main(int argc, char* argv[]){
 
	std::cout << std::boolalpha;
	

	HEAD1(test typeid and its return value(type_info))

	TRACE_CODE(int i = 5;);
	TRACE_CODE(int *j = &i);
	TRACE_CODEv(typeid(i).name()); 
	TRACE_CODEv(typeid(j).name()); 
	TRACE_CODEv(typeid(5).name()); 
	TRACE_CODEv(typeid("5").name()); 
	TRACE_CODEv(typeid(5).name()); 
	TRACE_CODEv(typeid(0.5).name()); 
 
	HORIZONTAL_LINE();// over

	return 0;
}
END_UNIT //typeinfo

	
BEGIN_UNIT_(cast)
//namespace vya=virya; cast is c++ internal operator
namespace n1{
struct A{int a;};
struct B:public A{int b; B(int n1, int n2        ):A{n1},b(n2){}};
struct C:public B{int c; C(int n1, int n2, int n3):B(n1,n2),c(n3){}};

std::string to_string(A&a){return std::string("{") +std::to_string(a.a)+ std::string("}");}
std::string to_string(B&b){return std::string("{") +std::to_string(b.a)+", "+std::to_string(b.b)+ std::string("}");}
std::string to_string(C&c){return std::string("{") +std::to_string(c.a)+", "+std::to_string(c.b)+", "+std::to_string(c.c)+ std::string("}");}
	
}

namespace n2{
	
struct A{int a; A(int n1):a(n1){} virtual ~A(){}};
struct B:public A{int b; B(int n1, int n2        ):A{n1},b(n2){}};
struct C:public B{int c; C(int n1, int n2, int n3):B(n1,n2),c(n3){}};

std::string to_string(A&a){return std::string("{") +std::to_string(a.a)+ std::string("}");}
std::string to_string(B&b){return std::string("{") +std::to_string(b.a)+", "+std::to_string(b.b)+ std::string("}");}
std::string to_string(C&c){return std::string("{") +std::to_string(c.a)+", "+std::to_string(c.b)+", "+std::to_string(c.c)+ std::string("}");}
}

template<class Obj> void printObj(Obj*obj){std::cout << (obj == nullptr ? std::string("null") : to_string(*obj));}

#define TRACE_CODEp(...)    printf(CODE_FORMAT,  #__VA_ARGS__); printObj(__VA_ARGS__); std::cout << "\n";


int main(int argc, char* argv[]){
 
	std::cout << std::boolalpha;
	HEAD1(test for operators cast, static_cast and dynamic_cast)
	
	HEAD1(define some variables)
	TRACE_CODE(int n1 = 8;)
	TRACE_CODE(int n2 = 5;)
	TRACE_CODE(float f1 = n1/n2);
	
	HEAD1(test cast for primitive types);
	TRACE_CODE(float f2 = static_cast<float>(n1)/n2;)
	ANNOTATE(float f3 = dynamic_cast<float>(n1)/n2; <=ERROR)
	TRACE_CODEv(f1);
	TRACE_CODEv(f2);
	{
		using namespace n1;
		HEAD1(test cast for classes, types are not polymorphic);
		TRACE_CODE(A a={100};)
		TRACE_CODE(B b={500,501};)
		TRACE_CODE(C c{800,801,802};)

		HEAD2(test static_cast, directly)
		TRACE_CODEp(static_cast<A*>(&a));
		TRACE_CODEp(static_cast<A*>(&b));
		TRACE_CODEp(static_cast<A*>(&c));

		ANNOTATEw(static_cast<B*>(&a));
		TRACE_CODEp(static_cast<B*>(&b));
		TRACE_CODEp(static_cast<B*>(&c));

		ANNOTATEw(static_cast<C*>(&a));
		ANNOTATEw(static_cast<C*>(&b));
		TRACE_CODEp(static_cast<C*>(&c));

		HEAD1(test dynamic_cast)
		HEAD1(directly)
		TRACE_CODEp(dynamic_cast<A*>(&a));
		TRACE_CODEp(dynamic_cast<A*>(&b));
		TRACE_CODEp(dynamic_cast<A*>(&c));
		ANNOTATEe(dynamic_cast<B*>(&a));
		TRACE_CODEp(dynamic_cast<B*>(&b));
		TRACE_CODEp(dynamic_cast<B*>(&c));
		ANNOTATEe(dynamic_cast<C*>(&a));
		ANNOTATEe(dynamic_cast<C*>(&b));
		TRACE_CODEp(dynamic_cast<C*>(&c));
		HEAD2(through func)
		TRACE_CODE(auto funcA =[](A*x){printObj(dynamic_cast<A*>(x));};);
		ANNOTATEe(auto funcB =[](A*x){printObj(dynamic_cast<B*>(x));};);
		ANNOTATEe(auto funcC =[](A*x){printObj(dynamic_cast<C*>(x));};);
		TRACE_CODEn(funcA(&a));
		TRACE_CODEn(funcA(&b));
		TRACE_CODEn(funcA(&c));		
	}

	{// clone code 
		using namespace n2;
		HEAD1(test cast for classes, types are polymorphic);
		TRACE_CODE(A a={100};)
		TRACE_CODE(B b={500,501};)
		TRACE_CODE(C c{800,801,802};)

		HEAD2(test static_cast, directly)
		TRACE_CODEp(static_cast<A*>(&a));
		TRACE_CODEp(static_cast<A*>(&b));
		TRACE_CODEp(static_cast<A*>(&c));

		ANNOTATEw(static_cast<B*>(&a));
		TRACE_CODEp(static_cast<B*>(&b));
		TRACE_CODEp(static_cast<B*>(&c));

		ANNOTATEw(static_cast<C*>(&a));
		ANNOTATEw(static_cast<C*>(&b));
		TRACE_CODEp(static_cast<C*>(&c));

		HEAD2(test dynamic_cast: types are polymorphic)
		HEAD3(directly)
		TRACE_CODEp(dynamic_cast<A*>(&a));
		TRACE_CODEp(dynamic_cast<A*>(&b));
		TRACE_CODEp(dynamic_cast<A*>(&c));
		TRACE_CODEp(dynamic_cast<B*>(&a));
		TRACE_CODEp(dynamic_cast<B*>(&b));
		TRACE_CODEp(dynamic_cast<B*>(&c));
		TRACE_CODEp(dynamic_cast<C*>(&a));
		TRACE_CODEp(dynamic_cast<C*>(&b));
		TRACE_CODEp(dynamic_cast<C*>(&c));
		HEAD3(through func)
		TRACE_CODE(auto funcA =[](A*x){printObj(dynamic_cast<A*>(x));};);
		TRACE_CODE(auto funcB =[](A*x){printObj(dynamic_cast<B*>(x));};);
		TRACE_CODE(auto funcC =[](A*x){printObj(dynamic_cast<C*>(x));};);
		TRACE_CODEn(funcA(&a));
		TRACE_CODEn(funcA(&b));
		TRACE_CODEn(funcA(&c));		
		TRACE_CODEn(funcB(&a));
		TRACE_CODEn(funcB(&b));
		TRACE_CODEn(funcB(&c));		
		TRACE_CODEn(funcC(&a));
		TRACE_CODEn(funcC(&b));
		TRACE_CODEn(funcC(&c));		
	}	

	
	HORIZONTAL_LINE();// over

	return 0;
}

END_UNIT//cast
