/** Introduction:
 The functions included are mainly to test items defined in memory
 */
#include <stdio.h>
#include <iostream>
#include <typeinfo>
#include <memory>
#include <mutex>
#include <thread>
#include <chrono>
#include <sstream>
#include <fstream>

#include "MRFuncEntryMacro.h"
#include "MuRanCommonFuncs.h"


#define DEF_FUNC(X) X(int argc, char* argv[])



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



BEGIN_SECTION(vtest06_shared_ptr)

class A1 {
public:
	A1(){printf("Constructor: %s\n", __FUNCTION__);}
	~A1(){printf("Destructor: %s\n", __FUNCTION__);}
};

class A2 : public A1 {
public:	
	A2(){printf("Constructor: %s\n", __FUNCTION__);}
	~A2(){printf("Destructor: %s\n", __FUNCTION__);}
};

static std::mutex mtx;


template<class T> std::string to_string(std::shared_ptr<T>& ref){
	std::stringstream ss;
	ss << "Address: " << ref.get() << " UseCount:" << ref.use_count();
	return ss.str();
}

void f(std::shared_ptr<A1> pA1){
	std::this_thread::sleep_for(std::chrono::seconds(3));
	std::shared_ptr<A1> local_obj = pA1;
	{
		std::lock_guard<std::mutex> guard(mtx);
		TRACE_CODEs(local_obj);
	}
}

int DEF_FUNC(vtest06_shared_ptr){
	TITLEH1(test shared_ptr)
	TRACE_CODE(std::shared_ptr<A1> sp = std::make_shared<A2>();)
	TRACE_CODEs(sp);
	TRACE_CODE(std::thread t1(f, sp), t2(f, sp), t3(f, sp);)
	TRACE_CODEs(sp);
	TRACE_CODE(sp.reset());
	TRACE_CODEs(sp);

	TRACE_CODE(t1.join(); t2.join(); t3.join();)
	DRAW_LINE();
	ANNOTATE(if sp.reset() not called, Destructor will be called under the below line)
	DRAW_LINE();
	return 0;
}

END_SECTION(vtest06_shared_ptr)

	
BEGIN_SECTION(vtest06_guard_ptr)

class A1 {
public:
	A1(){printf("Constructor: %s\n", __FUNCTION__);}
	~A1(){printf("Destructor: %s\n", __FUNCTION__);}
};

class A2 : public A1 {
public:	
	A2(){printf("Constructor: %s\n", __FUNCTION__);}
	~A2(){printf("Destructor: %s\n", __FUNCTION__);}
};



static std::mutex mtx;




int DEF_FUNC(vtest06_guard_ptr){
	TITLEH1(test guard_ptr)
//	TRACE_CODE(std::shared_ptr<A1> sp = std::make_shared<A2>();)
//	TRACE_CODEs(sp);
//	TRACE_CODE(std::thread t1(f, sp), t2(f, sp), t3(f, sp);)
//	TRACE_CODEs(sp);
//	TRACE_CODE(sp.reset());
//	TRACE_CODEs(sp);
//
//	TRACE_CODE(t1.join(); t2.join(); t3.join();)
//	DRAW_LINE();
//	ANNOTATE(if sp.reset() not called, Destructor will be called below the below line)
	DRAW_LINE();
	return 0;
}

END_SECTION(vtest06_guard_ptr)
	
BEGIN_SECTION(vtest06_weak_ptr)
	
std::weak_ptr<int> gw;
 
void observe()
{
    std::cout << "use_count == " << gw.use_count() << ": ";
    if (auto spt = gw.lock()) { // Has to be copied into a shared_ptr before usage
	std::cout << *spt << "\n";
    }
    else {
        std::cout << "gw is expired\n";
    }
}
 
int DEF_FUNC(vtest06_weak_ptr)
{
	TITLEH1(test weak_ptr)

    {
		TITLEH1("The shared ptr defined in the inner block")
        TRACE_CODE(auto sp = std::make_shared<int>(42););
		TRACE_CODE(gw = sp;)
 
		TITLEH2(observe called in the inner block)
		observe();
		
    }
 	TITLEH2(observe called the in outer block)
    observe();
}
END_SECTION(vtest06_weak_ptr)

	
BEGIN_SECTION(vtest06_unique_ptr)
	
struct B {
  virtual void bar() { std::cout << "B::bar\n"; }
  virtual ~B() = default;
};
struct D : B
{
    D() { std::cout << "D::D\n";  }
    ~D() { std::cout << "D::~D\n";  }
    void bar() override { std::cout << "D::bar\n";  }
};
 
// a function consuming a unique_ptr can take it by value or by rvalue reference
std::unique_ptr<D> pass_through(std::unique_ptr<D> p)
{
    p->bar();
    return p;
}
 
void close_file(std::FILE* fp) { std::fclose(fp); }
 
int DEF_FUNC(vtest06_unique_ptr)
{
  std::cout << "unique ownership semantics demo\n";
  {
      auto p = std::make_unique<D>(); // p is a unique_ptr that owns a D
      auto q = pass_through(std::move(p)); 
      assert(!p); // now p owns nothing and holds a null pointer
      q->bar();   // and q owns the D object
  } // ~D called here
 
  std::cout << "Runtime polymorphism demo\n";
  {
    std::unique_ptr<B> p = std::make_unique<D>(); // p is a unique_ptr that owns a D
                                                  // as a pointer to base
    p->bar(); // virtual dispatch
 
    std::vector<std::unique_ptr<B>> v;  // unique_ptr can be stored in a container
    v.push_back(std::make_unique<D>());
    v.push_back(std::move(p));
    v.emplace_back(new D);
    for(auto& p: v) p->bar(); // virtual dispatch
  } // ~D called 3 times
 
  std::cout << "Custom deleter demo\n";
  std::ofstream("demo.txt") << "demo.txt testing..."; // prepare the file to read
  {
      std::unique_ptr<std::FILE, decltype(&close_file)> fp(std::fopen("demo.txt", "r"),
                                                           &close_file);
      if(fp){ // fopen could have failed; in which case fp holds a null pointer
			int c;
			while((c = std::fgetc(fp.get())) != EOF)
				std::cout << (char)c ;
			std::cout << '\n';
	  }else
		  std::cout << "Error: there's no 'demo.txt' for test under the current work directory!\n";
  } // fclose() called here, but only if FILE* is not a null pointer
    // (that is, if fopen succeeded)
 
  std::cout << "Custom lambda-expression deleter demo\n";
  {
    std::unique_ptr<D, std::function<void(D*)>> p(new D, [](D* ptr)
        {
            std::cout << "destroying from a custom deleter...\n";
            delete ptr;
        });  // p owns D
    p->bar();
  } // the lambda above is called and D is destroyed
 
  std::cout << "Array form of unique_ptr demo\n";
  {
      std::unique_ptr<D[]> p{new D[3]};
  } // calls ~D 3 times
}

END_SECTION(vtest06_unique_ptr)
	
BEGIN_SECTION(vtest06_unique_lock)
struct Box {
    explicit Box(int num) : num_things{num} {}
 
    int num_things;
    std::mutex m;
};
 
void transfer(Box &from, Box &to, int num)
{
    // don't actually take the locks yet
    std::unique_lock<std::mutex> lock1(from.m, std::defer_lock);
    std::unique_lock<std::mutex> lock2(to.m, std::defer_lock);
 
    // lock both unique_locks without deadlock
    std::lock(lock1, lock2);
 
    from.num_things -= num;
    to.num_things += num;
 
    // 'from.m' and 'to.m' mutexes unlocked in 'unique_lock' dtors
}
 
int DEF_FUNC(vtest06_unique_lock)
{
	ANNOTATE(To avoid dead lock, we have three solutuions: 1. use std::defer_lock & unique_lock)
	ANNOTATE(                                              2. use std::adopted_lock & lock_guard)
	ANNOTATE(                                              3. use scoped_lock)
    Box acc1(100);
    Box acc2(50);
 
    std::thread t1(transfer, std::ref(acc1), std::ref(acc2), 10);
    std::thread t2(transfer, std::ref(acc2), std::ref(acc1), 5);
 
    t1.join();
    t2.join();
}
END_SECTION(vtest06_unique_lock)